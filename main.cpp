// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "renderer.h"
#if defined(__EMSCRIPTEN__)
SDL_Window*     g_Window = NULL;
SDL_GLContext   g_GLContext = NULL;
// For clarity, our main loop code is declared at the end.
static void main_loop(void*);
#else
#include <GLFW/glfw3.h>
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
#endif


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "ImGui + GLFW", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		fprintf(stderr, "Failed to initialize WebGL context!\n");
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

	// Exporting variables to shaders
	glUseProgram(shaderProgram);
	glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
	glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Only draw the triangle if the ImGUI checkbox is ticked
		if (drawTriangle)
			// Draw the triangle using the GL_TRIANGLES primitive
			glDrawArrays(GL_TRIANGLES, 0, 3);

		// ImGUI window creation
		ImGui::Begin("My name is window, ImGUI window");
		// Text that appears in the window
		ImGui::Text("Hello there adventurer!");
		// Checkbox that appears in the window
		ImGui::Checkbox("Draw Triangle", &drawTriangle);
		// Slider that appears in the window
		ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		// Fancy color editor that appears in the window
		ImGui::ColorEdit4("Color", color);
		// Ends the window
		ImGui::End();

        g_sRenderer->BeginScene();

		// Export variables to shader
		glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

// int main(int, char**)
// {
// #if defined(__EMSCRIPTEN__)
//     // Setup SDL
//     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
//     {
//         printf("Error: %s\n", SDL_GetError());
//         return -1;
//     }
// #else
//     // Setup window
//     glfwSetErrorCallback(glfw_error_callback);
//     if (!glfwInit())
//         return 1;
// #endif

// #if defined(__EMSCRIPTEN__)
//     // For the browser using Emscripten, we are going to use WebGL1 with GL ES2. See the Makefile. for requirement details.
//     // It is very likely the generated file won't work in many browsers. Firefox is the only sure bet, but I have successfully
//     // run this code on Chrome for Android for example.
//     const char* glsl_version = "#version 100";
//     //const char* glsl_version = "#version 300 es";
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

//     // Create window with graphics context
//     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//     SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//     SDL_DisplayMode current;
//     SDL_GetCurrentDisplayMode(0, &current);
//     SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
//     g_Window = SDL_CreateWindow("Dear ImGui Emscripten example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
//     g_GLContext = SDL_GL_CreateContext(g_Window);
//     if (!g_GLContext)
//     {
//         fprintf(stderr, "Failed to initialize WebGL context!\n");
//         return 1;
//     }
//     SDL_GL_SetSwapInterval(1); // Enable vsync
// #else
//     const char* glsl_version = "#version 130";
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

//        // Create window with graphics context
//     GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
//     if (window == NULL)
//         return 1;
//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1); // Enable vsync

//     // Initialize OpenGL loader
// #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//     bool err = gl3wInit() != 0;
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//     bool err = gladLoadGL() == 0;
// #endif
//     if (err)
//     {
//         fprintf(stderr, "Failed to initialize OpenGL loader!\n");
//         return 1;
//     }
// #endif

//     // Setup Dear ImGui context
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
//     io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

// #if defined(__EMSCRIPTEN__)
//     io.IniFilename = NULL;

//     ImGui_ImplSDL2_InitForOpenGL(g_Window, g_GLContext);
//     ImGui_ImplOpenGL3_Init(glsl_version);
// #else
//     io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
//     ImGuiStyle& style = ImGui::GetStyle();
//     if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//     {
//         style.WindowRounding = 0.0f;
//         style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//     }

//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init(glsl_version);
// #endif

//     // Setup Dear ImGui style
//     ImGui::StyleColorsDark();
//     //ImGui::StyleColorsClassic();

// #if defined(__EMSCRIPTEN__)
//     // This function call won't return, and will engage in an infinite loop, processing events from the browser, and dispatching them.
//     emscripten_set_main_loop_arg(main_loop, NULL, 0, true);
// }

// static void main_loop(void* arg)
// {
//     ImGuiIO& io = ImGui::GetIO();
//     IM_UNUSED(arg); // We can pass this argument as the second parameter of emscripten_set_main_loop_arg(), but we don't use that.

//     // Our state (make them static = more or less global) as a convenience to keep the example terse.
//     static bool show_demo_window = true;
//     static bool show_another_window = false;
//     static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//     // Poll and handle events (inputs, window resize, etc.)
//     // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//     // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//     // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//     // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//     SDL_Event event;
//     while (SDL_PollEvent(&event))
//     {
//         ImGui_ImplSDL2_ProcessEvent(&event);
//         // Capture events here, based on io.WantCaptureMouse and io.WantCaptureKeyboard
//     }

//     // Start the Dear ImGui frame
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplSDL2_NewFrame(g_Window);
//     ImGui::NewFrame();

//     g_sRenderer->BeginScene();
    
//     // Rendering
//     ImGui::Render();
//     SDL_GL_MakeCurrent(g_Window, g_GLContext);
//     glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
//     glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//     glClear(GL_COLOR_BUFFER_BIT);
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//     SDL_GL_SwapWindow(g_Window);
// }
// #else
// 		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
       

//     // Main loop
//     while (!glfwWindowShouldClose(window))
//     {
//         // Poll and handle events (inputs, window resize, etc.)
//         // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//         // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//         // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//         // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//         glfwPollEvents();

//         // Start the Dear ImGui frame
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();

//         // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        
//         // Rendering
//         // NAC::Renderer* render = NAC::Renderer::GetInstance();
        
//         g_sRenderer->BeginScene();
//         g_sRenderer->drawCircle();
//         // ImVec2 window_pos = ImGui::GetWindowPos(); 
//         // ImVec2 window_size = ImGui::GetWindowSize(); 
//         // ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f); 
//         // ImGui::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 0, 10 + 4); 
//         // ImGui::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 0, 10);
//         // ImDrawList* draw_list = ImGui::GetWindowDrawList();
//         // static float sz = 36.0f; 
//         // static float thickness = 4.0f; 
//         // static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 1.0f); 
//         // const ImVec2 p = ImGui::GetCursorScreenPos(); 
//         // const ImU32 col32 = ImColor(col); 
//         // float x = p.x + 4.0f, y = p.y + 4.0f;
//         // draw_list->AddCircle(ImVec2(x+sz*0.5f, y+sz*0.5f), sz*0.5f, col32, 6, thickness);

//         ImGui::Render();
//         int display_w, display_h;
//         glfwGetFramebufferSize(window, &display_w, &display_h);
//         glViewport(0, 0, display_w, display_h);


        

//         glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//         glClear(GL_COLOR_BUFFER_BIT);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
//         // Update and Render additional Platform Windows
//         // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//         //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
//         if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//         {
//             GLFWwindow* backup_current_context = glfwGetCurrentContext();
//             ImGui::UpdatePlatformWindows();
//             ImGui::RenderPlatformWindowsDefault();
//             glfwMakeContextCurrent(backup_current_context);
//         }

//         glfwSwapBuffers(window);
//     }

//     // Cleanup
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }
// #endif
