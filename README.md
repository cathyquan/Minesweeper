# Minesweeper
Developed a version of the classic Minesweeper game (http://minesweeperonline.com/) using object-oriented programming. Used SFML in the implementation of graphic user interface and windows control.

Rules Overview

The rules of the game are as follows:
- There exists a board, which contains a grid of spaces. A space could be a mine, or not. The player clicks on a space, and it gets revealed. The goal of the game is to reveal all the spaces that are not mines, while avoiding the spaces that are.
- When a space is revealed:
    - If it’s a mine, the game ends
    - If it’s not a mine, it shows the number of mines adjacent to that space (anywhere from 0 to 8, with 0 just showing as an empty space)
- If a space has no adjacent mines, all non-mine spaces adjacent to it are also revealed. The player uses the numbers as clues to figure out where other mines may be located.
- When all of the non-mine spaces have been revealed, the player wins!
   
Other features:
- Flags: Right-clicking a hidden space puts a flag on that space, marking it as a possible mine. Flagged spaces cannot be revealed (with left-clicks or as a result of adjacent spaces being revealed), but another right-click will remove the flag.
- Mine Counter: to track the number of mines that are on the board. Every time the player places a flag, the counter goes down by one. Every time they remove a flag, the counter goes up by one. The mine counter CAN go negative!
- Restart Button: The smiley face centered at the top or bottom of the window lets you restart a new board with everything reset and mines randomized

Non-standard features for my version of this project:
- Debug Button: Clicking this button will toggle the visibility of the mines on the board. Use this to help you test/debug various features of the game. Having to play the game properly each time you want to test something is very time-consuming. Creating these developer shortcuts helps speed up the development process
- Test Buttons #1-3: Another development shortcut, clicking on these loads a file with a specific board layout, details on this later.
