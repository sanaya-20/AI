import java.util.Scanner;

public class assi1 {
    public char[][] board; //declaring Tic Tac Toe board
    public char currentPlayer; //Current player Character - takes X or O

    public assi1() { //constructor
        board = new char[3][3]; 
        currentPlayer = 'X';
        initializeBoard();
    }

    public void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
    } //initialising board by setting all positions as -

    public void printBoard() {
        System.out.println("Current Game Board:");
        System.out.println("-------------------");
        for (int i = 0; i < 3; i++) {
            System.out.print("|");
            for (int j = 0; j < 3; j++) {
                System.out.print(" " + board[i][j] + " |");
            }
            System.out.println();
            System.out.println("-------------------");
        }
    }//printing the board

    public boolean isBoardFull() {
        for (char[] row : board) {
            for (char cell : row) {
                if (cell == '-') {
                    return false;
                }
            }
        }
        return true;
    }//checking if board is full

    public boolean isGameOver() {
        return hasPlayerWon('X') || hasPlayerWon('O') || isBoardFull();
    }//checking if Game is Over

    public boolean hasPlayerWon(char symbol) {
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
            return true; 
        }
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
            return true;
        }
 
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
                return true;
            }
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
                return true;
            }
        }//checks if player has won

        return false;
    }

    public void makeMove(int row, int col) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '-') {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    public void play() {
        Scanner scanner = new Scanner(System.in);

        while (!isGameOver()) {
            printBoard();

            if (currentPlayer == 'X') {
                System.out.println("Player X's turn. Enter row and column (0-2):");
                int row = scanner.nextInt();
                int col = scanner.nextInt();
                makeMove(row, col);
            } else {
                System.out.println("Computer's turn (O):");
                makeComputerMove();
                currentPlayer = 'X';
            } 

            if (isGameOver()) {
                break;
            }
        }

        System.out.println("Final board:");
        printBoard();

        if (hasPlayerWon('X')) {
            System.out.println("Player X wins!");
        } else if (hasPlayerWon('O')) {
            System.out.println("Computer wins!");
        } else {
            System.out.println("It's a draw!");
        }

        scanner.close();
    }

    public void makeComputerMove() {
        // try win
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = currentPlayer;
                    if (hasPlayerWon(currentPlayer)) {
                        return;
                    }
                    board[i][j] = '-';
                }
            }
        }

        // block win
        char opponentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = opponentPlayer;
                    if (hasPlayerWon(opponentPlayer)) {
                        board[i][j] = currentPlayer;
                        return;
                    }
                    board[i][j] = '-';
                }
            }
        }
        //first empty
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = currentPlayer;
                    return;
                }
            }
        }
    }

    public static void main(String[] args) {
        assi1 game = new assi1();
        game.play();
    }
}