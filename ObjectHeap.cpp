#include "stdafx.h"
#include "ObjectHeap.h"
#include "types.h"
#include "ClassHeap.h"

ObjectHeap::ObjectHeap(void)
:m_nNextObjectID(1)
{
}

ObjectHeap::~ObjectHeap(void)
{
}

Object ObjectHeap::CreateObject(JavaClass* pClass)
{
	Object object;	
	object.heapPtr=(__int64_t)NULL;
	object.type=0;

	if(pClass == NULL) return object;
	u4 some_count = pClass->GetObjectFieldCount();
	u4 osize= some_count+1; //+1 for class pointer
	Variable *obj = new Variable[osize];
	if(!obj) return object;
	memset(obj, 0, sizeof(Variable)*osize);
	object.heapPtr=m_nNextObjectID++;
	obj[0].ptrValue =(__int64_t) pClass;

	m_ObjectMap.SetAt((void *)object.heapPtr,obj);  // TODO map

	return object;
}

Object ObjectHeap::CreateStringObject(char* pStrValue, ClassHeap *pClassHeap)
{
	Object object;	
	object.heapPtr=(__int64_t)NULL;
	object.type=0;

	if(pClassHeap == NULL) return object;
	#ifdef JOSBUILD
	JavaClass *pClass=pClassHeap->GetClass("String");
	#else  // Linux
	JavaClass *pClass=pClassHeap->GetClass("java/lang/String");
	#endif

	if(pClass == NULL) return object;	

	object = CreateObject(pClass);
	Variable *pVar= this->GetObjectPointer(object);
	if(pVar==NULL) return object;

	pVar[1].ptrValue=(__int64_t)pStrValue;

	return object;
}

bool ObjectHeap::CreateObjectArray(JavaClass* pClass, u4 count, Object& object)
{
	Variable *pVar= new Variable[count+1];

	if(pVar)
	{
		memset(pVar, 0, sizeof(Variable)*(count+1));
		pVar[0].ptrValue = (__int64_t)pClass;
	}
	else
		return false;

	object.heapPtr=m_nNextObjectID++;
	
	m_ObjectMap.SetAt((void *)object.heapPtr,pVar);  // TODO map

	return true;
}

Variable* ObjectHeap::GetObjectPointer(Object object)
{
	void *obj = NULL;
	if(!m_ObjectMap.Lookup((void *)object.heapPtr, obj))  // TODO map
		return NULL;

	return (Variable*)obj;
}

Object ObjectHeap::CreateNewArray(u1 type, i4 count)
{
	Variable *obj= new Variable[count+1];
	Object object;
	object.heapPtr=0;
	object.type=type;

	if(obj)
	{
		memset(obj, 0, sizeof(Variable)*(count+1));
		object.heapPtr=m_nNextObjectID++;
		obj[0].intValue = type;

		m_ObjectMap.SetAt((void *)object.heapPtr,obj);  // TODO map
	}

	return object;
}
