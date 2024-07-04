// sapirblumshtein@gmail.com

#include "Board.hpp"
#include "Hexagon.hpp"
#include <iostream>
#include <algorithm>  // For std::find_if
#include <cstdlib>    // For std::rand and std::srand
#include <ctime>

// Constructor: Initializes the board
Board::Board() {
    initializeBoard();
}

// Returns all hexagons on the board
const std::vector<Hexagon>& Board::getHexagons() const {
    return hexagons;
}

// Returns all vertices on the board
const std::vector<Vertex>& Board::getVertices() const {
    return vertices;
}

// Returns all edges on the board
const std::vector<Edge>& Board::getEdges() const {
    return edges;
}

// Returns all players in the game
const std::vector<Player*>& Board::getPlayers() const {
    return players;
}

// Checks if a settlement can be placed at the given vertex
bool Board::canPlaceSettlement(Player* player, const Vertex& vertex) const {
    if (vertex.getStructure() != Vertex::Structure::None) {
        return false;
    }
    for (const auto* neighbor : vertex.getNeighbors()) {
        if (neighbor->getStructure() != Vertex::Structure::None) {
            return false;
        }
    }
    for (const auto* edge : vertex.getEdges()) {
        if (edge->getOwner() == player) {
            return true;
        }
    }
    return false;
}

// Checks if a road can be placed at the given edge
bool Board::canPlaceRoad(Player* player, const Edge& edge) const {
    if (edge.getOwner() != nullptr) {
        std::cout << "Edge is already occupied by another road.\n";
        return false; // Edge is already owned
    }

    int v1 = edge.getVertex1();
    int v2 = edge.getVertex2();

    // Check if the player owns one of the vertices connected by the edge
    if (vertices[v1].getOwner() == player || vertices[v2].getOwner() == player) {
        return true;
    }

    // Check if the player owns any neighboring edge
    auto ownedByPlayer = [player](const Edge& e) { return e.getOwner() == player; };
    return std::any_of(edges.begin(), edges.end(), ownedByPlayer);
}

// Checks if a city can be placed at the given vertex
bool Board::canPlaceCity(Player* player, const Vertex& vertex) const {
    return vertex.getOwner() == player && vertex.getStructure() == Vertex::Structure::Settlement;
}

// Builds a road for the player at the specified edge
bool Board::buildRoad(Player* player, int edgeIndex) {
    if (edgeIndex >= 0 && static_cast<std::vector<Edge>::size_type>(edgeIndex) < edges.size() &&
        canPlaceRoad(player, edges[edgeIndex])) {
        
        edges[edgeIndex].buildRoad(player);
        player->addRoad(edgeIndex);
        return true;
    }
    return false;
}

// Builds a settlement for the player at the specified vertex
bool Board::buildSettlement(Player* player, int vertexIndex) {
    Vertex& vertex = vertices.at(vertexIndex);

    if (vertex.getOwner() != nullptr) {
         std::cout << "Vertex is already occupied by another structure.\n";
         return false;
    }

    if (!player->canBuySettlement()) {
        return false;
    }

    vertex.setOwner(player);
    vertex.setStructure(Vertex::Structure::Settlement);
    return true;
}

// Builds a city for the player at the specified vertex
bool Board::buildCity(Player* player, int vertexIndex) {
    Vertex& vertex = vertices.at(vertexIndex);

    if (vertex.getOwner() != player) {
        std::cout << "Player does not own this settlement.";
    }

    if (vertex.getStructure() != Vertex::Structure::Settlement) {
        std::cout << "No settlement to upgrade to city.";
    }

    if (!player->canBuyCity()) {
        return false;
    }

    vertex.setStructure(Vertex::Structure::City);
    return true;
}

// Checks if a given edge is connected to the player's existing structures
bool Board::isConnected(Player* player, std::size_t edgeIndex) const {
    if (edgeIndex < 0 || edgeIndex >= edges.size()) return false;
    const Edge& edge = edges[edgeIndex];
    int v1 = edge.getVertex1();
    int v2 = edge.getVertex2();
    return vertices[v1].getOwner() == player || vertices[v2].getOwner() == player ||
           (vertices[v1].getOwner() == player && vertices[v2].getOwner() == player);
}

// Initializes the board with default settings
void Board::initializeBoard() {
    std::cout << "Initializing the board with initial placements.\n";
    vertices.resize(54);
    edges.resize(72);

    hexagons = {
        {WHEAT, 5}, {WOOD, 2}, {BRICK, 6},
        {SHEEP, 3}, {WOOD, 8}, {BRICK, 10},
        {WHEAT, 9}, {CLAY, 12}, {SHEEP, 11},
        {DESERT, 7}, {SHEEP, 6}, {CLAY, 4},
        {WOOD, 8}, {WHEAT, 11}, {WOOD, 9},
        {WHEAT, 11}, {SHEEP, 3}, {WOOD, 4},
        {CLAY, 5}
    };

    int vertexMapping[19][6] = {
        {0, 1, 2, 3, 4, 5}, {3, 6, 7, 8, 9, 4}, {8, 10, 11, 12, 13, 9},
        {12, 14, 15, 16, 17, 13}, {5, 4, 9, 18, 19, 20}, {9, 13, 21, 22, 23, 18},
        {13, 17, 24, 25, 26, 21}, {26, 25, 27, 28, 29, 30}, {18, 23, 31, 32, 33, 34},
        {23, 21, 26, 30, 35, 31}, {30, 29, 36, 37, 38, 35}, {35, 34, 39, 40, 41, 36},
        {31, 35, 42, 43, 44, 45}, {36, 41, 46, 47, 48, 39}, {45, 44, 49, 50, 51, 52},
        {39, 48, 53, 54, 55, 46}, {46, 41, 40, 39, 48, 47}, {50, 49, 51, 52, 53, 54},
        {52, 51, 54, 55, 56, 53}
    };

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 6; ++j) {
            int vertexIndex = vertexMapping[i][j];
            if (vertexIndex >= 0 && static_cast<std::vector<Vertex>::size_type>(vertexIndex) < vertices.size()) {
                hexagons[i].addVertex(&vertices[vertexIndex]);
            }
        }
    }

    int edgeMapping[19][6][2] = {
        {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}},
        {{3, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 4}, {4, 3}},
        {{8, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 9}, {9, 8}},
        {{12, 14}, {14, 15}, {15, 16}, {16, 17}, {17, 13}, {13, 12}},
        {{5, 4}, {4, 9}, {9, 18}, {18, 19}, {19, 20}, {20, 5}},
        {{9, 13}, {13, 21}, {21, 22}, {22, 23}, {23, 18}, {18, 9}},
        {{13, 17}, {17, 24}, {24, 25}, {25, 26}, {26, 21}, {21, 13}},
        {{26, 25}, {25, 27}, {27, 28}, {28, 29}, {29, 30}, {30, 26}},
        {{18, 23}, {23, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 18}},
        {{23, 21}, {21, 26}, {26, 30}, {30, 35}, {35, 31}, {31, 23}},
        {{30, 29}, {29, 36}, {36, 37}, {37, 38}, {38, 35}, {35, 30}},
        {{35, 34}, {34, 39}, {39, 40}, {40, 41}, {41, 36}, {36, 35}},
        {{31, 35}, {35, 42}, {42, 43}, {43, 44}, {44, 45}, {45, 31}},
        {{36, 41}, {41, 46}, {46, 47}, {47, 48}, {48, 39}, {39, 36}},
        {{45, 44}, {44, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 45}},
        {{39, 48}, {48, 53}, {53, 54}, {54, 55}, {55, 46}, {46, 39}},
        {{46, 41}, {41, 40}, {40, 39}, {39, 48}, {48, 47}, {47, 46}},
        {{50, 49}, {49, 51}, {51, 52}, {52, 53}, {53, 54}, {54, 50}},
        {{52, 51}, {51, 54}, {54, 55}, {55, 56}, {56, 53}, {53, 52}}
    };

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 6; ++j) {
            int v1 = edgeMapping[i][j][0];
            int v2 = edgeMapping[i][j][1];
            if (v1 >= 0 && v2 >= 0 &&
                static_cast<std::vector<Vertex>::size_type>(v1) < vertices.size() &&
                static_cast<std::vector<Vertex>::size_type>(v2) < vertices.size()) {
                Edge edge(v1, v2);
                edges.push_back(edge);
            }
        }
    }

    Player* player1 = new Player("Player 1");
    Player* player2 = new Player("Player 2");
    Player* player3 = new Player("Player 3");
    Player* player4 = new Player("Player 4");

    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    for (auto* player : players) {
        if (player == nullptr) continue;

        std::vector<int> startingVertices = {0, 3, 6, 9}; // Different initial vertices for players
        std::vector<int> startingEdges = {0, 3, 6, 9};    // Different initial edges for players

        player->addVictoryPoints(2);

        for (int vertexIndex : startingVertices) {
            if (vertexIndex >= 0 && static_cast<std::vector<Vertex>::size_type>(vertexIndex) < vertices.size()) {
                vertices[vertexIndex].buildSettlement(player);
                player->receiveResources(hexagons, vertexIndex);
                player->addSettlement(vertexIndex);
            }
        }

        for (int edgeIndex : startingEdges) {
            if (edgeIndex >= 0 && static_cast<std::vector<Edge>::size_type>(edgeIndex) < edges.size()) {
                edges[edgeIndex].buildRoad(player);
                player->addRoad(edgeIndex);
            }
        }
    }
}

// Distributes resources based on the dice roll
void Board::distributeResources(int diceRoll) {
    std::cout << "Distributing resources for dice roll: " << diceRoll << std::endl;
    for (auto& hexagon : hexagons) {
        if (hexagon.getNumber() == diceRoll) {
            for (auto* vertex : hexagon.getVertices()) {
                if (vertex->getOwner() != nullptr) {
                    Player* owner = vertex->getOwner();
                    Resource resource = hexagon.getResource();
                    owner->addResource(resource, 1);
                    std::cout << owner->getName() << " receives 1 " << Hexagon::resourceToString(resource) << "(s) from hexagon with number " << hexagon.getNumber() << std::endl;
                }
            }
        }
    }
}

// Sets the players in the game
void Board::setPlayers(const std::vector<Player*>& newPlayers) {
    players = newPlayers;
}

// Draws a development card for the specified player
void Board::drawDevelopmentCard(int playerId) {
    static const std::vector<std::string> cardTypes = {"Knight", "victory_point", "road_building", "year_of_plenty", "monopol"};

    if (playerId >= 0 && static_cast<std::vector<Player*>::size_type>(playerId) < players.size()) {
        std::string cardType = cardTypes[rand() % cardTypes.size()];
        DevelopCard* card = nullptr;

        if (cardType == "Knight") {
            card = new Knight();
        } else if (cardType == "victory_point") {
            card = new victoryPoint();
        } else if (cardType == "road_building") {
            card = new roadBuilding();
        } else if (cardType == "year_of_plenty") {
            card = new YearOfPlenty();
        } else if (cardType == "monopol") {
            card = new monopol();
        }

        if (card) {
            players[playerId]->addDevelopmentCard(*card);

            if (cardType == "Knight") {
                int knightCount = players[playerId]->getDevelopmentCardCount("Knight");
                if (knightCount > biggestArmy) {
                    biggestArmy = knightCount;
                    biggestArmyIndex = playerId;
                    players[playerId]->addVictoryPoints(2);
                }
            } else if (cardType == "victory_point") {
                players[playerId]->addVictoryPoints(1);
            }

            delete card;
        }
    }
}

// Prints the winner of the game
void Board::printWinner() {
    int maxPoints = -1;
    for (std::size_t i = 0; i < players.size(); ++i) {
        int points = players[i]->getVictoryPoints();
        if (points >= 10) {
            winnerIndex = i;
            std::cout << "Player " << players[i]->getName() << " wins with " << points << " points!\n";
            return;
        }
        if (points > maxPoints) {
            maxPoints = points;
        }
    }
    if (winnerIndex == -1) {
        std::cout << "No player has won yet. Highest points: " << maxPoints << "\n";
    }
}

// Prints the current state of the board
void Board::printBoard() const {
    std::vector<std::string> hexagonStrings;

    for (const auto& hex : hexagons) {
        hexagonStrings.push_back(Hexagon::resourceToString(hex.getResource()) + " " + std::to_string(hex.getNumber()));
    }

    const int numRows = 7;

    std::vector<std::vector<int>> boardLayout = {
        { -1, -1, -1, -1, -1, -1, -1 },
        { -1, -1,  0,  1,  2, -1, -1 },
        { -1,  3,  4,  5,  6,  -1 },
        { -1,  7,  8,  9, 10, 11, -1 },
        { -1, 12, 13, 14, 15,  -1 },
        { -1, -1, 16, 17, 18, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1 }
    };

    std::cout << "************ CATAN BOARD ************\n";

    for (int row = 0; row < numRows; ++row) {
        std::string rowOutput;

        if (row == 0 || row == numRows - 1) {
            rowOutput = "       sea   sea   sea   sea   sea       ";
        } else if (row == 1 || row == numRows - 2) {
            rowOutput = "    sea " + hexagonStrings[boardLayout[row][2]] + " " +
                        hexagonStrings[boardLayout[row][3]] + " " +
                        hexagonStrings[boardLayout[row][4]] + " sea    ";
        } else if (row == 2) {
            rowOutput = "  sea " + hexagonStrings[boardLayout[row][1]] + " " +
                        hexagonStrings[boardLayout[row][2]] + " " +
                        hexagonStrings[boardLayout[row][3]] + " " +
                        hexagonStrings[boardLayout[row][4]] + " " +
                        hexagonStrings[boardLayout[row][5]] + " sea  ";
        } else if (row == 3) {
            rowOutput = "sea " + hexagonStrings[boardLayout[row][1]] + " " +
                        hexagonStrings[boardLayout[row][2]] + " " +
                        hexagonStrings[boardLayout[row][3]] + " " +
                        hexagonStrings[boardLayout[row][4]] + " " +
                        hexagonStrings[boardLayout[row][5]] + " " +
                        hexagonStrings[boardLayout[row][6]] + " sea";
        } else if (row == 4) {
            rowOutput = "  sea " + hexagonStrings[boardLayout[row][1]] + " " +
                        hexagonStrings[boardLayout[row][2]] + " " +
                        hexagonStrings[boardLayout[row][3]] + " " +
                        hexagonStrings[boardLayout[row][4]] + " " +
                        hexagonStrings[boardLayout[row][5]] + " sea  ";
        
        } else if (row == 6) {
            rowOutput = "       sea " + hexagonStrings[boardLayout[row][3]] + " sea       ";
        }

        std::cout << rowOutput << "\n";
    }

    std::cout << "*************************************\n";
}
