#pragma once
#include "types.h"

#ifndef JOSBUILD
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <sys/stat.h> 
#include <fcntl.h> 
#endif

// #include "afxmt.h"
class ClassHeap;
class ObjectHeap;

class RuntimeEnvironment
{
public:
	Frame *pFrameStack;
	ClassHeap *pClassHeap;
	ObjectHeap *pObjectHeap;

	// CCriticalSection criticalSection;  // TODO mutex
};
Variable Add(RuntimeEnvironment* pRuntimeEnvironment);
Variable Print(RuntimeEnvironment* pRuntimeEnvironment);

Variable String_valueOf_F(RuntimeEnvironment* pRuntimeEnvironment);
Variable String_valueOf_J(RuntimeEnvironment* pRuntimeEnvironment);

Variable StringBuilder_append_String(RuntimeEnvironment* pRuntimeEnvironment);
Variable StringBuilder_append_I(RuntimeEnvironment* pRuntimeEnvironment);
Variable StringBuilder_append_C(RuntimeEnvironment* pRuntimeEnvironment);
Variable StringBuilder_append_Z(RuntimeEnvironment* pRuntimeEnvironment);
Variable StringBuilder_append_Object(RuntimeEnvironment* pRuntimeEnvironment);
Variable StringBuilder_append_F(RuntimeEnvironment* pRuntimeEnvironment);
Variable StringBuilder_append_J(RuntimeEnvironment* pRuntimeEnvironment);

Variable StringBuilder_toString_String(RuntimeEnvironment* pRuntimeEnvironment);
typedef Variable (*pNativeMethod)(RuntimeEnvironment* pRuntimeEnvironment);