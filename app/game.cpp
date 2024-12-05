#include <iostream>
#include <thread>  
#include <chrono>  
#include <iomanip>
#include <cmath>
#include <sstream>
#include <vector>
#include <cstdlib>   
#include <algorithm> 
#include <ctime>
#include <Node.hpp>
#include <Asset.hpp>
#include <Player.hpp>
#include <Character.hpp>
#include <Combatant.hpp>
#include <AdventureGameMap.hpp>

using namespace std;
using namespace chants;

bool isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

string getLastWord(const string& input) {
    stringstream ss(input);
    string word;
    string lastWord;
    
    while (ss >> word) {
        lastWord = word;  // Keep updating lastWord with the current word
    }
    
    return lastWord;
}


/**
 * Return type:
 * 0 - Dead player
 * 1 - Dead enemy
 * 2 - Both live
 * 3 - Both Dead
 */
int Battle(Player* player, Combatant* enemy)
{
    int returnValue = 2;
    cout << "\033[2J\033[1;1H";  // ANSI escape code to clear the screen
    cout << "\n";
    cout << "\n-------------------------------------\n";
    cout << getLastWord(player->GetName()) << setw(30) << getLastWord(enemy->GetName());
    cout << "\n" << player->GetHealth() << setw(34) << enemy->GetHealth();
    cout << "\n-------------------------------------\n";

    // Player attack
    cout << player->GetName() << " attacks " << enemy->GetName() << "!\n";
    player->Attack(enemy);
    cout << enemy->GetName() << " has " << enemy->GetHealth() << " health remaining.\n";
    // NPC Attack
    cout << enemy->GetName() << " attacks " << player->GetName() << "!\n";
    enemy->Attack(player);
    cout << player->GetName() << " has " << player->GetHealth() << " health remaining.\n";

    // If both player and enemy dies
    if (enemy->GetHealth() < 1 && player->GetHealth() <= 0)
    {
        return 0;
    }

    // If only the player dies
    if (player->GetHealth() <= 0)
    {
        cin.get();
        return 0;
    }

    // If enemy dies
    if (enemy->GetHealth() < 1)
    {
        if (enemy->GetMoney() > 0)
        {
            player->SetMoney(player->GetMoney() + enemy->collectMoney());
        }
    }
    
    // If player lives and enemy dies
    if (player->GetHealth() > 0 && enemy->GetHealth() <= 0)
    {
        player->SetStress(player->GetStress() + 5);
        return 1;
    }
    
    cout << "Continue?(Y/n)\n\n--:";
    string input;
    getline(cin, input);
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (input == "Y") // Quit
    {
        returnValue = Battle(player, enemy);   
    }
    player->SetMoney(player->GetMoney() - 50);
    player->SetStress(player->GetStress() + 1);
    return returnValue;
}

void InitializeCharacterLocations(vector<Character*>& characters, vector<Node*>& gameMap) {
    // Assign each character to a random node
    for (Character* character : characters) {
        int randomIndex = std::rand() % gameMap.size();
        gameMap[randomIndex]->AddCharacter(character);
    }
}

void PopulateAssets(vector<Asset*> assets, vector<Node*> gameMap)
{
    for (Asset* asset : assets)
    {
        if (asset->GetName() == "Bat")
        {
            gameMap[0]->AddAsset(asset);
        }
        if (asset->GetName() == "Kmife")
        {
            gameMap[3]->AddAsset(asset);
        }
        if (asset->GetName() == "Colt .38")
        {
            gameMap[7]->AddAsset(asset);
        }
        if (asset->GetName() == "Baretta 92")
        {
            gameMap[17]->AddAsset(asset);
        }
        if (asset->GetName() == "Remington 870")
        {
            gameMap[9]->AddAsset(asset);
        }

    }
}

/**
 * Takes current node, time in game, and player
 * Main interaction function
 */
void AtNode(Node* viewPort, int dateTime, Player* tonySoprano)
{
    bool stayInNode = true; // Loop control
    while (stayInNode)
    {
        string weapon1 = "   ";
        string weapon2 = "   ";
        if (tonySoprano->GetAssets().size() == 1)
        {
            weapon1 = tonySoprano->GetAssets()[0]->GetName();
            weapon1 = getLastWord(weapon1);
        }
        else if (tonySoprano->GetAssets().size() == 2)
        {
            weapon1 = tonySoprano->GetAssets()[0]->GetName();
            weapon1 = getLastWord(weapon1);
            weapon2 = tonySoprano->GetAssets()[0]->GetName();
            weapon2 = getLastWord(weapon2);
        }
        // Determine the time of day
        string time = (dateTime % 2 == 0) ? "Afternoon" : "Night";
        int day = (dateTime / 2) + 1; // Correct day calculation: day is 1-based

        // Clear screen
        cout << "\033[2J\033[1;1H";  // ANSI escape code to clear the screen
        cout << "\n\n";
        cout << "--------------------------------\n";
        // Display node information
        cout << viewPort->GetName() << " - " << "October " << day << ", " << time << "\n";
        cout << "Health: " << setw(7) << tonySoprano->GetHealth() << setw(15) << "Weapons: "
           << "\nMoney: " << setw(7) << tonySoprano->GetMoney() << setw(15) << weapon1
           << "\nStress: " << setw(7) << tonySoprano->GetStress() << setw(15) << weapon2 << "\n\n";
        cout << viewPort->Description;
        cout << "--------------------------------\n";

        // Menu
        cout << "\nWhat would you like to do?\n";
        cout << "1) View People\n";
        cout << "2) View Assets\n";
        cout << "3) Leave this location\n";
        cout << "Enter your choice: ";

        int choice;
        while (!(cin >> choice) || (choice < 1 || choice > 4)) {
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer

        int buffer;
        switch (choice)
        {
        case 1: // View People
            cout << "\nPeople at this location:\n";
            if (viewPort->GetCharacters().empty())
            {
                cout << "No one is here right now.\n";
                cout << "Press enter to continue...\n";
                cin.get();
            }
            else
            {
                int charCounter = 1;
                for (Character *character : viewPort->GetCharacters())
                {
                    cout << charCounter << ": " << character->GetName() << endl;
                    charCounter++;
                }
                cout << "\nEnter the number of the person you want to interact with (or 0 to go back): ";
                int selection;
                while (!(cin >> selection) || (selection < 0 || selection > viewPort->GetCharacters().size())) {
                    cout << "Invalid selection. Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (selection == 0) {
                    cout << "Returning to the previous menu...\n";
                } else {
                    Character* selectedCharacter = viewPort->GetCharacters()[selection - 1];
                    cout << selectedCharacter->GetName() << "...\n";
                    tuple<int, int> interactTuple = selectedCharacter->interact();
                    int stress = get<0>(interactTuple);
                    int money = get<1>(interactTuple);
                    tonySoprano->SetMoney(tonySoprano->GetMoney() + money);
                    tonySoprano->SetStress(tonySoprano->GetStress() + stress);

                    // If the selected character is a Combatant, offer the attack option
                    Combatant* combatant = dynamic_cast<Combatant*>(selectedCharacter);
                    if (combatant != nullptr) {
                        cout << "\nAttaack?\n";
                        cout << "1) Yes\n";
                        cout << "2) No\n";
                        cout << "Enter your choice: ";
                        int attackChoice;
                        while (!(cin >> attackChoice) || (attackChoice < 1 || attackChoice > 2)) {
                            cout << "Invalid choice. Please enter 1 or 2: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        if (attackChoice == 1) 
                        {
                            // Handle the combat logic here
                            cout << "Are you sure you want to attack " << combatant->GetName() << "?\nYou have: " << tonySoprano->GetPower() << " power\n" << combatant->GetName() << " has: " << combatant->GetPower() << " power\n";
                            cout << "Enter 'a' to attack: ";
                            string input;
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            getline(cin, input);
                            int initialStress = tonySoprano->GetStress();
                            int initialHealth = tonySoprano->GetHealth();
                            int result = Battle(tonySoprano, combatant);
                            if (result == 0)
                            {
                                cout << "The battle concludes as your vision blurs and strength fades. " << combatant->GetName() <<  " stands victorious over your lifeless body, smirking as they walk away.\n\nGame Over.\n\n";
                                cout << "Exiting\n";
                                cin.get();
                                return;
                            }
                            else if (result == 1)
                            {
                                cout << combatant->GetName() << " lies crumpled before you. You make a quick escape, avoiding attention.\n\n";
                                viewPort->RemoveCharacter(combatant->GetName());
                                cin.get();
                            }
                            else if (result == 2)
                            {
                                cout << "The crowd intervenes as fists fly and blood spills. You're both hauled away, and the fight ends in a stalemate. A fine leaves you with lighter pockets—and heavier stress.\n\n";
                                cin.get();
                            }
                            else if (result == 3)
                            {
                                cout << "The last strike cuts both ways. You collapse beside [Enemy Name], the echoes of the battle fading as the city claims you both.\n\n";
                                cin.get();
                                return;
                            }
                            cout << "Health change: " << tonySoprano->GetHealth() - initialHealth
                               << "\nStress change: " << tonySoprano->GetStress() - initialStress << "\n";
                            cin.get();

                            // Optionally, adjust stats after combat
                        } 
                        else 
                        {
                            cout << "You decided not to attack.\n";
                            cin.get();
                        }
                    }
                }
            }
            break;

        case 2: // View Assets
            cout << "\nAssets at this location:\n";
            if (viewPort->GetAssets().empty())
            {
                cout << "No assets are present here.\n";
                cout << "Press enter to continue...\n";
                cin.get();
            }
            else
            {
                int assetCounter = 1;  // Counter to list assets
                for (Asset *asset : viewPort->GetAssets())
                {
                    cout << assetCounter << ") " << asset->GetName()
                        << ": " << asset->GetMessage()
                        << "     Value: " << asset->GetValue() << endl;
                    assetCounter++;
                }
                
                // Ask the player if they want to pick up an item
                cout << "\nWould you like to pick up an asset? (Enter asset number or 0 to cancel): ";
                int assetChoice;
                
                // Validate input
                while (!(cin >> assetChoice) || (assetChoice < 0 || assetChoice > viewPort->GetAssets().size())) {
                    cout << "Invalid selection. Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                if (assetChoice == 0) {
                    cout << "You chose not to pick up any asset.\n";
                } else {
                    // Retrieve the selected asset
                    Asset* selectedAsset = viewPort->GetAssets()[assetChoice - 1];
                    cout << "You chose to pick up: " << selectedAsset->GetName() << "\n";
                    
                    // Add asset to player's inventory (you will need a method to handle this)
                    tonySoprano->AddAsset(viewPort->RemoveAsset(viewPort->GetAssets()[assetChoice-1]->GetName()));

                    // Remove asset from the current location (you will need a method to handle this)
                    // Did it in a single line... get wrecked

                    cout << "Weapon added to your inventory.\n";
                }
            }
            cout << "Press enter to continue...\n";
            cin.get();  // Wait for user to press enter before continuing
            break;

        case 3: // Leave this location
            cout << "\nYou decide to leave this location.\n";
            stayInNode = false; // Exit loop
            cout << "Press enter to continue...\n";
            cin.get();
            break;

        default: // Invalid input
            cout << "\nInvalid choice. Please try again.\n";
            cout << "Press enter to continue...\n";
            cin.get();
        }
    }
}


int FindNode(string loc, vector<Node*> gameMap)
{
    int intLoc = -1;
    if (isNumber(loc))
    {
        intLoc = stoi(loc);
    }
    for (Node* node : gameMap)
    {
        if (node->GetName() == loc || node->GetId() == intLoc)
            return node->GetId();
    }
    return -1;
}

void DistributeCharacters(std::vector<Character*>& characters, std::vector<Node*>& gameMap) {

    for (Character* character : characters)
    {
        if (character->GetName() == "Carmella Soprano" || character->GetName() == "AJ Soprano" || character->GetName() == "Meadow Soprano")
        {
            gameMap[0]->AddCharacter(character);
        }
        if (character->GetName() == "Dr. Melfi")
        {
            gameMap[13]->AddCharacter(character);
        }
        if (character->GetName() == "Artie Bucco")
        {
            gameMap[4]->AddCharacter(character);
        }
        if (character->GetName() == "Hesh Rabkin")
        {
            gameMap[15]->AddCharacter(character);
        }
        if (character->GetName() == "Adriana La Cerva")
        {
            gameMap[3]->AddCharacter(character);
        }
        if (character->GetName() == "Ralph Cifaretto")
        {
            gameMap[6]->AddCharacter(character);
        }
        if (character->GetName() == "Silvio Dante")
        {
            gameMap[7]->AddCharacter(character);
        }
        else
        {
            gameMap[rand() % gameMap.size()]->AddCharacter(character);
        }
    }

    // Clear the input characters vector since they've been distributed
    characters.clear();
}

vector<Character *> populateEntities() {
    vector<Character *> alive;
    // Characters
    Character *Carmella = new Character("Carmella Soprano", 0, -1); // takes money at house, adds stress
    alive.push_back(Carmella);

    Character *Junior = new Character("AJ Soprano", 0, -1); // takes money at house, adds stress
    alive.push_back(Junior);

    Character *Meadow = new Character("Meadow Soprano", 0, -1); // takes money at house, adds stress
    alive.push_back(Meadow);

    Character *Melfi = new Character("Dr. Melfi", 0, -1); // Releases stress at her office. not available at night
    alive.push_back(Melfi);

    Character *Adriana = new Character("Adriana La Cerva", 1200, 0); // Runs club, gives money. Sometimes moves in day
    alive.push_back(Adriana);

    Character *Artie = new Character("Artie Bucco", 1200, 0); // Runs the restaurant, gives money
    alive.push_back(Artie);

    Character *Hesh = new Character("Hesh Rabkin", 1200, 0); // Runs the horses, gives money
    alive.push_back(Hesh);

    // Combatants
    Combatant *Christopher = new Combatant("Christopher Moltesanti", 4500, 0, 100, 115);
    alive.push_back(Christopher);

    Combatant *Silvio = new Combatant("Silvio Dante", 4500, 0, 100, 115);
    alive.push_back(Silvio);

    Combatant *Paulie = new Combatant("Paulie Gualtieri", 4500, 0, 100, 115);
    alive.push_back(Paulie);

    Combatant *Furio = new Combatant("Furio Giunta", 0, 0, 100, 115);
    alive.push_back(Furio);

    Combatant *Ralph = new Combatant("Ralph Cifaretto", 0, 0, 100, 115);
    alive.push_back(Ralph);

    Combatant *JohnnySack = new Combatant("Johnny Sack", 0, 0, 100, 200);
    alive.push_back(JohnnySack);

    Combatant *PhilLeotardo = new Combatant("Phil Leotardo", 4500, 0, 100, 200);
    alive.push_back(PhilLeotardo);

    // Johnny Sack's goons
    Combatant *sack1 = new Combatant("Giovanni Russo", 0, 0, 100, 100);
    alive.push_back(sack1);

    Combatant *sack2 = new Combatant("Francesco Bianchi", 0, -1, 100, 100);
    alive.push_back(sack2);

    Combatant *sack3 = new Combatant("Marco De Luca", 0, -1, 100, 100);
    alive.push_back(sack3);

    // Phil Leotardo's goons
    Combatant *phil1 = new Combatant("Alessandra Moretti", 0, -1, 100, 100);
    alive.push_back(phil1);

    Combatant *phil2 = new Combatant("Luigi Romano", 0, -1, 100, 100);
    alive.push_back(phil2);

    Combatant *phil3 = new Combatant("Guido Caruso", 0, 0, 100, 100);
    alive.push_back(phil3);

    // Independent goons
    Combatant *goon1 = new Combatant("Jordan Taylor", 0, -1, 100, 100);
    alive.push_back(goon1);

    Combatant *goon2 = new Combatant("Casey Morgan", 0, -1, 100, 100);
    alive.push_back(goon2);

    Combatant *goon3 = new Combatant("Alex Parker", 0, 0, 100, 100);
    alive.push_back(goon3);

    return alive;
}

void HandleDayNightCycle(int& dayNightCounter, int& moveCounter, vector<Character*>& currentCharacters, vector<Node*>& gameMap) {
    // If the player has moved 5 times, change time/day and cycle business for characters
    if (moveCounter % 5 == 0 && moveCounter != 0) {
        // Distribute characters randomly or based on the logic of your game
        DistributeCharacters(currentCharacters, gameMap);

        // Increment day/night counter
        dayNightCounter += 1;

        // Cycle business for characters
        for (Node* node : gameMap) {
            for (Character* character : node->GetCharacters()) {
                character->cycleBusiness();
            }
        }
    }
}

void DisplayNodeConnections(Node* currentNode) {
    cout << "\nConnections from this location:\n";
    for (Node* node : currentNode->GetConnections()) {
        cout << setw(5) << node->GetId() << " : " << setw(15) << node->GetName() << endl;
    }
}

int GetValidNodeAddress(string& input, vector<Node*>& gameMap, int currentNode) {
    // Convert the input to an integer node address, return -1 if invalid
    int nodeAddr = -1;
    if (isNumber(input)) {
        nodeAddr = stoi(input);
    }

    // Validate if the node address exists in the current node's connections
    for (Node* node : gameMap[currentNode]->GetConnections()) {
        if (node->GetId() == nodeAddr) {
            return nodeAddr;  // Return valid node address
        }
    }

    return -1;  // Invalid node address
}


//
// All this game setup will be moved to gamemap and out of the main function
//
int main()
{
    AdventureGameMap _gameMap;
    srand(time(nullptr)); // seed the random number generator

    vector<Node*> gameMap = _gameMap.GetLocations();

    // build assets
    Asset bat("Baseball Bat", "Good for baseballs and kneecaps.", 25);
    Asset knife("Pocket Knife", "Sharp", 35);
    Asset colt38("Colt .38 Revolver", "Compact, reliable, leaves no shells behind.", 80);
    Asset baretta92("Baretta 92 Handgun", "Large magazine, large rounds.", 95);
    Asset remington870("Remington 870 Shotgun", "Be careful bringing this in public.", 150);

    gameMap[1]->AddAsset(&bat); // Bat goes by the pool, maybe the shed
    gameMap[9]->AddAsset(&remington870); // Shotgun goes on the yacht, stugots
    gameMap[17]->AddAsset(&baretta92); // Pistol goes in the HQ, Bada Bing
    gameMap[7]->AddAsset(&colt38); // Pistol goes in Chris' apartment
    gameMap[3]->AddAsset(&knife); // Knife goes in Adrianna's club

    // randomly add assets to nodes
    int numOfNodes = gameMap.size();

    vector<Character> alive;

    // build Characters
    // randomly add Characters to nodes

    vector<Character *> currentCharacters = populateEntities();
    

    // +++++++++ game loop ++++++++++
    int nodePointer = 0;  // Start at the first node (home)
    int dayNightCounter = 0;
    int moveCounter = 0;
    string input;
    Player* TonySoprano = new Player("Anthony Soprano", 150, 11430, 125, 0);
    DistributeCharacters(currentCharacters, gameMap);
    while (dayNightCounter < 29) {
        if (TonySoprano->GetMoney() < 0)
        {
            cout << "You went broke! Game over.\n\n";
            break;
        }
        if (moveCounter % 2 == 0 && moveCounter != 0)
        {   
            dayNightCounter += 1;
            for (Node* place : gameMap)
            {
                for (Character* character : place->GetCharacters())
                {
                    character->cycleBusiness();
                }
            }
            //DistributeCharacters(currentCharacters, gameMap);
        }

        // Display current node info and connections
        AtNode(gameMap[nodePointer], dayNightCounter, TonySoprano);
        if (TonySoprano->GetHealth() <= 0)
        {
            return 0;
        }
        DisplayNodeConnections(gameMap[nodePointer]);

        // Prompt for player input
        cout << "Go to node? e(x)it: ";
        getline(cin, input);

        // Exit if the user inputs "x"
        if (input == "x") {
            break;
        }


        // Get valid node address based on user input
        int nodeAddr = GetValidNodeAddress(input, gameMap, nodePointer);

        if (nodeAddr == -1) {
            cout << "Not a valid node address\n";
        } else {
            // Update the node pointer if the node address is valid
            nodePointer = nodeAddr;
        }

        // Increment move counter
        moveCounter += 1;
    }

    return 0;
}
