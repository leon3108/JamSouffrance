#include "./src/Components/IComponent.hpp"
#include "./src/System/Core.hpp"
#include "./src/Entity/Entity.hpp"
#include <iostream>
#include <memory>

int main()
{
    try {
        Core core({1920, 1080}, "r-type", 60);
    } catch (std::exception& e) {
        std::cout << "error :" << e.what() << std::endl;
    }
}