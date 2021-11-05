#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#pragma bank 1
#include "Introfield.c"
#include "edvindrawintro.c"
#include "flashingstar.c"
#include "fade.h"
#include "mastershogi.h"
#include "tanuki1.c"
#include "tanuki2.c"
#include "tanuki3.c"
#include "tanuki4.c"
#include "tanuki5.c"
#include "tanuki6.c"
#include "tanuki7.c"
#include "tanuki8.c"
#include "kitsune1.c"
#include "kitsune2.c"
#include "kitsune3.c"
#include "kitsune4.c"
#include "kitsune5.c"
#include "kitsune6.c"
#include "kitsune7.c"
#include "kitsune8.c"

int shine_x;

void opensetup()
{
   disable_interrupts();
   set_sprite_data(0, 9, Introtiles);
   set_sprite_data(10, 23, flashstar);
   set_bkg_data(0, 70, Introtiles);
   set_bkg_tiles(0, 0, 20, 18, edvindrawPLN0);
   SHOW_BKG;
   DISPLAY_ON;
   enable_interrupts();
}
void shine()
{
   disable_interrupts();
   shine_x = 0;
   set_sprite_tile(0, 8);
   set_sprite_tile(1, 8);
   set_sprite_tile(2, 10);
   set_sprite_tile(3, 10);
   set_sprite_tile(4, 10);
   set_sprite_tile(5, 10);
   set_sprite_prop(2, 0x00 |S_PALETTE);
   set_sprite_prop(3, 0x00 |S_PALETTE);
   set_sprite_prop(4, 0x00 |S_PALETTE);
   set_sprite_prop(5, 0x00 |S_PALETTE);
   move_sprite(0, shine_x, 104);
   move_sprite(1, shine_x, 112);
   move_sprite(2, 18, 96);
   move_sprite(3, 26, 96);
   move_sprite(4, 18, 104);
   move_sprite(5, 26, 104);
   SHOW_SPRITES;
   enable_interrupts();
}
void opening() BANKED
{
   globalframe += 1;
   if (globalframe == 1)
   {
      opensetup();
   }
   if (globalframe == 2)
   {
      if (fadecolor == 0){
		  blackfadein();
	  }
	  else{
		  whitefadein();
	  }
	  fadecolor = 0;
   }
   if (globalframe == 12)
   {
      shine();
	  changemusic(0);
   }
   if (globalframe >= 12)
   {
      move_sprite(0, shine_x, 104);
	  move_sprite(1, shine_x, 112);
	  if (shine_x < 168)
	  {
	     shine_x += 4;
      }
   }
   if ((globalframe == 24) || (globalframe == 56))
   {
      set_sprite_tile(2, 11);
      set_sprite_tile(3, 12);
      set_sprite_tile(4, 13);
      set_sprite_tile(5, 14);
   }
   if ((globalframe == 32) || (globalframe == 48))
   {
      set_sprite_tile(2, 15);
      set_sprite_tile(3, 16);
      set_sprite_tile(4, 17);
      set_sprite_tile(5, 18);
   }
   if (globalframe == 40)
   {
      set_sprite_tile(2, 19);
      set_sprite_tile(3, 20);
      set_sprite_tile(4, 21);
      set_sprite_tile(5, 22);
   }
   if (globalframe == 64)
   {
      set_sprite_tile(2, 10);
      set_sprite_tile(3, 10);
      set_sprite_tile(4, 10);
      set_sprite_tile(5, 10);
	  sprite_clean();
   }
   if (globalframe == 143)
   {
	  if (fadecolor == 0){
		  blackfadeout();
	  }
	  else{
		  whitefadeout();
	  }
   }
   if (globalframe == 144)
   {
      gamestate = 1;
	  globalframe = 0;
   }
}