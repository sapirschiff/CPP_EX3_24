#include "AdvancementCard.hpp"

AdvancementCard::AdvancementCard(ResourceType resourceType)
    : Card("Advancement"), resourceType(resourceType) { }

AdvancementCard::ResourceType AdvancementCard::getResourceType() const {
    return resourceType;
}
