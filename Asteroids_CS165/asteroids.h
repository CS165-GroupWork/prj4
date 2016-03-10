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
#include <cmath>
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
    float getRotation(){return rotation;};
    void setRotation(float theRotation){rotation = theRotation;};
    void updateCurrentPoint(){setX(getX()+DX); setY(getY()+DY);};
    
protected:
    bool alive;
    float DX;
    float DY;
    float rotation;
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
    float getVelocity(){return sqrt(getDX()*getDX()+getDY()*getDY());};
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
    //~Asteroid();
    Asteroid(int size);
    int getSize() {return size;}; //returns size of asteroid 1,2, or 3
    void setSize(int newSize) {size = newSize;}; //sets the asteroids size
    float getAngle(){return angle;};
    void setAngle(float newAngle) {angle = newAngle;};
    bool getIsHit() {return isHit;};
    void setHit(){isHit = true;};
    float getVelocity(){return sqrt(getDX()*getDX()+getDY()*getDY());};
private:
    int size;
    float angle;
    bool isHit = false;
};
/*****************************************
 * Physics class
 * The base for all the physics in the game
 ****************************************/
class Bullet : public MovingObject
{
public:
    Bullet();
    //~Bullet();
    
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
    void makeAsteroids(Point point, int sizeOfAsteroidHit, Asteroid &asteroid);
    void moveShip(int rotateLeft, int rotateRight, int forward, int reverse);     // move everything
    void shootBullets(int shoot);           // Shoot a Ship out
    void strike();                   // did we hit something?
    void killObjects();
private:
    bool dead;    // is the game over?
    int score;    // current score.. how many times did we hit the Ship?
    
};

#endif /* defined(__Asteroids_CS165__asteroids__) */
