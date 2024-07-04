// sapirblumshtein@gmail.com

#include "DevelopCard.hpp"

// Constructor for base class DevelopCard
DevelopCard::DevelopCard() {}

// Virtual destructor for base class DevelopCard
DevelopCard::~DevelopCard() {}

// Static function to create a card based on type
DevelopCard* DevelopCard::createCard(const std::string& cardType) {
    if (cardType == "Knight") {
        return new Knight();
    } else if (cardType == "victory_point") {
        return new victoryPoint();
    } else if (cardType == "road_building") {
        return new roadBuilding();
    } else if (cardType == "year_of_plenty") {
        return new YearOfPlenty();
    } else if (cardType == "monopoly") {
        return new monopol();
    }
    return nullptr;
}

// Implementation of Monopoly card
monopol::monopol() {}
monopol::~monopol() {}
int monopol::countOf() const { return 5; }
DevelopCard* monopol::clone() const { return new monopol(*this); }
std::string monopol::getName() const { return "monopol"; }

// Implementation of Victory Point card
victoryPoint::victoryPoint() {}
victoryPoint::~victoryPoint() {}
int victoryPoint::countOf() const { return 4; }
DevelopCard* victoryPoint::clone() const { return new victoryPoint(*this); }
std::string victoryPoint::getName() const { return "victory_point"; }

// Implementation of Year of Plenty card
YearOfPlenty::YearOfPlenty() {}
YearOfPlenty::~YearOfPlenty() {}
int YearOfPlenty::countOf() const { return 5; }
DevelopCard* YearOfPlenty::clone() const { return new YearOfPlenty(*this); }
std::string YearOfPlenty::getName() const { return "year_of_plenty"; }

// Implementation of Road Building card
roadBuilding::roadBuilding() {}
roadBuilding::~roadBuilding() {}
int roadBuilding::countOf() const { return 5; }
DevelopCard* roadBuilding::clone() const { return new roadBuilding(*this); }
std::string roadBuilding::getName() const { return "road_building"; }

// Implementation of Knight card
Knight::Knight() {}
Knight::~Knight() {}
int Knight::countOf() const { return 14; }
DevelopCard* Knight::clone() const { return new Knight(*this); }
std::string Knight::getName() const { return "Knight"; }
