//TODO make a config file and set game to read off configuration
//make bullets a lifespan
//let enemies be different shapes and colors and speeds
//implement score 
//give enemies smaller enimies when shot
#include "Game.h"

#include <iostream>
#include <fstream>
#include "math.h"

Game::Game(const std::string & config){
    init(config);
}

void Game::init(const std::string & path){
    //read in config file here
    //do at end
    std::ifstream fin(path);

    // fin >> m_playerConfig.SR;

    m_window.create(sf::VideoMode(1280,720), "Geometry Wars");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void Game::run(){
    //
    while(m_running){

        m_entities.update();

        sEnemySpawner();
        sMovement();
        sCollision();
        sLifespan();
        sUserInput();
        sRender();

        m_currentFrame++;


    }
}
void Game::setPaused(bool paused){

    
}
void Game::sMovement(){
    //if entity has position that updates it should have movement logic
    //if in bounds update position variable 
    //read players userinput component and handle position update
    //when player is out of bounds cant go further in that direction but can move other directions !!!
    // if((m_player->cTransform->pos.x >= 0 && m_player->cTransform->pos.x <= 1280) && (m_player->cTransform->pos.y >= 0 && m_player->cTransform->pos.y <= 688) ){

        //player movement 
        if(m_player->cInput->up && m_player->cTransform->pos.y >= 50){
            m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;
        }
        if(m_player->cInput->down && m_player->cTransform->pos.y <= 670){
            m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
        }
        if(m_player->cInput->left && m_player->cTransform->pos.x >= 50){
            m_player->cTransform->pos.x -= m_player->cTransform->velocity.x;
        }
        if(m_player->cInput->right && m_player->cTransform->pos.x <= 1230){
            m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
        }

        //enemy movement bouncing off the edges
        //for all entities with enemy tag 
        // enemyVec = m_entities.getEntities("enemy");
        // for m_entities.getEntities("enemy");
        //looping through array of entities of entity vec

        for(auto& enemy : m_entities.getEntities("enemy")){

                if(enemy->cShape->circle.getGlobalBounds().getPosition().x < 0){
                    enemy->cTransform->velocity.x = (enemy->cTransform->velocity.x * -1);
                }
                if(enemy->cShape->circle.getGlobalBounds().getPosition().x +70 > 1280){
                    enemy->cTransform->velocity.x = (enemy->cTransform->velocity.x * -1);
                }
                if(enemy->cShape->circle.getGlobalBounds().getPosition().y < 0){
                    enemy->cTransform->velocity.y = (enemy->cTransform->velocity.y * -1);
                }
                if(enemy->cShape->circle.getGlobalBounds().getPosition().y +70 > 720){
                    enemy->cTransform->velocity.y = (enemy->cTransform->velocity.y * -1);
                }
                enemy->cTransform->pos.x -= enemy->cTransform->velocity.x;
                enemy->cTransform->pos.y -= enemy->cTransform->velocity.y;
        }
        for(auto& bullet : m_entities.getEntities("bullet")){
                bullet->cTransform->pos.x += bullet->cTransform->velocity.x;
                bullet->cTransform->pos.y += bullet->cTransform->velocity.y;
        }


}
void Game::sUserInput(){
    //if entity has input component input logic
    //only set input component variables here not handle logic
    //the movement system will read the component variables and handle logic

    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_running = false;
        }
        //event triggered when key is pressed
        if(event.type == sf::Event::KeyPressed){
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                //set players input component "up" to true
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::A:
                //set players input component "left" to true
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::S:
                //set players input component "down" to true
                m_player->cInput->down = true;
                break;
            case sf::Keyboard::D:
                //set players input component "right" to true
                m_player->cInput->right = true;
                break;
            
            default:
                break;
            }
            // m_player->
        }
        if(event.type == sf::Event::KeyReleased){
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = false;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = false;
                break;
            
            default:
                break;
            }

        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){

            
                // std::cout << " left mouse button pressed at (" << event.mouseButton.x << "," << event.mouseButton.y <<")";
                //spawn the bullet going in the proper directions
                Vec2 mousePos(event.mouseButton.x,event.mouseButton.y);
                spawnBullet(m_player,mousePos);
            }

            if(event.mouseButton.button == sf::Mouse::Right){

            }

        }
        
    }
}
void Game::sLifespan(){
    // m_bulletspawntime = m_currentFrame;
        // std::cout << "comes here";
        for(auto b: m_entities.getEntities("bullet")){
            // std::cout << b->cLifespan->total << "this is total";
            if(b->cLifespan->total == m_currentFrame){
                b->destroy();
            }
        }

}
void Game::sRender(){

    m_window.clear();
    for(auto& e: m_entities.getEntities()){
        e->cShape->circle.setPosition(e->cTransform->pos.x,e->cTransform->pos.y);
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        m_window.draw(e->cShape->circle);
    }
    m_window.display();
}
void Game::sEnemySpawner(){
    //call spawn entity to spawn random entities randomly on the board 
    if (m_lastEnemySpawnTime + 240 < m_currentFrame )
    {
        spawnEnemy();
    }
    
    // spawnEnemy();

}
void Game::sCollision(){
    //BULLET ENEMY COLLISION
    for(auto b: m_entities.getEntities("bullet")){
        for(auto e: m_entities.getEntities("enemy")){

            //detect the collision using the distance between the positions of the bullet and enemy, and the 2 radius of the entity circles;
            float r1 = b->cShape->circle.getRadius();
            float r2 = e->cShape->circle.getRadius();

            Vec2 D(e->cTransform->pos.x - b->cTransform->pos.x, e->cTransform->pos.y - b->cTransform->pos.y);

            float dist = (D.x*D.x + D.y*D.y);

            if(dist < ((r1+r2)*(r1+r2))){
                // std::cout << "there was a collision";
                // std::cout << e->cShape->circle.getPointCount();
                spawnSmallEnemies(e);
                //remove big enemy 
                e->destroy();
                b->destroy();
            }


        }
    }
    //PLAYER ENEMY COLLISION
    for(auto e: m_entities.getEntities("enemy")){

            float r1 = m_player->cShape->circle.getRadius();
            float r2 = e->cShape->circle.getRadius();

            Vec2 D(e->cTransform->pos.x - m_player->cTransform->pos.x, e->cTransform->pos.y -  m_player->cTransform->pos.y);

            float dist = (D.x*D.x + D.y*D.y);

            if(dist < ((r1+r2)*(r1+r2))){
                // std::cout << "there was a collision";
                // std::cout << e->cShape->circle.getPointCount();
                spawnSmallEnemies(e);
                //remove big enemy 
                m_player->cTransform->pos.x =m_window.getSize().x/2;
                m_player->cTransform->pos.y= m_window.getSize().y/2;
            }
    }
    
}


//spawning logic
void Game::spawnPlayer(){
    auto entity = m_entities.addEntity("player");
    entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f,200.0f),Vec2(10.0f,10.0f),0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f,8,sf::Color(10,10,10),sf::Color(255,0,0),4.0f);
    entity->cInput = std::make_shared<CInput>();
    m_player = entity;
}
void Game::spawnEnemy(){
    //make an enemy entity and give it all the components it needs
    //make sure the enemy is pspawned in the bounds of the window
    auto entity = m_entities.addEntity("enemy");

    float ex = (rand() % m_window.getSize().x);
    float ey = (rand() % m_window.getSize().y);
    //better to use a while loop or to get a spawn that is in bounderies
    if(ex < 32 ){
        ex = 32;
    }
    if(ex > 1270){
        ex = 1240;
    }
    if(ey < 32 ){
        ey = 32;
    }
    if(ey > 670){
        ey = 670;
    }
    //params position velocity angle
    entity->cTransform = std::make_shared<CTransform>(Vec2(ex,ey),Vec2(1.0f,1.0f),2.0f);
    //params radius points incolor outcolor thickness
    entity->cShape = std::make_shared<CShape>(30.0f,3,sf::Color(0,0,255),sf::Color(255,255,255),4.0f);
    // entity->cInput = std::make_shared<CInput>();
    // m_player = entity;


    //records when the most recent enemy was spawned for spawner
    m_lastEnemySpawnTime = m_currentFrame;
}
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity){
    //get the correct amount of shapes to spawn 360/sides of shape
    //give them a lifespan
    //calculate the correct trajectory the small shapes will float off to 
    //give the shapes cTransform and add it to the movement system
    // std::cout << entity->cShape->circle.points; 
    int pointCount = entity->cShape->circle.getPointCount();
    //TODO
    // for(int i =0; i< pointCount; i++){
    //     auto smallentity = m_entities.addEntity("smallenemy");

    //     smallentity->cTransform;// finish TODO
    //     smallentity->cShape;
    //     smallentity->cLifespan;
    // }
    
}
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos){
    auto bullet = m_entities.addEntity("bullet");

    Vec2 D (mousePos.x - entity->cTransform->pos.x, mousePos.y - entity->cTransform->pos.y);
    float L = sqrt((D.x*D.x) + (D.y*D.y));
    // (mousePos.x - entity->cTransform->pos.x/L), (mousePos.y - entity->cTransform->pos.y/L)
    Vec2 norm((D.x/L),(D.y/L));
    
    Vec2 velocity = norm * 5;

    bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y),Vec2(velocity.x,velocity.y),2.0f);
    bullet->cShape = std::make_shared<CShape>(3.0f,16,sf::Color(255,255,255),sf::Color(255,255,255),2.0f);
    bullet->cLifespan = std::make_shared<CLifespan>(m_currentFrame + 80); //total remaining starts from 0
    // std::cout << "makesit here";
    // m_bulletspawntime = m_currentFrame;


    //D= (mx-px, my-py)
    //L = sqrt(x*x + y*y)
    //normailize D  N=(D.x /L ,D.y/L) now has L=1
    //Velocity = (S * N.x, S * N.y)
    // bullet->cCollision =
}
void Game::spawnSpecialWeapons(std::shared_ptr<Entity> entity){

}