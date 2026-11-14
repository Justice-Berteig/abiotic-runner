#include "game.hpp"
#include "globals.hpp"


bool Globals::isMuted     { false };
bool Globals::showHitboxes{ false };


int main()
{
    Game game;
    game.run();
}
