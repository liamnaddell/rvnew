#include <stddef.h>
#include "lock.h"

typedef struct ll_region {
	struct ll_region *next;
	struct ll_region *prev;
	long unsigned int size;
} ll_region;

typedef struct ll_head {
	lock l;
	ll_region *s;
} ll_head;

unsigned int page_count;
ll_head *start;

//return where to insert the new region after
ll_region *find_empty_space(size_t size, ll_region **before) {
	if (start->s == NULL) {
		return (ll_region *) (((void *) start)+sizeof(ll_region));

	}
	ll_region *head = start->s;
	while(head->next != NULL) {
		unsigned int d = (head->next) - (sizeof(ll_region) + head->size + head);
		if (d > size) {
			*before = head;
			return (ll_region *) (((void *) head)+sizeof(ll_region)+head->size);

		}
		head = head->next;
	}
	*before = head;
	return (ll_region *) (((void *) head)+sizeof(ll_region)+head->size);

}


void *malloc(size_t bytes) {
	aquire_lock(&start->l);
	ll_region *before = NULL;
	ll_region *r = find_empty_space(bytes, &before);
	r->size = bytes;
	if (before != NULL) {
		r->next = before->next;
		r->prev = before;
		if (before->next != NULL) {
			before->next->prev = r;
		}
	} else {
		r->next = NULL;
		r->prev = NULL;
	}
	release_lock(&start->l);
	return ((void *) r) + sizeof(ll_region);
}
void free(void *addr) {
	aquire_lock(&start->l);
	ll_region *r = addr - sizeof(ll_region);
	if (r->prev == NULL) {
		//bug here, can mark entire memory as used 
		start->s = r->next;
	} else if (r->next == NULL) {
		r->prev->next = NULL;
	} else {
		r->prev->next = r->next;
		r->next->prev = r->prev;
	}
	release_lock(&start->l);
}

void mem_init(void *base_addr, unsigned int pageno) {
	start = base_addr;
	start->s = NULL;
	start->l = LOCK_INIT;
}
