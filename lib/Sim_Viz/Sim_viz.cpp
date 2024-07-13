//
// Created by ehecatl on 7/12/24.
//

#include "Sim_viz.hpp"

#include <utility>

namespace SV{
    uint8_t Window::windows_amount = 0;
    std::map<std::string,GLuint> Window::Shaders::shader;

    Window::Window(std::string title, uint32_t width, uint32_t height,glm::vec3 bg_color):title(std::move(title)),width(width),height(height),background_color(bg_color){
        if (windows_amount == 0){
            if (!glfwInit()){
                throw std::runtime_error("Error initializing GLFW.\n");
            }
        }
        window = glfwCreateWindow(int(width),int(height),title.c_str(), nullptr, nullptr);
        if (!window){
            glfwTerminate();
            throw std::runtime_error(std::string("Error creating window: ").append(title).append("\n"));
        }
        windows_amount++;
        Get_context();
        GLenum error = glewInit();
        if (error != GLEW_OK){
            throw  std::runtime_error(std::string("Error initializing GLEW: ").append(reinterpret_cast<const char*>(glewGetErrorString(error))).append("\n"));
        }
    }
    void Window::Set_background_color(glm::vec3 color) {
        background_color = color;
    }

    void Window::Clear() const {
        glClearColor(background_color.r, background_color.g, background_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::Present_renderer() {
        glfwSwapBuffers(window);
    }

    bool Window::Should_close() {
        glfwPollEvents();
        return glfwWindowShouldClose(window);
    }

    void Window::Get_context() {
        glfwMakeContextCurrent(window);
    }

    Window::~Window() {
        windows_amount--;
        if (windows_amount == 0){
            Shaders::Free_all();
        }
        glfwDestroyWindow(window);

    }

    uint32_t Window::Get_width() const {
        return width;
    }

    uint32_t Window::Get_height() const {
        return height;
    }


    void Say_hello(){
        std::cout << "hola mundo!" << std::endl;
    }

    void Window::Transformations::Update_FTM() {
        final_transformation_matrix = projection_matrix * view_matrix * rotation_matrix;
    }

    void Window::Transformations::Set_View_matrix(glm::mat4 new_view_matrix) {
        view_matrix = new_view_matrix;
        Update_FTM();
    }

    void Window::Transformations::Set_Projection_matrix(glm::mat4 new_projection_matrix) {
        projection_matrix = new_projection_matrix;
        Update_FTM();
    }

    void Window::Transformations::Set_Rotation_matrix(glm::mat4 new_rotation_matrix) {
        rotation_matrix = new_rotation_matrix;
        Update_FTM();
    }

    void
    Window::Transformations::Create_View_matrix(glm::vec3 camera_position, glm::vec3 camera_target, glm::vec3 normal) {
        view_matrix = glm::lookAt(camera_position, camera_target, normal);
        Update_FTM();
    }

    void Window::Transformations::Create_Projection_matrix(uint32_t w_width,uint32_t w_height,float fov, float zNear, float zFar) {
        projection_matrix = glm::perspective(glm::radians(fov), float(w_width) / float(w_height), zNear, zFar); // Utiliza valores de ancho y alto apropiados
        Update_FTM();
    }

    void Window::Transformations::Create_Rotation_matrix(float angle_radian, glm::vec3 rotation_axis) {
        rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_radian, rotation_axis);
        Update_FTM();
    }

    std::string Window::Shaders::Read_file(const char *file) {
        return std::string();
    }

    void Window::Shaders::Load_custom_shaders(const std::string &vertex_file, std::string fragment_file) {

    }

    void Window::Shaders::Build_premade_shaders(uint16_t Flags) {

    }

    void Window::Shaders::Free_all() {

    }

    GLuint Window::Shaders::Get_shader_program(const std::string& name) {
        if (shader[name] == 0){
            throw  std::runtime_error(std::string("Shader Program not found:").append(name).append("\n"));
        }
        return shader[name];
    }

    void Object::Set_vertex(float *Vertex, uint32_t size) {

    }

    void Object::Set_vertex(std::vector<glm::vec3> vertex) {

    }

    float *Object::Unpack_vertex(std::vector<glm::vec3> packed_vertex) {
        return nullptr;
    }

    std::vector<glm::vec3> Object::Pack_vertex(float *Vertex, uint32_t size) {
        return std::vector<glm::vec3>();
    }
};