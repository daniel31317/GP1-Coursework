#include "Menu.h"


Menu::Menu()
{

}

GameState Menu::RunMenu()
{
    system("cls");
    std::cout << "Start Screen:\n";
    std::cout << "1. Player Space Invaders\n";
    std::cout << "2. Quit\n";
    std::cout << "Enter your choice: ";
    
    int choice;

    //will loop forever but there is returns so loop can be broken
    while (true)
    {
        if (std::cin >> choice) 
        {
            if (choice == 1)
            {
                system("cls");
                return GAMERUNNING;
            }
            else if (choice == 2)
            {
                system("cls");
                return QUITGAME;
            }
            else
            {
                std::cout << "Invalid Choice Please Choose 1 or 2:";
            }
        }
        else //if the player enters a string or char handle it
        {
            std::cout << "Invalid Input Please Try Again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
    }
}