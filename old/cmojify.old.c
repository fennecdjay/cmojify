// TODO: djay add copyright notice here

#ifdef _CMOJIFY_OLD
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cmojify.old.h"
#include "internal/emoji-map.h"

#define SIZEOF_EMOJI  sizeof(emojis) /sizeof(char*[2])

static inline const char* get_emoji(const char *buf) {
  for(long unsigned int i = 0; i < SIZEOF_EMOJI; ++i) {
    if(strcmp(buf, emojis[i][0]) == 0)
      return emojis[i][1];
  }
  return NULL;
}

static void fail(const char * base, const size_t len) {
  for(size_t i = 0; i <= len; ++i)
    putc(base[i], stdout);
}

static size_t parse_emoji(char *str) {
  const char *base = str;
  ++str;
  size_t len = 1;
  while(*str) {
    if(*str == ':') {
      const char *found = get_emoji(base);
      if(found)
        printf(found);
      else
        fail(base, len);
      return len;
    } else if(!(isalnum(*str) || *str == '_')) {
      fail(base, len);
      return len;
    }
    ++str;
    ++len;
  }
  return len;
}

void run(char *str) {
  while(*str) {
    if(*str == ':')
      str += parse_emoji(str);
    else
      putc(*str, stdout);
    ++str;
  }
}

#ifdef TEST_CMOJIFY
int main(int argc, char **argv) {
  for(int i = 1; i < argc; ++i)
    run(argv[i]);
  return 0;
}
#endif

#endif
