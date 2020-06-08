#include "keypad.h"
#include <stdio.h>
#include <string.h>

char keyboard[16] = {'1','2','3','4',
	             'q','w','e','r',
		     'a','s','d','f',
		     'z','x','c','v'};

int keyboard_read(int* key_value){
	int key_count = 0;
	char buf[10];
	scanf("%s",buf);
	key_count = strlen(buf);
	
	if(key_count!=1){
		return key_count;
	}
	else{
		for(int i=0; i<16 ;i++){
			if(buf[0] == keyboard[i]){
				*key_value = i;
			}
		}
	}
	return key_count;
}


		

	
				

	
