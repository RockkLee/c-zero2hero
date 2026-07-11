# typedef and enum in C

## `typedef`

`typedef` creates a new name for an existing type. 
It does not create a brand new type. It only gives the type another alias.

```c
typedef unsigned int u32;
typedef char *string;

int main() {
    u32 age = 25;
    string name = "alice";
}
```

Common use cases:

- shorten long type names
- make pointer types easier to read
- give domain-specific names to existing types

Example with `struct`:

```c
typedef struct {
    int x;
    int y;
} Point;

int main() {
    Point p = {10, 20};
}
```

Without `typedef`, you would usually write:

```c
struct Point {
    int x;
    int y;
};

int main() {
    struct Point p = {10, 20};
}
```

## `enum`

`enum` is used to define a set of named integer constants. It makes code easier to read than using raw numbers.

```c
enum Day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

int main() {
    enum Day today = WEDNESDAY;
}
```

By default, enum values start at `0` and increase by `1`:

```c
enum Day {
    MONDAY,    // 0
    TUESDAY,   // 1
    WEDNESDAY  // 2
};
```

You can also assign explicit values:

```c
enum StatusCode {
    STATUS_OK = 200,
    STATUS_NOT_FOUND = 404,
    STATUS_SERVER_ERROR = 500
};
```

## `typedef` with `enum`

`typedef` is often used with `enum` so you do not need to write `enum` every time.

```c
typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

int main() {
    Color pixel = GREEN;
}
```

This is similar to:

```c
enum Color {
    RED,
    GREEN,
    BLUE
};

int main() {
    enum Color pixel = GREEN;
}
```

## Practical example

```c
#include <stdio.h>

typedef enum {
    LOGIN_OK,
    LOGIN_BAD_PASSWORD,
    LOGIN_LOCKED
} LoginResult;

const char *result_to_string(LoginResult result) {
    switch (result) {
        case LOGIN_OK:
            return "login ok";
        case LOGIN_BAD_PASSWORD:
            return "bad password";
        case LOGIN_LOCKED:
            return "account locked";
        default:
            return "unknown";
    }
}

int main() {
    LoginResult result = LOGIN_BAD_PASSWORD;
    printf("%s\n", result_to_string(result));
}
```

## Summary

- `typedef` gives another name to an existing type
- `enum` defines named integer constants
- `typedef enum` is a common pattern for cleaner code
- `enum` improves readability compared with magic numbers
