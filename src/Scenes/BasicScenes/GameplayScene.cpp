#include "Scenes/BasicScenes/GameplayScene.hpp"

void GameplayScene::update()
{
    updateEntities();
}

void GameplayScene::updateEntities()
{
    for (std::pair<std::string, Entity*> entity_pair : entity_map_)
    {
        entity_pair.second->update(); // basic Update

        // Look for and process collisions
        CollidableEntity* ent1 = (CollidableEntity*)entity_pair.second;
        if (ent1) // if it's a collidable
        {
            // Look for other collidables
            for (std::pair<std::string, Entity*> collidable_pair : entity_map_)
            {
                CollidableEntity* ent2 = (CollidableEntity*)collidable_pair.second;

                // Found another collidable that is after this one (only check each pair once)
                if (ent2 && collidable_pair.first > entity_pair.first)
                    // if is colliding
                    if (ent2->isCollidingWith(ent1))
                    {   
                        // make both entities process collisions 
                        ent1->processCollision(ent2);
                        ent2->processCollision(ent1);
                    }
            }
        }

        entity_pair.second->entitySprite->update();
    }
}