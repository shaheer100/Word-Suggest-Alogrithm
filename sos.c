// This is the implementation of the sequence of strings (sos) ADT

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs136-trace.h"
#include "string-io.h"
#include "sos.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITIONS

struct sos {
  int len;
  int maxlen;
  char **data;
};

// we have provided sos_read() for you :)
// also, there is no need for you to test sos_read()

// see sos.h
struct sos *sos_read(void) {
  struct sos *seq = sos_create();
  while (1) {
    char *line = read_line();
    if (line == NULL) {
      break;
    }
    sos_insert_end(seq, line);
    free(line);
  }
  return seq;
}

//////////////////////////////////////////////////////////////////////////////

// The following are the functions you must implement

// We recommend that you complete them in the order below, as that may help
// facilitate your testing

// For example, we recommend you write the first few functions
// (create,destroy,length,insert_end,print)
// and then create your own simple tests (.in files) that sufficiently test
// those functions

// Once those functions are tested and debugged, write just one function
// at a time and test it before moving on to the next funciton

// Attempting to write all of the functions before you do any debugging or
// testing is an unwise strategy

//////////////////////////////////////////////////////////////////////////////

struct sos *sos_create(void) {
  struct sos *seq = malloc(sizeof(struct sos));
  seq->len = 0;
  seq->maxlen = 1;
  seq->data = malloc(seq->maxlen * sizeof(char *));
  return seq;
}


void sos_destroy(struct sos *seq) {
  assert(seq);
  
  for (int i = 0; i < seq->len; ++i) {
    free(seq->data[i]);
  }
  
  free(seq->data);
  free(seq);
}


int sos_length(const struct sos *seq) {
  assert(seq);
  return seq->len;
}


void sos_insert_end(struct sos *seq, const char *s) {
  assert(seq);
  assert(s);
  
  char *copy = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(copy, s);
  
  if (seq->len == seq->maxlen) {
    seq->maxlen *= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(char *));
  }
  
  seq->data[seq->len] = copy;
  seq->len += 1;
}


void sos_print(const struct sos *seq) {
  assert(seq);

  for (int i = 0; i < seq->len; ++i) {
    printf("%s\n", seq->data[i]);
  }
}


const char *sos_item_at(const struct sos *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < sos_length(seq));
  return seq->data[pos];
}


void sos_remove_end(struct sos *seq) {
  assert(seq);
  assert(0 < sos_length(seq));
  
  seq->len -= 1;
  free(seq->data[seq->len]);
}


void sos_insert_at(struct sos *seq, int pos, const char *s) {
  assert(seq);
  assert(s);
  assert(0 <= pos);
  assert(pos <= sos_length(seq));
  
  char *copy = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(copy, s);
  
  if (seq->len == seq->maxlen) {
    seq->maxlen *= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(char *));
  }
  
  for (int i = seq->len; i > pos; --i) {
    seq->data[i] = seq->data[i - 1];
  }
  
  seq->data[pos] = copy;
  seq->len += 1;
}


void sos_remove_at(struct sos *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < sos_length(seq));
  
  free(seq->data[pos]);
  
  for (int i = pos; i < seq->len - 1; ++i) {
    seq->data[i] = seq->data[i + 1];
  }

  seq->len -= 1;
}


void sos_replace_at(struct sos *seq, int pos, const char *s) {
  assert(seq);
  assert(s);
  assert(0 <= pos);
  assert(pos < sos_length(seq));
  
  char *copy = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(copy, s);
  
  free(seq->data[pos]); // free whatever is at pos
  
  seq->data[pos] = copy;
}


void sos_swap(struct sos *seq, int pos1, int pos2) {
  assert(seq);
  assert(0 <= pos1);
  assert(pos1 <= sos_length(seq));
  assert(0 <= pos2);
  assert(pos2 <= sos_length(seq));

  char *temp = seq->data[pos1];
  seq->data[pos1] = seq->data[pos2];
  seq->data[pos2] = temp;
}


struct sos *sos_dup(const struct sos *seq) {
  assert(seq);
  
  struct sos *dup = sos_create();
  
  for (int i = 0; i < seq->len; ++i) {
    char *new_str = seq->data[i];
    sos_insert_end(dup, new_str);
  }
  
  return dup;
}
