// sapirblumshtein@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "Hexagon.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Player.hpp"

class Hexagon;
class Vertex;
class Player;
class Edge;

class Board {
public:
    // Constructor: Initializes the board
    Board();

    // Returns all hexagons on the board
    const std::vector<Hexagon>& getHexagons() const;

    // Returns all vertices on the board
    const std::vector<Vertex>& getVertices() const;

    // Returns all edges on the board
    const std::vector<Edge>& getEdges() const;

    // Returns all players in the game
    const std::vector<Player*>& getPlayers() const;

    // Checks if a settlement can be placed at the given vertex
    bool canPlaceSettlement(Player* player, const Vertex& vertex) const;

    // Checks if a road can be placed at the given edge
    bool canPlaceRoad(Player* player, const Edge& edge) const;

    // Checks if a city can be placed at the given vertex
    bool canPlaceCity(Player* player, const Vertex& vertex) const;

    // Builds a settlement for the player at the specified vertex
    bool buildSettlement(Player* player, int vertexIndex);

    // Builds a road for the player at the specified edge
    bool buildRoad(Player* player, int edgeIndex);

    // Builds a city for the player at the specified vertex
    bool buildCity(Player* player, int vertexIndex);

    // Checks if a given edge is connected to the player's existing structures
    bool isConnected(Player* player, std::size_t edgeIndex) const;

    // Prints the current state of the board
    void printBoard() const;

    // Draws a development card for the specified player
    void drawDevelopmentCard(int playerId);

    // Prints the winner of the game
    void printWinner();

    // Sets the players in the game
    void setPlayers(const std::vector<Player*>& newPlayers);

    // Distributes resources based on the dice roll
    void distributeResources(int diceRoll);

    // Initializes the board with default settings
    void initializeBoard();

private:
    std::vector<Hexagon> hexagons; // List of hexagons on the board
    std::vector<Vertex> vertices;  // List of vertices on the board
    std::vector<Edge> edges;       // List of edges on the board
    int biggestArmyIndex = -1;     // Index of the player with the biggest army
    int biggestArmy = 3;           // Size of the biggest army
    std::vector<Player*> players;  // List of players in the game
    int winnerIndex = -1;          // Index of the winner

    // Formats the hexagon information for printing
    std::string formatHexagon(int index) const;
};

#endif // BOARD_HPP
