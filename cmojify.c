// cmojify: cmojify.c
// Copyright (C) 2021 Ethan Uppal
//
// This file is part of cmojify.
//
// cmojify is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// cmojify is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with cmojify.  If not, see <https://www.gnu.org/licenses/>.

#include "cmojify.h"
#include "internal/emoji-map.h"
#include <string.h> // strncpy
#include <ctype.h> // isalnum
#include <stdio.h>
#include <stdlib.h>

#define length(x) (sizeof(x)/sizeof(*(x)))
#define _min(x, y) ((x)<(y)?(x):(y))
#define strnequ(s1, s2, n) (strncmp(s1, s2, n) == 0)

static const char* lookup_emoji(const char* start, size_t length) {
    for (size_t i = 0; i < length(emojis); i++) {
        if (strnequ(emojis[i][0], start, length)) {
            return emojis[i][1];
        }
    }
    return NULL;
}

void cmojify(char* out, size_t n, const char* in) {
    // If the output buffer is zero characters, then we can just return
    if (n == 0) {
        return;
    }

    // We can then decrement n so we get the amount of characters we can write
    // before we have to write a null terminator
    n--;

    // i is the iterator for in
    // j is the iterator for out
    // Our stop condition is when either i or j reaches the end of their
    // respective buffers
    size_t j = 0;
    char current;
    for (size_t i = 0; (current = in[i]) && j < n; i++) {
        if (current == ':') {
            // This is an emoji!
            const char* start = in + i;

            // We can keep going until we reach end of emoji, end of file, or
            // invalid emoji character
            do {
                current = in[++i];
            } while (current && current != ':'
                     && (isalnum(current) || current == '_'));

            // The length of the emoji is the difference between our current
            // position and the start one
            size_t length = (size_t)(in + i - start) + (current != 0);

            // The number of characters reamining to be safely appended to the
            // output buffer
            const size_t remaining = n - j;

            #define _COPY_REMAINING() \
                const size_t copy_length = _min(remaining, length); \
                strncpy(out + j, start, copy_length); \
                j += copy_length

            if (current != ':') {
                _COPY_REMAINING();
                continue;
            }

            const char* emoji = lookup_emoji(start, length);
            if (emoji == NULL) {
                _COPY_REMAINING();
            } else {
                const size_t emoji_length = strlen(emoji);
                if (emoji_length <= remaining) {
                    memcpy(out + j, emoji, emoji_length);
                    j += emoji_length;
                }
            }
        } else if (current == '\\') {
            // We can do an escape sequence here
            if (in[i + 1] == '\\') {
                // Two backslashes escape to one
                i++;
                out[j++] = '\\';
            } else if (in[i + 1] == ':') {
                // We escape the colon
                i++;
                out[j++] = ':';
            }
        } else {
            // We can just copy over
            out[j++] = current;
        }
    }

    // Finally, we can assign the null terminator to our buffer
    out[j] = 0;
}
