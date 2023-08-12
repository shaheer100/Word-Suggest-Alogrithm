// This is the implementation of the counting Bloom filter ADT.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "countingbloomfilter.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See countingbloomfilter.h for documentation
const int CBF_SUCCESS = 0;
const int CBF_FAILURE = 1;
// -----------------------------------------------------------------------

struct hashtable {
  int (*func)(const char *, int);
  int *array;
};

// See countingbloomfilter.h for documentation
struct countingbloomfilter {
  int hash_len;
  int table_len;
  int array_len;
  struct hashtable **data;
};

// See countingbloomfilter.h for documentation
struct countingbloomfilter *cbf_create(int (**hash_funcs)(const char *, int),
                                       int hash_len, int nof_tables) { 
  assert(hash_funcs);
  assert(hash_len > 0);
  assert(nof_tables > 0);

  struct countingbloomfilter *cbf = malloc(sizeof(struct countingbloomfilter));
  cbf->data = malloc(nof_tables * sizeof(struct hashtable *));

  int base = 2;
  int len = 1;
  for (int i = hash_len; i > 0; --i) {
    len *= base;
  }

  for (int i = 0; i < nof_tables; ++i) {
    cbf->data[i] = malloc(sizeof(struct hashtable));
    cbf->data[i]->array = malloc(len * sizeof(int));
    for (int j = 0; j < len; ++j) {
      cbf->data[i]->func = hash_funcs[i];
      cbf->data[i]->array[j] = 0;
    }
  }

  cbf->hash_len = hash_len;
  cbf->table_len = nof_tables;
  cbf->array_len = len;
  
  return cbf;
}

// See countingbloomfilter.h for documentation
void cbf_destroy(struct countingbloomfilter *cbf) {
  assert(cbf);

  for (int i = 0; i < cbf->table_len; ++i) {
    free(cbf->data[i]->array);
    free(cbf->data[i]);
  }

  free(cbf->data);
  free(cbf);
}

// See countingbloomfilter.h for documentation
void cbf_insert(struct countingbloomfilter *cbf, const char *key) {
  assert(cbf);
  assert(key);

  int index = 0;

  for (int i = 0; i < cbf->table_len; ++i) {
    index = cbf->data[i]->func(key, cbf->hash_len);
    ++cbf->data[i]->array[index];
  }
}

// See countingbloomfilter.h for documentation
bool cbf_lookup(const struct countingbloomfilter *cbf, const char *key) {
  assert(cbf);
  assert(key);

  int index = 0;
  int flag = true;

  for (int i = 0; i < cbf->table_len; ++i) {
    index = cbf->data[i]->func(key, cbf->hash_len);
    if (!(cbf->data[i]->array[index] > 0)) {
      flag = false;
    }
  }

  return flag;
}

// See countingbloomfilter.h for documentation
int cbf_remove(struct countingbloomfilter *cbf, const char *key) {
  assert(cbf);
  assert(key);
  
  int index = 0;

  for (int i = 0; i < cbf->table_len; ++i) {
    index = cbf->data[i]->func(key, cbf->hash_len);
    if (cbf->data[i]->array[index] == 0) {
      return CBF_FAILURE;
    }
  }

  for (int j = 0; j < cbf->table_len; ++j) {
    index = cbf->data[j]->func(key, cbf->hash_len);
    --cbf->data[j]->array[index];
  }

  return CBF_SUCCESS;
}

// See countingbloomfilter.h for documentation
void cbf_print(const struct countingbloomfilter *cbf) {
  assert(cbf);

  for (int i = 0; i < cbf->table_len; ++i) {
    printf("table %d:\n", i);
    for (int j = 0; j < cbf->array_len; ++j) {
      printf("%3d\n", cbf->data[i]->array[j]);
    }
  }
}
