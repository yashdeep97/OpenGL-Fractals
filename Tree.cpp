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
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tree", NULL, NULL);
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
    
    string axiom = "F";
    int i=0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawPatternFromString(axiom);
        if(i<15){
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
        if(str[i] == 'F'){
            int x = rand();
            if(x%4 == 0){
                newstr += "F[-F][+F]";
            } else if(x%4 == 1){
                newstr += "F[-F]";
            } else if(x%4 == 2){
                newstr += "F[+F]";
            } else {
                newstr += "F";
            }
            
        } else {
            newstr += str[i];
        }
        i++;
    }
    str = newstr;
    
}

void drawPatternFromString(string str){
    
    Turtle turt;
    turt.setPosition(500,0,90);
    turt.changeWidth(2);
    stack <int> lengthStack;
    int length = 200;
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == 'F' || str[i] == 'H'){
            length *= 0.7;
            if (length > 10) {
                turt.changeColor(0.647059, 0.164706, 0.164706);
            } else {
                turt.changeColor(0.0, 1.0, 0.0);
            }
            turt.forward(length);
            
            if (length <= 10) {
                turt.makeCircle(3);
            }
        } else if(str[i] == '+'){
            turt.turnRight(30);
        } else if(str[i] == '-'){
            turt.turnLeft(30);
        } else if(str[i] == '['){
            turt.pushState();
            lengthStack.push(length);
        } else if(str[i] == ']'){
            turt.popState();
            length = lengthStack.top();
            lengthStack.pop();
        }
    }
}