obj := $(src:.c=.o)

CFLAGS += -fPIC
WARNINGS = -Wall -Wextra -std=c99 -Wpedantic -O2 -I.
CFLAGS += ${WARNINGS}

# OsX compatibility
ifeq ($(shell uname), Darwin)
AR = /usr/bin/libtool
AR_OPT = -static $^ -o $@
else
AR = ar
AR_OPT = rcs $@ $^
endif

libcmojify.a: cmojify.o
	${AR} ${AR_OPT}

cmojify.o: cmojify.c cmojify.h internal/emoji-map.h
	${CC} ${CFLAGS} -c cmojify.c

clean:
	rm -f cmojify.o cmojify libcmojify.a
