//-------| src/led.c |-------//
#include "led.h"

static short * led;

void init_led(short * address) {
	led = address;
}

void led_down_shift() {
	
	int i;
	for( i=1; i<=16 ; i++ ) {
		*led = (short)~( ((unsigned long)0xFF << i) >> 8 );
		usleep(50000);
	}
}

void led_up_shift() {
	
	int i;
	for( i=1; i<=16 ; i++ ) {
		*led = (short)~((unsigned long)0xFF00 >> i);
		usleep(100000);
	}
}

void led_blink_all() {
	int i;
	for( i=1; i<=16 ; i++ ) {
		if ( i%2 == 1 ) {
			*led = (short)~0xFF;
		}
		else {
			*led = (short)~0x00;
		}
		usleep(100000);
	}
}
void led_clear(){
	*led= (short)~0x00;
}

void led_all(){
	*led = (short)~0xff;
}

void led_bit(int number){
	*led = (short)~(number<<4);
	usleep(0);
}

void led_count(int count) {
	int binary_count;
	binary_count = power(count) - 1;
	//printf("%d",binary_count);
	* led = (short)~binary_count;
	usleep(50000);
}

int power(int b) {
	int cal_a = 1;
	for(int i = 0;i<b;i++){
		cal_a = cal_a*2;
	}
	return cal_a;
}
