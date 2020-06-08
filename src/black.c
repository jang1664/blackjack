#include <stdio.h>
int val[52]={
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10
};

int blackjack(int dealer[]);

int main(void){
	int a[2]={0,10};
	printf("%d",blackjack(a));
	return 0;	
}

int blackjack(int a[]){
	if(val[a[0]] ==1){
		if(val[a[1]] == 10){
			return 1;
		}
		else {return 0;}
	}
	else if(val[a[0]]==10){
		if(val[a[1]]==1){
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}
	
