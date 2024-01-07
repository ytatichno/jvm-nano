// stdafx.cpp : source file that includes just the standard includes
// kjvm.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information


#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

char * append(char * l, const char * r){
    // printf(">>>%p", l);
    char * old = l;

    size_t l_size = (old != NULL && old[0]!='\0' ? strnlen(old, MAX_STR_SIZE-1) : 0);
    size_t r_size = strnlen(r, MAX_STR_SIZE-1);
    size_t total_size = l_size + r_size + 1;
    if(total_size > MAX_STR_SIZE)
        total_size = MAX_STR_SIZE;
    
    l = (char*)calloc(total_size, sizeof(char));
    
    snprintf(l, MAX_STR_SIZE, "%.*s%.*s", (int)l_size, old, (int)r_size, r);

    // if(old != NULL){
    //     free(old);
    // }
    return l;
}