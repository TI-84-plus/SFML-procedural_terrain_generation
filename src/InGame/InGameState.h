#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "Renderer/renderer.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include "InGame.h"
#include <ostream>

class InGameState: public GameState 
{
    private:
        InGame Game;
        double MapSeed;
        
    public:

        InGameState(double seed) 
        {
            MapSeed = seed;
            std::cout<<"InGameState Seed:" <<int(seed)<<std::endl;
        }

        void Init() {};
        void Cleanup() {};

        void Pause() {};
        void Resume() {};

        void HandleInput(StateManager* game, sf::Event event) {

        switch (event.key.code)
        {
            case sf::Keyboard::W:
                std::cout<<"Registered1"<< MapSeed<<std::endl;
            break;
            
            default:
                break;
        }
        };
        void Update(StateManager* game) {};

        void Draw(StateManager* game, sf::RenderWindow& renderer) {
            renderer.clear();
            renderer.draw(Game.map);
            renderer.display();
            // std::cout<<"Registered2"<<std::endl;
        };



};
#endif
