#pragma once

#include <string>
#include "Character.hpp"

using namespace std;

namespace chants
{
    class Combatant : public Character
    {
    protected:
        int _health;
        int _power;
    public:
        Combatant(string name, int money, int businessLevel, int health, int power);
        int GetHealth();
        virtual int GetPower();
        void SetPower(int amount);
        void SetHealth(int amount);
        void Attack(Combatant* enemy);
        virtual tuple<int, int> interact() override;
        int collectMoney();
        virtual ~Combatant();
    };
}