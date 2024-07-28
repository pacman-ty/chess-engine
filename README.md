# Chess Engine

A chess engine built from scratch for CS246.

## Playing the Game

Interact with the system by issuing text-based commands. The following commands are supported:

### Commands

- **game white-player black-player**
  - Starts a new game.
  - The parameters `white-player` and `black-player` can be either `human` or `computer[1-4]`.

- **resign**
  - Concedes the game to your opponent.
  - This is the only way, outside of winning or drawing the game, to end a game.

- **move start end [promotion]**
  - Moves a piece from the starting coordinate to the ending coordinate.
  - Example: `move e2 e4`
  - Castling: `move e1 g1` (king-side) or `move e1 c1` (queen-side) for white.
  - Pawn promotion: `move e7 e8 Q`
  - For a computer player, the command `move` (without arguments) makes the computer player move.

- **setup**
  - Enters setup mode, where you can set up your own initial board configurations.
  - This can only be done when a game is not currently running.

#### Setup Mode Commands

- `+ K e1`
  - Places the piece K (white king in this case) on the square e1.
- `- e1`
  - Removes the piece from the square e1 and then redisplays the board.
  - If there is no piece at that square, take no action.
- `= colour`
  - Makes it the specified color’s turn to go next.
- `done`
  - Leaves setup mode.

Upon completion of setup mode, the board verifies that it contains exactly one white king and exactly one black king, and that neither king is in check.

## Running the Program

compile

```sh 
make
```

run

```sh
./chess
```

or for no gui 

```sh
./chess -nogui
```


### Tips for Graphics

#### Linux Systems

- If you are not using the X system display protocol, we highly recommend using the `-nogui` option.
- We do not currently have a Wayland-compatible display solution.

#### macOS

- Use XQuartz if you want a graphical display: [XQuartz](https://www.xquartz.org/)

#### Windows

- Good luck!

