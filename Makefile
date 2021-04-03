obj := $(src:.c=.o)

CFLAGS += -fPIC
# OsX compatibility
ifeq ($(shell uname), Darwin)
AR = /usr/bin/libtool
AR_OPT = -static $^ -o $@
else
AR = ar
AR_OPT = rcs $@ $^
endif

cmojify: cmojify.c
	${CC} -DTEST_CMOJIFY -Wall -Wextra -flto -Ofast $< -o cmojify

libcmojify.a: lib.o
	${AR} ${AR_OPT}

clean:
	rm -f cmojify.o cmojify libcmojify.a lib.o
