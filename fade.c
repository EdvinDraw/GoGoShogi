#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include "fade.h"
#include "mastershogi.h"
void performantdelay(UINT8 numloops)
{
   UINT8 i;
   for(i = 0; i < numloops; i++)
   {
      wait_vbl_done();
   }     
}
void blackfadeout()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         BGP_REG = 0xF9;
         break;
         case 1:
         BGP_REG = 0xFE;
         break;
         case 2:
		 OBP0_REG = 0xE4;
		 OBP1_REG = 0xD1;
         BGP_REG = 0xFF;
         break;						
      }
	  performantdelay(8);
   }
}
void blackfadein()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         BGP_REG = 0xFE;
         break;
         case 1:
         BGP_REG = 0xF9;
         break;
         case 2:
		 OBP0_REG = 0xE4;
		 OBP1_REG = 0xD1;
         BGP_REG = 0xE4;
         break;					
      }
	  performantdelay(8);
   }
}
void whitefadeout()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
		 BGP_REG = 0x80;
         break;
         case 1:
         BGP_REG = 0x40;
         break;
         case 2:
		 OBP0_REG = 0xE4;
		 OBP1_REG = 0xD1;
         BGP_REG = 0x00;
         break;						
      }
	  performantdelay(8);
   }
}
void whitefadein()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         BGP_REG = 0x40;
         break;
         case 1:
         BGP_REG = 0x80;
         break;
         case 2:
		 OBP0_REG = 0xE4;
		 OBP1_REG = 0xD1;
         BGP_REG = 0xE4;
         break;					
      }
	  performantdelay(8);
   }
}
void raccoonfadeout()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         OBP0_REG = 0x80;
         break;
         case 1:
         OBP0_REG = 0x40;
         break;
         case 2:
         OBP0_REG = 0x00;
         break;						
      }
	  performantdelay(8);
   }
}
void raccoonfadein()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         OBP0_REG = 0x40;
         break;
         case 1:
         OBP0_REG = 0x80;
         break;
         case 2:
         OBP0_REG = 0xE4;
         break;					
      }
	  performantdelay(8);
   }
}
void foxfadeout()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         OBP1_REG = 0x80;
         break;
         case 1:
         OBP1_REG = 0x40;
         break;
         case 2:
         OBP1_REG = 0x00;
         break;						
      }
	  performantdelay(8);
   }
}
void foxfadein()
{
   for(UINT8 f=0;f<3;f++)
   {
      switch(f)
      {
         case 0:
         OBP1_REG = 0x40;
         break;
         case 1:
         OBP1_REG = 0x80;
         break;
         case 2:
         OBP1_REG = 0xE4;
         break;					
      }
	  performantdelay(8);
   }
}
void raccoonsilverslash()
{
   for(UINT8 f=0;f<12;f++)
   {
      switch(f)
      {
         case 2:
         set_win_tiles(6, 9, 7, 1, black_silverslash1);
         break;
         case 3:
         set_win_tiles(6, 10, 7, 1, black_silverslash2);
         break;
         case 4:
         set_win_tiles(6, 11, 7, 1, black_silverslash3);
         break;
		 case 5:
         set_win_tiles(6, 12, 7, 1, black_silverslash4);
         break;
		 case 6:
         set_win_tiles(6, 9, 7, 1, no_slash1);
         break;
         case 7:
         set_win_tiles(6, 10, 7, 1, no_slash1);
         break;
         case 8:
         set_win_tiles(6, 11, 7, 1, no_slash1);
         break;
		 case 9:
         set_win_tiles(6, 12, 7, 1, no_slash1);
         break;
      }
	  performantdelay(12);
   }
}
void foxsilverslash()
{
   for(UINT8 f=0;f<12;f++)
   {
      switch(f)
      {
         case 2:
         set_win_tiles(7, 9, 7, 1, white_silverslash1);
         break;
         case 3:
         set_win_tiles(7, 10, 7, 1, white_silverslash2);
         break;
         case 4:
         set_win_tiles(7, 11, 7, 1, white_silverslash3);
         break;
		 case 5:
         set_win_tiles(7, 12, 7, 1, white_silverslash4);
         break;
		 case 6:
         set_win_tiles(7, 9, 7, 1, no_slash1);
         break;
         case 7:
         set_win_tiles(7, 10, 7, 1, no_slash1);
         break;
         case 8:
         set_win_tiles(7, 11, 7, 1, no_slash1);
         break;
		 case 9:
         set_win_tiles(7, 12, 7, 1, no_slash1);
         break;
      }
	  performantdelay(12);
   }
}
void raccoongoldslash()
{
   for(UINT8 f=0;f<16;f++)
   {
      switch(f)
      {
         case 2:
         set_win_tiles(6, 11, 1, 2, black_goldslash1);
         break;
         case 3:
         set_win_tiles(7, 12, 3, 1, black_goldslash2);
         break;
         case 4:
         set_win_tiles(10, 11, 3, 2, black_goldslash3);
         break;
		 case 5:
         set_win_tiles(10, 9, 3, 2, black_goldslash4);
         break;
		 case 6:
         set_win_tiles(8, 9, 2, 2, black_goldslash5);
         break;
         case 7:
         set_win_tiles(7, 11, 3, 1, black_goldslash6);
         break;
         case 8:
         set_win_tiles(6, 11, 1, 2, no_slash2);
         break;
         case 9:
         set_win_tiles(7, 12, 3, 1, no_slash3);
         break;
         case 10:
         set_win_tiles(10, 11, 3, 2, no_slash4);
         break;
		 case 11:
         set_win_tiles(10, 9, 3, 2, no_slash4);
         break;
		 case 12:
         set_win_tiles(8, 9, 2, 2, no_slash5);
         break;
         case 13:
         set_win_tiles(7, 11, 3, 1, no_slash3);
         break;
      }
	  performantdelay(8);
   }
}
void foxgoldslash()
{
   for(UINT8 f=0;f<16;f++)
   {
      switch(f)
      {
         case 2:
         set_win_tiles(13, 11, 1, 2, white_goldslash1);
         break;
         case 3:
         set_win_tiles(10, 12, 3, 1, white_goldslash2);
         break;
         case 4:
         set_win_tiles(7, 11, 3, 2, white_goldslash3);
         break;
		 case 5:
         set_win_tiles(7, 9, 3, 2, white_goldslash4);
         break;
		 case 6:
         set_win_tiles(10, 9, 2, 2, white_goldslash5);
         break;
         case 7:
         set_win_tiles(10, 11, 3, 1, white_goldslash6);
         break;
         case 8:
         set_win_tiles(13, 11, 1, 2, no_slash2);
         break;
         case 9:
         set_win_tiles(10, 12, 3, 1, no_slash3);
         break;
         case 10:
         set_win_tiles(7, 11, 3, 2, no_slash4);
         break;
		 case 11:
         set_win_tiles(7, 9, 3, 2, no_slash4);
         break;
		 case 12:
         set_win_tiles(10, 9, 2, 2, no_slash5);
         break;
         case 13:
         set_win_tiles(10, 11, 3, 1, no_slash3);
         break;
      }
	  performantdelay(8);
   }
}
void foxkingpunches()
{
   for(UINT8 f=0;f<32;f++)
   {
      switch(f)
      {
         case 2:
         set_win_tiles(6, 9, 2, 2, king_punch1);
         break;
         case 3:
         set_win_tiles(6, 9, 2, 2, king_punch2);
         break;
         case 4:
         set_win_tiles(6, 9, 2, 2, king_punch3);
         break;
		 case 5:
         set_win_tiles(6, 9, 2, 2, king_punch4);
         break;
		 case 6:
         set_win_tiles(6, 9, 2, 2, king_punch5);
         break;
         case 7:
         set_win_tiles(6, 9, 2, 2, no_slash5);
         break;
		 case 12:
         set_win_tiles(8, 10, 2, 2, king_punch1);
         break;
         case 13:
         set_win_tiles(8, 10, 2, 2, king_punch2);
         break;
         case 14:
         set_win_tiles(8, 10, 2, 2, king_punch3);
         break;
		 case 15:
         set_win_tiles(8, 10, 2, 2, king_punch4);
         break;
		 case 16:
         set_win_tiles(8, 10, 2, 2, king_punch5);
         break;
         case 17:
         set_win_tiles(8, 10, 2, 2, no_slash5);
         break;
		 case 22:
         set_win_tiles(7, 12, 2, 2, king_punch1);
         break;
         case 23:
         set_win_tiles(7, 12, 2, 2, king_punch2);
         break;
         case 24:
         set_win_tiles(7, 12, 2, 2, king_punch3);
         break;
		 case 25:
         set_win_tiles(7, 12, 2, 2, king_punch4);
         break;
		 case 26:
         set_win_tiles(7, 12, 2, 2, king_punch5);
         break;
         case 27:
         set_win_tiles(7, 12, 2, 2, no_slash5);
         break;
      }
	  performantdelay(4);
   }
}
void raccoonkingpunches()
{
   for(UINT8 f=0;f<32;f++)
   {
      switch(f)
      {
         case 2:
         set_win_tiles(12, 9, 2, 2, king_punch1);
         break;
         case 3:
         set_win_tiles(12, 9, 2, 2, king_punch2);
         break;
         case 4:
         set_win_tiles(12, 9, 2, 2, king_punch3);
         break;
		 case 5:
         set_win_tiles(12, 9, 2, 2, king_punch4);
         break;
		 case 6:
         set_win_tiles(12, 9, 2, 2, king_punch5);
         break;
         case 7:
         set_win_tiles(12, 9, 2, 2, no_slash5);
         break;
		 case 12:
         set_win_tiles(10, 10, 2, 2, king_punch1);
         break;
         case 13:
         set_win_tiles(10, 10, 2, 2, king_punch2);
         break;
         case 14:
         set_win_tiles(10, 10, 2, 2, king_punch3);
         break;
		 case 15:
         set_win_tiles(10, 10, 2, 2, king_punch4);
         break;
		 case 16:
         set_win_tiles(10, 10, 2, 2, king_punch5);
         break;
         case 17:
         set_win_tiles(10, 10, 2, 2, no_slash5);
         break;
		 case 22:
         set_win_tiles(11, 12, 2, 2, king_punch1);
         break;
         case 23:
         set_win_tiles(11, 12, 2, 2, king_punch2);
         break;
         case 24:
         set_win_tiles(11, 12, 2, 2, king_punch3);
         break;
		 case 25:
         set_win_tiles(11, 12, 2, 2, king_punch4);
         break;
		 case 26:
         set_win_tiles(11, 12, 2, 2, king_punch5);
         break;
         case 27:
         set_win_tiles(11, 12, 2, 2, no_slash5);
         break;
      }
	  performantdelay(4);
   }
}