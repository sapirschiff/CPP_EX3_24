
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib> // For std::rand and std::srand
#include "Board.hpp"
#include "Player.hpp"
#include "DevelopCard.hpp"
#include "AdvancementCard.hpp"

void initializePlayers(std::vector<Player*>& players, Board& board);

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed random number generator

    Board board;
    std::vector<Player*> players;

    initializePlayers(players, board);
    board.printBoard();

    bool gameWon = false;

    int playerCount = players.size();

    while (!gameWon) {
        for (int playerIndex = 0; playerIndex < playerCount; ++playerIndex) {
            auto* player = players[playerIndex];

            if (player->getVictoryPoints() >= 10) {
                std::cout << player->getName() << " wins with " << player->getVictoryPoints() << " points!" << std::endl;
                gameWon = true;
                break;
            }

            player->setTurn(true);
            
            // Roll the dice
            player->rollDice();
            int diceRoll = (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
            std::cout << player->getName() << " rolled a " << diceRoll << "\n";

            // If the dice roll is 7, invoke discard resources logic
            if (diceRoll == 7) {
                std::cout << "Dice roll is 7! Players with more than 7 resource cards must discard half." << std::endl;
                for (auto* p : board.getPlayers()) {
                    p->discardResources();
                }
            } else {
                // Distribute resources based on dice roll
                board.distributeResources(diceRoll);
            }

            // Example building a settlement
            int vertexIndex = 3;  // Example vertex index
            if (board.canPlaceSettlement(player, board.getVertices()[vertexIndex])) {
                if (player->canBuySettlement()) {
                    if (board.buildSettlement(player, vertexIndex)) {
                        std::cout << player->getName() << " built a settlement at vertex " << vertexIndex << std::endl;
                    } else {
                        std::cout << "Failed to build settlement at vertex " << vertexIndex << std::endl;
                    }
                } else {
                    std::cout << player->getName() << " does not have the resources to buy a settlement.\n";
                }
            } else {
                std::cout << player->getName() << " cannot place a settlement at vertex " << vertexIndex << std::endl;
            }

            // Example building a road
            int edgeIndex = 5; // Example edge index
            if (board.canPlaceRoad(player, board.getEdges()[edgeIndex])) {
                if (player->canBuyRoad()) {
                    if (board.buildRoad(player, edgeIndex)) {
                        std::cout << player->getName() << " built a road at edge " << edgeIndex << std::endl;
                    } else {
                        std::cout << "Failed to build road at edge " << edgeIndex << std::endl;
                    }
                } else {
                    std::cout << player->getName() << " does not have the resources to buy a road.\n";
                }
            } else {
                std::cout << player->getName() << " cannot place a road at edge " << edgeIndex << std::endl;
            }

            // Example upgrading a settlement to a city
            if (board.canPlaceCity(player, board.getVertices()[vertexIndex])) {
                if (player->canBuyCity()) {
                    if (board.buildCity(player, vertexIndex)) {
                        std::cout << player->getName() << " built a city at vertex " << vertexIndex << std::endl;
                    } else {
                        std::cout << "Failed to build city at vertex " << vertexIndex << std::endl;
                    }
                } else {
                    std::cout << player->getName() << " does not have the resources to buy a city.\n";
                }
            } else {
                std::cout << player->getName() << " cannot place a city at vertex " << vertexIndex << std::endl;
            }

            // Example of drawing a development card
            board.drawDevelopmentCard(playerIndex);
            std::cout << player->getName() << " drew a development card.\n";

            // Example use of a development card (Knight)
            if (player->canUseDevelopmentCard("knight")) {
                if (player->useDevelopmentCard("knight")) {
                    std::cout << player->getName() << " used a Knight card.\n";
                } else {
                    std::cout << player->getName() << " failed to use a Knight card.\n";
                }
            }

            player->printStatus();
            
            player->setTurn(false);
        }
    }

    board.printBoard();
    board.printWinner();

    // Clean up players to avoid memory leaks
    for (auto& player : players) {
        delete player;
    }

    return 0;
}

void initializePlayers(std::vector<Player*>& players, Board& board) {
    Player* alice = new Player("Alice");
    Player* bob = new Player("Bob");
    Player* charlie = new Player("Charlie");

    players.push_back(alice);
    players.push_back(bob);
    players.push_back(charlie);

    board.setPlayers(players); // Link players to the board using setter method
}
