#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "mastershogi.h"
#include "Shogitiles.h"

void boardupdate()
{
   if (board[1] == 10)
   {
      set_bkg_tiles(5,7,1,1,&shogidata[50]);
	  set_bkg_tiles(6,7,1,1,&shogidata[51]);
	  set_bkg_tiles(5,8,1,1,&shogidata[52]);
	  set_bkg_tiles(6,8,1,1,&shogidata[53]);
   }
}