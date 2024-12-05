#pragma once

#include <vector>
#include <string>
#include "Asset.hpp"
#include "Character.hpp"

using namespace std;

namespace chants
{

    class Node
    {
    private:
        int _id;
        string _name;
        vector<Node *> _connections;
        vector<Asset *> _assets;
        vector<Character *> _Characters;

    public:
        string Description;

        Node(int id, string name);
        int GetId();
        void SetId(int id);
        string GetName();
        void AddConnection(Node *conn);
        vector<Node *> GetConnections();
        Node *GetAConnection(int connId);

        void AddAsset(Asset *asset);
        Asset* RemoveAsset(string name);
        vector<Asset *>& GetAssets();

        void AddCharacter(Character *Character);
        void RemoveCharacter(string name);
        vector<Character *> GetCharacters();

        bool operator==(const Node &rhs) const;
    };
}