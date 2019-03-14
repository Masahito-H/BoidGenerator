/*
 * generating boids
 * boid.h
 *
 * Created by aa_debdeb on 2015/11/12.
 * Remodeled by Masahito H.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Masahito H.
 * Copyright (c) 2015 aa_debdeb
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __boids__boid__
#define __boids__boid__

#include <stdio.h>
#include "ofMain.h"

class Boid {
public:
    Boid(float x, float y);
    void run(vector<Boid> boids, float separateForce, float alignForce, float cohesionForce,
                                 float separateRadious, float alignRadious, float cohesionRadious, float maxSpeed, float regionRadious);
    void render();
    
    ofVec2f getLocation();
    
    static void setRegionControl(bool b);
    static bool getRegionControl();
    static void setRegionCoordinate(int x, int y);
    static ofVec2f getRegionCoordinate();
    static void setRegionFlag(bool b);
    static bool getRegionFlag();
    ofVec2f region(ofVec2f vec/*, vector<Boid> boids*/);
    ofVec2f region2(ofVec2f vec/*, vector<Boid> boids*/);
    
private:
    void applyForce(ofVec2f force);
    void flock(vector<Boid> boids);
    void borders();
    void update();
    ofVec2f seek(ofVec2f target);
    ofVec2f separate(vector<Boid> boids);
    ofVec2f align(vector<Boid> boids);
    ofVec2f cohesion(vector<Boid> boids);
    
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    float r;
    float maxForce;
    float maxSpeed;
    
    float separateForce;
    float alignForce;
    float cohesionForce;
    float separateRadious;
    float alignRadious;
    float cohesionRadious;
    float regionRadious;
    
    static ofVec2f regionCoordinate;
    static bool regionControl;
    static bool regionFlag;

};

#endif /* defined(__boids__boid__) */
