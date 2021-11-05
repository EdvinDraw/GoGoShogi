#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#ifndef BOARDCODE_H
#define BOARDCODE_H

extern uint8_t board[];
extern uint8_t pointx;
extern uint8_t pointy;
extern uint8_t pointx2;
extern uint8_t pointy2;
extern UINT8 drop;
extern UINT8 frame;
extern UINT8 valid;
extern UINT8 boardselected;
extern uint8_t pieceselected;
extern enum PieceType;
void initBoard();
extern bool boardselect(uint8_t x, uint8_t y);
extern bool isEmpty(uint8_t x, uint8_t y);
extern bool isWhite(uint8_t x, uint8_t y);
extern bool isBlack(uint8_t x, uint8_t y);
extern bool checkWhite();
extern bool checkBlack();
extern bool search_U;
extern bool search_D;
extern bool search_L;
extern bool search_R;
extern bool search_UL;
extern bool search_UR;
extern bool search_LL;
extern bool search_LR;
void boardupdate();
void pointersprite() BANKED;
void marker() BANKED;
void pointerpawn() BANKED;
void pointersilver() BANKED;
void pointergold() BANKED;
void pointerbishop() BANKED;
void pointerrook() BANKED;
void pointerking() BANKED;
void pointerpawnplus() BANKED;
void pointersilverplus() BANKED;
void pointerbishopplus() BANKED;
void pointerrookplus() BANKED;
void blackmove();
void whitemove();
void counter() BANKED;
void pointer() BANKED;
void boardsetup();
void canceling() BANKED;
void giving_up() BANKED;
void tablet(int status) BANKED;
void dropselect() BANKED;
void dropping() BANKED;

#endif