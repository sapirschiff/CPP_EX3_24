// Player.cpp
#include "Player.hpp"
#include "Board.hpp"
#include "Hexagon.hpp"
#include "Vertex.hpp"
#include "AdvancementCard.hpp"
#include <iostream>
#include <cstdlib>
#include <random>


// Constructor initializing player's name, victory points, and turn
Player::Player(const std::string& name)
    : name(name), victoryPoints(0), turn(false) {}
    
// Method to discard resources if the player has more than 7 and the roll dice is 7
void Player::discardResources() {
    int totalResources = 0;
    for (const auto& pair : resources) {
        totalResources += pair.second;
    }
    // If the player has more than 7 resources, they must discard half (rounded down)
    if (totalResources > 7) {
        int resourcesToDiscard = totalResources / 2;
        std::cout << name << " needs to discard " << resourcesToDiscard << " resource cards.\n";

        // Discard resources in arbitrary order; in a real game, the player would choose
        for (auto& pair : resources) {
            int discardAmount = std::min(pair.second, resourcesToDiscard);
            pair.second -= discardAmount;
            resourcesToDiscard -= discardAmount;

            if (resourcesToDiscard <= 0) break;
        }
    }
}

// Adds a specified amount of a resource to the player's resources
void Player::addResource(const std::string& resource, int amount) { 
    resources[resource] += amount;
}

const std::unordered_map<std::string, int>& Player::getResources() const {
    return resources;
}
// Remove a specified amount of a resource from the player's resources
bool Player::removeResource(const std::string& resource, int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
        return true;
    }
    return false;
}

// Checks if the player has at least a specified amount of a resource
bool Player::hasResource(const std::string& resource, int amount) const {
    auto it = resources.find(resource);
    return it != resources.end() && it->second >= amount;
}

// Adds a development card to the player's collection
void Player::addDevelopmentCard(const DevelopCard& card) {
    developmentCards[card.getType()]++;
}

// Uses a development card from the player's possession
bool Player::useDevelopmentCard(const std::string& cardType) {
    auto it = developmentCards.find(cardType);
    if ((cardType == "victory_point" ))
    {
        
    }
    
    if (it != developmentCards.end() && it->second > 0) {
        it->second--;
        return true;
    }
    return false;
}

// Gets the count of a specific type of development card
int Player::getDevelopmentCardCount(const std::string& cardType) const {
    auto it = developmentCards.find(cardType);
    return (it != developmentCards.end()) ? it->second : 0;
}

// Adds a specified number of victory points to the player's total
void Player::addVictoryPoints(int points) {
    victoryPoints += points;
}

// Gets the current total of the player's victory points
int Player::getVictoryPoints() const {
    return victoryPoints;
}

// Checks if it is currently the player's turn
bool Player::isTurn() const {
    return turn;
}

// Sets whether it is currently the player's turn
void Player::setTurn(bool turn) {
    this->turn = turn;
}

// Initializes the player's resources with a list of starting resources
void Player::initializeResources(const std::vector<std::string>& initialResources) {
    for (const auto& resource : initialResources) {
        addResource(resource, 1);
    }
}

// Prints the cities owned by the player
void Player::getCities(const std::vector<Vertex>& vertices) const {
    std::cout << "Cities for player " << name << ":" << std::endl;
    for (const auto& vertex : vertices) {
        if (vertex.getOwner() == this && vertex.getStructure() == Vertex::Structure::City) {
            // Print or process city information
            std::cout << "City at vertex index: " << &vertex - &vertices[0] << std::endl;  // Example: using pointer arithmetic
        }
    }
}

// Simulates rolling a dice
void Player::rollDice() {
    diceRoll = rand() % 6 + 1;
}

// Adds a settlement to the player's list of settlements
void Player::addSettlement(int vertexIndex) {
    settlements.push_back(vertexIndex);
}

// Adds a road to the player's list of roads
void Player::addRoad(int edgeIndex) {
    roads.push_back(edgeIndex);
}

// Gets the result of the last dice roll
int Player::getDiceRoll() const {
    return diceRoll;
}

// Gets a constant reference to the player's list of settlements
const std::vector<int>& Player::getSettlements() const {
    return settlements;
}

// Gets a constant reference to the player's list of roads
const std::vector<int>& Player::getRoads() const {
    return roads;
}

// Receives resources from the initial setup based on the placement of the settlement
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

// Gets the player's name
std::string Player::getName() const {
    return name;
}

// Trade resources with another player
void Player::tradeResources(Player& otherPlayer, const std::string& resource1, int amount1, const std::string& resource2, int amount2) {
    if (amount1 <= 0 || amount2 <= 0) {
        std::cout << "Trade amounts must be positive." << std::endl;
        return;
    }

    if (!hasResource(resource1, amount1)) {
        std::cout << name << " does not have enough " << resource1 << " to trade." << std::endl;
        return;
    }

    if (!otherPlayer.hasResource(resource2, amount2)) {
        std::cout << otherPlayer.getName() << " does not have enough " << resource2 << " to trade." << std::endl;
        return;
    }

    removeResource(resource1, amount1);
    otherPlayer.removeResource(resource2, amount2);
    addResource(resource2, amount2);
    otherPlayer.addResource(resource1, amount1);

    std::cout << name << " traded " << amount1 << " " << resource1 << " with " << otherPlayer.getName() << " for " << amount2 << " " << resource2 << "." << std::endl;
}

// Checks if the player can buy a settlement
bool Player::canBuySettlement() const {
    return hasResource("Brick", 1) && hasResource("Wood", 1) && hasResource("Sheep", 1) && hasResource("Wheat", 1);
}

// Checks if the player can buy a city
bool Player::canBuyCity() const {
    return hasResource("Clay", 3) && hasResource("Wheat", 2);
}

// Checks if the player can buy a road
bool Player::canBuyRoad() const {
    return hasResource("Brick", 1) && hasResource("Wood", 1);
}

// Uses a knight development card
bool Player::useKnight() {
    return useDevelopmentCard("knight");
}
bool Player::useVictoryPoint() {
    addVictoryPoints(1);
    return useDevelopmentCard("Victory_point");
}

// Uses a road building development card
bool Player::useRoadBuilding() {
    return useDevelopmentCard("road_building");
}

// Uses a year of plenty development card
bool Player::useYearOfPlenty() {
    return useDevelopmentCard("year_of_plenty");
}

// Uses a monopoly development card
bool Player::useMonopoly() {
    return useDevelopmentCard("monopoly");
}

// Checks if the player can use a specific type of development card
bool Player::canUseDevelopmentCard(const std::string& cardType) const {
    return getDevelopmentCardCount(cardType) > 0;
}

// Adds an advancement card to the player's possession
void Player::addAdvancementCard(const AdvancementCard& card) {
    advancementCards[card.getResourceType()]++;
}

// Uses an advancement card from the player's possession
bool Player::useAdvancementCard(AdvancementCard::ResourceType resourceType) {
    auto it = advancementCards.find(resourceType);
    if (it != advancementCards.end() && it->second > 0) {
        it->second--;
        return true;
    }
    return false;
}

// Prints the current status of the player
void Player::printStatus() const {
    std::cout << "Player: " << name << std::endl;
    std::cout << "Resources:" << std::endl;
    for (const auto& pair : resources) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "Development Cards:" << std::endl;
    for (const auto& pair : developmentCards) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "Victory Points: " << victoryPoints << std::endl;
    std::cout << "Turn: " << (turn ? "Yes" : "No") << std::endl;
}
