// File author is Ítalo Lima Marconato Matias
//
// Created on May 31 of 2018, at 18:45 BRT
// Last edited on June 28 of 2018, at 19:25 BRT

#define __CHICAGO_PMM__

#include <chicago/arch/multiboot.h>
#include <chicago/arch/pmm.h>

#include <chicago/mm.h>

UIntPtr MmBootAllocPointer = (UIntPtr)&KernelEnd;
UInt32 KernelRealEnd = 0;

UIntPtr MmBootAlloc(UIntPtr size, Boolean align) {
	if (MmBootAllocPointer == 0) {																						// Disabled?
		return 0;																										// Yup
	} else if (align && ((MmBootAllocPointer % MM_PAGE_SIZE) != 0)) {													// Align to page size?
		MmBootAllocPointer += MM_PAGE_SIZE - (MmBootAllocPointer % MM_PAGE_SIZE);										// Yes
	}
	
	MmBootAllocPointer += size;																							// Increase the ptr
	
	return MmBootAllocPointer - size;																					// Return the old one
}

UInt32 PMMCountMemory(Void) {
	PMultibootMemoryMap mmap = (PMultibootMemoryMap)MultibootHeaderPointer->mmap_address;								// Here we're going to use the memory map for getting the memory size because mem_lower and mem_upper are obsolete
	UInt32 mmapi = 0;
	UInt32 memsize = 0;
	
	while ((UInt32)mmap < MultibootHeaderPointer->mmap_address + MultibootHeaderPointer->mmap_length) {
		if (mmap->type > 4) {																							// Valid?
			mmap->type = 2;																								// Nope, so let's set as reserved
		} else if ((mmapi > 0) && (mmap->base_low == 0)) {																// End (before expected)?
			break;
		} else {
			if (mmap->type == 1) {																						// Add to memsize?
				memsize += mmap->length_low;																			// Yes
			}
		}
		
		mmap++;
		mmapi++;
	}
	
	return memsize;
}

Void PMMInit(Void) {
	MmMaxPages = PMMCountMemory() / MM_PAGE_SIZE;																		// Get memory size BASED ON THE MEMORY MAP ENTRIES (mem_lower and mem_upper are obsolete)
	MmUsedPages = MmMaxPages;																							// We're going to free the avaliable pages later
	MmPageStack = (PUIntPtr)MmBootAlloc(MmMaxPages * sizeof(UIntPtr), False);											// Alloc the page frame allocator stack using the initial boot allocator
	KernelRealEnd = MmBootAllocPointer;																					// Setup the KernelRealEnd variable
	MmBootAllocPointer = 0;																								// Break/disable the PMMDumbAlloc, now we should use MemoryAlloc/AlignedAlloc/Realloc/ZAlloc/Free/AlignedFree
	
	if ((KernelRealEnd % MM_PAGE_SIZE) != 0) {																			// Align the KernelRealEnd variable to page size
		KernelRealEnd += MM_PAGE_SIZE - (KernelRealEnd % MM_PAGE_SIZE);
	}
	
	PMultibootMemoryMap mmap = (PMultibootMemoryMap)MultibootHeaderPointer->mmap_address;
	UIntPtr mmapi = 0;
	UIntPtr kstart = ((UIntPtr)(&KernelStart)) - 0xC0000000;
	UIntPtr kend = KernelRealEnd - 0xC0000000;
	
	while ((UIntPtr)mmap < MultibootHeaderPointer->mmap_address + MultibootHeaderPointer->mmap_length) {
		if (mmap->type > 4) {																							// Valid?
			mmap->type = 2;																								// Nope, so let's set as reserved
		} else if ((mmapi > 0) && (mmap->base_low == 0)) {																// End (before expected)?
			break;
		} else {
			if (mmap->type == 1) {																						// Avaliable for use?
				for (UIntPtr i = 0; i < mmap->length_low; i += 0x1000) {												// YES!
					UIntPtr addr = mmap->base_low + i;
					
					if ((addr != 0) && (!((addr >= kstart) && (addr <= kend)))) {										// Just check if the addr isn't 0 nor it's the kernel physical address
						MmFreePage(addr);																				// Everything is ok, SO FREE IT!
					}
				}
			}
		}
		
		mmap++;
		mmapi++;
	}
}
