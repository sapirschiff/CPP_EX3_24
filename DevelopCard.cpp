#include "DevelopCard.hpp"

DevelopCard::DevelopCard() : Card("default") {
    this->cards["monopoly"] = 5;
    this->cards["road_building"] = 5;
    this->cards["year_of_plenty"] = 5;
    this->cards["victory_point"] = 4;
    this->cards["knight"] = 14;
}

DevelopCard::DevelopCard(const std::string& type) : Card(type) {
    // Initialize counts based on the type
    if (type == "monopoly" || type == "road_building" || type == "year_of_plenty") {
        this->cards[type] = 5;
    } else if (type == "victory_point") {
        this->cards[type] = 4;
    } else if (type == "knight") {
        this->cards[type] = 14;
    } else {
        this->cards["default"] = 0;
    }
}

int DevelopCard::getCardCount(const std::string& cardName) const {
    auto it = cards.find(cardName);
    if (it != cards.end()) {
        return it->second;
    }
    return 0;
}

void DevelopCard::addCard(const std::string& cardName, int count) {
    cards[cardName] += count;
}

bool DevelopCard::useCard(const std::string& cardName) {
    // Check if the card is available and the count is greater than 0
    if (cards.find(cardName) != cards.end() && cards[cardName] > 0) {
        return true;  // Card is available
    }
    return false; // Card is not available
}
