#ifndef DOT_H
#define DOT_H

#include <unistd.h>

#define MAX_DOT 5

void init_dot(short* address[]);
void dot_clear();
void dot_write(int decimal);

void dot_up_shift(int decimal);
void dot_down_shift(int decimal);
void dot_inverse(int decimal);
void dot_all();
void dot_error();
void dot_blink(int decimal);
#endif
