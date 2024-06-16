#include "Card.hpp"

// Constructor to initialize the card with a specific type
Card::Card(const std::string& type) : type(type) { }

// Method to get the type of the card
std::string Card::getType() const {
    return type;
}
