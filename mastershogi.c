#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "mastershogi.h"
char notation[] =
{
    "5ichi", "4ichi", "3ichi", "2ichi", "1ichi", 
	"5ni", "4ni", "3ni", "2ni", "1ni", 
	"5san", "4san", "3san", "2san", "1san", 
	"5yon", "4yon", "3yon", "2yon", "1yon", 
	"5go", "4go", "3go", "2go", "1go", 
};
UBYTE gamestate;
UINT16 globalframe;
UBYTE gamepad;
UBYTE joypressed;
struct class raccoon;
struct class fox;
int saved_bank;
UINT16 scroll;
int newgame;
int selection;
int selected;
int load;
int loader;
int flash;
int cpulevel;
int attacker;
int victim;
int pause;
int turn;
int color;
int black_check;
int white_check;
int P_one;
int P_two;
int S_one;
int S_two;
int G_one;
int G_two;
int B_one;
int B_two;
int R_one;
int R_two;
int fadecolor;
int cursor;

void loadingsetup()
{
   load = 0;
   loader = 0;
}
void loading()
{
   if (loader < 4)
   {
      loader += 1;
   }
   if (loader >= 4)
   {
	  if (load == 0)
	  {
         load = 1;
      }
	  else
	  {
         load = 0;
      }
      loader = 0;
   }
}

void sprite_clean()
{
   set_sprite_tile(0, 0);
   set_sprite_tile(1, 0);
   set_sprite_tile(2, 0);
   set_sprite_tile(3, 0);
   set_sprite_tile(4, 0);
   set_sprite_tile(5, 0);
   set_sprite_tile(6, 0);
   set_sprite_tile(7, 0);
   set_sprite_tile(8, 0);
   set_sprite_tile(9, 0);
   set_sprite_tile(10, 0);
   set_sprite_tile(11, 0);
   set_sprite_tile(12, 0);
   set_sprite_tile(13, 0);
   set_sprite_tile(14, 0);
   set_sprite_tile(15, 0);
   set_sprite_tile(16, 0);
   set_sprite_tile(17, 0);
   set_sprite_tile(18, 0);
   set_sprite_tile(19, 0);
   set_sprite_tile(20, 0);
   set_sprite_tile(21, 0);
   set_sprite_tile(22, 0);
   set_sprite_tile(23, 0);
   set_sprite_tile(24, 0);
   set_sprite_tile(25, 0);
   set_sprite_tile(26, 0);
   set_sprite_tile(27, 0);
   set_sprite_tile(28, 0);
   set_sprite_tile(29, 0);
   set_sprite_tile(30, 0);
   set_sprite_tile(31, 0);
   set_sprite_tile(32, 0);
   set_sprite_tile(33, 0);
   set_sprite_tile(34, 0);
   set_sprite_tile(35, 0);
   set_sprite_tile(36, 0);
   set_sprite_tile(37, 0);
   set_sprite_tile(38, 0);
   set_sprite_tile(39, 0);
   move_sprite(0, 40, 172);
   move_sprite(1, 48, 172);
   move_sprite(2, 56, 172);
   move_sprite(3, 64, 172);
   move_sprite(4, 72, 172);
   move_sprite(5, 80, 172);
   move_sprite(6, 88, 172);
   move_sprite(7, 96, 172);
   move_sprite(8, 104, 172);
   move_sprite(9, 112, 172);
   move_sprite(10, 40, 186);
   move_sprite(11, 48, 186);
   move_sprite(12, 56, 186);
   move_sprite(13, 64, 186);
   move_sprite(14, 72, 186);
   move_sprite(15, 80, 186);
   move_sprite(16, 88, 186);
   move_sprite(17, 96, 186);
   move_sprite(18, 104, 186);
   move_sprite(19, 112, 186);
   move_sprite(20, 40, 192);
   move_sprite(21, 48, 192);
   move_sprite(22, 56, 192);
   move_sprite(23, 64, 192);
   move_sprite(24, 72, 192);
   move_sprite(25, 80, 192);
   move_sprite(26, 88, 192);
   move_sprite(27, 96, 192);
   move_sprite(28, 104, 192);
   move_sprite(29, 112, 192);
   move_sprite(30, 40, 200);
   move_sprite(31, 48, 200);
   move_sprite(32, 56, 200);
   move_sprite(33, 64, 200);
   move_sprite(34, 72, 200);
   move_sprite(35, 80, 200);
   move_sprite(36, 88, 200);
   move_sprite(37, 96, 200);
   move_sprite(38, 104, 200);
   move_sprite(39, 112, 200);
}
const unsigned char falsevalid[] =
{
   0x01
};
const unsigned char truevalid[] =
{
   0x02
};
const unsigned char giveup[] =
{
   0x11, 0x13, 0x20, 0x0F, 0x00, 0x1F, 0x1A, 0x27, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x23, 0x0F, 0x1D, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x00
};
const unsigned char promote[] =
{
   0x1A, 0x1C, 0x19, 0x17, 0x19, 0x1E, 0x0F, 0x27, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x23, 0x0F, 0x1D, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x00
};
const unsigned char yourturn[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x23, 0x19, 0x1F, 0x1C, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x1E, 0x1F, 0x1C, 0x18, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char player1sturn[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x0C, 0x16, 0x0B, 0x0D, 0x15, 0x1D, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x1E, 0x1F, 0x1C, 0x18, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char player2sturn[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x21, 0x12, 0x13, 0x1E, 0x0F, 0x1D, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x1E, 0x1F, 0x1C, 0x18, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char blacksturn[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x0C, 0x16, 0x0B, 0x0D, 0x15, 0x00, 0x13, 0x1D, 
   0x1E, 0x12, 0x13, 0x18, 0x15, 0x13, 0x18, 0x11, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char whitesturn[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x21, 0x12, 0x13, 0x1E, 0x0F, 0x00, 0x13, 0x1D, 
   0x1E, 0x12, 0x13, 0x18, 0x15, 0x13, 0x18, 0x11, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char capturedarea[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x0D, 0x0B, 0x1A, 0x1E, 0x1F, 0x1C, 0x0F, 0x0E, 
   0x00, 0x1A, 0x13, 0x0F, 0x0D, 0x0F, 0x1D, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char playerone[] =
{
   0x02, 0x1A
};
const unsigned char playertwo[] =
{
   0x03, 0x1A
};
const unsigned char computerplayer[] =
{
   0x0D, 0x1A
};
const unsigned char zerocount[] =
{
   0x8B, 
   0x8C
};
const unsigned char onecount[] =
{
   0x8D, 
   0x8E
};
const unsigned char twocount[] =
{
   0x8F, 
   0x90
};
const unsigned char empty_square[] =
{
   0x29, 0x2A, 
   0x2B, 0x2C
};
const unsigned char black_pawn[] =
{
   0x2D, 0x2E, 
   0x2F, 0x30
};
const unsigned char white_pawn[] =
{
   0x31, 0x32, 
   0x33, 0x34
};
const unsigned char black_silver[] =
{
   0x35, 0x36, 
   0x37, 0x38
};
const unsigned char white_silver[] =
{
   0x39, 0x3A, 
   0x3B, 0x3C
};
const unsigned char black_gold[] =
{
   0x3D, 0x3E, 
   0x3F, 0x40
};
const unsigned char white_gold[] =
{
   0x41, 0x42, 
   0x43, 0x44
};
const unsigned char black_bishop[] =
{
   0X45, 0x46, 
   0x47, 0x48
};
const unsigned char white_bishop[] =
{
   0x49, 0x4A, 
   0x4B, 0x4C
};
const unsigned char black_rook[] =
{
   0x4D, 0x4E, 
   0x4F, 0x50
};
const unsigned char white_rook[] =
{
   0x51, 0x52, 
   0x53, 0x54
};
const unsigned char black_king[] =
{
   0x55, 0x56, 
   0x57, 0x58
};
const unsigned char white_king[] =
{
   0x59, 0x5A, 
   0x5B, 0x5C
};
const unsigned char black_pawnP[] =
{
   0x5D, 0x5E, 
   0x5F, 0x60
};
const unsigned char white_pawnP[] =
{
   0x61, 0x62, 
   0x63, 0x64
};
const unsigned char black_silverP[] =
{
   0x65, 0x66, 
   0x67, 0x68
};
const unsigned char white_silverP[] =
{
   0x69, 0x6A, 
   0x6B, 0x6C
};
const unsigned char black_bishopP[] =
{
   0x6D, 0x6E, 
   0x6F, 0x70
};
const unsigned char white_bishopP[] =
{
   0x71, 0x72, 
   0x73, 0x74
};
const unsigned char black_rookP[] =
{
   0x75, 0x76, 
   0x77, 0x78
};
const unsigned char white_rookP[] =
{
   0x79, 0x7A, 
   0x7B, 0x7C
};
const unsigned char possiblemove[] =
{
   0x7D, 0x7E, 
   0x7F, 0x80
};
const unsigned char nomove[] =
{
   0x81, 0x82, 
   0x83, 0x84
};
const unsigned char no_slash1[] =
{
   0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45
};
const unsigned char no_slash2[] =
{
   0x45,
   0x45
};
const unsigned char no_slash3[] =
{
   0x45, 0x45, 0x45
};
const unsigned char no_slash4[] =
{
   0x45, 0x45, 0x45,
   0x45, 0x45, 0x45
};
const unsigned char no_slash5[] =
{
   0x45, 0x45,
   0x45, 0x45
};
const unsigned char black_silverslash1[] =
{
   0x45, 0x45, 0x45, 0x46, 0x47, 0x48, 0x49
};
const unsigned char black_silverslash2[] =
{
   0x45, 0x45, 0x45, 0x45, 0x4A, 0x00, 0x4B
};
const unsigned char black_silverslash3[] =
{
   0x45, 0x45, 0x45, 0x4C, 0x4D, 0x00, 0x4E
};
const unsigned char black_silverslash4[] =
{
   0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55
};
const unsigned char white_silverslash1[] =
{
   0x59, 0x58, 0x57, 0x56, 0x45, 0x45, 0x45
};
const unsigned char white_silverslash2[] =
{
   0x5B, 0x00, 0x5A,0x45, 0x45, 0x45, 0x45
};
const unsigned char white_silverslash3[] =
{
   0x5E, 0x00, 0x5D,0x5C, 0x45, 0x45, 0x45
};
const unsigned char white_silverslash4[] =
{
   0x65, 0x64, 0x63,0x62, 0x61, 0x60, 0x5F
};
const unsigned char black_goldslash1[] =
{
   0x6E,
   0x75
};
const unsigned char black_goldslash2[] =
{
   0x76, 0x77, 0x78
};
const unsigned char black_goldslash3[] =
{
   0x72, 0x73, 0x74,
   0x79, 0x7A, 0x7B
};
const unsigned char black_goldslash4[] =
{
   0x67, 0x68, 0x69,
   0x45, 0x6C, 0x6D
};
const unsigned char black_goldslash5[] =
{
   0x45, 0x66,
   0x6A, 0x6B
};
const unsigned char black_goldslash6[] =
{
   0x6F, 0x70, 0x71
};
const unsigned char white_goldslash1[] =
{
   0x84,
   0x8B
};
const unsigned char white_goldslash2[] =
{
   0x8E, 0x8D, 0x8C
};
const unsigned char white_goldslash3[] =
{
   0x8A, 0x89, 0x88,
   0x91, 0x90, 0x8F
};
const unsigned char white_goldslash4[] =
{
   0x7F, 0x7E, 0x7D,
   0x83, 0x82, 0x45
};
const unsigned char white_goldslash5[] =
{
   0x7C, 0x45,
   0x81, 0x80
};
const unsigned char white_goldslash6[] =
{
   0x87, 0x86, 0x85
};
const unsigned char king_punch1[] =
{
   0x92, 0x93,
   0x94, 0x95
};
const unsigned char king_punch2[] =
{
   0x96, 0x97,
   0x98, 0x99
};
const unsigned char king_punch3[] =
{
   0x9A, 0x9B,
   0x9C, 0x9D
};
const unsigned char king_punch4[] =
{
   0x9E, 0x9F,
   0xA0, 0xA1
};
const unsigned char king_punch5[] =
{
   0xA2, 0xA3,
   0xA4, 0xA5
};