#version 330

// Atributos de entrada
layout(location = 0) in vec3 aPos;    // Posiciones de los vértices
layout(location = 1) in vec3 aColor;  // Colores de los vértices

// Matriz de proyección uniforme
uniform mat4 FTM;
// Variables para pasar al shader de fragmentos
out vec3 FragColor; // Color del vértice

void main() {
    // Transformar la posición del vértice por la matriz de proyección
    gl_Position = FTM*vec4(aPos.x,aPos.y,aPos.z, 1.0);

    // Pasar el color del vértice al shader de fragmentos
    FragColor = aColor;
}