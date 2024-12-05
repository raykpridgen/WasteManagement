#pragma once
#include <string>
#include <tuple>
using namespace std;

namespace chants
{
    class Character
    {
        protected:
            string _name;
            int _money;
            int _businessLevel;



        public:
            Character(string name, int money, int businessLevel);
            string GetName();
            int GetMoney();
            int GetLevel();
            void SetLevel(int newlevel);
            void SetMoney(int amount);
            void cycleBusiness();
            virtual tuple<int, int> interact();
            virtual ~Character();
    };
}