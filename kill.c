#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#pragma bank 7
#include "fade.h"
#include "mastershogi.h"
#include "fujiyama.c"
#include "generalattack.c"
#include "weapons.c"

extern const unsigned char kuroidefeated[];
extern const unsigned char shiroidefeated[];
extern const unsigned char kuroifuhyo1[];
extern const unsigned char shiroifuhyo1[];
extern const unsigned char kuroifuhyo2[];
extern const unsigned char shiroifuhyo2[];
extern const unsigned char kuroiginshou1[];
extern const unsigned char shiroiginshou1[];
extern const unsigned char kuroiginshou2[];
extern const unsigned char shiroiginshou2[];
extern const unsigned char kuroikinshou1[];
extern const unsigned char shiroikinshou1[];
extern const unsigned char kuroikinshou2[];
extern const unsigned char shiroikinshou2[];
extern const unsigned char kuroihisha1[];
extern const unsigned char shiroihisha1[];
extern const unsigned char kuroihisha2[];
extern const unsigned char shiroihisha2[];
extern const unsigned char kuroikakugyo1[];
extern const unsigned char shiroikakugyo1[];
extern const unsigned char kuroikakugyo2[];
extern const unsigned char shiroikakugyo2[];
extern const unsigned char kuroiooshou1[];
extern const unsigned char shiroiooshou1[];
extern const unsigned char kuroiooshou2[];
extern const unsigned char shiroiooshou2[];
extern const unsigned char deadpawnraccoon[];
extern const unsigned char deadpawnfox[];
extern const unsigned char deadsilverraccoon[];
extern const unsigned char deadsilverfox[];
extern const unsigned char deadgoldraccoon[];
extern const unsigned char deadgoldfox[];
extern const unsigned char deadrookraccoon[];
extern const unsigned char deadrookfox[];
extern const unsigned char deadbishopraccoon[];
extern const unsigned char deadbishopfox[];
extern const unsigned char fujitiles[];

int raccoonact;
int foxact;

void raccoonmovement(int animation){
	switch(animation){
		case 0:
		blackdefeat();
		break;
		case 1:
		blackpawn1();
		break;
		case 2:
		blackpawn2();
		break;
		case 3:
		blacksilver1();
		break;
		case 4:
		blacksilver2();
		break;
		case 5:
		blackgold1();
		break;
		case 6:
		blackgold2();
		break;
		case 7:
		blackrook1();
		break;
		case 8:
		blackrook2();
		break;
		case 9:
		blackbishop1();
		break;
		case 10:
		blackbishop2();
		break;
		case 11:
		blackking1();
		break;
		case 12:
		blackking2();
		break;
		case 13:
		blackdead();
		break;
	}
}
void foxmovement(int animation){
	switch(animation){
		case 0:
		whitedefeat();
		break;
		case 1:
		whitepawn1();
		break;
		case 2:
		whitepawn2();
		break;
		case 3:
		whitesilver1();
		break;
		case 4:
		whitesilver2();
		break;
		case 5:
		whitegold1();
		break;
		case 6:
		whitegold2();
		break;
		case 7:
		whiterook1();
		break;
		case 8:
		whiterook2();
		break;
		case 9:
		whitebishop1();
		break;
		case 10:
		whitebishop2();
		break;
		case 11:
		whiteking1();
		break;
		case 12:
		whiteking2();
		break;
		case 13:
		whitedead();
		break;
	}
}
void cutscenesetup()
{
   disable_interrupts();
   HIDE_SPRITES;
   sprite_clean();
   if (turn == 0){
	   switch(attacker){
		   case 1:
		   foxact = 1;
		   banked_set_sprite_data(40, 14, shiroifuhyo1, 4);
		   banked_set_sprite_data(55, 17, shiroifuhyo2, 4);
		   break;
		   case 2:
		   foxact = 3;
		   banked_set_sprite_data(40, 15, shiroiginshou1, 4);
		   banked_set_sprite_data(56, 15, shiroiginshou2, 4);
		   break;
		   case 3:
		   foxact = 5;
		   banked_set_sprite_data(40, 15, shiroikinshou1, 4);
		   banked_set_sprite_data(56, 14, shiroikinshou2, 4);
		   break;
		   case 4:
		   foxact = 7;
		   banked_set_sprite_data(40, 15, shiroihisha1, 4);
		   banked_set_sprite_data(56, 15, shiroihisha2, 4);
		   break;
		   case 5:
		   foxact = 9;
		   banked_set_sprite_data(40, 15, shiroikakugyo1, 4);
		   banked_set_sprite_data(56, 13, shiroikakugyo2, 4);
		   break;
		   case 6:
		   foxact = 11;
		   banked_set_sprite_data(40, 13, shiroiooshou1, 4);
		   banked_set_sprite_data(54, 15, shiroiooshou2, 4);
		   break;
		}
		switch(victim){
		   case 1:
		   raccoonact = 1;
		   banked_set_sprite_data(0, 14, kuroifuhyo1, 4);
		   banked_set_sprite_data(15, 11, kuroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadpawnraccoon, 4);
		   break;
		   case 2:
		   raccoonact = 3;
		   banked_set_sprite_data(0, 15, kuroiginshou1, 4);
		   banked_set_sprite_data(16, 11, kuroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadsilverraccoon, 4);
		   break;
		   case 3:
		   raccoonact = 5;
		   banked_set_sprite_data(0, 15, kuroikinshou1, 4);
		   banked_set_sprite_data(16, 11, kuroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadgoldraccoon, 4);
		   break;
		   case 4:
		   raccoonact = 7;
		   banked_set_sprite_data(0, 15, kuroihisha1, 4);
		   banked_set_sprite_data(16, 11, kuroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadrookraccoon, 4);
		   break;
		   case 5:
		   raccoonact = 9;
		   banked_set_sprite_data(0, 15, kuroikakugyo1, 4);
		   banked_set_sprite_data(16, 11, kuroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadbishopraccoon, 4);
		   break;
		}
   }
   if (turn == 1){
	   switch(attacker){
		   case 1:
		   raccoonact = 1;
		   banked_set_sprite_data(0, 14, kuroifuhyo1, 4);
		   banked_set_sprite_data(15, 17, kuroifuhyo2, 4);
		   break;
		   case 2:
		   raccoonact = 3;
		   banked_set_sprite_data(0, 15, kuroiginshou1,4);
		   banked_set_sprite_data(16, 15, kuroiginshou2, 4);
		   break;
		   case 3:
		   raccoonact = 5;
		   banked_set_sprite_data(0, 15, kuroikinshou1, 4);
		   banked_set_sprite_data(16, 14, kuroikinshou2, 4);
		   break;
		   case 4:
		   raccoonact = 7;
		   banked_set_sprite_data(0, 15, kuroihisha1, 4);
		   banked_set_sprite_data(16, 15, kuroihisha2, 4);
		   break;
		   case 5:
		   raccoonact = 9;
		   banked_set_sprite_data(0, 15, kuroikakugyo1, 4);
		   banked_set_sprite_data(16, 13, kuroikakugyo2, 4);
		   break;
		   case 6:
		   raccoonact = 11;
		   banked_set_sprite_data(0, 13, kuroiooshou1, 4);
		   banked_set_sprite_data(14, 15, kuroiooshou2, 4);
		   break;
		}
		switch(victim){
		   case 1:
		   foxact = 1;
		   banked_set_sprite_data(40, 14, shiroifuhyo1, 4);
		   banked_set_sprite_data(55, 11, shiroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadpawnfox, 4);
		   break;
		   case 2:
		   foxact = 3;
		   banked_set_sprite_data(40, 15, shiroiginshou1, 4);
		   banked_set_sprite_data(56, 11, shiroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadsilverfox, 4);
		   break;
		   case 3:
		   foxact = 5;
		   banked_set_sprite_data(40, 15, shiroikinshou1, 4);
		   banked_set_sprite_data(56, 11, shiroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadgoldfox, 4);
		   break;
		   case 4:
		   foxact = 7;
		   banked_set_sprite_data(40, 15, shiroihisha1, 4);
		   banked_set_sprite_data(56, 11, shiroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadrookfox, 4);
		   break;
		   case 5:
		   foxact = 9;
		   banked_set_sprite_data(40, 15, shiroikakugyo1, 4);
		   banked_set_sprite_data(56, 11, shiroidefeated, 4);
		   banked_set_sprite_data(80, 9, deadbishopfox, 4);
		   break;
		}
   }
   set_sprite_data(90, 6, attacknumber);
   banked_set_bkg_data(0, 102, fujitiles,3);
   set_bkg_tiles(0, 0, 20, 18, fujiscenePLN0);
   banked_set_win_data(0,166,fujitiles,3);
   set_win_tiles(0,0,20,18,blackmapPLN0);
   SHOW_BKG;
   DISPLAY_ON;
   enable_interrupts();
}
void cutscene() BANKED
{
   if ((globalframe < 65) || (globalframe >= 68 & globalframe < 156) || (globalframe >= 157)){
	   globalframe += 1;
   }
   if (globalframe > 0){
	   raccoonmovement(raccoonact);
	   foxmovement(foxact);
   }
   if ((globalframe > 0 & globalframe <156) || (globalframe >= 161))
   {
	   if (raccoon.hspeed == 0){
		   if (raccoon.hcool > 0){
			   raccoon.hmove = 0;
			   raccoon.hcool = 0;
		   }
	   }
	   else{
		   if (raccoonact == 0){
			   if (raccoon.hcool < 2){
				   raccoon.hcool += 1;
				}
				if (raccoon.hcool >= 2){
					if (raccoon.back == 0){
						raccoon.x += 1;
					}
					else{
						raccoon.x -= 1;
					}
					raccoon.hcool = 0;
				}
		   }
		   else{
			   if (raccoon.hcool < 4){
				   raccoon.hcool += 1;
			   }
			   if (raccoon.hcool >= 4){
				   if (raccoon.back == 0){
					   if (raccoon.hmove < raccoon.hspeed){
						   raccoon.hmove += 1;
					   }
					   if (raccoon.hmove > raccoon.hspeed){
						   raccoon.hmove = raccoon.hspeed;
					   }
				   }
				   else{
					   if (raccoon.hmove < raccoon.hspeed){
						   raccoon.hmove += 1;
					   }
					   if (raccoon.hmove > raccoon.hspeed){
						   raccoon.hmove = raccoon.hspeed;
					   }
				   }
			   raccoon.hcool = 0;
			}
			if (raccoon.back == 0){
				raccoon.x += raccoon.hmove;
			}
			if (raccoon.back == 1){
				raccoon.x -= raccoon.hmove;
				}
			}
	   }
	   
	   if (fox.hspeed == 0){
		   if (fox.hcool > 0){
			   fox.hmove = 0;
			   fox.hcool = 0;
		   }
	   }
	   else{
		   if (foxact == 0){
			   if (fox.hcool < 2){
				   fox.hcool += 1;
				}
				if (fox.hcool >= 2){
					if (fox.back == 0){
						fox.x -= 1;
					}
					else{
						fox.x += 1;
					}
					fox.hcool = 0;
				}
		   }
		   else{
			   if (fox.hcool < 4){
				   fox.hcool += 1;
				}
				if (fox.hcool >= 4){
					if (fox.back == 0){
						if (fox.hmove < fox.hspeed){
							fox.hmove += 1;
						}
						if (fox.hmove > fox.hspeed){
							fox.hmove = fox.hspeed;
						}
					}
					else{
						if (fox.hmove < fox.hspeed){
							fox.hmove += 1;
						}
						if (fox.hmove > fox.hspeed){
							fox.hmove = fox.hspeed;
						}
					}
					fox.hcool = 0;
				}
				if (fox.back == 0){
					fox.x -= fox.hmove;
				}
				if (fox.back == 1){
					fox.x += fox.hmove;
				}
			}
	   }
	   
	   if (raccoon.jump == 0){
		   if (raccoon.vspeed != 0){
			   raccoon.vspeed = 0;
			}
			if (raccoon.vcool != 0){
				raccoon.vcool = 0;
			}
			if (raccoon.y <120){
				raccoon.jump = 1;
			}
		}
		if (raccoon.jump > 0){
			if (raccoon.fall == 0){
				if (raccoon.vspeed > 0){
					if (raccoon.vcool < 11){
						raccoon.vcool += 1;
					}
					if (raccoon.vcool >= 11){
						raccoon.vspeed -= 1;
						raccoon.vcool = 0;
					}
				}
				if (raccoon.vspeed <= 0){
					raccoon.fall = 1;
				}
			}
			if (raccoon.fall == 1){
				if (raccoon.vcool < 11){
					raccoon.vcool += 1;
				}
				if (raccoon.vcool >= 11){
					raccoon.vspeed -= 1;
					raccoon.vcool = 0;
				}
			}
			raccoon.y -= raccoon.vspeed;
			if (raccoon.y > 120){
				raccoon.back = 0;
				raccoon.hspeed = 0;
				raccoon.hcool = 0;
				raccoon.y = 120;
				raccoon.jump = 0;
			}
		}
		
		if (fox.jump == 0){
		   if (fox.vspeed != 0){
			   fox.vspeed = 0;
			}
			if (fox.vcool != 0){
				fox.vcool = 0;
			}
			if (fox.y <120){
				fox.jump = 1;
			}
		}
		if (fox.jump > 0){
			if (fox.fall == 0){
				if (fox.vspeed > 0){
					if (fox.vcool < 11){
						fox.vcool += 1;
					}
					if (fox.vcool >= 11){
						fox.vspeed -= 1;
						fox.vcool = 0;
					}
				}
				if (fox.vspeed <= 0){
					fox.fall = 1;
				}
			}
			if (fox.fall == 1){
				if (fox.vcool < 11){
					fox.vcool += 1;
				}
				if (fox.vcool >= 11){
					fox.vspeed -= 1;
					fox.vcool = 0;
				}
			}
			fox.y -= fox.vspeed;
			if (fox.y > 120){
				fox.back = 0;
				fox.hspeed = 0;
				fox.hcool = 0;
				fox.y = 120;
				fox.jump = 0;
			}
		}
   }
   if (globalframe == 1)
   {
      sprite_clean();
	  cutscenesetup();
   }
   if (globalframe == 2)
   {
      if (fadecolor == 0){
		  blackfadein();
	  }
	  else{
		  whitefadein();
	  }
	  pause = 0;
	  fadecolor = 0;
   }
   if (globalframe == 3)
   {
      changemusic(2);
	  setupraccoon();
	  setupfox();
	  if (turn == 0){
		  switch(attacker){
			  case 1:
			  foxact = 1;
			  break;
			  case 2:
			  foxact = 3;
			  break;
			  case 3:
			  foxact = 5;
			  break;
			  case 4:
			  foxact = 7;
			  break;
			  case 5:
			  foxact = 9;
			  break;
			  case 6:
			  foxact = 11;
			  break;
		  }
		  switch(victim){
			  case 1:
			  raccoonact = 1;
			  break;
			  case 2:
			  raccoonact = 3;
			  break;
			  case 3:
			  raccoonact = 5;
			  break;
			  case 4:
			  raccoonact = 7;
			  break;
			  case 5:
			  raccoonact = 9;
			  break;
			  case 6:
			  raccoonact = 11;
			  break;
		  }
	  }
	  else{
		  switch(attacker){
			  case 1:
			  raccoonact = 1;
			  break;
			  case 2:
			  raccoonact = 3;
			  break;
			  case 3:
			  raccoonact = 5;
			  break;
			  case 4:
			  raccoonact = 7;
			  break;
			  case 5:
			  raccoonact = 9;
			  break;
			  case 6:
			  raccoonact = 11;
			  break;
		  }
		  switch(victim){
			  case 1:
			  foxact = 1;
			  break;
			  case 2:
			  foxact = 3;
			  break;
			  case 3:
			  foxact = 5;
			  break;
			  case 4:
			  foxact = 7;
			  break;
			  case 5:
			  foxact = 9;
			  break;
			  case 6:
			  foxact = 11;
			  break;
		  }
	  }
   }
   if (globalframe == 4)
   {
      SHOW_SPRITES;
   }
   if (globalframe == 65)
   {
	  if (turn == 0){
		  switch(attacker){
			  case 1:
			  fox.jump = 1;
			  fox.back = 1;
			  fox.hspeed = 1;
			  fox.vspeed = 2;
			  globalframe = 66;
			  break;
			  case 2:
			  HIDE_SPRITES;
			  SHOW_WIN;
			  foxact = 4;
			  globalframe = 66;
			  break;
			  case 3:
			  HIDE_SPRITES;
			  SHOW_WIN;
			  foxact = 6;
			  globalframe = 66;
			  break;
			  case 4:
			  foxact = 8;
			  fox.shot = fox.x-4;
			  globalframe = 66;
			  break;
			  case 5:
			  foxact = 10;
			  fox.shot = fox.x-4;
			  globalframe = 66;
			  break;
			  case 6:
			  foxact = 12;
			  fox.shot = fox.x-4;
			  globalframe = 66;
			  break;
		  }
	  }
	  else{
		  switch(attacker){
			  case 1:
			  raccoon.jump = 1;
			  raccoon.back = 1;
			  raccoon.hspeed = 1;
			  raccoon.vspeed = 2;
			  globalframe = 66;
			  break;
			  case 2:
			  HIDE_SPRITES;
			  SHOW_WIN;
			  raccoonact = 4;
			  globalframe = 66;
			  break;
			  case 3:
			  HIDE_SPRITES;
			  SHOW_WIN;
			  raccoonact = 6;
			  globalframe = 66;
			  break;
			  case 4:
			  raccoonact = 8;
			  raccoon.shot = raccoon.x+4;
			  globalframe = 66;
			  break;
			  case 5:
			  raccoonact = 10;
			  raccoon.shot = raccoon.x+4;
			  globalframe = 66;
			  break;
			  case 6:
			  raccoonact = 12;
			  raccoon.shot = raccoon.x+4;
			  globalframe = 66;
			  break;
		  }
	  }
   }
   if (globalframe == 66)
   {
	  if (turn == 0){
		  switch(attacker){
			  case 1:
			  if (fox.jump == 0){
				  globalframe = 67;
			  }
			  break;
			  case 2:
			  foxsilverslash();
			  SHOW_SPRITES;
			  HIDE_WIN;
			  globalframe = 68;
			  break;
			  case 3:
			  foxgoldslash();
			  SHOW_SPRITES;
			  HIDE_WIN;
			  globalframe = 68;
			  break;
			  case 4:
			  if (fox.shot <= 72){
				  fox.shot = 200;
				  globalframe = 68;
			  }
			  else{
				  fox.shot -= 3;
			  }
			  break;
			  case 5:
			  if (fox.shot <= 72){
				  fox.shot = 200;
				  globalframe = 68;
			  }
			  else{
				  fox.shot -= 2;
			  }
			  break;
			  case 6:
			  if (fox.shot <= 72){
				  fox.shot = 200;
				  globalframe = 67;
			  }
			  else{
				  fox.shot -= 1;
			  }
			  break;
		  }
	  }
	  else{
		  switch(attacker){
			  case 1:
			  if (raccoon.jump == 0){
				  globalframe = 67;
			  }
			  break;
			  case 2:
			  raccoonsilverslash();
			  SHOW_SPRITES;
			  HIDE_WIN;
			  globalframe = 68;
			  break;
			  case 3:
			  raccoongoldslash();
			  SHOW_SPRITES;
			  HIDE_WIN;
			  globalframe = 68;
			  break;
			  case 4:
			  if (raccoon.shot >= 88){
				  raccoon.shot = 200;
				  globalframe = 68;
			  }
			  else{
				  raccoon.shot += 3;
			  }
			  break;
			  case 5:
			  if (raccoon.shot >= 88){
				  raccoon.shot = 200;
				  globalframe = 68;
			  }
			  else{
				  raccoon.shot += 2;
			  }
			  break;
			  case 6:
			  if (raccoon.shot >= 88){
				  raccoon.shot = 200;
				  globalframe = 67;
			  }
			  else{
				  raccoon.shot += 1;
			  }
			  break;
		  }
	  }
   }
   if (globalframe == 67)
   {
	  if (turn == 0){
		  switch(attacker){
			  case 1:
			  if (fox.jump == 0){
				  if (fox.x > 80){
					  foxact = 2;
					  fox.back = 0;
					  fox.hspeed = 3;
				  }
				  if (fox.x <= 80){
					  fox.hspeed = 0;
					  globalframe = 68;
				  }
			  }
			  break;
			  case 6:
			  HIDE_SPRITES;
			  SHOW_WIN;
			  foxkingpunches();
			  SHOW_SPRITES;
			  HIDE_WIN;
			  globalframe = 68;
			  break;
		  }
	  }
	  else{
		  switch(attacker){
			  case 1:
			  if (raccoon.jump == 0){
				  if (raccoon.x < 80){
					  raccoonact = 2;
					  raccoon.back = 0;
					  raccoon.hspeed = 3;
				  }
				  if (raccoon.x >= 80){
					  raccoon.hspeed = 0;
					  globalframe = 68;
				  }
			  }
			  break;
			  case 6:
			  HIDE_SPRITES;
			  SHOW_WIN;
			  raccoonkingpunches();
			  SHOW_SPRITES;
			  HIDE_WIN;
			  globalframe = 68;
			  break;
		  }
	  }
   }
   if (globalframe == 68)
   {
	  if (turn == 0){
		  raccoon.jump = 1;
		  raccoon.back = 1;
		  raccoon.hspeed = 1;
		  raccoon.vspeed = 2;
		  raccoon.y -= 8;
		  raccoonact = 0;
	  }
	  else{
		  fox.jump = 1;
		  fox.back = 1;
		  fox.hspeed = 1;
		  fox.vspeed = 2;
		  fox.y -= 8;
		  foxact = 0;
	  }
   }
   if (globalframe == 148)
   {
	  if (turn == 0){
		  switch(attacker){
			  case 1:
			  foxact = 1;
			  break;
			  case 5:
			  foxact = 9;
			  break;
			  case 6:
			  foxact = 11;
			  break;
		  }
	  }
	  else{
		  switch(attacker){
			  case 1:
			  raccoonact = 1;
			  break;
			  case 5:
			  raccoonact = 9;
			  break;
			  case 6:
			  raccoonact = 11;
			  break;
		  }
	  }
   }
   if (globalframe == 156)
   {
	  if (turn == 0){
		  if (raccoon.y <= 78){
			  raccoonfadeout();
			  globalframe = 157;
		  }
		  if (raccoon.y > 78){
			  raccoon.y -= 1;
		  }
	  }
	  else{
		  if (fox.y <= 78){
			  foxfadeout();
			  globalframe = 157;
		  }
		  if (fox.y > 78){
			  fox.y -= 1;
		  }
	  }
   }
   if (globalframe == 157)
   {
	  if (turn == 0){
		  raccoonact = 13;
	  }
	  else{
		  foxact = 13;
	  }
   }
   if (globalframe == 160)
   {
	  if (turn == 0){
		  raccoonfadein();
		  globalframe = 161;
	  }
	  else{
		  foxfadein();
		  globalframe = 161;
	  }
   }
   if (globalframe == 255)
   {
	  sprite_clean();
	  if (fadecolor == 0){
		  blackfadeout();
	  }
	  else{
		  whitefadeout();
	  }
   }
   if (globalframe == 256)
   {
      gamestate = 5;
	  globalframe = 0;
   }
}