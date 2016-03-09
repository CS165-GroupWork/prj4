//
//  asteroids.cpp
//  Asteroids_CS165
//
//  Created by Drey Platt on 2/13/16.
//  Copyright (c) 2016 Drey Platt. All rights reserved.
//

#include "asteroids.h"
/***********************************************************************
 * Program:
 *    Project
 * Author:
 *    Br. Helfrich
 * Summary:
 *     This game is a set of classes each representing a different object
 *
 * Ship
 * - dX
 * - dY
 * - direction
 * - currentPoint
 * Bullets
 * - dX
 * - dY
 * - size
 * - velocity
 * - direction
 * - currentPoint
 * Asteroids
 * - dX
 * - dY
 * - size
 * - velocity
 * - direction
 * - currentPoint

 ***********************************************************************/

#include "point.h"       // the Ship has a position
#include "uiInteract.h"  // interface with OpenGL
#include "uiDraw.h"      // all the draw primitives exist here
#include <math.h>  //for the sine and cosine values
#include "asteroids.h"
#include <vector>
#include <stdlib.h>
#include <math.h>



#define shipSize 25
#define PI 3.14159265 //to convert to radians from degrees
float currentTime = 0.00;
// set the bounds of the game
float Point::xMin = -150.0;
float Point::xMax =  150.0;
float Point::yMin = -150.0;
float Point::yMax =  150.0;
bool isfinishedStrike = true;
bool isfinishedAdvance = true;
bool anotherasteroid = true;
bool isfinishedAdvanceAsteroids = true;
float randasteroidTime;
int bulletDiameter = 2;
int asteroidDiameter = 20;
float shipAngle = 0;
float timeTilNextasteroid;
float ShipVelocity = 10;
int score = 0;
bool leftIsPressed;
bool rightIsPressed;
bool forwardIsPressed;
bool reverseIsPressed;
int timePressedRight = 0;
int timePressedLeft = 0;

Ship ship;
std::vector <Bullet> theBullets;
std::vector <Asteroid> theAsteroids;

/***************************************************
 * Asteroids :: CONSTRUCTOR
 * Give the bullet a set velocity and set
 * the positions of everything else.
 ***************************************************/
Ship::Ship()
{
    // put the ShipCurrentPoint where it belongs
//    ship.setX(0);
//    ship.setY(0);
    shipAngle = 0;
};
/***************************************************
 * Asteroids :: CONSTRUCTOR
 * Give the bullet a set velocity and set
 * the positions of everything else.
 ***************************************************/
Asteroids::Asteroids()
{
    // put the ShipCurrentPoint where it belongs
    shipAngle = 0;
};

Asteroid::Asteroid(){
    this->setSize(3);
    this->setX(random(ship.getCurrentPoint().getXMin(), ship.getCurrentPoint().getXMax()));
    this->setY(random(ship.getCurrentPoint().getYMin(), ship.getCurrentPoint().getYMax()));
    this->setDX(random(-.2, .2));
    this->setDY(random(-.2, .2));
    this->setAngle(random(0, 360));
    this->giveLife();
}
//
///********************************************
// * Asteroids :: ADVANCE
// * Move the Ship forward by some amount
// *******************************************/
void Asteroids::advanceShip()
{
ship.updateCurrentPoint();
isfinishedAdvance = true;
    float X = ship.getCurrentPoint().getX();
    float Y = ship.getCurrentPoint().getY();
    float newX = X * -1;
    float newY = Y * -1;
    //check bounds for ship so its not so boring
    if(X > ship.getCurrentPoint().getXMax()){
        ship.setX(newX);
        //std::cout << "RIGHT" << std::endl;
    }
    if(X < ship.getCurrentPoint().getXMin()){
        ship.setX(newX);
        //std::cout << "LEFT" << std::endl;
    }
    if(Y > ship.getCurrentPoint().getYMax()){
        ship.setY(newY);
        //std::cout << "TOP" << std::endl;
    }
    if(Y < ship.getCurrentPoint().getYMin()){
        ship.setY(newY);
        //std::cout << "BOTTOM" << std::endl;
    }
}
///********************************************
// * Asteroids :: moveAsteroids
// *******************************************/
void Asteroids::moveAsteroids()
{
    
    //loop through the Asteroids
for (int j = 0; j < theAsteroids.size(); j++){
    theAsteroids[j].updateCurrentPoint();
    float X = theAsteroids[j].getCurrentPoint().getX();
    float Y = theAsteroids[j].getCurrentPoint().getY();
    float newX = X * -1;
    float newY = Y * -1;
    //check bounds for ship so its not so boring
    if(X > theAsteroids[j].getCurrentPoint().getXMax()){
        theAsteroids[j].setX(newX);
        //std::cout << "RIGHT" << std::endl;
    }
    if(X< theAsteroids[j].getCurrentPoint().getXMin()){
        theAsteroids[j].setX(newX);
        //std::cout << "LEFT" << std::endl;
    }
    if(Y   > theAsteroids[j].getCurrentPoint().getYMax()){
        theAsteroids[j].setY(newY);
        //std::cout << "TOP" << std::endl;
    }
    if(Y  < theAsteroids[j].getCurrentPoint().getYMin()){
        theAsteroids[j].setY(newY );
        //std::cout << "BOTTOM" << std::endl;
    }

        }
        isfinishedAdvanceAsteroids = true;
}
///****************************************
// * STRIKE
// * Strike the ShipCurrentPoint.  The further from the center,
// * the more it hits
// ****************************************/
//void Asteroids::strike()
//{
//    
//    // Ship not at the ShipCurrentPoint yet
//    //loop through all the bullets in vector
//    int theSize = (int)theBullets.size();
//    int theasteroidSize =(int)theasteroids.size();
//    for (int i = 0; i < theSize; i++){
//        float bulX = theBullets[i].bulletPoint.getX();
//        float bulY = theBullets[i].bulletPoint.getY();
//        for (int j = 0; j < theasteroidSize; j++){
//            float asteroidX = theasteroids[j].asteroidPoint.getX();
//            float asteroidY = theasteroids[j].asteroidPoint.getY();
//            //if the distance is closer than the tolerance level
//            if((bulX-asteroidX < 30) || (bulY-asteroidY <30)){
//                float disBetween = sqrtf((fabs(asteroidX - bulX)* fabs(asteroidX - bulX)) +(fabs(asteroidY - bulY)* fabs(asteroidY - bulY)));
//                //  std::cout << "Dist: " << disBetween << << std::endl;
//                if (disBetween < 24){
//                    //remove the asteroid and bullet
//                    theBullets[i] = theBullets.back(); theBullets.pop_back(); //i--;
//                    theasteroids[j] = theasteroids.back(); theasteroids.pop_back(); //j--;
//                    score++;
//                    //theasteroids[i].alive = false;
//                    //theBullets[j].alive = false;
//                }
//            }
//        }
//        
//    }
//    //
//    // yeah, we hit the Ship
//    //
//    
//    // hit.  Change the dx direction.
//    //   dx *= -1.0;
//    //   Ship.setX(Ship.getXMax() - 1.0);
//    //
//    //   // get some score
//    //   score++;
//    //
//    //   // speed rotateLeft every 5 points
//    //   if (score % 5 == 0)
//    //      dx += -1.0;
//    //
//    //   // the dy is changed by the angle.
//    //   dy += distance / 5;
//    isfinishedStrike=true;
//}
//
//
///**************************************************
// * SKEET : SHOOT
// * Shoot the Ship with the spacebar
// *************************************************/
//void Asteroids::shoot(int space)
//{
//    //Should a new bullet Ship be shot out?
//    if(space && theBullets.size() < 5){
//        
//        //create a new bullet
//        Bullet newBullet;
//        //set that bullets velocity
//        newBullet.dx = ShipVelocity*(sin((angle-90)*PI/180));
//        newBullet.dy = ShipVelocity*(cos((angle-90)*PI/180));
//        //give that new bullet its start location
//        newBullet.bulletPoint.setX(ShipCurrentPoint.getXMax());
//        newBullet.bulletPoint.setY(ShipCurrentPoint.getYMin());
//        //add that bullet to the vector 'theBullets'
//        theBullets.push_back(newBullet);
//        //create a new bullet Ship
//        //give that bulet Ship a start location
//        
//        //give it a velocity x and y based on current angle
//        
//        //        Point rotateLeftpoint(Ship.getXMin() + 5, Ship.getYMax() - 50);
//        //        drawNumber(rotateLeftpoint, dy);
//        //        // draw the rotateRight
//        //Point rotateRightpoint(5,  - 100);
//        // drawNumber(rotateRightpoint, (int)theBullets.size());
//    }
//    
//}
//
///**************************************************
// * Asteroids : TIMECHECK
// * Move the ShipCurrentPoint
// *************************************************/
//void Asteroids::timeCheck()
//{
//    if (timeTilNextasteroid<=currentTime){
//        //set the random asteroid time
//        randasteroidTime = ((float) rand() / (RAND_MAX));
//        //set current time as the last time a asteroid was released
//        timeTilNextasteroid = currentTime + randasteroidTime;
//        anotherasteroid = true;
//        // std::cout << "asteroid";
//    } else {
//        anotherasteroid = false;
//    }
//}
///**************************************************
// * Asteroids : NEWasteroidS
// * create a new asteroid object
// *************************************************/
//void Asteroids::newasteroids()
//{
//    float randXVelocity = ((float) rand() / (RAND_MAX));
//    float randYVelocity = ((float) rand() / (RAND_MAX));
//    float randYPos = ((float) rand() / (RAND_MAX));
//    //create a new bullet
//    asteroid newasteroid;
//    //give that new asteroid its start location
//    newasteroid.asteroidPoint.setX(newasteroid.asteroidPoint.getXMin());
//    float yPos = (newasteroid.asteroidPoint.getYMax() - newasteroid.asteroidPoint.getYMin()) * randYPos;
//    
//    //std::cout << "new asteroid\n";
//    float newYpos=newasteroid.asteroidPoint.getYMin() + yPos;
//    newasteroid.asteroidPoint.setY(newYpos);
//    //set that bullets velocity
//    float asteroidXVel = (randXVelocity*3) + 3;
//    float asteroidYVel = (randYVelocity*4);
//    //if the asteroid is above the half way point makes it come rotateRight
//    if (newYpos > 0){
//        asteroidYVel = asteroidYVel * -1;
//    }
//    newasteroid.dx = asteroidXVel;
//    newasteroid.dy = asteroidYVel;
//    //std::cout << "new asteroid "<< asteroidXVel << ", " << asteroidYVel << "ypos: " << newYpos << "\n";
//    //add that asteroid to the vector 'theasteroids'
//    theasteroids.push_back(newasteroid);
//}
/**************************************************
 * Asteroids : MOVE
 * Move the gun
 *************************************************/
void Asteroids::moveShip(int rotateLeft, int rotateRight, int forward, int reverse)
{
    //booleans to check if the keys have been released
    float newAngle = 0;
    float prevAngle =ship.getAngle();
    float newDX;
    float newDY;
    float prevDX = ship.getDX();
    float prevDY = ship.getDY();
    /////////ADJUST THE SPEED NOW ////////
    if (forward>0) {
        //go forward by increasing dx and dy relative to the angle
        newDY = -.2*(sin((prevAngle-90)*PI/180));
        newDX = -.2*(cos((prevAngle-90)*PI/180));
        ship.setDX(newDX + prevDX);
        ship.setDY(newDY + prevDY);
        forwardIsPressed = true;
        //now the change is figured out add that to the current x and y
    }
    
    
    if (reverse>0 ){
        newDY = .2*(sin((prevAngle-90)*PI/180));
        newDX = .2*(cos((prevAngle-90)*PI/180));
        ship.setDX(newDX + prevDX);
        ship.setDY(newDY + prevDY);
        
    }
    
    
    
    if (forward==0){
        forwardIsPressed = false;
    }
    
    if (reverse==0){
        reverseIsPressed = false;
    }
    if (rotateLeft>0) {
        timePressedRight++;
        int multiplier = (timePressedRight % 5) + 1;
        newAngle = prevAngle - (2 * multiplier);
        ship.setAngle(newAngle);
    }
    if (rotateRight>0 ){
        timePressedLeft++;
        int multiplier = (timePressedLeft % 5) + 1;
        newAngle = prevAngle + (2 * multiplier);
        ship.setAngle(newAngle);
    }
    
    if (rotateRight==0){
        leftIsPressed = false;
        timePressedLeft = 0;
    }
    
    if (rotateLeft==0){
        rightIsPressed = false;
        timePressedRight = 0;
    }

}
/*************************************************
 * Asteroids : DRAW
 * Draw the stuff
 ************************************************/
void Asteroids::draw()
{

    // draw the Ship and the ShipCurrentPoint
 
    drawShip(ship.getCurrentPoint(), ship.getAngle(),forwardIsPressed);
    
    // draw the Ship
    //loop through all the bullets in the vector and draw them
//    for (int i = 0; i < theBullets.size(); i++){
//        if (theBullets[i].alive){
//            drawCircle(theBullets[i].bulletPoint, bulletDiameter);
//            //drawNumber(theBullets[i].bulletPoint, i);
//        }
//    }
    // draw the asteroids
    //loop through all the asteroids in the vector and draw them
    for (int j = 0; j < theAsteroids.size(); j++){
        if (theAsteroids[j].isAlive()){
            if(theAsteroids[j].getSize() == 3){
                drawLargeAsteroid( theAsteroids[j].getCurrentPoint(), theAsteroids[j].getAngle());
            }
            if(theAsteroids[j].getSize() == 2){
                drawMediumAsteroid(theAsteroids[j].getCurrentPoint(), theAsteroids[j].getAngle());
            }
            if(theAsteroids[j].getSize() == 1){
                drawSmallAsteroid(theAsteroids[j].getCurrentPoint(), theAsteroids[j].getAngle());;
            }
            // drawNumber(theasteroids[j].asteroidPoint, j);
        }
        //  std::cout << theasteroids[j].asteroidPoint;
    }
   Point scorePointX(ship.getCurrentPoint().getXMin() + 5, ship.getCurrentPoint().getYMax() - 5);
     Point scorePointY(ship.getCurrentPoint().getXMin() + 5, ship.getCurrentPoint().getYMax() - 20);
   drawNumber(scorePointX, ship.getX());
    drawNumber(scorePointY, ship.getY());
}
//
/*********************************************
 * CALLBACK
 * The main interaction loop of the engine.
 * This gets called from OpenGL.  It give us our
 * interface pointer (where we get our events from)
 * as well as a void pointer which we know is our
 * game class.
 *********************************************/
void callBack(const Interface *pUI, void *p)
{
    
    currentTime = currentTime +.0333;
    // we know the void pointer is our game class so
    // cast it into the game class.
    Asteroids *pAsteroids = (Asteroids *)p;
    
//    pAsteroids->shoot(pUI->isSpace());
//    //only run if previous loop is finished
//    if (isfinishedStrike){
//        isfinishedStrike = false;
//        pAsteroids->strike();
//    }
//    // advance the Ship
    if(isfinishedAdvanceAsteroids){
        isfinishedAdvanceAsteroids = false;
         pAsteroids->moveAsteroids();
    }
    
    if(isfinishedAdvance){
        isfinishedAdvance = false;
        pAsteroids->advanceShip();
    }
//
//    //std::cout << isfinishedAdvance << isfinishedStrike <<std::endl;
//    // check the ShipCurrentPoint
    pAsteroids->moveShip(pUI->isRight(), pUI->isLeft(), pUI->isUp(), pUI->isDown());
    pAsteroids->moveAsteroids();
    pAsteroids->draw();
//    // did we hit the Ship?
//    
//    //check if another asteroid can be realeased yet
//    //get back boolean value
//    pAsteroids->timeCheck();
//    
//    if(anotherasteroid){
//        //we can now initiate another asteroid and add it to the asteroid vector
//        pAsteroids->newasteroids();
//    }
    // draw it
    
}


/*********************************
 * MAIN
 * initialize the drawing window, initialize
 * the game,and run it!
 *********************************/
int main(int argc, char **argv)
{
    
    // Start the drawing
    Interface ui(argc, argv, "Asteroids!");
    
    // play the game.  Our function callback will get called periodically
    //called 30 times per second
    
    Asteroids Asteroids;
    
    //create starting large asteroids 5 of them
    for (int i = 0; i<5; i++){
        Asteroid newAsteroid;
        theAsteroids.push_back(newAsteroid);
    }
    

    ui.run(callBack, (void *)&Asteroids);
    
    return 0;
}
