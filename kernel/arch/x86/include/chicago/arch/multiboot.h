// File author is Ítalo Lima Marconato Matias
//
// Created on May 27 of 2018, at 13:38 BRT
// Last edited on May 27 of 2018, at 13:38 BRT

#ifndef __CHICAGO_ARCH_MULTIBOOT_H__
#define __CHICAGO_ARCH_MULTIBOOT_H__

#include <chicago/types.h>

typedef struct MultibootHeaderStruct
{
	UInt32 flags;
	UInt32 mem_lower;
	UInt32 mem_upper;
	UInt32 boot_device;
	UInt32 cmd_line;
	UInt32 mods_count;
	UInt32 mods_address;
	UInt32 num;
	UInt32 size;
	UInt32 address;
	UInt32 shndx;
	UInt32 mmap_length;
	UInt32 mmap_address;
	UInt32 drives_length;
	UInt32 drives_address;
	UInt32 config_table;
	UInt32 boot_loader_name;
	UInt32 apm_table;
	UInt32 vbe_control_info;
	UInt32 vbe_mode_info;
	UInt32 vbe_mode;
	UInt32 vbe_interface_segment;
	UInt32 vbe_interface_offset;
	UInt32 vbe_interface_length;
} Packed MultibootHeader, *PMultibootHeader;

typedef struct MultibootMemoryMapStruct
{
	UInt32 size;
	UInt32 base_low;
	UInt32 base_high;
	UInt32 length_low;
	UInt32 length_high;
	UInt32 type;
} Packed MultibootMemoryMap, *PMultibootMemoryMap;

extern UInt32 MultibootHeaderMagic;
extern PMultibootHeader MultibootHeaderPointer;

#endif		// __CHICAGO_ARCH_MULTIBOOT_H__