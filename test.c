// cmojify: test.c: A testing program to ensure cmojify works.
// Copyright (C) 2021 Ethan Uppal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "cmojify.h" // cmojify
#include <stdio.h> // printf

int main() {
    char buffer[16];
    cmojify(buffer, sizeof(buffer), "Hello! :art: :)");
    printf("%s\n", buffer);
    return 0;
}
