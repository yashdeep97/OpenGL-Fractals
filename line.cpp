#include <iostream>
#include <bits/stdc++.h>

#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow *window);
void drawPoint(int x, int y);
void drawLine(int x1, int y1, int x2, int y2);

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


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawLine(400, 0, 0, 100);

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

void drawPoint(int x, int y){
    int point[] = { x, y };
    glEnableClientState( GL_VERTEX_ARRAY ); //enable drawing vertex array
    // glPointSize(40.0);
    glVertexPointer( 2, GL_INT, 0, point );
    glDrawArrays( GL_POINTS, 0, 1);
    glDisableClientState( GL_VERTEX_ARRAY );
}

void drawLine(int x1, int y1, int x2, int y2){
    if(x1 > x2 && y1 > y2){
        swap(x1, x2);
        swap(y1, y2);
    } else if(x1 > x2 && y2 > y1){
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    //when modulus of slope is between 0 and 1
    if( abs( dx ) >= abs( dy ) ){
        //slope is between 0 and 1
        if( dy >= 0 ){
            int d = 2 * dy - dx;
            int incrE = 2 * dy;
            int incrNE = 2 * ( dy - dx );
            int x = x1, y = y1;
            drawPoint( x, y );
            while( x < x2 ){
                if( d <= 0 ){
                    d += incrE;
                    x++;
                } else {
                    d += incrNE;
                    x++;
                    y++;
                }
                drawPoint( x, y );
            }
        //slope beween -1 and 0
        } else {            
            int d = 2 * dy + dx;
            int incrE = 2 * dy;
            int incrSE = 2 * ( dy + dx );
            int x = x1, y = y1;
            drawPoint( x, y );
            while( x < x2 ){
                if( d > 0 ){
                    d += incrE;
                    x++;
                } else {
                    d += incrSE;
                    x++;
                    y--;
                }
                drawPoint( x, y );
            }
        }
     
    } else {
        //slope is greater than 1
        if( dy >= 0 ){
            int d = 2 * dx - dy;
            int incrN = 2 * dx;
            int incrNE = 2 * ( dx - dy );
            int x = x1, y = y1;
            drawPoint( x, y );
            while( y < y2 ){
                if( d <= 0 ){
                    d += incrN;
                    y++;
                } else {
                    d += incrNE;
                    x++;
                    y++;
                }
                drawPoint( x, y );
            }
        //slope is less than -1
        } else {
            int d = -2 * dx - dy;
            int incrS = -2 * dx;
            int incrSE = -2 * ( dx + dy );
            int x = x1, y = y1;
            drawPoint( x, y );
            while( y > y2 ){
                if( d <= 0 ){
                    d += incrSE;
                    y--;
                    x++;
                } else {
                    d += incrS;
                    y--;
                }
                drawPoint( x, y );
            }
        }
        
    }
    
}