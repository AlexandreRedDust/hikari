#ifndef HIKARI_CORE_GAME_GAMECONTROLLER
#define HIKARI_CORE_GAME_GAMECONTROLLER

#include <map>
#include <string>
#include <memory>
#include "hikari/core/Platform.hpp"
#include "hikari/core/game/GameState.hpp"

// #include <oolua.h>

#pragma warning(push)
#pragma warning(disable:4251)

namespace sf {
    class RenderTarget;
}

namespace hikari {

    typedef std::shared_ptr<GameState> StatePtr;

    class HIKARI_API GameController {
    private:
        StatePtr state;
        std::string currState;
        std::string prevState;
        std::string nextState;
        std::map< std::string, StatePtr > states;

        /**
            DefaultGameState is used by a GameController instance as it's current state
            at time of construction. It is a simple State which does nothing -- it's
            simply a placeholder.
        */
        class DefaultGameState : public GameState {
        private:
            const std::string name;
        public:
            DefaultGameState();
            virtual ~DefaultGameState() { }
            virtual void handleEvent(sf::Event &event);
            virtual void render(sf::RenderTarget &target);
            virtual bool update(const float &dt);
            virtual void onEnter();
            virtual void onExit();
            virtual const std::string &getName() const;
        };

    public:
        GameController();

        void addState(const std::string &name, const StatePtr &state);

        /**
            Immediately trasitions from the current state in to the new state specified 
            by name. If no state can be identified for the given name an exception will 
            be thrown.

            The name supplied will also be set as the "next" state.
        */
        void setState(const std::string &name);

        /**
            Sets the next state to transition to but does not cause the current state to
            transition.
        */
        void setNextState(const std::string &name);

        void handleEvent(sf::Event &event);
        void render(sf::RenderTarget &target);
        void update(const float &dt);
    };

} // hikari

#pragma warning(pop)

#endif // HIKARI_CORE_GAME_GAMECONTROLLER