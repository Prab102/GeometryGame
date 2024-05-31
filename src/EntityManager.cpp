#include "EntityManager.h"
#include <iostream>
#include <algorithm>

EntityManager::EntityManager(){

}
void EntityManager::removeDeadEntities(EntityVec & vec){
    std::vector<std::shared_ptr<Entity>> bin2;
    EntityVec bin;

    for(auto e: vec){

        // std::remove_if(vec.begin(),vec.end(),e);
        if(!e->isActive())
        {
             bin.push_back(e);
            // std::cout << "remove this entity" << e->m_tag << std::endl;
            // // vec.erase(std::remove_if(vec.begin(),vec.end(),[](const auto& e){return (!e->isActive)}), vec.end());
            // std::vector<std::shared_ptr<Entity>>::iterator it;
            // std::vector<int>::iterator it2;

            // it = std::find(vec.begin(),vec.end(),e);
            // std::cout << *it;
            //     // vec.erase(it);
            // if(it != vec.end()){
            //     // vec.erase(it);
            //     bin.push_back(e);
            // }
            // std::remove_if(vec.begin(),vec.end(),[](const auto& e){return e->isActive();});
        }
    }
    for(auto del :bin){
         std::vector<std::shared_ptr<Entity>>::iterator it;
         it = std::find(vec.begin(),vec.end(),del);
            // std::cout << *it;
                // vec.erase(it);
            if(it != vec.end()){
                vec.erase(it);
                // bin.push_back(e);
            }
    }
}
void EntityManager::update(){
    // EntityVec  map_entities;
    for(auto e : m_entitiesToAdd){
        m_entities.push_back(e);
        // std::cout << "this is the tag " << m_entities << " ";
        // EntityVec  map_entities;
        // map_entities.pushback(e);
        if(m_entityMap.find(e->tag()) != m_entityMap.end()){
            //adds an entity if the map already has a spot for the entities
            m_entityMap[e->tag()].push_back(e);

        }
        else{
            //creates a key value pair in entitymap to store entity vectors
            m_entityMap[e->tag()] = EntityVec();
        }

       

    }

    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for(auto& [tag,entityVec] : m_entityMap){
        removeDeadEntities(entityVec);
    }

}
std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag){
    
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++,tag));
    m_entitiesToAdd.push_back(entity);
    
    return entity;
}

const EntityVec & EntityManager::getEntities(){

    return m_entities;
}
const EntityVec & EntityManager::getEntities(const std::string & tag){
    
    return m_entityMap[tag];
}