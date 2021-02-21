#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cmojify.h"

#define SIZEOF_EMOJI  sizeof(emojis) /sizeof(char*[2])

static inline const char* get_emoji(const char *buf) {
  for(long unsigned int i = 0; i < SIZEOF_EMOJI; ++i) {
    if(!strncmp(buf, emojis[i][0], strlen(emojis[i][0])))
      return emojis[i][1];
  }
  return NULL;
}
/*
static void fail(const char * base, const size_t len) {
  for(size_t i = 0; i <= len; ++i)
    putc(base[i], stdout);
}
*/
static char* parse_emoji(char *str, char *out, size_t *len) {
  char *base = str;
  char *out_base = out;
  ++str;
  *len = 1;
  while(*str) {
    if(*str == ':') {
      const char *found = get_emoji(base);
      if(found) {
        *len += strlen(found);
        strcpy(out, found);
      }
      return out;
    } else if(!(isalnum(*str) || *str == '_')) {
//      fail(base, len);
      return out_base;
    }
    ++str;
    (*len)++;
    ++out;
  }
  return out_base;
}

void cmojify(char *str, char *buf) {
  size_t len;
  while(*str) {
    if(*str == ':') {
      const char *out = parse_emoji(str, buf, &len);
      strcpy(buf, out);
      str += len;
      buf += len;
    } else
      *buf = *str;
    ++str;
    ++buf;
  }
}

#ifdef TEST_CMOJIFY
int main(int argc, char **argv) {
  for(int i = 1; i < argc; ++i) {
    char out[strlen(argv[i]) + 1];
    cmojify(argv[i], out);
    puts(out);
  }
  return 0;
}
#endif
