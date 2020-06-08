
//-------| lib/main.h |-------//
#ifndef	MAIN_H
#define	MAIN_H 


#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()
#include <string.h>
#include <math.h>


#include "ieb.h"
#include "led.h"
#include "dot.h"
#include "fnd.h"
#include "clcd.h"
#include "keypad.h"

#define hit 0
#define stand 1
#define win 1
#define lose 2
#define push 3
#define blackjack_win 0
#define dealer_facedown 0
#define dealer_faceup 1

int main();
short* mapper(off_t offset);
void unmapper();
void emergency_closer();

void random_c(); //0~51 사이의 수에서 랜덤하게 20개를 뽑음
int add(int a[],int count); //카드패를 인자로 받아서 Ace를 유리한 쪽으로 판단해서 카드패의 합을 구함
int best(int candidate[]);
int calculate_chip(int state); //게임이 끝날때 칩 갯수를 계산함
int blackjack(int a[]); //카드패를 인자로 받아 블랙잭인지 아닌지를 판단
void end(int state); //게임이 끝났을 때 다음 게임으로 넘어가기 전에 변수등을  정리하는 함수
void clear_all(); //모든 하드웨어를 clear하는 함수
#endif
