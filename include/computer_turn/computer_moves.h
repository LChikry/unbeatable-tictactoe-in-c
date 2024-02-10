#ifndef COMPUTER_MOVES_H
#define COMPUTER_MOVES_H

int MarkTheOppositeCornerOfACorner(char *board);

int MarkARandomOppositeCornerOfAMiddle(char *board);

int MarkARandomCorner(char *board);

int MarkARandomMiddle(char *board);

int MarkATargetedOppositeCornerOfAMiddle(char *board);

int MarkTheAdjacentCornerToAMiddle(char *board);

int MakeTheCriticalMove(char *board, int winning_direction,
                        int squares_location);

#endif