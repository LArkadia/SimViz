//
// Created by ehecatl on 7/12/24.
//

#include "Sim_viz.hpp"

#include <utility>

namespace SV{
    uint8_t Window::windows_amount = 0;
    std::map<std::string,GLint> Window::Shaders::shader;

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
        transformations = Transformations();
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
        projection_matrix = glm::perspective(glm::radians(fov), float(w_width) / float(w_height), zNear, zFar);
        Update_FTM();
    }

    void Window::Transformations::Create_Rotation_matrix(float angle_radian, glm::vec3 rotation_axis) {
        rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_radian, rotation_axis);
        Update_FTM();
    }

    void Window::Transformations::Mount_FTM_2_shader(const std::string &shader_name) {
        Update_FTM();
        auto shader_program = Shaders::Get_shader_program(shader_name);
        GLint FTM_Loc = glGetUniformLocation(shader_program,"FTM");
        glUseProgram(shader_program);
        glUniformMatrix4fv(FTM_Loc,1,GL_FALSE,glm::value_ptr(final_transformation_matrix));
    }


    std::string Window::Shaders::Read_file(const char *filepath) {
        std::ifstream file(filepath);
        if (!file){
            throw std::runtime_error(std::string("Failed to open file: ").append(filepath).append("\n"));
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void Window::Shaders::Load_custom_shaders(const std::string& shader_name,const std::string &vertex_file, const std::string& fragment_file) {

        //Read shaders files
        std::string V_S_S = Shaders::Read_file(vertex_file.c_str());    //Vertex    Shader Source
        std::string F_S_S = Shaders::Read_file(fragment_file.c_str());  //Fragment  Shader Source
        //convert string to char buffer
        const char* V_S_C = V_S_S.c_str();  //Vertex    Shader Code
        const char* F_S_C = F_S_S.c_str();  //Fragment  Shader Code
        //create Shaders
        GLuint  V_S = glCreateShader(GL_VERTEX_SHADER);     //Vertex    Shader
        GLuint  F_S = glCreateShader(GL_FRAGMENT_SHADER);   //Fragment  Shader
        //load Shaders source code
        glShaderSource(V_S,1,&V_S_C, nullptr);
        glShaderSource(F_S,1,&F_S_C, nullptr);
        //Compile shaders
        glCompileShader(V_S);
        glCompileShader(F_S);
        //Check for errors
        GLint V_C_S; //Vertex   Compile Status
        GLint F_C_S; //Fragment Compile Status
        //Get error compilation status
        glGetShaderiv(V_S,GL_COMPILE_STATUS,&V_C_S);
        glGetShaderiv(F_S,GL_COMPILE_STATUS,&F_C_S);
        //Error Handler
        if (V_C_S != GL_TRUE){
            GLint L_L; //Log length
            glGetShaderiv(V_S,GL_INFO_LOG_LENGTH,&L_L);
            auto log = new GLchar[L_L];
            glGetShaderInfoLog(V_S,L_L, nullptr,log);
            std::string E_L(log); // Error log
            delete[] log;
            throw std::runtime_error(std::string("Error compiling Vertex Shader").append(E_L).append("\n"));
        }
        if(F_C_S != GL_TRUE){
            GLint L_L; //Log length
            glGetShaderiv(F_S,GL_INFO_LOG_LENGTH,&L_L);
            auto log = new GLchar[L_L];
            glGetShaderInfoLog(F_S,L_L, nullptr,log);
            std::string E_L(log); // Error log
            delete[] log;
            throw std::runtime_error(std::string("Error compiling Fragment Shader").append(E_L).append("\n"));
        }

        // Create Shader program
        shader[shader_name] = glCreateProgram();
        //Attach Shaders to program
        glAttachShader(shader[shader_name],V_S);
        glAttachShader(shader[shader_name],F_S);
        //Link Shaders program
        glLinkProgram(shader[shader_name]);
        //Error handler
        GLint linked;
        glGetProgramiv(shader[shader_name] ,GL_LINK_STATUS,&linked);
        if (!linked){
            GLint L_L; //Log length
            glGetShaderiv(shader[shader_name],GL_INFO_LOG_LENGTH,&L_L);
            auto log = new GLchar[L_L];
            glGetShaderInfoLog(shader[shader_name],L_L, nullptr,log);
            std::string E_L(log); // Error log
            delete[] log;
            throw std::runtime_error(std::string("Error linking Shader Program: ").append(log).append("\n"));
        }
        //Free shader resources
        glDeleteShader(V_S);
        glDeleteShader(F_S);
    }

    void Window::Shaders::Build_premade_shaders(uint16_t Flags) {

    }

    void Window::Shaders::Free_all() {
        for (auto& [name,program]:shader) {
            glDeleteProgram(program);
        }
    }

    GLint Window::Shaders::Get_shader_program(const std::string& name) {
        if (shader[name] == 0){
            throw  std::runtime_error(std::string("Shader Program not found:").append(name).append("\n"));
        }
        return shader[name];
    }

    void Object::Set_vertexes(std::unique_ptr<float[]> vertex, uint size) {
        Vertexes = std::move(vertex);
        Vertexes_size = size;
    }

    void Object::Set_vertexes(const std::vector<glm::vec3>& vertex) {
        auto vertex_unpacked = Object::Unpack_vertex(vertex);
        Vertexes = std::move(vertex_unpacked);
        Vertexes_size = vertex.size()*3;
    }

    std::unique_ptr<float[]> Object::Unpack_vertex(std::vector<glm::vec3> packed_vertex) {
        std::unique_ptr<float[]> unpacked_vertex = std::make_unique<float[]>(packed_vertex.size()*3);
        for (uint i = 0; i < packed_vertex.size(); ++i) {
            unpacked_vertex[i*3] = packed_vertex[i].x;
            unpacked_vertex[i*3 + 1] = packed_vertex[i].x;
            unpacked_vertex[i*3 + 2] = packed_vertex[i].x;
        }
        return unpacked_vertex;
    }

    std::vector<glm::vec3> Object::Pack_vertex(std::unique_ptr<float[]> vertex, uint32_t size) {
       std::vector<glm::vec3> packed_vertex;
       packed_vertex.reserve(size/3);
        for (uint i = 0; i < size; i+=3) {
            packed_vertex.emplace_back(vertex[i],vertex[i + 1],vertex[i + 2]);
        }
        return  packed_vertex;
    }

    void Object::Set_indexes(std::unique_ptr<float[]> index, uint32_t size) {
        Indexes = std::move(index);
        Indexes_size = size;
    }

    void Object::Set_indexes(const std::vector<glm::vec3>& index) {
        auto vertex_unpacked = Object::Unpack_vertex(index);
        Vertexes = std::move(vertex_unpacked);
        Vertexes_size = index.size()*3;
    }
}