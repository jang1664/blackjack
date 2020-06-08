#include <stdio.h>

int ADD(int dealer[],int dealer_count);
int best(int candidate[]);
int val[52]={
		1,2,3,4,5,6,7,8,9,10,10,10,10,
		1,2,3,4,5,6,7,8,9,10,10,10,10,
		1,2,3,4,5,6,7,8,9,10,10,10,10,
		1,2,3,4,5,6,7,8,9,10,10,10,10
};
int main(void){
	int dealer[6] = {0,0,0,8,8};
	printf("%d\n", ADD(dealer,5));
	return 0;
}

nt val[52]={
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10
};
int ADD(int dealer[],int dealer_count){
	int i=0;
	int num_ace = 0;
	int sum=0;
	for(i;i<dealer_count; i++){
		if(val[dealer[i]] ==1){
			num_ace = num_ace +1;
		}
		else{
			sum = sum+val[dealer[i]];
		}

	}
	
	int candidate[2]={0,0};
	switch(num_ace){
	case 0:
		return sum;
	case 1:
		candidate[0] = sum+1;
		candidate[1] = sum+11;
		return best(candidate);
		
	case 2:
		candidate[0] = sum+2;
		candidate[1] = sum+12;
		return best(candidate);
	case 3:
		candidate[0] = sum+3;
		candidate[1] = sum+13;
		return best(candidate);
	case 4:
		candidate[0] = sum+4;
		candidate[1] = sum+14;
		return best(candidate);
	}
}

int best(int candidate[]){
	if(candidate[1]<22){
		return candidate[1];
	}
	else{
		return candidate[0];
	}
}
