#include "Board.hpp"
#include "Hexagon.hpp"
#include <iostream>
#include <algorithm>  // For std::find_if
#include <cstdlib>    // For std::rand and std::srand
#include <ctime> 

Board::Board() {
    initializeBoard();
}

const std::vector<Hexagon>& Board::getHexagons() const {
    return hexagons;
}

const std::vector<Vertex>& Board::getVertices() const {
    return vertices;
}

const std::vector<Edge>& Board::getEdges() const {
    return edges;
}

const std::vector<Player*>& Board::getPlayers() const {
    return players;
}

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

bool Board::canPlaceRoad(Player* player, const Edge& edge) const {
    if (edge.getOwner() != nullptr) {
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


bool Board::canPlaceCity(Player* player, const Vertex& vertex) const {
    return vertex.getOwner() == player && vertex.getStructure() == Vertex::Structure::Settlement;
}

bool Board::buildSettlement(Player* player, int vertexIndex) {
        std::cout << "Attempting to build settlement for player " << player->getName() << " at vertex " << vertexIndex << std::endl;
    // Check if the vertexIndex is valid and if the player can place a settlement at the specified vertex
    if (vertexIndex >= 0 && static_cast<std::vector<Vertex>::size_type>(vertexIndex) < vertices.size() &&
        canPlaceSettlement(player, vertices[vertexIndex])) {
        
        // Add 1 victory point to the player
        player->addVictoryPoints(1);
        
        // Build the settlement at the specified vertex
        vertices[vertexIndex].buildSettlement(player);
        
        // Record the settlement in the player's data
        player->addSettlement(vertexIndex);
        std::cout << "Settlement built successfully." << std::endl;
        return true;  // Indicate that the settlement was successfully built
    }
    std::cout << "Failed to build settlement." << std::endl;
    return false;  // Indicate that the settlement could not be built
}

bool Board::buildRoad(Player* player, int edgeIndex) {
    // Check if the edgeIndex is valid and if the player can place a road at the specified edge
    if (edgeIndex >= 0 && static_cast<std::vector<Edge>::size_type>(edgeIndex) < edges.size() &&
        canPlaceRoad(player, edges[edgeIndex])) {
        
        // Build the road at the specified edge
        edges[edgeIndex].buildRoad(player);
        
        // Record the road in the player's data
        player->addRoad(edgeIndex);
        
        return true;  // Indicate that the road was successfully built
    }
    
    return false;  // Indicate that the road could not be built
}

bool Board::buildCity(Player* player, int vertexIndex) {

    // Check if player has enough resources
    if (!player->hasResource("Wheat", 2) || !player->hasResource("Clay", 3)) {
        std::cout << "Player does not have enough resources to build a city." << std::endl;
        return false;
    }

    if (vertexIndex >= 0 && static_cast<std::vector<Vertex>::size_type>(vertexIndex) < vertices.size() &&
        vertices[vertexIndex].getOwner() == player && vertices[vertexIndex].canBuildSettlement()) {
        
        player->removeResource("Clay", 3);
        player->removeResource("Wheat", 2);
    

        vertices[vertexIndex].upgradeToCity();

        std::cout << "City successfully built for player " << player->getName() << " at vertex " << vertexIndex << std::endl;

        return true;
    } else {
        std::cout << "Cannot build city at vertex " << vertexIndex << " for player " << player->getName() << std::endl;
        return false;
    }
}

bool Board::isConnected(Player* player, std::size_t edgeIndex) const {
    if (edgeIndex < 0 || edgeIndex >= edges.size()) return false;
    const Edge& edge = edges[edgeIndex];
    int v1 = edge.getVertex1();
    int v2 = edge.getVertex2();
    return vertices[v1].getOwner() == player || vertices[v2].getOwner() == player ||
           (vertices[v1].getOwner() == player && vertices[v2].getOwner() == player);
}

void Board::initializeBoard() {
    // Resize vertices and edges to appropriate sizes
    vertices.resize(54);
    edges.resize(72);

    // Initialize hexagons
    hexagons = {
        {"Wheat", 5}, {"Wood", 2}, {"Brick", 6},
        {"Sheep", 3}, {"Wood", 8}, {"Brick", 10},
        {"Wheat", 9}, {"Clay", 12}, {"Sheep", 11}, 
        {"Desert", 7}, {"Sheep", 6}, {"Clay", 4},
        {"Wood", 8}, {"Wheat", 11}, {"Wood", 9},
        {"Wheat", 11}, {"Sheep", 3}, {"Wood", 4}, 
        {"Clay", 5}
    };

    // Mapping vertices and edges to hexagons
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

    // Example players (replace or extend as needed)
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");
    Player player4("Player 4");

    players.push_back(&player1);
    players.push_back(&player2);
    players.push_back(&player3);
    players.push_back(&player4);

    // Add initial settlements and roads for players
    for (auto* player : players) {
        if (player == nullptr) continue;

        // Example Initialization (ensure it matches game rules)
        std::vector<int> startingVertices = {0, 1}; // Example indices; customize as needed
        std::vector<int> startingEdges = {0, 1};    // Example indices; customize as needed

        player->addVictoryPoints(2); // Initial settlements provide victory points

        for (int vertexIndex : startingVertices) {
            vertices[vertexIndex].buildSettlement(player);
            player->receiveResources(hexagons, vertexIndex);
            player->addSettlement(vertexIndex);
        }

        for (int edgeIndex : startingEdges) {
            edges[edgeIndex].buildRoad(player);
            player->addRoad(edgeIndex);
        }
    }
}
void Board::distributeResources(int diceRoll) {
    std::cout << "Distributing resources for dice roll: " << diceRoll << "\n";

    for (auto* player : players) {
        player->receiveResources(hexagons, diceRoll);
    }
    // Iterate over each hexagon in the list of hexagons
    for (const auto& hexagon : hexagons) {
        // Check if the number on the hexagon matches the rolled dice number
        if (hexagon.getNumber() == diceRoll) {
            // Iterate over each vertex (corner) of the hexagon
            for (const auto* vertex : hexagon.getVertices()) {
                // Check if the vertex has a structure (settlement or city) and has an owner (player)
                if (vertex->getStructure() != Vertex::Structure::None && vertex->getOwner() != nullptr) {
                    // Get the resource type produced by the hexagon
                    std::string resource = hexagon.getResource();
                    // Determine the amount of resources to give based on the structure type (2 for city, 1 for settlement)
                    int amount = (vertex->getStructure() == Vertex::Structure::City) ? 2 : 1;
                    // Add the determined amount of resources to the owner's resources
                    vertex->getOwner()->addResource(resource, amount);
                    std::cout << vertex->getOwner()->getName() << " receives " << amount << " " << resource << "(s) from hexagon with number " << diceRoll << "\n";

                }
            }
        }
    }
}


void Board::setPlayers(const std::vector<Player*>& newPlayers) {
    players = newPlayers;
}
//1.Selects a random development card type from a predefined list.
//2.Increases the victory points based on the card drawn.
//3.Updates the player’s development card count and checks if the player should receive points for the biggest army.
void Board::drawDevelopmentCard(int playerId) {
    static const std::vector<std::string> cardTypes = {"knight", "victory_point", "road_building", "year_of_plenty", "monopoly"};
    if (playerId >= 0 && static_cast<std::vector<Player*>::size_type>(playerId) < players.size()) {
        std::string cardType = cardTypes[rand() % cardTypes.size()];
        DevelopCard card(cardType);
        players[playerId]->addDevelopmentCard(card);

        if (cardType == "knight") { // if he have the big army
            int knightCount = players[playerId]->getDevelopmentCardCount("knight");
            if (knightCount > biggestArmy) {
                biggestArmy = knightCount;
                biggestArmyIndex = playerId;
                players[playerId]->addVictoryPoints(2);
            }
        } else if (cardType == "victory_point") { // if he get the victory point 
            players[playerId]->addVictoryPoints(1);
        }
    }
}
//1.Loops through the players to check if any player has reached 10 or more victory points.
//2.Declares the player as the winner if they have 10 or more points.
//3.If no player has won, it prints the highest points held by any player.
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

void Board::printBoard() const {
    std::vector<std::string> hexagonStrings;

    // Populate hexagonStrings with the formatted hexagon information
    for (const auto& hex : hexagons) {
        hexagonStrings.push_back(hex.getResource() + " " + std::to_string(hex.getNumber()));
    }

    const int numRows = 7;

    // Define the board layout with -1 representing sea spaces
    std::vector<std::vector<int>> boardLayout = {
        { -1, -1, -1, -1, -1, -1, -1 },
        { -1, -1,  0,  1,  2, -1, -1 },
        { -1,  3,  4,  5,  6,  -1 },
        { -1,  7,  8, 9, 10, 11, -1 },
        { -1, 12, 13, 14, 15,  -1 },
        { -1, -1, 16, 17, 18, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1 }
    };

    std::cout << "************ CATAN BOARD ************\n";

    // Print each row of the board
    for (int row = 0; row < numRows; ++row) {
        std::string rowOutput;

        // Adjust spacing based on row number
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

        // Print the row with adjusted formatting
        std::cout << rowOutput << "\n";
    }

    std::cout << "*************************************\n";
}
