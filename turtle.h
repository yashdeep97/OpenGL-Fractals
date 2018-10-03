#ifndef TURTLE_H
#define TURTLE_H

#include "basics.h"
#include <algorithm>
#include <math.h>
#include <stack>

struct position{
    int x; // x coordinate of turtle
    int y; // y coordinate of turtle
    int a; // angle of turtle with x axis
};

class Turtle{
    private:
        stack <position> saved;  // stack for saving position of turtle (for branching)
        int currentX, currentY;  // current x and y coordinate of turtle
        int angle;  // current angle of the turtle
        Basics basics;  // object of Basics class
    public:
        // Set position of turtle to start drawing
        // @param x : x coordinate of starting point
        // @param y : y coordinate of starting point
        // @param a : angle to begin drawing with
        void setPosition(int x, int y, int a){
            currentX = x;
            currentY = y;
            angle = a;
        }
        // move turtle forward (with the predefined angle) and draw its path
        // @param l : length to move forward
        void forward(int l){
            double ang = ((double)angle / 180.0) * ((double) M_PI);
            int newX = currentX + (int)(l*cos(ang));
            int newY = currentY + (int)(l*sin(ang));
            basics.drawLine(currentX, currentY, newX, newY );
            currentX = newX;
            currentY = newY;
        }
        // Turn turtle right by given angle
        // @param a : angle
        void turnRight(int a){
            angle -= a;
        }
        // Turn turtle left by given angle
        // @param a : angle
        void turnLeft(int a){
            angle += a;
        }
        // Push current position of turtle into stack
        void pushState(){
            struct position curr;
            curr.x = currentX;
            curr.y = currentY;
            curr.a = angle;
            saved.push(curr);
        }
        // Pop from stackand set current position to it
        void popState(){
            struct position newCurr = saved.top();
            currentX = newCurr.x;
            currentY = newCurr.y;
            angle = newCurr.a;
            saved.pop();
        }
        // Change color of path being drawn
        // @param r : red intensity
        // @param g : green intensity
        // @param b : blue intensity
        void changeColor(GLfloat r, GLfloat g, GLfloat b){
            basics.setColor(r, g, b);
        }
        // Set width of path to be drawn
        // @param w : width
        void changeWidth(GLdouble w){
            basics.setWidth(w);
        }
        // Draw circle of radius r
        // @param r : radius
        void makeCircle(int r){
            basics.drawCircle(currentX, currentY, r);
        }

};

#endif