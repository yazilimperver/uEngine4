#include "gl_support.h"
#include "gl_include.h"

#ifndef ANDROID
extern bool CheckGLError(std::string& errorList)
{
	GLenum err;
	bool isErrorOccurred = false;

	while ((err = glGetError()) != GL_NO_ERROR) 
	{
		errorList.append((char*)glewGetErrorString(err));
		errorList.append("\r\n");

		isErrorOccurred = true;
	}

	return isErrorOccurred;
}

#else
extern bool CheckGLError(std::string& errorList)
{
	return false;
}
#endif
