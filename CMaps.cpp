#include "CMaps.h"
#include "stdafx.h"

CMapStringToPtr::CMapStringToPtr(){
    maxsize = 8;
	size = 0;
	list = (KV*)calloc(maxsize, sizeof(KV));    
	DLOG("your mama");
	printf(">>%p\n", this);
}
CMapStringToPtr::~CMapStringToPtr(){
    for(int i = 0; i < size; ++i){
        free(list[i].key);
        // maybe free value
    }
    free(list);

}
bool CMapStringToPtr::Lookup(const char * key, void * & value){
	if(key == NULL) return false;
    for (int i = 0; i < size; i++)
		{   // not works with NULL
			if (list[i].key == key || strncmp(list[i].key, key, MAX_STR_SIZE) == 0)
			{
				value = list[i].value;
				return true;
			}
		}
		return false;
}
void CMapStringToPtr::SetAt(const char * key, void * newValue){
		if(key == NULL) return;
		for (int i = 0; i < size; i++)
		{		// not works with NULL
			if (list[i].key == key || strncmp(list[i].key, key, MAX_STR_SIZE) == 0)
			{
				list[i].value = newValue;
				return;
			}
		}
		if (size == maxsize) {
			list = (KV*)realloc(list, maxsize*2*sizeof(KV));
			maxsize*=2;
		}
		list[size].value = newValue;
		int key_len = strnlen(key, MAX_STR_SIZE-1)+1;
        list[size].key = (char*)calloc(key_len, sizeof(char));
        strncpy(list[size].key, key, key_len);
		size++;
	
}

void CMapStringToPtr::RemoveAll(){
    for(int i = 0; i < size; ++i){
        free(list[i].key);
        // maybe free value
    }
    free(list);
    maxsize = 8;
    size = 0;
    list = (KV*)calloc(maxsize, sizeof(KV)); 
}

// CMapPtrToPtr

CMapPtrToPtr::CMapPtrToPtr(){
    maxsize = 8;
	size = 0;
	list = (KV*)calloc(maxsize, sizeof(KV));    
}
CMapPtrToPtr::~CMapPtrToPtr(){
    free(list);

}
bool CMapPtrToPtr::Lookup(void * key, void * & value){
    for (int i = 0; i < size; i++)
		{
			if (list[i].key == key)
			{
				value = list[i].value;
				return true;
			}
		}
		return false;
}
void CMapPtrToPtr::SetAt(void * key, void * newValue){
		for (int i = 0; i < size; i++)
		{
			if (list[i].key == key)
			{
				list[i].value = newValue;
				return;
			}
		}
		if (size == maxsize) {
			list = (KV*)realloc(list, maxsize*2*sizeof(KV));
			maxsize*=2;
		}
		list[size].value = newValue;
        list[size].key = key;
		size++;
	
}

void CMapPtrToPtr::RemoveAll(){
    // maybe free value too
    free(list);
    maxsize = 8;
    size = 0;
    list = (KV*)calloc(maxsize, sizeof(KV)); 
}

// CMapPtrToWord

CMapPtrToWord::CMapPtrToWord(){
    maxsize = 8;
	size = 0;
	list = (KV*)calloc(maxsize, sizeof(KV));    
}
CMapPtrToWord::~CMapPtrToWord(){
    free(list);

}
bool CMapPtrToWord::Lookup(void * key, u2 & value){
    for (int i = 0; i < size; i++)
		{
			if (list[i].key == key)
			{
				value = list[i].value;
				return true;
			}
		}
		return false;
}
void CMapPtrToWord::SetAt(void * key, u2 newValue){
		for (int i = 0; i < size; i++)
		{
			if (list[i].key == key)
			{
				list[i].value = newValue;
				return;
			}
		}
		if (size == maxsize) {
			list = (KV*)realloc(list, maxsize*2*sizeof(KV));
			maxsize*=2;
		}
		list[size].value = newValue;
        list[size].key = key;
		size++;
	
}

void CMapPtrToWord::RemoveAll(){
    free(list);
    maxsize = 8;
    size = 0;
    list = (KV*)calloc(maxsize, sizeof(KV)); 
}

