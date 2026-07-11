# Memory Allocation
## Dynamic Memory Allocation
```c++
#define MAX_EMPLOYEES 1000

struct employee_t {
    int id;
    int income;
    bool staff;
}

void initialize_employee(struct employee_t *e) {
    e->id = 0;
    e->income = 0;
    e->staff = false;
}

int main() {
    int n = 4;

    struct employee_t *employees = malloc(sizeof(struct employee_t) * n);
    // `employees` = one pointer --> address of the first employee
    // heap list in C is one contiguous block, not one pointer per element
    // allocated bytes = sizeof(struct employee_t) * n
    // `employees[i]` = jump `i` chunks --> each chunk = sizeof(struct employee_t)
    if (employees == NULL) {
        printf("The allocator failed\n");
        return -1;
    }

    initialize_employee(&employees[0]);

    free(employees);
    employees = NULL;
}
```

## Static Memory Allocation
```c++
int main() {
    struct employee_t employees[4];
    for (int i = 0; i < 4; i++) {
        initialize_employee(&employees[i]);
    }
}
```
