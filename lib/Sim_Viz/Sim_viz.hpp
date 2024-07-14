//
// Created by ehecatl on 7/12/24.
//

#ifndef SIMVIZ_SIM_VIZ_HPP
#define SIMVIZ_SIM_VIZ_HPP
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdint>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

namespace SV{
    void Say_hello();
    class Window{
    private:
        GLFWwindow* window;
        static uint8_t windows_amount;
        std::string title;
        uint32_t width;
        uint32_t height;
        glm::vec3 background_color;
    public:
        class Transformations;
        class Shaders;
        Window(std::string title,uint32_t width, uint32_t height,glm::vec3 bg_color);
        ~Window();
        void Get_context();
        [[nodiscard]] uint32_t Get_width() const;
        [[nodiscard]] uint32_t Get_height() const;
        void Set_background_color(glm::vec3 color);
        void Clear() const;
        void Present_renderer();
        bool Should_close();

        class Transformations{
        private:
            glm::mat4 view_matrix;
            glm::mat4 projection_matrix;
            glm::mat4 rotation_matrix;
            glm::mat4 final_transformation_matrix;
            void Update_FTM();
        public:
            //Mount FTM to shader program uniform transformation
            void Mount_FTM_2_shader(const std::string& shader_name);
            //Mount externally calculated matrices
            void Set_View_matrix(glm::mat4 new_view_matrix);
            void Set_Projection_matrix(glm::mat4 new_projection_matrix);
            void Set_Rotation_matrix(glm::mat4 new_rotation_matrix);

            //Calculate matrices
            void Create_View_matrix(glm::vec3 camera_position,glm::vec3 camera_target,glm::vec3 normal);
            void Create_Projection_matrix(uint32_t w_width,uint32_t w_height,float fov, float zNear,float zFar);
            //void Create_Projection_matrix(float fov, float zNear,float zFar);
            void Create_Rotation_matrix(float angle_radian, glm::vec3 rotation_axis);
        };
        class Shaders{
        private:
            static std::map<std::string,GLint> shader;
            static std::string Read_file(const char* file);
        public:
            static void Load_custom_shaders(const std::string &shader_name,const std::string& vertex_file,const std::string &fragment_file);
            static void Build_premade_shaders(uint16_t Flags);
            static GLint Get_shader_program(const std::string& name);
            static void Free_all();
        };
        Transformations transformations{};
        Shaders         shaders;
    };
    class Object{
        friend Window;
    private:
        std::unique_ptr<float[]> Vertexes;
        uint Vertexes_size;
        std::unique_ptr<float[]> Indexes;
        uint Indexes_size;
    public:
        void Set_vertexes(std::unique_ptr<float[]> vertex,uint32_t size);
        void Set_vertexes(const std::vector<glm::vec3>& vertex);
        void Set_indexes(std::unique_ptr<float[]> index,uint32_t size);
        void Set_indexes(const std::vector<glm::vec3>& index);
        static std::unique_ptr<float[]> Unpack_vertex(std::vector<glm::vec3> packed_vertex);
        static std::vector<glm::vec3> Pack_vertex(std::unique_ptr<float[]> vertex,uint32_t size);
    };

    enum SF{
        _2D             = 0b0000'0000'0000'0000,
        _3D             = 0b1000'0000'0000'0000,

        all_same_color  = 0b0000'0000'0000'0000,
        point_color     = 0b0100'0000'0000'0000,

        transformations = 0b0010'0000'0000'0000

    };
};


#endif //SIMVIZ_SIM_VIZ_HPP