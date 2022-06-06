#include <xc.h>
#include <stdint.h>

#ifndef DLL
#define DLL

typedef struct _DLLObject_ DLLObject;

/*
 * Creates a new doubly linked list
 *  
 * returns the new list's head object
 */
DLLObject * DLL_create();
void DLL_free(DLLObject * listHead);
uint32_t DLL_length(DLLObject * listHead);
uint32_t DLL_add(void * data, DLLObject * listHead);
void * findListEntryUID(uint32_t uid, DLLObject * listHead);
unsigned DLL_isEmpty(DLLObject * listHead);
void removeListEntryUID(uint32_t targetUID, DLLObject * listHead);
void DLL_remove(DLLObject * target);
void* DLL_pop(DLLObject * listHead);
void DLL_dump(DLLObject * listHead);
void DLL_moveToEnd(DLLObject * currObject, DLLObject * listHead);

struct _DLLObject_{
    DLLObject * next;
    DLLObject * prev;
    uint32_t uid;
    void * data;
};

#endif