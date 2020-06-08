#ifndef FND_H
#define FND_H

#include <unistd.h>

#define MAX_FND 8

void init_fnd(short* address[]);
void fnd_clear();
void fnd_write(int hexadecimal, int fnd_num);
void fnd_all();
void fnd_hexa_number(unsigned long number);
void fnd_chip(int chip_remain, int chip_betting); //fnd에 남은 칩수와 배팅 칩수를 출력
#endif
