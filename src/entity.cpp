#include "src/headers/entity.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

Entity::Entity (sf::Vector2f initPosition, float radius, sf::Color initcolor,
        int points, sf::Vector2f initSpeed) {
    shape = sf::CircleShape(radius, points);
    shape.setFillColor(initcolor);
    previousPosition = initPosition;
    shape.setPosition(initPosition + initSpeed);
}

/*
//Using simple algorithm
void Entity::updatePosition (float dt, sf::Vector2f positionVector) {
    shape.setPosition(shape.getPosition() + dt * speed + positionVector);
}

void Entity::updateSpeed (float dt, sf::Vector2f speedVector) {
    speed += speedVector + acceleration * dt;
}*/

//Using verlet

void Entity::updatePosition (float dt, sf::Vector2f positionVector) {
    sf::Vector2f temp = shape.getPosition();
    shape.setPosition(2.0f * shape.getPosition() - previousPosition + dt * dt * acceleration + positionVector);
    previousPosition = temp;
}


void Entity::updateSpeed (float dt, sf::Vector2f speedVector) {
    speed += speedVector + acceleration * dt;
}


void Entity::resetAcceleration() {
    acceleration = sf::Vector2f();
}


void Entity::updateAcceleration (sf::Vector2f accelerationVector) {
    acceleration += accelerationVector;
}

sf::CircleShape& Entity::getShape () { return shape; }

const sf::Vector2f& Entity::getPosition () { return shape.getPosition(); }
const sf::Vector2f& Entity::getSpeed () { return speed;}
