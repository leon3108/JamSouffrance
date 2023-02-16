#include "./BackgroundFactory.hpp"

BackgroundFactory::BackgroundFactory(/* args */)
{
}

BackgroundFactory::~BackgroundFactory()
{
}

Entity *BackgroundFactory::create() const 
{
    Background *background = new Background();
    Components::Position poscompBackground({0, 0});
    Components::Object objcompBackground("./assets/GamePlay/background/Stars.png");
    Components::Movements movcompBackground(5);

    background->addComp(std::make_shared<Components::Position>(poscompBackground));
    background->addComp(std::make_shared<Components::Object>(objcompBackground));
    background->addComp(std::make_shared<Components::Movements>(movcompBackground));
    return background;
}