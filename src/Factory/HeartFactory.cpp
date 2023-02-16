#include "./HeartFactory.hpp"

HeartFactory::HeartFactory(/* args */)
{
}

HeartFactory::~HeartFactory()
{
}

Entity *HeartFactory::create() const 
{
    Heart *heart = new Heart();
    Components::Position poscompHeart({100, 950});
    Components::Object objcompHeart("./assets/coeur-rouge-mini.png");
    heart->addComp(std::make_shared<Components::Position>(poscompHeart));
    heart->addComp(std::make_shared<Components::Object>(objcompHeart));
    return heart;
}