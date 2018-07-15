// File author is Ítalo Lima Marconato Matias
//
// Created on July 14 of 2018, at 22:08 BRT
// Last edited on July 15 of 2018, at 01:37 BRT

#include <chicago/alloc.h>
#include <chicago/list.h>

PList ListNew(Boolean free) {
	PList out = (PList)MemAllocate(sizeof(List));					// Allocate the space for the initial list (without any entry)
	
	if (out == Null) {												// Failed?
		return Null;												// Yes...
	}
	
	out->head = Null;												// "Zero" everything
	out->tail = Null;
	out->length = 0;
	out->free = free;												// Except the "free", set it to what the user defined
	
	return out;
}

Void ListFree(PList list) {
	PListNode cur;
	
	while (list->head != Null) {									// Let's free the list entries!
		cur = list->head;											// Save the cur list->head
		list->head = cur->next;										// Move to the next
		
		if (list->free) {											// We need to free this pointer?
			MemFree((UIntPtr)cur->data);							// Yes
		}
		
		MemFree((UIntPtr)cur);										// Free the list mode
	}
	
	MemFree((UIntPtr)list);											// Free the list
}

Boolean ListAdd(PList list, PVoid data) {
	PListNode node = (PListNode)MemAllocate(sizeof(ListNode));		// Allocate a new list node
	
	if (node == Null) {												// Failed?
		return False;												// Yes, so return False...
	}
	
	node->data = data;												// We don't need to copy the data
	node->next = Null;
	
	if (list->length == 0) {										// This is the head and tail (the first entry)?
		list->head = list->tail = node;								// Yes!
		node->prev = node;
	} else {
		list->tail->next = node;									// No
		node->prev = list->tail;
		list->tail = node;
	}
	
	list->length++;
	
	return True;
}

PVoid ListRemove(PList list, UIntPtr idx) {
	if (idx > list->length) {										// Too high idx?
		return Null;												// Yes, so we can't do anything
	}
	
	PListNode cur = list->head;
	PVoid data = Null;
	
	for (UInt32 i = 0; i < idx; i++) {								// Get the list node
		cur = cur->next;
	}
	
	data = cur->data;												// Save the data
	
	if (cur == list->head) {										// Was the list head?
		list->head = cur->next;										// Yup, so set the list head to the next entry (comparated to the node, of course)
	}
	if (cur == list->tail) {										// Was the list tail?
		list->tail = cur->prev;										// Yup, so set the list tail to the prev entry (comparated to the node, of course)
	}
	if (cur->prev != Null) {										// Had a prev?
		cur->prev->next = cur->next;								// Yes, so fix it
	}
	if (cur->next != Null) {										// Had a next?
		cur->next->prev = cur->prev;								// Yes, so fix it
	}
	
	MemFree((UIntPtr)cur);											// Free the node
	
	list->length--;													// Decrease the length
	
	return data;													// And return the data!
}

PVoid ListGet(PList list, UInt32 idx) {
	if (idx > list->length) {										// Too high idx?
		return Null;												// Yes, so we can't do anything
	}
	
	PListNode node = list->head;
	
	for (UInt32 i = 0; i < idx; i++) {								// Get the list node
		node = node->next;
	}
	
	return node->data;												// And return the data
}
