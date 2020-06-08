#include <stdio.h>

int main(void){
char* deck[52]={"HA","H2","H3","H4","H5","H6","H7","H8","H9","HT","HJ","HK","HQ",
                "DA","D2","D3","D4","D5","D6","D7","D8","D9","DT","DJ","DK","DQ",
                "CA","C2","C3","C4","C5","C6","C7","C8","C9","CT","CJ","CK","CQ",
                "SA","S2","S3","S4","S5","S6","S7","S8","S9","ST","SJ","SK","SQ"};
	int i=0;
	char* a[6];
	for(i;i<6;i++){
		a[i]=(char*)deck[i];
	}
	for(i=0;i<6;i++){
		printf("%s\n",a[i]);
	}
	return 0;
}
