#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rollDie() {
    return rand() % 6 + 1;
}

int player1 = 0, player2 = 0;

void printBoard() {
    int board[101],i;
    for (i = 1; i <= 100; i++) {
        board[i] = i;
    }

    int alt = 0, iterLR = 101, iterRL = 80, val = 100;
    while (val--) {
        if (alt == 0) {
            iterLR--;
            if (iterLR == player1) {
                printf("#P1 ");
            } else if (iterLR == player2) {
                printf("#P2 ");
            } else {
                printf("%d ", board[iterLR]);
            }

            if (iterLR % 10 == 1) {
                printf("\n\n");
                alt = 1;
                iterLR -= 10;
            }
        } else {
            iterRL++;
            if (iterRL == player1) {
                printf("#P1 ");
            } else if (iterRL == player2) {
                printf("#P2 ");
            } else {
                printf("%d ", board[iterRL]);
            }

            if (iterRL % 10 == 0) {
                printf("\n\n");
                alt = 0;
                iterRL -= 30;
            }
        }
        if (iterRL == 10) break;
    }
    printf("\n");
}

int movePlayer(int currentPlayer, int roll) {
    int newPosition = currentPlayer + roll;
    int snakesAndLadders[101] = {0};

    snakesAndLadders[6] = 40;   // Ladder from 6 to 46
    snakesAndLadders[23] = -10; // Snake from 23 to 13
    snakesAndLadders[45] = -7;  // Snake from 45 to 38
    snakesAndLadders[61] = -18; // Snake from 61 to 43
    snakesAndLadders[65] = -8;  // Snake from 65 to 57
    snakesAndLadders[77] = 5;   // Ladder from 77 to 82
    snakesAndLadders[98] = -10; // Snake from 98 to 88

    int newSquare = newPosition + snakesAndLadders[newPosition];
    if (newSquare > 100) {
        return currentPlayer; // Player cannot move beyond 100
    }
    return newSquare;
}

int main() {
    srand(time(0));
    int currentPlayer = 1;
    int won = 0;

    printf("Snake and Ladder Game\n");

    while (!won) {
        printf("\nPlayer %d, press Enter to roll the die...", currentPlayer);
        getchar(); // Wait for the player to press Enter
        int roll = rollDie();
        printf("You rolled a %d.\n", roll);

        if (currentPlayer == 1) {
            player1 = movePlayer(player1, roll);
            printf("Player 1 is now at square %d.\n\n", player1);
            printBoard();
            if (player1 == 100) {
                printf("Player 1 wins!\n");
                won = 1;
            }
        } else {
            player2 = movePlayer(player2, roll);
            printf("Player 2 is now at square %d.\n\n", player2);
            printBoard();
            if (player2 == 100) {
                printf("Player 2 wins!\n");
                won = 1;
            }
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch player
    }

    return 0;
}

