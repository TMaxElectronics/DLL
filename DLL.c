/*
    Copyright (C) 2020-2022 TMax-Electronics.de
*/

#include <xc.h>
#include <stdint.h>

#include "DLL.h"

typedef struct{
    uint32_t nextUID;
} HeadData;

DLLObject * createNewDll(){
    DLLObject * head = malloc(sizeof(DLLObject));
    HeadData * headData = malloc(sizeof(HeadData));
    headData->nextUID = 0;
    head->uid = 0;
    head->data = (void*) headData;
    head->next = head;
    head->prev = head;
    return head;
}

void DLL_clear(DLLObject * listHead){
    DLLObject * currObject = listHead->next;
    while(currObject != listHead){
        currObject = currObject->next;
        DLL_remove(currObject->prev);
    }
}

uint32_t DLL_add(void * data, DLLObject * listHead){
    //allocate memory for new object
    DLLObject * newObject = malloc(sizeof(DLLObject));
    
    //relink objects
    listHead->prev->next = newObject;
    newObject->prev = listHead->prev;
    listHead->prev = newObject;
    newObject->next = listHead;
    
    //set new object's data
    newObject->uid = ((HeadData*) listHead->data)->nextUID++;
    newObject->data = data;
    
    return newObject->uid;
}

void * DLL_find(void * dataPtr, DLLObject * listHead){
    DLLObject * currObject = listHead->next;
    while(currObject != listHead){
        if(currObject->data == dataPtr) return currObject->data; //target object found
        currObject = currObject->next;
    }
    return 0; //object not found
}

void * DLL_get(uint16_t index, DLLObject * listHead){
    DLLObject * currObject = listHead->next;
    if(currObject == listHead) return 0;
    uint16_t currIndex = 0;
    for(; currIndex < index; currIndex ++){
        currObject = listHead->next;
        if(currObject == listHead) return 0;
    }
    return currObject->data;
}

unsigned DLL_isEmpty(DLLObject * listHead){
    return listHead->next == listHead;
}

/*void removeListEntry(void * targetDataPtr, DLLObject * listHead){
    DLLObject * currObject = listHead->next;
    while(currObject->data != targetDataPtr){
        currObject = currObject.next;
        if(currObject == listHead) return;
    }
    removeListEntry(currObject);
}*/

void DLL_remove(DLLObject * target){
    
    target->prev->next = target->next;
    target->next->prev = target->prev;
    free(target);
}

void DLL_pop(DLLObject * listHead){
    DLL_remove(listHead->next);
}

void DLL_moveToEnd(DLLObject * currObject, DLLObject * listHead){
    currObject->prev->next = currObject->next;
    currObject->next->prev = currObject->prev;
    
    listHead->prev->next = currObject;
    currObject->prev = listHead->prev;
    listHead->prev = currObject;
    currObject->next = listHead;
} 