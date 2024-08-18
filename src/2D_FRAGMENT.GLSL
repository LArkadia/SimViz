#version 330

// Variables recibidas del shader de vértices
in vec3 FragColor; // Color del vértice

// Color de salida del fragmento
out vec4 FragColorOut;

void main() {
    // Usar el color recibido del shader de vértices como color de salida
    FragColorOut = vec4(FragColor, 1.0);
}