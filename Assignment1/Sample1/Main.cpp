#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    int height = 500;
    int width = 500;

    window = glfwCreateWindow(height, width, "Nicholas Liu", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    float pi = 3.14159f;

    const int sides = 8;
    float z = 0.f;
    float r = 0.5f;
    float angle = 45.f;
    float offset = 0.54f;

    GLfloat vertices[sides * 3];
    for (int i = 0; i < 8; i++) {
        float x = i * angle + 22.5f;
        vertices[i * 3] = r * cos(x * pi / 180.f);
        vertices[i * 3 + 1] = r * sin(x * pi / 180.f);;
        vertices[i * 3 + 2] = z;
        //std::cout << i << ": " << vertices[i * 3] << ", " << vertices[i * 3 + 1] << std::endl;
    }
    for (int i = 0; i < 8; i++) {
        vertices[i * 3 + 1] += offset;
        //std::cout << i << ": " << vertices[i * 3] << ", " << vertices[i * 3 + 1] << std::endl;
    }
    unsigned int indices[] = {
        1,2,3,
        1,3,0,
        0,3,4,
        0,4,7,
        7,4,5,
        7,5,6
    };
    
    //float R = r / sin(67.5f);
    //float a = R * sin(22.5);
    GLuint VAO, VBO, EBO;
    //Initialize VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind VAO- any calls after this will automatically point to the VAO
    glBindVertexArray(VAO);
    //Create an array buffer to store our vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Create element array buffer to store indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //Add the size of our vertex array in bytes and the contents to the buffer
    glBufferData(GL_ARRAY_BUFFER, //What type of data is in this buffer
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);
        //
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Tell VAO how to interpret the array buffer
    glVertexAttribPointer(0,
        3, //Vertex has 3 properties- X, Y, Z positions
        GL_FLOAT, //Type of array to expect
        GL_FALSE, 
        3 * sizeof(float),
        (void*)0);
    //The VAO to use the data above
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        
        //Bind VAO to prep for drawing
        glBindVertexArray(VAO);
        //Draw opbect
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}