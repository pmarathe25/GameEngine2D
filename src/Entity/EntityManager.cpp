EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) {
    renderModule = RenderComponent(window);
    entities.reserve(expectedNumEntities);
}

int getNewEntity(const sf::Vector2f& position) {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        entities.at(newID) = Entity(position);
    } else {
        newID = entities.size();
        entities.push_back(Entity(position));
    }
    return newID;
}

void destroyEntity(int eID) {

}

void update(float frametime) {
    renderModule.update();
}

void attachComponent(int eID, const Component& component) {

}

void detachComponent(int eID, componentID cID) {
    
}
