# Chess Engine

A chess engine built from scratch for CS246.

## A Quick Overview

The chess game is designed using the Model-View-Controller (MVC) architectural pattern, incorporating the Observer design pattern for handling display updates. 

## Board Class (Model)

The `Board` class functions as the **Model** in the MVC architecture. It maintains the state of the game by managing all chess pieces and provides methods to execute moves, as well as to check for stalemate and checkmate conditions.

### Key Responsibilities:
- **Move Execution**: Executes moves based on user input.
- **Game State Evaluation**: Checks for stalemate and checkmate conditions.

## Piece Classes

Each type of chess piece is represented by a class that inherits from an abstract `Piece` class. These classes implement the following virtual methods:

- `getPossibleMoves()`: Computes all possible moves for the piece according to its movement rules.
- `getPossibleCaptures()`: Determines all potential capture moves for the piece.

### Inheritance Hierarchy:
- **Abstract Piece Class**: Defines the interface for all chess pieces.
- **Concrete Piece Classes**: Implement specific movement and capture rules for each type of piece (e.g., Pawn, Rook, Knight).

## Handling Display

The display system follows the MVC pattern with the Observer design pattern to reflect changes in the game state.

### Components:
- **Abstract Observer Class**: Base class for all display observers.
- **Text View**: Inherits from the abstract observer class and outputs the board state to the standard output.
- **Window View**: Inherits from the abstract observer class and renders the board state to an X11 Window.

### Observers:
- **Text View**: Implements the `notify()` method to print the board state in a text format.
- **Window View**: Implements the `notify()` method to draw the board state in a graphical X11 window.

## Playing the Game

Interact with the system by issuing text-based commands. The following commands are supported:

### Commands

- **game white-player black-player**
  - Starts a new game.
  - The parameters `white-player` and `black-player` can be either `human` or `computer[1-4]`.
  - To make two bots play against each other until checkmate or stalemate after intializing the game (`game computer1 computer3`) run `cvc`

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

First `cd` into the `src` folder 

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


## Chess Engine Examined

The chess engine incorporates a series of progressively sophisticated bots, each building on the capabilities of the previous level. Central to the functionality of each bot is the getRandomMove() function. This function generates a seed and uses the standard library's algorithm to get a uniform probability distribution for move selection provided vector of moves. This is used for Check moves caputring moves and avoid capturing moves.

### Bot Levels

### Level 1: Basic Random Bot
The Level 1 bot is the most straightforward to implement. It compiles a list of all possible legal moves, including both captures and regular moves, and selects one at random with no preference. This bot operates purely on randomness, without any strategic consideration.

### Level 2: Check and Capture Preference Bot
The Level 2 bot introduces a rudimentary strategy by prioritizing moves that put the opponent in check. It operates as follows:
1. **Check Moves**: It filters for capturing moves that would attack the opponent's king.
2. **Capturing Moves**: If no check moves are available, it considers all capturing moves.
3. **Random Moves**: If neither check nor capturing moves are possible, it defaults to a random legal move.
Despite its simplicity, the Level 2 bot consistently outperforms the Level 1 bot due to its basic strategic considerations.

### Level 3: Avoid Capture Bot
The Level 3 bot builds on the strategy of the Level 2 bot with an additional layer of complexity: avoiding capture. Its decision-making process is:
1. **Check Moves**: Prioritize moves that put the opponent in check.
2. **Avoid Capturing Moves**: Identify pieces that are under threat from the opponent and prioritize moves that either retaliate (capture the threatening piece) or move out of danger.
3. **Capturing Moves**: If no pieces are under threat, consider capturing moves.
4. **Random Moves**: Default to a random legal move if no other preferred moves are available.
This bot improves over Level 2 by incorporating defensive tactics, ensuring pieces under attack respond or evade before considering other moves.

### Level 4: Piece Value-Based Bot
The Level 4 bot introduces intrinsic piece values to its decision-making process. It builds on the logic of the Level 2 bot but prioritizes moves based on the value of the pieces involved. The assigned values are:
- Pawn: 1
- Knight/Bishop: 3
- Rook: 5
- Queen: 9
- King: Infinite

The decision process for Level 4 is:
1. **Highest Value Capture**: Among capturing moves, select the one that captures the piece with the highest value.
2. **Check Moves**: Consider moves that put the opponent in check.
3. **Capturing Moves**: Default to capturing moves if no higher priority moves are available.
4. **Random Moves**: If no other criteria are met, select a random legal move.

### Level 5: Enhanced Piece Value and Avoid Capture Bot
The Level 5 bot, akin to a "Magnus Carlsen" in our chess engine, combines the strategies of Levels 3 and 4. It incorporates both the avoidance of capture and the value of pieces into its decision-making:
1. **Highest Value Avoid Capture**: Avoid capture, prioritizing moves that save higher value pieces.
2. **Highest Value Capture**: Among capturing moves, select the one that captures the piece with the highest value.
3. **Check Moves**: Prioritize moves that put the opponent in check.
4. **Capturing Moves**: Consider capturing moves if no other criteria are met.
5. **Random Moves**: Default to a random legal move if no other moves are preferred.

### Possible next steps for better bots 

Implementing a minimax algorithm with adjustable depth and alpha-beta pruning would significantly enhance our current bots. The primary advantage of the minimax algorithm, especially when combined with alpha-beta pruning, is its superior decision-making capabilities and improved efficiency compared to our existing bots. By controlling the algorithm's depth via a parameter, we can scale the bot's complexity and proficiency. For instance, bot 1 could have a depth of 1, while subsequent bots could increment depth by 2. Although higher depths increase computational demands, alpha-beta pruning mitigates this by eliminating unnecessary calculations, making the approach more computationally feasible. This offers an elegant and scalable solution for the AI component of our chess game.


## Tips for Graphics

### Linux Systems

- If you are not using the X system display protocol, we highly recommend using the `-nogui` option.
- We do not currently have a Wayland-compatible display solution.

### macOS

- Use XQuartz if you want a graphical display: [XQuartz](https://www.xquartz.org/)

### Windows

- Good luck!

