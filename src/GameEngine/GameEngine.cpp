#include "include/GLFW/glfw3.h"
#include "GameEngine.h"

namespace engine {
    
     // Define the vertices
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    void gameEngine::initialize() {
        // Create a window and initialize OpenGL context
        window = glfwCreateWindow(800, 600, "My Game", NULL, NULL);
        glfwMakeContextCurrent(window);

        // Load shaders and set up vertex buffers
          // Define the shader loading function
    GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath);

        // Load shaders and set up vertex buffers
        shaderProgram = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    

        // Set up rendering parameters (e.g. depth testing, blending, etc.)
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void gameEngine::update() {
          // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind shader program and vertex buffer
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // Set up shader uniforms (e.g. camera position, model matrix, etc.)
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

        // Draw the scene
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the front and back buffers
        glfwSwapBuffers(window);
    }

    void gameEngine::shutdown() {
         // Delete vertex buffer and shader program
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(shaderProgram);

        // Destroy the window and OpenGL context
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
}
