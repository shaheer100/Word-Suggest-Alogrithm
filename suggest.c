// This is the implementation of the suggest module.

#include "suggest.h"
#include "triple-s.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////// 
// do not modify this constant:
const int SUGGEST_MAX_STRLEN = 63;
/////////////////////////////////////////////////////////////////////////////

// O(m) * (O(d * m) + O(n + m*logn) + O(m)) = O(d * m^2 + mn + m^2 * logn + m^2)
// time: O(d * m^2 + mn + m^2 * logn + m^2)
//       where d is the size of the dictionary [dict], and n the length of sss [suggestions]
struct triple_s *suggest(const struct countingbloomfilter *dict, 
                         const char *word) {
  assert(dict);
  assert(word);
  int word_len = strlen(word);
  assert(word_len <= SUGGEST_MAX_STRLEN);

  struct triple_s *suggestions = sss_create();

  for (int i = 0; i < word_len; ++i) { // n suggestions
    char *copy = malloc((word_len + 1) * sizeof(char));
    strcpy(copy, word); // O(m)
    for (int j = i; j < word_len; ++j) { // O(m)
      copy[j] = copy[j + 1];
    }
    if (cbf_lookup(dict, copy)) { // O(d * m), where d is the size of dict, and m length of word
      sss_add(suggestions, copy); // O(n + m*logn), n is the length of sss (suggestions)
    }
    free(copy);
  } 

  for (int i = 0; i <= word_len; ++i) { // 26 * (n + 1) suggestions
    for (char c = 'a'; c <= 'z'; ++c) { // O(26)
      char *copy = malloc((word_len + 2) * sizeof(char));
      strcpy(copy, word); // O(m)
      for (int j = word_len; j >= i; --j) { // O(m)
        copy[j + 1] = copy[j];
      }
      copy[i] = c;
      if (cbf_lookup(dict, copy)) { // O(d * m)
        sss_add(suggestions, copy); // O(n + m*logn)
      }
      free(copy);
    }
  }
  
  for (int i = 0; i < word_len; ++i) { // 26 * n suggestions
    for (char c = 'a'; c <= 'z'; ++c) { // O(26)
      char *copy = malloc((word_len + 1) * sizeof(char));
      strcpy(copy, word); // O(m)
      copy[i] = c;
      if (cbf_lookup(dict, copy)) { // O(d * m)
        sss_add(suggestions, copy); // O(n + m*logn)
      }
      free(copy);
    }
  }
  
  for (int i = 0; i < word_len - 1; ++i) { // (n-1) suggestions
    char *copy = malloc((word_len + 1) * sizeof(char));
    strcpy(copy, word); // O(m)
    for (int j = i + 1; j < word_len; ++j) { // O(m)
      char temp = copy[i];
      copy[i] = copy[j];
      copy[j] = temp;
      break;
    }
    if (cbf_lookup(dict, copy)) { // O(d * m)
      sss_add(suggestions, copy); // O(n + m*logn)
    }
    free(copy);
  }

  return suggestions;
}
