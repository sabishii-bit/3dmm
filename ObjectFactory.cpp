#include "GraphicsObjects.h"

std::unique_ptr<Object3D> ObjectFactory::createObject(const std::string& type) 
{
    if (type == "cube") {
        return std::make_unique<Cube>();
    }
    else if (type == "pyramid") {
        return std::make_unique<Pyramid>();
    }
    else if (type == "sphere") {
        return std::make_unique<Sphere>();
    }
    else {
        throw std::invalid_argument("Unknown object type: " + type);
    }
}