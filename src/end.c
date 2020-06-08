#include <stdio.h>
#include <fcntl.h>              // open()
#include <unistd.h>             // close(), off_t
#include <sys/mman.h>   // mmap(), munmap()
#include <stdlib.h>     // exit()
#include <string.h>
#include <math.h>

#include "main.h"
#include "ieb.h"
#include "led.h"
#include "dot.h"
#include "fnd.h"
#include "clcd.h"
#include "keypad.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};

static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};

static int fd;
static int map_counter =0;
static void* map_data[100];

//전역변수들
static int chip_remain;
static int chip_betting;
static int val[52]={
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10
};

char* deck[52]={"HA","H2","H3","H4","H5","H6","H7","H8","H9","HT","HJ","HK","HQ",
           	"DA","D2","D3","D4","D5","D6","D7","D8","D9","DT","DJ","DK","DQ",
           	"CA","C2","C3","C4","C5","C6","C7","C8","C9","CT","CJ","CK","CQ",
           	"SA","S2","S3","S4","S5","S6","S7","S8","S9","ST","SJ","SK","SQ"};

static int dealer[6];
static int player[6];
static int card[20];
static int dealer_count;
static int player_count;
static int card_count;
int dealer_sum;
int player_sum;

int main(int argc, char* argv[]) {
	
	int i;
	short * led, *dot[MAX_DOT], *fnd[MAX_FND];
	short *clcd_cmd, *clcd_data;
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = mapper(IEB_LED);
	for(i=0; i<MAX_DOT; i++){
		dot[i] = mapper(IEB_DOT[i]);
	}
	for(i=0;i<MAX_FND;i++){
		fnd[i] = mapper(IEB_FND[i]);
	}
	clcd_cmd = mapper(IEB_CLCD_CMD);
	clcd_data = mapper(IEB_CLCD_DATA);

	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd,clcd_data);

	/*led_all();
	fnd_all();
	dot_all();
	char a[]={'0','1','2','3'};
	clcd_write_string(a);
	int b;
	scanf("%d",&b);
	chip_remain =1000;
	chip_betting =100;
	end(0);
	printf("%d",chip_remain);
	return 0;*/ //end() test
	
	/*
	chip_remain =9999;
	chip_betting =99;
	fnd_chip(chip_remain,chip_betting);
	return 0;
	*/ //fnd_chip() test

	/*
	for(int i=0;i<6;i++){
		dealer[i]=i+1;
	}

	for(i=0;i<6;i++){
		player[i]=i+2;
	}

	clcd_print(dealer,player,6,6,20,12,0);
	return 0;*/ //clcd_print() test

	clcd_write("black",NULL);
}

void end(int stat){
	chip_remain = calculate_chip(stat);
	clear_all();
}

void clear_all(){
	led_clear();
	dot_clear();
	fnd_clear();
	clcd_clear_display();
}
short* mapper(off_t offset){
        map_data[map_counter] = mmap(NULL, sizeof(short), PROT_WRITE, MAP_SHARED        ,fd,offset);

        if(map_data[map_counter]==MAP_FAILED){
                fprintf(stderr,"Cannot do mmap()");
                emergency_closer();
        }
        return (short*)map_data[map_counter++];
}

void unmapper(){
        int i;
        for(i=0; i<map_counter;i++){
                munmap(map_data[i],sizeof(short));
        }
        map_counter=0;
}

void emergency_closer(){
        unmapper();
        close(fd);
        exit(EXIT_FAILURE);
}

int calculate_chip(int stat){
        switch(stat){
                case 0:
                        return chip_remain + (int)chip_betting*1.5;
                case 1:
                        return chip_remain + chip_betting;
                case 2:
                        return chip_remain - chip_betting;
        }
}           
