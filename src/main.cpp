//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"
const uint Width = 1900;
const uint Height = 1000;
int main(){
    glm::vec3 Gris_bonito(0.1f,0.1f,0.1f);


    SV::Window window0("Test",Width,Height,Gris_bonito);
    window0.shaders->Load_custom_shaders("main","src/Vertex.glsl","src/Fragment.glsl");
    window0.shaders->Use("main");
    window0.transformations.Create_Projection_matrix(Width,Height,60.0f,0.1f,100.0f);
    window0.transformations.Create_View_matrix(glm::vec3(-10,10,10),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    window0.Mount_FTM_2_shader("main");

    long tam = 36;




    window0.Get_context();
    window0.Clear();
    window0.Present_renderer();

    SV::Line EJEX({-9.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {1, 0, 0});
    SV::Line EJEY({0.0, -5.0, 0.0}, {0.0, 5.0, 0.0}, {0, 1, 0});
    SV::Line EJEZ({0.0,0.0,-9.0},{0.0,0.0,10.0},{0,0,1});
    SV::Line Diagonal ({0,-1,-1},{0,1,1},{0,1,1});
    SV::Hyperboloid hiperboloide(
            {0,0,0},
            {0,1,1},
            0.1,
            -5,0,0.05,
            30,
            {1,0,0.5}
            );
    SV::Hyperboloid hiperboloide2(
            {0,0,0},
            {0,-1,1},
            0.1,
            -5,0,0.05,
            30,
            {1,0.5,1}
    );
    SV::Hyperboloid hiperboloide3(
            {0,0,0},
            {0,1,-1},
            0.1,
            -5,0,0.05,
            30,
            {1,0.5,.8}
    );
    SV::Hyperboloid hiperboloide4(
            {0,0,0},
            {0,-1,-1},
            0.1,
            -5,0,0.05,
            30,
            {1,0.3,0.4}
    );

    //SV::N_agon nagono({0,0,0},1.0,6,{0.5,0.1,0.6});

    float step = 0.05;
    int n = 0;
    while(!window0.Should_close()){
        n++;
        window0.transformations.Create_Rotation_matrix(step*n,{0,1,0});
        window0.Mount_FTM_2_shader("main");
        window0.Clear();
        EJEX.Draw();
        EJEY.Draw();
        EJEZ.Draw();
        Diagonal.Draw();
        hiperboloide.Draw();
        hiperboloide2.Draw();
        hiperboloide3.Draw();
        hiperboloide4.Draw();
        window0.Present_renderer();
    }

}