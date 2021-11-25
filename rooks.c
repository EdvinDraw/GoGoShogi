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

void rookupdate() BANKED{
	for(uint8_t x=0; x<6; x++){
		for(uint8_t y=0; y<6; y++){
			
			if (board[x + y * BOARD_W] == (ROOK | IS_WHITE)){
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
						if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) && (board[(x) + (y-a) * BOARD_W] == (KING | IS_WHITE))){
							whitethreat[(x) + (y-a) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t b = 1; b < BOARD_H; b++){
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
						if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) && (board[(x) + (y+b) * BOARD_W] == (KING | IS_WHITE))){
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
						if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) && (board[(x-c) + (y) * BOARD_W] == (KING | IS_WHITE))){
							whitethreat[(x-c) + (y) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t d = 1; d < BOARD_W; d++){
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
						if ( (board[(x) + (y+d) * BOARD_W] == EMPTY) && (board[(x+d) + (y) * BOARD_W] == (KING | IS_WHITE))){
							whitethreat[(x+d) + (y) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
			}
			else if (board[x + y * BOARD_W] == (ROOK)){
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
						if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) && (board[(x) + (y-a) * BOARD_W] == (KING))){
							blackthreat[(x) + (y-a) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t b = 1; b < BOARD_H; b++){
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
						if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) && (board[(x) + (y+b) * BOARD_W] == (KING))){
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
						if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) && (board[(x-c) + (y) * BOARD_W] == (KING))){
							blackthreat[(x-c) + (y) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t d = 1; d < BOARD_W; d++){
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
						if ( (board[(x+d) + (y) * BOARD_W] == EMPTY) && (board[(x+d) + (y) * BOARD_W] == (KING))){
							blackthreat[(x+d) + (y) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
			}
			else if (board[x + y * BOARD_W] == (ROOKPLUS | IS_WHITE)){
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
						if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) && (board[(x) + (y-a) * BOARD_W] == (KING | IS_WHITE))){
							whitethreat[(x) + (y-a) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t b = 1; b < BOARD_H; b++){
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
						if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) && (board[(x) + (y+b) * BOARD_W] == (KING | IS_WHITE))){
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
						if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) && (board[(x-c) + (y) * BOARD_W] == (KING | IS_WHITE))){
							whitethreat[(x-c) + (y) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t d = 1; d < BOARD_W; d++){
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
						if ( (board[(x) + (y+d) * BOARD_W] == EMPTY) && (board[(x+d) + (y) * BOARD_W] == (KING | IS_WHITE))){
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
			else if (board[x + y * BOARD_W] == (ROOKPLUS)){
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
						if ( (board[(x) + (y-a) * BOARD_W] == EMPTY) && (board[(x) + (y-a) * BOARD_W] == (KING))){
							blackthreat[(x) + (y-a) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t b = 1; b < BOARD_H; b++){
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
						if ( (board[(x) + (y+b) * BOARD_W] == EMPTY) && (board[(x) + (y+b) * BOARD_W] == (KING))){
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
						if ( (board[(x-c) + (y) * BOARD_W] == EMPTY) && (board[(x-c) + (y) * BOARD_W] == (KING))){
							blackthreat[(x-c) + (y) * BOARD_W] = 2;
						}
						else{
							break;
						}
					}
				}
				for(uint8_t d = 1; d < BOARD_W; d++){
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
						if ( (board[(x+d) + (y) * BOARD_W] == EMPTY) && (board[(x+d) + (y) * BOARD_W] == (KING))){
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
		}
	}
}