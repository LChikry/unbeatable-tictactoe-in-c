#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "../../include/game_play/saving_gameplays.h"

// Behind the scenes
void TerminalCleaner(void);

// Messages
void LogoPrinter(void);
void WelcomePage(void);
void ErrorMessagePrinter(void);
void SuccessfulMessagePrinter(void);
void GameIntro(void);
void WinnerMessagePrinter(int game_mode, int game_result);
void SavedGameMessage(char *gameplay_title,
                      bool is_gameplay_saved_successfully);

// others
int PickRandomlyWhoWillPlayFirst(void);
void BoardPrinter(char *board);
void MultiplePlayerBoardPrinter(char *board, int number_of_players);
int PrintSavedGameplayTitles(int gameplay_mode);
void PrintSavedGameplayBoards(GameplayNumbers gameplays_to_print,
                              int gameplay_mode, int titles_count);
void DisplayMultiplePlayerRules(void);

#endif