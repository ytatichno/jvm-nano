#pragma once
#include "types.h"

class CMapStringToPtr{
    struct KV
    {
        char *key;
        void *value;
    };
public:
    KV * list;
    int maxsize;
    int size;
public:

	inline void * operator new(size_t size){
		// return malloc(size);
		return calloc(size,sizeof(char));
	}
	inline void operator delete(void * ptr){
		if(ptr != NULL)
			free(ptr);
	}

    CMapStringToPtr();
    ~CMapStringToPtr();
    bool Lookup(const char * key, void * & value);
    void SetAt(const char * key, void * newValue);
    void RemoveAll();
    
};


class CMapPtrToPtr{
    struct KV
    {
        void *key;
        void *value;
    };
    KV * list;
    int maxsize;
    int size;
public:
    CMapPtrToPtr();
    ~CMapPtrToPtr();
    bool Lookup(void * key, void * & value);
    void SetAt(void * key, void * newValue);
    void RemoveAll();
    
};

class CMapPtrToWord{
    struct KV
    {
        void *key;
        u2 value;
    };
    KV * list;
    int maxsize;
    int size;
public:
    CMapPtrToWord();
    ~CMapPtrToWord();
    bool Lookup(void * key, u2 & value);
    void SetAt(void * key, u2 newValue);
    void RemoveAll();
    
};

