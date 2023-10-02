#include "entity.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>

class Simulation {
    sf::RenderWindow* window;
    bool gravityToggle = true;
    static constexpr float GRAVITY_VALUE = 500.0f;
    static constexpr float COLLISION_ELASTICITY = 0.5f;
    public:
    std::vector<Entity> allEntityList; 
    Simulation(sf::RenderWindow* win);
    static sf::Vector2f getUnitVector(sf::Vector2f rawVector);
    static float scalarMultiplcation (sf::Vector2f v1, sf::Vector2f v2);
    void addEntity (int numberToBeAdded, sf::Vector2f initposition, float radius, sf::Color color, int points, sf::Vector2f initSpeed);
    void resolveCollisions ();
    void updateAll (float dt);
    void drawAll ();
    void toggleGravity();
};
