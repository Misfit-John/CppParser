#ifndef __ERROR_CODE_H__
#define __ERROR_CODE_H__

namespace JZErrorCode
{
	enum ErrorCode
	{
		errNoError		= 0,
		errUnknow 		= 1,
		errOpenFileFail = 2,
		errNoSuchPath	= 3,
		errDoubleDefineMarco = 4,
		errSharpFollowNothing = 5,
		errSharpFollowWithUnknowKeyWord = 6,
		errSharDefineFollowWithNothing = 7,
		errSharpIncludeNotSurroundWithRightSeperator = 8,
		errSharpIncludeFollowNoFile = 9,
		errCommentBlockDoEnd = 10,
	};
};

#endif //__ERROR_CODE_H__
