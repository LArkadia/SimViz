//
// Created by ehecatl on 7/15/24.
//
#include "Geometry.hpp"

#include <cmath>

//Shapes Definitions
GT::Geometrical_components GT::Shape::line(glm::vec3 Origin, glm::vec3 direction_xyz, glm::vec3 color) {
    Geometrical_components Shape;
    Shape.color = color;
    Shape.vertex.push_back(Origin);
    glm::vec3 endPoint = Origin + direction_xyz;
    Shape.vertex.push_back(endPoint);
    Shape.index = nullptr;
    Shape.index_size = 0;
    return Shape;
}

GT::Geometrical_components GT::Shape::line(glm::vec3 Origin, glm::vec2 direction_angles, glm::vec3 color) {
    Geometrical_components Shape;
    Shape.color = color;

    Shape.vertex.push_back(Origin);

    float azimuth = glm::radians(direction_angles.x);
    float elevation = glm::radians(direction_angles.y);
    glm::vec3 direction_xyz(
            std::cos(elevation) * std::sin(azimuth),
            std::sin(elevation),
            std::cos(elevation) * std::cos(azimuth)
    );

    glm::vec3 endPoint = Origin + direction_xyz;
    Shape.vertex.push_back(endPoint);

    return Shape;
}


GT::Geometrical_components GT::Shape::Circle(glm::vec3 Center, uint radius, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}

GT::Geometrical_components GT::Shape::N_agon_radius(glm::vec3 Center, uint radius, uint sides, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}

GT::Geometrical_components GT::Shape::N_agon_apothem(glm::vec3 Center, uint apothem, uint sides, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}

GT::Geometrical_components GT::Shape::N_agon_side(glm::vec3 Center, uint side, uint sides, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}
//Bodys Definitions
GT::Geometrical_components
GT::Body::Cuboid(glm::vec3 base_center, uint height, uint width, uint depth, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}

GT::Geometrical_components GT::Body::Pyramid(glm::vec3 base_center, uint height, uint faces, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}

GT::Geometrical_components GT::Body::Prism(glm::vec3 base_center, uint height, uint faces, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}

GT::Geometrical_components GT::Body::Polyhedron(glm::vec3 base_center, uint radius, uint faces, glm::vec3 color) {
    GT::Geometrical_components Shape;

    return Shape;
}
