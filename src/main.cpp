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

    float step = 0.005;
    int n = 0;
    while(!window0.Should_close()){
        n++;
        window0.Clear();

        EJEX.Draw();
        //EJEY.Draw();
        EJEZ.Draw();Eje1.Draw();
        Hyperboloids[0].Draw();
        Hyperboloids[1].Draw();
        Hyperboloids[2].Draw();
        Hyperboloids[3].Draw();
        for (const auto& line:mics){
            line.Draw();
        }

        window0.Present_renderer();
    }

}

glm::vec3 Find_source(std::vector<glm::vec3> Hyperboloids){
    glm::vec3 source;

    return source;
}