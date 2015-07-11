#include "DefineManager.h"
#include "ErrorCode.h"
#include "JZLogger.h"

DefineManager::DefineManager()
{
	
}

DefineManager::~DefineManager()
{

}

DefineManager* DefineManager::getGlobalInstance()
{
	static DefineManager* instance = NULL;
	if (NULL == instance)
	{
		instance = new DefineManager();
	}
	return instance;
}

void DefineManager::init()
{
	//
}

DefineManager::DefineManagerReturnCode DefineManager::isDefined(const string& srcDefine)
{
	if (mCanceledDefine.end() != mCanceledDefine.find(srcDefine))
	{
		return eDefMgrNotDefined;
	}
	if (mSrcLexMap.end() != mSrcLexMap.find(srcDefine))
	{
		return eDefMgrDefined;
	}
	DefineManager* globalInstance = DefineManager::getGlobalInstance();
	if(this != globalInstance && NULL != globalInstance)
	{
		//this is not global instance
		DefineManagerReturnCode ret = globalInstance->isDefined(srcDefine);
		if (eDefMgrDefined == ret)
		{
			return ret;
		}
	}
	return eDefMgrNotDefined ;
}

DefineManager::DefineManagerReturnCode DefineManager::addDefineMap(const string& src, const DefineRec& rec)
{
	if(eDefMgrDefined == isDefined(src))
	{
		return eDefMgrDoubleDefineMacro;
	}
	if (rec.key != src)
	{
		return eDefMgrKeyDiffFromSrc;
	}
	mSrcLexMap[src] = rec;

	return eDefMgrNoError;
}

const DefineRec* DefineManager::findDefineMap(const string& srcDefine)
{
	if (eDefMgrNotDefined == isDefined(srcDefine))
	{
		return NULL;
	}

	//for define macro ,use the one that is latest defined
	auto it = mSrcLexMap.find(srcDefine);
	if (mSrcLexMap.end() != it)
	{
		return &(it->second);
	}

	DefineManager* globalInstance = DefineManager::getGlobalInstance();
	if (this != globalInstance && NULL != globalInstance)
	{
		auto ret = globalInstance->findDefineMap(srcDefine);
		if(NULL != ret)
		{
			return ret;	
		}
	}
	return NULL;
}
