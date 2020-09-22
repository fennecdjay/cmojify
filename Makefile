obj := $(src:.c=.o)

# OsX compatibility
ifeq ($(shell uname), Darwin)
AR = /usr/bin/libtool
AR_OPT = -static $^ -o $@
else
AR = ar
AR_OPT = rcs $@ $^
endif

cmojify: cmojify.c
	cc -DTEST_CMOJIFY -Wall -Wextra -flto -Ofast $< -o cmojify

libcmojify.a: cmojify.o
	${AR} ${AR_OPT}

clean:
	rm -f cmojify.o cmojify libcmojify.a
