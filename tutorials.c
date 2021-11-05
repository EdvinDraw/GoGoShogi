#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#pragma bank 4
#include "tutorialone.c"
#include "tutorialtwo.c"
#include "fade.h"
#include "mastershogi.h"
#include "raccoonpawn1.c"
#include "raccoonpawn2.c"
#include "raccoonsilver1.c"
#include "raccoonsilver2.c"
#include "raccoongold1.c"
#include "raccoongold2.c"
#include "raccoonrook1.c"
#include "raccoonrook2.c"
#include "raccoonbishop1.c"
#include "raccoonbishop2.c"
#include "raccoonking1.c"
#include "raccoonking2.c"
#include "raccoondown.c"
#include "foxpawn1.c"
#include "foxpawn2.c"
#include "foxsilver1.c"
#include "foxsilver2.c"
#include "foxgold1.c"
#include "foxgold2.c"
#include "foxrook1.c"
#include "foxrook2.c"
#include "foxbishop1.c"
#include "foxbishop2.c"
#include "foxking1.c"
#include "foxking2.c"
#include "foxdown.c"
#include "deadpawnblack.c"
#include "deadpawnwhite.c"
#include "deadsilverblack.c"
#include "deadsilverwhite.c"
#include "deadgoldblack.c"
#include "deadgoldwhite.c"
#include "deadrookblack.c"
#include "deadrookwhite.c"
#include "deadbishopblack.c"
#include "deadbishopwhite.c"

extern const unsigned char arrowcursor[];

void helpsetup()
{
   disable_interrupts();
   SCY_REG = scroll;
   HIDE_SPRITES;
   sprite_clean();
   scroll = 0;
   selection = 2;
   set_bkg_tiles(0, 0, 20, 18, pageonePLN0);
   selected = 0;
   flash = 0;
   joypressed = 0;
   SHOW_BKG;
   DISPLAY_ON;
   enable_interrupts();
}
void uparrow()
{
   disable_interrupts();
   set_sprite_tile(0, 1);
   set_sprite_prop(0, 0x00);
   move_sprite(0, 156, 138);
   SHOW_SPRITES;
   enable_interrupts();
}
void downarrow()
{
   disable_interrupts();
   set_sprite_tile(1, 2);
   set_sprite_prop(1, 0x00);
   move_sprite(1, 156, 150);
   SHOW_SPRITES;
   enable_interrupts();
}
void helpmenu() BANKED
{
   if ((globalframe < 4) || ((globalframe > 4) & (globalframe < 7)))
   {
      globalframe += 1;
   }
   if (globalframe == 1)
   {
      helpsetup();
	  set_bkg_tiles(0, scroll, 20, scroll+18, pageonePLN0);
   }
   if (globalframe == 2)
   {
	  if (fadecolor == 0){
		  blackfadein();
	  }
	  else{
		  whitefadein();
	  }
	  fadecolor = 1;
   }
   if (globalframe == 3)
   {
      uparrow();
	  downarrow();
   }
   if (globalframe >= 4)
   {
	  scroll_bkg(0, scroll);
	  move_bkg(0, scroll);
	  if (joypressed == 0)
	  {
	     if ((joypad() & J_A))
	     {
		    selected = 1;
			selection += 1;
			globalframe = 5;
			joypressed = 1;
	     }
		 if ((joypad() & J_B))
	     {
		    selected = 1;
			selection -= 1;
			globalframe = 5;
			joypressed = 1;
	     }
		 if (joypad() & J_UP)
	     {
			scroll -= 1;
	     }
	     if ((joypad() & J_DOWN))
	     {
	        scroll += 1;
	     }
	  }
   }
   if (globalframe == 6)
   {
      sprite_clean();
	  if (fadecolor == 0){
		  blackfadeout();
	  }
	  else{
		  whitefadeout();
	  }
   }
   if (globalframe == 7)
   {
      if (selection <= 1)
	  {
	     gamestate = 2;
	  }
	  globalframe = 0;
   }
   if (joypressed == 1)
   {
      if ((!(joypad() & J_UP)) & (!(joypad() & J_DOWN)) & (!(joypad() & J_LEFT)) & (!(joypad() & J_RIGHT)) & (!(joypad() & J_A)) & (!(joypad() & J_START)) & (!(joypad() & J_SELECT)))
      {
         joypressed = 0;
      }
   }
}