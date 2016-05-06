#include "GrammarData.h"
#include "StringUtil.h"
#include "JZLogger.h"

/*********************************************************
  Grammar Node 
 ********************************************************/

GrammarNode::GrammarNode():
  mFather(NULL)
{
}

GrammarNode::~GrammarNode()
{
  auto it = mChildrens.begin();
  for(;it != mChildrens.end(); it++)
  {
    delete (*it);
  }
}

void GrammarNode::setFather(GrammarNode* father)
{
  mFather = father;
}
/*********************************************************
  Grammar node end
 Grammar Block start 
 ********************************************************/
GrammarBlock::GrammarBlock(){}
GrammarBlock::~GrammarBlock(){}

GrammarBlock GrammarBlock::createTopNode()
{
  JZFUNC_BEGIN_LOG();
  GrammarBlock instance;
  instance.mFather = NULL;
  instance.mNodeType = eGrammarNodeTopNode;

  //add other init for top class node
  vector<string> basicInt;
  basicInt.push_back("int");
  BasicDefine *intDefine = new BasicDefine(basicInt);
  instance.addDataTypeDefine(intDefine);

  vector<string> basicUnsignedInt;
  basicUnsignedInt.push_back("unsigned");
  basicUnsignedInt.push_back("int");
  BasicDefine *uintDefine = new BasicDefine(basicUnsignedInt);
  instance.addDataTypeDefine(uintDefine);

  vector<string> basicLong;
  basicLong.push_back("long");
  BasicDefine *longDefine = new BasicDefine(basicLong);
  instance.addDataTypeDefine(longDefine);

  vector<string> basicLongLong;
  basicLongLong.push_back("long");
  basicLongLong.push_back("long");
  BasicDefine *longLongDefine = new BasicDefine(basicLongLong);
  instance.addDataTypeDefine(longLongDefine);
  JZFUNC_END_LOG();
  return instance;
}

uint32 GrammarBlock::addDataTypeDefine(DataTypeDefine *dataType)
{
  dataType->setFather(this) ;

  string sig = dataType->getSignature();

  auto it = mDataTypeList.find(sig);
  if(mDataTypeList.end() != it)
  {
    return eGrammarErrorDoubleDefinedDataType;
  }
  mDataTypeList[sig] = dataType;
  mChildrens.push_back(mDataTypeList[sig]);

  return eGrammarErrorNoError;
}

uint32 GrammarBlock::addVarDefine(VarDefine* var)
{
  var->setFather(this);
  string key = var->getId();
  auto it = mVarList.find(key);
  if(mVarList.end() != it)
  {
    return eGrammarErrorDoubleDefinedVar;
  }
  mVarList[key] = var;
  mChildrens.push_back(mVarList[key]);
  return eGrammarErrorNoError;
}

VarDefine* GrammarBlock::getVarDef(const string key)
{
  auto it = mVarList.find(key);
  if(mVarList.end() == it)
  {
    return NULL;
  }
  else
  {
    return it->second;
  }
}

DataTypeDefine* GrammarBlock::getDataDef(const string key)
{
  auto it = mDataTypeList.find(key);
  if(mDataTypeList.end() == it)
  {
    return NULL;
  }
  else
  {
    return it->second;
  }
}
/*********************************************************
  GrammarBlock end
 DataTypeDefine begin 
 ********************************************************/

DataTypeDefine::DataTypeDefine():
  mBody(NULL)
{
}
DataTypeDefine::~DataTypeDefine()
{
//  if (NULL != mBody)
//  {
//    delete mBody;
//    mBody = NULL;
//  }
}

string DataTypeDefine::getSignature()
{
  return mSignature;
}

string DataTypeDefine::getKeyWord(int index)
{
  if(index < mKeyWords.size())
  {
    return mKeyWords[index];
  }
  else
  {
    return "";
  }
}

uint32 DataTypeDefine::addBody(GrammarBlock* body)
{
  if(NULL == body)
  {
    return eGrammarErrorUnknown;
  }

  body->setFather(this);
  mBody = body;
  mChildrens.push_back(body);
  

  return eGrammarErrorNoError;
}

/*********************************************************
  DataTypeDefine end
 BasicDefine beging 
 ********************************************************/

BasicDefine::BasicDefine(vector<string> keyWord)
{
  mKeyWords = keyWord;
  string tmpSig = "";
  for (int i = 0; i < keyWord.size(); i++) 
  {
    uint32 size = keyWord[i].size();
    tmpSig += "_" + StringUtil::tostr(size) + keyWord[i];
  }
  mSignature = tmpSig;
  mNodeType = eDataTypeBasic;
}

BasicDefine::~BasicDefine(){}

/*********************************************************
  BasicDefine end
 VarDefine begin 
 ********************************************************/

uint32 VarDefine::init(string id, DataTypeDefine* define)
{
  mIdentify = id;
  mDataType = define;
  if (NULL == define)
  {
    JZWRITE_ERROR("NULL define");
    return eGrammarErrorUnknown;
  }
  return eGrammarErrorNoError;
}

string VarDefine::getId()
{
  return mIdentify;
}

/*********************************************************
  VarDefine end
  EnumDefine begin
 ********************************************************/

EnumDefine::EnumDefine(string id)
{
  mKeyWords.push_back(id);
  mSignature = id;
  mNodeType = eDataTypeEnum;
}

EnumDefine::~EnumDefine(){
  JZFUNC_END_LOG();
}

uint32 EnumDefine::addField(const string& id)
{
  auto it = mFields.find(id);
  if(mFields.end() != it)
  {
    return eGrammarErrorDoubleDefinedVar;
  }
  //yes, this is not exactlly right value. I think a vector will be better for this.
  mFields[id] = mFields.size();
  return eGrammarErrorNoError;
}

uint32 EnumDefine::addField(const string& id, int value)
{
  auto it = mFields.find(id);
  if(mFields.end() != it)
  {
    return eGrammarErrorDoubleDefinedVar;
  }
  mFields[id] = value;
  return eGrammarErrorNoError;
}

bool EnumDefine::fieldExist(const string& id)
{
  auto it = mFields.find(id);
  if(mFields.end() != it)
  {
    return true;
  }
  else
  {
    return false;
  }
}
