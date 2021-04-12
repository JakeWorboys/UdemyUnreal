#include <iostream> 
#include <ctime>

void PrintOpeningMessage(int LevelDifficulty)
{
    std :: cout << "You are a secret agent trying to hack into a Level " << LevelDifficulty;
    std :: cout << " secure server inside an enemy base.\nYou pull out your hacking tool and plug it into the access point. It beeps briefly before the screen flashes white.\n";
}

bool PlayGame(int LevelDifficulty)
{
    PrintOpeningMessage(LevelDifficulty);

    int CodeA = rand() % LevelDifficulty + LevelDifficulty;
    int CodeB = rand() % LevelDifficulty + LevelDifficulty;
    int CodeC = rand() % LevelDifficulty + LevelDifficulty;
    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    std :: cout << "\n The hacking tool beeps once more as the screen displays clues to help you crack the encryption code;\n";
    std :: cout << "\n+ The code is three digits long";
    std :: cout << "\n+ The sum of the three numbers is: " << CodeSum;
    std :: cout << "\n+ The three numbers multiply together to equal: " << CodeProduct << std :: endl;

    int GuessA, GuessB, GuessC;
    std :: cin >> GuessA;
    std :: cin >> GuessB;
    std :: cin >> GuessC;
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
    std :: cout << "\nThe hacking tool beeps three more times...\n";
    std :: cout << "...\n";
    std :: cout << "...\n";
    std :: cout << "...\n";
    std :: cout << "\nSuccess! The code was correct! Hurry and grab the files before you get caught!\n \n \n \n";

    return true;
    }
    else
    {
    std :: cout << "\nThe hacking tool beeps three more times...\n";
    std :: cout << "...\n";
    std :: cout << "...\n";
    std :: cout << "...\n";
    std :: cout << "\nThe alarms are ringing, the code must have been wrong! Quick, run before they catch you!\n \n \n \n";

    return false;
    }
}

int main()
{
    srand(time(NULL));

    int LevelDifficulty = 1;
    int MaxDifficulty = 5;

    while (LevelDifficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std :: cin.clear();
        std :: cin.ignore();

        if (bLevelComplete)
        {
            ++LevelDifficulty;
        }
    }

    return 0;
}