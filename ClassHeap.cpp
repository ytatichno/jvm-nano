#include "stdafx.h"
#include "ClassHeap.h"
#include "JavaClass.h"
#include "FilePathManager.h"

// #include "string.h"
ClassHeap::ClassHeap(void)
{
	// m_ClassMap{};
	m_ClassMap = new CMapStringToPtr();
	pFilePathManager = new FilePathManager();
}

ClassHeap::~ClassHeap(void)
{
	
}

bool ClassHeap::AddClass(JavaClass* pJavaClass)
{
	if(!pJavaClass) return false;
	char * name=pJavaClass->GetName();

	//TODO- check if already exists

	m_ClassMap->SetAt(name, pJavaClass);
	return true;
}

JavaClass* ClassHeap::GetClass(const char * strClassName)
{
	printf(">>%d", ((CMapStringToPtr*)((u8)this + (u8)m_ClassMap))->size);
	void *pClass=NULL;
	if(!m_ClassMap->Lookup(strClassName, pClass))
	{
		pClass = malloc(sizeof(JavaClass));
		bool bRet=this->LoadClass(strClassName, (JavaClass*)pClass);
		if(!bRet)
		{
			free(pClass);
			pClass=NULL;
		}		
	}

	return (JavaClass*)pClass;
}

bool ClassHeap::LoadClass(const char * strClassName, JavaClass *pClass)
{
	char * path, * relPath;
	if(!pClass) return false;
	int classNameSize = strnlen(strClassName, MAX_STR_SIZE-1) + 1;
	char * strClassNameCopy = (char*)calloc(classNameSize, sizeof(char));
	memcpy(strClassNameCopy,strClassName, classNameSize*sizeof(char));


	relPath = append(strClassNameCopy,".class");
	if(!pFilePathManager->GetAbsolutePath(relPath, &path))
		return false;	

	bool bRet=pClass->LoadClassFromFile(path);

	if(!bRet) return false;

	pClass->SetClassHeap(this);

	return AddClass(pClass);
}
