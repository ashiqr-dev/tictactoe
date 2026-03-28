/*
 * WARNING: dont enter a character it will freak out.
 *
 * FIX: fgets and sscanf for input validation
 */

#include <stdbool.h>
#include <stdio.h>

int board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void print_board();
bool update_board(int row, int col, bool turn);
int check_board();

int get_row();
int get_col();

int main(void)
{
    printf("TIC TAC TOE\n\n");
    print_board();

    bool turn = false;

    // game loop
    while (1) {
        printf("\nPLAYER %d:\n", (int)turn + 1);
        int user_row = get_row();

        int user_col = get_col();

        bool ret = update_board(user_row, user_col, turn);
        while (!ret) {
            printf("\nSquare is already taken.\n");
            int user_row = get_row();
            int user_col = get_col();
            ret = update_board(user_row, user_col, turn);
        }
        puts("");
        print_board();

        int player = check_board();
        if (player != 0) {
            if (player == 3) {
                printf("\nDRAW!\n");
                break;
            }
            printf("\nPLAYER %d WON!\n", player);
            break;
        }

        turn = !turn;
    }

    return 0;
}

void print_board()
{
    char turn = ' ';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (board[i][j]) {
            case 0:
                turn = '-';
                break;
            case 1:
                turn = 'X';
                break;
            case 2:
                turn = 'O';
                break;
            }
            printf("|%c", turn);
        }
        printf("|\n");
    }
}

bool update_board(int row, int col, bool turn)
{
    if (board[row - 1][col - 1] == 0) {
        board[row - 1][col - 1] = (int)turn + 1;
        return true;
    } else {
        return false;
    }
}

int check_board()
{
    /* int board[3][3] = {
     * {00, 01, 02},
     * {10, 11, 12},
     * {20, 21, 22}
     * };
     */

    // check horizontals (3 cases)
    int i = 0;

    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    // check verticals (3 cases)
    for (i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    /* diag: \
     * board[0, 0] board [1, 1] board [2, 2]
     * diag: /
     * board [0, 2] board [1, 1] board [2, 0]
     */
    for (i = 0; i < 3; i += 2) {
        if (board[0][0 + i] == board[1][1] && board[1][1] == board[2][2 - i]) {
            return board[1][1];
        }
    }

    // now check for a draw
    bool draw = true;
    for (i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                draw = false;
                goto finish;
            }
        }
    }
finish:
    return draw ? 3 : 0;
}

int get_row()
{
    int user_row;
    printf("Which row?: ");
    scanf("%d", &user_row);
    while ((user_row < 1 || user_row > 3)) {
        printf("Please enter a valid row.\n");
        printf("Which row?: ");
        scanf("%d", &user_row);
    }
    return user_row;
}

int get_col()
{
    int user_col;
    printf("Which column?: ");
    scanf("%d", &user_col);
    while (user_col < 1 || user_col > 3) {
        printf("Please enter a valid column.\n");
        printf("Which row?: ");
        scanf("%d", &user_col);
    }
    return user_col;
}
