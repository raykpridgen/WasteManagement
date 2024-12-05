#include <AdventureGameMap.hpp>

namespace chants
{
    AdventureGameMap::AdventureGameMap()
    {
        buildMapNodes();
    }

    void AdventureGameMap::buildMapNodes()
    {
                // build all nodes
        Node* home = new Node(0, "Home");
        home->Description = "You are inside your magnificent home in North Caldwell, New Jersey.\n";

        Node* pool = new Node(1, "Pool");
        pool->Description = "You are standing outside, in front of your pool. Beyond it you can see your secret stash.\n";

        Node* newark = new Node(2, "Newark");
        newark->Description = "Newark is a gritty and bustling hub of urban life, where the echoes of industry mix with the shadows of organized crime. As one of New Jersey's largest cities, it's a place of contrasts—shiny new developments rising amidst crumbling warehouses, and luxury cars parked beside graffiti-covered alleys.\n";

        Node* crazyHorse = new Node(3, "The Crazy Horse");
        crazyHorse->Description = "Adriana La Cerva's nightclub. You use her office as an outpost for business operations.\n";

        Node* vesuvio = new Node(4, "Vesuvio");
        vesuvio->Description = "Artie Bucco's restaurant, the best Italian food around. This place is open today because of your contributions.\n";

        Node* badaBing = new Node(5, "The Bada Bing!");
        badaBing->Description = "This is your strip club. Here you can manage your business or have a little fun.\n";

        Node* stripClub = new Node(6, "Strip Club");
        stripClub->Description = "This is where the money comes in for this location. Plenty of scantily clad ladies and booze in here.\n";

        Node* stripClubOffice = new Node(7, "Office");
        stripClubOffice->Description = "This is your main office. The family's main business is run out of here, and you meet with your crew here often.\n";

        Node* newDocks = new Node(8, "Newark Docks");
        newDocks->Description = "A bustling hub of maritime transportation. Your yacht is docked here.\n";

        Node* stugots = new Node(9, "Stugots");
        stugots->Description = "This is your luxury yacht. You use this to drive away from civilization to discuss sensitive matters, or invite people to sleep with the fishes.\n";

        Node* moltApartment = new Node(10, "Moltesanti Apartment");
        moltApartment->Description = "This is Christopher Moltesanti and Adriana La Cerva's apartment. Christopher is your second in command, so keeping in touch is important.\n";

        Node* jerseyCity = new Node(11, "Jersey City");
        jerseyCity->Description = "Jersey City is a bustling urban area just across the Hudson River from Manhattan. It's a mix of old-school charm and new developments, where mob activity blends seamlessly with the everyday life of its citizens.\n";

        Node* satPork = new Node(12, "Satriale's Pork Store");
        satPork->Description = "This is your crew's unofficial headquarters. The aroma of cured meats and coffee fills the air as the family gathers here to discuss business and settle disputes.\n";

        Node* melfiOffice = new Node(13, "Dr. Melfi's Office");
        melfiOffice->Description = "Dr. Melfi's office is a calm, quiet space where you come to confront your inner demons. Her compassionate demeanor offers solace, but her questions cut deep.\n";

        Node* casino = new Node(14, "Casino");
        casino->Description = "The casino is a glitzy haven for high-stakes gambling and laundering money. Amidst the flashing lights and sound of slot machines, deals are made, and fortunes are lost.\n";

        Node* horseRaces = new Node(15, "Horse Races");
        horseRaces->Description = "The racetrack is a place of excitement and tension, where you can gamble on horses, make deals in the stands, or just enjoy the spectacle with your crew.\n";

        Node* country = new Node(16, "Country");
        country->Description = "The countryside offers a peaceful reprieve from the chaos of city life. It's a place for quiet reflection or handling family matters away from prying eyes.\n";

        Node* sackHouse = new Node(17, "Johnny Sack's House");
        sackHouse->Description = "Johnny Sack's mansion exudes wealth and power. Located in the suburbs, it serves as a stronghold for the New York crew and a place for delicate negotiations.\n";

        Node* pineBarrens = new Node(18, "Pine Barrens");
        pineBarrens->Description = "The Pine Barrens are an isolated, snowy forest where unfinished business is often resolved. Beware—getting lost here can mean more than just losing your way.\n";

        Node* meadowlands = new Node(19, "Meadowlands");
        meadowlands->Description = "A sprawling sports complex that doubles as a meeting spot for shady deals. Whether it's a football game or a secret rendezvous, this place is full of possibilities.\n";

        Node* notAvailable = new Node(20, "Nowhere");
        notAvailable->Description = "Place to store characters not able to be reached in a turn.";

        // connect nodes paths
        // Add connections between the nodes

        home->AddConnection(pool);
        home->AddConnection(newark);
        home->AddConnection(jerseyCity);
        home->AddConnection(country);

        pool->AddConnection(home);

        newark->AddConnection(home);
        newark->AddConnection(jerseyCity);
        newark->AddConnection(crazyHorse);
        newark->AddConnection(vesuvio);
        newark->AddConnection(badaBing);
        newark->AddConnection(newDocks);
        newark->AddConnection(moltApartment);

        crazyHorse->AddConnection(newark);

        vesuvio->AddConnection(newark);

        badaBing->AddConnection(newark);
        badaBing->AddConnection(stripClub);
        badaBing->AddConnection(stripClubOffice);

        newDocks->AddConnection(newark);
        newDocks->AddConnection(stugots);

        moltApartment->AddConnection(newark);

        stripClub->AddConnection(badaBing);

        stripClubOffice->AddConnection(badaBing);

        stugots->AddConnection(newDocks);

        jerseyCity->AddConnection(home);
        jerseyCity->AddConnection(newark);
        jerseyCity->AddConnection(satPork);
        jerseyCity->AddConnection(melfiOffice);
        jerseyCity->AddConnection(casino);
        jerseyCity->AddConnection(horseRaces);

        satPork->AddConnection(jerseyCity);

        melfiOffice->AddConnection(jerseyCity);

        casino->AddConnection(jerseyCity);

        horseRaces->AddConnection(jerseyCity);

        country->AddConnection(sackHouse);
        country->AddConnection(pineBarrens);
        country->AddConnection(meadowlands);

        country->AddConnection(home);
        sackHouse->AddConnection(country);
        pineBarrens->AddConnection(country);
        meadowlands->AddConnection(country);

        // Build map in the same order as Node IDs above.
        // The index of each node in the vector must match its ID.
        locations.push_back(home);
        locations.push_back(pool);
        locations.push_back(newark);
        locations.push_back(crazyHorse);
        locations.push_back(vesuvio);
        locations.push_back(badaBing);
        locations.push_back(stripClub);
        locations.push_back(stripClubOffice);
        locations.push_back(newDocks);
        locations.push_back(stugots);
        locations.push_back(moltApartment);
        locations.push_back(jerseyCity);
        locations.push_back(satPork);
        locations.push_back(melfiOffice);
        locations.push_back(casino);
        locations.push_back(horseRaces);
        locations.push_back(country);
        locations.push_back(sackHouse);
        locations.push_back(pineBarrens);
        locations.push_back(meadowlands);

    }

    vector<Node*> AdventureGameMap::GetLocations()
    {
        return locations;
    }

}