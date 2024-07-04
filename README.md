
# Catan Game Implementation

**Author:** Sapir Blumshtein  
**Email:** sapirblumshtein@gmail.com

## Introduction

This project is an implementation of the board game "Settlers of Catan". The game involves multiple players who collect resources, build settlements, roads, and cities, and aim to earn victory points. The game is played in rounds, where players take turns to roll dice, collect resources, and perform actions.

## Classes Overview

### 1. `Player`
Represents a player in the game.

**Responsibilities:**
- Manage player's resources.
- Handle development cards.
- Track player's settlements, roads, and cities.
- Perform game actions like rolling dice, building settlements/roads/cities, and trading resources.

**Key Methods:**
- `addResource()`: Add resources to the player.
- `removeResource()`: Remove resources from the player.
- `rollDice()`: Roll the dice to determine resource distribution.
- `buildSettlement()`: Build a settlement if the player has enough resources.
- `placeRoad()`: Place a road if the player has enough resources.
- `buyDevelopmentCard()`: Buy a development card if the player has enough resources.
- `useDevelopmentCard()`: Use a development card.
- `tradeResources()`: Trade resources with another player.
- `printResources()`: Print the player's current resources.
- `printStatus()`: Print the player's current status including resources and victory points.

### 2. `Board`
Represents the game board.

**Responsibilities:**
- Initialize and manage the game board, including hexagons, vertices, and edges.
- Handle the placement of settlements, roads, and cities.
- Distribute resources based on dice rolls.
- Track the players in the game and manage turns.
- Determine the winner of the game.

**Key Methods:**
- `initializeBoard()`: Initialize the game board with hexagons, vertices, and edges.
- `setPlayers()`: Set the players in the game.
- `buildSettlement()`: Build a settlement at a specified vertex.
- `buildRoad()`: Build a road at a specified edge.
- `buildCity()`: Upgrade a settlement to a city.
- `distributeResources()`: Distribute resources to players based on dice rolls.
- `printBoard()`: Print the current state of the game board.
- `printWinner()`: Print the winner of the game if a player has enough victory points.

### 3. `Hexagon`
Represents a hexagon tile on the game board.

**Responsibilities:**
- Store the type of resource the hexagon provides.
- Store the number associated with the hexagon for resource distribution.
- Manage vertices associated with the hexagon.

**Key Methods:**
- `addVertex()`: Add a vertex to the hexagon.
- `getVertices()`: Get the vertices associated with the hexagon.

### 4. `Vertex`
Represents a vertex on the game board where a settlement or city can be placed.

**Responsibilities:**
- Track the owner of the vertex (player who owns the settlement or city).
- Track the type of structure on the vertex (none, settlement, city).

**Key Methods:**
- `setOwner()`: Set the owner of the vertex.
- `getOwner()`: Get the owner of the vertex.
- `setStructure()`: Set the type of structure on the vertex.
- `getStructure()`: Get the type of structure on the vertex.

### 5. `Edge`
Represents an edge on the game board where a road can be placed.

**Responsibilities:**
- Track the owner of the edge (player who owns the road).
- Track the vertices connected by the edge.

**Key Methods:**
- `setOwner()`: Set the owner of the edge.
- `getOwner()`: Get the owner of the edge.
- `getVertex1()`: Get the first vertex connected by the edge.
- `getVertex2()`: Get the second vertex connected by the edge.

### 6. `DevelopCard`
Represents a development card in the game.

**Responsibilities:**
- Handle different types of development cards (e.g., knight, victory point).
- Provide the functionality to use the card.

**Key Methods:**
- `getName()`: Get the name/type of the development card.
- `clone()`: Clone the development card for adding to a player's hand.

### Main Game Flow (`catan.cpp`)

The `catan.cpp` file contains the main game loop where the game is initialized, players take turns, and the game progresses through rounds. The main steps include:
1. Initializing players and the game board.
2. Placing initial settlements and roads for each player.
3. Running through multiple rounds where players roll dice, collect resources, build structures, trade resources, and use development cards.
4. Printing the status and resources of each player after each round.
5. Determining and printing the winner once a player reaches the required number of victory points.

## Conclusion

This implementation provides a basic simulation of the "Settlers of Catan" game. The game logic includes resource management, building structures, trading, and using development cards. The code is designed to be extendable and modifiable to accommodate additional game rules and features.

Feel free to explore and modify the code to enhance the gameplay and add new features!
