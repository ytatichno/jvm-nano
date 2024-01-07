#include "stdafx.h"

#include "NativeMethods.h"
#include "ObjectHeap.h"
#include "ClassHeap.h"

#ifndef MAX_STR_SIZE
#define MAX_STR_SIZE 2048
#endif

Variable Add(RuntimeEnvironment* pRuntimeEnvironment)
{
	Frame* pFrameStack=pRuntimeEnvironment->pFrameStack;

	Variable returnVal;
	Frame *pFrame=&pFrameStack[0];
	returnVal.intValue= pFrame->pOpStack[pFrame->sp].intValue + pFrame->pOpStack[pFrame->sp-1].intValue;
	return returnVal;
}

Variable Print(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	Object object=pFrame->stack[pFrame->sp].object;
	Variable *pVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(object);
	if(pVar)
	{
		char*pString = (char*)pVar[1].ptrValue;
		if(pString)
			printf("%s",pString);
	}

	returnVal.intValue=0;
	return returnVal;	
}

Variable String_valueOf_F(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;

	//static method
	f4 floatVal=pFrame->stack[0].floatValue;

	char* str = (char*)calloc(16, sizeof(char));
	// str.Format(_T("%f"), floatVal);
	// TODO overflow security
	snprintf(str, 16, "%f", floatVal);
	returnVal.object=pRuntimeEnvironment->pObjectHeap->CreateStringObject(str, pRuntimeEnvironment->pClassHeap);			
	
	return returnVal;
}
//TODO delete or write LONG
Variable String_valueOf_J(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	//Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	//ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	//ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;

	////static method
	//f4 floatVal=pFrame->stack[0].floatValue;

	//CString str;
	//str.Format(_T("%f"), floatVal);
	//returnVal.object=pRuntimeEnvironment->pObjectHeap->CreateStringObject(&str, pRuntimeEnvironment->pClassHeap);			
	
	return returnVal;
}

//Method java/lang/StringBuilder.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
Variable StringBuilder_append_String(RuntimeEnvironment* pRuntimeEnvironment)
{
	// we put a CString object as the first field in StringBuilder object

	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	Object object=pFrame->stack[pFrame->sp].object;
	Variable *pVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(object);
	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pVar && pThisVar)
	{
		char*pString = (char*)pVar[1].ptrValue;
		char*pThisString = (char*)pThisVar[1].ptrValue;

		if(pThisVar[1].ptrValue==(__int64_t)NULL)
		{
			size_t pStringLen = strnlen(pString, MAX_STR_SIZE-1)+1;
			pThisString = (char*)calloc(pStringLen, sizeof(char));
			pThisVar[1].ptrValue= (__int64_t)pThisString;  // (LONG_PTR) (pThisString=new CString());
			strncpy(pThisString, pString, pStringLen-1);
			pThisString[pStringLen - 1] = '\0';
		}

		else if(pThisString && pString)
		{

			char * pThisStringOld = pThisString;

			size_t thisString_size = strnlen(pThisStringOld, MAX_STR_SIZE-1);
			size_t string_size = strnlen(pString, MAX_STR_SIZE-1);
			size_t total_size = thisString_size + string_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			
			snprintf(pThisString, MAX_STR_SIZE, "%.*s%.*s", (int)thisString_size, pThisStringOld, (int)string_size, pString);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}
		}
	}
	
	returnVal.object=thisObject;

	return returnVal;
}

Variable StringBuilder_append_I(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	i4 intVal=pFrame->stack[pFrame->sp].intValue;
	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{		
		char *pThisString = (char *)pThisVar[1].ptrValue;
		
		if(pThisString)
		{
				
			char * pThisStringOld = pThisString;

			size_t thisString_size = (pThisStringOld != NULL ? strnlen(pThisStringOld, MAX_STR_SIZE-1) : 0);
			size_t int_size = 15;
			size_t total_size = thisString_size + int_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			
			snprintf(pThisString, MAX_STR_SIZE, "%.*s%d", (int)thisString_size, pThisStringOld, intVal);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}
		}
	}
	
	returnVal.object=thisObject;

	return returnVal;
}

Variable StringBuilder_append_C(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	u1 charValue = pFrame->stack[pFrame->sp].charValue;

	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{		
		char *pThisString = (char *)pThisVar[1].ptrValue;

		if(pThisString)
		{

			char * pThisStringOld = pThisString;

			size_t thisString_size = (pThisStringOld != NULL ? strnlen(pThisStringOld, MAX_STR_SIZE-1) : 0);
			size_t char_size = 1;
			size_t total_size = thisString_size + char_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			
			snprintf(pThisString, MAX_STR_SIZE, "%.*s%c", (int)thisString_size, pThisStringOld, charValue);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}
		}
	}
	
	returnVal.object=thisObject;

	return returnVal;
}

Variable StringBuilder_append_Z(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	u4 boolValue = pFrame->stack[pFrame->sp].intValue;

	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{		
		char *pThisString = (char *)pThisVar[1].ptrValue;


		if(pThisString)
		{
			char * pThisStringOld = pThisString;

			size_t thisString_size = (pThisStringOld != NULL ? strnlen(pThisStringOld, MAX_STR_SIZE-1) : 0);
			size_t bool_size = 5;
			size_t total_size = thisString_size + bool_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			if(boolValue)
				snprintf(pThisString, MAX_STR_SIZE, "%.*strue", (int)thisString_size, pThisStringOld);
			else
				snprintf(pThisString, MAX_STR_SIZE, "%.*sfalse", (int)thisString_size, pThisStringOld);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}
		}
	}
	
	returnVal.object=thisObject;

	return returnVal;

}

Variable StringBuilder_append_F(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	f4 floatValue = pFrame->stack[pFrame->sp].floatValue;

	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{		
		char *pThisString = (char *)pThisVar[1].ptrValue;

		if(pThisString)
		{

			char * pThisStringOld = pThisString;

			size_t thisString_size = (pThisStringOld != NULL ? strnlen(pThisStringOld, MAX_STR_SIZE-1) : 0);
			size_t float_size = 15;
			size_t total_size = thisString_size + float_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			
			snprintf(pThisString, MAX_STR_SIZE, "%.*s%f", (int)thisString_size, pThisStringOld, floatValue);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}

		}
	}
	
	returnVal.object=thisObject;

	return returnVal;

}

//LONG
Variable StringBuilder_append_J(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;

	i4 i4High = pFrame->stack[pFrame->sp-1].intValue;
	i4 i4Low = pFrame->stack[pFrame->sp].intValue;

	i8 longValue= MAKEI8(i4High, i4Low);

	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{		
		char *pThisString = (char *)pThisVar[1].ptrValue;

		if(pThisString)
		{

			char * pThisStringOld = pThisString;

			size_t thisString_size = (pThisStringOld != NULL ? strnlen(pThisStringOld, MAX_STR_SIZE-1) : 0);
			size_t long_size = 31;
			size_t total_size = thisString_size + long_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			
			snprintf(pThisString, MAX_STR_SIZE, "%.*s%lld", (int)thisString_size, pThisStringOld, (long long int)longValue);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}
		}
	}
	
	returnVal.object=thisObject;

	return returnVal;

}

//TODO DOUBLE
Variable StringBuilder_append_D(RuntimeEnvironment* pRuntimeEnvironment)
{
	
	Variable returnVal;
	/*
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	
	f4 floatValue1 = pFrame->stack[pFrame->sp-1].floatValue;
	f4 floatValue2 = pFrame->stack[pFrame->sp].floatValue;

	f8 floatValue=0.0

	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{		
		CString *pThisString = (CString *)pThisVar[1].ptrValue;

		if(pThisVar[1].ptrValue==(__int64_t)NULL)
		{
			pThisVar[1].ptrValue=(LONG_PTR) (pThisString=new CString());
		}

		if(pThisString)
		{
			//We now use...
			CString str;
			str.Format(_T("%f"), floatValue);
			pThisString->Append(str.GetBuffer());
		}
	}
	
	returnVal.object=thisObject;
	*/
	returnVal.floatValue=0;

	return returnVal;

}


Variable StringBuilder_append_Object(RuntimeEnvironment* pRuntimeEnvironment)
{
	Variable returnVal;
	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;
	Object object=pFrame->stack[pFrame->sp].object;
	Variable *pVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(object);
	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	
	// TODO: call objects toString and append
	if(pThisVar)
	{
		
		char *pThisString = (char *)pThisVar[1].ptrValue;

		char* pString;
		if(pVar)
		{
			JavaClass *pClass = (JavaClass *)pVar[0].ptrValue;		
			// str.Format(_T("Object [%X] of Class %ws"),object.heapPtr, pClass->GetName());
			pString = (char*)calloc(512, sizeof(char));
			snprintf(pString, 512, "Object [%p] of Class %s", (void*)object.heapPtr, pClass->GetName());
		}
		else{
			pString = (char*)calloc(8,sizeof(char));
			sprintf(pString, "null");
		}
			

		if(pThisVar[1].ptrValue==(__int64_t)NULL)
		{
			size_t pStringLen = strnlen(pString, MAX_STR_SIZE-1)+1;
			pThisString = (char*)calloc(pStringLen, sizeof(char));
			pThisVar[1].ptrValue= (__int64_t)pThisString;  // (LONG_PTR) (pThisString=new CString());
			strncpy(pThisString, pString, pStringLen-1);
			pThisString[pStringLen - 1] = '\0';
		}

		else if(pThisString && pString)
		{
			//We now use...
			// pThisString->Append(pString->GetBuffer());
			//TODO Improve StringBuilder to prevent reallocs

			char * pThisStringOld = pThisString;

			size_t thisString_size = strnlen(pThisStringOld, MAX_STR_SIZE-1);
			size_t string_size = strnlen(pString, MAX_STR_SIZE-1);
			size_t total_size = thisString_size + string_size + 1;
			if(total_size > MAX_STR_SIZE)
				total_size = MAX_STR_SIZE;
			
			pThisString = (char*)calloc(total_size, sizeof(char));
			
			snprintf(pThisString, MAX_STR_SIZE, "%.*s%.*s", (int)thisString_size, pThisStringOld, (int)string_size, pString);

			if(pThisStringOld != NULL){
				free(pThisStringOld);
			}
		}
	}
	
	
	returnVal.object=thisObject;

	return returnVal;
}

Variable StringBuilder_toString_String(RuntimeEnvironment* pRuntimeEnvironment)
{
	// we put a CString object as the first field in StringBuilder object

	Variable returnVal;
	returnVal.object.heapPtr=(__int64_t)NULL;

	Frame *pFrame=&pRuntimeEnvironment->pFrameStack[0];
	ObjectHeap *pObjectHeap = pRuntimeEnvironment->pObjectHeap;
	ClassHeap *pClassHeap = pRuntimeEnvironment->pClassHeap;
	Object thisObject=pFrame->stack[0].object;

	Variable *pThisVar=pRuntimeEnvironment->pObjectHeap->GetObjectPointer(thisObject);

	if(pThisVar)
	{
		

		if(pThisVar[1].ptrValue==(__int64_t)NULL)
		{
			pThisVar[1].ptrValue= (__int64_t)calloc(4, sizeof(char));  // (LONG_PTR) (pThisString=new CString());
		}

		char *pThisString = (char *)pThisVar[1].ptrValue;

		if(pThisString)
		{
			returnVal.object=pRuntimeEnvironment->pObjectHeap->CreateStringObject(pThisString, pRuntimeEnvironment->pClassHeap);
		}
	}
	
	return returnVal;
}