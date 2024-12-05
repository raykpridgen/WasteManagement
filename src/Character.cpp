#include "../inc/Character.hpp"
#include <iostream>
#include <tuple>
#include <thread>
#include <chrono>
namespace chants
{
    Character::Character(string name, int money, int businessLevel)
    {
        _name = name;
        _money = money;
        _businessLevel = businessLevel;
    }
    
    string Character::GetName()
    {
        return _name;
    }

    int Character::GetMoney()
    {
        return _money;
    }
    
    int Character::GetLevel()
    {
        return _businessLevel;
    }

    void Character::SetMoney(int amount)
    {
        _money = amount;
    }

    void Character::SetLevel(int newLevel)
    {
        _businessLevel = newLevel;

    }

    /**
     * Updates earned money for a character
     */
    void Character::cycleBusiness()
    {
        float currentMoney = this->GetLevel();
        float multiple = 1 / ((rand() % 12) + 2);
        currentMoney = currentMoney * multiple;
        this->SetMoney(this->GetMoney() + (int)currentMoney);
    }

    /**
     * Returns tuple of stress and money (stress, money)
     * Stress can go up or down
     * Money can be taken from or given to player
     */
    tuple<int, int> Character::interact() 
    {
        int health = 0;
        int stress = 0;
        int money = 0;
        // Non-money making characters (family, etc)
        if (this->GetLevel() < 0)
        {
            cout << this->GetName() << " greets you with a smile and a hug." << endl;
            cin.get();  // Wait for user input

            // Family
            if (this->GetName() == "Carmella Soprano" || this->GetName() == "AJ Soprano" || this->GetName() == "Meadow Soprano")
            {
                int randStress = rand() % 100;
                int randMoney = rand() % 6400;

                if (randStress < 30)
                {
                    cout << this->GetName() << " discusses some stressful family business with you. Your stress has increased.\n" << endl;
                    cin.get();  // Wait for user input
                    stress += (randStress % 2) + 1;

                }
                else if (randStress > 70)
                {
                    cout << "You spend quality time with " << this->GetName() << ". Your stress has decreased.\n" << endl;
                    cin.get();  // Wait for user input
                    stress -= (randStress % 2) + 1;
                }
                else if (randStress < 70 && randStress > 55)
                {
                    cout << this->GetName() << " asks you for " << randMoney << " dollars. You oblige.\n" << endl;
                    cin.get();  // Wait for user input
                    money -= randMoney;
                }
                else
                {
                    cout << "You spend quality time with " << this->GetName() << ". You feel indifferent.\n" << endl;
                    cin.get();  // Wait for user input
                }
            }

            // Dr. Melfi - always decrease stress
            else if (this->GetName() == "Dr. Melfi")
            {
                cout << "You have a productive therapy session. Your stress has decreased.\n";
                cin.get();  // Wait for user input
                stress -= (rand() % 2) + 1;
            }
        }

        // Money-making characters
        else
        {
            int investRand = rand() % 18000;
            // No business yet
            if (this->GetLevel() == 0)
            {
                cout << this->GetName() << " offers to cut you in on some business they are getting. Would you like to invest for $" << investRand << "?\n";
                cout << "Y - Yes\nN - No\n--: ";
                string input;
                cin.ignore();  // Ensure we clear any leftover newline characters in the buffer
                getline(cin, input);  // Get the user input
                if (input == "Y")
                {
                    cout << "You have invested $" << investRand << " with " << this->GetName() << ". Check back later to claim your earnings.\n";
                    this_thread::sleep_for(std::chrono::seconds(5));
                    money = -1 * investRand;
                    this->SetLevel(investRand);
                }
                else
                {
                    cout << "No money invested. Returning.\n";
                }
            }
            // Business owner
            else
            {
                cout << this->GetName() << " has made $" << this->GetMoney() << " for you. Collect with 'x':\n";
                string input;
                getline(cin, input);
                if (input == "x")
                {
                    cout << "Money collected.\n";
                    money = this->GetMoney();
                    this->SetMoney(0);
                }
            }
        }
        cout << "Press enter to continue...\n";
        cin.get();  // Wait for user input before continuing
        return {stress, money};
}

    Character::~Character()
    {
        cout <<  this->GetName() << " went into the witness protection program." << endl;
    }
}