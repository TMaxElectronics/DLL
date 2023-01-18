/*
    Copyright (C) 2020-2022 TMax-Electronics.de
*/

#include <xc.h>
#include <stdint.h>

#include "DLL.h"
#include "portable.h"

typedef struct{
    uint32_t nextUID;
} HeadData;

DLLObject * DLL_create(){
    DLLObject * head = pvPortMalloc(sizeof(DLLObject));
    HeadData * headData = pvPortMalloc(sizeof(HeadData));
    headData->nextUID = 0;
    head->uid = 0;
    head->data = (void*) headData;
    head->next = head;
    head->prev = head;
    return head;
}

//LEAKY IF THE LIST CONTAINS ITEMS!!!
void DLL_free(DLLObject * listHead){
    DLL_clear(listHead);
    vPortFree(listHead->data);
    vPortFree(listHead);
}

uint32_t DLL_length(DLLObject * listHead){
    DLLObject * currObj = listHead->next;
    uint32_t count = 0;
    while(currObj != listHead){
        count ++;
        currObj = currObj->next;
    }
    return count;
}

void DLL_clear(DLLObject * listHead){
    DLLObject * currObject = listHead->next;
    while(currObject != listHead){
        currObject = currObject->next;
        DLL_remove(currObject->prev);
    }
}

uint32_t DLL_add(void * data, DLLObject * listHead){
    if(data == 0) return 0;
    //allocate memory for new object
    DLLObject * newObject = pvPortMalloc(sizeof(DLLObject));
    
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

DLLObject * DLL_find(void * dataPtr, DLLObject * listHead){
    DLLObject * currObject = listHead->next;
    while(currObject != listHead){
        if(currObject->data == dataPtr) return currObject; //target object found
        currObject = currObject->next;
    }
    return NULL; //object not found
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

void DLL_removeData(void * dataPtr, DLLObject * listHead){
    DLLObject * target = DLL_find(dataPtr, listHead);
    if(target != NULL) DLL_remove(target);
}

void DLL_remove(DLLObject * target){
    target->prev->next = target->next;
    target->next->prev = target->prev;
    vPortFree(target);
}

void* DLL_pop(DLLObject * listHead){
    if(listHead->next == listHead){
        return NULL;
    }
    void* ret = listHead->next->data;
    DLL_remove(listHead->next);
    return ret;
}

void DLL_moveToEnd(DLLObject * currObject, DLLObject * listHead){
    currObject->prev->next = currObject->next;
    currObject->next->prev = currObject->prev;
    
    listHead->prev->next = currObject;
    currObject->prev = listHead->prev;
    listHead->prev = currObject;
    currObject->next = listHead;
} 