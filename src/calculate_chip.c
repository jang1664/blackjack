#include <stdio.h>

int val[52]={
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10

};

int calculate_chip(int chip_remain, int chip_betting, int stat);

int main(void){
	printf("%d\n",calculate_chip(1000,100,1));
	printf("%d\n",calculate_chip(1000,100,2));
	return 0;
	
}

int calculate_chip(int chip_remain, int chip_betting, int stat){
	switch(stat){
		case 0:
			return chip_remain + (int)chip_betting*1.5;
		case 1:
			return chip_remain + chip_betting;
		case 2:
			return chip_remain - chip_betting;
	}
}
