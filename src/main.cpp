#include "engine.h"
#include "GameEngine/GameEngine.h"

int main ()
{
    engine::Audio audio ;
    audio.shutdown();
    
    engine::gameEngine gameEngine ;
    gameEngine.update();
    
    gameEngine.initialize();


    return 0 ;
}