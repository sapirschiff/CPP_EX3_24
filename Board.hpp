#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Hexagon.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

class Player;  // Forward declaration

class Board {
public:
    Board();
    const std::vector<Hexagon>& getHexagons() const;
    const std::vector<Vertex>& getVertices() const;
    const std::vector<Edge>& getEdges() const;
    const std::vector<Player*>& getPlayers() const;

    
    bool canPlaceSettlement(Player* player, const Vertex& vertex) const;
    bool canPlaceRoad(Player* player, const Edge& edge) const;
    bool canPlaceCity(Player* player, const Vertex& vertex) const;

    bool buildSettlement(Player* player, int vertexIndex);
    bool buildRoad(Player* player, int edgeIndex);
    bool buildCity(Player* player, int vertexIndex);

    bool isConnected(Player* player, std::size_t edgeIndex) const;
    void printBoard() const;

    void drawDevelopmentCard(int playerId);
    void printWinner();
    void setPlayers(const std::vector<Player*>& newPlayers);
    void distributeResources(int diceRoll);

private:
    void initializeBoard();
    std::vector<Hexagon> hexagons;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    int biggestArmyIndex = -1;
    int biggestArmy = 2;
    std::vector<Player*> players;
    int winnerIndex = -1;
    std::string formatHexagon(int index) const;
};

#endif // BOARD_HPP
