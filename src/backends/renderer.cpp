#include "renderer.h"

namespace NAC
{
	Renderer* Renderer::m_pInstance;

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	Renderer* Renderer::GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new Renderer();

		return m_pInstance;
	}

	// void Renderer::Initialize()
	// {
	// 	// ImGuiIO& io = ImGui::GetIO();

	// 	// io.Fonts->AddFontFromMemoryTTF(g_fFont, sizeof(g_fFont), 14.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	// 	// m_pFont = io.Fonts->AddFontFromMemoryTTF(g_fFont, sizeof(g_fFont), 32.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	// }

	void Renderer::drawCircle()
	{
		// Shader sources
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
		// IMGUI_CHECKVERSION();
		// ImGui::CreateContext();
		// ImGuiIO& io = ImGui::GetIO(); (void)io;
		// ImGui::StyleColorsDark();
		// ImGui_ImplGlfw_InitForOpenGL(window, true);
		// ImGui_ImplOpenGL3_Init("#version 330");

		// Variables to be changed in the ImGUI window
		bool drawTriangle = true;
		float size = 1.0f;
		float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

		// Exporting variables to shaders
		glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		// ImGui_ImplOpenGL3_NewFrame();
		// ImGui_ImplGlfw_NewFrame();
		// ImGui::NewFrame();

		

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

		// Export variables to shader
		glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

	}

	void Renderer::BeginScene()
	{
       
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		static bool show_demo_window = true;
		static bool show_another_window = false;
        static float f = 0.0f;
        static int counter = 0;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

   
		ImVec2 window_pos = ImGui::GetWindowPos(); 
        ImVec2 window_size = ImGui::GetWindowSize(); 
        ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f); 
        ImGui::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 0, 10 + 4); 
        ImGui::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 0, 10);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        static float sz = 36.0f; 
        static float thickness = 4.0f; 
        static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 1.0f); 
        const ImVec2 p = ImGui::GetCursorScreenPos(); 
        const ImU32 col32 = ImColor(col); 
        float x = p.x + 4.0f, y = p.y + 4.0f;
        draw_list->AddCircle(ImVec2(x+sz*0.5f, y+sz*0.5f), sz*0.5f, col32, 6, thickness);

		
		// Rendering
       
		// ImGuiIO& io = ImGui::GetIO();

		// ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		// ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		// ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

		// ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		// ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
	}

	// void Renderer::EndScene()
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();
	// 	window->DrawList->PushClipRectFullScreen();

	// 	ImGui::End();
	// 	ImGui::PopStyleColor();
	// 	ImGui::PopStyleVar(2);
	// }

	// float Renderer::RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	std::stringstream stream(text);
	// 	std::string line;

	// 	float y = 0.0f;
	// 	int i = 0;

	// 	while (std::getline(stream, line))
	// 	{
	// 		ImVec2 textSize = m_pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

	// 		if (center)
	// 		{
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());

	// 			window->DrawList->AddText(m_pFont, size, { position.x - textSize.x / 2.0f, position.y + textSize.y * i }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), line.c_str());
	// 		}
	// 		else
	// 		{
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	// 			window->DrawList->AddText(m_pFont, size, { (position.x) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());

	// 			window->DrawList->AddText(m_pFont, size, { position.x, position.y + textSize.y * i }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), line.c_str());
	// 		}

	// 		y = position.y + textSize.y * (i + 1);
	// 		i++;
	// 	}

	// 	return y;
	// }

	// void Renderer::RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	window->DrawList->AddLine(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), thickness);
	// }

	// void Renderer::RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness, uint32_t segments)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	window->DrawList->AddCircle(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments, thickness);
	// }

	// void Renderer::RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xff;
	// 	float r = (color >> 16) & 0xff;
	// 	float g = (color >> 8) & 0xff;
	// 	float b = (color) & 0xff;

	// 	window->DrawList->AddCircleFilled(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments);
	// }

	// void Renderer::RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags, float thickness)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddRect(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags, thickness);
	// }

	// void Renderer::RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddRectFilled(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	// }

	// void Renderer::RenderImage(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddImage(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }));
	// }

	// void Renderer::RenderImageRounded(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	// {
	// 	ImGuiWindow* window = ImGui::GetCurrentWindow();

	// 	float a = (color >> 24) & 0xFF;
	// 	float r = (color >> 16) & 0xFF;
	// 	float g = (color >> 8) & 0xFF;
	// 	float b = (color) & 0xFF;

	// 	window->DrawList->AddImageRounded(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	// }
}