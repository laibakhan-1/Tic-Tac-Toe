#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class BOARD
{
public:
    void drawBoard(char board[3][3])
{
    system("cls"); //for clear screen.
    cout<<"\t============================="<<endl;
    cout << "\t\tTic Tac Toe"<<endl;
    cout<<"\t============================="<<endl;
    cout << "\tPlayer 1 (X)  -  Player 2 (O)" << endl << endl;
    cout << endl;

    cout << "\t\t     |     |     " << endl;
    cout << "\t\t  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;

    cout << "\t\t_____|_____|_____" << endl;
    cout << "\t\t     |     |     " << endl;

    cout << "\t\t  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;

    cout << "\t\t_____|_____|_____" << endl;
    cout << "\t\t     |     |     " << endl;
    cout << "\t\t  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;

    cout << "\t\t     |     |     " << endl << endl;
}
};

class GAME_MOVES
{
public:
    char turn; //for player turn that we already initialize with 'X' turn.
    int row, column; //instead of entering row and column we simplify it by simple enter the number using switch case.
    bool draw; //check conditions for draw or not.
    char board[3][3]; //for accessing location.
    int xMoves, oMoves; //to keep track of the number of moves made by each player ('X' ,'O').

    GAME_MOVES() {
        resetGame(); //for reset board to plat next game.
    }

    bool checkForWin()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) //for rows
                return true;
        }

        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) //for columns
                return true;
        }

        if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) //for diagnols
            return true;

        if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) //for diagnols
            return true;

        return false; //check if all conditions are false then return false.
    }

    bool checkForDraw()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'X' && board[i][j] != 'O') //to check whether the box are filled or not, if all box are not fill then no one is wining then it's draw.
                    return false;
            }
        }
        draw = true;
        return true;
    }

    void playerTurn()
    {
        int choice;
        cout << "\tPlayer " << turn << ", enter a number: ";
        cin >> choice;

        switch (choice)
        {
        case 1: row = 0; column = 0; break;
        case 2: row = 0; column = 1; break;
        case 3: row = 0; column = 2; break;
        case 4: row = 1; column = 0; break;
        case 5: row = 1; column = 1; break;
        case 6: row = 1; column = 2; break;
        case 7: row = 2; column = 0; break;
        case 8: row = 2; column = 1; break;
        case 9: row = 2; column = 2; break;
        default:
            cout << "Invalid move" << endl;
            playerTurn(); //to not stoped the game,and allow the player for next move.
            return; // Important to return after an invalid move
        }

        if (turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O') //we did it because the turn of next player is overwrite.
        {
            board[row][column] = 'X';
            turn = 'O'; //for turn of next player 'O'.
            xMoves++;
        }
        else if (turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O')
        {
            board[row][column] = 'O';
            turn = 'X'; //for turn of next player 'X'.
            oMoves++;
        }
        else
        {
            cout << "Invalid move, try again." << endl;
            playerTurn();
        }
    }

    void resetGame()  //Overall, the resetGame function ensures that all aspects of the game state are reset to their initial values, preparing the game for a new round of play.
    {
        turn = 'X'; //This sets the initial turn to player 'X'. The game always starts with player 'X'.
        draw = false; //Sets draw to false, indicating that the game is not a draw at the beginning.
        
        //These lines below reset the move counters for both players to zero.
        xMoves = 0; //Sets xMoves to 0, resetting the count of moves made by player 'X'.
        oMoves = 0;
        char initialBoard[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };  //During the resetGame function, this initialBoard array is used to reset the main game board (board) to its initial state. This is done using nested for loops to copy each element from initialBoard to the corresponding position in board.
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = initialBoard[i][j]; //These nested for loops copy the values from initialBoard to the main game board (board). This sets the board to its initial state, with each cell labeled with its corresponding number (1 to 9).
    }
};

class FILE_HANDLER {
public:
    void saveGameStats(char winner, int xMoves, int oMoves, int xWins, int oWins) {
        ofstream outFile("game_stats.txt", ios::app); // Append to the file instead of overwriting
        if (outFile.is_open()) {
            outFile << "Player " << winner << " wins!" << endl;
            outFile << "Player X moves: " << xMoves << endl;
            outFile << "Player O moves: " << oMoves << endl;
            outFile << "Player X wins: " << xWins << endl;
            outFile << "Player O wins: " << oWins << endl;
            if (xWins > oWins) {
                outFile << "Player X wins more games!" << endl;
            } else if (xWins < oWins) {
                outFile << "Player O wins more games!" << endl;
            } else {
                outFile << "Both players have won the same number of games!" << endl;
            }
            outFile.close();
        }
    }
};

int main() {
    GAME_MOVES game;
    BOARD board;
    FILE_HANDLER fileHandler;
    int gamesToPlay;
    int xWins = 0, oWins = 0; //Declares and initializes two integer variables to keep track of the number of wins for Player X and Player O, respectively.

    cout << "Enter the number of times you want to play the game: ";
    cin >> gamesToPlay;

    for (int i = 0; i < gamesToPlay; i++) {
        char lastTurn = 'X'; //Declares a character variable to keep track of the last player who made a move. It is initialized to 'X' because Player X starts the game

        while (!game.checkForWin() && !game.checkForDraw()) //if there is no winner nor a draw then call the board. A while loop that runs as long as there is no winner and the game is not a draw.
		{
            board.drawBoard(game.board); //Calls the drawBoard method of the BOARD class to display the current state of the game board.
            game.playerTurn(); //Calls the playerTurn method of the GAME_MOVES class to handle the current player's move.
            lastTurn = (game.turn == 'X') ? 'O' : 'X';  // Update lastTurn after each valid move.
        }

           //occurs after the game has concluded (either a win or a draw) and ensures that the final state of the board is displayed to the players.
        board.drawBoard(game.board); 

        if (game.checkForWin()) {
            cout << "Player " << lastTurn << " wins!" << endl;
            
            //Calls the saveGameStats method of the FILE_HANDLER class to save the game statistics to a file.
            fileHandler.saveGameStats(lastTurn, game.xMoves, game.oMoves, xWins, oWins); 
            
            //Updates the win count for the respective player
			if (lastTurn == 'X') {
                xWins++;
            } else {
                oWins++;
            }
        }
        else if (game.checkForDraw()) {
            cout << "It's a draw!" << endl;
            fileHandler.saveGameStats('D', game.xMoves, game.oMoves, xWins, oWins);
        }

        // Pause to display the result of the game
        system("pause");

        // Reset the game state for the next game
        game.resetGame();
    }

    return 0;
}
