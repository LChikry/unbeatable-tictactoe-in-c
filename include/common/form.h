#ifndef FORM_H
#define FORM_H

int MainMenuPage(void);

int ComputerModeMenuPage(void);

int FriendsModeMenuPage(void);

int ResetScoreMenuPage(void);

int IsUserWillPlayFirst(void);

int EndGameMenuPage(char *board);

int GameTitleMenuPage(void);

void GetGameTitle(char *gameplay_title, int max_size);

#endif