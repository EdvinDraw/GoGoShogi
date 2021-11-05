#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#ifndef GAMESTATE_H
#define GAMESTATE_H
#define BOARD_W 5
#define BOARD_H 5
#define FIVE 5
#define FOUR 7
#define THREE 9
#define TWO 11
#define ONE 13
#define ICHI 7
#define NI 9
#define SAN 11
#define YON 13
#define GO 15
#define TYPE_MASK 0x3F
#define IS_BLACK 0x70
#define IS_WHITE 0x80
#define THREAT 0x50
#define NONE 0x10
#define BLACK 0x20
#define WHITE 0x30
#define BLACKNWHITE 0x40
//Bank 0
void changemusic(int music) BANKED;
void banked_set_sprite_data(uint8_t start, uint8_t count, char *data, int bank) BANKED;
void banked_set_bkg_data(uint8_t start, uint8_t count, char *data, int bank) BANKED;
void banked_set_win_data(uint8_t start, uint8_t count, char *data, int bank) BANKED;
//Bank 1
void opensetup();
void opening() BANKED;
//Bank 2
void titlesetup();
void titlemenu() BANKED;
//Bank 3
void menusetup();
void menumenu() BANKED;
//Bank 4
void helpsetup();
void helpmenu() BANKED;
//Bank 5
void boardsetup();
void shogifield() BANKED;
extern const unsigned char falsevalid[];
extern const unsigned char truevalid[];
extern const unsigned char giveup[];
extern const unsigned char promote[];
extern const unsigned char yourturn[];
extern const unsigned char player1sturn[];
extern const unsigned char player2sturn[];
extern const unsigned char blacksturn[];
extern const unsigned char whitesturn[];
extern const unsigned char capturedarea[];
extern const unsigned char playerone[];
extern const unsigned char playertwo[];
extern const unsigned char computerplayer[];
extern const unsigned char zerocount[];
extern const unsigned char onecount[];
extern const unsigned char twocount[];
extern const unsigned char empty_square[];
extern const unsigned char black_pawn[];
extern const unsigned char white_pawn[];
extern const unsigned char black_silver[];
extern const unsigned char white_silver[];
extern const unsigned char black_gold[];
extern const unsigned char white_gold[];
extern const unsigned char black_bishop[];
extern const unsigned char white_bishop[];
extern const unsigned char black_rook[];
extern const unsigned char white_rook[];
extern const unsigned char black_king[];
extern const unsigned char white_king[];
extern const unsigned char black_pawnP[];
extern const unsigned char white_pawnP[];
extern const unsigned char black_silverP[];
extern const unsigned char white_silverP[];
extern const unsigned char black_bishopP[];
extern const unsigned char white_bishopP[];
extern const unsigned char black_rookP[];
extern const unsigned char white_rookP[];
extern const unsigned char possiblemove[];
extern const unsigned char nomove[];
//Bank 6
void colorsetup();
void colormenu() BANKED;
//Bank 7
void cutscenesetup();
void cutscene() BANKED;
extern const unsigned char no_slash1[];
extern const unsigned char no_slash2[];
extern const unsigned char no_slash3[];
extern const unsigned char no_slash4[];
extern const unsigned char no_slash5[];
extern const unsigned char black_silverslash1[];
extern const unsigned char black_silverslash2[];
extern const unsigned char black_silverslash3[];
extern const unsigned char black_silverslash4[];
extern const unsigned char white_silverslash1[];
extern const unsigned char white_silverslash2[];
extern const unsigned char white_silverslash3[];
extern const unsigned char white_silverslash4[];
extern const unsigned char black_goldslash1[];
extern const unsigned char black_goldslash2[];
extern const unsigned char black_goldslash3[];
extern const unsigned char black_goldslash4[];
extern const unsigned char black_goldslash5[];
extern const unsigned char black_goldslash6[];
extern const unsigned char white_goldslash1[];
extern const unsigned char white_goldslash2[];
extern const unsigned char white_goldslash3[];
extern const unsigned char white_goldslash4[];
extern const unsigned char white_goldslash5[];
extern const unsigned char white_goldslash6[];
extern const unsigned char king_punch1[];
extern const unsigned char king_punch2[];
extern const unsigned char king_punch3[];
extern const unsigned char king_punch4[];
extern const unsigned char king_punch5[];
//Bank 8
void setupraccoon() BANKED;
void setupfox() BANKED;
void blackdefeat() BANKED;
void whitedefeat() BANKED;
void blackdead() BANKED;
void whitedead() BANKED;
void blackpawn1() BANKED;
void whitepawn1() BANKED;
void blackpawn2() BANKED;
void whitepawn2() BANKED;
void blacksilver1() BANKED;
void whitesilver1() BANKED;
void blacksilver2() BANKED;
void whitesilver2() BANKED;
void blackgold1() BANKED;
void whitegold1() BANKED;
void blackgold2() BANKED;
void whitegold2() BANKED;
void blackrook1() BANKED;
void whiterook1() BANKED;
void blackrook2() BANKED;
void whiterook2() BANKED;
void blackbishop1() BANKED;
void whitebishop1() BANKED;
void blackbishop2() BANKED;
void whitebishop2() BANKED;
void blackking1() BANKED;
void whiteking1() BANKED;
void blackking2() BANKED;
void whiteking2() BANKED;
//Bank 9
void pointer() BANKED;
//Other
struct class{
	
	uint8_t x;
	uint8_t y;
	uint8_t shot;
	uint8_t aniframe;
	uint8_t jump;
	uint8_t fall;
	uint8_t back;
	uint8_t hspeed;
	uint8_t hcool;
	uint8_t hmove;
	uint8_t vspeed;
	uint8_t vcool;
};

extern struct class raccoon;
extern struct class fox;
extern UBYTE gamestate;
extern UINT16 globalframe;
extern UBYTE gamepad;
extern UBYTE joypressed;
extern int saved_bank;
extern UINT16 scroll;
extern int newgame;
extern int selection;
extern int selected;
extern int load;
extern int loader;
void loading();
void sprite_clean();
extern int flash;
extern int cpulevel;
extern int attacker;
extern int victim;
extern int pause;
extern int turn;
extern int color;
extern int black_check;
extern int white_check;
extern int P_one;
extern int P_two;
extern int S_one;
extern int S_two;
extern int G_one;
extern int G_two;
extern int B_one;
extern int B_two;
extern int R_one;
extern int R_two;
extern int fadecolor;
extern int cursor;
#endif