#pragma once
#define NAC_RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class Renderer
{
	private:
		// SDL2 window
		SDL_Window* window;
		SDL_GLContext glContext;
		SDL_Event event;

		// OpenGL context
		GLint majorVersion;
		GLint minorVersion;

		// imgui
		ImGuiIO io;
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//create a shader program
		ShaderProgram* shaderProgram;

		//create a mesh
		Mesh* mesh;
		Mesh* mesh2;

		//create a texture
		Texture* texture;
		Texture* texture2;

		//create a camera
		Camera* camera;

		//create a transform
		Transform* transform;
		Transform* transform2;

	public:
		Renderer();
		~Renderer();

		bool Initialize();
		void Shutdown();

		void Render();
		void DrawGUI();
};