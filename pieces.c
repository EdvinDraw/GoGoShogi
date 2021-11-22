#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#pragma bank 10
#include "mastershogi.h"
#include "pieces.h"
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

void boardupdate2() BANKED{
	for(uint8_t x=1; x<6; x++){
		for(uint8_t y=1; y<6; y++){
			
			if (turn == 0){
				if (blackthreat[(x) + (y) * BOARD_W] == 0){
					set_bkg_tiles(0+x, 0+y, 1, 1, falsevalid);
				}
				else if (blackthreat[(x) + (y) * BOARD_W] == 1){
					set_bkg_tiles(0+x, 0+y, 1, 1, truevalid);
				}
				else if (blackthreat[(x) + (y) * BOARD_W] == 2){
					set_bkg_tiles(0+x, 0+y, 1, 1, twovalid);
				}
			}
			else if (turn == 1){
				if (whitethreat[(x) + (y) * BOARD_W] == 0){
					set_bkg_tiles(0+x, 0+y, 1, 1, falsevalid);
				}
				else if (whitethreat[(x) + (y) * BOARD_W] == 1){
					set_bkg_tiles(0+x, 0+y, 1, 1, truevalid);
				}
				else if (whitethreat[(x) + (y) * BOARD_W] == 2){
					set_bkg_tiles(0+x, 0+y, 1, 1, twovalid);
				}
			}
			
			if ((board[x + y * BOARD_W] & TYPE_MASK) == EMPTY){
				set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, empty_square);
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == PAWN){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_pawn);
				}
				else {
					if (boardselected == 0){
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_pawn);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == PAWNPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						whitethreat[(x) + (y-1) * BOARD_W] = 1;
						whitethreat[(x-1) + (y) * BOARD_W] = 1;
						whitethreat[(x+1) + (y) * BOARD_W] = 1;
						whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_pawnP);
				}
				else {
					if (boardselected == 0){
						blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x-1) + (y) * BOARD_W] = 1;
						blackthreat[(x+1) + (y) * BOARD_W] = 1;
						blackthreat[(x) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_pawnP);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == SILVER){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						whitethreat[(x-1) + (y-1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y-1) * BOARD_W] = 1;
						whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_silver);
				}
				else {
					if (boardselected == 0){
						blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x-1) + (y+1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_silver);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == SILVERPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						whitethreat[(x) + (y-1) * BOARD_W] = 1;
						whitethreat[(x-1) + (y) * BOARD_W] = 1;
						whitethreat[(x+1) + (y) * BOARD_W] = 1;
						whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_silverP);
				}
				else{
					if (boardselected == 0){
						blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x-1) + (y) * BOARD_W] = 1;
						blackthreat[(x+1) + (y) * BOARD_W] = 1;
						blackthreat[(x) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_silverP);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == GOLD){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						whitethreat[(x) + (y-1) * BOARD_W] = 1;
						whitethreat[(x-1) + (y) * BOARD_W] = 1;
						whitethreat[(x+1) + (y) * BOARD_W] = 1;
						whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_gold);
				}
				else {
					if (boardselected == 0){
						blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x-1) + (y) * BOARD_W] = 1;
						blackthreat[(x+1) + (y) * BOARD_W] = 1;
						blackthreat[(x) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_gold);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == ROOK){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
					bool upthreat = false;
					bool downthreat = false;
					bool leftthreat = false;
					bool rightthreat = false;
					for(uint8_t a = 1; a < y; a++){
						if (upthreat == false){
							if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) || (board[(x) + (y-a) * BOARD_W] == (KING)) ){
								whitethreat[(x) + (y-a) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y-a) * BOARD_W] != EMPTY) && (board[(x) + (y-a) * BOARD_W] != (KING)) ){
								whitethreat[(x) + (y-a) * BOARD_W] = 1;
								upthreat = true;
							}
						}
						else if (upthreat == true){
							if (board[(x) + (y-a) * BOARD_W] == EMPTY){
								whitethreat[(x) + (y-a) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t b = 1; b < 5; b++){
						if (downthreat == false){
							if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) || (board[(x) + (y+b) * BOARD_W] == (KING)) ){
								whitethreat[(x) + (y+b) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y+b) * BOARD_W] != EMPTY) && (board[(x) + (y+b) * BOARD_W] != (KING)) ){
								whitethreat[(x) + (y+b) * BOARD_W] = 1;
								downthreat = true;
							}
						}
						else if (downthreat == true){
							if (board[(x) + (y+b) * BOARD_W] == EMPTY){
								whitethreat[(x) + (y+b) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t c = 1; c < x; c++){
						if (leftthreat == false){
							if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) || (board[(x-c) + (y) * BOARD_W] == (KING)) ){
								whitethreat[(x-c) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x-c) + (y) * BOARD_W] != EMPTY) && (board[(x-c) + (y) * BOARD_W] != (KING)) ){
								whitethreat[(x-c) + (y) * BOARD_W] = 1;
								leftthreat = true;
							}
						}
						else if (leftthreat == true){
							if (board[(x-c) + (y) * BOARD_W] == EMPTY){
								whitethreat[(x-c) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t d = 1; d < 5; d++){
						if (rightthreat == false){
							if ( (board[(x+d) + (y) * BOARD_W] == EMPTY) || (board[(x+d) + (y) * BOARD_W] == (KING)) ){
								whitethreat[(x+d) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x+d) + (y) * BOARD_W] != EMPTY) && (board[(x+d) + (y) * BOARD_W] != (KING)) ){
								whitethreat[(x+d) + (y) * BOARD_W] = 1;
								rightthreat = true;
							}
						}
						else if (rightthreat == true){
							if (board[(x+d) + (y) * BOARD_W] == EMPTY){
								whitethreat[(x+d) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_rook);
				}
				else {
					if (boardselected == 0){
					bool upthreat = false;
					bool downthreat = false;
					bool leftthreat = false;
					bool rightthreat = false;
					for(uint8_t a = 1; a < y; a++){
						if (upthreat == false){
							if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) || (board[(x) + (y-a) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x) + (y-a) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y-a) * BOARD_W] != EMPTY) && (board[(x) + (y-a) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x) + (y-a) * BOARD_W] = 1;
								upthreat = true;
							}
						}
						else if (upthreat == true){
							if (board[(x) + (y-a) * BOARD_W] == EMPTY){
								blackthreat[(x) + (y-a) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t b = 1; b < 5; b++){
						if (downthreat == false){
							if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) || (board[(x) + (y+b) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x) + (y+b) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y+b) * BOARD_W] != EMPTY) && (board[(x) + (y+b) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x) + (y+b) * BOARD_W] = 1;
								downthreat = true;
							}
						}
						else if (downthreat == true){
							if (board[(x) + (y+b) * BOARD_W] == EMPTY){
								blackthreat[(x) + (y+b) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t c = 1; c < x; c++){
						if (leftthreat == false){
							if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) || (board[(x-c) + (y) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x-c) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x-c) + (y) * BOARD_W] != EMPTY) && (board[(x-c) + (y) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x-c) + (y) * BOARD_W] = 1;
								leftthreat = true;
							}
						}
						else if (leftthreat == true){
							if (board[(x-c) + (y) * BOARD_W] == EMPTY){
								blackthreat[(x-c) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t d = 1; d < 5; d++){
						if (rightthreat == false){
							if ( (board[(x+d) + (y) * BOARD_W] == EMPTY) || (board[(x+d) + (y) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x+d) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x+d) + (y) * BOARD_W] != EMPTY) && (board[(x+d) + (y) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x+d) + (y) * BOARD_W] = 1;
								rightthreat = true;
							}
						}
						else if (rightthreat == true){
							if (board[(x+d) + (y) * BOARD_W] == EMPTY){
								blackthreat[(x+d) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_rook);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == ROOKPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
					bool upthreat = false;
					bool downthreat = false;
					bool leftthreat = false;
					bool rightthreat = false;
					for(uint8_t a = 1; a < y; a++){
						if (upthreat == false){
							if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) || (board[(x) + (y-a) * BOARD_W] == (KING)) ){
								whitethreat[(x) + (y-a) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y-a) * BOARD_W] != EMPTY) && (board[(x) + (y-a) * BOARD_W] != (KING)) ){
								whitethreat[(x) + (y-a) * BOARD_W] = 1;
								upthreat = true;
							}
						}
						else if (upthreat == true){
							if (board[(x) + (y-a) * BOARD_W] == EMPTY){
								whitethreat[(x) + (y-a) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t b = 1; b < 5; b++){
						if (downthreat == false){
							if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) || (board[(x) + (y+b) * BOARD_W] == (KING)) ){
								whitethreat[(x) + (y+b) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y+b) * BOARD_W] != EMPTY) && (board[(x) + (y+b) * BOARD_W] != (KING)) ){
								whitethreat[(x) + (y+b) * BOARD_W] = 1;
								downthreat = true;
							}
						}
						else if (downthreat == true){
							if (board[(x) + (y+b) * BOARD_W] == EMPTY){
								whitethreat[(x) + (y+b) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t c = 1; c < x; c++){
						if (leftthreat == false){
							if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) || (board[(x-c) + (y) * BOARD_W] == (KING)) ){
								whitethreat[(x-c) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x-c) + (y) * BOARD_W] != EMPTY) && (board[(x-c) + (y) * BOARD_W] != (KING)) ){
								whitethreat[(x-c) + (y) * BOARD_W] = 1;
								leftthreat = true;
							}
						}
						else if (leftthreat == true){
							if (board[(x-c) + (y) * BOARD_W] == EMPTY){
								whitethreat[(x-c) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t d = 1; d < 5; d++){
						if (rightthreat == false){
							if ( (board[(x+d) + (y) * BOARD_W] == EMPTY) || (board[(x+d) + (y) * BOARD_W] == (KING)) ){
								whitethreat[(x+d) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x+d) + (y) * BOARD_W] != EMPTY) && (board[(x+d) + (y) * BOARD_W] != (KING)) ){
								whitethreat[(x+d) + (y) * BOARD_W] = 1;
								rightthreat = true;
							}
						}
						else if (rightthreat == true){
							if (board[(x+d) + (y) * BOARD_W] == EMPTY){
								whitethreat[(x+d) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					whitethreat[(x-1) + (y-1) * BOARD_W] = 1;
					whitethreat[(x+1) + (y-1) * BOARD_W] = 1;
					whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
					whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_rookP);
				}
				else {
					if (boardselected == 0){
					bool upthreat = false;
					bool downthreat = false;
					bool leftthreat = false;
					bool rightthreat = false;
					for(uint8_t a = 1; a < y; a++){
						if (upthreat == false){
							if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) || (board[(x) + (y-a) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x) + (y-a) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y-a) * BOARD_W] != EMPTY) && (board[(x) + (y-a) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x) + (y-a) * BOARD_W] = 1;
								upthreat = true;
							}
						}
						else if (upthreat == true){
							if (board[(x) + (y-a) * BOARD_W] == EMPTY){
								blackthreat[(x) + (y-a) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t b = 1; b < 5; b++){
						if (downthreat == false){
							if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) || (board[(x) + (y+b) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x) + (y+b) * BOARD_W] = 1;
							}
							else if ( (board[(x) + (y+b) * BOARD_W] != EMPTY) && (board[(x) + (y+b) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x) + (y+b) * BOARD_W] = 1;
								downthreat = true;
							}
						}
						else if (downthreat == true){
							if (board[(x) + (y+b) * BOARD_W] == EMPTY){
								blackthreat[(x) + (y+b) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t c = 1; c < x; c++){
						if (leftthreat == false){
							if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) || (board[(x-c) + (y) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x-c) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x-c) + (y) * BOARD_W] != EMPTY) && (board[(x-c) + (y) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x-c) + (y) * BOARD_W] = 1;
								leftthreat = true;
							}
						}
						else if (leftthreat == true){
							if (board[(x-c) + (y) * BOARD_W] == EMPTY){
								blackthreat[(x-c) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					for(uint8_t d = 1; d < 5; d++){
						if (rightthreat == false){
							if ( (board[(x+d) + (y) * BOARD_W] == EMPTY) || (board[(x+d) + (y) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x+d) + (y) * BOARD_W] = 1;
							}
							else if ( (board[(x+d) + (y) * BOARD_W] != EMPTY) && (board[(x+d) + (y) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x+d) + (y) * BOARD_W] = 1;
								rightthreat = true;
							}
						}
						else if (rightthreat == true){
							if (board[(x+d) + (y) * BOARD_W] == EMPTY){
								blackthreat[(x+d) + (y) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
					blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
					blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
					blackthreat[(x-1) + (y+1) * BOARD_W] = 1;
					blackthreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_rookP);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == BISHOP){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						bool upleftthreat = false;
						bool uprightthreat = false;
						bool downleftthreat = false;
						bool downrightthreat = false;
						for(uint8_t a = 1; a < x; a++){
							for(uint8_t b = 1; b < y; b++){
								if (upleftthreat == false){
									if ( (board[(x-a) + (y-a) * BOARD_W] == EMPTY) || (board[(x-a) + (y-b) * BOARD_W] == (KING)) ){
										whitethreat[(x-a) + (y-b) * BOARD_W] = 1;
									}
									else if ( (board[(x-a) + (y-b) * BOARD_W] != EMPTY) && (board[(x-a) + (y-b) * BOARD_W] != (KING)) ){
										whitethreat[(x-a) + (y-b) * BOARD_W] = 1;
										upleftthreat = true;
									}
								}
								else if (upleftthreat == true){
									if (board[(x-a) + (y-b) * BOARD_W] == EMPTY){
										whitethreat[(x-a) + (y-b) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
							for(uint8_t c = 1; c < 5; c++){
								if (downleftthreat == false){
									if ( (board[(x-a) + (y+c) * BOARD_W] == EMPTY) || (board[(x-a) + (y+c) * BOARD_W] == (KING)) ){
										whitethreat[(x-a) + (y+c) * BOARD_W] = 1;
									}
									else if ( (board[(x-a) + (y+c) * BOARD_W] != EMPTY) && (board[(x-a) + (y+c) * BOARD_W] != (KING)) ){
										whitethreat[(x-a) + (y+c) * BOARD_W] = 1;
										downleftthreat = true;
									}
								}
								else if (downleftthreat == true){
									if (board[(x-a) + (y+c) * BOARD_W] == EMPTY){
										whitethreat[(x-a) + (y+c) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
						}
						for(uint8_t d = 1; d < 5; d++){
							for(uint8_t e = 1; e < y; e++){
								if (uprightthreat == false){
									if ( (board[(x+d) + (y-e) * BOARD_W] == EMPTY) || (board[(x+d) + (y-e) * BOARD_W] == (KING)) ){
										whitethreat[(x+d) + (y-e) * BOARD_W] = 1;
									}
									else if ( (board[(x+d) + (y-e) * BOARD_W] != EMPTY) && (board[(x+d) + (y-e) * BOARD_W] != (KING)) ){
										whitethreat[(x+d) + (y-e) * BOARD_W] = 1;
										uprightthreat = true;
									}
								}
								else if (uprightthreat == true){
									if (board[(x+d) + (y-e) * BOARD_W] == EMPTY){
										whitethreat[(x+d) + (y-e) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
							for(uint8_t f = 1; f < 5; f++){
								if (downrightthreat == false){
									if ( (board[(x+d) + (y+f) * BOARD_W] == EMPTY) || (board[(x+d) + (y+f) * BOARD_W] == (KING)) ){
										whitethreat[(x+d) + (y+f) * BOARD_W] = 1;
									}
									else if ( (board[(x+d) + (y+f) * BOARD_W] != EMPTY) && (board[(x+d) + (y+f) * BOARD_W] != (KING)) ){
										whitethreat[(x+d) + (y+f) * BOARD_W] = 1;
										downrightthreat = true;
									}
								}
								else if (downrightthreat == true){
									if (board[(x+d) + (y+f) * BOARD_W] == EMPTY){
										whitethreat[(x+d) + (y+f) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
						}
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_bishop);
				}
				else {
					if (boardselected == 0){
						bool upleftthreat = false;
						bool uprightthreat = false;
						bool downleftthreat = false;
						bool downrightthreat = false;
						for(uint8_t a = 1; a < x; a++){
							for(uint8_t b = 1; b < y; b++){
								if (upleftthreat == false){
									if ( (board[(x-a) + (y-a) * BOARD_W] == EMPTY) || (board[(x-a) + (y-b) * BOARD_W] == (KING | IS_WHITE)) ){
										whitethreat[(x-a) + (y-b) * BOARD_W] = 1;
									}
									else if ( (board[(x-a) + (y-b) * BOARD_W] != EMPTY) && (board[(x-a) + (y-b) * BOARD_W] != (KING | IS_WHITE)) ){
										whitethreat[(x-a) + (y-b) * BOARD_W] = 1;
										upleftthreat = true;
									}
								}
								else if (upleftthreat == true){
									if (board[(x-a) + (y-b) * BOARD_W] == EMPTY){
										whitethreat[(x-a) + (y-b) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
							for(uint8_t c = 1; c < 5; c++){
								if (downleftthreat == false){
									if ( (board[(x-a) + (y+c) * BOARD_W] == EMPTY) || (board[(x-a) + (y+c) * BOARD_W] == (KING | IS_WHITE)) ){
										whitethreat[(x-a) + (y+c) * BOARD_W] = 1;
									}
									else if ( (board[(x-a) + (y+c) * BOARD_W] != EMPTY) && (board[(x-a) + (y+c) * BOARD_W] != (KING | IS_WHITE)) ){
										whitethreat[(x-a) + (y+c) * BOARD_W] = 1;
										downleftthreat = true;
									}
								}
								else if (downleftthreat == true){
									if (board[(x-a) + (y+c) * BOARD_W] == EMPTY){
										whitethreat[(x-a) + (y+c) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
						}
						for(uint8_t d = 1; d < 5; d++){
							for(uint8_t e = 1; e < y; e++){
								if (uprightthreat == false){
									if ( (board[(x+d) + (y-e) * BOARD_W] == EMPTY) || (board[(x+d) + (y-e) * BOARD_W] == (KING | IS_WHITE)) ){
										whitethreat[(x+d) + (y-e) * BOARD_W] = 1;
									}
									else if ( (board[(x+d) + (y-e) * BOARD_W] != EMPTY) && (board[(x+d) + (y-e) * BOARD_W] != (KING | IS_WHITE)) ){
										whitethreat[(x+d) + (y-e) * BOARD_W] = 1;
										uprightthreat = true;
									}
								}
								else if (uprightthreat == true){
									if (board[(x+d) + (y-e) * BOARD_W] == EMPTY){
										whitethreat[(x+d) + (y-e) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
							for(uint8_t f = 1; f < 5; f++){
								if (downrightthreat == false){
									if ( (board[(x+d) + (y+f) * BOARD_W] == EMPTY) || (board[(x+d) + (y+f) * BOARD_W] == (KING | IS_WHITE)) ){
										whitethreat[(x+d) + (y+f) * BOARD_W] = 1;
									}
									else if ( (board[(x+d) + (y+f) * BOARD_W] != EMPTY) && (board[(x+d) + (y+f) * BOARD_W] != (KING | IS_WHITE)) ){
										whitethreat[(x+d) + (y+f) * BOARD_W] = 1;
										downrightthreat = true;
									}
								}
								else if (downrightthreat == true){
									if (board[(x+d) + (y+f) * BOARD_W] == EMPTY){
										whitethreat[(x+d) + (y+f) * BOARD_W] = 2;
									}
									else{
										break;
									}
								}
							}
						}
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_bishop);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == BISHOPPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (boardselected == 0){
						bool upperleftrow = 1;
						bool upperrightrow = 1;
						bool lowerleftrow = 1;
						bool lowerrightrow = 1;
						whitethreat[(x) + (y-1) * BOARD_W] = 1;
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
						whitethreat[(x-1) + (y) * BOARD_W] = 1;
						whitethreat[(x+1) + (y) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_bishopP);
				}
				else {
					if (boardselected == 0){
						bool upperleftrow = 1;
						bool upperrightrow = 1;
						bool lowerleftrow = 1;
						bool lowerrightrow = 1;
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
						blackthreat[(x) + (y+1) * BOARD_W] = 1;
						blackthreat[(x-1) + (y) * BOARD_W] = 1;
						blackthreat[(x+1) + (y) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_bishopP);
				}
			}
			else if ((board[x + y * BOARD_W] & TYPE_MASK) == KING){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					if (blackthreat[x + y * BOARD_W] == 1){
						if (white_check == 0){
							white_check = 1;
						}
					}
					else if (blackthreat[x + y * BOARD_W] != 1){
						if (white_check == 1){
							white_check = 0;
						}
					}
					
					if (boardselected == 0){
						whitethreat[(x-1) + (y-1) * BOARD_W] = 1;
						whitethreat[(x) + (y-1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y-1) * BOARD_W] = 1;
						whitethreat[(x-1) + (y) * BOARD_W] = 1;
						whitethreat[(x+1) + (y) * BOARD_W] = 1;
						whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
						whitethreat[(x) + (y+1) * BOARD_W] = 1;
						whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, white_king);
				}
				else {
					if (whitethreat[x + y * BOARD_W] == 1){
						if (black_check == 0){
							black_check = 1;
						}
					}
					else if (whitethreat[x + y * BOARD_W] != 1){
						if (black_check == 1){
							black_check = 0;
						}
					}
					
					if (boardselected == 0){
						blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x) + (y-1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
						blackthreat[(x-1) + (y) * BOARD_W] = 1;
						blackthreat[(x+1) + (y) * BOARD_W] = 1;
						blackthreat[(x-1) + (y+1) * BOARD_W] = 1;
						blackthreat[(x) + (y+1) * BOARD_W] = 1;
						blackthreat[(x+1) + (y+1) * BOARD_W] = 1;
					}
					set_bkg_tiles(x*2+SIX, y*2+ZERO, 2, 2, black_king);
				}
			}
		}
	}
}