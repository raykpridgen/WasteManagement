#include "../inc/Asset.hpp"
namespace chants
{
    Asset::Asset(string name, string message, int value)
    {
        _name = name;
        _message = message;
        _value = value;
    }

    string Asset::GetName()
    {
        return _name;
    }

    string Asset::GetMessage()
    {
        return _message;
    }

    int Asset::GetValue()
    {
        return _value;
    }
}