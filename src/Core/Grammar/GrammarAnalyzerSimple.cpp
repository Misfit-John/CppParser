/*********************************************************
  put some simple api into this file 
 ********************************************************/

#include "GrammarReturner.h"
#include "GrammarAnalyzer.h"
#include "GrammarUtil.h"
#include "LexUtil.h"
#include "JZLogger.h"

GrammarAnalyzer::GrammarAnalyzer(LexRecList list):
  mRecList(list),
  mTopBlock(GrammarBlock::createTopNode())
{

  mTopReturner = new GrammarReturnerBase(eGrmTop, "");
}

GrammarAnalyzer::~GrammarAnalyzer()
{
  delete mTopReturner;
}

GrammarBlock* GrammarAnalyzer::getTopBlock()
{
  return &mTopBlock;
}

bool GrammarAnalyzer::isLegalVarIdentify(const string& id, GrammarBlock* curBlock)
{
  const VarDefine* def = curBlock->getVarDefInBlock(id);
  if(NULL != def)
  {
    return false;
  }

  bool isKey = GrmUtilPtr->isKeyWord(id);
  if(true == isKey)
  {
    return false;
  }

  for(int i = 0 ; i < id.size() ; i++)
  {
    if(i == 0)
    {
      if (true == LexUtil::isConstNumberChar(id[i]))
      {
        return false;
      }
      else if (true == LexUtil::isInterpunction(id[i]))
      {
        return false;
      }
    }
    char curChar = id[i];
    if (false == LexUtil::isIdentifyChar(curChar))
    {
      return false;
    }
  }
  return true;
}

bool GrammarAnalyzer::invoke(handler han,const string& handStr, const string& func, const int line, const int index, int& lastIndex, GrammarBlock* curBlock, GrammarReturnerBase* ret,bool isOpt)
{
  mInvokeCount[handStr]++;
  if (index == mRecList.size())
  {
    return false;
  }
  if (false == mLoopBreaker.insert(func, line, index))
  {
    return false;
  }
  int32 tryLast = lastIndex;
  uint32 invokeRet = (this->*han)(index, tryLast, curBlock, ret);
  mLoopBreaker.remomve(func, line, index);
  if (eGrmErrNoError == invokeRet)
  {
    lastIndex = tryLast;
    JZWRITE_DEBUG("true for %s:%d:%d", func.c_str(), line, index);
    return true;
  }
  else
  {
    if (isOpt)
    {
      lastIndex = index - 1;
      JZWRITE_DEBUG("true for %s:%d:%d", func.c_str(), line, index);
      return true;
    }
    JZWRITE_DEBUG("false for %s:%d:%d", func.c_str(), line, index);
    return false;
  }
}

bool GrammarAnalyzer::invoke(const string& file, const int line, const int index,int& lastIndex, const string& key, bool isOpt, bool inOneLine)
{
  JZWRITE_DEBUG("invoked by %s:%d:%d", file.c_str(), line, index);
  if (mRecList.size() <= index)
  {
    return false;
  }
  if (false == mLoopBreaker.insert(file, line, index))
  {
    return false;
  }
  uint32 invokeRet = expect(key, index, inOneLine);
  mLoopBreaker.remomve(file, line, index);

  if (eGrmErrNoError == invokeRet)
  {
    lastIndex = index;
    JZWRITE_DEBUG("true for %s:%d:%d", file.c_str(), line, index);
    return true;
  }
  else
  {
    if (isOpt)
    {
      lastIndex = index - 1;
      JZWRITE_DEBUG("true for %s:%d:%d", file.c_str(), line, index);
      return true;
    }
    JZWRITE_DEBUG("false for %s:%d:%d", file.c_str(), line, index);
    return false;
  }
}

GrammarReturnerBase* GrammarAnalyzer::getReturner() const{
  return mTopReturner;
}

void GrammarAnalyzer::printInvokeCount() const{
  for(auto it = mInvokeCount.begin(); mInvokeCount.end()  != it ; it++ )
  {
    printf("Invoke:%s num:%d\n", it->first.c_str(), it->second);
  }
  
}
