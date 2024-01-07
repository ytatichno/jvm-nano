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

#include "CMaps.h"

class JavaClass;
class FilePathManager;



/// @brief singleton
class ClassHeap 
{
	CMapStringToPtr *m_ClassMap;
	FilePathManager *pFilePathManager;
private:  // singleton
	ClassHeap(void);
	ClassHeap(const ClassHeap&);
	ClassHeap& operator=(ClassHeap&);

	static ClassHeap * p_instance;

public:
	virtual ~ClassHeap(void);  // probably should be private
public:

	inline void * operator new(size_t size){
		// return malloc(size);
		return calloc(size,sizeof(char));
	}
	inline void operator delete(void * ptr){
		if(ptr != NULL)
			free(ptr);
	}

	static ClassHeap * getInstance();

	bool AddClass(JavaClass* pJavaClass);
	JavaClass* GetClass(const char * strClassName);
	bool LoadClass(const char * strClassName, JavaClass *pClass);
};
 