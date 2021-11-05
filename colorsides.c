#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#pragma bank 6
#include "Shogitiles.c"
#include "optionscreen2.c"
#include "fade.h"
#include "mastershogi.h"

extern const unsigned char arrowcursor[];

void colorsetup()
{
   disable_interrupts();
   SCY_REG = 0;
   HIDE_SPRITES;
   sprite_clean();
   set_bkg_tiles(0,0,20,18,colorscreenPLN0);
   selection = 1;
   selected = 0;
   flash = 0;
   joypressed = 0;
   SHOW_BKG;
   DISPLAY_ON;
   enable_interrupts();
}
void leftarrow2()
{
   disable_interrupts();
   set_sprite_tile(0,0);
   set_sprite_prop(0,0x00);
   move_sprite(0,56,104);
   SHOW_SPRITES;
   enable_interrupts();
}
void colormenu() BANKED
{
   if ((globalframe < 4) || ((globalframe > 4) & (globalframe < 7)))
   {
      globalframe += 1;
   }
   if (globalframe == 1)
   {
      colorsetup();
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
      leftarrow2();
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
		 if ((joypad() & J_B))
	     {
		    selected = 1;
			selection = 3;
			globalframe = 5;
	     }
		 if (joypad() & J_UP)
	     {
	        if (selection > 0)
		    {
		       selection -= 1;
		    }
		    if (selection <= 0)
		    {
		       selection = 2;
		    }
		    joypressed = 1;
	     }
	     if ((joypad() & J_DOWN) || (joypad() & J_SELECT))
	     {
	        if (selection < 3)
		    {
		       selection += 1;
		    }
		    if (selection >= 3)
		    {
		       selection = 1;
		    }
		    joypressed = 1;
	     }
	  }
	  if (selection == 1)
      {
         move_sprite(0,56,104);
	  }
	  if (selection == 2)
      {
         move_sprite(0,56,128);
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
      if (selection == 1)
	  {
	     newgame = 1;
		 color = 0;
		 turn = 0;
		 pause = 0;
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
		 gamestate = 5;
	  }
	  if (selection == 2)
	  {
	     newgame = 1;
		 color = 1;
		 turn = 1;
		 pause = 0;
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
		 gamestate = 5;
	  }
	  if (selection == 3)
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