#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "SFML/Graphics/Shape.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class Entity {
    
    sf::Vector2f speed;
    sf::Vector2f acceleration;
    sf::CircleShape shape; // also has position
    
    public:
    sf::Vector2f previousPosition;
    Entity (sf::Vector2f initPosition ,float radius, sf::Color color = sf::Color::Green,
            int points = 30, sf::Vector2f initSpeed = sf::Vector2f(0,0));
    
    void updatePosition (float dt, sf::Vector2f positionVector = sf::Vector2f(0,0));
    void updateSpeed (float dt, sf::Vector2f speedVector = sf::Vector2f(0,0));
    void resetAcceleration ();
    void updateAcceleration (sf::Vector2f accelerationVector);
    sf::CircleShape& getShape ();
    const sf::Vector2f& getPosition ();
    const sf::Vector2f& getSpeed ();

};
