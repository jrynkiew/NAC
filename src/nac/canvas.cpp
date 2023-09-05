#include "canvas.h"

namespace _NAC
{
    const char* Canvas::vertexShaderSource = R"(
        attribute vec3 aPos;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        varying vec3 FragColor;
        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            FragColor = aPos; // Color vertices based on their position
        }
    )";
    #ifdef __EMSCRIPTEN__
    const char* Canvas::fragmentShaderSource = R"(
        precision mediump float;
        varying vec3 FragColor;
        void main()
        {
            gl_FragColor = vec4(FragColor, 1.0);
        }
    )";
    #else
    const char* Canvas::fragmentShaderSource = R"(
        varying vec3 FragColor;
        void main()
        {
            gl_FragColor = vec4(FragColor, 1.0);
        }
    )";
    #endif

    float Canvas::cubeVertices[] = {
                // Positions
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f
            };
    
    unsigned int Canvas::cubeIndices[] = {
                0, 1, 2,
                2, 3, 0,
                4, 5, 6,
                6, 7, 4,
                0, 3, 7,
                7, 4, 0,
                1, 2, 6,
                6, 5, 1,
                2, 3, 6,
                6, 7, 3,
                0, 1, 5,
                5, 4, 0
            };

    Canvas::Canvas(GLFWwindow* window) {
        m_pWindow = window;
    }

    Canvas::~Canvas() {
    }

    bool Canvas::Initialize() {
        // Create Vertex Array Object (VAO), Vertex Buffer Object (VBO), and Element Buffer Object (EBO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind VAO
        glBindVertexArray(VAO);

        // Bind and set VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        // Bind and set EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Compile and link the shaders
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // Check for vertex shader compilation errors...

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Check for fragment shader compilation errors...

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for shader program linking errors...

        glUseProgram(shaderProgram);

        mat4x4_identity(model);
        mat4x4_translate_in_place(model, 0.0f, 0.0f, -3.0f); // Translate the cube back in the -z direction
        mat4x4_identity(view);
        mat4x4_identity(projection);
        mat4x4_perspective(projection, 45.0f * (3.14159265359f / 180.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Get the uniform locations for the shaders
        modelLoc = glGetUniformLocation(shaderProgram, "model");
        viewLoc = glGetUniformLocation(shaderProgram, "view");
        projectionLoc = glGetUniformLocation(shaderProgram, "projection");

        glEnable(GL_DEPTH_TEST);

        rotationSpeed = 0.01f;
        return true;
    }

    void Canvas::Shutdown() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
    }

    void Canvas::Draw() {
        glfwGetFramebufferSize(m_pWindow, &width, &height);
        glViewport(0, 0, width, height);
        // Rotate the cube
        // Adjust the speed as needed
        mat4x4_rotate_Y(model, model, rotationSpeed);
        mat4x4_rotate_X(model, model, rotationSpeed);

        // Update the uniform matrices
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)view);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (const GLfloat*)projection);

        // Draw the cube
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}
