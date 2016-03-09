//
//  asteroids.h
//  Asteroids_CS165
//
//  Created by Drey Platt on 2/13/16.
//  Copyright (c) 2016 Drey Platt. All rights reserved.
//

#ifndef __Asteroids_CS165__asteroids__
#define __Asteroids_CS165__asteroids__
#include "point.h"
#include <stdio.h>
/*****************************************
 * Physics class
 * The base for all the physics in the game
 ****************************************/
class MovingObject{
public:
    float getDY(){return DY;};
    float getDX(){return DX;};
    float getX(){return currentPoint.getX();};
    float getY(){return currentPoint.getY();};
    Point getCurrentPoint(){return currentPoint;};
    void setX(float X) {currentPoint.setX(X);};
    void setY(float Y) {currentPoint.setY(Y);};
    void setDX(float dx) {DX = dx;};
    void setDY(float dy) {DY = dy;};
    bool isAlive() {return alive;}
    void kill() {alive = false;}
    void giveLife() {alive = true;}
    void updateCurrentPoint(){currentPoint.setX(getX()+DX); currentPoint.setY(getY()+DY);};
protected:
    bool alive;
    float DX;
    float DY;
    Point currentPoint; // location of the ShipCurrentPoint
};
/*****************************************
 * Physics class
 * The base for all the physics in the game
 ****************************************/
class Ship : public MovingObject
{
public:
    Ship();
    float getAngle(){return angle;};
    void setAngle(float newAngle) {angle = newAngle;};
private:
    float angle;
};
/*****************************************
 * Physics class
 * The base for all the physics in the game
 ****************************************/
class Asteroid : public MovingObject
{
public:
    Asteroid();
    Asteroid(int size, Point point);
    int getSize() {return size;}; //returns size of asteroid 1,2, or 3
    void setSize(int newSize) {size = newSize;}; //sets the asteroids size
    float getAngle(){return angle;};
    void setAngle(float newAngle) {angle = newAngle;};
private:
    int size;
    float angle;
};
/*****************************************
 * Physics class
 * The base for all the physics in the game
 ****************************************/
class Bullet : public MovingObject
{
public:
    Bullet();
    
};
/*****************************************
 * Asteroids
 * The main Asteroids structure containing everything
 * necessary to plan our beloved game
 ****************************************/
class Asteroids
{
public:
    Asteroids();                          // set rotateLeft the game
    void advanceShip();              // advance the game by one move
    void moveAsteroids();
    // void timeCheck();                // check to see if asteroid can go
    // void newasteroids();                 // create a new asteroid
    void draw();                     // draw everything
    void moveShip(int rotateLeft, int rotateRight, int forward, int reverse);     // move everything
    //void shoot(int shoot);           // Shoot a Ship out
    // void strike();                   // did we hit something?
private:
    bool dead;    // is the game over?
    int score;    // current score.. how many times did we hit the Ship?
    
};

#endif /* defined(__Asteroids_CS165__asteroids__) */
