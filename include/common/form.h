#ifndef FORM_H
#define FORM_H

typedef struct {
  int *list_of_saved_numbers;
  int list_length;
} GameplayNumbers;

int MainMenuPage(void);

int ComputerModeMenuPage(void);

int FriendsModeMenuPage(void);

int ResetScoreMenuPage(void);

int IsUserWillPlayFirst(void);

int EndGameMenuPage(char *board);

int GameTitleMenuPage(void);

void GetGameTitle(char *gameplay_title);

int GetGameplayModeOfSavedGames(void);

int GetSavedGameplayAction(void);

GameplayNumbers GetSavedGameplayNumber(GameplayTitles saved_games);

#endif