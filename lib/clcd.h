//-------| lib/clcd.h |-------//
#ifndef	CLCD_H
#define	CLCD_H 


#include <unistd.h> // usleep()


#define CLCD_CMD_US		40
#define CLCD_DATA_US	(CLCD_CMD_US + 4)
#define CLCD_RETURN_US	(1520 - CLCD_CMD_US)



void init_clcd(short * address_cmd, short * address_data);
void clcd_write_cmd(int cmd);
void clcd_write_data(int data);
void clcd_clear_display();
void clcd_return_home();
void clcd_entry_mode_set(int ID, int S);
void clcd_display_control(int D, int C, int B);
void clcd_shift(int SC, int RL);
void clcd_function_set(int DL, int N, int F);
void clcd_set_DDRAM(int address);
void clcd_write_string(char str[]);

void clcd_write(char fir[], char sec[]); //두 문자열을 받아서 clcd의 윗줄, 아랫줄에 각각 출력
void clcd_print(int d[], int p[],int dc, int pc, int ds, int ps, int df); //딜러와 플레이어의 카드패를 clcd에 출력
#endif
