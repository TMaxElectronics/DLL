#include <xc.h>
#include <stdint.h>

#ifndef DLL
#define DLL

typedef struct _DLLObject_ DLLObject;

/*
 * WARNING:
 * 
 * the DLL_FOREACH function is NOT deletion during loop safe. If the current entry gets deleted while the loop is running there will be a free'd memory access
 * 
 * If that feature is absolutely necessary you can, as a workaround, implement the loop yourself, keeping the above problem in mind.
 */
#define DLL_FOREACH(VARIABLE, LIST) DLLObject * VARIABLE = LIST; while((VARIABLE = VARIABLE->next) != LIST)

/*
 * Creates a new doubly linked list
 *  
 * returns the new list's head object
 */
DLLObject * DLL_create();
void DLL_clear(DLLObject * listHead);
void DLL_free(DLLObject * listHead);
uint32_t DLL_length(DLLObject * listHead);
uint32_t DLL_add(void * data, DLLObject * listHead);
void * findListEntryUID(uint32_t uid, DLLObject * listHead);
unsigned DLL_isEmpty(DLLObject * listHead);
void removeListEntryUID(uint32_t targetUID, DLLObject * listHead);
void DLL_remove(DLLObject * target);
void DLL_removeData(void * dataPtr, DLLObject * listHead);
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