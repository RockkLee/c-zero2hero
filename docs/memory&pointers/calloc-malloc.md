# `calloc()` and `malloc()` in C

`malloc()` and `calloc()` allocate memory on the heap. Heap memory remains allocated until the program releases it with `free()`.

For example, this allocates space for one struct:

```c++
// calloc(number_of_items, size_of_each_item)
struct example_t *item = calloc(1, sizeof(struct example_t)); // 1 item x sizeof(struct example_t) bytes per item
```

```c
malloc(sizeof(struct example_t))
```

Both functions are declared in `<stdlib.h>`:

```c++
#include <stdlib.h>
```

## The important difference

`calloc()` clears the allocated memory to zero. `malloc()` does not.

```c
struct example_t *a = calloc(1, sizeof(struct example_t));
// All bytes are zero, if allocation succeeds.

struct example_t *b = malloc(sizeof(struct example_t));
// Bytes have indeterminate values until assigned.
```

Zero initialization is helpful when every field should start at zero. Use `malloc()` when the program will assign every byte before reading it.

## Equivalent code

This `calloc()` call:

```c
struct example_t *item = calloc(1, sizeof(struct example_t));
```

is approximately equivalent to:

```c
struct example_t *item = malloc(sizeof(struct example_t));
if (item != NULL) {
	memset(item, 0, sizeof(struct example_t));
}
```

The `calloc()` version is shorter and avoids forgetting the `memset()`.

## Allocating an array

To allocate space for several items, pass the item count as the first argument:

```c
struct example_t *items = calloc(count, sizeof(struct example_t));
```

For example, if `count` is `3`, the allocation is:

```text
3 items x sizeof(struct example_t) bytes per item
```

`calloc()` initializes every element in the array to zero.

## Always check for `NULL`

Both `calloc()` and `malloc()` return `NULL` when allocation fails. The correct check is:

```c
if (item == NULL) {
	printf("Memory allocation failed\\n");
	return STATUS_ERROR;
}
```

Do not compare an allocation result with `(void *)-1`; that value is commonly used by some other APIs, but not by `malloc()` or `calloc()`.

## Free allocated memory

Memory from either function stays allocated until it is released:

```c
free(item);
item = NULL;
```

Only call `free()` on memory returned by allocation functions (or on `NULL`).
