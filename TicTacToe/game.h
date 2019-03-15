//
//  game.h
//  TicTacToe in C
//
//  Created by Fin Bießler on 28.01.19.
//  Copyright © 2019 Fin Bießler. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>

//General defines for the game
#define N               3
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define CELL_HEIGHT   (SCREEN_HEIGHT/N)
#define CELL_WIDTH    (SCREEN_WIDTH/N)

//Board contents
#define EMPTY    0
#define PLAYER_X 1
#define PLAYER_0 2

//GAMESTATES
#define RUNNING_STATE      0
#define PLAYER_X_WON_STATE 1
#define PLAYER_0_WON_STATE 2
#define TIE_STATE          3
#define QUIT_STATE         4

//Type for the gamestate
struct gamestate {
    int board[N*N];
    int player;
    int state;
};

typedef struct gamestate gamestate;

#endif /* game_h */
