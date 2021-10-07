#include <stdio.h>
#include <stdint.h>
#include "memallocator.h"

typedef uint8_t byte;
typedef struct Descriptor Descriptor;

Descriptor* head = NULL;
Descriptor* lastBlock = NULL;
byte* stackStart;
int initSize;
int allocatedSize = 0;

struct Descriptor {
    int32_t size;
    Descriptor* prev;
    Descriptor* next;
};

int32_t descriptorsSize = sizeof(Descriptor) + sizeof(int32_t);

int meminit(void* pMemory, int size) {
    head = (Descriptor*) pMemory;
    head->size = size;
    int32_t* endDescriptor = (int32_t*)((byte*)pMemory + size - sizeof(int32_t));
    *endDescriptor = size;
    head->next = NULL;
    head->prev = NULL;
    lastBlock = head;
    stackStart = (byte*)pMemory;
    initSize = size;
    allocatedSize += descriptorsSize;
    return 1;
}

void memdone() {
    Descriptor* cur = head;
    int mempool = 0;
    while (cur != NULL) {
        int32_t* endDescriptor = (int32_t*)((byte*)cur + cur->size - sizeof(int32_t));
        if (*endDescriptor > 0) {
            mempool += cur->size - descriptorsSize;
        }
        cur = cur->next;
    }
    if (mempool + allocatedSize - initSize > descriptorsSize) {
        printf("memory leak!\n");
        printf("memorypool: %d\n", mempool);
        printf("allocated: %d\n", allocatedSize);
        printf("initSize: %d\n", initSize);
    }
}

void *memalloc(int size) {
    Descriptor* cur = lastBlock;
    while (1) {
        int32_t* endDescriptor = (int32_t*)((byte*)cur + cur->size - sizeof(int32_t));
        if (*endDescriptor - descriptorsSize >= size) {
            // new block
            if (cur->size >= 2 * descriptorsSize + size + 1) {
                Descriptor* newBlock = (Descriptor*)((byte*)cur + descriptorsSize + size);
                newBlock->prev = cur;
                newBlock->next = cur->next;
                cur->next = newBlock;
                newBlock->size = cur->size - descriptorsSize - size;
                cur->size = descriptorsSize + size;

                int32_t* newEndDesc = (int32_t*)((byte*)newBlock + newBlock->size - sizeof(int32_t));
                *newEndDesc = newBlock->size;
                allocatedSize += descriptorsSize;
            }
            endDescriptor = (int32_t*)((byte*)cur + cur->size - sizeof(int32_t));
            *endDescriptor = -cur->size;
            lastBlock = cur;
            allocatedSize += size;

            return (void*)((byte*)cur + sizeof(Descriptor));
        }

        cur = cur->next;
        if (cur == NULL) {
            cur = head;
        }
        if (cur == lastBlock) {
            break;
        }
    }
    return 0;
}

void memfree(void *p) {
    Descriptor* curDesc = (Descriptor*)((byte*)p - sizeof(Descriptor));
    int32_t* curEndDesc = (int32_t*)((byte*)curDesc + curDesc->size - sizeof(int32_t));
    int merged = 0;
    allocatedSize -= curDesc->size - descriptorsSize;

    //merge right
    if ((byte*)curDesc + curDesc->size + descriptorsSize + 1 <= (byte*) stackStart + initSize) {
        Descriptor* rightDescriptor = (Descriptor*) ((byte*) curDesc + curDesc->size);
        int32_t* rightEndDesc = (int32_t*) ((byte*) rightDescriptor + rightDescriptor->size - sizeof(int32_t));
        if (*rightEndDesc > 0) {
            curDesc->next = rightDescriptor->next;
            if (rightDescriptor->next != NULL) {
                rightDescriptor->next->prev = curDesc;
            }

            if (lastBlock == rightDescriptor) {
                lastBlock = curDesc;
            }

            curDesc->size = curDesc->size + rightDescriptor->size;
            *rightEndDesc = curDesc->size;
            curEndDesc = (int32_t*)((byte*)curDesc + curDesc->size - sizeof(int32_t));
            merged = 1;
            allocatedSize -= descriptorsSize;
        }
    }
    //merge left
    if ((byte*)curDesc >= (byte*)stackStart + descriptorsSize + 1) {
        int32_t* leftEndDesc = (int32_t*) ((byte*) curDesc - sizeof(int32_t));
        if (*leftEndDesc > 0) {
            Descriptor* leftDescriptor = (Descriptor*) ((byte*) curDesc - *leftEndDesc);
            leftDescriptor->next = curDesc->next;
            if (curDesc->next != NULL) {
                curDesc->next->prev = leftDescriptor;
            }

            if (lastBlock == curDesc) {
                lastBlock = leftDescriptor;
            }

            leftDescriptor->size = leftDescriptor->size + curDesc->size;
            *curEndDesc = leftDescriptor->size;
            curDesc = leftDescriptor;
            merged = 1;
            allocatedSize -= descriptorsSize;
        }
    }
    if (merged == 0) {
        *curEndDesc = curDesc->size;
    }
}

int memgetminimumsize() {
    return descriptorsSize;
}

int memgetblocksize() {
    return descriptorsSize;
}
