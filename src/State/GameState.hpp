#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"

class StateManager;
class GameState
{
public:
	const int screenwidth = 1920;
	const int screenheight = 1080;
	
    sf::View view;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleInput(StateManager* game, sf::Event event) = 0;
    virtual void Update(StateManager* game) = 0;
    virtual void Draw(StateManager* game, sf::RenderWindow& renderer) = 0;
};

#endif
