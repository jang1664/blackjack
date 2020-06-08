#include "dot.h"

static unsigned short dot_decimal[16][MAX_DOT] = {
	{0x7f,0x48,0x48,0x48,0x78},//p
	
	{0x7f,0x41,0x41,0x41,0x3e},//d

	{0x2a,0x12,0x02,0x12,0x2a},//v

	{0x02,0x34,0x04,0x34,0x02},//Lose

	{0x78,0x08,0x08,0x7f,0x08},//4

	{0x79,0x49,0x49,0x49,0x4f},//5

	{0x7f,0x49,0x49,0x49,0x4f},//6

	{0x40,0x40,0x40,0x40,0x7f},//7

	{0x7f,0x49,0x49,0x49,0x7f},//8

	{0x78,0x48,0x48,0x48,0x7f},//9

	{0x1f,0x24,0x64,0x24,0x1f},//A

	{0xff,0x49,0x49,0x49,0x36},//B

	{0x3e,0x41,0x41,0x41,0x22},//C

	{0x41,0xff,0x41,0x41,0x3e},//D

	{0xff,0x49,0x49,0x41,0x41},//E

	{0xff,0x48,0x48,0x40,0x40},//F
};

static short* dot[MAX_DOT];

void init_dot(short* address[]){
	int i;
	for(i=0;i<MAX_DOT;i++){
		dot[i] = address[i];
	}
}

void dot_clear(){
	int i;
	for(i=0;i<MAX_DOT;i++){
		*dot[i]=0x00;
	}
	usleep(0);
}

void dot_write(int decimal){
	int i;
	for(i=0; i<MAX_DOT;i++){
		*dot[i] = dot_decimal[decimal][i];
	}
	usleep(500000);
}

void dot_up_shift(int decimal){
	int shift, i;
	for(shift=0; shift<=7; shift++){
		for(i=0; i<MAX_DOT;i++){
			*dot[i] =(dot_decimal[decimal][i]) << shift;
		}
		usleep(500000);
	}
}
 
void dot_down_shift(int decimal){
	int shift, i;
	for(shift=0; shift<=7; shift++){
		for(i=0; i<MAX_DOT;i++){
			*dot[i] =(dot_decimal[decimal][i]) >> shift;
		}
		usleep(500000);
	}
}

void dot_inverse(int decimal){
	int shift, i;
	for(shift=0;shift<3;shift++){
		for(i=0;i<MAX_DOT;i++){	
			*dot[i] = dot_decimal[decimal][i];
		}
		usleep(300000);
	
		for(i=0;i<MAX_DOT;i++){	
			*dot[i] =~(dot_decimal[decimal][i]);
		}
		usleep(300000);
	}
	dot_clear();
}

static unsigned short dot_E[MAX_DOT] = {0x7f,0x49,0x49,0x49,0x49};

void dot_error(){
	int i;
	for(i=0 ; i<MAX_DOT; i++){
		*dot[i] = dot_E[i];
	}
	usleep(100000);
}

void dot_all(){
	int i;
	for(i=0;i<MAX_DOT;i++){
		*dot[i] = 0x7f;
	}
	usleep(100000);
}

void dot_blink(int decimal){
    int i,j;
    for(i=0;i<16;i++){
        if(i%2 == 0){
		dot_write(decimal);
        }   
        else{
            dot_clear();
	    usleep(500000);
        }
    }
}
