#ifndef SAVING_GAMEPLAYS_H
#define SAVING_GAMEPLAYS_H

#include <stdbool.h>

#include "../common/common.h"

GameplayNode *SaveTheMove(GameplayNode **top, int new_move);

int GetNextGameplayTitleNumber(int game_mode_choice);

int SaveTheGameplay(GameplayNode *top, int game_mode, const char *game_title,
                    bool is_user_played_first);

void DeleteTheGameplay(GameplayNode **top);

GameplayTitles GetSavedGameplaysTitleAndNumber(int game_mode);

void DeleteSavedGameplays(GameplayTitles saved_games,
                          GameplayNumbers saved_gameplays_number,
                          int game_mode);

#endif