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

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    Simulation sim (&window);

    sf::Clock frameClock;
    int timerReference = 0;
    const int MAX_AUTO_ENTITY = 10;
    sf::Clock runningClock;
    float frameTime = 0;

    runningClock.restart();
    while (window.isOpen())
    {   
        if (frameClock.getElapsedTime().asSeconds() > timerReference
                && sim.allEntityList.size() < MAX_AUTO_ENTITY) {
            timerReference += 5;
            sim.addEntity(1, sf::Vector2f(100,100), 15.0f, sf::Color::Red, 30, sf::Vector2f());
        }
        frameTime = frameClock.getElapsedTime().asSeconds(); 
        frameClock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        sim.resolveCollisions();
        sim.updateAll(frameTime);
        std::cout<<"pos : "<<sim.allEntityList[0].getShape().getPosition().x
            <<", "<<sim.allEntityList[0].getShape().getPosition().y<<"\n";

        window.clear();
        sim.drawAll();
        //window.draw();
        window.display();
    }

    return 0;
}
