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
int ticks =0;
bool isfinishedStrike;
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
int lives = 3;
bool canShootAnother;
bool leftIsPressed;
bool rightIsPressed;
bool forwardIsPressed;
bool reverseIsPressed;
int timePressedRight = 0;
int timePressedLeft = 0;
bool objectsHaveDied = false;
Ship ship;
std::vector <Bullet> theBullets;
std::vector <Asteroid> theAsteroids;

/***************************************************
 * Ship :: CONSTRUCTOR
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
 * Bullet :: CONSTRUCTOR
 * Give the bullet a set velocity and set
 * the positions of everything else.
 ***************************************************/
Bullet::Bullet()
{
//    float thex = ship.getCurrentPoint().getX();
//    float they = ship.getCurrentPoint().getY();
//    this->getCurrentPoint().setX(thex);
//    this->getCurrentPoint().setY(they);
    float angleRadian = (ship.getAngle()-90) *PI/180;
    this->setDX(-1*(ship.getVelocity()+5)*cos(angleRadian));
    this->setDY(-1*(ship.getVelocity()+5)*sin(angleRadian));
    alive = true;
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
    setSize(3);
    setX(random(ship.getCurrentPoint().getXMin(), ship.getCurrentPoint().getXMax()));
    setY(random(ship.getCurrentPoint().getYMin(), ship.getCurrentPoint().getYMax()));
    setDX(random(-.2, .2));
    setDY(random(-.2, .2));
    setAngle(random(0, 360));
    giveLife();
    setRotation(random(-2, 2));
}
Asteroid::Asteroid(int size){
    setSize(size);
    giveLife();
}
void Asteroids::makeAsteroids(Point point, int sizeOfAsteroidHit, Asteroid &asteroid){
    float angleRadian = (asteroid.getAngle()-90) *PI/180;
    if (sizeOfAsteroidHit == 3){
            //create 2 medium asteroids and a small
        Asteroid mediumForward(2);
        
        mediumForward.setX(point.getX());
        mediumForward.setY(point.getY());
        mediumForward.setAngle(asteroid.getAngle());
        
        mediumForward.setDX(-1*(asteroid.getVelocity()+1)*cos(angleRadian));
        mediumForward.setDY(-1*(asteroid.getVelocity()+1)*sin(angleRadian));
        theAsteroids.push_back(mediumForward);
        Asteroid mediumBack(2);
        
        mediumBack.setX(point.getX());
        mediumBack.setY(point.getY());
        mediumBack.setDX(-1*(asteroid.getVelocity()-1)*cos(angleRadian));
        mediumBack.setDY(-1*(asteroid.getVelocity()-1)*sin(angleRadian));
        mediumBack.setAngle(asteroid.getAngle());
        theAsteroids.push_back(mediumBack);
    }else if(sizeOfAsteroidHit == 2){
           // create 2 small asteroids
            Asteroid smallLeft(1);
        
        smallLeft.setX(point.getX());
        smallLeft.setY(point.getY());
        smallLeft.setDX(1*(asteroid.getVelocity()-1)*cos(angleRadian));
        smallLeft.setDY(-1*(asteroid.getVelocity()-1)*sin(angleRadian));
        smallLeft.setAngle(asteroid.getAngle());
        theAsteroids.push_back(smallLeft);
    };
    //there is always a smallRight one
  Asteroid smallRight(1);

    
    //change properties for smallRight
    smallRight.setX(point.getX());
    smallRight.setY(point.getY());
    smallRight.setDX(-1*(asteroid.getVelocity()-1)*cos(angleRadian));
    smallRight.setDY(1*(asteroid.getVelocity()-1)*sin(angleRadian));
    smallRight.setAngle(asteroid.getAngle());
    theAsteroids.push_back(smallRight);
    asteroid.kill();
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
    else if(X< theAsteroids[j].getCurrentPoint().getXMin()){
        theAsteroids[j].setX(newX);
        //std::cout << "LEFT" << std::endl;
    }
    else if(Y   > theAsteroids[j].getCurrentPoint().getYMax()){
        theAsteroids[j].setY(newY);
        //std::cout << "TOP" << std::endl;
    }
    else if(Y  < theAsteroids[j].getCurrentPoint().getYMin()){
        theAsteroids[j].setY(newY );
        //std::cout << "BOTTOM" << std::endl;
    }

        }
        isfinishedAdvanceAsteroids = true;
}
/****************************************
 * STRIKE
 * Strike the ShipCurrentPoint.  The further from the center,
 * the more it hits
 ****************************************/
void Asteroids::strike()
{
    
    // Ship not at the ShipCurrentPoint yet
    //loop through all the bullets in vector
    int theSize = (int)theBullets.size();
    int theAsteroidSize =(int)theAsteroids.size();
    
    
    for (int i = 0; i < theSize; i++){
        float bulX = theBullets[i].getX();
        float bulY = theBullets[i].getY();
        for (int j = 0; j < theAsteroidSize; j++){
            float asteroidX = theAsteroids[j].getX();
            float asteroidY = theAsteroids[j].getY();
            //if the distance is closer than the tolerance level
            if((bulX-asteroidX < (theAsteroids[j].getSize() * 10)) || (bulY-asteroidY < (theAsteroids[j].getSize() * 10))){
                float disBetween = sqrtf((fabs(asteroidX - bulX)* fabs(asteroidX - bulX)) +(fabs(asteroidY - bulY)* fabs(asteroidY - bulY)));
                //  std::cout << "Dist: " << disBetween << << std::endl;
                if (disBetween < 20){
                    theAsteroids[j].setHit();
                    //std::cout << j ;
                    int which = theAsteroids[j].getSize();
                    if (which == 3) {
                        //large asteroid to 2 medium and 1 small
                        makeAsteroids(theAsteroids[j].getCurrentPoint(), 3, theAsteroids[j]);
                        // std::cout << k;
                    } else if (which == 2){
                        //medium asteroid to 2 small
                        makeAsteroids(theAsteroids[j].getCurrentPoint(), 2, theAsteroids[j]);
                    } else {
                        theAsteroids[j].kill();
                    }
                    theBullets[i].kill();
                }
            }
        }
        
    }
    //now check on the ship collision
   
        float bulX = ship.getX();
        float bulY = ship.getY();
        for (int j = 0; j < theAsteroidSize; j++){
            float asteroidX = theAsteroids[j].getX();
            float asteroidY = theAsteroids[j].getY();
            //if the distance is closer than the tolerance level
            if((bulX-asteroidX < (theAsteroids[j].getSize() * 10)) || (bulY-asteroidY < (theAsteroids[j].getSize() * 10))){
                float disBetween = sqrtf((fabs(asteroidX - bulX)* fabs(asteroidX - bulX)) +(fabs(asteroidY - bulY)* fabs(asteroidY - bulY)));
                //  std::cout << "Dist: " << disBetween << << std::endl;
                if (disBetween < 20){
                    theAsteroids[j].setHit();
                    ship.setX(0);
                    ship.setY(0);
                    ship.setAngle(0);
                    int which = theAsteroids[j].getSize();
                    if (which == 3) {
                        //large asteroid to 2 medium and 1 small
                        makeAsteroids(theAsteroids[j].getCurrentPoint(), 3, theAsteroids[j]);
                        // std::cout << k;
                    } else if (which == 2){
                        //medium asteroid to 2 small
                        makeAsteroids(theAsteroids[j].getCurrentPoint(), 2, theAsteroids[j]);
                    } else {
                        theAsteroids[j].kill();
                    }

                    lives--;
                }
            }
        }
    

        //remove and add asteroids depending on size
//    for (int k = 0; k < theAsteroidSize; k++){
//            bool hasItHit = theAsteroids[k].getIsHit();
//            if (hasItHit){
//                std::cout << hasItHit;
//
//            }
       // }
    //std::cout << isfinishedStrike;
    isfinishedStrike=true;
}


/**************************************************
 * SKEET : SHOOT
 * Shoot the Ship with the spacebar
 *************************************************/
void Asteroids::shootBullets(int space)
{
    
    //Should a new bullet Ship be shot out? If so create new ones!
    if(space && (theBullets.size() < 5)){
        //create a new bullet
        canShootAnother = false;
        Bullet newBullet;
        newBullet.setX(ship.getX());
        newBullet.setY(ship.getY());
        //add that bullet to the vector 'theBullets'
        theBullets.push_back(newBullet);
    }
    //now move them all
    
    for (int j = 0; j < theBullets.size(); j++){
        theBullets[j].updateCurrentPoint();
    
    if(theBullets[j].getCurrentPoint().getX() > theBullets[j].getCurrentPoint().getXMax()){
        theBullets[j].kill();
        //std::cout << "RIGHT" << std::endl;
    }
    else if(theBullets[j].getCurrentPoint().getX()< theBullets[j].getCurrentPoint().getXMin()){
        theBullets[j].kill();
        //std::cout << "LEFT" << std::endl;
    }
    else if(theBullets[j].getCurrentPoint().getY()   > theBullets[j].getCurrentPoint().getYMax()){
        theBullets[j].kill();
        //std::cout << "TOP" << std::endl;
    }
    else if(theBullets[j].getCurrentPoint().getY()  < theBullets[j].getCurrentPoint().getYMin()){
        theBullets[j].kill();
         //i--;
        //std::cout << "BOTTOM" << std::endl;
    }
        
    }
}
void Asteroids::killObjects(){
    //kill bullets
    objectsHaveDied = false;
    for (int j = 0; j < theBullets.size(); j++){
    //now loop through and kill all the bullets that need it
        if(!(theBullets[j].isAlive())){
            theBullets[j] = theBullets.back(); theBullets.pop_back();
            //theBullets[j].~Bullet();
            j--;
        }
    }
    //kills Asteroids
    for (int i = 0; i < theAsteroids.size(); i++){
        //now loop through and kill all the bullets that need it
        if(!(theAsteroids[i].isAlive())){
            theAsteroids[i] = theAsteroids.back(); theAsteroids.pop_back();
            //theAsteroids[j].~Asteroids();
            i--;
        }
    }
    //let us know that all the objects have been killed so we can proceed
    objectsHaveDied = true;
}
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
    
    
//    if (reverse>0 ){
//        newDY = .2*(sin((prevAngle-90)*PI/180));
//        newDX = .2*(cos((prevAngle-90)*PI/180));
//        ship.setDX(newDX + prevDX);
//        ship.setDY(newDY + prevDY);
//        
//    }
    
    
    
    if (forward==0){
        forwardIsPressed = false;
    }
    
//    if (reverse==0){
//        reverseIsPressed = false;
//    }
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
            theAsteroids[j].setAngle(theAsteroids[j].getAngle() + theAsteroids[j].getRotation());
            int theAsteroidsSize = theAsteroids[j].getSize();
            if(theAsteroidsSize== 3){
                drawLargeAsteroid( theAsteroids[j].getCurrentPoint(), theAsteroids[j].getAngle());
              //  std::cout << theAsteroidsSize;
            }
            if(theAsteroidsSize== 2){
                drawMediumAsteroid(theAsteroids[j].getCurrentPoint(), theAsteroids[j].getAngle());
            }
            if(theAsteroidsSize== 1){
                drawSmallAsteroid(theAsteroids[j].getCurrentPoint(), theAsteroids[j].getAngle());;
            }
        }
  
    }
    for (int i = 0; i < theBullets.size(); i++){
        if (theBullets[i].isAlive()){
          drawDot(theBullets[i].getCurrentPoint());
        }
    }
    Point shipLifeOne(ship.getCurrentPoint().getXMin() + 10, ship.getCurrentPoint().getYMax() - 10);
    Point shipLifeTwo(ship.getCurrentPoint().getXMin() + 25, ship.getCurrentPoint().getYMax() - 10);
    Point shipLifeThree(ship.getCurrentPoint().getXMin() + 40, ship.getCurrentPoint().getYMax() - 10);
    if (lives ==3){
     drawShip(shipLifeOne, 0);
     drawShip(shipLifeTwo, 0);
     drawShip(shipLifeThree, 0);
    }else if (lives ==2){
            drawShip(shipLifeOne, 0);
            drawShip(shipLifeTwo, 0);
        }else if (lives ==1){
            drawShip(shipLifeOne, 0);
        }
  //  Point scorePointY(ship.getCurrentPoint().getXMin() + 5, ship.getCurrentPoint().getYMax() - 20);
  
   // drawNumber(scorePointY, ship.getY());
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
    
    //pAsteroids->shootBullets(pUI->isSpace());
    //only run if previous loop is finished

    pAsteroids->killObjects();
    
    if (isfinishedStrike){
        isfinishedStrike = false;
        pAsteroids->strike();
        
    }
    // advance the Ship
    if(isfinishedAdvanceAsteroids){
        isfinishedAdvanceAsteroids = false;
         pAsteroids->moveAsteroids();
    }
    
    if(isfinishedAdvance){
        isfinishedAdvance = false;
        pAsteroids->advanceShip();
    }

   // std::cout << isfinishedStrike;
    pAsteroids->moveShip(pUI->isRight(), pUI->isLeft(), pUI->isUp(), pUI->isDown());
 
    pAsteroids->shootBullets(pUI->isSpace());

    //pAsteroids->moveAsteroids();
    pAsteroids->draw();

    ticks++;
    if(ticks > 10) {
        //std::cout << ticks;
        ticks = 0;
        canShootAnother = true;
    }
    
}


/*********************************
 * MAIN
 * initialize the drawing window, initialize
 * the game,and run it!
 *********************************/
int main(int argc, char **argv)
{
    isfinishedStrike = true;
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
