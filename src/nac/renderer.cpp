// class that will render the scene using SDL2, SDL2_image, OpenGL, and imgui


// constructor
Renderer::Renderer()
{
	// SDL2 window
	window = nullptr;
	glContext = nullptr;
	majorVersion = 3;
	minorVersion = 3;

	// imgui
	io = ImGui::GetIO();

	//create a shader program
	shaderProgram = nullptr;

	//create a mesh
	mesh = nullptr;
	mesh2 = nullptr;

	//create a texture
	texture = nullptr;
	texture2 = nullptr;

	//create a camera
	camera = nullptr;

	//create a transform
	transform = nullptr;
	transform2 = nullptr;
}

// destructor
Renderer::~Renderer()
{
	Shutdown();
}

// initialize the renderer
bool Renderer::Initialize()
{
	// create the window
	window = SDL_CreateWindow("NAC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Error during SDL window creation!\n");
		return false;
	}

	// create the OpenGL context
	glContext = SDL_GL_CreateContext(window);
	if (!glContext)
	{
		printf("Error during SDL OpenGL context creation!\n");
		return false;
	}

	// set the OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);

	// set the OpenGL context to the current one
	SDL_GL_MakeCurrent(window, glContext);

	// initialize GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error during GLEW initialization: %s\n", glewGetErrorString(glewError));
		return false;
	}

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// create the shader program
	shaderProgram = new ShaderProgram("shaders\\vertex.glsl", "shaders\\fragment.glsl");

	// create the mesh
	mesh = new Mesh("res\\models\\cube.obj");
	mesh2 = new Mesh("res\\models\\cube.obj");

	// create the texture
	texture = new Texture("res\\textures\\test.png");
	texture2 = new Texture("res\\textures\\test.png");

	// create the camera
	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), 70.0f, (float)1280 / 720.0f, 0.01f, 1000.0f);

	// create the transform
	transform = new Transform();
	transform2 = new Transform();

	// initialize imgui
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui::StyleColorsDark();

	return true;
}