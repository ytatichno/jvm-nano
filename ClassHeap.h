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



class ClassHeap
{
	CMapStringToPtr *m_ClassMap;
	FilePathManager *pFilePathManager;
public:
	ClassHeap(void);
public:
	virtual ~ClassHeap(void);
public:
	bool AddClass(JavaClass* pJavaClass);
	JavaClass* GetClass(const char * strClassName);
	bool LoadClass(const char * strClassName, JavaClass *pClass);
};
 