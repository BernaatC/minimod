#ifndef MINIMOD_H

#include <stdint.h>
#include <stdlib.h>

// 2^63
#define P63 9223372036854775808

#define LOWER(X) (X & (uint64_t)UINT32_MAX)
#define HIGHER(X) (X >> 32)
#define OVERFLOW(X, Y) ((X > UINT64_MAX - Y) ? 1 : 0)

void shl128(uint64_t* higher, uint64_t* lower) {
	(*higher) = (*higher) << 1;
	if ((*lower) >= P63) {
		(*higher)++;
	}
	(*lower) = (*lower) << 1;
}

void shr128(uint64_t* higher, uint64_t* lower) {
	(*lower) = (*lower) >> 1;
	if ((*higher) % 2 == 1) {
		(*lower) += P63;
	}
	(*higher) = (*higher) >> 1;
}


#define LINKED_LIST_NODE struct LinkedListNode
typedef struct LinkedListNode{
	uint64_t val;
	LINKED_LIST_NODE* prev;
	LINKED_LIST_NODE* next;
};

#define LINKED_LIST struct LinkedList
typedef struct LinkedList {
	LINKED_LIST_NODE* first;
	LINKED_LIST_NODE* last;
};

LINKED_LIST newList() {
	LINKED_LIST list = { 0, 0 };
	return list;
}

void append(LINKED_LIST* self, const uint64_t newValue) {
	if (self->first != 0) {
		self->last->next = (LINKED_LIST_NODE*)malloc(sizeof(LINKED_LIST_NODE));
		self->last->next->prev = self->last;
		self->last = self->last->next;
	}
	else {
		self->first = (LINKED_LIST_NODE*)malloc(sizeof(LINKED_LIST_NODE));
		self->first->prev = 0;
		self->last = self->first;
	}
	self->last->val = newValue;
	self->last->next = 0;
}

void clearList(LINKED_LIST* self) {
	if (self->first != 0) {
		LINKED_LIST_NODE* iterator = self->first;
		while (iterator->next != 0) {
			LINKED_LIST_NODE* last = iterator;
			iterator = iterator->next;
			free(last);
		}
		free(iterator);
		self->first = 0;
		self->last = 0;
	}
}

uint64_t length(const LINKED_LIST list) {
	uint64_t length = 0;
	LINKED_LIST_NODE* iterator = list.first;
	while (iterator != 0) {
		length++;
		iterator = iterator->next;
	}
	return length;
}

uint64_t subMod(const uint64_t a, const uint64_t b, const uint64_t m) {  // (a - b) % m
	uint64_t ap = a % m, bp = b % m;
	if (bp > ap) {
		return m - (bp - ap);
	}
	else {
		return (ap - bp);
	}
}

uint64_t addMod(const uint64_t a, const uint64_t b, const uint64_t m) {  // (a + b) % m
	uint64_t bp = m - (b % m);
	return subMod(a, bp, m);
}

uint64_t mulMod(const uint64_t a, const uint64_t b, const uint64_t m) {  // (a * b) % m
	uint64_t ll = LOWER(a) * LOWER(b), lh = LOWER(a) * HIGHER(b), hl = HIGHER(a) * LOWER(b), hh = HIGHER(a) * HIGHER(b);
	uint64_t higher = hh + HIGHER(lh) + HIGHER(hl), lower;
	lower = LOWER(lh) + LOWER(hl) + HIGHER(ll);
	higher += HIGHER(lower);
	lower = (lower << 32) + LOWER(ll);
	
	if (higher > 0) {
		uint64_t modHigher = 0, modLower = m;
		while (higher > modHigher && modHigher < P63) {
			shl128(&modHigher, &modLower);
		}
		if (higher > modHigher) {
			higher = higher - modHigher;
		}
		while (higher > 0) {
			if (modHigher < higher || ((modHigher == higher) && (modLower < lower))) {
				higher = higher - modHigher - ((modLower > lower) ? 1 : 0);
				lower = lower - modLower;
			}
			shr128(&modHigher, &modLower);
		}
	}
	return (lower % m);
}

uint64_t invMod(const uint64_t a, const uint64_t m) {  // (a ^ -1) % m
	LINKED_LIST quotients = newList();
	uint64_t x = m, y = a % m, result = m;
	uint64_t r = x % y;
	while (r != 0) {
		append(&quotients, (x - r) / y);
		x = y;
		y = r;
		r = x % y;
	}
	if (y == 1) {
		LINKED_LIST pList = newList();
		append(&pList, 0);
		append(&pList, 1);
		LINKED_LIST_NODE* iterator = quotients.first;
		while (iterator != 0) {
			append(&pList, (iterator->val * pList.last->val) + pList.last->prev->val);
			iterator = iterator->next;
		}
		uint64_t value = pList.last->val, len = length(pList);
		clearList(&pList);
		result = ((len % 2 == 0) ? value : m - value);
	}
	clearList(&quotients);
	return result;
}

uint64_t divMod(const uint64_t a, const uint64_t b, const uint64_t m) {  // (a / b) % m
	uint64_t binv = invMod(b, m);
	return ((binv == m) ? m : mulMod(a, binv, m));
}

uint64_t powMod(const uint64_t a, const uint64_t b, const uint64_t m) {  // (a ^ b) % m
	uint64_t bp = b;
	uint64_t result = 1;
	for (uint64_t i = 0; i < 64; i++) {
		uint64_t currentBit = ((bp >= P63) ? 1 : 0);
		if (currentBit == 1) {
			result = mulMod(result, a, m);
		}
		if (i < 63 && result != 1) {
			result = mulMod(result, result, m);
		}
		bp = bp << 1;
	}
	return result;
}

#endif  // !MINIMOD_H