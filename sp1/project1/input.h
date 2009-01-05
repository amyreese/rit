/*
 * Copyright (C) 2008	John Reese
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __PROJECT1_INPUT__
#define __PROJECT1_INPUT__

#define LINE_SIZE 256 // 256 bytes should be enough for anybody
#define ARGS_SIZE LINE_SIZE/2 + 1

/**
 * Tokenize an input line into a list of arguments.
 */
int tokenize_input( char* input, char *args[] );

#endif // __PROJECT1_INPUT__
