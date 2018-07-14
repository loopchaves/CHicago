// File author is Ítalo Lima Marconato Matias
//
// Created on July 13 of 2018, at 00:45 BRT
// Last edited on July 13 of 2018, at 00:34 BRT

#ifndef __CHICAGO_ALLOC_INT_H__
#define __CHICAGO_ALLOC_INT_H__

#include <chicago/types.h>

typedef struct MemoryAllocBlockStruct {
	UIntPtr size;
	UInt32 free;
	UIntPtr addr;
	struct MemoryAllocBlockStruct *next;
	struct MemoryAllocBlockStruct *prev;
	Char data[1];
} MemoryAllocBlock, *PMemoryAllocBlock;

#endif		// __CHICAGO_ALLOC_INT_H__