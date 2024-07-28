# Chess Engine
chess engine built from scratch for cs246

### Playing the game
Interact with the system by issuing text-based commands. The following commands are supported:
• `game white-player black-player` starts a new game. The parameters white-player and black-player
can be either `human` or `computer[1-4]`.
• `resign` concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a
game.
• A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved. For
example: move e2 e4. Castling would specified by the two-square move for the king: move e1 g1 or move e1
c1 for white. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7
e8 Q. In the case of a computer player, the command move (without arguments) makes the computer player make a
move.
• setup enters setup mode, within which you can set up your own initial board configurations. This can only be done
when a game is not currently running. Within setup mode, the following language is used:
– + K e1 places the piece K (i.e., white king in this case) on the square e1. If a piece is already on that square, it
is replaced. The board should be redisplayed.
– - e1 removes the piece from the square e1 and then redisplays the board. If there is no piece at that square, take
no action.
– = colour makes it colour’s turn to go next.
Page 3 of 5
CS246 SPRING 2024 PROJECT – CHESS
– done leaves setup mode.
Upon completion of setup mode, you must verify that the board contains exactly one white king and exactly one black
king; that no pawns are on the first or last row of the board; and that neither king is in check

 

After compiling run `./chess` or `./chess -nogui`

Tips for graphics 

**Linux systems**
If you are not using X system display protocal we highly recommend you use the `-nogui` option. We do not currently have a Wayland compatible display solution.  

**MacOs**

XQuarts if you want a graphical display (https://www.xquartz.org/)

 **Windows**

 Goodluck 
