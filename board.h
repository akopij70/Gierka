#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cassert>

#define NR_OF_ROWS 4
#define NR_OF_COLUMNS 8
#define MIDDLE_NR_OF_ROWS NR_OF_ROWS/2
#define MIDDLE_NR_OF_COLUMNS NR_OF_COLUMNS/2 -1
#define NUMBER_OF_FIELDS 3

class Field_on_the_board
{
    private:
    char boarder[NR_OF_ROWS][NR_OF_COLUMNS] = {" _____ ", "|     |", "|     |", "|_____|"};  //to są znaki do utworzenia jednego pola
    //char middle = boarder[MIDDLE_NR_OF_ROWS][MIDDLE_NR_OF_COLUMNS];
    public:
    /*char operator() (int i, int j) const 
    { 
        assert(((i >= 0) && i < (NR_OF_ROWS)) && ((j >= 0) && j < (NR_OF_COLUMNS)));
        return boarder[i][j];
    }
    */
    char& ChangeMiddle() {return boarder[MIDDLE_NR_OF_ROWS][MIDDLE_NR_OF_COLUMNS];}
    char ShowMiddle() const {return boarder[MIDDLE_NR_OF_ROWS][MIDDLE_NR_OF_COLUMNS];}
    void ClearMiddle() {boarder[MIDDLE_NR_OF_ROWS][MIDDLE_NR_OF_COLUMNS] = ' ';}
    void ShowRow(int number_of_row) 
    {
        assert(number_of_row >= 0 && number_of_row < NR_OF_ROWS);
        for (int i = 0; i < NR_OF_COLUMNS; i++)
        {
            std::cout << boarder[number_of_row][i];
        }
    }
};

class Board
{
    private:
    char player_team;
    char computer_team;
    int best_move[2];
    public:
    Field_on_the_board all_fields[NUMBER_OF_FIELDS][NUMBER_OF_FIELDS];

    void SetGame();
    void ShowBoard();
    void SetTeams(char player_choice);
    void PlayerTurn();
    bool GetDestinationColumn(int& destination_column);
    bool GetDestinationRow(int& destination_row);
    bool CheckDestination(int& destination);
    bool IsTheFieldEmpty(const int& row, const int& column);


    void TryToBitAI()
    {
        SetGame();
        ShowBoard();
        while (isMovesLeft() && WhoIsWinning() == 0)
        {
            PlayerTurn();
            ShowBoard();
            AITurn();
            ShowBoard();
        }
        if (WhoIsWinning() == 10)
            std::cout << "Komputer wygral\n";
        else if (WhoIsWinning() == - 10)
            std::cout << "Wygraleas z komputerem\n";
        else 
            std::cout << "Remis";
    }

    int AITurn() {FindBestMove(); Move(computer_team, best_move[0], best_move[1]);}

    void Move(const char& team, const int& destination_row, const int& destination_column)
    {
        all_fields[destination_row][destination_column].ChangeMiddle() = team;
    }

/*
Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			// Check if cell is empty
			if (board[i][j]=='_')
			{
				// Make the move
				board[i][j] = player;

				// compute evaluation function for this
				// move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = '_';

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	printf("The value of the best Move is : %d\n\n",
			bestVal);

	return bestMove;
}
*/

    int FindBestMove()
    {
        int current_score = -1000;
        for (int i = 0; i < NUMBER_OF_FIELDS; i++)
        {
            for (int j = 0; j < NUMBER_OF_FIELDS; j++)
            {
                if (all_fields[i][j].ShowMiddle() == ' ')
                {
                    all_fields[i][j].ChangeMiddle() = computer_team;
                    int new_score = MiniMax(0, false);   // AI zasymulowalo ruch, teraz pora na symulacje ruchu gracza
                    all_fields[i][j].ClearMiddle();
                    if (new_score > current_score)
                    {
                        current_score = new_score;
                        best_move[0] = i;
                        best_move[1] = j;
                    }
                }
            }
        }
    }

    bool isMovesLeft()
    {
        for (int i = 0; i < NUMBER_OF_FIELDS; i++)
            for (int j = 0; j < NUMBER_OF_FIELDS; j++)
                if (all_fields[i][j].ShowMiddle() == ' ')
                    return true;
        return false;
    }


    int WhoIsWinning()
    {
        for (int i = 0; i < NUMBER_OF_FIELDS; i++)
        {
            if (all_fields[i][0].ShowMiddle() == all_fields[i][1].ShowMiddle() && all_fields[i][1].ShowMiddle() == all_fields[i][2].ShowMiddle())
            {
                if (all_fields[i][0].ShowMiddle() == computer_team)
                    return +10;
                else if (all_fields[i][0].ShowMiddle() == player_team)
                    return -10;
            }
        }


        for (int i = 0; i < NUMBER_OF_FIELDS; i++)
	    {
            if (all_fields[0][i].ShowMiddle() == all_fields[1][i].ShowMiddle() && all_fields[1][i].ShowMiddle() == all_fields[2][i].ShowMiddle())
            {
                if (all_fields[0][i].ShowMiddle() == computer_team)
                    return +10;

                else if (all_fields[0][i].ShowMiddle() == player_team)
                    return -10;
            }
        }

        if (all_fields[0][0].ShowMiddle() == all_fields[1][1].ShowMiddle() && all_fields[1][1].ShowMiddle() == all_fields[2][2].ShowMiddle())
        {
            if (all_fields[0][0].ShowMiddle() == computer_team)
                return +10;
            else if (all_fields[0][0].ShowMiddle() == player_team)
                return -10;
        }

        if (all_fields[0][2].ShowMiddle() == all_fields[1][1].ShowMiddle() && all_fields[1][1].ShowMiddle() == all_fields[2][0].ShowMiddle())
        {
            if (all_fields[0][2].ShowMiddle() == computer_team)
                return +10;
            else if (all_fields[0][2].ShowMiddle() == player_team)
                return -10;
        }
	    // Else if none of them have won then return 0
	    return 0;
    }

/*
    int evaluate(char b[3][3])
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
		if (b[row][0]==b[row][1] &&
			b[row][1]==b[row][2])
		{
			if (b[row][0]==player)
				return +10;
			else if (b[row][0]==opponent)
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		if (b[0][col]==b[1][col] &&
			b[1][col]==b[2][col])
		{
			if (b[0][col]==player)
				return +10;

			else if (b[0][col]==opponent)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
		if (b[0][0]==player)
			return +10;
		else if (b[0][0]==opponent)
			return -10;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
		if (b[0][2]==player)
			return +10;
		else if (b[0][2]==opponent)
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}
*/
    

/*    
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	// If Maximizer has won the game return his/her
	// evaluated score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie
	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = player;

					// Call minimax recursively and choose
					// the maximum value
					best = max( best,
						minimax(board, depth+1, !isMax) );

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = opponent;

					// Call minimax recursively and choose
					// the minimum value
					best = min(best,
						minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}
*/
    int MiniMax(int depth, bool maximizing) 
    {
        int result = WhoIsWinning();

        if (result == 10 || result == -10)
            return result;

        if (isMovesLeft() == false)
		    return 0;

        

        if (maximizing)
        {
            int current_score = -1000;
            for (int i = 0; i < NUMBER_OF_FIELDS; i++)
            {
                for (int j = 0; j < NUMBER_OF_FIELDS; j++)
                {
                    if (all_fields[i][j].ShowMiddle() == ' ')
                    {
                        all_fields[i][j].ChangeMiddle() = computer_team;
                        int new_score = MiniMax(depth + 1, false);
                        all_fields[i][j].ClearMiddle();
                        if (new_score > current_score)
                            current_score = new_score;
                    }
                }
            }
            return current_score;
        }
        else
        {
            int current_score = 10000;
            for (int i = 0; i < NUMBER_OF_FIELDS; i++)
            {
                for (int j = 0; j < NUMBER_OF_FIELDS; j++)
                {
                    if (all_fields[i][j].ShowMiddle() == ' ')
                    {
                        all_fields[i][j].ChangeMiddle() = player_team;
                        int new_score = MiniMax(depth + 1, true);
                        all_fields[i][j].ClearMiddle();
                        if (new_score < current_score)
                            current_score = new_score;
                    }
                }
            }
            return current_score;
        }
    }

};

bool TeamVeryficationResult(char choice);
#endif
    /*int WhoIsWinning() 
    {
        int j;
        char symbol_to_compare;

        for (int i = 0; i < NUMBER_OF_FIELDS; i++) 
        {
            symbol_to_compare = all_fields[i][0].ShowMiddle();
            j = 0;
            while (j < NUMBER_OF_FIELDS && all_fields[i][j].ShowMiddle() == symbol_to_compare)
                j++;
            if (j == 3)
            {
                if (symbol_to_compare == computer_team)
                    return 1;
                else if (symbol_to_compare == player_team)
                    return -1;
                //else return 0;
            }
        }

        for (int i = 0; i < NUMBER_OF_FIELDS; i++) 
        {
            symbol_to_compare = all_fields[0][i].ShowMiddle();
            j = 0;
            while (j < NUMBER_OF_FIELDS && all_fields[j][i].ShowMiddle() == symbol_to_compare)
                j++;
            if (j == 3)
            {
                if (symbol_to_compare == computer_team)
                    return 1;
                else if (symbol_to_compare == player_team)
                    return -1;
                //else return 0;
            }
        }
        symbol_to_compare = all_fields[1][1].ShowMiddle();
        for (int i = 0; i < NUMBER_OF_FIELDS, all_fields[i][i].ShowMiddle() == symbol_to_compare; i++) 
        {
            if (i == 2)
            {
                if (symbol_to_compare == computer_team)
                    return 1;
                else if (symbol_to_compare == player_team)
                    return -1;
                //else 
                    //return 0;
            }
        }
        if (all_fields[2][0].ShowMiddle() == all_fields[1][1].ShowMiddle() && all_fields[0][2].ShowMiddle() == all_fields[1][1].ShowMiddle())
        {
            symbol_to_compare = all_fields[1][1].ShowMiddle();
            if (symbol_to_compare == computer_team)
                return 1;
            else if (symbol_to_compare == player_team)
                return -1;
        }
    }
    */
//bool TeamVeryficationResult(char choice);