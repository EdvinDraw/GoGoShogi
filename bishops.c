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

void bishopupdate() BANKED{
	for(uint8_t x=0; x<6; x++){
		for(uint8_t y=0; y<6; y++){
			
			if (board[x + y * BOARD_W] == (BISHOP | IS_WHITE)){
				bool upperleftrow = 1;
				bool upperrightrow = 1;
				bool lowerleftrow = 1;
				bool lowerrightrow = 1;
				for(uint8_t a = 1; a < x; a++){
					for(uint8_t b = 1; b < y; b++){
						if (upperleftrow == false){
							if ( (board[(x-a) + (y-b) * BOARD_W] == EMPTY) || (board[(x-a) + (y-b) * BOARD_W] == (KING)) ){
								whitethreat[(x-a) + (y-b) * BOARD_W] = 1;
							}
							else if ( (board[(x-a) + (y-b) * BOARD_W] != EMPTY) && (board[(x-a) + (y-b) * BOARD_W] != (KING)) ){
								whitethreat[(x-a) + (y-b) * BOARD_W] = 1;
								upperleftrow = true;
							}
						}
						else if (upperleftrow == true){
							if ( (board[(x-a) + (y-b) * BOARD_W] == EMPTY) && (board[(x-a) + (y-b) * BOARD_W] == (KING | IS_WHITE))){
								whitethreat[(x-a) + (y-b) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
				for(uint8_t c = 1; c < BOARD_W; c++){
					for(uint8_t d = 1; d < y; d++){
						if (upperrightrow == false){
							if ( (board[(x+c) + (y-d) * BOARD_W] == EMPTY) || (board[(x+c) + (y-d) * BOARD_W] == (KING)) ){
								whitethreat[(x+c) + (y-d) * BOARD_W] = 1;
							}
							else if ( (board[(x+c) + (y-d) * BOARD_W] != EMPTY) && (board[(x+c) + (y-d) * BOARD_W] != (KING)) ){
								whitethreat[(x+c) + (y-d) * BOARD_W] = 1;
								upperrightrow = true;
							}
						}
						else if (upperrightrow == true){
							if ( (board[(x+c) + (y-d) * BOARD_W] == EMPTY) && (board[(x+c) + (y-d) * BOARD_W] == (KING | IS_WHITE))){
								whitethreat[(x+c) + (y-d) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
				for(uint8_t e = 1; e < x; e++){
					for(uint8_t f = 1; f < BOARD_H; f++){
						if (lowerleftrow == false){
							if ( (board[(x-e) + (y+f) * BOARD_W] == EMPTY) || (board[(x-e) + (y+f) * BOARD_W] == (KING)) ){
								whitethreat[(x-e) + (y+f) * BOARD_W] = 1;
							}
							else if ( (board[(x-e) + (y+f) * BOARD_W] != EMPTY) && (board[(x-e) + (y+f) * BOARD_W] != (KING)) ){
								whitethreat[(x-e) + (y+f) * BOARD_W] = 1;
								lowerleftrow = true;
							}
						}
						else if (lowerleftrow == true){
							if ( (board[(x-e) + (y+f) * BOARD_W] == EMPTY) && (board[(x-e) + (y+f) * BOARD_W] == (KING | IS_WHITE))){
								whitethreat[(x-e) + (y+f) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
				for(uint8_t g = 1; g < BOARD_W; g++){
					for(uint8_t h = 1; h < BOARD_H; h++){
						if (lowerrightrow == false){
							if ( (board[(x+g) + (y+h) * BOARD_W] == EMPTY) || (board[(x+g) + (y+h) * BOARD_W] == (KING)) ){
								whitethreat[(x+g) + (y+h) * BOARD_W] = 1;
							}
							else if ( (board[(x+g) + (y+h) * BOARD_W] != EMPTY) && (board[(x+g) + (y+h) * BOARD_W] != (KING)) ){
								whitethreat[(x+g) + (y+h) * BOARD_W] = 1;
								lowerrightrow = true;
							}
						}
						else if (lowerrightrow == true){
							if ( (board[(x+g) + (y+h) * BOARD_W] == EMPTY) && (board[(x+g) + (y+h) * BOARD_W] == (KING | IS_WHITE))){
								whitethreat[(x+g) + (y+h) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
			}
			else if (board[x + y * BOARD_W] == (BISHOP)){
				bool upperleftrow = 1;
				bool upperrightrow = 1;
				bool lowerleftrow = 1;
				bool lowerrightrow = 1;
				for(uint8_t a = 1; a < x; a++){
					for(uint8_t b = 1; b < y; b++){
						if (upperleftrow == false){
							if ( (board[(x-a) + (y-b) * BOARD_W] == EMPTY) || (board[(x-a) + (y-b) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x-a) + (y-b) * BOARD_W] = 1;
							}
							else if ( (board[(x-a) + (y-b) * BOARD_W] != EMPTY) && (board[(x-a) + (y-b) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x-a) + (y-b) * BOARD_W] = 1;
								upperleftrow = true;
							}
						}
						else if (upperleftrow == true){
							if ( (board[(x-a) + (y-b) * BOARD_W] == EMPTY) && (board[(x-a) + (y-b) * BOARD_W] == (KING))){
								blackthreat[(x-a) + (y-b) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
				for(uint8_t c = 1; c < BOARD_W; c++){
					for(uint8_t d = 1; d < y; d++){
						if (upperrightrow == false){
							if ( (board[(x+c) + (y-d) * BOARD_W] == EMPTY) || (board[(x+c) + (y-d) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x+c) + (y-d) * BOARD_W] = 1;
							}
							else if ( (board[(x+c) + (y-d) * BOARD_W] != EMPTY) && (board[(x+c) + (y-d) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x+c) + (y-d) * BOARD_W] = 1;
								upperrightrow = true;
							}
						}
						else if (upperrightrow == true){
							if ( (board[(x+c) + (y-d) * BOARD_W] == EMPTY) && (board[(x+c) + (y-d) * BOARD_W] == (KING))){
								blackthreat[(x+c) + (y-d) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
				for(uint8_t e = 1; e < x; e++){
					for(uint8_t f = 1; f < BOARD_H; f++){
						if (lowerleftrow == false){
							if ( (board[(x-e) + (y+f) * BOARD_W] == EMPTY) || (board[(x-e) + (y+f) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x-e) + (y+f) * BOARD_W] = 1;
							}
							else if ( (board[(x-e) + (y+f) * BOARD_W] != EMPTY) && (board[(x-e) + (y+f) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x-e) + (y+f) * BOARD_W] = 1;
								lowerleftrow = true;
							}
						}
						else if (lowerleftrow == true){
							if ( (board[(x-e) + (y+f) * BOARD_W] == EMPTY) && (board[(x-e) + (y+f) * BOARD_W] == (KING))){
								blackthreat[(x-e) + (y+f) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
				for(uint8_t g = 1; g < BOARD_W; g++){
					for(uint8_t h = 1; h < BOARD_H; h++){
						if (lowerrightrow == false){
							if ( (board[(x+g) + (y+h) * BOARD_W] == EMPTY) || (board[(x+g) + (y+h) * BOARD_W] == (KING | IS_WHITE)) ){
								blackthreat[(x+g) + (y+h) * BOARD_W] = 1;
							}
							else if ( (board[(x+g) + (y+h) * BOARD_W] != EMPTY) && (board[(x+g) + (y+h) * BOARD_W] != (KING | IS_WHITE)) ){
								blackthreat[(x+g) + (y+h) * BOARD_W] = 1;
								lowerrightrow = true;
							}
						}
						else if (lowerrightrow == true){
							if ( (board[(x+g) + (y+h) * BOARD_W] == EMPTY) && (board[(x+g) + (y+h) * BOARD_W] == (KING))){
								blackthreat[(x+g) + (y+h) * BOARD_W] = 2;
							}
							else{
								break;
							}
						}
					}
				}
			}
			else if (board[x + y * BOARD_W] == (BISHOPPLUS | IS_WHITE)){
				bool upperleftrow = 1;
				bool upperrightrow = 1;
				bool lowerleftrow = 1;
				bool lowerrightrow = 1;
				whitethreat[(x-1) + (y-1) * BOARD_W] = 1;
				whitethreat[(x+1) + (y-1) * BOARD_W] = 1;
				whitethreat[(x-1) + (y+1) * BOARD_W] = 1;
				whitethreat[(x+1) + (y+1) * BOARD_W] = 1;
			}
			else  if (board[x + y * BOARD_W] == (BISHOPPLUS)){
				bool upperleftrow = 1;
				bool upperrightrow = 1;
				bool lowerleftrow = 1;
				bool lowerrightrow = 1;
				blackthreat[(x-1) + (y-1) * BOARD_W] = 1;
				blackthreat[(x+1) + (y-1) * BOARD_W] = 1;
				blackthreat[(x-1) + (y+1) * BOARD_W] = 1;
				blackthreat[(x+1) + (y+1) * BOARD_W] = 1;
			}
		}
	}
}