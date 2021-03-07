#ifndef _printop_h
#define _printop_h

#include "../information/system_info.h"

#include <stdio.h>

void print_logo();

void print_star(char *title);
void print_line(char *title);
void print_pause(char *notice);
void bool_printf(int bl);

void flushiobuf();

#endif