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

class ObjectHeap
{
public:
	ObjectHeap(void);
public:
	virtual ~ObjectHeap(void);
public:
	virtual Variable* GetObjectPointer(Object object);
	Object CreateObject(JavaClass* pClass);
	Object CreateStringObject(char* pStrValue, ClassHeap *pClassHeap);
	Object CreateNewArray(u1 type, i4 count);
	bool CreateObjectArray(JavaClass* pClass, u4 count, Object& object);
private:
	CMapPtrToPtr m_ObjectMap;  // TODO map
	u4 m_nNextObjectID;

};
