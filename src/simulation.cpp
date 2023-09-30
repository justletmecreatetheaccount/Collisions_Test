#include "./headers/simultation.hpp"
#include "./headers/entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <bits/fs_fwd.h>
#include <iostream>
#include <cmath>
#include <math.h>

Simulation::Simulation(sf::RenderWindow* win) { window = win; };

float Simulation::scalarMultiplcation(sf::Vector2f v1, sf::Vector2f v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f Simulation::getUnitVector(sf::Vector2f rawVector) {
    return sf::Vector2f(rawVector.x / std::sqrt(std::pow(rawVector.x, 2) + std::pow(rawVector.y, 2)),
                rawVector.y / std::sqrt(std::pow(rawVector.x, 2) + std::pow(rawVector.y, 2)));
}

void Simulation::addEntity(int numberToBeAdded, sf::Vector2f initPosition, float radius, sf::Color color, int points, sf::Vector2f initSpeed) {
    for (int i = 0; i < numberToBeAdded; i++) {
       allEntityList.emplace_back(Entity(initPosition, radius, color, points, initSpeed));
    }
}
//Testing If https://www.youtube.com/watch?v=lS_qeBy3aQI is correct in saying that verlet actually takes care of everything
/*
void Simulation::resolveCollisions() {
    bool sureNoCollisions = false; bool foundCollision = true; sf::Vector2f EjEiVector = sf::Vector2f(); while (!sureNoCollisions) { foundCollision = false;
        for (int i = 0; i < allEntityList.size(); i++) {
            //collisions with borders
            if (allEntityList[i].getPosition().x + allEntityList[i].getShape().getRadius() > (*window).getSize().x) {

                allEntityList[i].getShape().setPosition(sf::Vector2f((*window).getSize().x - allEntityList[i].getShape().getRadius(), allEntityList[i].getPosition().y));
                allEntityList[i].updateSpeed(0, sf::Vector2f(-allEntityList[i].getSpeed().x - COLLISION_ELASTICITY * allEntityList[i].getSpeed().x, allEntityList[i].getSpeed().y));
                foundCollision = true;
                std::cout<<"Found Collision with Right\n";
            }
            if (allEntityList[i].getPosition().x + allEntityList[i].getShape().getRadius() < 0) {

                allEntityList[i].getShape().setPosition(sf::Vector2f(0 + allEntityList[i].getShape().getRadius(), allEntityList[i].getPosition().y));
                allEntityList[i].updateSpeed(0, sf::Vector2f(-allEntityList[i].getSpeed().x - COLLISION_ELASTICITY * allEntityList[i].getSpeed().x, allEntityList[i].getSpeed().y));
                foundCollision = true;
                std::cout<<"Found Collision with Left\n";
            }
            if (allEntityList[i].getPosition().y + allEntityList[i].getShape().getRadius() > (*window).getSize().y) {

                allEntityList[i].getShape().setPosition(sf::Vector2f(allEntityList[i].getPosition().x, (*window).getSize().y - allEntityList[i].getShape().getRadius()));
                allEntityList[i].updateSpeed(0, sf::Vector2f(allEntityList[i].getSpeed().x, -allEntityList[i].getSpeed().y - COLLISION_ELASTICITY * allEntityList[i].getSpeed().y));
                foundCollision = true;
                std::cout<<"Found Collision with Down\n";
            }
            for (int j = i+1; j < allEntityList.size(); j++) {
                std::cout<<j<<" "<<allEntityList.size()<<"\n";
                //collisions with other balls
                EjEiVector = sf::Vector2f(allEntityList[i].getPosition().x - allEntityList[j].getPosition().x,
                        allEntityList[i].getPosition().y - allEntityList[j].getPosition().y); //Vector j -> i

                if (std::sqrt(std::pow(EjEiVector.x, 2) + std::pow(EjEiVector.y, 2)) <
                        allEntityList[i].getShape().getRadius() + allEntityList[j].getShape().getRadius()) {

                    foundCollision = true;
                    allEntityList[i].updateSpeed(0, sf::Vector2f(Simulation::scalarMultiplcation(allEntityList[i].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * Simulation::getUnitVector(EjEiVector) + allEntityList[i].getSpeed()
                                - Simulation::scalarMultiplcation(allEntityList[i].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * Simulation::getUnitVector(EjEiVector)));
                    allEntityList[j].updateSpeed(0, sf::Vector2f(Simulation::scalarMultiplcation(allEntityList[j].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * -Simulation::getUnitVector(EjEiVector) + allEntityList[j].getSpeed()
                                - Simulation::scalarMultiplcation(allEntityList[j].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * -Simulation::getUnitVector(EjEiVector)));
                    std::cout<<"Found Collision with other ball \n";
                }
            }
        }
        if (!foundCollision) {
            sureNoCollisions = true;
        }
    }
}
*/
void Simulation::resolveCollisions() {
    bool sureNoCollisions = false; bool foundCollision = true; sf::Vector2f EjEiVector = sf::Vector2f(); 
    while (!sureNoCollisions) { foundCollision = false;
        for (int i = 0; i < allEntityList.size(); i++) {
            //collisions with borders
            if (allEntityList[i].getPosition().x + allEntityList[i].getShape().getRadius() > (*window).getSize().x) {

                allEntityList[i].getShape().setPosition(sf::Vector2f((*window).getSize().x - allEntityList[i].getShape().getRadius(), allEntityList[i].getPosition().y));
                foundCollision = true;
                std::cout<<"Found Collision with Right\n";
            }
            if (allEntityList[i].getPosition().x + allEntityList[i].getShape().getRadius() < 0) {

                allEntityList[i].getShape().setPosition(sf::Vector2f(0 + allEntityList[i].getShape().getRadius(), allEntityList[i].getPosition().y));
                foundCollision = true;
                std::cout<<"Found Collision with Left\n";
            }
            if (allEntityList[i].getPosition().y + allEntityList[i].getShape().getRadius() > (*window).getSize().y) {

                allEntityList[i].getShape().setPosition(sf::Vector2f(allEntityList[i].getPosition().x, (*window).getSize().y - allEntityList[i].getShape().getRadius()));
                foundCollision = true;
                std::cout<<"Found Collision with Down\n";
            }
            for (int j = i+1; j < allEntityList.size(); j++) {
                std::cout<<j<<" "<<allEntityList.size()<<"\n";
                //collisions with other balls
                EjEiVector = sf::Vector2f(allEntityList[i].getPosition().x - allEntityList[j].getPosition().x,
                        allEntityList[i].getPosition().y - allEntityList[j].getPosition().y); //Vector j -> i

                if (std::sqrt(std::pow(EjEiVector.x, 2) + std::pow(EjEiVector.y, 2)) <
                        allEntityList[i].getShape().getRadius() + allEntityList[j].getShape().getRadius()) {

                    foundCollision = true;
                    allEntityList[i].updateSpeed(0, sf::Vector2f(Simulation::scalarMultiplcation(allEntityList[i].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * Simulation::getUnitVector(EjEiVector) + allEntityList[i].getSpeed()
                                - Simulation::scalarMultiplcation(allEntityList[i].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * Simulation::getUnitVector(EjEiVector)));
                    allEntityList[j].updateSpeed(0, sf::Vector2f(Simulation::scalarMultiplcation(allEntityList[j].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * -Simulation::getUnitVector(EjEiVector) + allEntityList[j].getSpeed()
                                - Simulation::scalarMultiplcation(allEntityList[j].getSpeed(), Simulation::getUnitVector(EjEiVector))
                                * -Simulation::getUnitVector(EjEiVector)));
                    std::cout<<"Found Collision with other ball \n";
                }
            }
        }
        if (!foundCollision) {
            sureNoCollisions = true;
        }
    }
}
void Simulation::updateAll(float dt) {
    if (gravityToggle) {
        for (Entity& entity : allEntityList) {
            entity.updateAcceleration(sf::Vector2f(0, GRAVITY_VALUE));
            entity.updateSpeed(dt);
            entity.updatePosition(dt);
            entity.resetAcceleration();
        }
    } else {
        for (Entity entity : allEntityList) {
            entity.updateSpeed(dt);
            entity.updatePosition(dt);
            entity.resetAcceleration();
        }
    }
}

void Simulation::drawAll() {
    for (Entity entity : allEntityList) {
        (*window).draw(entity.getShape());
    }
}

void Simulation::toggleGravity() {
    gravityToggle = !gravityToggle;
}
