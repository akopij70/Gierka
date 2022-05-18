#include "board.h"

void Board::ShowBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < NR_OF_ROWS; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                all_fields[i][k].ShowRow(j);
            }
            std::cout << std::endl;
        }
    }
}

void Board::SetGame()
{
    char player_choice;
    std::cout << "Wybierz kim chcesz byc:\n";
    std::cout << "Jezeli chcesz grac jako kolko wcisnij o\n";
    std::cout << "Jezeli chcesz grac jako krzyzyk wcisnij x\n";
    std::cout << "Potwierdz wybor przyciskiem ENTER\n";
    std::cin >> player_choice;
    while (TeamVeryficationResult(player_choice) == false)
        std::cin >> player_choice;
    SetTeams(player_choice);
    std::cout << "Grasz jako: " << player_team << std::endl;
}

bool TeamVeryficationResult(char choice)
{
    if (choice != 'o' && choice != 'x' && choice != 'O' && choice != 'X' )
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Nie rozpoznano wyboru. Ponow probe\n";
        return false;
    }
    else 
        return true;
}
void Board::SetTeams(char player_choice)
{
    if (player_choice == 'O' || player_choice == 'o')
    {
        player_team = 'O';
        computer_team = 'X';
    }
    else 
    {
        player_team = 'X';
        computer_team = 'O';
    }
}

void Board::PlayerTurn()
{
    int destination_row, destination_column;
    while (GetDestinationRow(destination_row) == false)
        ;
    while (GetDestinationColumn(destination_column) == false)
        ;
    if (IsTheFieldEmpty(destination_row, destination_column) == true)
        Move(player_team, destination_row, destination_column);
    else 
    {
        std::cout << "Zajete pole\n"; 
        PlayerTurn();
    }
}

bool Board::GetDestinationColumn(int& destination_column)
{
    std::cout << "Podaj kolumne, ktora chcesz zagrac:\n";
    std::cin >> destination_column;
    return CheckDestination(destination_column);  
}

bool Board::GetDestinationRow(int& destination_row)
{
    std::cout << "Podaj wiersz, ktory chcesz zagrac:\n";
    std::cin >> destination_row;
    return CheckDestination(destination_row);  
}

bool Board::CheckDestination(int& destination)
{
    if (destination <= NUMBER_OF_FIELDS && destination > 0)
    {
        destination--; 
        return true;
    }
    else 
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Nie rozpoznano wyboru. Ponow probe\n";
            return false;
        }
}

bool Board::IsTheFieldEmpty(const int& row, const int& column)
{
    if (all_fields[row][column].ShowMiddle() == ' ')
        return true;
    else 
        return false;
}