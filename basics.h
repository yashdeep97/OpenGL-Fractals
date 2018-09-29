#ifndef BASICS_H
#define BASICS_H

#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h>

using namespace std;

class Basics{
    public:
        void drawPoint(int x, int y){
            int point[] = { x, y };
            glEnableClientState( GL_VERTEX_ARRAY ); //enable drawing vertex array
            // glPointSize(40.0);
            glVertexPointer( 2, GL_INT, 0, point );
            glDrawArrays( GL_POINTS, 0, 1);
            glDisableClientState( GL_VERTEX_ARRAY );
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
};

#endif