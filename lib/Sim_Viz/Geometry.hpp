//
// Created by ehecatl on 7/15/24.
//
#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include <tuple>


#ifndef SIMVIZ_GEOMETRY_HPP
#define SIMVIZ_GEOMETRY_HPP

namespace GT {
    typedef struct{
        uint default_draw_mode;
        std::vector<glm::vec3> vertex;
        uint*     index;
        uint      index_size;
        glm::vec3 color;
    }Geometrical_components;

    namespace Shape {
        Geometrical_components line             (glm::vec3 Origin, glm::vec3 direction_xyz                  ,glm::vec3 color);
        Geometrical_components line             (glm::vec3 Origin, glm::vec2 direction_angles               ,glm::vec3 color);
        Geometrical_components Circle           (glm::vec3 Center, uint radius                              ,glm::vec3 color);
        Geometrical_components N_agon_radius    (glm::vec3 Center, uint radius,   uint sides                ,glm::vec3 color);
        Geometrical_components N_agon_apothem   (glm::vec3 Center, uint apothem,  uint sides                ,glm::vec3 color);
        Geometrical_components N_agon_side      (glm::vec3 Center, uint side,     uint sides                ,glm::vec3 color);

    }
    namespace Body {
        Geometrical_components Cuboid           (glm::vec3 base_center ,uint height, uint width, uint depth ,glm::vec3 color);
        Geometrical_components Pyramid          (glm::vec3 base_center ,uint height, uint faces             ,glm::vec3 color);
        Geometrical_components Prism            (glm::vec3 base_center ,uint height, uint faces             ,glm::vec3 color);
        Geometrical_components Polyhedron       (glm::vec3 base_center ,uint radius, uint faces             ,glm::vec3 color);

    }
    namespace Transform {
        Geometrical_components Translation      (std::vector<glm::vec3> vertexes, glm::vec3 displacement_vec);
        Geometrical_components Rotation_1Axis   (std::vector<glm::vec3> vertexes, glm::vec3 axis, float radians);
        Geometrical_components Scaling          (std::vector<glm::vec3> vertexes, float scale);
        Geometrical_components Mirror           (std::vector<glm::vec3> vertexes, glm::vec3 plains);
    }
}

#endif //SIMVIZ_GEOMETRY_HPP
