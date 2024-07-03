#ifndef MULTIPLE_PLAYER_GAME_CHECKERS_H
#define MULTIPLE_PLAYER_GAME_CHECKERS_H

const char MultiplePlayerWinnerChecker(char *board, const int number_of_players,
                                       char *symbols);

bool IsSomeoneCloseToWin(char *board, const int number_of_players,
                         char *symbols);

#endif