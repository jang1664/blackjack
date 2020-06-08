#include "keypad.h"
#include <stdio.h>
#include <string.h>

char keyboard[10] = {'0','1','2','3','4',
	             '5','6','7','8','9'};

int pows(int j);

int keyboard_read(int* key_value){
	int key_count = 0;
	int temp=0;
	int i,j;
	char buf[10];
	scanf("%s",buf);
	key_count = strlen(buf);
	for(i=0;i<key_count;i++){
		for(j=0; j<10 ;j++){
			if(buf[i] == keyboard[j]){
				temp = temp+j*pows(key_count-i-1);
			}
		}
	}
	*key_value = temp;
	return key_count;
}

int pows(int j){
	int k;
	int temp=1;
	for(k=0;k<j;k++){
		temp = temp*10;
	}
	return temp;
}
		

	
				

	
