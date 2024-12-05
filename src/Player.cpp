#include "../inc/Player.hpp"
#include "../inc/Combatant.hpp"
#include <iostream>
using namespace std;

namespace chants
{
    Player::Player(string name, int health, int money, int power, int stress)
    :Combatant(name, money, -1, health, power), _stress(stress)
    {}

    void Player::AddAsset(Asset* asset)
    {
        if (this->GetAssets().size() < 2)
        {
            _assets.push_back(asset);
        }
        else
        {
            // Remove a weapon for a new one if player has 2 already
            this->_assets.pop_back();
            _assets.push_back(asset);
        }
        
    }

    // Returns players power for a fight
    int Player::GetPower()
    {
        int val = _power;
        for (Asset* asset : _assets)
        {
            val += asset->GetValue();
        }
        return val;
    }

    void Player::GetCrew()
    {
        std::cout << "Your crew includes: \n";
        for (const auto& member : _crew) {
            std::cout << "- " << member->GetName() << " (Health: " << member->GetHealth() << ")\n";
        }
    }

    int Player::GetStress()
    {
        return _stress;
    }

    void Player::SetStress(int newStress)
    {
        _stress = newStress;
    }
    
    vector<Asset *> Player::GetAssets()
    {
        return _assets;
    }
}