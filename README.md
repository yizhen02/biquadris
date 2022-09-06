# biquadris

Tetris is expanded for two player competition, leading to this game Biquandris.

Biquadris is a Tetris-style game for two players. Each player takes turns manipulating a block on one of two boards. A row can be deleted if all of its conditions are met. A block can be deleted if all of its cells are cleared. When a player's block on one of the boards cannot be filled, he or she loses. The number of lines and blocks deleted will be used to calculate your score. Moreover, players can take some special actions during the game to interfere with their opponents’ turns.

Our implementation of Biquadris follows mainly the Model-View-Controller Architecture with massive use of factory and decorator patterns.

Biquadris is not real-time, i.e. you have as much time to decide where to put a block. Moreover, there are extra features (Special Actions) available when a player, upon dropping a block, clears at least two rows simultaneously. A special action has negative influence on the opponent's turn: 
1)blind: The player’s board, from columns 3-9, and from rows 3-12, is covered with question marks (?), until the player drops a block; then the display reverts to normal. 
2)heavy: Every time a player moves a block left or right, the block automatically falls by two rows, after the horizontal move. If it is not possible for the block to drop two rows, it is considered to be dropped, and the turn ends. If the player is already in a level in which blocks are heavy, the effect is cumulative (i.e., the player suffers from both effects).
3)force: Change the opponent’s current block to be one of the player’s choosing. If the block cannot be placed in its initial position, the opponent loses. (E.g., force Z)

The game has both text-based and graphical displays. They look as follows:
<img width="1008" alt="Screen Shot 2022-09-06 at 5 18 39 PM" src="https://user-images.githubusercontent.com/112984472/188740534-66f7a036-bb57-44e5-8ff0-40dbb5f9ae30.png">
<img width="334" alt="Screen Shot 2022-09-06 at 5 18 52 PM" src="https://user-images.githubusercontent.com/112984472/188740582-4163ba03-d40c-4417-9f52-e7ca22ad264f.png">
