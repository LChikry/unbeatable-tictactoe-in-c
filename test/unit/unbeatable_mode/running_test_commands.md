# To Run the User Playing Choices Code

1. Be in the root directory

2. Compile the test

```
gcc -o bin/test/helper/user_choices_samples test/unit/unbeatable_mode/user_choices_samples.c
```

3. Run the test

```
bin/test/helper/./user_choices_samples
```

# To Run the Game Simulator

1. Be in the root directory

2. Compile the test

```
gcc -o bin/test/unit/unbeatable_mode_game_simulation test/unit/unbeatable_mode/unbeatable_mode_game_simulation.c src/game_play/game_checkers.c src/game_play/user_turn.c src/game_play/game_play.c src/computer_turn/unbeatable_mode.c src/computer_turn/normal_mode.c src/computer_turn/computer_moves.c src/computer_turn/computer_turn.c src/common/graphic.c src/common/err.c
```

3. Run the test

```
bin/test/unit/./unbeatable_mode_game_simulation
```
