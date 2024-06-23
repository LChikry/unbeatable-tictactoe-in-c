#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define true 1
#define false 0

#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define PLAYER_THREE 'V'
#define PLAYER_FOUR 'Q'
#define PLAYER_FIVE '@'

int main(void) {
  int number_of_players = 5;
  char board[(number_of_players + 1) * (number_of_players + 1)];

  for (size_t i = 0; i < (number_of_players + 1) * (number_of_players + 1);
       i++) {
    board[i] = '0';
  }

  return 0;
}