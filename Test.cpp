#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
#include <cassert>
#include "Board.hpp"
#include "Player.hpp"
#include "DevelopCard.hpp"
#include "AdvancementCard.hpp"

// Function prototypes for test cases
void testInitialVictoryPoints();
void testAddVictoryPoint();
void testKnightVictoryPoints();
void testBuildCityWithNoSettlement();
void testBuildCityWithSettlement();
void testTradeResources();
void testDiscardResourcesOnRollOfSeven();
void additionalTests();
void testDefaultConstructor();
void testAddCard();
void testUseCard();

// Test cases using doctest
TEST_CASE("Initial Victory Points") {
    Player alice("Alice");
    Player bob("Bob");

    CHECK(alice.getVictoryPoints() == 0);
    CHECK(bob.getVictoryPoints() == 0);
}

TEST_CASE("Add Victory Point") {
    Player alice("Alice");
    alice.addVictoryPoints(1);

    CHECK(alice.getVictoryPoints() == 1);
}


TEST_CASE("Build City With No Settlement") {
    Player alice("Alice");
    Board board;
    std::vector<Player*> players = {&alice};
    board.setPlayers(players);

    bool built = board.buildCity(&alice, 0);

    CHECK(!built);
}

TEST_CASE("Discard Resources on Roll of Seven") {
    Player alice("Alice");
    alice.addResource("wood", 8);

    int diceRoll = 7;
    if (diceRoll == 7) {
        alice.discardResources();
    }

    int totalResources = 0;
    for (const auto& pair : alice.getResources()) {
        totalResources += pair.second;
    }

    CHECK(totalResources == 4);
}

TEST_CASE("Additional Tests") {
    Player bob("Bob");
    Board board;
    std::vector<Player*> players = {&bob};
    board.setPlayers(players);

    Player alice("Alice");
    alice.addResource("wood", 3);
    bob.addResource("brick", 3);
    alice.tradeResources(bob, "wood", 2, "brick", 2);

    CHECK(alice.getResources().at("wood") == 1);
    CHECK(alice.getResources().at("brick") == 2);
    CHECK(bob.getResources().at("brick") == 1);
    CHECK(bob.getResources().at("wood") == 2);

    bool used = bob.useDevelopmentCard("invalid_card");
    CHECK(!used);

    bool roadBuilt = board.buildRoad(&bob, 0);
    CHECK(!roadBuilt);
}

TEST_CASE("Default Constructor") {
    DevelopCard card;
    CHECK(card.getCardCount("monopoly") == 5);
    CHECK(card.getCardCount("road_building") == 5);
    CHECK(card.getCardCount("year_of_plenty") == 5);
    CHECK(card.getCardCount("victory_point") == 4);
    CHECK(card.getCardCount("knight") == 14);
}

TEST_CASE("Add Card") {
    DevelopCard card;
    card.addCard("monopoly", 3);
    CHECK(card.getCardCount("monopoly") == 8);
}

TEST_CASE("Use Card") {
    DevelopCard card;
    CHECK(card.useCard("monopoly"));
    CHECK(card.getCardCount("monopoly") == 5);
    CHECK(!card.useCard("non_existent_card"));
}

TEST_CASE("Build City with Settlement") {
    Board board;
    Player alice("Alice");

    // Assuming resources are managed, ensure Alice has the required resources
    alice.addResource("Brick", 1);
    alice.addResource("Wood", 1);
    alice.addResource("Wheat", 1);
    alice.addResource("Sheep", 1);

    // Build settlement for Alice at vertex 0
    bool settlementBuilt = board.buildSettlement(&alice, 0);
    std::cout << "Settlement built: " << settlementBuilt << std::endl;

    // Check if settlement was built successfully
    CHECK(alice.canBuySettlement());
   

    // Build city for Alice at vertex 0
    alice.addResource("Wheat", 2);
    alice.addResource("Clay", 3);
    
    CHECK(alice.canBuyCity());
}

    

TEST_CASE("Use Development Cards") {
    Player alice("Alice");

    // Alice adds some development cards
    alice.addDevelopmentCard(DevelopCard("Knight"));
    alice.addDevelopmentCard(DevelopCard("road_building"));
    alice.addDevelopmentCard(DevelopCard("victory_point"));

    // Alice uses a knight card
    alice.useDevelopmentCard("Knight");

    // Check that the knight card was used and no longer in hand
    CHECK(alice.getDevelopmentCardCount("Knight") == 0);

    // Check that using a victory point card increases victory points
    alice.useVictoryPoint();
   
    CHECK(alice.getVictoryPoints() == 1); // Assuming a victory point card adds 1 point

    // Check that using a road building card works (assuming game logic allows building roads)
    bool roadBuilt = alice.useDevelopmentCard("road_building");
    CHECK(roadBuilt); // Assuming it successfully builds roads
}  


TEST_CASE("Additional Tests") {
     Player alice("Alice");
    Player bob("Bob");

    alice.addResource("wood", 3);
    bob.addResource("brick", 3);

    // Alice trades 2 wood for 2 brick with Bob
    alice.tradeResources(bob, "wood", 2, "brick", 2);

    CHECK(alice.hasResource("wood", 1) == true);
    CHECK(alice.hasResource("brick", 2) == true);
    CHECK(bob.hasResource("wood", 2) == true);
    CHECK(bob.hasResource("brick", 1) == true);

    
}