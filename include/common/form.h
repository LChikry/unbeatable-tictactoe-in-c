#ifndef FORM_H
#define FORM_H

int MainMenuPage(void);

int ComputerModeMenuPage(void);

int FriendsModeMenuPage(void);

int ResetScoreMenuPage(void);

int WhoWillPlayFirst(void);

void AssignPlayingSymbols(char *user_playing_symbol,
                          char *computer_playing_symbol);

int EndGameMenuPage(char *board, const char computer_playing_symbol);

#endif