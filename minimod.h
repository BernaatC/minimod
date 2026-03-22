#ifndef MINIMOD_H
#define MINIMOD_H

#include <stdint.h>


int isCongruent(const uint64_t a, const uint64_t b, const uint64_t m) {
	return ((a % m) == (b % m));
}

uint64_t addMod(const uint64_t a, const uint64_t b, const uint64_t m) {
	uint64_t ap = a % m, bp = m - (b % m);
	return ((ap > bp) ? ap - bp : m - (bp - ap));
}

uint64_t subMod(const uint64_t a, const uint64_t b, const uint64_t m) {
	uint64_t ap = a % m, bp = b % m;
	return ((bp > ap) ? (m - (bp - ap)) : (ap - bp));
}

uint64_t mulMod(const uint64_t a, const uint64_t b, const uint64_t m) {
	uint64_t ap = a % m, bp = b, res = 0;
	while (bp > 0) {
		if (bp & 1) {
			res = addMod(res, ap, m);
		}
		ap = ((ap < 9223372036854775808) ? (ap << 1) : (ap - (m - ap))) % m;  // 2^63
		bp = bp >> 1;
	}
	return res;
}

uint64_t invMod(const uint64_t a, const uint64_t m) {
	uint64_t x = m, y = a % m;
	uint64_t r = x % y;
	uint64_t pPrev = 0, pCurr = 1, aux;
	int neg = 0;
	while (r != 0) {
		aux = pCurr;
		pCurr = ((x / y) * pCurr) + pPrev;
		pPrev = aux;
		neg = !neg;
		x = y;
		y = r;
		r = x % y;
	}
	if (y > 1) {
		return m;
	}
	return (neg ? (m - pCurr) : pCurr);
}

uint64_t divMod(const uint64_t a, const uint64_t b, const uint64_t m) {
	uint64_t binv = invMod(b, m);
	return ((binv == m) ? m : mulMod(a, binv, m));
}

uint64_t powMod(const uint64_t a, const uint64_t b, const uint64_t m) {
	uint64_t bp = b;
	uint64_t result = 1;
	for (uint64_t i = 0; i < 64; i++) {
		if (bp >= 9223372036854775808) {  // 2^63
			result = mulMod(result, a, m);
		}
		if (i < 63 && result != 1) {
			result = mulMod(result, result, m);
		}
		bp = bp << 1;
	}
	return result;
}


int isCongruent32(const uint32_t a, const uint32_t b, const uint32_t m) {
	return ((a % m) == (b % m));
}

uint32_t subMod32(const uint32_t a, const uint32_t b, const uint32_t m) {
	uint32_t ap = a % m, bp = b % m;
	return ((bp > ap) ? (m - (bp - ap)) : (ap - bp));
}

uint32_t addMod32(const uint32_t a, const uint32_t b, const uint32_t m) {
	return (uint32_t)(((uint64_t)a + (uint64_t)b) % m);
}

uint32_t mulMod32(const uint32_t a, const uint32_t b, const uint32_t m) {
	return (uint32_t)(((uint64_t)a * (uint64_t)b) % m);
}

uint32_t invMod32(const uint32_t a, const uint32_t m) {
	uint32_t x = m, y = a % m;
	uint32_t r = x % y;
	uint32_t pPrev = 0, pCurr = 1, aux;
	int neg = 0;
	while (r != 0) {
		aux = pCurr;
		pCurr = ((x / y) * pCurr) + pPrev;
		pPrev = aux;
		neg = ~neg;
		x = y;
		y = r;
		r = x % y;
	}
	if (y > 1) {
		return m;
	}
	return (neg ? (m - pCurr) : pCurr);
}

uint32_t divMod32(const uint32_t a, const uint32_t b, const uint32_t m) {
	uint32_t binv = invMod32(b, m);
	return ((binv == m) ? m : mulMod32(a, binv, m));
}

uint32_t powMod32(const uint32_t a, const uint32_t b, const uint32_t m) {
	uint32_t bp = b;
	uint32_t result = 1;
	for (uint32_t i = 0; i < 32; i++) {
		if (bp >= 2147483648) {  // 2^31
			result = mulMod32(result, a, m);
		}
		if (i < 31 && result != 1) {
			result = mulMod32(result, result, m);
		}
		bp = bp << 1;
	}
	return result;
}

#endif  // !MINIMOD_H