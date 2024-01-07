// kjvm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "kjvm.h"
#include "JavaClass.h"
#include "ClassHeap.h"
#include "types.h"
#include "constants.h"
#include "ExecutionEngine.h"
#include "ObjectHeap.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif


using namespace std;

JavaClass* LoadClass(char* strClassPath)
{	
	JavaClass *pClass = new JavaClass();
	if(!pClass->LoadClassFromFile(strClassPath))
	{
		free(pClass);
		pClass=NULL;
	}

	return pClass;
}

void ShowClassInfo(JavaClass* pClass);

void Execute(char* strClass)
{
	char* path=strClass;
	ClassHeap heap;
	JavaClass *pClass1, *pClass2, *pClass3;
	pClass1 = new JavaClass();
	pClass2 = new JavaClass();

	bool bRet=heap.LoadClass(strClass, pClass1);
	#ifdef JOSBUILD
	bRet=heap.LoadClass("Object", pClass2);  // to evade dirs in JOS
	#else  // Linux
	bRet=heap.LoadClass("java/lang/Object", pClass2);
	#endif

	ObjectHeap oheap;

	Frame *pFrameStack = new Frame[20];
	Frame::pBaseFrame = pFrameStack;

	memset(pFrameStack, 0, sizeof(Frame)*20);

	Frame::pOpStack = new Variable[100];
	memset(Frame::pOpStack, 0, sizeof(Variable)*100);

	ExecutionEngine ex;
	ex.pClassHeap = &heap;
	ex.pObjectHeap = &oheap;
	int startFrame=0;

	Object object=oheap.CreateObject(pClass1);
	JavaClass *pVirtualClass=pClass1;
	// Entry point EntryPoint
	// TODO make public static void main entry point
	int mindex = pClass1->GetMethodIndex("Entry","()I",pVirtualClass);
	pFrameStack[startFrame].pClass = pVirtualClass;	

	pFrameStack[startFrame].pMethod = &pVirtualClass->methods[mindex];
	pFrameStack[startFrame].stack = Frame::pOpStack;
	pFrameStack[startFrame].sp = pFrameStack[startFrame].pMethod->pCode_attr->max_locals;
	pFrameStack[startFrame].stack[0].object = object;
	ex.Execute(&pFrameStack[startFrame]);

}



int _tmain(int argc, char** argv)
{
	int nRetCode = 0;

	if(argc<2) return -1;

	// TODO: many files
	Execute(argv[1]); 
	
	return nRetCode;
}

void Test2()
{
	// char* path=_T("Test");

	// char* path2=_T("java\\lang\\Object");

	//to evade dirs in JOS
	const char* path = "Test";
	const char* path2 = "Object";

	ClassHeap heap;
	JavaClass *pClass1, *pClass2, *pClass3;
	pClass1 = new JavaClass();
	pClass2 = new JavaClass();

	bool bRet=heap.LoadClass(path, pClass1);
	bRet=heap.LoadClass(path2, pClass2);

	pClass3=heap.GetClass("Test");

	for(int i=0;pClass3&& i< pClass3->interfaces_count; i++)
	{
		u2 intr=pClass3->interfaces[i];
		char* name;
		cp_info *pi=pClass3->constant_pool[intr];
		assert(pi->tag == CONSTANT_Class);
		char *p=(char *)pi;
		int ni=getu2((char *)(&p[1]));
		pClass3->GetStringFromConstPool(ni, name);

		printf("Loading Interface %s\n", name);
		JavaClass *pClass4 = new JavaClass();
		bRet=heap.LoadClass(name, pClass4);

		if(bRet) ShowClassInfo(pClass4);
	}
}

void ShowClassInfo(JavaClass* pClass)
{
	if(!pClass) return;

	// TODO make debug print tag like ">>""

	char* name= pClass->GetName();
	printf("Class Name = [%s]\n",name);
	name= pClass->GetSuperClassName();
	printf("Super Class Name = [%s]\n",name);

	printf("Object Size = [%u]\n", pClass->GetObjectSize());
	
	for(int i=1;i<pClass->constant_pool_count-1;i++)
	{		
		char* strRetVal;
		printf("Pool %d Type = %d ", i,pClass->constant_pool[i]->tag); 
		if(1!=pClass->constant_pool[i]->tag)
			continue;
		pClass->GetStringFromConstPool(i, strRetVal);	
		printf("String at %d [%s]\n",i, strRetVal);
	}
	
	for(int i=0;i<pClass->methods_count;i++)
	{
		if(pClass->methods[i].pCode_attr != NULL)
		{
			printf("Method %d\nCode Length= %d\n", i,pClass->methods[i].pCode_attr->code_length);
			printf("Max stack = %d, Max Locals = %d, Exception table length= %d\nCODE\n",pClass->methods[i].pCode_attr->max_stack, pClass->methods[i].pCode_attr->max_locals, pClass->methods[i].pCode_attr->exception_table_length);		

			for(u4 j=0;j<pClass->methods[i].pCode_attr->code_length;j++)
				printf("%d ", pClass->methods[i].pCode_attr->code[j]);
			printf("\nENDCODE\n");
		}
		else if(pClass->methods[i].access_flags && ACC_NATIVE)
		{
			printf("Method %d is native\n",i);
		}
	}

	for(int i=0; i< pClass->fields_count; i++)
	{
		char* name, * desc;

		pClass->GetStringFromConstPool(pClass->fields[i].name_index, name);
		pClass->GetStringFromConstPool(pClass->fields[i].descriptor_index, desc);
		printf("Filed %d: Name: %s Type: %s\n",i, name, desc);
	}

	for(int i=0; i< pClass->interfaces_count; i++)
	{
		u2 intr=pClass->interfaces[i];
		char* name;
		cp_info *pi=pClass->constant_pool[intr];
		assert(pi->tag == CONSTANT_Class);
		char *p=(char *)pi;
		int ni=getu2((char *)(&p[1]));
		pClass->GetStringFromConstPool(ni, name);

		printf("Interface %d: Name %s\n",i, name);

	}
}
//Entry Point EntryPoint
#ifdef JOSBUILD
void
umain(int argc, char **argv) {
    binaryname = "java";
	_tmain(argc, argv);
}
#else  // Linux
int main(int argc, char ** argv){
	_tmain(argc, argv);
}
#endif

