//
// Created by ehecatl on 7/12/24.
//

#ifndef SIMVIZ_SIM_VIZ_HPP
#define SIMVIZ_SIM_VIZ_HPP


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
    [[maybe_unused]] void Say_hello();
    class Window{
    private:
        static uint8_t windows_amount;
        std::string title;
        [[maybe_unused]] uint32_t width;
        [[maybe_unused]] uint32_t height;
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
        void Mount_Dimensions_2_shader(const std::string &shaders_name);
        [[maybe_unused]] void Set_background_color(glm::vec3 color);
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
            [[maybe_unused]] void Set_View_matrix(glm::mat4 new_view_matrix);
            [[maybe_unused]] void Set_Projection_matrix(glm::mat4 new_projection_matrix);
            [[maybe_unused]] void Set_Rotation_matrix(glm::mat4 new_rotation_matrix);

            //Calculate matrices
            [[maybe_unused]] void Create_View_matrix(glm::vec3 camera_position,glm::vec3 camera_target,glm::vec3 normal);
            [[maybe_unused]] void Create_Projection_matrix(uint32_t w_width,uint32_t w_height,float fov, float zNear,float zFar);
            //void Create_Projection_matrix(float fov, float zNear,float zFar);
            [[maybe_unused]] void Create_Rotation_matrix(float angle_radian, glm::vec3 rotation_axis);
        };
        class Shaders{
        private:
            std::map<std::string,GLint> shader;
            static std::string Read_file(const char* file);
        public:
            [[maybe_unused]] void Load_custom_shaders(const std::string &shader_name,const std::string& vertex_file,const std::string &fragment_file);
            [[maybe_unused]] void Build_premaded_shaders(uint16_t Flags);
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

        uint    Width,Height;
        GLenum Draw_mode;
        [[maybe_unused]] GLuint VAO,VBO,EBO;
        int Indexes_size;
    protected:
        std::vector<std::vector<glm::vec3>> shader_parameters;
        glm::vec3 Position{};

        void SetupObject(float* vertexes,long vertexes_size,uint* indexes,long indexes_size);
    public:
        [[maybe_unused]] [[nodiscard]] GLuint    GetVao() const;
        [[maybe_unused]] [[nodiscard]] int      GetVertex_amount() const;
        //Object(const GT::Geometrical_components& components);
        // Without position
        [[maybe_unused]] Object(const GLenum& draw_mode,std::vector<std::vector<glm::vec3>> vectors);
        [[maybe_unused]] Object(const GLenum& draw_mode,std::vector<std::vector<glm::vec3>> vectors,uint* indexes,long indexes_size);
        //With position
        [[maybe_unused]] Object(glm::vec3 position ,const GLenum& draw_mode,std::vector<std::vector<glm::vec3>> vectors);
        [[maybe_unused]] Object(glm::vec3 position ,const GLenum& draw_mode,std::vector<std::vector<glm::vec3>> vectors,uint* indexes,long indexes_size);
        //Object(const GLenum& Draw_mode,const std::vector<glm::vec3>& vertex);
        //Object(const GLenum& Draw_mode,const std::vector<glm::vec3>& vertex,const std::vector<glm::vec3>& index);
        void Draw() const;
        [[maybe_unused]] std::vector<glm::vec3> Get_vertexes();
        [[nodiscard]] long Get_arrays_size() const;
        float* Pack_shader_params();
        [[maybe_unused]] [[nodiscard]] static float* Unpack_vertexes(std::vector<glm::vec3> packed_vertex);
        [[maybe_unused]] static std::vector<glm::vec3> Pack_vertex(std::unique_ptr<float[]> vertex,uint32_t size);
        [[maybe_unused]] void Move(glm::vec3 displacement);
        [[maybe_unused]] void Rotate(glm::vec3 axis,float radians);
        [[maybe_unused]] void Rotate(float pitch,float yaw);
        [[maybe_unused]] void Scale_up(float scale);
        [[maybe_unused]] void Mirror(glm::vec3 mirror_plane);
        [[maybe_unused]] void Update();

    };
    class [[maybe_unused]] Line : public Object{
    protected:
        static std::vector<std::vector<glm::vec3 >>Generate_vectors(glm::vec3 origin, glm::vec3 target, glm::vec3 color);
    public:
        Line(glm::vec3 origin,glm::vec3 target,glm::vec3 color);
        void Re_def(glm::vec3 origin,glm::vec3 target);
    };
    class [[maybe_unused]] N_agon : public Object{
    protected:
        static std::vector<std::vector<glm::vec3>> Generate_vectors(glm::vec3 center, float radius,uint sides,glm::vec3 color);
    public:
        N_agon(glm::vec3 center, float radius,uint sides,glm::vec3 color);
    };
    class [[maybe_unused]] Circle : public N_agon{
    protected:

    public:
        [[maybe_unused]] Circle(glm::vec3 center, float radius,glm::vec3 color);
    };
    class [[maybe_unused]] Cuboid : public Object{

    };
    class [[maybe_unused]] Pyramid : public Object{

    };
    class [[maybe_unused]] Prism : public  Object{

    };
    class [[maybe_unused]] Polyhedron  : public Object{

    };
    class [[maybe_unused]] Hyperboloid : public Object{
    protected:
        static std::vector<std::vector<glm::vec3 >>Generate_vectors(glm::vec3 center, glm::vec3 focus, float difference, float lim_inf, float lim_sup, float resolution, uint points_per_disc, glm::vec3 color);
    public:
        Hyperboloid(glm::vec3 center,glm::vec3 focus,float diference,float lim_inf,float lim_sup,float resolution,uint points_per_disc, glm::vec3 color);

    };


}


#endif //SIMVIZ_SIM_VIZ_HPP