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
void drawCircle(int xCenter , int yCenter , int radius);
void draw_eight_points(int xCenter , int yCenter , int x , int y);
void drawImage();
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

        drawImage();
        
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

void drawCircle(int xc , int yc , int radius){
	int x = 0 ;
	int y = radius ;
	int d = 1 - radius ;
	int deltaE = 3 ;
	int deltaSE = -2 * radius + 5 ;

	draw_eight_points(xc , yc , 0 , 0 ) ;

	while(y >x ){
		if(d < 0){ // selects E 
			d += deltaE ;
			deltaE += 2 ;
			deltaSE += 2 ;
		}
		else{ // selects SE 
			d += deltaSE ; 
			deltaSE += 4 ;
			deltaE += 2 ;
			y -- ;
		}
		x ++ ;
		draw_eight_points(xc , yc , x , y ) ;
	}
}

void draw_eight_points(int xc , int yc , int x , int y){
	drawPoint(xc + x , yc + y) ;
	drawPoint(xc - x , yc + y) ;
	drawPoint(xc + x , yc - y) ;
	drawPoint(xc - x , yc - y) ;
	drawPoint(xc + y , yc + x) ;
	drawPoint(xc + y , yc - x) ;
	drawPoint(xc - y , yc + x) ;
	drawPoint(xc - y , yc - x) ;
}

void drawLine(int x1, int y1, int x2, int y2){
    if(x1 > x2 && y1 >= y2){
        swap(x1, x2);
        swap(y1, y2);
    } else if(x1 > x2 && y2 >= y1){
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

void drawImage(){
    drawLine(100,100,250,400);
    drawLine(250,400,300,400);
    drawLine(300,400,300,150);
    drawLine(300,150,250,150);
    drawLine(250,150,250,200);
    drawLine(250,200,205,200);
    drawLine(205,200,150,100);
    drawLine(150,100,100,100);

    drawLine(250,240,250,310);
    drawLine(250,310,215,240);
    drawLine(215,240,250,240);

    drawLine(250,250,300,220);
    drawLine(250,190,300,220);

    drawCircle(235,240,120);
    drawCircle(235,240,160);
}