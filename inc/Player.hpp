#pragma once

#include <string>
#include <vector>
#include "Asset.hpp"
#include "Combatant.hpp"

using namespace std;

namespace chants
{
    class Player : public Combatant
    {
    protected:
        vector<Asset*> _assets;
        vector<Combatant*> _crew;
        int _stress;

    public:
        Player(string name, int health, int money, int power, int stress);
        void AddAsset(Asset* asset);
        vector<Asset*> GetAssets();
        virtual int GetPower() override;
        int GetTotalAssetValue();
        void GetCrew();
        int GetStress();
        void SetStress(int newStress);
    };
}
