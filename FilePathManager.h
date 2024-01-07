#pragma once

#ifndef JOSBUILD
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <sys/stat.h> 
#include <fcntl.h> 
#endif

class FilePathManager
{
public:

	inline void * operator new(size_t size){
		// return malloc(size);
		return calloc(size,sizeof(char));
	}
	inline void operator delete(void * ptr){
		if(ptr != NULL)
			free(ptr);
	}

	FilePathManager(void);
public:
	~FilePathManager(void);
public:
	bool GetAbsolutePath(char * strRelativePath, char ** strAbsolutePath);
};
