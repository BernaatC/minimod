# minimod
Small modular arithmetic library in C for 64-bit unsigned integers

## Setup
Simply add the minimod.h file to your project and link it wherever needed

## Cheatsheet
**int isCongruent(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
**int isCongruent32(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
Returns whether a and b are congruent modulo m
**uint64_t addMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
**uint32_t addMod32(const uint32_t a, const uint32_t b, const uint32_t m)**<br>
Returns (a + b) mod m<br><br>
**uint64_t subMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
**uint32_t subMod32(const uint32_t a, const uint32_t b, const uint32_t m)**<br>
Returns (a - b) mod m<br><br>
**uint64_t mulMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
**uint32_t mulMod32(const uint32_t a, const uint32_t b, const uint32_t m)**<br>
Returns (a * b) mod m<br><br>
**uint64_t divMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
**uint32_t divMod32(const uint32_t a, const uint32_t b, const uint32_t m)**<br>
Returns (a / b) mod m if the multiplicative inverse of b mod m exists, otherwise returns m<br><br>
**uint64_t invMod(const uint64_t a, const uint64_t m)**<br>
Returns (a ^ (-1)) mod m if the multiplicative inverse of a mod m exists, otherwise returns m<br><br>
**uint64_t powMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
**uint32_t powMod32(const uint32_t a, const uint32_t b, const uint32_t m)**<br>
Returns (a ^ b) mod m
