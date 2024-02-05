# Unfair TicTacToe

## About the Game

This game is similar to the TicTacToe game you can find in Google search engine, which is developed by google itself. However, it has slightly more possibility to win than the Google version.

I start creating the game because I found two main ways to never get beaten by anyone, or even beat them. But latter on, I found that Google already developed the same thing. Nevertheless, my program implements a slight different algorithm than what Google does. Therefore, I continued developing it, so the community can have a C based clone of the game in addition to gaining experience from this fun project.

## How to Install & Use

1. go to src folder.
   `cd src`

2. compile the program to an executable file using this command
   `gcc -o ../bin/src/main main.c ./computer_turn/unbeatable_mode.c ./computer_turn/normal_mode.c ./computer_turn/computer_moves.c ./computer_turn/computer_turn.c ./common/err.c ./common/graphic.c ./common/form.c ./game_play/game_checkers.c ./game_play/user_turn.c ./game_play/game_play.c`

3. execute the program using this command
   `../bin/src/./main`

## Technologies & Knowledge Used
- Terminal manipulation (Escape Sequences).
- Modularization of the code (Makefile & CMake).
- Linked List data structure
- 

## Issues I'm aware of
- The game exit at the end of playing a round with the computer.