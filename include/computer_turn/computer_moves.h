#ifndef COMPUTER_MOVES_H
#define COMPUTER_MOVES_H

int MarkTheOppositeCornerOfACorner(char *board, const char playing_symbol);

int MarkARandomOppositeCornerOfAMiddle(char *board, const char playing_symbol);

int MarkARandomCorner(char *board, const char playing_symbol);

int MarkARandomMiddle(char *board, const char playing_symbol);

int MarkATargetedOppositeCornerOfAMiddle(char *board,
                                         const char playing_symbol);

int MarkTheAdjacentCornerToAMiddle(char *board,
                                   const char computer_playing_symbol);

int MakeTheCriticalMove(char *board, const char computer_playing_symbol,
                        int winning_direction, int squares_location);

#endif