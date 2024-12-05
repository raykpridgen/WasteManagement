#pragma once

#include <string>

using namespace std;

namespace chants
{
    class Asset
    {
    private:
        string _name;
        string _message;
        int _value;

    public:
        Asset(string name, string message, int value);
        string GetName();
        string GetMessage();
        int GetValue();
    };
}