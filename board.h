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
    
    public:
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
    void TryToBitAI();
    int AITurn() {FindBestMove(); Move(computer_team, best_move[0], best_move[1]);}
    void Move(const char& team, const int& destination_row, const int& destination_column)
    {
        all_fields[destination_row][destination_column].ChangeMiddle() = team;
    }
    void FindBestMove();
    bool IsAnyFieldEmpty();
    int WhoIsWinning();
    int CheckHorizontal();
    int CheckVertical();
    int CheckDiagonals();
    int MiniMax(int depth, bool maximizing);
};

bool TeamVeryficationResult(char choice);
#endif