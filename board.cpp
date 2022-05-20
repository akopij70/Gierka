#include "board.h"

void Board::TryToBitAI()
{
    SetGame();
    ShowBoard();
    while (IsAnyFieldEmpty() && WhoIsWinning() == 0)
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

void Board::FindBestMove()
{
    int current_score = -1000;
    for (int i = 0; i < NUMBER_OF_FIELDS; i++)
    {
        for (int j = 0; j < NUMBER_OF_FIELDS; j++)
        {
            if (IsTheFieldEmpty(i, j))
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

bool Board::IsTheFieldEmpty(const int& row, const int& column)
{
    if (all_fields[row][column].ShowMiddle() == ' ')
        return true;
    else 
        return false;
}

bool Board::IsAnyFieldEmpty()
{
    for (int i = 0; i < NUMBER_OF_FIELDS; i++)
    {   
        for (int j = 0; j < NUMBER_OF_FIELDS; j++)
        {   
            if (all_fields[i][j].ShowMiddle() == ' ')
                return true;
        }
    }
    return false;
}


int Board::MiniMax(int depth, bool maximizing) 
{
    int result = WhoIsWinning();

    if (result == 10 || result == -10)
        return result;

    if (IsAnyFieldEmpty() == false)
		return 0;

    if (maximizing)
    {
        int current_score = -1000;
        for (int i = 0; i < NUMBER_OF_FIELDS; i++)
        {
            for (int j = 0; j < NUMBER_OF_FIELDS; j++)
            {
                if (IsTheFieldEmpty(i, j))
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
                if (IsTheFieldEmpty(i,j))
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

int Board::WhoIsWinning()
{
    int result;

    result = CheckHorizontal();
    if (result != 0)
        return result;

    result = CheckVertical();
    if (result != 0)
        return result;

    result = CheckDiagonals();
    if (result != 0)
        return result;
            
    return 0;
}

int Board::CheckHorizontal()
{
    char symbols_to_compare[NUMBER_OF_FIELDS];
    bool are_symbols_the_same;
        
    for (int i = 0; i < NUMBER_OF_FIELDS; i++)
    {
        are_symbols_the_same = true;
        for (int j = 0; j < NUMBER_OF_FIELDS; j++)
        {
            symbols_to_compare[j] = all_fields[i][j].ShowMiddle();
            if (symbols_to_compare[i] == ' ')
                are_symbols_the_same = false;
            else if (j > 0 && are_symbols_the_same == true && symbols_to_compare[j] == symbols_to_compare[j-1])
                are_symbols_the_same = true;
            else if (j > 0)
                are_symbols_the_same = false;
        }
        if (symbols_to_compare[0] == computer_team && are_symbols_the_same == true)
            return +10;
        if (symbols_to_compare[0] == player_team && are_symbols_the_same == true)
            return -10;
    }
    return 0;
}

int Board::CheckVertical()
{
    char symbols_to_compare[NUMBER_OF_FIELDS];
    bool are_symbols_the_same;

    for (int i = 0; i < NUMBER_OF_FIELDS; i++)
    {
        are_symbols_the_same = true;
        for (int j = 0; j < NUMBER_OF_FIELDS; j++)
        {
            symbols_to_compare[j] = all_fields[j][i].ShowMiddle();
            if (symbols_to_compare[i] == ' ')
                are_symbols_the_same = false;
            else if (j > 0 && are_symbols_the_same == true && symbols_to_compare[j] == symbols_to_compare[j-1])
                are_symbols_the_same = true;
            else if (j > 0)
                are_symbols_the_same = false;
        }
        if (symbols_to_compare[0] == computer_team && are_symbols_the_same == true)
            return +10;
        if (symbols_to_compare[0] == player_team && are_symbols_the_same == true)
            return -10;
    }
    return 0;
}

int Board::CheckDiagonals()
{
    char symbols_to_compare[NUMBER_OF_FIELDS];
    bool are_symbols_the_same = true;

    for (int i = 0; i < NUMBER_OF_FIELDS; i++)
    {
        symbols_to_compare[i] = all_fields[i][i].ShowMiddle();
        if (symbols_to_compare[i] == ' ')
            are_symbols_the_same = false;
        else if (i > 0 && are_symbols_the_same == true && symbols_to_compare[i] == symbols_to_compare[i-1])
            are_symbols_the_same = true;
        else if (i > 0)
            are_symbols_the_same = false;
    }
    if (symbols_to_compare[NUMBER_OF_FIELDS - 1] == computer_team && are_symbols_the_same == true)
        return +10;
    if (symbols_to_compare[NUMBER_OF_FIELDS - 1] == player_team && are_symbols_the_same == true)
        return -10;
        

    are_symbols_the_same = true;
    for (int i = 0, j = (NUMBER_OF_FIELDS - 1); i < NUMBER_OF_FIELDS; i++, j--)
    {
        symbols_to_compare[i] = all_fields[i][j].ShowMiddle();
        if (symbols_to_compare[i] == ' ')
            are_symbols_the_same = false;
        else if (i > 0 && are_symbols_the_same == true && symbols_to_compare[i] == symbols_to_compare[i-1])
            are_symbols_the_same = true;
        else if (i > 0)
            are_symbols_the_same = false;
    }
    if (symbols_to_compare[NUMBER_OF_FIELDS - 1] == computer_team && are_symbols_the_same == true)
        return +10;
    if (symbols_to_compare[NUMBER_OF_FIELDS - 1] == player_team && are_symbols_the_same == true)
        return -10;

    return 0;
}
