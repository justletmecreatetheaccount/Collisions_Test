// local includes
#include "./headers/entity.hpp"
#include "./headers/simultation.hpp"
// functional includes 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <ctime>
#include <iostream>
#include <queue>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    Simulation sim (&window);

    sf::Clock frameClock;
    int timerReference = 0;
    int waitTime = 1;
    const int MAX_AUTO_ENTITY = 100;
    sf::Clock runningClock;
    float frameTime = 0;

    int subSteps = 8;

    //sim.addEntity(1, sf::Vector2f(100,100), 15.0f, sf::Color::Red, 30, sf::Vector2f());

    runningClock.restart();
    while (window.isOpen())
    {   
        if (runningClock.getElapsedTime().asSeconds() > timerReference
                && sim.allEntityList.size() < MAX_AUTO_ENTITY) {
            timerReference += waitTime;
            sim.addEntity(1, sf::Vector2f(100,100), 15.0f, sf::Color::Red, 30, sf::Vector2f(0.1, 0.1));
        }
        frameTime = frameClock.getElapsedTime().asSeconds(); 
        frameClock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < subSteps; i++) {
            sim.resolveCollisions();
            sim.updateAll(frameTime/subSteps);
        }

        window.clear();
        sim.drawAll();
        //window.draw();
        window.display();
    }

    return 0;
}
