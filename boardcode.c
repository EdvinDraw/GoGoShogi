#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#pragma bank 5
#include "mastershogi.h"
#include "boardcode.h"
uint8_t board[BOARD_W * BOARD_H];
uint8_t pointx = 2;
uint8_t pointy = 2;
uint8_t pointx2 = 2;
uint8_t pointy2 = 2;
UINT8 drop = 0;
UINT8 frame = 0;
UINT8 valid = 0;
UINT8 boardselected = 0;
uint8_t pieceselected = EMPTY;

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

void initBoard(){
	static uint8_t const startingBoard[] =
	{
		ROOK | IS_WHITE, BISHOP | IS_WHITE, SILVER | IS_WHITE, GOLD | IS_WHITE, KING | IS_WHITE, 
		EMPTY, EMPTY, EMPTY, EMPTY, PAWN | IS_WHITE, 
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
		PAWN, EMPTY, EMPTY, EMPTY, EMPTY, 
		KING, GOLD, SILVER, BISHOP, ROOK, 
	};
	memcpy(board, startingBoard, sizeof(board));
}

bool boardselect(uint8_t x, uint8_t y){
	return board[x + y * BOARD_W];
}
bool isEmpty(uint8_t x, uint8_t y){
	return board[x + y * BOARD_W] == EMPTY;
}
bool isWhite(uint8_t x, uint8_t y){
	return board[x + y * BOARD_W] & IS_WHITE;
}
bool isBlack(uint8_t x, uint8_t y){
	return (board[x + y * BOARD_W] != EMPTY) && !isWhite(x, y);
}
bool checkWhite(){
	for(uint8_t x=0; x<BOARD_W; x++){
		for(uint8_t y=0; y<BOARD_H; y++) {
			if (board[x + y * BOARD_W] == (KING | IS_WHITE)){
				return 0;
			}
		}
	}
	return 1;
}
bool checkBlack(){
	for(uint8_t x=0; x<BOARD_W; x++){
		for(uint8_t y=0; y<BOARD_H; y++) {
			if (board[x + y * BOARD_W] == KING){
				return 0;
			}
		}
	}
	return 1;
}

void pointersprite() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 72);
	set_sprite_tile(1, 73);
	set_sprite_tile(2, 73);
	set_sprite_tile(3, 72);
	set_sprite_tile(4, 74);
	set_sprite_tile(5, 75);
	set_sprite_tile(6, 75);
	set_sprite_tile(7, 74);
	set_sprite_tile(8, 74);
	set_sprite_tile(9, 75);
	set_sprite_tile(10, 75);
	set_sprite_tile(11, 74);
	set_sprite_tile(12, 72);
	set_sprite_tile(13, 73);
	set_sprite_tile(14, 73);
	set_sprite_tile(15, 72);
	set_sprite_prop(0, 0x00 |S_PALETTE);
	set_sprite_prop(1, 0x00 |S_PALETTE);
	set_sprite_prop(2, S_FLIPX | 0x01 |S_PALETTE);
	set_sprite_prop(3, S_FLIPX | 0x01 |S_PALETTE);
	set_sprite_prop(4, 0x00 |S_PALETTE);
	set_sprite_prop(5, 0x00 |S_PALETTE);
	set_sprite_prop(6, S_FLIPX | 0x01 |S_PALETTE);
	set_sprite_prop(7, S_FLIPX | 0x01 |S_PALETTE);
	set_sprite_prop(8, S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(9, S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(10, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(11, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(12, S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(13, S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(14, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
	set_sprite_prop(15, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
	enable_interrupts();
}
void canceling() BANKED{
	board[pointx2 + pointy2 * BOARD_W] = pieceselected;
	pointx = pointx2;
	pointy = pointy2;
	boardselected = 0;
	pointersprite();
}
void pointerpawn() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 1);
	set_sprite_tile(2, 2);
	set_sprite_tile(3, 3);
	attacker = 1;
	enable_interrupts();
}
void pointersilver() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 4);
	set_sprite_tile(1, 5);
	set_sprite_tile(2, 6);
	set_sprite_tile(3, 7);
	attacker = 2;
	enable_interrupts();
}
void pointergold() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 8);
	set_sprite_tile(1, 9);
	set_sprite_tile(2, 10);
	set_sprite_tile(3, 11);
	attacker = 3;
	enable_interrupts();
}
void pointerbishop() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 12);
	set_sprite_tile(1, 13);
	set_sprite_tile(2, 14);
	set_sprite_tile(3, 15);
	attacker = 5;
	enable_interrupts();
}
void pointerrook() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 16);
	set_sprite_tile(1, 17);
	set_sprite_tile(2, 18);
	set_sprite_tile(3, 19);
	attacker = 4;
	enable_interrupts();
}
void pointerking() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 20);
	set_sprite_tile(1, 21);
	set_sprite_tile(2, 22);
	set_sprite_tile(3, 23);
	attacker = 6;
	enable_interrupts();
}
void pointerpawnplus() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 24);
	set_sprite_tile(1, 25);
	set_sprite_tile(2, 26);
	set_sprite_tile(3, 27);
	attacker = 1;
	enable_interrupts();
}
void pointersilverplus() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 28);
	set_sprite_tile(1, 29);
	set_sprite_tile(2, 30);
	set_sprite_tile(3, 31);
	attacker = 2;
	enable_interrupts();
}
void pointerbishopplus() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 32);
	set_sprite_tile(1, 33);
	set_sprite_tile(2, 34);
	set_sprite_tile(3, 35);
	attacker = 5;
	enable_interrupts();
}
void pointerrookplus() BANKED{
	disable_interrupts();
	set_sprite_tile(0, 36);
	set_sprite_tile(1, 37);
	set_sprite_tile(2, 38);
	set_sprite_tile(3, 39);
	attacker = 4;
	enable_interrupts();
}

void boardupdate(){
	if (pause == 4){
		if (pieceselected == PAWN){
			for(uint8_t d = 1; d < BOARD_W; d++){
				if ((pointy == 0) || (board[pointx + (pointy-1) * BOARD_W] == (KING | IS_WHITE)) || (board[pointx + (0+d) * BOARD_W] == PAWN) || (board[pointx + pointy * BOARD_W] != EMPTY)){
					if (valid == 1){
						valid = 0;
					}
					break;
				}
				else{
					if (valid == 0){
						valid = 1;
					}
				}
			}
		}
		else if (pieceselected == (PAWN | IS_WHITE)){
			for(uint8_t d = 1; d < BOARD_W; d++){
				if ((pointy == 4) || (board[pointx + (pointy+1) * BOARD_W] == KING) || (board[pointx + (0+d) * BOARD_W] == (PAWN | IS_WHITE)) || (board[pointx + pointy * BOARD_W] != EMPTY)){
					if (valid == 1){
						valid = 0;
					}
					break;
				}
				else{
					if (valid == 0){
						valid = 1;
					}
				}
			}
		}
		else{
			if (board[pointx + pointy * BOARD_W] == EMPTY){
				if (valid == 0){
					valid = 1;
				}
			}
			else{
				if (valid == 1){
					valid = 0;
				}
			}
		}
	}
	else{
		if ((pieceselected & TYPE_MASK) == PAWN){
			if (pieceselected & IS_WHITE) {
				if ((pointx == (pointx2)) && (pointy == (pointy2+1))){
					if (valid == 0){
						valid = 1;
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
			else{
				if ((pointx == (pointx2)) && (pointy == (pointy2-1))){
					if (valid == 0){
						valid = 1;
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
		}
		if ((pieceselected & TYPE_MASK) == SILVER){
			if (pieceselected & IS_WHITE) {
				if ( ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
					if (valid == 0){
						valid = 1;
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
			else{
				if ( ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
					if (valid == 0){
						valid = 1;
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
		}
		if ((pieceselected & TYPE_MASK) == ROOK){
			if (pieceselected & IS_WHITE) {
				bool search_U = true;
				bool search_D = true;
				bool search_L = true;
				bool search_R = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isWhite(pointx2, pointy2-a)) { search_U = false; }
					if (isWhite(pointx2, pointy2+a)) { search_D = false; }
					if (isWhite(pointx2-a, pointy2)) { search_L = false; }
					if (isWhite(pointx2+a, pointy2)) { search_R = false; }
					if ( (search_U && pointx == (pointx2) && pointy == (pointy2-a)) || (search_D && pointx == (pointx2) && pointy == (pointy2+a)) || (search_L && pointx == (pointx2-a) && pointy == (pointy2)) || (search_R && pointx == (pointx2+a) && pointy == (pointy2)) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2, pointy2-a)) { search_U = false; }
					if (!isEmpty(pointx2, pointy2+a)) { search_D = false; }
					if (!isEmpty(pointx2-a, pointy2)) { search_L = false; }
					if (!isEmpty(pointx2+a, pointy2)) { search_R = false; }
				}
			}
			else{
				bool search_U = true;
				bool search_D = true;
				bool search_L = true;
				bool search_R = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isBlack(pointx2, pointy2-a)) { search_U = false; }
					if (isBlack(pointx2, pointy2+a)) { search_D = false; }
					if (isBlack(pointx2-a, pointy2)) { search_L = false; }
					if (isBlack(pointx2+a, pointy2)) { search_R = false; }
					if ( (search_U && pointx == (pointx2) && pointy == (pointy2-a)) || (search_D && pointx == (pointx2) && pointy == (pointy2+a)) || (search_L && pointx == (pointx2-a) && pointy == (pointy2)) || (search_R && pointx == (pointx2+a) && pointy == (pointy2)) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2, pointy2-a)) { search_U = false; }
					if (!isEmpty(pointx2, pointy2-a)) { search_D = false; }
					if (!isEmpty(pointx2-a, pointy2)) { search_L = false; }
					if (!isEmpty(pointx2+a, pointy2)) { search_R = false; }
				}
			}
		}
		
		if ((pieceselected & TYPE_MASK) == BISHOP){
			if (pieceselected & IS_WHITE) {
				bool search_UL = true;
				bool search_UR = true;
				bool search_LL = true;
				bool search_LR = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isWhite(pointx2-a, pointy2-a)) { search_UL = false; }
					if (isWhite(pointx2+a, pointy2-a)) { search_UR = false; }
					if (isWhite(pointx2-a, pointy2+a)) { search_LL = false; }
					if (isWhite(pointx2+a, pointy2+a)) { search_LR = false; }
					if ( (search_UL && pointx == (pointx2-a) && pointy == (pointy2-a)) || (search_UR && pointx == (pointx2+a) && pointy == (pointy2-a)) || (search_LL && pointx == (pointx2-a) && pointy == (pointy2+a)) || (search_LR && pointx == (pointx2+a) && pointy == (pointy2+a)) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2-a, pointy2-a)) { search_UL = false; }
					if (!isEmpty(pointx2+a, pointy2-a)) { search_UR = false; }
					if (!isEmpty(pointx2-a, pointy2+a)) { search_LL = false; }
					if (!isEmpty(pointx2+a, pointy2+a)) { search_LR = false; }
				}
			}
			else{
				bool search_UL = true;
				bool search_UR = true;
				bool search_LL = true;
				bool search_LR = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isBlack(pointx2-a, pointy2-a)) { search_UL = false; }
					if (isBlack(pointx2+a, pointy2-a)) { search_UR = false; }
					if (isBlack(pointx2-a, pointy2+a)) { search_LL = false; }
					if (isBlack(pointx2+a, pointy2+a)) { search_LR = false; }
					if ( (search_UL && pointx == (pointx2-a) && pointy == (pointy2-a)) || (search_UR && pointx == (pointx2+a) && pointy == (pointy2-a)) || (search_LL && pointx == (pointx2-a) && pointy == (pointy2+a)) || (search_LR && pointx == (pointx2+a) && pointy == (pointy2+a)) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2-a, pointy2-a)) { search_UL = false; }
					if (!isEmpty(pointx2+a, pointy2-a)) { search_UR = false; }
					if (!isEmpty(pointx2-a, pointy2+a)) { search_LL = false; }
					if (!isEmpty(pointx2+a, pointy2+a)) { search_LR = false; }
				}
			}
		}
		if ((pieceselected & TYPE_MASK) == KING){
			if (pieceselected & IS_WHITE) {
				if ( ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2))) || ((pointx == (pointx2+1)) && (pointy == (pointy2))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
					if (((board[pointx + pointy * BOARD_W] & THREAT) == BLACK) || ((board[pointx + pointy * BOARD_W] & THREAT) == BLACKNWHITE)){
						if (valid == 1){
							valid = 0;
						}
					}
					else{
						if (valid == 0){
							valid = 1;
						}
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
			else{
				if ( ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2))) || ((pointx == (pointx2+1)) && (pointy == (pointy2))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
					if (((board[pointx + pointy * BOARD_W] & THREAT) == WHITE) || ((board[pointx + pointy * BOARD_W] & THREAT) == BLACKNWHITE)){
						if (valid == 1){
							valid = 0;
						}
					}
					else{
						if (valid == 0){
							valid = 1;
						}
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
		}
		if (((pieceselected & TYPE_MASK) == GOLD) || ((pieceselected & TYPE_MASK) == PAWNPLUS) || ((pieceselected & TYPE_MASK) == SILVERPLUS)){
			if (pieceselected & IS_WHITE) {
				if ( ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2))) || ((pointx == (pointx2+1)) && (pointy == (pointy2))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
					if (valid == 0){
						valid = 1;
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
			else{
				if ( ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2))) || ((pointx == (pointx2+1)) && (pointy == (pointy2))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) ){
					if (valid == 0){
						valid = 1;
					}
				}
				else{
					if (valid == 1){
						valid = 0;
					}
				}
			}
		}
		if ((pieceselected & TYPE_MASK) == ROOKPLUS){
			if (pieceselected & IS_WHITE) {
				bool search_U = true;
				bool search_D = true;
				bool search_L = true;
				bool search_R = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isWhite(pointx2, pointy2-a)) { search_U = false; }
					if (isWhite(pointx2, pointy2+a)) { search_D = false; }
					if (isWhite(pointx2-a, pointy2)) { search_L = false; }
					if (isWhite(pointx2+a, pointy2)) { search_R = false; }
					if ( (search_U && pointx == (pointx2) && pointy == (pointy2-a)) || (search_D && pointx == (pointx2) && pointy == (pointy2+a)) || (search_L && pointx == (pointx2-a) && pointy == (pointy2)) || (search_R && pointx == (pointx2+a) && pointy == (pointy2)) || ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2, pointy2-a)) { search_U = false; }
					if (!isEmpty(pointx2, pointy2+a)) { search_D = false; }
					if (!isEmpty(pointx2-a, pointy2)) { search_L = false; }
					if (!isEmpty(pointx2+a, pointy2)) { search_R = false; }
				}
			}
			else{
				bool search_U = true;
				bool search_D = true;
				bool search_L = true;
				bool search_R = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isBlack(pointx2, pointy2-a)) { search_U = false; }
					if (isBlack(pointx2, pointy2+a)) { search_D = false; }
					if (isBlack(pointx2-a, pointy2)) { search_L = false; }
					if (isBlack(pointx2+a, pointy2)) { search_R = false; }
					if ( (search_U && pointx == (pointx2) && pointy == (pointy2-a)) || (search_D && pointx == (pointx2) && pointy == (pointy2+a)) || (search_L && pointx == (pointx2-a) && pointy == (pointy2)) || (search_R && pointx == (pointx2+a) && pointy == (pointy2)) || ((pointx == (pointx2-1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2-1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2+1))) || ((pointx == (pointx2+1)) && (pointy == (pointy2+1))) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2, pointy2-a)) { search_U = false; }
					if (!isEmpty(pointx2, pointy2+a)) { search_D = false; }
					if (!isEmpty(pointx2-a, pointy2)) { search_L = false; }
					if (!isEmpty(pointx2+a, pointy2)) { search_R = false; }
				}
			}
		}
		if ((pieceselected & TYPE_MASK) == BISHOPPLUS){
			if (pieceselected & IS_WHITE) {
				bool search_UL = true;
				bool search_UR = true;
				bool search_LL = true;
				bool search_LR = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isWhite(pointx2-a, pointy2-a)) { search_UL = false; }
					if (isWhite(pointx2+a, pointy2-a)) { search_UR = false; }
					if (isWhite(pointx2-a, pointy2+a)) { search_LL = false; }
					if (isWhite(pointx2+a, pointy2+a)) { search_LR = false; }
					if ( (search_UL && pointx == (pointx2-a) && pointy == (pointy2-a)) || (search_UR && pointx == (pointx2+a) && pointy == (pointy2-a)) || (search_LL && pointx == (pointx2-a) && pointy == (pointy2+a)) || (search_LR && pointx == (pointx2+a) && pointy == (pointy2+a)) || ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2))) || ((pointx == (pointx2+1)) && (pointy == (pointy2))) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2-a, pointy2-a)) { search_UL = false; }
					if (!isEmpty(pointx2-a, pointy2+a)) { search_UR = false; }
					if (!isEmpty(pointx2+a, pointy2-a)) { search_LL = false; }
					if (!isEmpty(pointx2+a, pointy2+a)) { search_LR = false; }
				}
			}
			else{
				bool search_UL = true;
				bool search_UR = true;
				bool search_LL = true;
				bool search_LR = true;
				for(uint8_t a = 1; a < BOARD_W; a++){
					if (isBlack(pointx2-a, pointy2-a)) { search_UL = false; }
					if (isBlack(pointx2+a, pointy2-a)) { search_UR = false; }
					if (isBlack(pointx2-a, pointy2+a)) { search_LL = false; }
					if (isBlack(pointx2+a, pointy2+a)) { search_LR = false; }
					if ( (search_UL && pointx == (pointx2-a) && pointy == (pointy2-a)) || (search_UR && pointx == (pointx2+a) && pointy == (pointy2-a)) || (search_LL && pointx == (pointx2-a) && pointy == (pointy2+a)) || (search_LR && pointx == (pointx2+a) && pointy == (pointy2+a)) || ((pointx == (pointx2)) && (pointy == (pointy2-1))) || ((pointx == (pointx2)) && (pointy == (pointy2+1))) || ((pointx == (pointx2-1)) && (pointy == (pointy2))) || ((pointx == (pointx2+1)) && (pointy == (pointy2))) ){
						if (valid == 0){
							valid = 1;
						}
						break;
					}
					else {
						if (valid == 1){
							valid = 0;
						}
					}
					if (!isEmpty(pointx2-a, pointy2-a)) { search_UL = false; }
					if (!isEmpty(pointx2+a, pointy2-a)) { search_UR = false; }
					if (!isEmpty(pointx2-a, pointy2+a)) { search_LL = false; }
					if (!isEmpty(pointx2+a, pointy2+a)) { search_LR = false; }
				}
			}
		}
	}
	
	for(uint8_t x=0; x<BOARD_W; x++){
		for(uint8_t y=0; y<BOARD_H; y++) {
			if ((board[x + y * BOARD_W] & TYPE_MASK) == EMPTY){
				set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, empty_square);
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == PAWN){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_pawn);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_pawn);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == PAWNPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_pawnP);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_pawnP);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == SILVER){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_silver);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_silver);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == SILVERPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_silverP);
				}
				else{
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_silverP);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == GOLD){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_gold);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_gold);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == ROOK){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_rook);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_rook);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == ROOKPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_rookP);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_rookP);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == BISHOP){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_bishop);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_bishop);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == BISHOPPLUS){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_bishopP);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_bishopP);
				}
			}
			if ((board[x + y * BOARD_W] & TYPE_MASK) == KING){
				if (board[x + y * BOARD_W] & IS_WHITE) {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, white_king);
				}
				else {
					set_bkg_tiles(x*2+FIVE, y*2+ICHI, 2, 2, black_king);
				}
			}
		}
	}
}

void tablet(int status) BANKED{
	switch(status){
		case 0:
			move_sprite(16, 190, 174);
			if (cpulevel == 0){
				if (turn == 0){
					set_bkg_tiles(6, 1, 8, 4, player1sturn);
				}
				else{
					set_bkg_tiles(6, 1, 8, 4, player2sturn);
				}
			}
			if (cpulevel > 0){
				if (turn == color){
					set_bkg_tiles(6, 1, 8, 4, yourturn);
				}
				else{
					if (color == 0){
						set_bkg_tiles(6, 1, 8, 4, whitesturn);
					}
					else{
						set_bkg_tiles(6, 1, 8, 4, blacksturn);
					}
				}
			}
		break;
		case 1:
			set_bkg_tiles(6, 1, 8, 4, giveup);
			set_sprite_tile(16, 76);
			set_sprite_prop(16, 0x00|S_PALETTE);
			move_sprite(16, 64, 40);
		break;
		case 2:
			set_bkg_tiles(6, 1, 8, 4, promote);
			set_sprite_tile(16, 76);
			set_sprite_prop(16, 0x00|S_PALETTE);
			move_sprite(16, 64, 40);
		break;
		case 3:
			set_bkg_tiles(6, 1, 8, 4, capturedarea);
			set_sprite_tile(16, 76);
			set_sprite_prop(16, 0x00|S_PALETTE);
		break;
	}
}
void giving_up() BANKED{
	selection = 1;
	pause = 1;
	set_bkg_tiles(6, 1, 8, 4, giveup);
	set_sprite_tile(16, 76);
	set_sprite_prop(16, 0x00|S_PALETTE);
}