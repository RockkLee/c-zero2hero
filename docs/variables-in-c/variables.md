# Variables in C
## Types of variables
```c
char a;          // 1byte, 8 bits
short b;         // 2byte, 16 bits
int c;           // 4byte, 32 bits
long long int d; // 8byte, 64 biys
float e;         // 4byte, 32 bits
double f;        // 8byte, 64 biys

unsigned int c_unsigned;
```

## Type Casting
```c
// To type cast a variable, you do the following expression.
int other_var = -1;
unsigned int x = (unsigned int)other_var;

// Signedness Casting
// -1 becomes UINT_MAX in the following value
// (int other_var = -2; -> 0xfffffffe)
int other_var = -1; // 32bit -> 0xffffffff
unsigned int x = (unsigned int)other_var; // 32bit -> 0xffffffff

// Up Casting

short other_var = -1; // 16bit -> 0xffff
int x = (int)other_var; // 32bit -> 0xffffffff

// Down Casting
int x = 0xfffffefe; // 32bits -> 0xfffffefe
short other_var = (short)x; // 16bits -> 0xfefe

// Floats
float f = 3.14; // 32bits
int wasafloat = (int)f; // 32bits -> 0x00000003
```