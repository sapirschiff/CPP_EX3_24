# Catan Game Implementation
### Project by Sapir Blumshtein
### Student ID: 324246651

## Overview
This project simulates the board game "Catan". The game consists of a board with 19 plots of land surrounded by the sea. Each plot of land yields specific resources like wood, bricks, wool, oats, and iron, while the desert yields nothing. Players collect these resources to build roads, settlements, and cities, and to buy development cards, all of which contribute to their victory points. The first player to reach 10 victory points wins the game.

## Game Components
- **Board**: Consists of 19 hexagonal plots of various resource types.
- **Players**: Each player has resources and the ability to build roads, settlements, and cities, as well as the ability to trade and use development cards.
- **Resources**: Wood, bricks, wool, oats, iron, and nothing (desert).
- **Development Cards**: Allow players to gain additional benefits like knights, roads, or resources.
- **Settlements and Cities**: Contribute to a player's victory points and resource collection.

## Class Hierarchy
- **Board**: Manages the hexagons, vertices, edges, and players. Distributes resources and handles the building of settlements, roads, and cities.
- **Player**: Manages a player's resources, development cards, and victory points. Allows actions such as trading, building, and using cards.
- **Hexagon**: Represents a plot of land on the board.
- **Vertex**: Represents the intersection points of hexagons, where settlements and cities can be built.
- **Edge**: Represents the connections between vertices, where roads can be built.
- **Card**: Base class for all cards.
    - **DevelopCard**: Represents development cards with their respective effects.
    - **AdvancementCard**: Represents special cards that give different resource types.

## Methods
### Board Class
- `Board()`: Constructor to initialize the board.
- `initializeBoard()`: Sets up the initial state of the board with hexagons, vertices, and edges.
- `distributeResources(int diceRoll)`: Distributes resources to players based on the dice roll.
- `drawDevelopmentCard(int playerId)`: Allows a player to draw a development card.
- `canPlaceSettlement(Player* player, const Vertex& vertex) const`: Checks if a player can place a settlement on a vertex.
- `canPlaceRoad(Player* player, const Edge& edge) const`: Checks if a player can place a road on an edge.
- `canPlaceCity(Player* player, const Vertex& vertex) const`: Checks if a player can place a city on a vertex.
- `buildSettlement(Player* player, int vertexIndex)`: Builds a settlement for a player.
- `buildRoad(Player* player, int edgeIndex)`: Builds a road for a player.
- `buildCity(Player* player, int vertexIndex)`: Builds a city for a player.
- `printBoard() const`: Prints the current state of the board.
- `printWinner()`: Checks and prints the winner.
- `getPlayers() const`: Returns the list of players.

### Player Class
- `Player(const std::string& name)`: Constructor to initialize a player.
- `discardResources()`: Forces a player to discard half of their resources.
- `addResource(const std::string& resource, int amount)`: Adds a specified amount of a resource to the player's resources.
- `removeResource(const std::string& resource, int amount)`: Removes a specified amount of a resource from the player's resources.
- `hasResource(const std::string& resource, int amount) const`: Checks if the player has at least a specified amount of a resource.
- `addDevelopmentCard(const DevelopCard& card)`: Adds a development card to the player's collection.
- `useDevelopmentCard(const std::string& cardType)`: Uses a development card from the player's possession.
- `getDevelopmentCardCount(const std::string& cardType) const`: Gets the count of a specific type of development card.
- `addVictoryPoints(int points)`: Adds a specified number of victory points to the player's total.
- `getVictoryPoints() const`: Gets the current total of the player's victory points.
- `isTurn() const`: Checks if it is currently the player's turn.
- `setTurn(bool turn)`: Sets whether it is currently the player's turn.
- `initializeResources(const std::vector<std::string>& initialResources)`: Initializes the player's resources with a list of starting resources.
- `getCities(const std::vector<Vertex>& vertices) const`: Prints the cities owned by the player.
- `rollDice()`: Simulates rolling a dice.
- `addSettlement(int vertexIndex)`: Adds a settlement to the player's list of settlements.
- `addRoad(int edgeIndex)`: Adds a road to the player's list of roads.
- `getDiceRoll() const`: Gets the result of the last dice roll.
- `getSettlements() const`: Gets a constant reference to the player's list of settlements.
- `getRoads() const`: Gets a constant reference to the player's list of roads.
- `receiveResources(const std::vector<Hexagon>& hexagons, int vertexIndex)`: Receives resources from the initial setup based on the placement of the settlement.
- `getName() const`: Gets the player's name.
- `tradeResources(Player& otherPlayer, const std::string& resource1, int amount1, const std::string& resource2, int amount2)`: Trades resources with another player.
- `canBuySettlement() const`: Checks if the player can buy a settlement.
- `canBuyCity() const`: Checks if the player can buy a city.
- `canBuyRoad() const`: Checks if the player can buy a road.
- `useKnight()`: Uses a knight development card.
- `useRoadBuilding()`: Uses a road building development card.
- `useYearOfPlenty()`: Uses a year of plenty development card.
- `useMonopoly()`: Uses a monopoly development card.
- `canUseDevelopmentCard(const std::string& cardType) const`: Checks if the player can use a specific type of development card.
- `addAdvancementCard(const AdvancementCard& card)`: Adds an advancement card to the player's possession.
- `useAdvancementCard(AdvancementCard::ResourceType resourceType)`: Uses an advancement card from the player's possession.
- `printStatus() const`: Prints the current status of the player.

## Development Environment
### Libraries Used:
- Standard C++ Library (iostream, vector, string, etc.)
- Custom Headers for Game Components

## Compilation
### Makefile
Make sure to see the provided `Makefile` to compile and run the project. The `make` command can be used to compile the project, and `make clean` to clean up the object files and executable.

## Running the Game
To run the game, use the following command after compilation:
