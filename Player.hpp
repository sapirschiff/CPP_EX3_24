#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "DevelopCard.hpp"
#include "AdvancementCard.hpp"



class Hexagon;
class Vertex;

class Player {
public:
    Player(const std::string& name);

    void addResource(const std::string& resource, int amount);
    bool removeResource(const std::string& resource, int amount);
    bool hasResource(const std::string& resource, int amount) const;
    const std::unordered_map<std::string, int>& getResources() const;


    void addDevelopmentCard(const DevelopCard& card);
    bool useDevelopmentCard(const std::string& cardType);
    int getDevelopmentCardCount(const std::string& cardType) const;

    void addAdvancementCard(const AdvancementCard& card);//
    bool useAdvancementCard(AdvancementCard::ResourceType resourceType);//

    void addVictoryPoints(int points);
    int getVictoryPoints() const;
    bool isTurn() const;
    void setTurn(bool turn);
    void printStatus() const;
    std::string getName() const;
    void initializeResources(const std::vector<std::string>& initialResources) ;

    // Game actions
    void rollDice();
    void discardResources(); // to remove resoccrse if the number is 7
    void addSettlement(int vertexIndex);
    void addRoad(int edgeIndex);
    void receiveResources(const std::vector<Hexagon>& hexagons, int vertexIndex);//
    int getDiceRoll() const;//
    const std::vector<int>& getSettlements() const;
    const std::vector<int>& getRoads() const;
    void getCities(const std::vector<Vertex>& vertices) const;
    void tradeResources(Player& otherPlayer, const std::string& resource1, int amount1, const std::string& resource2, int amount2);

    // Check if player can buy or use certain actions
    bool canBuySettlement() const;
    bool canBuyCity() const;
    bool canBuyRoad() const;
    bool canUseDevelopmentCard(const std::string& cardType) const;

    // Use development cards
    bool useKnight();
    bool useRoadBuilding();
    bool useYearOfPlenty();
    bool useMonopoly();
    bool useVictoryPoint() ;

private:
    std::string name;
    int victoryPoints;
    bool turn;
    int diceRoll;
    std::unordered_map<std::string, int> resources;
    std::unordered_map<AdvancementCard::ResourceType, int> advancementCards;
    std::unordered_map<std::string, int> developmentCards;
    std::vector<Vertex> vertices;
    std::vector<int> settlements;
    std::vector<int> roads;
};

#endif  // PLAYER_HPP
