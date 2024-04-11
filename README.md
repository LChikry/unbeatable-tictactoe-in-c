# Unbeatable TicTacToe in C


## Important Notes

This game is in beta version. I only fully finished the development of the first choice in the main menu. Thus, choices from 2 to 4 needs to get programmed.


## About the Game

This game is similar to the TicTacToe game you can find in Google search engine, which is developed by google itself. However, this one has slightly more possibility to win in the unbeatable mode than the Google version.

Furthermore, this game has more features such as saving the gameplays and their scores in addition to the feature of playing with multiple friends at once (up to 5 friends).


## A Brief History

I start creating the game because I found two main ways to never get beaten by anyone, or even beat them. But latter on, I found that Google already developed the same thing. Nevertheless, my program implements a slight different algorithm than what Google does. Therefore, I continued developing it, so the community can have a C based clone of the game in addition to gaining experience from this fun project.

## How to Run The Game

1. Download the code of the master branch.
2. Open the program folder in the terminal.
3. Run the game using this command:

```
bin/src/./main
```

## Compile The Game (If You Couldn't Run It)

1. Open the program folder in the terminal.
2. Compile the game using this command:

```
gcc -o bin/src/main ./src/main.c ./src/computer_turn/unbeatable_mode.c ./src/computer_turn/normal_mode.c ./src/computer_turn/computer_moves.c ./src/computer_turn/computer_turn.c ./src/common/err.c ./src/common/graphic.c ./src/common/form.c ./src/game_play/game_checkers.c ./src/game_play/user_turn.c ./src/game_play/game_play.c ./src/game_play/saving_gameplays.c
```

3. Now, run the game using this command:

```
bin/src/./main
```

## Contributing

Please follow the following steps to contribute to this project. There are some important procedures.

1. Fork and clone this repository.
2. Create a branch from the `dev` branch, not the master.
3. Make you changes
4. Open a pull request to the `dev` branch, not the master.
5. Voila!

## Issues I'm aware of

- none.
