#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#pragma bank 5
#include "Shogiobjects.c"
#include "Board.c"
#include "fade.h"
#include "boardcode.h"
#include "mastershogi.h"

extern const unsigned char shogidata[];
extern const unsigned char kitsunelose[];
extern const unsigned char kitsunehappy[];
extern const unsigned char kitsunethink1[];
extern const unsigned char kitsunethink2[];
extern const unsigned char kitsunewin1[];
extern const unsigned char kitsunewin2[];
extern const unsigned char kitsunesad[];
extern const unsigned char kitsunenormal[];
extern const unsigned char tanukilose[];
extern const unsigned char tanukihappy[];
extern const unsigned char tanukithink1[];
extern const unsigned char tanukithink2[];
extern const unsigned char tanukiwin1[];
extern const unsigned char tanukiwin2[];
extern const unsigned char tanukisad[];
extern const unsigned char tanukinormal[];

enum PieceType{
	EMPTY = 0, 
	PAWN, 
	PAWNPLUS, 
	SILVER, 
	SILVERPLUS, 
	GOLD, 
	BISHOP, 
	BISHOPPLUS, 
	ROOK, 
	ROOKPLUS, 
	KING, 
};

void marker() BANKED{
	move_sprite(0, (16*pointx)-8+48, (16*pointy)-8+72);
	move_sprite(1, (16*pointx)+48, (16*pointy)-8+72);
	move_sprite(2, (16*pointx)+8+48, (16*pointy)-8+72);
	move_sprite(3, (16*pointx)+16+48, (16*pointy)-8+72);
	move_sprite(4, (16*pointx)-8+48, (16*pointy)+72);
	move_sprite(5, (16*pointx)+48, (16*pointy)+72);
	move_sprite(6, (16*pointx)+8+48, (16*pointy)+72);
	move_sprite(7, (16*pointx)+16+48, (16*pointy)+72);
	move_sprite(8, (16*pointx)-8+48, (16*pointy)+8+72);
	move_sprite(9, (16*pointx)+48, (16*pointy)+8+72);
	move_sprite(10, (16*pointx)+8+48, (16*pointy)+8+72);
	move_sprite(11, (16*pointx)+16+48, (16*pointy)+8+72);
	move_sprite(12, (16*pointx)-8+48, (16*pointy)+16+72);
	move_sprite(13, (16*pointx)+48, (16*pointy)+16+72);
	move_sprite(14, (16*pointx)+8+48, (16*pointy)+16+72);
	move_sprite(15, (16*pointx)+16+48, (16*pointy)+16+72);
}

void blackmove(){ //Movesets for the black pieces
	if (isWhite(pointx, pointy)){
		banked_set_bkg_data(170, 16, tanukihappy, 1);
		if ((board[pointx + pointy * BOARD_W] == (PAWN | IS_WHITE)) || (board[pointx + pointy * BOARD_W] == (PAWNPLUS | IS_WHITE))){
			victim = 1;
			P_one += 1;
		}
		else if ((board[pointx + pointy * BOARD_W] == (SILVER | IS_WHITE)) || (board[pointx + pointy * BOARD_W] == (SILVERPLUS | IS_WHITE))){
			victim = 2;
			S_one += 1;
		}
		else if (board[pointx + pointy * BOARD_W] == (GOLD | IS_WHITE)){
			victim = 3;
			G_one += 1;
		}
		else if ((board[pointx + pointy * BOARD_W] == (ROOK | IS_WHITE)) || (board[pointx + pointy * BOARD_W] == (ROOKPLUS | IS_WHITE))){
			victim = 4;
			R_one += 1;
		}
		else if ((board[pointx + pointy * BOARD_W] == (BISHOP | IS_WHITE)) || (board[pointx + pointy * BOARD_W] == (BISHOPPLUS | IS_WHITE))){
			victim = 5;
			B_one += 1;
		}
		
		board[pointx + pointy * BOARD_W] = pieceselected;
		boardselected = 0;
		pointersprite();
		turn = 1;
		pause = 2;
		globalframe = 4;
	}
	else if (isBlack(pointx, pointy)){
		board[pointx2 + pointy2 * BOARD_W] = pieceselected;
		pointx = pointx2;
		pointy = pointy2;
		boardselected = 0;
		pointersprite();
	}
	else if (board[pointx + pointy * BOARD_W] == EMPTY){
		banked_set_bkg_data(170, 16, tanukinormal, 1);
		board[pointx + pointy * BOARD_W] = pieceselected;
		boardselected = 0;
		pointersprite();
		turn = 1;
	}
}
void whitemove(){ //Movesets for the white pieces
	if (isBlack(pointx, pointy)){
		banked_set_bkg_data(186, 16, kitsunehappy, 1);
		if ((board[pointx + pointy * BOARD_W] == PAWN) || (board[pointx + pointy * BOARD_W] == PAWNPLUS)){
			victim = 1;
			P_two += 1;
		}
		else if ((board[pointx + pointy * BOARD_W] == SILVER) || (board[pointx + pointy * BOARD_W] == SILVERPLUS)){
			victim = 2;
			S_two += 1;
		}
		else if (board[pointx + pointy * BOARD_W] == GOLD){
			victim = 3;
			G_two += 1;
		}
		else if ((board[pointx + pointy * BOARD_W] == ROOK) || (board[pointx + pointy * BOARD_W] == ROOKPLUS)){
			victim = 4;
			R_two += 1;
		}
		else if ((board[pointx + pointy * BOARD_W] == BISHOP) || (board[pointx + pointy * BOARD_W] == BISHOPPLUS)){
			victim = 5;
			B_two += 1;
		}
		
		board[pointx + pointy * BOARD_W] = pieceselected;
		boardselected = 0;
		pointersprite();
		turn = 0;
		pause = 2;
		globalframe = 4;
	}
	else if (isWhite(pointx, pointy)){
		board[pointx2 + pointy2 * BOARD_W] = (pieceselected | IS_WHITE);
		pointx = pointx2;
		pointy = pointy2;
		boardselected = 0;
		pointersprite();
	}
	else if (board[pointx + pointy * BOARD_W] == EMPTY){
		banked_set_bkg_data(186, 16, kitsunenormal, 1);
		board[pointx + pointy * BOARD_W] = pieceselected;
		boardselected = 0;
		pointersprite();
		turn = 0;
	}
}

void boardsetup()
{
   disable_interrupts();
   HIDE_SPRITES;
   sprite_clean();
   banked_set_bkg_data(0, 203, shogidata, 6);
   banked_set_bkg_data(170, 16, tanukinormal, 1);
   banked_set_bkg_data(186, 16, kitsunenormal, 1);
   set_bkg_tiles(0, 0, 20, 18, BattlefieldPLN0);
   set_sprite_data(0, 77, Object);
   attacker = 1;
   victim = 1;
   if (newgame == 1){
	   initBoard();
   }
   SHOW_SPRITES;
   enable_interrupts();
}
void shogifield() BANKED
{
   if ((globalframe < 3) || ((globalframe > 3) & (globalframe < 7)))
   {
      globalframe += 1;
   }
   if (globalframe == 1)
   {
	  boardsetup();
   }
   if (globalframe == 2)
   {
	  if (fadecolor == 0){
		  blackfadein();
	  }
	  else{
		  whitefadein();
	  }
	  pointersprite();
	  marker();
	  counter();
	  if (newgame == 1){
		  black_check = 0;
		  white_check = 0;
		  changemusic(4);
		  newgame = 0;
	  }
	  fadecolor = 0;
   }
    if (globalframe == 3)
   {
	  boardupdate();
	  tablet(pause);
	  switch(pause){
		case 0:
		if (joypressed == 0){
			if ((joypad() & J_START)){
				giving_up();
				joypressed = 1;
			}
			if ((joypad() & J_SELECT)){
				selection = 1;
				pause = 3;
				dropselect();
				joypressed = 1;
			}
			if ((joypad() & J_A)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){ //To the left is for Singleplayer, and to the right is for Multiplayer
					if (turn == 0){ //Black's turn
						if (boardselected == 0){ //Not selected a piece
							if (isBlack(pointx, pointy)){
								boardselect(pointx, pointy);
								pointx2 = pointx;
								pointy2 = pointy;
								pieceselected = (board[pointx + pointy * BOARD_W]);
								board[pointx2 + pointy2 * BOARD_W] = EMPTY;
								boardselected = 1;
							}
						}
						else{ //Selected a piece
							if (pointx == pointx2 && pointy == pointy2){ //If you select the same position, it will cancel your piece
								canceling();
							}
							else{
								if (valid == 1){
									if (pointy == 0 || pointy2 == 0){
										if (pieceselected == PAWN){
											pieceselected = PAWNPLUS;
											if (isWhite(pointx,pointy)){
												blackmove();
											}
											else{
												pause = 5;
											}
										}
										else if (pieceselected == SILVER || pieceselected == ROOK || pieceselected == BISHOP){
											selection = 1;
											pause = 2;
											set_bkg_tiles(6, 1, 8, 4, promote);
											set_sprite_tile(16, 76);
											set_sprite_prop(16, 0x00|S_PALETTE);
										}
										else{
											blackmove();
										}
									}
									else{
										blackmove();
									}
								}
								else{
									canceling();
								}
							}
						}
					}
					if (turn == 1){ //White's turn
						if (boardselected == 0){ //Not selected a piece
							if (isWhite(pointx, pointy)){
								boardselect(pointx, pointy);
								pointx2 = pointx;
								pointy2 = pointy;
								pieceselected = (board[pointx + pointy * BOARD_W] | IS_WHITE);
								board[pointx2 + pointy2 * BOARD_W] = EMPTY;
								boardselected = 1;
							}
						}
						else{ //Selected a piece
							if (pointx == pointx2 && pointy == pointy2){ //If you select the same position, it will cancel your piece
								canceling();
							}
							else{
								if (valid == 1){
									if (pointy == 4 || pointy2 == 4){
										if (pieceselected == (PAWN | IS_WHITE)){
											pieceselected = (PAWNPLUS | IS_WHITE);
											if (isBlack(pointx,pointy)){
												whitemove();
											}
											else{
												pause = 5;
											}
										}
										else if (pieceselected == (SILVER | IS_WHITE) || pieceselected == (ROOK | IS_WHITE) || pieceselected == (BISHOP | IS_WHITE)){
											selection = 1;
											pause = 2;
											set_bkg_tiles(6, 1, 8, 4, promote);
											set_sprite_tile(16, 76);
											set_sprite_prop(16, 0x00|S_PALETTE);
										}
										else{
											whitemove();
										}
									}
									else{
										whitemove();
									}
								}
								else{
									canceling();
								}
							}
						}
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_B)){
				if (boardselected == 1){
					if (pieceselected == (board[pointx + pointy * BOARD_W] & IS_WHITE)){ //White piece cancelled
						board[pointx2 + pointy2 * BOARD_W] = (pieceselected | IS_WHITE);
					}
					else{ //Black piece cancelled
						board[pointx2 + pointy2 * BOARD_W] = pieceselected;
					}
					boardselect(pointx, pointy);
					pointx = pointx2;
					pointy = pointy2;
					boardselected = 0;
					pointersprite();
				}
				joypressed = 1;
			}
			if ((joypad() & J_UP)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointy == 0){
						pointy = 4;
					}
					else{
						pointy -= 1;
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_DOWN)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointy == 4){
						pointy = 0;
					}
					else{
						pointy += 1;
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_LEFT)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointx == 0){
						pointx = 4;
					}
					else{
						pointx -= 1;
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_RIGHT)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointx == 4){
						pointx = 0;
					}
					else{
						pointx += 1;
					}
				}
				joypressed = 1;
			}
		}
		if (joypressed == 1){
			counter();
			if (boardselected == 0){
				marker();
			}
			else{
				pointer();
			}
		}
		break;
		case 1: //Giving up?
		if (selection == 1){
			move_sprite(16, 64, 40);
		}
		if (selection == 2){
			move_sprite(16, 64, 48);
		}
		if (joypressed == 0){
			if ((joypad() & J_A)){
				if (selection == 1){
					globalframe = 4;
					joypressed = 1;
				}
				if (selection == 2){
					pause = 0;
					selection = 1;
					joypressed = 1;
				}
			}
			if ((joypad() & J_B)){
				pause = 0;
				selection = 1;
			}
			if ((joypad() & J_UP)){
				if (selection == 1){
					selection = 2;
				}
				else{
					selection -= 1;
				}
				joypressed = 1;
			}
			if ((joypad() & J_DOWN)){
				if (selection == 2){
					selection = 1;
				}
				else{
					selection += 1;
				}
			joypressed = 1;
			}
		}
		if (joypressed == 1){
			counter();
			if (boardselected == 0){
				marker();
			}
			else{
				pointer();
			}
		}
		case 2: //Promote?
		if (selection == 1){
			move_sprite(16, 64, 40);
		}
		if (selection == 2){
			move_sprite(16, 64, 48);
		}
		if (joypressed == 0){
			if ((joypad() & J_A)){
				if (selection == 1){
					pause = 0;
					selection = 1;
					if (turn == 0){
						if (pieceselected == SILVER){
							pieceselected = SILVERPLUS;
						}
						if (pieceselected == ROOK){
							pieceselected = ROOKPLUS;
						}
						if (pieceselected == BISHOP){
							pieceselected = BISHOPPLUS;
						}
						if (isWhite(pointx,pointy)){
							blackmove();
						}
						else{
							pause = 5;
						}
					}
					else{
						if (pieceselected == (SILVER | IS_WHITE)){
							pieceselected = (SILVERPLUS | IS_WHITE);
						}
						if (pieceselected == (ROOK | IS_WHITE)){
							pieceselected = (ROOKPLUS | IS_WHITE);
						}
						if (pieceselected == (BISHOP | IS_WHITE)){
							pieceselected = (BISHOPPLUS | IS_WHITE);
						}
						if (isBlack(pointx,pointy)){
							whitemove();
						}
						else{
							pause = 5;
						}
					}
					joypressed = 1;
				}
				if (selection == 2){
					pause = 0;
					selection = 1;
					if (turn == 0){
						blackmove();
					}
					else{
						whitemove();
					}
					joypressed = 1;
				}
			}
			if ((joypad() & J_UP)){
				if (selection == 1){
					selection = 2;
				}
				else{
					selection -= 1;
				}
				joypressed = 1;
			}
			if ((joypad() & J_DOWN)){
				if (selection == 2){
					selection = 1;
				}
				else{
					selection += 1;
				}
			joypressed = 1;
			}
		}
		if (joypressed == 1){
			counter();
			if (boardselected == 0){
				marker();
			}
			else{
				pointer();
			}
		}
		break;
		case 3: //Captured pieces area
		if (joypressed == 0){
			if ((joypad() & J_A)){
				switch(selection){
					case 1:
						if (turn == 0){
							if (P_one > 0){
								pieceselected = PAWN;
								boardselected = 1;
								pause = 4;
							}
						}
						if (turn == 1){
							if (P_two > 0){
								pieceselected = (PAWN | IS_WHITE);
								boardselected = 1;
								pause = 4;
							}
						}
					break;
					case 2:
						if (turn == 0){
							if (S_one > 0){
								pieceselected = SILVER;
								boardselected = 1;
								pause = 4;
							}
						}
						if (turn == 1){
							if (S_two > 0){
								pieceselected = (SILVER | IS_WHITE);
								boardselected = 1;
								pause = 4;
							}
						}
					break;
					case 3:
						if (turn == 0){
							if (G_one > 0){
								pieceselected = GOLD;
								boardselected = 1;
								pause = 4;
							}
						}
						if (turn == 1){
							if (G_two > 0){
								pieceselected = (GOLD | IS_WHITE);
								boardselected = 1;
								pause = 4;
							}
						}
					break;
					case 4:
						if (turn == 0){
							if (B_one > 0){
								pieceselected = BISHOP;
								boardselected = 1;
								pause = 4;
							}
						}
						if (turn == 1){
							if (B_two > 0){
								pieceselected = (BISHOP | IS_WHITE);
								boardselected = 1;
								pause = 4;
							}
						}
					break;
					case 5:
						if (turn == 0){
							if (R_one > 0){
								pieceselected = ROOK;
								boardselected = 1;
								pause = 4;
							}
						}
						if (turn == 1){
							if (R_two > 0){
								pieceselected = (ROOK | IS_WHITE);
								boardselected = 1;
								pause = 4;
							}
						}
					break;
				}
				joypressed = 1;
			}
			if ((joypad() & J_B)){
				boardselected = 0;
				pointersprite();
				pause = 0;
				selection = 1;
			}
			if ((joypad() & J_UP)){
				if (selection == 1){
					selection = 5;
				}
				else{
					selection -= 1;
				}
				joypressed = 1;
			}
			if ((joypad() & J_DOWN)){
				if (selection == 5){
					selection = 1;
				}
				else{
					selection += 1;
				}
				joypressed = 1;
			}
		}
		if (joypressed == 1){
			counter();
			dropselect();
		}
		break;
		case 4: //Place a captured piece
		if (joypressed == 0){
			if ((joypad() & J_A)){
				if (valid == 1){
					dropping();
				}
				else{
					boardselected = 0;
					pointersprite();
				}
				pause = 0;
				joypressed = 1;
			}
			if ((joypad() & J_B)){
				boardselected = 0;
				pointersprite();
				pause = 0;
				joypressed = 1;
			}
			if ((joypad() & J_UP)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointy == 0){
						pointy = 4;
					}
					else{
						pointy -= 1;
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_DOWN)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointy == 4){
						pointy = 0;
					}
					else{
						pointy += 1;
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_LEFT)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointx == 0){
						pointx = 4;
					}
					else{
						pointx -= 1;
					}
				}
				joypressed = 1;
			}
			if ((joypad() & J_RIGHT)){
				if ((turn == color & cpulevel != 0) || (cpulevel == 0)){
					if (pointx == 4){
						pointx = 0;
					}
					else{
						pointx += 1;
					}
				}
				joypressed = 1;
			}
		}
		if (joypressed == 1){
			counter();
			if (boardselected == 0){
				marker();
			}
			else{
				pointer();
			}
		}
		break;
		case 5: //Promotion animation
		for(uint8_t i = 0; i < 5; i++){
			switch(i){
				case 0:
					set_sprite_tile(0, 40);
					set_sprite_tile(1, 41);
					set_sprite_tile(2, 42);
					set_sprite_tile(3, 43);
					performantdelay(8);
				break;
				case 1:
					set_sprite_tile(0, 44);
					set_sprite_tile(1, 45);
					set_sprite_tile(2, 46);
					set_sprite_tile(3, 47);
					performantdelay(8);
				break;
				case 2:
					set_sprite_tile(0, 48);
					set_sprite_tile(1, 49);
					set_sprite_tile(2, 50);
					set_sprite_tile(3, 51);
					performantdelay(8);
				break;
				case 3:
					pointer();
					performantdelay(32);
				break;
				case 4:
					if (turn == 0){
						banked_set_bkg_data(170, 16, tanukihappy, 1);
						board[pointx + pointy * BOARD_W] = pieceselected;
						boardselected = 0;
						pointersprite();
						turn = 1;
					}
					else{
						banked_set_bkg_data(186, 16, kitsunehappy, 1);
						board[pointx + pointy * BOARD_W] = pieceselected;
						boardselected = 0;
						pointersprite();
						turn = 0;
					}
					pause = 0;
					marker();
				break;
			}
		}
		break;
	  }
	  if (frame < 32)
	  {
	     frame += 1;
	  }
	  if (frame >= 32)
	  {
	     frame = 0;
	  }
	  if (frame <= 1)
	  {
	     if (turn == 0)
		 {
			if (black_check == 0){
				banked_set_bkg_data(170, 16, tanukithink1, 1);
			}
			else{
				banked_set_bkg_data(170, 16, tanukisad, 1);
			}
		 }
		 if (turn == 1)
		 {
			if (white_check == 0){
				banked_set_bkg_data(186, 16, kitsunethink1, 1);
			}
			else{
				banked_set_bkg_data(186, 16, kitsunesad, 1);
			}
		 }
      }
	  if (frame == 16)
	  {
		 if (turn == 0)
		 {
			if (black_check == 0){
				banked_set_bkg_data(170, 16, tanukithink2, 1);
			}
			else{
				banked_set_bkg_data(170, 16, tanukisad, 1);
			}
		 }
		 if (turn == 1)
		 {
			if (white_check == 0){
				banked_set_bkg_data(186, 16, kitsunethink2, 1);
			}
			else{
				banked_set_bkg_data(186, 16, kitsunesad, 1);
			}
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
      if (pause == 1)
	  {
	     if (selection == 1)
	     {
	        gamestate = 1;
	     }
	  }
	  if (pause == 2)
	  {
	     gamestate = 7;
	  }
	  globalframe = 0;
   }
   if ((!(joypad() & J_UP)) & (!(joypad() & J_DOWN)) & (!(joypad() & J_LEFT)) & (!(joypad() & J_RIGHT)) & (!(joypad() & J_A)) & (!(joypad() & J_START)) & (!(joypad() & J_SELECT)))
   {
      joypressed = 0;
   }
}
