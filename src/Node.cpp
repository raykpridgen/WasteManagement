#include <Node.hpp>

namespace chants
{

    Node::Node(int id, string name)
    {
        _id = id;
        _name = name;
    }

    int Node::GetId()
    {
        return _id;
    }

    void Node::SetId(int id)
    {
        _id = id;
    }

    string Node::GetName()
    {
        return _name;
    }

    void Node::AddConnection(Node *conn)
    {
        _connections.push_back(conn);
    }

    vector<Node *> Node::GetConnections()
    {
        return _connections;
    }

    Node* Node::GetAConnection(int connId)
    {
        if (connId >= 0 && connId < _connections.size()) {
            return _connections[connId];
        }
    return nullptr; // Or throw an exception
}

    void Node::AddAsset(Asset *asset)
    {
        _assets.push_back(asset);
    }

    Asset* Node::RemoveAsset(string name) 
    {
        Asset* deletedAsset = nullptr; // Initialize to nullptr
        for (auto it = _assets.begin(); it != _assets.end(); ++it) {
            if ((*it)->GetName() == name) {
                deletedAsset = *it;
                _assets.erase(it); // Erase the asset
                break; // Exit the loop once found
            }
        }
        return deletedAsset; // Return nullptr if no asset is found
    }

    vector<Asset *>& Node::GetAssets() 
    {
        return _assets;
    }

    bool Node::operator==(const Node &rhs) const
    {
        return _name == rhs._name;
    }

    void Node::AddCharacter(Character *Character)
    {
        _Characters.push_back(Character);
    }

    void Node::RemoveCharacter(string name)
    {
        for (Character* character : _Characters)
        {
            if (name == character->GetName())
            {
                this->_Characters.erase(remove(_Characters.begin(), _Characters.end(), character), _Characters.end());
            }

        }
    }

    vector<Character *> Node::GetCharacters()
    {
        return _Characters;
    }
}