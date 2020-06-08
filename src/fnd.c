#include "fnd.h"

static unsigned short fnd_hexadecimal[16]={
	0x3f, //0
	0x06, //1
	0x5b, //2
	0x4f,
	0x66,
	0x6d,
	0x7d,
	0x07,
	0x7f,
	0x67,
	0x77,
	0x7c,
	0x39,
	0x5e,
	0x79,
	0x71
};

static short* fnd[MAX_FND];

void init_fnd(short* address[]){
	int i;
	for(i=0 ; i<MAX_FND ; i++){
		fnd[i] = address[i];
	}
}

void fnd_clear(){
	int i;
	for(i=0; i<MAX_FND; i++){
		*fnd[i] = 0;
	}
}

void fnd_all(){
	int i;
	for(i=0; i<MAX_FND; i++){
		*fnd[i]=0xff;
	}
}

void fnd_write(int hexadecimal, int fnd_num){
	*fnd[fnd_num] = fnd_hexadecimal[hexadecimal];
	usleep(0);
}

void fnd_hexa_number(unsigned long number){
	int i;
	for(i=0;i<MAX_FND;i++){
		fnd_write( (short)(number & 0xf), i);
		number = number >> 4;
	}
}

void fnd_chip(int chip_remain,int chip_betting){
	int fnd_1[4];
	int fnd_2[3];

	int digit[7];

	digit[0] = chip_remain/1000;
	chip_remain = chip_remain - 1000*digit[0];
	digit[1] = chip_remain/100;
	chip_remain = chip_remain - 100*digit[1];
	digit[2] = chip_remain/10;
	chip_remain = chip_remain - 10*digit[2];
	digit[3] = chip_remain;
	
	digit[4] = chip_betting/100;
	chip_betting = chip_betting - 100*digit[4];
	digit[5] = chip_betting/10;
	chip_betting = chip_betting - 10*digit[5];
	digit[6] = chip_betting;
	int i, k;
	for(i=0;i<4;i++){
		fnd_write(digit[i],7-i);
	}
	//fnd_write(0x38,3);
	for(k=5;k<8;k++){
		fnd_write(digit[k-1],7-k);
	}
}
	
