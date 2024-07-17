//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"
int main(){
    glm::vec3 Gris_bonito(0.1f,0.1f,0.1f);


    SV::Window window0("Test",600,500,Gris_bonito);
    window0.shaders->Load_custom_shaders("main","src/Vertex.glsl","src/Fragment.glsl");
    window0.shaders->Use("main");
    window0.transformations.Create_Projection_matrix(600,500,60.0f,0.1f,100.0f);
    window0.transformations.Create_View_matrix(glm::vec3(0,0,-5),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    window0.Mount_FTM_2_shader("main");

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    auto cubo_crudo = std::vector<std::vector<glm::vec3>> {
            {
                    {-0.5f, -0.5f, -0.5f},  // Vértice 0
                    { 0.5f, -0.5f, -0.5f},  // Vértice 1
                    { 0.5f,  0.5f, -0.5f},  // Vértice 2
                    {-0.5f,  0.5f, -0.5f},  // Vértice 3
                    {-0.5f, -0.5f,  0.5f},  // Vértice 4
                    { 0.5f, -0.5f,  0.5f},  // Vértice 5
                    { 0.5f,  0.5f,  0.5f},  // Vértice 6
                    {-0.5f,  0.5f,  0.5f}   // Vértice 7
            },
            {
                    {1.0f, 0.0f, 0.0f},  // Color del vértice 0
                    {0.0f, 1.0f, 0.0f},  // Color del vértice 1
                    {0.0f, 0.0f, 1.0f},  // Color del vértice 2
                    {1.0f, 1.0f, 0.0f},  // Color del vértice 3
                    {1.0f, 0.0f, 1.0f},  // Color del vértice 4
                    {0.0f, 1.0f, 1.0f},  // Color del vértice 5
                    {0.5f, 0.5f, 0.5f},  // Color del vértice 6
                    {0.0f, 0.0f, 0.0f}   // Color del vértice 7
            }
    };
    uint indices[] = {
            // Cara delantera
            0, 1, 2,
            2, 3, 0,
            // Cara trasera
            4, 5, 6,
            6, 7, 4,
            // Cara izquierda
            0, 4, 7,
            7, 3, 0,
            // Cara derecha
            1, 5, 6,
            6, 2, 1,
            // Cara superior
            3, 2, 6,
            6, 7, 3,
            // Cara inferior
            0, 1, 5,
            5, 4, 0
    };

    long tam = 36;




    window0.Get_context();
    //SV::Object Triangulo(GL_TRIANGLES,std::move(triangulo_crudo));
    window0.Clear();
    window0.Present_renderer();

    //SV::Object Cubo(GL_TRIANGLES,std::move(cubo_crudo),indices,tam);
    SV::Line EJEX({-10.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {1, 0, 0});
    SV::Line EJEY({0.0, -10.0, 0.0}, {0.0, 10.0, 0.0}, {0, 1, 0});
    //SV::Line linea3({0.0,0.0,-10.0},{0.0,0.0,10.0},{0,0,1});
    //std::cout << "-----------------" << std::endl;
    //EJEX.Move({0.1,0.0,0.5});
    //EJEX.Update();
    SV::N_agon nagono({0,0,0},1.0,6,{0.5,0.1,0.6});

    while(!window0.Should_close()){

        //Cubo.Draw();
        window0.Clear();
        nagono.Draw();
        //EJEX.Move({0.00005,0.0,0.00005});
        //EJEX.Update();
        EJEX.Draw();
        EJEY.Draw();
        //linea3.Draw();
        //Triangulo.Draw();
        window0.Present_renderer();
    }

}