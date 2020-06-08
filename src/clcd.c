//-------| src/clcd.c |-------//
#include "clcd.h"



static short * clcd_cmd, * clcd_data;
extern char* deck[52];

/*char* deck[52]={"HA","H2","H3","H4","H5","H6","H7","H8","H9","HT","HJ","HK","HQ",
                "DA","D2","D3","D4","D5","D6","D7","D8","D9","DT","DJ","DK","DQ",
                "CA","C2","C3","C4","C5","C6","C7","C8","C9","CT","CJ","CK","CQ",
                "SA","S2","S3","S4","S5","S6","S7","S8","S9","ST","SJ","SK","SQ"};
*/

void init_clcd(short * address_cmd, short * address_data) {
	int D=1, C=0, B=0;
	int DL=1, N=1, F=0;
	
	clcd_cmd  = address_cmd;
	clcd_data = address_data;
	
	clcd_clear_display();
	clcd_return_home();
	clcd_display_control(D, C, B);
	clcd_function_set(DL, N, F);
}

void clcd_write_cmd(int cmd) {
	*clcd_cmd = (short)cmd; usleep(CLCD_CMD_US);
}
void clcd_write_data(int data) {
	*clcd_data = (short)data; usleep(CLCD_DATA_US);
}

void clcd_clear_display() {
	clcd_write_cmd(0x01); usleep(CLCD_RETURN_US);
}
void clcd_return_home() {
	clcd_write_cmd(0x02); usleep(CLCD_RETURN_US);
}
void clcd_entry_mode_set(int ID, int S) {
	int cmd = 1 << 2;
	if( ID != 0 ) { cmd |= (1 << 1); }
	if( S  != 0 ) { cmd |= (1 << 0); }
	clcd_write_cmd(cmd);
}
void clcd_display_control(int D, int C, int B) {
	int cmd = 1 << 3;
	if( D != 0 ) { cmd |= (1 << 2); }
	if( C != 0 ) { cmd |= (1 << 1); }
	if( B != 0 ) { cmd |= (1 << 0); }
	clcd_write_cmd(cmd);
}
void clcd_shift(int SC, int RL) {
	int cmd = 1 << 4;
	if( SC != 0 ) { cmd |= (1 << 3); }
	if( RL != 0 ) { cmd |= (1 << 2); }
	clcd_write_cmd(cmd);
	clcd_write_cmd(cmd);
}
void clcd_function_set(int DL, int N, int F) {
	int cmd = 1 << 5;
	if( DL != 0 ) { cmd |= (1 << 4); }
	if( N  != 0 ) { cmd |= (1 << 3); }
	if( F  != 0 ) { cmd |= (1 << 2); }
	clcd_write_cmd(cmd);
}
void clcd_set_DDRAM(int address) {
	int cmd = 1 << 7;
	cmd |= address;
	clcd_write_cmd(cmd);
}

void clcd_write_string(char str[]) {
	int i;
	for( i=0; (str[i] != 0); i++) {
		clcd_write_data(str[i]);
	}
}

void clcd_write(char fir[], char sec[]) {
	clcd_entry_mode_set(1, 0);
	clcd_write_string(fir);
	clcd_set_DDRAM(0x40);
	clcd_write_string(sec);
	usleep(5000);
}

void clcd_print(int d[], int p[], int dc, int pc, int ds, int ps, int df) {

	//char * card_d[6][10] = {"H4", "C7", "SJ", "D3", "D7", "CQ"};
	//char * card_p[6][10] = {"H3", "C6", "JT", "D2", "D6", "CJ"};
	char* card_d[6];
	char* card_p[6];
	char dealer_sum[2];
	char player_sum[2];
	int i, j;
	for(i=0;i<dc;i++){
		card_d[i] =(char*)deck[d[i]];
	}
	
	for(j=0;j<pc;j++){
		card_p[j] =(char*)deck[p[j]];
	}

	dealer_sum[0]=(ds/10) + 48;
	ds = ds - 10*(ds/10);
	dealer_sum[1] = ds + 48;

	player_sum[0]=(ps/10) + 48;
	ps = ps - 10*(ps/10);
	player_sum[1] = ps + 48;

	if (df == 0){
		clcd_entry_mode_set(1,0);
		clcd_write_string(card_d[0]);
		clcd_set_DDRAM( 2 );
		clcd_write_string("??");
		/*clcd_set_DDRAM( 0x40 );
		clcd_write_string(card_p[0]);
		clcd_set_DDRAM( 0x40 + 2);
		clcd_write_string(card_p[1]);
		clcd_set_DDRAM( 14 );
		clcd_write_string("??");
		clcd_set_DDRAM( 0x40 + 14 );
		clcd_write_string(player_sum);*/
		
		for(int i=0; i<pc; i++) {
			clcd_set_DDRAM( 0x40 + i*2 );
			clcd_write_string(card_p[i]);
		}
		clcd_set_DDRAM( 14 );
		clcd_write_string("??");
		clcd_set_DDRAM( 0x40 + 14 );
		clcd_write_string(player_sum);
	}
	else if(df == 1) {
		clcd_entry_mode_set(1,0);

		for(int i=0; i<dc; i++) {
			clcd_set_DDRAM( i *2 );
			clcd_write_string(card_d[i]);
		}
		for(int i=0; i<pc; i++) {
			clcd_set_DDRAM( 0x40 + i*2 );
			clcd_write_string(card_p[i]);
		}

		clcd_set_DDRAM( 14 );
		clcd_write_string(dealer_sum);
		clcd_set_DDRAM( 0x40 + 14 );
		clcd_write_string(player_sum);
	}
}
