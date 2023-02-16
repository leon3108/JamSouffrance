#include "./ProjectilesFactory.hpp"

ProjectilesFactory::ProjectilesFactory(/* args */)
{
}

ProjectilesFactory::~ProjectilesFactory()
{
}

Entity *ProjectilesFactory::create() const
{
    Projectiles *projectile = new Projectiles();
    Components::Position positionCompProjectile;
    Components::Object objCompProj("./assets/GamePlay/explosion/r-typesheet1.gif");
    Components::Movements moveCompProjectile(7);
    Components::Animation animCompProjectile(5, 2);
    Components::Collision collisionCompProjectile;
    projectile->addComp(std::make_shared<Components::Position>(positionCompProjectile));
    projectile->addComp(std::make_shared<Components::Object>(objCompProj));
    projectile->addComp(std::make_shared<Components::Movements>(moveCompProjectile));
    projectile->addComp(std::make_shared<Components::Animation>(animCompProjectile));
    projectile->addComp(std::make_shared<Components::Collision>(collisionCompProjectile));
    projectile->getObjectComp()->setRefRect({232.0f, 103.0f, 17, 12});
    projectile->getCollisionComp()->setCollisionRect(projectile->getObjectComp()->getRect());
    return projectile;
}