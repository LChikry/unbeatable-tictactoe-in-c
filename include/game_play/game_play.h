#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include <stdbool.h>

#include "../../include/game_play/saving_gameplays.h"

int GamePlay(char *board, int game_mode, bool should_user_play,
             GameplayNode **top);

#endif