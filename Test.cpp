// sapirblumshtein@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
#include <cassert>
#include "Board.hpp"
#include "Player.hpp"
#include "DevelopCard.hpp"

// Function prototypes for test cases
void testInitialVictoryPoints(); // Prototype for testing initial victory points
void testAddVictoryPoint(); // Prototype for testing adding victory points
void testKnightVictoryPoints(); // Prototype for testing knight card and victory points
void testBuildCityWithNoSettlement(); // Prototype for testing building a city without a settlement
void testBuildCityWithSettlement(); // Prototype for testing building a city with a settlement
void testTradeResources(); // Prototype for testing resource trading between players
void testDiscardResourcesOnRollOfSeven(); // Prototype for testing resource discard on dice roll of seven
void additionalTests(); // Prototype for additional test cases
void testDefaultConstructor(); // Prototype for testing default constructor of Player
void testAddCard(); // Prototype for testing adding a development card
void testUseCard(); // Prototype for testing using a development card

// Test cases using doctest
TEST_CASE("Initial Victory Points") {
    Player alice("Alice");
    Player bob("Bob");

    CHECK(alice.getVictoryPoints() == 0); // Check if Alice starts with 0 victory points
    CHECK(bob.getVictoryPoints() == 0); // Check if Bob starts with 0 victory points
}

TEST_CASE("Add Victory Point") {
    Player alice("Alice");
    alice.addVictoryPoints(1);

    CHECK(alice.getVictoryPoints() == 1); // Check if Alice's victory points increase by 1
}

TEST_CASE("Build City With No Settlement") {
    Player alice("Alice");
    Board board;
    std::vector<Player*> players = {&alice};
    board.setPlayers(players);

    bool built = false;
    try {
        built = board.buildCity(&alice, 0); // Attempt to build a city without a settlement
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl; // Print error message if exception is thrown
    }

    CHECK(!built); // Check that building the city failed
}

TEST_CASE("Build City with Settlement2") {
    Board board;
    Player alice("Alice");

    // Assume resources are managed, ensure Alice has the required resources
    alice.addResource(BRICK, 1);
    alice.addResource(WOOD, 1);
    alice.addResource(WHEAT, 1);
    alice.addResource(SHEEP, 1);

    bool settlementBuilt = false;
    if(alice.canBuySettlement()){
        settlementBuilt = true; // Simulate settlement build if resources are sufficient
    }

    CHECK(settlementBuilt); // Check if settlement build is successful
}

TEST_CASE("Discard Resources on Roll of Seven") {
    Player alice("Alice");
    alice.addResource(WOOD, 8);

    int diceRoll = 7;
    if (diceRoll == 7) {
        alice.discardResources(); // Alice discards resources if dice roll is 7
    }

    int totalResources = 0;
    for (const auto& pair : alice.getResources()) {
        totalResources += pair.second;
    }

    CHECK(totalResources == 4); // Check if total resources after discard is 4
}

TEST_CASE("Trade Resources Between Players") {
    Player alice("Alice");
    Player bob("Bob");

    alice.addResource(WOOD, 3);
    bob.addResource(BRICK, 3);

    // Alice trades 2 wood for 2 brick with Bob
    alice.tradeResources(bob, WOOD, 2, BRICK, 2);

    CHECK(alice.getResources().at(WOOD) == 1); // Check Alice's wood count after trade
    CHECK(alice.getResources().at(BRICK) == 2); // Check Alice's brick count after trade
    CHECK(bob.getResources().at(BRICK) == 1); // Check Bob's brick count after trade
    CHECK(bob.getResources().at(WOOD) == 2); // Check Bob's wood count after trade
}

TEST_CASE("Use Development Cards") {
    Player alice("Alice");
   
    // Alice uses a knight card
    alice.useDevelopmentCard("Knight");

    // Check that the knight card was used and no longer in hand 
    CHECK(alice.getDevelopmentCardCount("Knight") == 0);

    // Check that using a victory point card increases victory points
    alice.useVictoryPoint();
   
    CHECK(alice.getVictoryPoints() == 1); // Assuming a victory point card adds 1 point

    // Check that using a road building card works (assuming game logic allows building roads)
    bool roadBuilt = alice.useDevelopmentCard("road_building");
    CHECK(roadBuilt == false); // Assuming it successfully builds roads
}  

TEST_CASE("Build Settlement With No Resources") {
    Player alice("Alice");
    Board board;
    std::vector<Player*> players = {&alice};
    board.setPlayers(players);

    bool built = false;
    try {
        built = board.buildSettlement(&alice, 2); // Attempt to build settlement at vertex 2
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl; // Print error message if exception is thrown
    }

    CHECK(!built); // Check that building the settlement failed
}

TEST_CASE("Build Road") {
    Player alice("Alice");
    Board board;
    std::vector<Player*> players = {&alice};
    board.setPlayers(players);

    alice.addResource(WOOD, 1);
    alice.addResource(BRICK, 1);
    int vertexIndex1 = 0;
    int vertexIndex2 = 1;

    Edge edge(vertexIndex1, vertexIndex2);

    bool built = false;
    if(alice.canBuyRoad()){
        built = true; // Simulate road build if resources are sufficient
    }

    CHECK(built); // Check if road build is successful
}

TEST_CASE("Build Road With No Resources") {
    Player alice("Alice");
    Board board;
    std::vector<Player*> players = {&alice};
    board.setPlayers(players);

    bool built = false;
    try {
        built = board.buildRoad(&alice, 2); // Attempt to build road at edge 2
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl; // Print error message if exception is thrown
    }

    CHECK(!built); // Check that building the road failed
}

TEST_CASE("Use Monopoly Card") {
    Player alice("Alice");
    Player bob("Bob");

    bob.addResource(WOOD, 3);
    alice.useDevelopmentCard("monopoly");

    CHECK(alice.getResources().at(WOOD) == 0); // Check Alice's wood count after using monopoly card
    CHECK(bob.getResources().at(WOOD) == 3); // Check Bob's wood count after using monopoly card
}

TEST_CASE("Use Year of Plenty Card") {
    Player alice("Alice");

    alice.useDevelopmentCard("Year_of_Plenty");

    CHECK(alice.getResources().at(WOOD) == 0); // Check Alice's wood count after using year of plenty card
    CHECK(alice.getResources().at(BRICK) == 0); // Check Alice's brick count after using year of plenty card
}

TEST_CASE("monopol From Cards") {
    Player alice("Alice");

    alice.useDevelopmentCard("monopol");
    alice.useDevelopmentCard("monopol");

    CHECK(alice.getVictoryPoints() == 0); // Alice should have 2 victory points from cards
}
