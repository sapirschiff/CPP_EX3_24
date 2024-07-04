// sapirblumshtein@gmail.com

#ifndef DEVELOPCARD_HPP
#define DEVELOPCARD_HPP

#include <string>

// Base class for all development cards
class DevelopCard {
public:
    DevelopCard(); // Constructor
    virtual ~DevelopCard(); // Virtual destructor

    virtual int countOf() const = 0; // Pure virtual function to get the count of the card type
    virtual DevelopCard* clone() const = 0; // Pure virtual function to clone the card
    virtual std::string getName() const = 0; // Pure virtual function to get the name of the card
    static DevelopCard* createCard(const std::string& cardType); // Static function to create a card based on type
};

// Derived class for Monopoly card
class monopol : public DevelopCard {
public:
    monopol(); // Constructor
    virtual ~monopol(); // Destructor

    int countOf() const override; // Override to get the count of Monopoly cards
    DevelopCard* clone() const override; // Override to clone Monopoly card
    std::string getName() const override; // Override to get the name of Monopoly card
};

// Derived class for Victory Point card
class victoryPoint : public DevelopCard {
public:
    victoryPoint(); // Constructor
    virtual ~victoryPoint(); // Destructor

    int countOf() const override; // Override to get the count of Victory Point cards
    DevelopCard* clone() const override; // Override to clone Victory Point card
    std::string getName() const override; // Override to get the name of Victory Point card
};

// Derived class for Year of Plenty card
class YearOfPlenty : public DevelopCard {
public:
    YearOfPlenty(); // Constructor
    virtual ~YearOfPlenty(); // Destructor

    int countOf() const override; // Override to get the count of Year of Plenty cards
    DevelopCard* clone() const override; // Override to clone Year of Plenty card
    std::string getName() const override; // Override to get the name of Year of Plenty card
};

// Derived class for Road Building card
class roadBuilding : public DevelopCard {
public:
    roadBuilding(); // Constructor
    virtual ~roadBuilding(); // Destructor

    int countOf() const override; // Override to get the count of Road Building cards
    DevelopCard* clone() const override; // Override to clone Road Building card
    std::string getName() const override; // Override to get the name of Road Building card
};

// Derived class for Knight card
class Knight : public DevelopCard {
public:
    Knight(); // Constructor
    virtual ~Knight(); // Destructor

    int countOf() const override; // Override to get the count of Knight cards
    DevelopCard* clone() const override; // Override to clone Knight card
    std::string getName() const override; // Override to get the name of Knight card
};

#endif // DEVELOPCARD_HPP
