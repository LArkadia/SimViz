//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"
const uint Width = 1900;
const uint Height = 1000;
glm::vec3 Mid_Point(const glm::vec3& point1, const glm::vec3& point2) {
    return (point1 + point2) / 2.0f;
}
glm::vec3 Find_source(std::vector<glm::vec3> Hyperboloids);
float hyperbolic_difference(glm::vec3 source,glm::vec3 f1,glm::vec3 f2);
int main(){
    glm::vec3 Gris_bonito(0.1f,0.1f,0.1f);


    SV::Window window0("Test",Width,Height,Gris_bonito);
    window0.shaders->Load_custom_shaders("main","src/Vertex.glsl","src/Fragment.glsl");
    window0.shaders->Use("main");
    window0.transformations.Create_Projection_matrix(Width,Height,60.0f,0.1f,100.0f);
    window0.transformations.Create_View_matrix(glm::vec3(6,8,4),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    window0.Mount_FTM_2_shader("main");

    glm::vec3 source = {3,3,3};
    std::vector<glm::vec3> microphones = {
            {0,5,0},
            {-5,0,-5},
            {5,0,-5},
            {0,0,5}
    };
    /*
    std::vector<SV::Hyperboloid> Hyperboloids;
    for (int i = 0; i < 4; ++i) {
        for (int j = i+1; j < 4; ++j) {
            Hyperboloids.emplace_back(
                    Mid_Point(microphones[i],microphones[j]),
                    microphones[i],
                    glm::distance(source,microphones[j]) - glm::distance(source,microphones[i]),
                    -5,0,0.01,30,
                    glm::vec3(0.6,0.6,0.7)
            );
        }
    }
     */
    std::vector<SV::Line> lineas;
    float radius = 5;
    int points_disc = 10;
    float step = radius/points_disc;
    for (int i = 0; i < points_disc; i++)
    {
        float theta = i * M_PI/points_disc;
        for (int j = 0; j < points_disc; j++)
        {
            float phi = 2 * M_PI * j /points_disc;
            lineas.push_back(
                SV::Line(
                    {0,0,0},
                {radius * std::sin(theta) * std::cos(phi),
                radius * std::sin(theta) * std::sin(phi),
                radius * std::cos(theta)},
                {0,1,1}
                )
            );
        }
        
    }
    


    SV::Line Eje1(source,{0,0,0},{0,1,0});


    window0.Get_context();
    window0.Clear();
    window0.Present_renderer();

    SV::Line EJEX({-9.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {1, 0, 0});
    SV::Line EJEY({0.0, -5.0, 0.0}, {0.0, 5.0, 0.0}, {0, 1, 0});
    SV::Line EJEZ({0.0,0.0,-9.0},{0.0,0.0,10.0},{0,0,1});

    std::vector<SV::Line> mics;
    for (auto focus:microphones) {
        mics.emplace_back(
                glm::vec3(0,0,0),
                focus,
                glm::vec3(0.2,0.4,0.6)
                );
    }

    //SV::N_agon nagono({0,0,0},1.0,6,{0.5,0.1,0.6});
    SV::Line Fuente(
        {0,0,0},
        source,
        {1,1,1}
    );
    while(!window0.Should_close()){
 
        window0.Clear();

        EJEX.Draw();
        //EJEY.Draw();
        EJEZ.Draw();Eje1.Draw();
        Fuente.Draw();

        for (const auto& line:mics){
            line.Draw();
        }
        for(const auto& line:lineas){
            line.Draw();
        }

        window0.Present_renderer();
    }

}

glm::vec3 Find_source(std::vector<glm::vec3> Hyperboloids){
    glm::vec3 source;

    return source;
}
float hyperbolic_difference(glm::vec3 source,glm::vec3 f1,glm::vec3 f2){
    return glm::distance(source,f1) - glm::distance(source,f2);
}