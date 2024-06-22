#ifndef FORM_H
#define FORM_H

#include <stdbool.h>

#include "common.h"

int MainMenuPage(void);

int GetGameplayMode(void);

int FriendsModeMenuPage(void);

int ResetScoreMenuPage(void);

bool IsUserWillPlayFirst(void);

int EndGameMenuPage(char *board);

int GameTitleMenuPage(void);

void GetGameTitle(char *gameplay_title);

int GetSavedGameplayAction(void);

GameplayNumbers GetSavedGameplayNumber(GameplayTitles saved_games, int game_mode);

#endif