1. Be in the root directory

2. compile

```
gcc -o bin/test/all_tests_run test/run_testing.c test/unit/unbeatable_mode/unbeatable_mode_game_simulation.c src/game_play/game_checkers.c src/game_play/user_turn.c src/game_play/game_play.c src/computer_turn/unbeatable_mode.c src/computer_turn/normal_mode.c src/computer_turn/computer_moves.c src/computer_turn/computer_turn.c src/common/graphic.c src/common/err.c test/unit/unbeatable_mode/user_choices_samples.c
```

3. run

```
bin/test/./all_tests_run
```
