// File author is Ítalo Lima Marconato Matias
//
// Created on May 11 of 2018, at 13:15 BRT
// Last edited on May 12 of 2018, at 09:03 BRT

#ifndef __CHICAGO_TYPES_H__
#define __CHICAGO_TYPES_H__

/* Base types */

#define Void void
#define PVoid void*
#define Char char
#define PChar char*
#define Short short
#define PShort short*
#define Int int
#define PInt int*
#define Long long
#define PLong long*

/* Unsigned types */

typedef unsigned Char UInt8, *PUInt8;
typedef unsigned Short UInt16, *PUInt16;
typedef unsigned Int UInt32, *PUInt32;
typedef unsigned Long ULong, *PULong;
typedef unsigned Long Long UInt64, *PUInt64;

/* Signed types */

typedef signed Char Int8, *PInt8;
typedef signed Short Int16, *PInt16;
typedef signed Int Int32, *PInt32;
typedef signed Long Long Int64, *PInt64;

/* Inline assembly */

#define Asm __asm__
#define Volatile __volatile__

/* Variadic arguments */

#define VariadicList __builtin_va_list
#define VariadicStart(v, l) __builtin_va_start(v, l)
#define VariadicEnd(v) __builtin_va_end(v)
#define VariadicArg(v, l) __builtin_va_arg(v, l)
#define VariadicCopy(d, s) __builtin_va_copy(d, s)

/* Attributes */

#define Packed __attribute__((packed))

/* Boolean and other defines */

typedef Char Boolean, *PBoolean;

#define True 1
#define False 0

#define Null ((PVoid)0)

#define Const const

#endif		// __CHICAGO_TYPES_H__