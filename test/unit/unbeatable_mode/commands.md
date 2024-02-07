# To Run the User Playing Choices Code

1. Go to test/unit/unbeatable_mode directory from the root directory

```
cd test/unit/unbeatable_mode
```

2. Compile the test

```
gcc -o ../../../bin/test/helper/user_choices_samples user_choices_samples.c
```

3. Run the test

```
../../../bin/test/helper/./user_choices_samples
```

# To Run the Game Simulator

1. Go to src directory from the root directory

```
  cd src
```

2. Compile the test

```
gcc -o ../bin/test/unit/unbeatable_mode_game_simulation ../test/unit/unbeatable_mode/unbeatable_mode_game_simulation.c game_play/game_checkers.c game_play/user_turn.c game_play/game_play.c computer_turn/unbeatable_mode.c computer_turn/normal_mode.c computer_turn/computer_moves.c computer_turn/computer_turn.c common/graphic.c common/err.c
```

3. Run the test

```
../bin/test/unit/./unbeatable_mode_game_simulation
```
