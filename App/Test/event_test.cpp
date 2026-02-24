#include <iostream>

#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/EventA.hpp"
#include "Events/CustomEvents/HitEvent.hpp"
#include "Events/EventHandler.hpp"

#include "Entity/Entity.hpp"
#include "Entity/Player/Player.hpp"
#include "Entity/Ennemies/Ennemy.hpp"

#include "Scenes/Scene.hpp"
#include "Scenes/BasicScenes/MenuScene.hpp"

/// TEST for Event Propagation
/// Paired to "event_test.bash" in "Builders" dir
int main() {
    Player* pl = new Player("player");
    // Player* pl2 = new Player(); // For memory leak test
    Ennemy* en = new Ennemy("ennemy1", 7);
    Ennemy* en2 = new Ennemy("ennemy2", 1);
    std::cout << "Created Player & Ennemies" << std::endl;



    MenuScene* menu = new MenuScene();
    std::cout << "Created MenuScene" << std::endl;



    EventHandler* evHandler = new EventHandler();
 // EventHandler* evHandler2 = new EventHandler(); // will throw error because it is a singleton class



    menu->setEventHandler(evHandler);
    evHandler->setCurrentScene(menu);
    std::cout << "Linked EventHandler & MenuScene" << std::endl;



    menu->addEntity(pl, "player");
    // menu->addEntity(pl2, "player"); // Will override player and cause memory leak (only 16 bytes so no big deal but still) //
    menu->addEntity(en, "ennemy1");
    menu->addEntity(en2, "ennemy2");
    std::cout << "Added Player & Ennemies to MenuScene" << std::endl;


    menu->updateEntity(); // Creates a HitEvent //


    while (!menu->eventHandler->isEmpty()) {
        menu->eventHandler->processEvent();
    }


    delete menu; // will delete the EventHandlers and the Entities //

    // delete pl2;

    return 0;
}