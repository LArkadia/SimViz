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
        static uint8_t windows_amount;
        std::string title;
        uint32_t width;
        uint32_t height;
        glm::vec3 background_color;
    public:
        GLFWwindow* window;
        class Transformations;
        class Shaders;
        Window(std::string title,uint32_t width, uint32_t height,glm::vec3 bg_color);
        Window(std::string title,uint32_t width, uint32_t height,glm::vec3 bg_color,Window* shared_resources_window);
        ~Window();
        void Get_context() const;
        void Mount_FTM_2_shader(const std::string &shader_name);
        [[nodiscard]] uint32_t Get_width() const;
        [[nodiscard]] uint32_t Get_height() const;
        void Set_background_color(glm::vec3 color);
        void Clear() const;
        void Present_renderer() const;
        [[nodiscard]] bool Should_close() const;

        class Transformations{
        private:
            glm::mat4 view_matrix;
            glm::mat4 projection_matrix;
            glm::mat4 rotation_matrix;
            glm::mat4 final_transformation_matrix;

        public:
            Transformations();
            void Update_FTM();

            [[nodiscard]] const glm::mat4 &GetFTM() const;

//Mount FTM to shader program uniform transformation
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
            std::map<std::string,GLint> shader;
            static std::string Read_file(const char* file);
        public:
            void Load_custom_shaders(const std::string &shader_name,const std::string& vertex_file,const std::string &fragment_file);
            void Build_premade_shaders(uint16_t Flags);
            GLint Get_shader_program(const std::string& name);
            void Use(const std::string& shader_name);
            void Free_all();
        };
        Transformations transformations;
        Shaders*         shaders;
    };
    class Object{
        friend Window;
    private:
        std::vector<std::vector<glm::vec3>> shader_parameters;
        uint    Width,Height;
        GLenum Draw_mode;
        GLuint VAO,VBO,EBO;
        int Indexes_size;
    protected:
        void SetupObject(float* vertexes,long vertexes_size);
        void SetupObject(float* vertexes,long vertexes_size,uint* indexes,long indexes_size);
    public:
        [[nodiscard]] GLuint    GetVao() const;
        [[nodiscard]] int      GetVertex_amount() const;
        //Object(const GT::Geometrical_components& components);
        Object(const GLenum& draw_mode,std::vector<std::vector<glm::vec3>> vectors);
        Object(const GLenum& draw_mode,std::vector<std::vector<glm::vec3>> vectors,uint* indexes,long indexes_size);
        //Object(const GLenum& Draw_mode,const std::vector<glm::vec3>& vertex);
        //Object(const GLenum& Draw_mode,const std::vector<glm::vec3>& vertex,const std::vector<glm::vec3>& index);
        void Draw() const;
        std::vector<glm::vec3> Get_vertexes();
        [[nodiscard]] long Get_arrays_size() const;
        float* Pack_shader_params();
        [[nodiscard]] static float* Unpack_vertexes(std::vector<glm::vec3> packed_vertex);
        static std::vector<glm::vec3> Pack_vertex(std::unique_ptr<float[]> vertex,uint32_t size);

    };
    class Line : public Object{
    private:
        static std::vector<std::vector<glm::vec3 >>Generate_vectors(glm::vec3 origin, glm::vec3 target, glm::vec3 color);
        public:
        Line(glm::vec3 origin,glm::vec3 target,glm::vec3 color);
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
