#include "main.h"

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
char* deck[52]={"HA","H2","H3","H4","H5","H6","H7","H8","H9","HT","HJ","HK","HQ",
		"DA","D2","D3","D4","D5","D6","D7","D8","D9","DT","DJ","DK","DQ",
		"CA","C2","C3","C4","C5","C6","C7","C8","C9","CT","CJ","CK","CQ",
		"SA","S2","S3","S4","S5","S6","S7","S8","S9","ST","SJ","SK","SQ"};
int val[52]={
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10,
                1,2,3,4,5,6,7,8,9,10,10,10,10};

static int dealer[6];
static int player[6];
static int card[20];
static int dealer_count;
static int player_count;
static int card_count;
int dealer_sum;
int player_sum;
static int player_choice;

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

	//s0
	chip_remain = 500;
	clcd_write("welcom to BJ","press any key");
	getchar();
	s1:
	clcd_clear_display();
	if(chip_remain <= 0){
		clcd_write("game over", "you lose");
		led_blink_all();
		goto end;
	}
	else if(chip_remain >=1000){
		clcd_write("game over","you win");
		led_blink_all();
		goto end;
	}
	fnd_chip(chip_remain,0);
	clcd_clear_display();
	clcd_write("betting","");
	int betting_flag=0;
	do{	
		if(betting_flag==1){
			clcd_clear_display();
			clcd_write("invalid","");
		}
//		keyboard_read("%s",&chip_betting);
		scanf("%d",&chip_betting);
		betting_flag=1;
	}while(chip_betting>chip_remain);

	fnd_chip(chip_remain, chip_betting);
	clcd_clear_display();
	clcd_write("start","when All LED off");
	led_all();
	usleep(3000000);
	
	s2:
	led_clear();
	dealer_count=0; player_count=0; card_count=0;

	random_c(card);

	for(dealer_count;dealer_count<2;dealer_count++){
		dealer[dealer_count] = card[card_count];
		card_count++;
	}

	for(player_count;player_count<2;player_count++){
		player[player_count] = card[card_count];
		card_count++;
	}
	dealer_sum = add(dealer,dealer_count);
	player_sum = add(player,player_count);
	clcd_clear_display();
	clcd_print(dealer,player,dealer_count,player_count,dealer_sum,player_sum,dealer_facedown);

	if(blackjack(player)){
		if(blackjack(dealer)){
			end(push);//무승부
			goto s1;
		}
		else{
			end(blackjack_win);//blackjack 승리
			goto s1;
		}
	}
	else{
		player_sel:
			//int player_choice;
			dot_write(0);
			//keyboard_read("%d",&player_choice);
			scanf("%d",&player_choice);
			if(player_choice==hit){
				player[player_count]=card[card_count]; player_count++; card_count++;
				player_sum=add(player,player_count);
				clcd_print(dealer,player,dealer_count,player_count,dealer_sum,player_sum,dealer_facedown);
				led_count(player_count);
				if(player_sum>21){
					end(lose);
					goto s1;
				}
				else if(player_count==6){
					if(blackjack(dealer)){
						end(lose);
						goto s1;
					}
					else{end(win);
						goto s1;}
				}
				else{ goto player_sel; }
			}
			else if(player_choice = stand){
				s3:
				clcd_print(dealer,player,dealer_count,player_count,dealer_sum,player_sum,dealer_faceup);
				dot_write(1);
				if(blackjack(dealer)){
					end(lose);
					goto s1;
				}
				else{
					dealer_sel:
						dealer_sum = add(dealer,dealer_count);
						clcd_print(dealer,player,dealer_count,player_count,dealer_sum,player_sum,dealer_faceup);
						if(dealer_sum<17){
							led_up_shift();
							dealer[dealer_count] =card[card_count];
							dealer_count++; card_count++;
							goto dealer_sel;
						}
						else if(dealer_sum >=17){
							if(dealer_sum>21){end(win); goto s1;}
							else if(dealer_sum>player_sum){end(lose); goto s1;}
							else if(dealer_sum==player_sum){end(push); goto s1;}
							else if(dealer_sum<player_sum){end(win); goto s1;}
						}
				}
			}
	}

	end:
	unmapper();
	close(fd);
	return 0;
	
}

short* mapper(off_t offset){
	map_data[map_counter] = mmap(NULL, sizeof(short), PROT_WRITE, MAP_SHARED	,fd,offset);
	
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


void random_c(){
    
    int i;    
    for(i=0; i<20; i++){
        card[i] = (rand()%52);
    
    }
}
int add(int a[],int count){
	int i=0;
	int num_ace = 0;
	int sum=0;
	for(i;i<count; i++){
		if(val[a[i]] ==1){
			num_ace = num_ace +1;
		}
		else{
			sum = sum+val[a[i]];
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

int calculate_chip(int stat){
	switch(stat){
		case 0:
			return chip_remain + (int)chip_betting*1.5;
		case 1:
			return chip_remain + chip_betting;
		case 2:
			return chip_remain - chip_betting;
		case 3:
			return chip_remain;
	}
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

void end(int stat){
        chip_remain = calculate_chip(stat);
	usleep(3000000);
        clear_all();
}

void clear_all(){
        led_clear();
        dot_clear();
        fnd_clear();
        clcd_clear_display();
}	
