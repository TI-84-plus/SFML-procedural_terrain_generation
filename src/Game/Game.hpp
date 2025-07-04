#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "MapSelection/MapSelectionState.hpp"
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include "MainMenu/Menu.hpp"
#include <chrono>
#include <string>
#include "MainMenu/Menu.hpp"


class MapSelectionState;
class Game
{
private:
    sf::Clock deltaClock;
    float deltaTime;
    sf::RenderWindow render = sf::RenderWindow(sf::VideoMode(screenwidth, screenheight), "Procedural generation");
    
    //Game Runner
    bool IsRunning = true;
    StateManager manager;


	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	float fps;

public:

    Game();

    void Run();

    //Process Input
    void ProcessingInput();

    //Update
    void Update();

    //Render
    void Render();
};
#endif
