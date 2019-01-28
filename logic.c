//
//  logic.c
//  Flappy Bird in C
//
//  Created by Fin Bießler on 28.01.19.
//  Copyright © 2019 Fin Bießler. All rights reserved.
//
#include "game.h"
#include "logic.h"
int count_cells(gamestate *game){
    int count = 0;
    for(int i = 0; i < N*N; i++){
        if(game -> board[i] == EMPTY){
            count ++;
        }
    }
    return count;
}
int check_player_won(gamestate *game, int player){
    int row_count = 0;
    int col_count = 0;
    int diag1_count = 0;
    int diag2_count = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(game -> board[i*N+j] == player){
                row_count++;
            }
            if(game -> board[j*N+i] == player){
                col_count++;
            }
        }
        if(row_count >= N || col_count >= N){
            return 1;
        }
        row_count = 0;
        col_count = 0;
        if(game -> board[i*N+i] == player){
            diag1_count++;
        }
        if(game -> board[i*N+N-i-1] == player){
            diag2_count++;
        }
    }
    return diag1_count >= N || diag2_count >= N;
}

void game_over_condition(gamestate *game){
    if(check_player_won(game, PLAYER_X)){
        game -> state = PLAYER_X_WON_STATE;
    } else if (check_player_won(game, PLAYER_0)){
        game -> state = PLAYER_0_WON_STATE;
    } else if (!count_cells(game)){
        game -> state = TIE_STATE;
    }
}
void switch_player(gamestate *game){
    if(game -> player == PLAYER_X){
        game -> player = PLAYER_0;
    } else{
        game -> player = PLAYER_X;
    }
}
void player_turn(gamestate *game, int row, int col){
    if(game->board[row*N+col] == EMPTY){
        game -> board[row*N+col] = game -> player;
        switch_player(game);
        game_over_condition(game);
    }
}

void reset_game(gamestate *game){
    game -> state = RUNNING_STATE;
    game -> player = PLAYER_X;
    for(int i = 0; i < N*N; i++){
        game -> board[i] = EMPTY;
    }
}
void click_on_cell(gamestate *game, int row, int col){
    if(game->state == RUNNING_STATE){
        player_turn(game, row, col);
    } else{
        reset_game(game);
    }
}
