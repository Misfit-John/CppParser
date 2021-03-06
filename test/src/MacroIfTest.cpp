#include "MacroLex.h"
#include "CmdInputFactor.h"
#include <gtest/gtest.h>
#include "JZLogger.h"

//cover case: basic test
TEST(MacroLex, macroIfTest1){
  //this is really a strong test, so don't do it for more than one file every time
  int argc = 2;
  char argv0[128] = {0},argv1[128] = {0};
  strcpy(argv0,"tester");
  strcpy(argv1,"./test/TestSet/macro_if_test_1");
  char* argv[2] = {argv0,argv1};

	JZSetLoggerLevel(JZ_LOG_TEST);

	//analyze command line input
	CmdInputFactor::getInstance()->analyze(argc, argv);

	//now begin to analyze the files input from command line
	string toCompileFile = CmdInputFactor::getInstance()->getNextFile();

  MacroLex lex;

  lex.analyzeAFile(toCompileFile);

  LexRecList recList = lex.getRecList();

  ASSERT_EQ(11, recList.size());
  ASSERT_STREQ("hello", recList[0].word.c_str());
  ASSERT_STREQ("nono", recList[1].word.c_str());
  ASSERT_STREQ("yes", recList[2].word.c_str());
  ASSERT_STREQ("yes3", recList[3].word.c_str());
  ASSERT_STREQ("defined", recList[4].word.c_str());
  ASSERT_STREQ("(", recList[5].word.c_str());
  ASSERT_STREQ("hello", recList[6].word.c_str());
  ASSERT_STREQ(")", recList[7].word.c_str());
  ASSERT_STREQ("yes5", recList[8].word.c_str());
  ASSERT_STREQ("yes6", recList[9].word.c_str());
  ASSERT_STREQ("yes7", recList[10].word.c_str());
}

//cover case: simple calculation
TEST(MacroLex, macroIfTest2){
  //this is really a strong test, so don't do it for more than one file every time
  int argc = 2;
  char argv0[128] = {0},argv1[128] = {0};
  strcpy(argv0,"tester");
  strcpy(argv1,"./test/TestSet/macro_if_test_2");
  char* argv[2] = {argv0,argv1};


	//analyze command line input
	CmdInputFactor::getInstance()->analyze(argc, argv);

	//now begin to analyze the files input from command line
	string toCompileFile = CmdInputFactor::getInstance()->getNextFile();

  MacroLex lex;

  lex.analyzeAFile(toCompileFile);

  LexRecList recList = lex.getRecList();

  ASSERT_EQ(17, recList.size());
  ASSERT_STREQ("yes0", recList[0].word.c_str());
  ASSERT_STREQ("yes1", recList[1].word.c_str());
  ASSERT_STREQ("yes2", recList[2].word.c_str());
  ASSERT_STREQ("yes3", recList[3].word.c_str());
  ASSERT_STREQ("yes4", recList[4].word.c_str());
  ASSERT_STREQ("yes5", recList[5].word.c_str());
  ASSERT_STREQ("yes6", recList[6].word.c_str());
  ASSERT_STREQ("yes7", recList[7].word.c_str());
  ASSERT_STREQ("yes9", recList[8].word.c_str());
  ASSERT_STREQ("yes10", recList[9].word.c_str());
  ASSERT_STREQ("yes11", recList[10].word.c_str());
  ASSERT_STREQ("yes12", recList[11].word.c_str());
  ASSERT_STREQ("yes13", recList[12].word.c_str());
  ASSERT_STREQ("yes14", recList[13].word.c_str());
  ASSERT_STREQ("yes16", recList[14].word.c_str());
  ASSERT_STREQ("yes17", recList[15].word.c_str());
  ASSERT_STREQ("yes18", recList[16].word.c_str());
}

//cover case: triple calculation
TEST(MacroLex, macroIfTest3){
  //this is really a strong test, so don't do it for more than one file every time
  int argc = 2;
  char argv0[128] = {0},argv1[128] = {0};
  strcpy(argv0,"tester");
  strcpy(argv1,"./test/TestSet/macro_if_test_3");
  char* argv[2] = {argv0,argv1};


	//analyze command line input
	CmdInputFactor::getInstance()->analyze(argc, argv);

	//now begin to analyze the files input from command line
	string toCompileFile = CmdInputFactor::getInstance()->getNextFile();

  MacroLex lex;

  lex.analyzeAFile(toCompileFile);

  LexRecList recList = lex.getRecList();

  ASSERT_EQ(10, recList.size());
  ASSERT_STREQ(recList[0].word.c_str(), "yes1");
  ASSERT_STREQ(recList[1].word.c_str(), "yes2");
  ASSERT_STREQ(recList[2].word.c_str(), "yes4");
  ASSERT_STREQ(recList[3].word.c_str(), "yes6");
  ASSERT_STREQ(recList[4].word.c_str(), "yes7");
  ASSERT_STREQ(recList[5].word.c_str(), "yes10");
  ASSERT_STREQ(recList[6].word.c_str(), "yes11");
  ASSERT_STREQ(recList[7].word.c_str(), "yes11");
  ASSERT_STREQ(recList[8].word.c_str(), "yes15");
  ASSERT_STREQ(recList[9].word.c_str(), "yes16");
}

//cover case: defined test
TEST(MacroLex, macroIfTest4){
  //this is really a strong test, so don't do it for more than one file every time
  int argc = 2;
  char argv0[128] = {0},argv1[128] = {0};
  strcpy(argv0,"tester");
  strcpy(argv1,"./test/TestSet/macro_if_test_4");
  char* argv[2] = {argv0,argv1};


	//analyze command line input
	CmdInputFactor::getInstance()->analyze(argc, argv);

	//now begin to analyze the files input from command line
	string toCompileFile = CmdInputFactor::getInstance()->getNextFile();

  MacroLex lex;

  lex.analyzeAFile(toCompileFile);

  LexRecList recList = lex.getRecList();

  ASSERT_EQ(2, recList.size());
  ASSERT_STREQ(recList[0].word.c_str(), "no1");
  ASSERT_STREQ(recList[1].word.c_str(), "no2");
}
