#ifndef FORM_H
#define FORM_H

#include <stdbool.h>

#include "common.h"

int MainMenuPage(void);

int ComputerModeMenuPage(void);

int FriendsModeMenuPage(void);

int ResetScoreMenuPage(void);

bool IsUserWillPlayFirst(void);

int EndGameMenuPage(char *board);

int GameTitleMenuPage(void);

void GetGameTitle(char *gameplay_title);

int GetGameplayModeOfSavedGames(void);

int GetSavedGameplayAction(void);

GameplayNumbers GetSavedGameplayNumber(GameplayTitles saved_games);

#endif