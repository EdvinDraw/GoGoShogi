#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#pragma bank 9
#include "mastershogi.h"
#include "boardcode.h"

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

void goldupdate() BANKED{
	for(uint8_t x=1; x<6; x++){
		for(uint8_t y=1; y<6; y++){
			
			if (board[x + y * BOARD_W] == (GOLD | IS_WHITE)){
				whitethreat[(x) + (y-1) * BOARD_W] = 1;
				whitethreat[(x-1) + (y) * BOARD_W] = 1;
				whitethreat[(x+1) + (y) * BOARD_W] = 1;
				whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
				whitethreat[(x) + (y+1) * BOARD_W] = 1;
				whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
			}
			else if (board[x + y * BOARD_W] == (GOLD)){
				blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
				blackthreat[(x) + (y-1) * BOARD_W] = 1;
				blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
				blackthreat[(x-1) + (y) * BOARD_W] = 1;
				blackthreat[(x+1) + (y) * BOARD_W] = 1;
				blackthreat[(x) + (y+1) * BOARD_W] = 1;
			}
		}
	}
}