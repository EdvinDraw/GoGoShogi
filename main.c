//Inclutions
#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#pragma bank 0
#include "hUGEDriver.h"
#include "gogosgb_border.c"
#include "gogosgb_border.h"
#include "gogoborder.h"
#include "mastershogi.h"

extern const hUGESong_t goodsound;
extern const hUGESong_t titlesong;
extern const hUGESong_t sakura;
extern const hUGESong_t killertheme;
UBYTE music_bank = 1;
void changemusic(int music) BANKED
{
   UBYTE saved_bank = _current_bank;
   switch(music)
   {
      case 0:
         SWITCH_ROM_MBC1(1);
		 music_bank = 1;
		 hUGE_init(&goodsound);
      break;
	  case 1:
         SWITCH_ROM_MBC1(3);
		 music_bank = 3;
		 hUGE_init(&titlesong);
      break;
	  case 2:
         SWITCH_ROM_MBC1(6);
		 music_bank = 6;
		 hUGE_init(&killertheme);
      break;
	  case 4:
         SWITCH_ROM_MBC1(2);
		 music_bank = 2;
		 hUGE_init(&sakura);
      break;
   }
   SWITCH_ROM_MBC1(saved_bank);
}
void musicVBL()
{
   UBYTE saved_bank = _current_bank;
   SWITCH_ROM_MBC1(music_bank);
   hUGE_dosound();
   SWITCH_ROM_MBC1(saved_bank);
}
void banked_set_sprite_data(uint8_t start, uint8_t count, char *data, int bank) BANKED
{
  UBYTE saved_bank = _current_bank;
  SWITCH_ROM_MBC1(bank);
  set_sprite_data(start, count, data);
  SWITCH_ROM_MBC1(saved_bank);
}
void banked_set_bkg_data(uint8_t start, uint8_t count, char *data, int bank) BANKED
{
  UBYTE saved_bank = _current_bank;
  SWITCH_ROM_MBC1(bank);
  set_bkg_data(start, count, data);
  SWITCH_ROM_MBC1(saved_bank);
}
void banked_set_win_data(uint8_t start, uint8_t count, char *data, int bank) BANKED
{
  UBYTE saved_bank = _current_bank;
  SWITCH_ROM_MBC1(bank);
  set_win_data(start, count, data);
  SWITCH_ROM_MBC1(saved_bank);
}

void main()
{
   DISPLAY_ON;
   if (sgb_check())
   {
      set_sgb_border(border_chr, sizeof(border_chr), border_map, sizeof(border_map), border_pal, sizeof(border_pal));
   }
   fadecolor = 1;
   cpulevel = 1;
   turn = 0;
   P_one = 0;
   P_two = 0;
   S_one = 0;
   S_two = 0;
   G_one = 0;
   G_two = 0;
   B_one = 0;
   B_two = 0;
   R_one = 0;
   R_two = 0;
   gamestate = 0;
   globalframe = 0;
   BGP_REG = 0x00;
   OBP0_REG = 0xE4;
   OBP1_REG = 0xD1;
   NR52_REG = 0x80;
   NR51_REG = 0xFF;
   NR50_REG = 0x77;
   SHOW_BKG;
   SHOW_SPRITES;
   add_VBL(musicVBL);
   while(1)
   {
      switch(gamestate)
      {
         case 0:
			opening();
         break;
         case 1:
			titlemenu();
         break;
		 case 2:
			menumenu();
         break;
		 case 4:
			helpmenu();
         break;
		 case 5:
			shogifield();
         break;
		 case 6:
			colormenu();
         break;
		 case 7:
			cutscene();
         break;
      }
	  wait_vbl_done();
   }
}