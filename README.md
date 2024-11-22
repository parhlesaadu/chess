This project is a simplified, two-player version of chess designed for command-line interfaces (it does not contain any graphics). The chessboard is an 8x8 character array, wherein dots represent free cells, while letters represent the following pieces:
- K/k - King: Can move one cell from its original position, either vertically or horizontally or diagonally
- Q/q - Queen: Can move any distance either vertically or horizontally or diagonally
- R/r - Rook: Can move any distance either vertically or horizontally
- B/b - Bishop: Can move any distance diagonally
- N/n - Knight: Can move either two cells vertically and then one cell horizontally, or two cells horizontally and then one cell vertically
- This game does not contain any pawns.

Uppercase letters denote Player 1's pieces, while lowercase letters denote Player 2's. Players start their move by selecting a piece and entering its current coordinates (in terms of rows and columns), after which they are given several choices of new coordinates according to the rules specified above. Each player can eliminate any of their opponent's pieces, regardless of type, by landing on it. The game concludes when either king is eliminated.

**How to run the game:**
As this code does not contain external libraries, it can easily be executed on any C++ compiler. If you don't have an integrated development environment (IDE) on your computer, you can  copy and paste the entire code and run it [here](https://www.programiz.com/cpp-programming/online-compiler/).

**Credits:**\
[Saad Ahmed](https://linkedin.com/in/parhlesaadu) - input validation, procedure design\
[Mohammad Umer](https://linkedin.com/in/mohammad-umer-1506bb250) - interface design
