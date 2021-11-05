#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#pragma bank 2
#include "Shogititlescreen.c"
#include "Shogititle.c"
#include "starttext.c"
#include "fade.h"
#include "mastershogi.h"

void titlesetup()
{
   disable_interrupts();
   HIDE_SPRITES;
   set_sprite_data(0, 41, texttiles);
   set_bkg_data(0, 219, titletiles);
   set_bkg_tiles(0, 0, 20, 18, titlescenePLN0);
   selection = 1;
   selected = 0;
   flash = 0;
   joypressed = 0;
   SHOW_BKG;
   DISPLAY_ON;
   enable_interrupts();
}
void pressstarttext()
{
   disable_interrupts();
   set_sprite_tile(0, 26);
   set_sprite_tile(1, 28);
   set_sprite_tile(2, 15);
   set_sprite_tile(3, 29);
   set_sprite_tile(4, 29);
   set_sprite_tile(5, 29);
   set_sprite_tile(6, 30);
   set_sprite_tile(7, 11);
   set_sprite_tile(8, 28);
   set_sprite_tile(9, 30);
   set_sprite_prop(0, 0x00);
   set_sprite_prop(1, 0x00);
   set_sprite_prop(2, 0x00);
   set_sprite_prop(3, 0x00);
   set_sprite_prop(4, 0x00);
   set_sprite_prop(5, 0x00);
   set_sprite_prop(6, 0x00);
   set_sprite_prop(7, 0x00);
   set_sprite_prop(8, 0x00);
   set_sprite_prop(9, 0x00);
   move_sprite(0, 48, 124);
   move_sprite(1, 56, 124);
   move_sprite(2, 64, 124);
   move_sprite(3, 72, 124);
   move_sprite(4, 80, 124);
   move_sprite(5, 88, 132);
   move_sprite(6, 96, 132);
   move_sprite(7, 104, 132);
   move_sprite(8, 112, 132);
   move_sprite(9, 120, 132);
   SHOW_SPRITES;
   enable_interrupts();
}
void textappear()
{
   disable_interrupts();
   set_sprite_tile(0, 26);
   set_sprite_tile(1, 28);
   set_sprite_tile(2, 15);
   set_sprite_tile(3, 29);
   set_sprite_tile(4, 29);
   set_sprite_tile(5, 29);
   set_sprite_tile(6, 30);
   set_sprite_tile(7, 11);
   set_sprite_tile(8, 28);
   set_sprite_tile(9, 30);
   enable_interrupts();
}
void textdisappear()
{
   disable_interrupts();
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
   enable_interrupts();
}
void titlemenu() BANKED
{
   if ((globalframe < 4) || ((globalframe > 4) & (globalframe < 64)))
   {
      globalframe += 1;
   }
   if (globalframe == 1)
   {
      titlesetup();
   }
   if (globalframe == 2)
   {
	  if (fadecolor == 0){
		  blackfadein();
	  }
	  else{
		  whitefadein();
	  }
	  changemusic(1);
	  fadecolor = 1;
   }
   if (globalframe == 3)
   {
      pressstarttext();
   }
   if (globalframe == 4)
   {
      if (joypressed == 0)
	  {
		 if ((joypad() & J_A) || (joypad() & J_START))
	     {
		    selected = 1;
			globalframe = 5;
	     }
      }
	  if (flash < 75)
	  {
	     flash += 1;
	  }
	  if (flash >= 75)
	  {
	     flash = 0;
	  }
	  if (flash == 1)
	  {
	     textappear();
	  }
	  if (flash == 61)
	  {
	     textdisappear();
	  }
   }
   if ((globalframe == 8) || (globalframe == 24) || (globalframe == 40) || (globalframe == 56))
   {
      textdisappear();
   }
   if ((globalframe == 16) || (globalframe == 32) || (globalframe == 48))
   {
      textappear();
   }
   if (globalframe == 63)
   {
      if (fadecolor == 0){
		  blackfadeout();
	  }
	  else{
		  whitefadeout();
	  }
   }
   if (globalframe == 64)
   {
      gamestate = 2;
	  globalframe = 0;
   }
   if (joypressed == 1)
   {
      if ((!(joypad() & J_A)) & (!(joypad() & J_START)))
      {
         joypressed = 0;
      }
   }
}