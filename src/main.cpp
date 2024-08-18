//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"
#include <tuple>
#include <vector>
#include <cmath>

const uint Width = 1900;
const uint Height = 1000;
glm::vec3 Mid_Point(const glm::vec3& point1, const glm::vec3& point2) {
    return (point1 + point2) / 2.0f;
}

glm::vec3 Find_source(const std::vector<glm::vec3>& Hyperboloids);
float hyperbolic_difference(glm::vec3 source, glm::vec3 f1, glm::vec3 f2);
glm::vec3 estimated_source(std::vector<float> differences, std::vector<std::tuple<std::vector<float>, glm::vec3>> table);

int main(){
    //===============================>Window Setup<==============================
    glm::vec3 Gris_bonito(0.1f,0.1f,0.1f);
    SV::Window window0("Test", Width, Height, Gris_bonito);
    window0.shaders->Load_custom_shaders("main","src/2D_VERTEX.GLSL","src/2D_FRAGMENT.GLSL");
    window0.shaders->Use("main");
    window0.Mount_Dimensions_2_shader("main");
    //Definición de los ejes
    std::vector<SV::Line> Axles;
    Axles.emplace_back(glm::vec3 (-1900,0.0,0.0),glm::vec3 (1900,0.0,0.0),glm::vec3(1.0,0.0,0.0));
    Axles.emplace_back(glm::vec3 (0.0,-1000,0.0),glm::vec3 (0.0,1000,0.0),glm::vec3(0.0,1.0,0.0));
    SV::Circle circulo1({0,0,-1},1000,{0.0,0.7,0.9});
    //===============================>Main loop<===============================
    while (!window0.Should_close()) {
        window0.Clear();circulo1.Draw();
        for (const auto& Axis:Axles) {Axis.Draw();}




        window0.Present_renderer();
    }
    return 0;
}

glm::vec3 Find_source(const std::vector<glm::vec3>& Hyperboloids) {
    glm::vec3 source;
    return source;
}

float hyperbolic_difference(glm::vec3 source, glm::vec3 f1, glm::vec3 f2) {
    return glm::distance(source, f1) - glm::distance(source, f2);
}

glm::vec3 estimated_source(std::vector<float> differences, std::vector<std::tuple<std::vector<float>, glm::vec3>> table) {
    glm::vec3 source;
    float min_square_distance = std::numeric_limits<float>::max(); // Inicializar con el máximo valor posible
    for (const auto& entry : table) {
        const auto& float_vec = std::get<std::vector<float>>(entry);
        float distance = 0.0f;
        for (int i = 0; i < differences.size(); i++) {
            distance += pow(float_vec[i] - differences[i], 2);
        }
        if (distance < min_square_distance) {
            source = std::get<glm::vec3>(entry);
            min_square_distance = distance;
        }
    }
    return source;
}
