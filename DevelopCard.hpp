#ifndef DEVELOPCARD_HPP
#define DEVELOPCARD_HPP

#include "Card.hpp"
#include <string>
#include <unordered_map>

class DevelopCard : public Card {
private:
    std::unordered_map<std::string, int> cards;  
    int id;                                      
    std::string name;                           
    std::string description;                    

public:
    DevelopCard();  // Default constructor
    DevelopCard(const std::string& type);  // Constructor with type

    int getCardCount(const std::string& cardName) const;
    void addCard(const std::string& cardName, int count);
    bool useCard(const std::string& cardName);
};

#endif // DEVELOPCARD_HPP
