#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* This is the maximum size allowed for the underlying 2D array */
#define MAX_SIZE 10

/*********************************************************************************/
/*********************************************************************************/
/*** Place your definitions of the functions from connect4.c here ***/
/*********************************************************************************/
/*********************************************************************************/


/*********************************************************************************/
int FourPos(int values[], int size) {
    // Function which finds a sequence of four adjacent identical integers
    // Returns the index of the starting point of the sequence
    // If a sequence of four adjacent identical integers is not found, the function returns -1.
    int count = 1; // Count keeps track of how many identical numbers in a row
    for (int i = 1; i < size; i++) {
        // If the value at index i, equals the value at the previous index, count is incremented
        if (values[i] == values[i-1]) {
            count++;
        } else {
            // If not equal, count is reset back to 1
            count = 1;
        }
        
        // If count = 4, meaning there is four identical numbers in a row, it returns the index where the seqeunce starts
        if (count == 4) {
            return (i-3);
            
        }
    }
    // If a sequence of four identical numbers is not found, return -1
    return -1;
}

void PrintGrid(int board[MAX_SIZE][MAX_SIZE], int size) {
    // Prints a row of # above the board
    for (int i = 0; i < (size * 2 + 1); i++) {
        printf("#");
    }

    printf("\n");

    // Prints each row of the board
    for (int i = 0; i < size; i++) {
        printf("#"); // The left #

        // Prints each element of the current row being printed
        for (int j = 0; j < size; j++) {
            if (j < size - 1) {
                // Prints value with a space
                printf("%d ", board[i][j]);
            } else {
                // For last value no space
                printf("%d", board[i][j]);
            }
        }

        printf("#\n"); // Right # + new line
    }

    // Prints a row of # below the board
    for (int i = 0; i < (size * 2 + 1); i++) {
        printf("#");
    }
	printf("\n");
}
// Function edits the contents of the board, according to the order of the characters in the string, initalise
void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size, char *initialise) {
	
	// Loops through every position on board
	for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
				// Sets to 0
                board[i][j] = 0;
            }
        }
    // Index to loop through every element in the board
    int i = 0; 
	
	// If the input is NULL
    if (initialise == NULL) {
		// End the loop
        return;
    }
	
    // Loop through every position on the board
    while (i != size*size && initialise[i] != '\0') {
        // If the character currently is equal to X, set the current element to 1
        if (initialise[i] == 'X') {
            board[i/size][i%size] = 1;
        }
        // If the character currently is equal to O, set the current element to 2
        if (initialise[i] == 'O') {
            board[i/size][i%size] = 2;
        }
        
        // Increment i, to check the next character
        i++;
        
    }
    
}
// Finds a sequence of four identical tokens, if found, returns the player whose token it is, otherwise 0.
int FourInARow(int board[MAX_SIZE][MAX_SIZE], int size, int row, int col) {

    int matchingElement = board[row][col];
    
    // Vertical check
    // Count for identical adajcent elements
    int count = 0; 
    // If the cell is empty/0, return 0 as no four in a row.
    if (matchingElement == 0) { 
        return 0;
    }
    
    // Loop through one collumn
    for (int i=0;i<size;i++) {
        // Increment if the current cell matches the target number!
        if (board[i][col] == matchingElement) {
            count++;
        // Otherwise reset count
        } else {
            count = 0;
        }
        // Checks if there is a sequence of four including the cell given by the user.
        if (count >= 4 && row <= i && i-3 <= row) {
            // Returns 1 or 2 depending who won
            return matchingElement;
        }
    }
    
    // Horizontal check
    
    // Reset Count
    count = 0;
    
    // Loop through one row
    for (int i = 0; i < size; i++) {
        // Increment if the current cell matches the target number!
        if (board[row][i] == matchingElement) {
            count++;
        // Otherwise reset count
        } else {
            count = 0;
        }
        // Checks if there is a sequence of four including the cell given by the user.
        if (count >= 4 && i - 3 <= col && col <= i) {
            // Returns 1 or 2 depending who won
            return matchingElement;
        }
    }
    
    // Diagonal check (Top left to Bottom Right)
    count = 0;
    
    // Finding start position
    int startRow = row;
    int startCol = col;
    // Finds the top left starting element, that is on the same line as the point on row,col
    while (startRow != 0 && startCol != 0) {
        startRow--;
        startCol--;
    }
    
    // The number of how many times to iterate of particular diagonal
    int EndPosFactor; 
    EndPosFactor = size - startRow - startCol;
    // Loop through one diagonal
    for (int i = 0; i<EndPosFactor; i++) {
        int CurrentRow = startRow + i;
        int CurrentCol = startCol + i;
        // Increment if the current cell matches the target number!
        if (board[CurrentRow][CurrentCol] == matchingElement) {
            count++;
        // Otherwise reset count
        } else {
            count = 0;
        }
        // Checks if there is a sequence of four including the cell given by the user.
        if (count >= 4 && (CurrentRow - 3 <= row && row <= CurrentRow) &&
        (CurrentCol - 3 <= col && col <= CurrentCol)) {
            // Returns 1 or 2 depending who won
            return matchingElement;
        }
     }
     
    // Diagonal Check 2 (Bottom Left to Top Right)
    count = 0;
     
    // Finding start position
    startRow = row;
    startCol = col;
    // Finds the bottom left starting element, that is on the same line as the point on row,col
    while (startRow != size -1 && startCol != 0) {
         startRow++;
         startCol--;
     }
     
    // The number of how many times to iterate of particular diagonal
    if (startCol == size - 1) {
        EndPosFactor = startRow + 1;
    } else {
        EndPosFactor = size - startCol;
    }
    
    // Loop through one diagonal
    for (int i=0;i<EndPosFactor;i++) {
        int CurrentRow = startRow - i;
        int CurrentCol = startCol + i;
        // Increment if the current cell matches the target number!
        if (board[CurrentRow][CurrentCol] == matchingElement) {
            count++;
        // Otherwise reset count
        } else {
            count = 0;
        }
        // Checks if there is a sequence of four including the cell given by the user.
        if (count >= 4 && (CurrentRow + 3 >= row && row >= CurrentRow) &&
        (CurrentCol >= col && col >= CurrentCol - 3)) {
            // Returns 1 or 2 depending who won
            return matchingElement;
        }
    }
    // If no sequence of four found, return 0
    return 0;
    
}
// Inserts a token into the board, in any four cartenl direcitons. If there is no slot for the token, no token is placed.
void PopIn(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player) {
    
    // Checks if token is supposed to go from the top
    if (side == 'T') {
        // Only inserts token if top of the collumn is empty
        if (board[0][move] == 0) {
            // Loop through the collumn
            for (int i=0;i<size-1;i++) {
                // If the next slot is taken, but the current one is free. Insert the token here.
                if (board[i+1][move] != 0 && board[i][move] == 0) {
                    board[i][move] = player;
                    // Breaks the loop so it wont iterate more.
                    break;
                }
                // If we reach the bottom most position and its empty. Insert the token here.
                if (i == size-2 && board[i+1][move] == 0) {
                    board[i+1][move] = player;
                }
            }
        }    
    }    
    // Checks if token is supposed to go from the left
    if (side == 'L') {
        // Only inserts token if left of the row is empty
        if (board[move][0] == 0) {  
            // Loop through the row
            for (int i=0;i<size-1;i++) {
                // If the next slot is taken, but the current one is free. Insert the token here.
                if (board[move][i+1] != 0 && board[move][i] == 0) {
                    board[move][i] = player;
                    // Breaks the loop so it wont iterate more.
                    break;
                }
                // If we reach the right most position and its empty. Insert the token here.
                if (i == size-2 && board[move][i+1] == 0) {
                    board[move][i+1] = player;
                }
            }
        }       
    }
    // Checks if token is supposed to go from the right
    if (side == 'R') {
        // Only inserts token if right of the row is empty
        if (board[move][size-1] == 0) {
            // Loop through the row
            for (int i=size-1;i>0;i--) {
                // If the next slot is taken, but the current one is free. Insert the token here.
                if (board[move][i-1] != 0 && board[move][i] == 0) {
                    board[move][i] = player;
                    // Breaks the loop so it wont iterate more.
                    break;
                }
                // If we reach the left most position and its empty. Insert the token here.
                if (i == 1 && board[move][i-1] == 0) {
                    board[move][i-1] = player;
                }
            }
        }
    }
    // Checks if token is supposed to go from the bottom
    if (side == 'B') {
        // Only inserts token if bottom of the collumn is empty
        if (board[size-1][move] == 0) {
            // Loop through the collumn
            for (int i=size-1;i>0;i--) {
                // If the next slot is taken, but the current one is free. Insert the token here.
                if (board[i-1][move] != 0 && board[i][move] == 0) {
                    board[i][move] = player;
                     // Breaks the loop so it wont iterate more.
                    break;
                }
                // If we reach the top most position and its empty. Insert the token here.
                if (i == 1 && board[i-1][move] == 0) {
                    board[i-1][move] = player;
                }
            }
        }    
    }
}

// Removes the players token from specified side and slot, then shifts the remaining pieces to fill that space.
void PopOut(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player) {
    
    // Start at 0, to check first slot
    int i = 0;
    
    // Checks if token is supposed to be removed from the top
    if (side == 'T') {
        // Checks if its the players token
        if (board[0][move] == player) {
            // Loops through each slot
            while (board[i][move] != 0) {
                // If it reaches the end, without encountering a 0. Sets the slot as 0 and stops.
                if (i==size-1) {
                    board[i][move] = 0;
                    break;
                }
                // Copys the next piece onto the current piece
                board[i][move] = board[i+1][move];
                // Increment to next slot
                i++;
            }
        }
    }   
    
    // Resets, at 0, to check first slot
    i = 0;
    
    // Checks if token is supposed to be removed from the left
    if (side == 'L') {
        // Checks if its the players token
        if (board[move][0] == player) {
            // Loops through each slot
            while (board[move][i] != 0) {
                // If it reaches the end, without encountering a 0. Sets the slot as 0 and stops.
                if (i==size-1) {
                    board[move][i] = 0;
                    break;
                }
                // Copys the next piece onto the current piece
                board[move][i] = board[move][i+1];
                // Increment to next slot
                i++;
            }
        }
    }  
    
    // Resets, at size -1, to check first slot on the right
    i = size - 1;
    
    // Checks if token is supposed to be removed from the right
    if (side == 'R') {
        // Checks if its the players token
        if (board[move][size-1] == player) {
            // Loops through each slot
            while (board[move][i] != 0) {
                // If it reaches the end, without encountering a 0. Sets the slot as 0 and stops.
                if (i==0) {
                    board[move][i] = 0;
                    break;
                }
                 // Copys the next piece onto the current piece
                board[move][i] = board[move][i-1];
                // Decrement to next slot
                i--;
            }
        }
    } 
    
    // Resets, at size -1, to check first slot on the right
    i = size - 1;
    // Checks if token is supposed to be removed from the bottom
    if (side == 'B') {
        // Checks if its the players token
        if (board[size-1][move] == player) {
            // Loops through each slot
            while (board[i][move] != 0) {
                // If it reaches the end, without encountering a 0. Sets the slot as 0 and stops.
                if (i==0) {
                    board[i][move] = 0;
                    break;
                }
                // Copys the next piece onto the current piece
                board[i][move] = board[i-1][move];
                // Decrement to next slot
                i--;
            }
        }
    }

}

// Preforms either a Popin/Popout/neither, depending on the state of the board
void MakeMove(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player) {
    
    // Checks if token is supposed to be removed/added from the top
    if (side == 'T') {
        // If slot is empty, add token
        if (board[0][move] == 0) {
            PopIn(board, size, side, move, player);
        }
        
        // If slot is contains players token, remove it
        else if (board[0][move] == player) {
            PopOut(board, size, side, move, player);
        }
    }
    
    // Checks if token is supposed to be removed/added from the left
    if (side == 'L') {
        // If slot is empty, add token
        if (board[move][0] == 0) {
            PopIn(board, size, side, move, player);
        }
        
        // If slot is contains players token, remove it
        else if (board[move][0] == player) {
            PopOut(board, size, side, move, player);
        }
    }
    
    // Checks if token is supposed to be removed/added from the right
    if (side == 'R') {
        // If slot is empty, add token
        if (board[move][size-1] == 0) {
            PopIn(board, size, side, move, player);
        }
        
        // If slot is contains players token, remove it
        else if (board[move][size-1] == player) {
            PopOut(board, size, side, move, player);
        }
    }
    
    // Checks if token is supposed to be removed/added from the bottom
    if (side == 'B') {
        // If slot is empty, add token
        if (board[size-1][move] == 0) {
            PopIn(board, size, side, move, player);
        }
        
        // If slot is contains players token, remove it
        else if (board[size-1][move] == player) {
            PopOut(board, size, side, move, player);
        }
    }
    
}
// Checks wether the game is a draw, won, lost, or continuing
// Draw = 3, PlayerTwoWin = 2, PlayerOwnWin = 1, NoWin = 0, (values returned)
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size) {
    
    // Flags to check if a player has a winning configuation
    int PlayerOneWin = 0;
    int PlayerTwoWin = 0;
    
    // Loops through every element
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            
            // Checks if a winning sequence is found for the current element for player One and Two
            if (FourInARow(board, size, i, j) == 1) {
                // If found set to one, to set flag
                PlayerOneWin = 1; 
            }
            if (FourInARow(board, size, i, j) == 2) {
                // If found set to one, to set flag
                PlayerTwoWin = 1;
            }
                
        }
        
    }
    
    // If both players have won, = draw, return 3
    if (PlayerOneWin && PlayerTwoWin) {
        return 3;
    }
    else {
        
        // Return 1 if player one only won
        if (PlayerOneWin) {
            return 1;
        }
        
        // Return 2, if player two only won
        if (PlayerTwoWin) {
            return 2;
        }
        
        // Return 0, if nobody won/continuing
        else {
            return 0;
        }
    }
    
    
    
}
// Prints the board "prettier"
void PrintBoard(int board[MAX_SIZE][MAX_SIZE], int size) {
    
    // First row for T
    printf("-- ");
    for (int i=0;i<size;i++) {
        printf("T ");
    }
    printf("--\n-- ");
    
    // Collumn Numbers
    for (int i=0;i<size;i++) {
        printf("%d ",i);
    }
    printf("--\n");
    for (int i=0;i<size;i++) {
        
        // Row Number with L
        printf("L%d ",i);
        for (int j=0;j<size;j++) {
            
            // Checks if the cell is empty, then prints .
            if (board[i][j] == 0) {
                printf(". ");
            }
            
            // Checks if the cell is player one's, then prints X
            if (board[i][j] == 1) {
                printf("X ");
            }
            
            // Checks if the cell is player two's, then prints O
            if (board[i][j] == 2) {
                printf("O ");
            }
        }
        
        // Row Number with R
        printf("%dR\n",i);
    }
    printf("-- ");
    
    // Collumn Numbers
    for (int i=0;i<size;i++) {
        printf("%d ",i);
    }
    printf("--\n-- ");
    
    // Last row for B
    for (int i=0;i<size;i++) {
        printf("B ");
    }
    printf("--\n");
    
    
    
}
/*********************************************************************************/


/*********************************************************************************/
/*********************************************************************************/
/*** The following functions support an interactive game of Connect Four ***/
/*********************************************************************************/
/*********************************************************************************/

/*********************************************************************************/
/** GetMove ** /
/** This function is called when a human player is asked to enter their move.  The character
(representing the side of the board) and the digit (representing the row/column) are
returned via the pointers *side and *move.
/*********************************************************************************/
void GetMove(char *side, int *move, int player)
{
	char a = ' ';
	char b = ' ';
	printf("Player %d: enter move [side/position]: ", player);
	while (!(a == 'T' || a == 'L' || a == 'R' || a == 'B')) {
		scanf("%c", &a);
	}
	while (!(b >= '0' && b <= '9')) {
		scanf("%c", &b);
	}
	*side = a;
	*move = (int)(b - '0');
}

/*********************************************************************************/
/** GetMoveBot1 ** /
/** This function is called when the first bot (Bot 1) is asked to select a move.
The function is given the current configuration of the board, and its chosen move
is returned via the pointers *side and *move. 
/*********************************************************************************/
void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int rand_move;
	int rand_side;
	int End = 0; // Allows while loop to keep looping until condition met!
	player = board[0][0]; // statement to prevent compiler warning
	int count = 0;
	
	
		
	// Loops until a condition is met!
	while (End == 0 && count < 100) {
		rand_side = rand() % 4;
		rand_move = rand() % size;
		*move = rand_move;
		count++;
		// If the top is empty, and the current side is Top then run!
		if (board[0][*move] == 0 && rand_side == 0) {
			*side = 'T';
			End = 1;	
		}
		
		// If the bottom is empty, and the current side is Bottom then run!
		if (board[size-1][*move] == 0 && rand_side == 1) {
			*side = 'B';
			End = 1;	
		}
		
		// If the left is empty, and the current side is Left then run!
		if (board[*move][0] == 0 && rand_side == 2) {
			*side = 'L';
			End = 1;	
		}
		// If the right is empty, and the current side is Right then run!
		if (board[*move][size-1] == 0 && rand_side == 3) {
			*side = 'R';
			End = 1;	
		}
		
		// If no conditon is met, values are randomised again!
	}	
		
}

/*********************************************************************************/
/** GetMoveBot2 ** /
/** This function is called when the second bot (Bot 2) is asked to select a move.
The function is given the current configuration of the board, and its chosen move
is returned via the pointers *side and *move. 
/*********************************************************************************/
#include <stdlib.h>

#define MAX_SIZE 10

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
    int opponent = (player == 1) ? 2 : 1;
    int best_col = -1;

    // Try every column twice: first for win, then for block
    for (int check = 0; check < 2 && best_col == -1; check++) {
        int target = (check == 0) ? player : opponent;
        for (int c = 0; c < size; c++) {
            int r = -1;
            for (int i = size - 1; i >= 0; i--) if (board[i][c] == 0) { r = i; break; }
            if (r == -1) continue;

            // Count 4 in all directions without editing board
            int dirs[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
            for (int d = 0; d < 4; d++) {
                int count = 1;
                for (int s = -1; s <= 1; s += 2) {
                    int dr = dirs[d][0]*s, dc = dirs[d][1]*s;
                    int rr = r+dr, cc = c+dc;
                    while (rr>=0 && rr<size && cc>=0 && cc<size && board[rr][cc]==target) {
                        count++;
                        rr += dr; cc += dc;
                    }
                }
                if (count >= 4) { best_col = c; break; }
            }
        }
    }

    // Otherwise random
    if (best_col == -1)
        best_col = rand() % size;

    *side = 'T';
    *move = best_col;
}


/*********************************************************************************/
/** PlayOneGame ** /
/** This function plays one game of Connect Four.  The starting player (either 1 
or 2) is provided as input.  This function returns the player who won the game.
/*********************************************************************************/
int PlayOneGame(int startingPlayer, int size, int gameType)
{
	int board[MAX_SIZE][MAX_SIZE];
	int player, gameOver, move;
	char side;

	player = startingPlayer;
	gameOver = 0;

	// Initialise the board, and if a human is playing then display the board.
	InitialiseBoard(board, size, NULL);
	if (gameType != 3) {
		PrintBoard(board, size);
	}

	// Play one move at a time, displaying the board if necessary, until the game is over
	while (!gameOver) {
		if (gameType == 1) {
			GetMove(&side, &move, player);
		} else if (gameType == 2) {
			if (player == 1) {
				GetMove(&side, &move, player);
			} else {
				GetMoveBot1(board, size, player, &side, &move);
				printf("Bot has decided to move: %c %d\n", side, move);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(board, size, player, &side, &move);
			} else {
				GetMoveBot2(board, size, player, &side, &move);
			}
		}

		MakeMove(board, size, side, move, player);
		gameOver = CheckGameOver(board, size);

		if (gameType != 3) {
			PrintBoard(board, size);
		}
		if (!gameOver) {
			player = 3 - player;
		}
	}
	return gameOver;
}

/*********************************************************************************/
/** PlayOneGame ** /
/** This function plays Connect Four.  The user can choose the size of the board, who the
players will be (human or bot) and how many games will be played (if the bots are competing).
/*********************************************************************************/
void PlayConnectFour(void)
{
	int size, gameType, numberOfGames, result;
	int i, wins1, wins2, draws, player;

	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	// Prompt the user for the board size
	printf("\n\n==================");
	printf("\nEnter board size: ");
	scanf("%d", &size);

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	wins1 = 0;
	wins2 = 0;
	draws = 0;

	// Player 1 will always start the first game
	// If a tournament is being played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, size, gameType);
		if (result == 1) {
			wins1++;
		} else if (result == 2) {
			wins2++;
		} else {
			draws++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// If a single game was played, show the result:
	if (gameType != 3) {
		if (result == 3) {			
			printf("\nGame over! The game was a draw!\n\n");
		} else {
			printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
		}
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d / Draws = %d\n\n", numberOfGames, wins1, wins2, draws);
	}
}



/*********************************************************************************/
int main(void)
{
	printf("ENGGEN131 Project - Semester Two - 2025\n");
	printf("                                 _      __                 \n");
	printf("                                | |    / _|                \n");
	printf("  ___ ___  _ __  _ __   ___  ___| |_  | |_ ___  _   _ _ __ \n");
	printf(" / __/ _ \\| '_ \\| '_ \\ / _ \\/ __| __| |  _/ _ \\| | | | '__|\n");
	printf("| (_| (_) | | | | | | |  __/ (__| |_  | || (_) | |_| | |   \n");
	printf(" \\___\\___/|_| |_|_| |_|\\___|\\___|\\__| |_| \\___/ \\__,_|_|   \n\n");

	PlayConnectFour();

	return 0;
}
