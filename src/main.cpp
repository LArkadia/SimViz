//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"

int main(){
    glm::vec3 Rojo(0.1f,0.1f,0.1f);
    SV::Window window0("Test",600,500,Rojo);
    window0.Get_context();
    SV::Window::Shaders::Load_custom_shaders("main","src/Vertex.glsl","src/Fragment.glsl");
    window0.transformations.Create_Projection_matrix(600,500,150.0f,0.1f,500.0f);
    window0.transformations.Create_View_matrix(glm::vec3(10.0,10.0,10.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    window0.transformations.Mount_FTM_2_shader("main");
    glUseProgram(SV::Window::Shaders::Get_shader_program("main"));

    std::vector<glm::vec3> Cubo;
    Cubo.reserve(8*2*3); // Reservar 8 vertices de 3 dimensiones 2, posicion - color
    Cubo.emplace_back(-1.0f, -1.0f,  1.0f);
    Cubo.emplace_back(1.0f, 0.0f, 0.0f);

    Cubo.emplace_back(1.0f, -1.0f,  1.0f);
    Cubo.emplace_back(0.0f, 1.0f, 0.0f);

    Cubo.emplace_back(1.0f,  1.0f,  1.0f);
    Cubo.emplace_back(0.0f, 0.0f, 1.0f);

    Cubo.emplace_back(-1.0f,  1.0f,  1.0f);
    Cubo.emplace_back(1.0f, 1.0f, 0.0f);

    Cubo.emplace_back(-1.0f, -1.0f, -1.0f);
    Cubo.emplace_back(1.0f, 0.0f, 1.0f);

    Cubo.emplace_back( 1.0f, -1.0f, -1.0f);
    Cubo.emplace_back(0.0f, 1.0f, 1.0f);

    Cubo.emplace_back(1.0f,  1.0f, -1.0f);
    Cubo.emplace_back(1.0f, 1.0f, 1.0f);

    Cubo.emplace_back(-1.0f,  1.0f, -1.0f);
    Cubo.emplace_back(0.0f, 0.0f, 0.0f);

    GLuint VAO,VBO;

    window0.Clear();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,Cubo.size()*3, SV::Object::Unpack_vertex(Cubo).get(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // Colores de los vértices
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS,0,Cubo.size()*3);

    window0.Present_renderer();
    while(!window0.Should_close()){







    }
}