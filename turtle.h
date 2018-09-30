#ifndef TURTLE_H
#define TURTLE_H

#include "basics.h"
#include <algorithm>
#include <math.h>
#include <stack>

struct position{
    int x;
    int y;
    int a;
};

class Turtle{
    private:
        stack <position> saved;
        int currentX, currentY;
        int angle;
        Basics basics;
    public:
        void setPosition(int x, int y, int a){
            currentX = x;
            currentY = y;
            angle = a;
        }
        void forward(int l){
            double ang = ((double)angle / 180.0) * ((double) M_PI);
            int newX = currentX + (int)(l*cos(ang));
            int newY = currentY + (int)(l*sin(ang));
            basics.drawLine(currentX, currentY, newX, newY );
            currentX = newX;
            currentY = newY;
        }
        void turnRight(int a){
            angle -= a;
        }
        void turnLeft(int a){
            angle += a;
        }
        void pushState(){
            struct position curr;
            curr.x = currentX;
            curr.y = currentY;
            curr.a = angle;
            saved.push(curr);
        }
        void popState(){
            struct position newCurr = saved.top();
            currentX = newCurr.x;
            currentY = newCurr.y;
            angle = newCurr.a;
            saved.pop();
        }
        void changeColor(GLfloat r, GLfloat g, GLfloat b){
            basics.setColor(r, g, b);
        }

};

#endif