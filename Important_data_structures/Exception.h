//  Multiple include guard start
#ifndef EXCEPTION_H_INCLUDED__
#define EXCEPTION_H_INCLUDED__

#include <string>

struct Exception
{
//	Constructors/destructor
/*
		Exception constructor
		Params: message
*/
	Exception(const std::wstring& message_) : message(message_)
	{
	}

//	Members
	std::wstring message;
};

//  Multiple include guard end
#endif