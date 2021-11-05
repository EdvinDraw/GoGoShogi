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
void counter() BANKED{
	if (cpulevel == 0){
		set_bkg_tiles(1, 6, 2, 1, playerone);
		set_bkg_tiles(17, 6, 2, 1, playertwo);
	}
	else{
		if (color == 0){
			set_bkg_tiles(1, 6, 2, 1, playerone);
			set_bkg_tiles(17, 6, 2, 1, computerplayer);
		}
		else{
			set_bkg_tiles(1, 6, 2, 1, computerplayer);
			set_bkg_tiles(17, 6, 2, 1, playerone);
		}
	}
	switch(P_one){
		case 0:
		set_bkg_tiles(3, 7, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(3, 7, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(3, 7, 1, 2, twocount);
		break;
	}
	switch(S_one){
		case 0:
		set_bkg_tiles(3, 9, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(3, 9, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(3, 9, 1, 2, twocount);
		break;
	}
	switch(G_one){
		case 0:
		set_bkg_tiles(3, 11, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(3, 11, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(3, 11, 1, 2, twocount);
		break;
	}
	switch(B_one){
		case 0:
		set_bkg_tiles(3, 13, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(3, 13, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(3, 13, 1, 2, twocount);
		break;
	}
	switch(R_one){
		case 0:
		set_bkg_tiles(3, 15, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(3, 15, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(3, 15, 1, 2, twocount);
		break;
	}
	switch(P_two){
		case 0:
		set_bkg_tiles(16, 7, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(16, 7, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(16, 7, 1, 2, twocount);
		break;
	}
	switch(S_two){
		case 0:
		set_bkg_tiles(16, 9, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(16, 9, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(16, 9, 1, 2, twocount);
		break;
	}
	switch(G_two){
		case 0:
		set_bkg_tiles(16, 11, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(16, 11, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(16, 11, 1, 2, twocount);
		break;
	}
	switch(B_two){
		case 0:
		set_bkg_tiles(16, 13, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(16, 13, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(16, 13, 1, 2, twocount);
		break;
	}
	switch(R_two){
		case 0:
		set_bkg_tiles(16, 15, 1, 2, zerocount);
		break;
		case 1:
		set_bkg_tiles(16, 15, 1, 2, onecount);
		break;
		case 2:
		set_bkg_tiles(16, 15, 1, 2, twocount);
		break;
	}
}
void dropselect() BANKED{
	if (turn == 1){ //Black's column
		if (selection == 1){
			move_sprite(0, 144, 64);
			move_sprite(1, 152, 64);
			move_sprite(2, 160, 64);
			move_sprite(3, 168, 64);
			move_sprite(4, 144, 72);
			move_sprite(5, 152, 72);
			move_sprite(6, 160, 72);
			move_sprite(7, 168, 72);
			move_sprite(8, 144, 80);
			move_sprite(9, 152, 80);
			move_sprite(10, 160, 80);
			move_sprite(11, 168, 80);
			move_sprite(12, 144, 88);
			move_sprite(13, 152, 88);
			move_sprite(14, 160, 88);
			move_sprite(15, 168, 88);
		}
		if (selection == 2){
			move_sprite(0, 144, 80);
			move_sprite(1, 152, 80);
			move_sprite(2, 160, 80);
			move_sprite(3, 168, 80);
			move_sprite(4, 144, 88);
			move_sprite(5, 152, 88);
			move_sprite(6, 160, 88);
			move_sprite(7, 168, 88);
			move_sprite(8, 144, 96);
			move_sprite(9, 152, 96);
			move_sprite(10, 160, 96);
			move_sprite(11, 168, 96);
			move_sprite(12, 144, 104);
			move_sprite(13, 152, 104);
			move_sprite(14, 160, 104);
			move_sprite(15, 168, 104);
		}
		if (selection == 3){
			move_sprite(0, 144, 96);
			move_sprite(1, 152, 96);
			move_sprite(2, 160, 96);
			move_sprite(3, 168, 96);
			move_sprite(4, 144, 104);
			move_sprite(5, 152, 104);
			move_sprite(6, 160, 104);
			move_sprite(7, 168, 104);
			move_sprite(8, 144, 112);
			move_sprite(9, 152, 112);
			move_sprite(10, 160, 112);
			move_sprite(11, 168, 112);
			move_sprite(12, 144, 120);
			move_sprite(13, 152, 120);
			move_sprite(14, 160, 120);
			move_sprite(15, 168, 120);
		}
		if (selection == 4){
			move_sprite(0, 144, 112);
			move_sprite(1, 152, 112);
			move_sprite(2, 160, 112);
			move_sprite(3, 168, 112);
			move_sprite(4, 144, 120);
			move_sprite(5, 152, 120);
			move_sprite(6, 160, 120);
			move_sprite(7, 168, 120);
			move_sprite(8, 144, 128);
			move_sprite(9, 152, 128);
			move_sprite(10, 160, 128);
			move_sprite(11, 168, 128);
			move_sprite(12, 144, 136);
			move_sprite(13, 152, 136);
			move_sprite(14, 160, 136);
			move_sprite(15, 168, 136);
		}
		if (selection == 5){
			move_sprite(0, 144, 128);
			move_sprite(1, 152, 128);
			move_sprite(2, 160, 128);
			move_sprite(3, 168, 128);
			move_sprite(4, 144, 136);
			move_sprite(5, 152, 136);
			move_sprite(6, 160, 136);
			move_sprite(7, 168, 136);
			move_sprite(8, 144, 144);
			move_sprite(9, 152, 144);
			move_sprite(10, 160, 144);
			move_sprite(11, 168, 144);
			move_sprite(12, 144, 152);
			move_sprite(13, 152, 152);
			move_sprite(14, 160, 152);
			move_sprite(15, 168, 152);
		}
	}
	else{ //White's column
		if (selection == 1){
			move_sprite(0, 0, 64);
			move_sprite(1, 8, 64);
			move_sprite(2, 16, 64);
			move_sprite(3, 24, 64);
			move_sprite(4, 0, 72);
			move_sprite(5, 8, 72);
			move_sprite(6, 16, 72);
			move_sprite(7, 24, 72);
			move_sprite(8, 0, 80);
			move_sprite(9, 8, 80);
			move_sprite(10, 16, 80);
			move_sprite(11, 24, 80);
			move_sprite(12, 0, 88);
			move_sprite(13, 8, 88);
			move_sprite(14, 16, 88);
			move_sprite(15, 24, 88);
		}
		if (selection == 2){
			move_sprite(0, 0, 80);
			move_sprite(1, 8, 80);
			move_sprite(2, 16, 80);
			move_sprite(3, 24, 80);
			move_sprite(4, 0, 88);
			move_sprite(5, 8, 88);
			move_sprite(6, 16, 88);
			move_sprite(7, 24, 88);
			move_sprite(8, 0, 96);
			move_sprite(9, 8, 96);
			move_sprite(10, 16, 96);
			move_sprite(11, 24, 96);
			move_sprite(12, 0, 104);
			move_sprite(13, 8, 104);
			move_sprite(14, 16, 104);
			move_sprite(15, 24, 104);
		}
		if (selection == 3){
			move_sprite(0, 0, 96);
			move_sprite(1, 8, 96);
			move_sprite(2, 16, 96);
			move_sprite(3, 24, 96);
			move_sprite(4, 0, 104);
			move_sprite(5, 8, 104);
			move_sprite(6, 16, 104);
			move_sprite(7, 24, 104);
			move_sprite(8, 0, 112);
			move_sprite(9, 8, 112);
			move_sprite(10, 16, 112);
			move_sprite(11, 24, 112);
			move_sprite(12, 0, 120);
			move_sprite(13, 8, 120);
			move_sprite(14, 16, 120);
			move_sprite(15, 24, 120);
		}
		if (selection == 4){
			move_sprite(0, 0, 112);
			move_sprite(1, 8, 112);
			move_sprite(2, 16, 112);
			move_sprite(3, 24, 112);
			move_sprite(4, 0, 120);
			move_sprite(5, 8, 120);
			move_sprite(6, 16, 120);
			move_sprite(7, 24, 120);
			move_sprite(8, 0, 128);
			move_sprite(9, 8, 128);
			move_sprite(10, 16, 128);
			move_sprite(11, 24, 128);
			move_sprite(12, 0, 136);
			move_sprite(13, 8, 136);
			move_sprite(14, 16, 136);
			move_sprite(15, 24, 136);
		}
		if (selection == 5){
			move_sprite(0, 0, 128);
			move_sprite(1, 8, 128);
			move_sprite(2, 16, 128);
			move_sprite(3, 24, 128);
			move_sprite(4, 0, 136);
			move_sprite(5, 8, 136);
			move_sprite(6, 16, 136);
			move_sprite(7, 24, 136);
			move_sprite(8, 0, 144);
			move_sprite(9, 8, 144);
			move_sprite(10, 16, 144);
			move_sprite(11, 24, 144);
			move_sprite(12, 0, 152);
			move_sprite(13, 8, 152);
			move_sprite(14, 16, 152);
			move_sprite(15, 24, 152);
		}
	}
}
void dropping() BANKED{
	if (pieceselected == (PAWN)){
		P_one -= 1;
		board[pointx + pointy * BOARD_W] = PAWN;
	}
	else if (pieceselected == (PAWN | IS_WHITE)){
		P_two -= 1;
		board[pointx + pointy * BOARD_W] = (PAWN | IS_WHITE);
	}
	else if (pieceselected == SILVER){
		S_one -= 1;
		board[pointx + pointy * BOARD_W] = SILVER;
	}
	else if (pieceselected == (SILVER | IS_WHITE)){
		S_two -= 1;
		board[pointx + pointy * BOARD_W] = (SILVER | IS_WHITE);
	}
	else if (pieceselected == GOLD){
		G_one -= 1;
		board[pointx + pointy * BOARD_W] = GOLD;
	}
	else if (pieceselected == (GOLD | IS_WHITE)){
		G_two -= 1;
		board[pointx + pointy * BOARD_W] = (GOLD | IS_WHITE);
	}
	else if (pieceselected == ROOK){
		R_one -= 1;
		board[pointx + pointy * BOARD_W] = ROOK;
	}
	else if (pieceselected == (ROOK | IS_WHITE)){
		R_two -= 1;
		board[pointx + pointy * BOARD_W] = (ROOK | IS_WHITE);
	}
	else if (pieceselected == BISHOP){
		B_one -= 1;
		board[pointx + pointy * BOARD_W] = BISHOP;
	}
	else if (pieceselected == (BISHOP | IS_WHITE)){
		B_two -= 1;
		board[pointx + pointy * BOARD_W] = (BISHOP | IS_WHITE);
	}
	boardselected = 0;
	pointersprite();
	if (turn == 0){
		turn = 1;
	}
	else{
		turn = 0;
	}
}
void pointer() BANKED{
	disable_interrupts();
	if (boardselected == 1){
		if (turn == 0){
			set_sprite_prop(0, 0x00 |S_PALETTE);
			set_sprite_prop(1, 0x00 |S_PALETTE);
			set_sprite_prop(2, 0x00 |S_PALETTE);
			set_sprite_prop(3, 0x00 |S_PALETTE);
			move_sprite(0, (16*pointx)+46, (16*pointy)+70);
			move_sprite(1, (16*pointx)+8+46, (16*pointy)+70);
			move_sprite(2, (16*pointx)+46, (16*pointy)+8+70);
			move_sprite(3, (16*pointx)+8+46, (16*pointy)+8+70);
		}
		if (turn == 1){
			set_sprite_prop(0, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
			set_sprite_prop(1, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
			set_sprite_prop(2, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
			set_sprite_prop(3, S_FLIPX | 0x01 |S_FLIPY | 0x01 |S_PALETTE);
			move_sprite(0, (16*pointx)+8+46, (16*pointy)+8+70);
			move_sprite(1, (16*pointx)+46, (16*pointy)+8+70);
			move_sprite(2, (16*pointx)+8+46, (16*pointy)+70);
			move_sprite(3, (16*pointx)+46, (16*pointy)+70);
		}
		
		if ((pieceselected == PAWN) || (pieceselected == (PAWN | IS_WHITE))){
			pointerpawn();
		}
		else if ((pieceselected == PAWNPLUS) || (pieceselected == (PAWNPLUS | IS_WHITE))){
			pointerpawnplus();
		}
		else if ((pieceselected == SILVER) || (pieceselected == (SILVER | IS_WHITE))){
			pointersilver();
		}
		else if ((pieceselected == SILVERPLUS) || (pieceselected == (SILVERPLUS | IS_WHITE))){
			pointersilverplus();
		}
		else if ((pieceselected == GOLD) || (pieceselected == (GOLD | IS_WHITE))){
			pointergold();
		}
		else if ((pieceselected == BISHOP) || (pieceselected == (BISHOP | IS_WHITE))){
			pointerbishop();
		}
		else if ((pieceselected == BISHOPPLUS) || (pieceselected == (BISHOPPLUS | IS_WHITE))){
			pointerbishopplus();
		}
		else if ((pieceselected == ROOK) || (pieceselected == (ROOK | IS_WHITE))){
			pointerrook();
		}
		else if ((pieceselected == ROOKPLUS) || (pieceselected == (ROOKPLUS | IS_WHITE))){
			pointerrookplus();
		}
		else if ((pieceselected == KING) || (pieceselected == (KING | IS_WHITE))){
			pointerking();
		}
		
		move_sprite(4, 190, 174);
		move_sprite(5, 190, 174);
		move_sprite(6, 190, 174);
		move_sprite(7, 190, 174);
		move_sprite(8, 190, 174);
		move_sprite(9, 190, 174);
		move_sprite(10, 190, 174);
		move_sprite(11, 190, 174);
		move_sprite(12, 190, 174);
		move_sprite(13, 190, 174);
		move_sprite(14, 190, 174);
		move_sprite(15, 190, 174);
	}
	enable_interrupts();
}