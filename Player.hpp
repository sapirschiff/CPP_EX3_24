// sapirblumshtein@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "DevelopCard.hpp"
#include "Resource.hpp"
#include "Board.hpp" 

class Board;   // Forward declaration for Board class
class Hexagon; // Forward declaration for Hexagon class
class Vertex;  // Forward declaration for Vertex class

class Player {
public:
    Player(const std::string& name); // Constructor
    ~Player(); // Destructor

    void addResource(Resource resource, int amount); // Add resources to player
    bool removeResource(Resource resource, int amount); // Remove resources from player
    bool hasResource(Resource resource, int amount) const; // Check if player has specific resources
    const std::unordered_map<Resource, int>& getResources() const; // Get player's resources

    void addDevelopmentCard(const DevelopCard& card); // Add development card to player
    bool useDevelopmentCard(const std::string& cardType); // Use a development card
    int getDevelopmentCardCount(const std::string& cardType) const; // Get count of specific development card

    void addAdvancementCard(Resource resource); // Add advancement card to player
    bool useAdvancementCard(Resource resourceType); // Use an advancement card

    void addVictoryPoints(int points); // Add victory points to player
    int getVictoryPoints() const; // Get player's victory points
    bool isTurn() const; // Check if it's player's turn
    void setTurn(bool turn); // Set player's turn
    void printStatus() const; // Print player's status
    std::string getName() const; // Get player's name
    void initializeResources(const std::vector<Resource>& initialResources); // Initialize player's resources

    void rollDice(); // Roll dice for player
    void discardResources(); // Discard resources if needed
    void addSettlement(int vertexIndex); // Add settlement to player
    void addRoad(int edgeIndex); // Add road to player
    void receiveResources(const std::vector<Hexagon>& hexagons, int vertexIndex); // Receive resources from hexagons
    int getDiceRoll() const; // Get dice roll value
    const std::vector<int>& getSettlements() const; // Get player's settlements
    const std::vector<int>& getRoads() const; // Get player's roads
    void getCities(const std::vector<Vertex>& vertices) const; // Get player's cities
    void tradeResources(Player& otherPlayer, Resource resource1, int amount1, Resource resource2, int amount2); // Trade resources between players

    bool canBuySettlement() const; // Check if player can buy a settlement
    bool canBuyCity() const; // Check if player can buy a city
    bool canBuyRoad() const; // Check if player can buy a road
    bool canUseDevelopmentCard(const std::string& cardType) const; // Check if player can use a development card

    bool useKnight(); // Use knight development card
    bool useRoadBuilding(); // Use road building development card
    bool useYearOfPlenty(); // Use year of plenty development card
    bool useMonopoly(); // Use monopoly development card
    bool useVictoryPoint(); // Use victory point development card

    void placeInitialSettlement(int vertexIndex); // Place initial settlement
    void placeInitialRoad(int edgeIndex); // Place initial road
    void printResources() const; // Print player's resources
    void placeRoad(int edgeIndex); // Place road
    void buildSettlement(int vertexIndex); // Build settlement
    void buyDevelopmentCard(); // Buy development card
    void buildCity(int vertexIndex); // Build city
    void setBoard(Board* board); // Set the board for player

private:
    std::string name;
    int victoryPoints;
    bool turn;
    int diceRoll;
    std::vector<DevelopCard*> cards;
    std::unordered_map<Resource, int> resources;
    std::unordered_map<Resource, int> advancementCards;
    std::unordered_map<std::string, int> developmentCards;
    std::vector<Vertex> vertices;
    std::vector<int> settlements;
    std::vector<int> roads;
    Board* board;
};

#endif  // PLAYER_HPP
