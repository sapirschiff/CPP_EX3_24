#ifndef CARD_HPP
#define CARD_HPP

#include <string>

// Base class representing a generic card
class Card {
public:
    // Constructor to initialize the card with a specific type
    Card(const std::string& type);

    // Virtual destructor
    virtual ~Card() = default;

    // Method to get the type of the card
    std::string getType() const;

protected:
    std::string type;  // Type of the card
};

#endif // CARD_HPP
