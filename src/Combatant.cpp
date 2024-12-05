#include "../inc/Combatant.hpp"
#include "../inc/Character.hpp"
#include <time.h>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

namespace chants
{
    Combatant::Combatant(string name, int money, int businessLevel, int health, int power)
    :Character(name, money, businessLevel), _health(health), _power(power)
    {}

    int Combatant::GetHealth()
    {
        return _health;
    }

    int Combatant::GetPower()
    {
        return _power;
    }
    
    void Combatant::SetHealth(int amount)
    {
        _health = amount;
    }
    
    void Combatant::SetPower(int amount)
    {
        _power = amount;
    }
    
    int Combatant::collectMoney()
    {
        if (this->GetHealth() <= 0)
        {
            return this->GetMoney();
        }
        else
        {
            return 0;
        }
    }

    void Combatant::Attack(Combatant* enemy)
    {
        int combatantPower = this->GetPower();
        int hitChance = rand() % 500;
        
        if (hitChance < combatantPower)
        {
            hitChance = (int)hitChance % (combatantPower - 50);
            enemy->SetHealth(enemy->GetHealth() - hitChance);
            std::cout << enemy->GetName() << " has been damaged " << hitChance << " points by " << this->GetName() << endl;
        }
        else
        {
            cout << this->GetName() << " has missed " << enemy->GetName() << "!\n" << endl;
        }
    }
    /**
     * Returns tuple vals for (health, stress, money)
     */
    tuple<int, int> Combatant::interact()
    {
        int health = 0;
        int stress = 0;
        int money = 0;
        
        cout << this->GetName() << " greets you with a firm handshake and a stern look.\n" << endl;

        // Random Gift event
        if (this->GetName() == "Christopher Moltesanti" || this->GetName() == "Silvio Dante" || this->GetName() == "Paulie Gualtieri" || this->GetName() == "Furio Giunta" || this->GetName() == "Ralph Cifaretto")
        {
            int randGift = rand() % 5000;

            if (randGift % 69 < 2)
            {
                cout << this->GetName() << " has given you a gift of " << randGift << " for being such an amazing boss.\n" << endl;
                money += randGift;
            }
        }
        if (this->GetLevel() >= 0)
        {
            int investRand = rand() % 18000;
            // No business yet
            if (this->GetLevel() == 0)
            {
                cout << this->GetName() << " offers to cut you in on some business they are getting. Would you like to invest for $" << investRand << "?\n";
                cout << "Y - Yes\nN - No\n--: ";
                string input;
                cin.ignore();
                getline(cin, input);
                if (input == "Y")
                {
                    cout << "You have funded $" << investRand << " for " << this->GetName() << ". Check back later to claim your earnings.\n";
                    this_thread::sleep_for(std::chrono::seconds(5));
                    money = -1 * investRand;
                    this->SetLevel(investRand);
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
        cin.get();
        return {stress, money};
    }

    Combatant::~Combatant()
    {
        cout <<  this->GetName() << " is pushing up daisies." << endl;
    }
}