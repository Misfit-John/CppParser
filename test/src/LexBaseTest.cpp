#include "LexBase.h"
#include "CmdInputFactor.h"
#include <gtest/gtest.h>
#include "JZLogger.h"

//this will be a large test, will have lots of test here, I don't sure if we should seperate this into many parts

//this is lib test entryp, I will use this file as entry
void globalInitAtBegin();

//cover test: comment, basic input
TEST(LexBase, simpleInput){
  //this is really a strong test, so don't do it for more than one file every time
  int argc = 2;
  char argv0[128] = {0},argv1[128] = {0};
  strcpy(argv0,"tester");
  strcpy(argv1,"./test/TestSet/simple");
  char* argv[2] = {argv0,argv1};

	//init
	globalInitAtBegin();

	JZSetLoggerLevel(JZ_LOG_TEST);

	//analyze command line input
	CmdInputFactor::getInstance()->analyze(argc, argv);

	//now begin to analyze the files input from command line
	string toCompileFile = CmdInputFactor::getInstance()->getNextFile();

  LexBase lex;
  lex.analyzeAFile(toCompileFile);
  LexRecList recList = lex.getRecList();

	JZSetLoggerLevel(JZ_LOG_DEBUG);
  lex.printLexRec();
	JZSetLoggerLevel(JZ_LOG_TEST);
  EXPECT_EQ(3, recList.size());
  ASSERT_STREQ("int", recList[0].word.c_str());
  ASSERT_STREQ("a", recList[1].word.c_str());
  ASSERT_STREQ(";", recList[2].word.c_str());

}