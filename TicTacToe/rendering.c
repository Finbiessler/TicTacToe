//
//  rendering.c
//  TicTacToe in C
//
//  Created by Fin Bießler on 28.01.19.
//  Copyright © 2019 Fin Bießler. All rights reserved.
//
#include "game.h"
#include "rendering.h"
//Colors for in which certain objects should be rendered
const SDL_Color GRID_COLOR     = {.r = 255, .g = 255, .b = 255};
const SDL_Color PLAYER_X_COLOR = {.r = 255, .g = 0, .b = 0};
const SDL_Color PLAYER_0_COLOR = {.r = 0, .g = 0, .b = 255};
const SDL_Color TIE_COLOR      = {.r = 150, .g = 150, .b = 150};

// Function which renders the grid for the board
void render_grid(SDL_Renderer *renderer, const SDL_Color *color){
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    for(int i = 1; i < N; i++){
        SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCREEN_WIDTH, i * CELL_HEIGHT);
    }
} /* render_grid */

void render_x(SDL_Renderer *renderer, int row, int col, const SDL_Color *color){

    const float half_box_side = fmin(CELL_HEIGHT, CELL_WIDTH) * 0.25;
    const float center_x      = CELL_WIDTH * 0.5 + col * CELL_WIDTH;
    const float center_y      = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderDrawLine(renderer, center_x - half_box_side, center_y - half_box_side, center_x + half_box_side, center_y + half_box_side);
    SDL_RenderDrawLine(renderer, center_x + half_box_side, center_y - half_box_side, center_x - half_box_side, center_y + half_box_side);
}

void render_o(SDL_Renderer *renderer, int row, int col, const SDL_Color *color){
    const float half_box_side = fmin(CELL_HEIGHT, CELL_WIDTH) * 0.25;
    const float center_x      = CELL_WIDTH * 0.5 + col * CELL_WIDTH;
    const float center_y      = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_Rect rect;
    rect.x = center_x - half_box_side;
    rect.y = center_y - half_box_side;
    rect.w = half_box_side*2;
    rect.h = half_box_side*2;
    SDL_RenderDrawRect(renderer, &rect);


}

// Function which renders the board i. e. the content of the cells
void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            switch (board[i*N+j]) {
                    case PLAYER_0:
                        render_o(renderer, i, j, player_o_color);
                        break;
                    case PLAYER_X:
                        render_x(renderer, i, j, player_x_color);

                default:
                    break;
            }
        }
    }
} /* render_board */

// For rendering the game when it is in one of the gameover states, the color depends on the function call
void render_gameover_state(SDL_Renderer *renderer, const gamestate *game,  const SDL_Color *color){
    render_grid(renderer, color);
    render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_0_COLOR);
} /* render_gameover_state */

// For rendering the game when it is in the running state
void render_running_state(SDL_Renderer *renderer, const gamestate *game){
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_0_COLOR);
} /* render_running_state */

void render_game(SDL_Renderer *renderer, const gamestate *game){
    switch (game -> state) {
            case RUNNING_STATE:
                render_running_state(renderer, game);
                break;
            case PLAYER_X_WON_STATE:
                render_gameover_state(renderer, game, &PLAYER_X_COLOR);
                break;
            case PLAYER_0_WON_STATE:
                render_gameover_state(renderer, game, &PLAYER_0_COLOR);
                break;
            case TIE_STATE:
                render_gameover_state(renderer, game, &TIE_COLOR);
                break;



        default:
            break;
    }
}
