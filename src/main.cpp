//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"
int main(){
    glm::vec3 Rojo(0.1f,0.1f,0.1f);
    SV::Window window0("Test",600,500,Rojo);
    window0.Get_context();
    SV::Window::Shaders::Load_custom_shaders("main","src/Vertex.glsl","src/Fragment.glsl");
    window0.transformations.Create_Projection_matrix(600,500,60.0f,0.1f,100.0f);
    window0.transformations.Create_View_matrix(glm::vec3(2,2,-2),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    glUseProgram(SV::Window::Shaders::Get_shader_program("main"));
    window0.transformations.Mount_FTM_2_shader("main");


    std::vector<glm::vec3> triangulo = {
            {-0.5f, -0.5f,  0.0f}, // Posición del primer vértice
            {1.0f, 0.0f, 0.0f},   // Color del primer vértice (si así lo deseas)

            {0.5f, -0.5f,  0.0f}, // Posición del segundo vértice
            {0.0f, 1.0f, 0.0f},   // Color del segundo vértice

            {0.0f, 0.5f,  0.0f},  // Posición del tercer vértice
            {0.0f, 0.0f, 1.0f}    // Color del tercer vértice
    };


    std::vector<glm::vec3> cubo = {
            // Cara delantera (rojo)
            {-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f},
            {1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f},

            {-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f},
            {-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f},

            // Cara trasera (verde)
            {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},
            {1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},
            {1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},

            {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},
            {1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},
            {-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},

            // Cara izquierda (azul)
            {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f},
            {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 1.0f},
            {-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f},

            {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f},
            {-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f},
            {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f},

            // Cara derecha (amarillo)
            {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 0.0f},
            {1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 0.0f},
            {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 0.0f},

            {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 0.0f},
            {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 0.0f},
            {1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 0.0f},

            // Cara superior (magenta)
            {-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f},
            {1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f},
            {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f},

            {-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f},
            {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f},
            {-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f},

            // Cara inferior (cian)
            {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 1.0f},
            {1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 1.0f},
            {1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 1.0f},

            {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 1.0f},
            {1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 1.0f}
    };

    SV::Object Triangulo(GL_TRIANGLES,triangulo);
    SV::Object Cubo(GL_TRIANGLES,cubo);

    window0.Clear();

    glBindVertexArray(Cubo.GetVao());
    glDrawArrays(GL_TRIANGLES,0,Cubo.GetVertex_amount());

    window0.Present_renderer();
    while(!window0.Should_close()){
        glDrawArrays(GL_TRIANGLES,0,Cubo.GetVertex_amount());
        window0.Present_renderer();

    }
}