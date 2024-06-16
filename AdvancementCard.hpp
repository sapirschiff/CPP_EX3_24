#ifndef ADVANCEMENTCARD_HPP
#define ADVANCEMENTCARD_HPP

#include "Card.hpp"

class AdvancementCard : public Card {
public:
    enum ResourceType { Crop, Land, Stone, Sheep };

    AdvancementCard(ResourceType resourceType);
    ResourceType getResourceType() const;

private:
    ResourceType resourceType;
};

#endif // ADVANCEMENTCARD_HPP
