//
// Created by ehecatl on 7/15/24.
//
#include <glm/glm.hpp>
#include <vector>
#include <tuple>

#ifndef SIMVIZ_GEOMETRY_HPP
#define SIMVIZ_GEOMETRY_HPP

namespace Shape{
    std::vector<glm::vec3>  line            (int x,int y,uint length                );
    std::vector<glm::vec3>  Circle          (int x,int y,uint radius                );
    std::vector<glm::vec3>  N_agon_radius   (int x,int y,uint radius    ,uint sides );
    std::vector<glm::vec3>  N_agon_apothem  (int x,int y,uint apothem   ,uint sides );
    std::vector<glm::vec3>  N_agon_side     (int x,int y,uint side      ,uint sides );

}
namespace Body{
    std::vector<glm::vec3>  Cuboid          (int x,int y,uint height,uint width,uint depth  );
    std::vector<glm::vec3>  Pyramid         (int x,int y,uint height,uint faces             );
    std::vector<glm::vec3>  Prism           (int x,int y,uint height,uint faces             );
    std::vector<glm::vec3>  Polyhedron      (int x,int y,uint radius,uint faces             );

}
namespace Transform{
    std::vector<glm::vec3>  Translation     (std::vector<glm::vec3> vertexes,glm::vec3 displacement_vec                 );
    std::vector<glm::vec3>  Rotation_1Axis  (std::vector<glm::vec3> vertexes,glm::vec3 axis             ,float radians  );
    std::vector<glm::vec3>  Scaling         (std::vector<glm::vec3> vertexes                            ,float scale    );
    std::vector<glm::vec3>  Mirror          (std::vector<glm::vec3> vertexes,glm::vec3 plains                           );

}


#endif //SIMVIZ_GEOMETRY_HPP
