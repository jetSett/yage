#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>

#include <Utils/Logger.hpp>
#include <ResourcesMgr/MediaManager.hpp>
#include <3D/OPENGL2/OGL2Renderer.hpp>

#include "Engines/MessageManaging.hpp"

class Engine;

class Game : public MessageReceiver
{
    public:
        virtual ~Game();
        void run();
        void messageTo(Message& m);
        Game();

        virtual void processMessage(Message);

    private:
        void stopReceiver(Message&);

        void stop();

        void initMediaMgr();

        std::unordered_map<std::string, SmartPtr<Engine>> _engines;
};

#endif // GAME_HPP
