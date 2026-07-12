#define _POSIX_C_SOURCE 200809L

#include <kv.h>
#include <stdlib.h>
#include <string.h>


#define TOMBSTONE 0x1

size_t hash(char *str_val, int capacity) {
    // hash a string, then clamp it to table capacity
    // typedef
    // size_t = unsigned integer type
    size_t hash = 0x13371337deadbeef; // seed value = starting hash state

    /* gen a hash output */
    // Read string from left to right, push old hash bits from left to right
    // loop until the string reaches '\0'
    while (*str_val) {
        // a char is 8bits / 1byte
        hash ^= *str_val; // "a char (1byte)" XOR "the hash value"
        hash = hash << 8; // shift hash left for 1byte to make room for a new byte
        hash += *str_val; // add current character value into the rightmost byte of the hash

        str_val++; // move to next character in the string
    } // stop after processing every character

    /* squash the hash output to the size of the capacity (if capacity = 10 -> result: 0 ~ 9) */
    return hash % capacity; // map hash into valid index range: 0 ~ capacity-1
}

// fn kv_put
// params:
//   - db:    a pointer to the db
//   - key:   a pointer to the key value
//   - value: a pointer to the value itself
// returns: the index of the key, otherwise on
// error, returns -1, on not found return -2
int kv_put(kv_t *db, char *key, char *value) {
    if (!db || !key || !value) return -1;

    size_t idx = hash(key, db->capacity);

    // linear probing: if the first slot is occupied. tru the next one -> avoid hash collision
    for (int i = 0; i < db->capacity - 1; i++) {
        size_t real_idx = (idx + i) % db->capacity;
        kv_entry_t *entry = &db->entries[real_idx];

        // found the slot, occupied, and the key matches
        if (entry->key
            && entry->key != (void *) TOMBSTONE
            && !strcmp(entry->key, key) // strcmp: return 0 if equal
        ) {
            // same key found -> replace the old value with the new value
            char *newval = strdup(value);
            if (!newval) return -1;
            free(entry->value);
            entry->value = newval;
            return real_idx;
        }

        // found the slot, and its empty or tombstone
        if (!entry->key || entry->key == (void *) TOMBSTONE) {
            char *newval = strdup(value);
            char *newkey = strdup(key);
            if (!newval || !newkey) {
                free(newkey);
                free(newval);
                return -1;
            }

            entry->key = newkey;
            entry->value = newval;
            db->count++;
            return real_idx;
        }
    }

    // the db is occupied;
    // this could happen: when every "hole" in the kv_db is collided,
    // or:
    return -2;
}

// fn kv_get
// params:
//   - db:  a pointer to the db
//   - key: a pointer to the key value
// returns: the pointer to the value
// NULL if not found
char *kv_get(kv_t *db, char *key) {
    size_t idx = hash(key, db->capacity);

    for (int i = 0; i < db->capacity - 1; i++) {
        size_t real_idx = (idx + i) % db->capacity;
        kv_entry_t *entry = &db->entries[real_idx];

        // is no key, therefore return nothing
        if (entry->key == NULL) {
            return NULL;
        }

        // find an entry and the keys match
        if (entry->key &&
            // if entry->key == TOMBSTONE: means the key of the "hole" was collided before, then it was deleted,
            // so the correct "hole" should be next to the current index
            entry->key != (void *) TOMBSTONE &&
            !strcmp(entry->key, key)) {
            return entry->value;
        }
    }

    return NULL;
}

// fn kv_delete
// params:
//   - db:  a pointer to the db
//   - key: a pointer to the key value
// returns: the index of the deletion
//          -1 if the key is not found
int kv_delete(kv_t *db, char *key) {
    if (!db || !key) return -1;

    size_t idx = hash(key, db->capacity);

    for (int i = 0; i < db->capacity - 1; i++) {
        size_t real_idx = (idx + i) % db->capacity;
        kv_entry_t *entry = &db->entries[real_idx];

        if (entry->key == NULL) {
            return -1;
        }

        if (entry->key &&
            entry->key != (void *) TOMBSTONE &&
            !strcmp(entry->key, key)) {
            free(entry->key);
            free(entry->value);
            db->count--;
            entry->key = (void *) TOMBSTONE;
            entry->value = NULL;

            return real_idx;
        }
    }

    return -1;
}

// fn kv_free
// params:
//   - db: a pointer to the db
// returns: 0 on success, -1 on failure
int kv_free(kv_t *db) {
    if (!db) return -1;

    for (int i = 0; i < db->capacity - 1; i++) {
        kv_entry_t *e = &db->entries[i];

        // no need to free e->key & e->value if e->key is TOMBSTONE (if e->key == TOMBSTONE: it represents the entry is deleted)
        // because e->key and e->value no longer heap pointers
        if (e->key && e->key != (void *) TOMBSTONE) {
            free(e->key);
            free(e->value);
            e->key = NULL;
            e->value = NULL;
            db->count--;
        }
    }

    free(db->entries);
    free(db);

    return 0;
}

kv_t *kv_init(size_t capacity) {
    if (capacity == 0) return NULL;

    kv_t *table = malloc(sizeof(kv_t));
    if (table == NULL) {
        return NULL;
    }

    table->capacity = capacity;
    table->count = 0;

    // calloc: allocates the number of types (e.g., a number of struct/int/string) of memory
    table->entries = calloc(sizeof(kv_entry_t), capacity);
    if (table->entries == NULL) {
        return NULL;
    }

    return table;
}
