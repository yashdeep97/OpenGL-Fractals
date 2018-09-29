#include "basics.h"
#include "turtle.h"
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow *window);

void drawPattern(Turtle& turt, int l);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (window == NULL)
    {
		cout<<"Failed to create window"<<endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // New coordinate system
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode( GL_MODELVIEW );

	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    string axiom = "A";


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Turtle turt;
        turt.setPosition(320,0,90);
        drawPattern(turt, 100);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

		// handle escape key press
        processInput(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Re-adjust Viewport size when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// cout<<height<<" "<<width<<endl;
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void drawPattern(Turtle& turt, int l){

    turt.forward(l);
    if(l>1){
        turt.pushState();
        turt.turnRight(30);
        drawPattern(turt,l*0.7);

        turt.popState();
        turt.turnLeft(30);
        drawPattern(turt, l*0.7);
    }
}