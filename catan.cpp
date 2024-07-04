// sapirblumshtein@gmail.com

#include "Board.hpp"
#include "Player.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    // Create players and game board
    Player* p1 = new Player("Amit");
    Player* p2 = new Player("Omer");
    Player* p3 = new Player("Roni");
    Board* board = new Board();

    p1->setBoard(board);
    p2->setBoard(board);
    p3->setBoard(board);

    // Add players to the board
    std::vector<Player*> players = {p1, p2, p3};
    board->setPlayers(players);

    // Start the game: Each player places 2 settlements and 2 roads
    p1->placeInitialSettlement(9);
    p1->placeInitialRoad(10);
    p2->placeInitialSettlement(29);
    p2->placeInitialRoad(37);
    p3->placeInitialSettlement(33);
    p3->placeInitialRoad(42);
    p3->placeInitialSettlement(41);
    p3->placeInitialRoad(53);
    p2->placeInitialSettlement(20);
    p2->placeInitialRoad(25);
    p1->placeInitialSettlement(11);
    p1->placeInitialRoad(14);

    std::cout << std::endl;
    std::cout << "              ******** ROUND # 1 !! ********" << std::endl;
    p1->rollDice();
    p1->placeRoad(15); // p1 builds a road

    try {
        p3->rollDice(); // p3 tries to roll the dice out of turn
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();
    p2->placeRoad(27); // p2 builds a road
    p3->rollDice();

    try {
        p3->placeRoad(1); // p3 tries to build a road in an illegal location
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p1->rollDice();
    p2->rollDice();
    p3->rollDice();

    std::cout << "              ******** ROUND # 1 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << std::endl;
    std::cout << "              ******** ROUND # 2 !! ********" << std::endl;
    p1->rollDice();
    p2->rollDice();
    p3->rollDice();

    try {
        p1->buildSettlement(13); // p1 tries to build a settlement
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p2->buildSettlement(22); // p2 tries to build a settlement
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p3->buildSettlement(18); // p3 tries to build a settlement
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "              ******** ROUND # 2 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << std::endl;
    std::cout << "              ******** ROUND # 3 !! ********" << std::endl;
    p1->rollDice();

    try {
        p1->buildSettlement(13); // p1 tries to build a settlement
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();

    try {
        p2->buildSettlement(22); // p2 tries to build a settlement
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p3->rollDice();

    try {
        p3->buildSettlement(18); // p3 tries to build a settlement
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p1->rollDice();
    p2->rollDice();
    p3->rollDice();

    std::cout << "              ******** ROUND # 3 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << std::endl;
    std::cout << "              ******** ROUND # 4 !! ********" << std::endl;
    p1->rollDice();
    p2->rollDice();
    p3->rollDice();
    p1->rollDice();

    try {
        p1->buyDevelopmentCard(); // p1 tries to buy a development card
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p1->placeRoad(5); // p1 tries to build a road
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();

    try {
        p2->buyDevelopmentCard(); // p2 tries to buy a development card
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p2->placeRoad(39); // p2 tries to build a road
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p3->rollDice();

    try {
        p3->buyDevelopmentCard(); // p3 tries to buy a development card
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p3->placeRoad(51); // p3 tries to build a road
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "              ******** ROUND # 4 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << std::endl;
    std::cout << "              ******** ROUND # 5 !! ********" << std::endl;
    p1->rollDice();
    p2->rollDice();
    p3->rollDice();
    p1->rollDice();

    try {
        p1->buildCity(11); // p1 tries to build a city
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();

    try {
        p2->buildCity(29); // p2 tries to build a city
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p3->rollDice();

    try {
        p3->buildCity(41); // p3 tries to build a city
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "              ******** ROUND # 5 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << std::endl;
    std::cout << "              ******** ROUND # 6 !! ********" << std::endl;
    p1->rollDice();
    p2->rollDice();
    p3->rollDice();
    p1->rollDice();

    try {
        p1->buildCity(9);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p1->placeRoad(5);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();

    try {
        p2->buildSettlement(31);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p2->buildCity(20);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p3->rollDice();

    try {
        p3->buildCity(41);
        p3->buildCity(33);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "              ******** ROUND # 6 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << "              ******** ROUND # 7 !! ********" << std::endl; /// place towns (same as round 6)
    p1->rollDice();
    p2->rollDice();
    p3->rollDice();
    p1->rollDice();

    try {
        p1->buildCity(9);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p1->placeRoad(5);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();

    try {
        p2->buildSettlement(31);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p2->buildCity(20);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p3->rollDice();

    try {
        p3->buildCity(33);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "              ******** ROUND # 7 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << "              ******** ROUND # 8 !! ********" << std::endl; /// trades + develop card
    p1->rollDice();
    p2->rollDice();
    p3->rollDice();
    p1->rollDice();

    try {
        p1->tradeResources(*p2, WOOD, 1, WHEAT, 1); // p1 tries to trade with p2
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p1->tradeResources(*p2, BRICK, 1, CLAY, 1); // p1 tries to trade with p2
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p1->buyDevelopmentCard(); // p1 tries to buy a development card
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();

    try {
        p2->tradeResources(*p3, WOOD, 1, CLAY, 2); // p2 tries to trade with p3
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p2->tradeResources(*p3, BRICK, 1, SHEEP, 2); // p2 tries to trade with p3
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p2->buyDevelopmentCard(); // p2 tries to buy a development card
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p3->rollDice();

    try {
        p3->tradeResources(*p1, BRICK, 1, SHEEP, 1); // p3 tries to trade with p1
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        p3->buyDevelopmentCard(); // p3 tries to buy a development card
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "              ******** ROUND # 8 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    std::cout << "              ******** ROUND # 9 !! ********" << std::endl; // implements development cards
    p1->rollDice();
    p1->useDevelopmentCard("Knight"); // p1 uses a development card
    try {
        p1->buyDevelopmentCard();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    p2->rollDice();
    p2->useDevelopmentCard("Knight");
    p3->rollDice();
    p3->useDevelopmentCard("Knight");

    std::cout << "              ******** ROUND # 9 DATA: ********" << std::endl;
    std::cout << p1->getName() << " Number of points: " << p1->getVictoryPoints() << std::endl;
    std::cout << p2->getName() << " Number of points: " << p2->getVictoryPoints() << std::endl;
    std::cout << p3->getName() << " Number of points: " << p3->getVictoryPoints() << std::endl;

    board->printWinner(); // Check for winner
    board->printBoard();

    delete p1;
    delete p2;
    delete p3;
    delete board;

    return 0;
}
