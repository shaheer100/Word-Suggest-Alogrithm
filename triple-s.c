// Implementation of a triple_s (SSS) ADT

// This is a "wrapper" ADT that provides a triple_s ADT interface, but all of the data
// is actually stored inside of an SOS ADT

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "sos.h"
#include "sss.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITION

struct triple_s {
  struct sos *seq;
};

//////////////////////////////////////////////////////////////////////////////

struct triple_s *sss_create(void) {
  struct triple_s *sss = malloc(sizeof(struct triple_s));
  sss->seq = sos_create();
  return sss;
}


void sss_destroy(struct triple_s *sss) {
  assert(sss);
  sos_destroy(sss->seq);
  free(sss);
}


int sss_count(const struct triple_s *sss) {
  assert(sss);
  return sos_length(sss->seq);
}


int sss_search(const struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);

  int low = 0;
  int high = sss_count(sss) - 1;
  
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (strcmp(sos_item_at(sss->seq, mid), s) == 0) {
      return mid;
    } else if (strcmp(sos_item_at(sss->seq, mid), s) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  
  return -1;
}


const char *sss_get(const struct triple_s *sss, int idx) {
  assert(sss);
  assert(0 <= idx);
  assert(idx < sss_count(sss));
  return sos_item_at(sss->seq, idx);
}


void sss_add(struct triple_s *sss, const char *s){
  assert(sss);
  assert(s);

  int low = 0;
  int high = sss_count(sss) - 1;
  
  if (sss_count(sss) == 0) { // trivial case
    sos_insert_at(sss->seq, low, s);
    return;
  }

  while (low <= high) {
    int mid = low + (high - low) / 2;
    const char *mid_str = sos_item_at(sss->seq, mid);
    if (strcmp(mid_str, s) == 0) { // item already exists, no need to add 
      return;
    } else if (strcmp(mid_str, s) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  sos_insert_at(sss->seq, low, s);
}


void sss_add_follows(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  
  if (sss_count > 0) { // won't run if sss_count = 0
    int top = sss_count(sss) - 1;
    assert((strcmp(sss_get(sss, top), s) < 0));  
  }
  
  sos_insert_end(sss->seq, s);
}


void sss_remove(struct triple_s *sss, const char *s){
  assert(sss);
  assert(s);
  
  int index = sss_search(sss, s);
  
  if (index == -1) {
    return;
  } 
  
  sos_remove_at(sss->seq, index);
}
