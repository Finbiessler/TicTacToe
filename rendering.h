//
//  rendering.h
//  Flappy Bird in C
//
//  Created by Fin Bießler on 28.01.19.
//  Copyright © 2019 Fin Bießler. All rights reserved.
//

#ifndef rendering_h
#define rendering_h

#include <stdio.h>
#include <SDL2/SDL.h>

void render_game(SDL_Renderer *renderer, const gamestate *game);

#endif /* rendering_h */
