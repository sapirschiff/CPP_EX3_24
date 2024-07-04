// sapirblumshtein@gmail.com

#include "Player.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include "DevelopCard.hpp"
#include "Edge.hpp"
#include "Hexagon.hpp"
#include <iostream>
#include <cstdlib>
#include <random>
#include <stdexcept>

// Constructor to initialize player's name and resources
Player::Player(const std::string& name): name(name), victoryPoints(0), turn(false), board(nullptr) {
    resources[WOOD] = 0;
    resources[BRICK] = 0;
    resources[SHEEP] = 0;
    resources[WHEAT] = 0;
    resources[CLAY] = 0;
}

// Destructor to clean up dynamically allocated development cards
Player::~Player() {
    for (auto card : cards) {
        delete card;
    }
}

// Function to discard resources when the total exceeds 7
void Player::discardResources() {
    int totalResources = 0;
    for (const auto& pair : resources) {
        totalResources += pair.second;
    }
    if (totalResources > 7) {
        int resourcesToDiscard = totalResources / 2;
        std::cout << name << " needs to discard " << resourcesToDiscard << " resource cards.\n";

        for (auto& pair : resources) {
            int discardAmount = std::min(pair.second, resourcesToDiscard);
            pair.second -= discardAmount;
            resourcesToDiscard -= discardAmount;

            if (resourcesToDiscard <= 0) break;
        }
    }
}

// Function to add resources to player
void Player::addResource(Resource r, int amount) {
    resources[r] += amount; // Use += to add resources
}

// Function to get player's resources
const std::unordered_map<Resource, int>& Player::getResources() const {
    return resources;
}

// Function to remove resources from player
bool Player::removeResource(Resource r, int amount) {
    if (resources[r] >= amount) {
        resources[r] -= amount;
        return true;
    }
    return false;
}

// Function to check if player has specific resources
bool Player::hasResource(Resource r, int amount) const {
    auto it = resources.find(r);
    return it != resources.end() && it->second >= amount;
}

// Function to add a development card to player
void Player::addDevelopmentCard(const DevelopCard& card) {
    cards.push_back(card.clone());
    developmentCards[card.getName()]++;
}

// Function to use a development card
bool Player::useDevelopmentCard(const std::string& cardType) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if ((*it)->getName() == cardType) {
            delete *it;
            cards.erase(it);
            developmentCards[cardType]--;
            return true;
        }
    }
    return false;
}

// Function to get the count of specific development card
int Player::getDevelopmentCardCount(const std::string& cardType) const {
    auto it = developmentCards.find(cardType);
    return it != developmentCards.end() ? it->second : 0;
}

// Function to add victory points to player
void Player::addVictoryPoints(int points) {
    victoryPoints += points;
}

// Function to get player's victory points
int Player::getVictoryPoints() const {
    return victoryPoints;
}

// Function to check if it's player's turn
bool Player::isTurn() const {
    return turn;
}

// Function to set player's turn
void Player::setTurn(bool turn) {
    this->turn = turn;
}

// Function to initialize player's resources
void Player::initializeResources(const std::vector<Resource>& initialResources) {
    for (const auto& resource : initialResources) {
        addResource(resource, 1);
    }
}

// Function to print cities owned by player
void Player::getCities(const std::vector<Vertex>& vertices) const {
    std::cout << "Cities for player " << name << ":\n";
    for (const auto& vertex : vertices) {
        if (vertex.getOwner() == this && vertex.getStructure() == Vertex::Structure::City) {
            std::cout << "City at vertex index: " << &vertex - &vertices[0] << '\n';
        }
    }
}

// Function to roll dice and distribute resources based on the roll
void Player::rollDice() {
    diceRoll = rand() % 6 + 1 + rand() % 6 + 1;
    std::cout << name << " rolled a " << diceRoll << '\n';
    if (board != nullptr) {
        board->distributeResources(diceRoll);
    }
}

// Function to add settlement to player
void Player::addSettlement(int vertexIndex) {
    settlements.push_back(vertexIndex);
}

// Function to add road to player
void Player::addRoad(int edgeIndex) {
    roads.push_back(edgeIndex);
}

// Function to get dice roll value
int Player::getDiceRoll() const {
    return diceRoll;
}

// Function to get player's settlements
const std::vector<int>& Player::getSettlements() const {
    return settlements;
}

// Function to get player's roads
const std::vector<int>& Player::getRoads() const {
    return roads;
}

// Function to receive resources from hexagons
void Player::receiveResources(const std::vector<Hexagon>& hexagons, int vertexIndex) {
    for (const auto& hex : hexagons) {
        for (const auto* vertex : hex.getVertices()) {
            if (vertex == &vertices[vertexIndex]) {
                addResource(hex.getResource(), 1);
                break;
            }
        }
    }
}

// Function to get player's name
std::string Player::getName() const {
    return name;
}

// Function to trade resources between players
void Player::tradeResources(Player& otherPlayer, Resource resource1, int amount1, Resource resource2, int amount2) {
    if (amount1 <= 0 || amount2 <= 0) {
        std::cout << "Trade amounts must be positive.\n";
        return;
    }

    if (!hasResource(resource1, amount1)) {
        std::cout << name << " does not have enough " << Hexagon::resourceToString(resource1) << " to trade.\n";
        return;
    }

    if (!otherPlayer.hasResource(resource2, amount2)) {
        std::cout << otherPlayer.getName() << " does not have enough " << Hexagon::resourceToString(resource2) << " to trade.\n";
        return;
    }

    removeResource(resource1, amount1);
    otherPlayer.removeResource(resource2, amount2);
    addResource(resource2, amount2);
    otherPlayer.addResource(resource1, amount1);

    std::cout << name << " traded " << amount1 << " " << Hexagon::resourceToString(resource1) << " with " << otherPlayer.getName() << " for " << amount2 << " " << Hexagon::resourceToString(resource2) << ".\n";
}

// Function to check if player can buy a settlement
bool Player::canBuySettlement() const {
    return hasResource(BRICK, 1) && hasResource(WOOD, 1) && hasResource(SHEEP, 1) && hasResource(WHEAT, 1);
}

// Function to check if player can buy a city
bool Player::canBuyCity() const {
    return hasResource(CLAY, 3) && hasResource(WHEAT, 2);
}

// Function to check if player can buy a road
bool Player::canBuyRoad() const {
    return hasResource(BRICK, 1) && hasResource(WOOD, 1);
}

// Function to use knight development card
bool Player::useKnight() {
    return useDevelopmentCard("knight");
}

// Function to use victory point development card
bool Player::useVictoryPoint() {
    addVictoryPoints(1);
    return useDevelopmentCard("victory_point");
}

// Function to use road building development card
bool Player::useRoadBuilding() {
    return useDevelopmentCard("road_building");
}

// Function to use year of plenty development card
bool Player::useYearOfPlenty() {
    return useDevelopmentCard("year_of_plenty");
}

// Function to use monopoly development card
bool Player::useMonopoly() {
    return useDevelopmentCard("monopoly");
}

// Function to check if player can use a development card
bool Player::canUseDevelopmentCard(const std::string& cardType) const {
    return getDevelopmentCardCount(cardType) > 0;
}

// Function to add advancement card to player
void Player::addAdvancementCard(Resource resource) {
    advancementCards[resource]++;
}

// Function to use an advancement card
bool Player::useAdvancementCard(Resource resourceType) {
    auto it = advancementCards.find(resourceType);
    if (it != advancementCards.end() && it->second > 0) {
        it->second--;
        return true;
    }
    return false;
}

// Function to print player's resources
void Player::printResources() const {
    for (const auto& resource : resources) {
        std::cout << resource.first << ": " << resource.second << std::endl;
    }
}

// Function to place a road
void Player::placeRoad(int edgeIndex) {
    if (canBuyRoad()) {
        removeResource(WOOD, 1);
        removeResource(BRICK, 1);
        addRoad(edgeIndex);
    } else {
        std::cout << "Not enough resources to place a road.\n";
    }
}

// Function to build a settlement
void Player::buildSettlement(int vertexIndex) {
    if (canBuySettlement()) {
        removeResource(WOOD, 1);
        removeResource(BRICK, 1);
        removeResource(SHEEP, 1);
        removeResource(WHEAT, 1);
        addSettlement(vertexIndex);
        addVictoryPoints(1);
    } else {
        std::cout << "Not enough resources to build a settlement.\n";
    }
}

// Function to buy a development card
void Player::buyDevelopmentCard() {
    // Assume each development card costs 1 wheat, 1 sheep, and 1 ore
    if (hasResource(WHEAT, 1) && hasResource(SHEEP, 1) && hasResource(CLAY, 1)) {
        removeResource(WHEAT, 1);
        removeResource(SHEEP, 1);
        removeResource(CLAY, 1);
        // Add a development card to the player's collection
    } else {
        std::cout << "Not enough resources to buy a development card.\n";
    }
}

// Function to build a city
void Player::buildCity(int vertexIndex) {
    if (canBuyCity()) {
        removeResource(WHEAT, 2);
        removeResource(CLAY, 3);
        // Assume adding a city replaces a settlement
        // Additional logic to handle city building
        addVictoryPoints(1);
    } else {
       std::cout << "Not enough resources to build a city.\n";
    }
}

// Function to place initial settlement
void Player::placeInitialSettlement(int vertexIndex) {
    // Check if the location is occupied
    for (const auto& settlement : settlements) {
        if (settlement == vertexIndex) {
            std::cout << "Settlement already exists at this vertex.\n";
        }
    }

    // Check that the settlement is not within two edges of another settlement
    for (const auto& settlement : settlements) {
        if (abs(settlement - vertexIndex) <= 2) {
            std::cout << "Cannot place a settlement within two edges of another settlement.\n";
        }
    }
    addVictoryPoints(1);
    addSettlement(vertexIndex);
    // Additional logic to handle initial settlement placement
}

// Function to place initial road
void Player::placeInitialRoad(int edgeIndex) {
    // Check if the location is occupied
    for (const auto& road : roads) {
        if (road == edgeIndex) {
            std::cout << "Road already exists at this edge.\n";
        }
    }

    // Check that the initial road is placed adjacent to an initial settlement
    bool adjacentToSettlement = false;
    for (const auto& settlement : settlements) {
        if (abs(settlement - edgeIndex) == 1) {
            adjacentToSettlement = true;
            break;
        }
    }

    if (!adjacentToSettlement) {
        std::cout << "Initial road must be placed adjacent to an initial settlement.\n";
    }

    addRoad(edgeIndex);
    // Additional logic to handle initial road placement
}

// Function to print player's status
void Player::printStatus() const {
    std::cout << "Player: " << name << '\n';
    std::cout << "Resources:\n";
    for (const auto& pair : resources) {
        std::cout << "  " << Hexagon::resourceToString(pair.first) << ": " << pair.second << '\n';
    }
    std::cout << "Development Cards:\n";
    for (const auto& pair : developmentCards) {
        std::cout << "  " << pair.first << ": " << pair.second << '\n';
    }
    std::cout << "Victory Points: " << victoryPoints << '\n';
    std::cout << "Turn: " << (turn ? "Yes" : "No") << '\n';
}

// Function to set the board for player
void Player::setBoard(Board* board) {
    this->board = board;
}
