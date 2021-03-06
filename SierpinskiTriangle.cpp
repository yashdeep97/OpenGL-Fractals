#include "basics.h"
#include "turtle.h"
#include <string>
#include <unistd.h>
#include <time.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow *window);

void nextGeneration(string&);
void drawPatternFromString(string);

int main(void)
{
    GLFWwindow* window;
    srand(time(0));
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shrub", NULL, NULL);
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
    int i=0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawPatternFromString(axiom);
        if(i<8){
            nextGeneration(axiom);
            i++;
            sleep(1);
        }
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

void nextGeneration(string& str){
    int i = 0;
    string newstr = "";
    while(i < str.length()){
        if(str[i] == 'A'){
            newstr += "B-A-B";
        } else if(str[i] == 'B'){
            newstr += "A+B+A";
        } else {
            newstr += str[i];
        }
        i++;
    }
    str = newstr;
    
}

void drawPatternFromString(string str){
    
    Turtle turt;
    turt.setPosition(100,100,0);
    stack <int> lengthStack;
    int length = 3;
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == 'A' || str[i] == 'B'){
            turt.forward(length);
        } else if(str[i] == '-'){
            turt.turnRight(60);
        } else if(str[i] == '+'){
            turt.turnLeft(60);
        } else if(str[i] == '['){
            turt.pushState();
        } else if(str[i] == ']'){
            turt.popState();
            length = lengthStack.top();
            lengthStack.pop();
        }
    }
}