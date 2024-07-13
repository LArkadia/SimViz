//
// Created by ehecatl on 7/12/24.
//
#include "lib/Sim_Viz/Sim_viz.hpp"

int main(){
    glm::vec3 Rojo(1.0f,0.0f,1.0f);
    SV::Window window0("Test",600,500,Rojo);
    while(!window0.Should_close()){
        window0.Clear();




        window0.Present_renderer();
    }
}