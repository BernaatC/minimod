# minimod
Small modular arithmetic library in C for 64-bit unsigned integers

## Installation
Simply add the minimod.h file to your project and link it wherever needed

## Cheatsheet
**uint64_t addMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
Returns (a + b) mod m<br><br>
**uint64_t subMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
Returns (a - b) mod m<br><br>
**uint64_t mulMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
Returns (a * b) mod m<br><br>
**uint64_t divMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
Returns (a / b) mod m if the multiplicative inverse of b mod m exists, otherwise returns m<br><br>
**uint64_t invMod(const uint64_t a, const uint64_t m)**<br>
Returns (a ^ (-1)) mod m if the multiplicative inverse of a mod m exists, otherwise returns m<br><br>
**uint64_t powMod(const uint64_t a, const uint64_t b, const uint64_t m)**<br>
Returns (a ^ b) mod m
