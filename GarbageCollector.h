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

class RuntimeEnvironment;
class GarbageCollector  // TODO GC
{

public:
	GarbageCollector(void);
	virtual ~GarbageCollector(void);
	virtual bool Execute(RuntimeEnvironment* pRuntimeEnvironment);
protected:
	virtual bool MarkGarbage(RuntimeEnvironment* pRuntimeEnvironment);
	virtual bool SweepGarbase(RuntimeEnvironment* pRuntimeEnvironment);

private:

	// The word is 1 for marked and 0 for unmarked
	CMapPtrToWord m_Objects;
};
