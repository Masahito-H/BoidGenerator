/*
 * generating boids
 * boid.cpp
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

#include "boid.h"

ofVec2f Boid::regionCoordinate;
bool Boid::regionControl;
bool Boid::regionFlag;

Boid::Boid(float x, float y){
    acceleration = ofVec2f(0, 0);
    float angle = ofRandom(TWO_PI);
    velocity = ofVec2f(cos(angle), sin(angle));
    location = ofVec2f(x, y);
    r = 3.0;
    maxForce = 0.03;
    
    regionCoordinate = ofVec2f(0, 0);
}

void Boid::run(vector<Boid> boids, float separateForce, float alignForce, float cohesionForce,
                                   float separateRadious, float alignRadious, float cohesionRadious, float maxSpeed, float regionRadious){
    this->separateForce = separateForce;
    this->alignForce = alignForce;
    this->cohesionForce = cohesionForce;
    this->separateRadious = separateRadious;
    this->alignRadious = alignRadious;
    this->cohesionRadious = cohesionRadious;
    this->maxSpeed = maxSpeed;
    this -> regionRadious = regionRadious;
    flock(boids);
    update();
    borders();
}

void Boid::applyForce(ofVec2f force){
    acceleration += force;
}

void Boid::flock(vector<Boid> boids){
    ofVec2f sep = separate(boids);
    
    ///*
    if(Boid::regionControl && Boid::regionFlag){
        sep = region2(sep/*, boids*/);
    }
    //*/
    
    ofVec2f ali = align(boids);
    ofVec2f coh = cohesion(boids);
    
    /*
    if(Boid::Control && Boid::Region){
        coh = region(coh, boids);
    }
    */
    
    sep = sep * separateForce;
    ali = ali * alignForce;
    coh = coh * cohesionForce;
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
}

void Boid::update(){
    velocity += acceleration;
    velocity.limit(maxSpeed);
    location += velocity;
    acceleration *= 0;
}

ofVec2f Boid::seek(ofVec2f target){
    ofVec2f desired = target - location;
    desired.normalize();
    desired *= maxSpeed;
    ofVec2f steer = desired - velocity;
    steer.limit(maxForce);
    return steer;
}

void Boid::render(){
    ofVec2f origin = ofVec2f(1.0, 0.0);
    float theta = origin.angle(velocity) + 90;
    ofSetColor(200, 200);
    
    /*
    ofPushMatrix();
    ofTranslate(location.x, location.y);
    ofRotateDeg(theta);
    ofBeginShape();
    ofVertex(0, -r * 2);
    ofVertex(-r, r * 2);
    ofVertex(r, r * 2);
    ofEndShape();
    ofPopMatrix();
    */
    
    ofDrawCircle(location.x, location.y, 1);
}

void Boid::borders(){
    if(location.x < -r) location.x = ofGetWidth() + r;
    if(location.y < -r) location.y = ofGetHeight() + r;
    if(location.x > ofGetWidth() + r) location.x = -r;
    if(location.y > ofGetHeight() + r) location.y = -r;
}

ofVec2f Boid::separate(vector<Boid> boids){
    float desiredSeparation = separateRadious;
    ofVec2f steer = ofVec2f(0, 0);
    int count = 0;
    for(int i = 0; i < boids.size(); i++){
        Boid other = boids[i];
        float d = location.distance(other.location);
        if((d > 0) && (d < desiredSeparation)){
            ofVec2f diff = location - other.location;
            diff.normalize();
            diff /= d;
            steer += diff;
            count++;
        }
    }
    if(count > 0){
        steer /= (float(count));
    }
    
    if(steer.length() > 0){
        steer.normalize();
        steer *= maxSpeed;
        steer -= velocity;
        steer.limit(maxForce);
    }
    return steer;
    
}

ofVec2f Boid::align(vector<Boid> boids){
    float neighbordist = alignRadious;
    ofVec2f sum = ofVec2f(0, 0);
    int count = 0;
    for(int i = 0; i < boids.size(); i++){
        Boid other = boids[i];
        float d = location.distance(other.location);
        if((d > 0) && (d < neighbordist)){
            sum += other.velocity;
            count++;
        }
    }
    if(count > 0){
        sum /= (float(count));
        sum.normalize();
        sum *= maxSpeed;
        ofVec2f steer = sum - velocity;
        steer.limit(maxForce);
        return steer;
    } else {
        return ofVec2f(0, 0);
    }
}

ofVec2f Boid::cohesion(vector<Boid> boids){
    float neighbordist = cohesionRadious;
    ofVec2f sum = ofVec2f(0, 0);
    int count = 0;
    
    for(int i = 0; i < boids.size(); i++){
        Boid other = boids[i];
        float d = location.distance(other.location);
        if((d > 0) && (d < neighbordist)){
            sum += other.location;
            count++;
        }
    }
    if(count > 0){
        sum /= (float(count));
        
        if(Boid::regionControl && !Boid::regionFlag){
            sum = regionCoordinate;
        }
        
        return seek(sum);
    } else {
        return ofVec2f(0, 0);
    }
}



ofVec2f Boid::getLocation(){
    return location;
}



void Boid::setRegionControl(bool b){
    if(Boid::regionControl != b){
        Boid::regionControl = b;
    }
}

bool Boid::getRegionControl(){
    return Boid::regionControl;
}

void Boid::setRegionCoordinate(int x, int y){
    regionCoordinate.set(x, y);
}

ofVec2f Boid::getRegionCoordinate(){
    return regionCoordinate;
}

void Boid::setRegionFlag(bool b){
    if(Boid::regionFlag != b){
        Boid::regionFlag = b;
    }
}

bool Boid::getRegionFlag(){
    return Boid::regionFlag;
}



//costomize
ofVec2f Boid::region(ofVec2f vec/*, vector<Boid> boids*/){
    float neighbordist = regionRadious;
    ofVec2f induct = ofVec2f(0, 0);
    float d = regionCoordinate.distance(location);
    
    if((d > 0) && (d < neighbordist)){
        induct = regionCoordinate;
        return seek(induct);
    }
    else{
        return vec;
    }
}

ofVec2f Boid::region2(ofVec2f vec/*, vector<Boid> boids */){
    float neighbordist = regionRadious;
    ofVec2f induct = ofVec2f(0, 0);
    float d = regionCoordinate.distance(location);
    
    if((d > 0) && (d < neighbordist)){
        induct = location - regionCoordinate;
        induct.normalize();
        induct /= d;
        
        if(induct.length() > 0){
            induct.normalize();
            induct *= maxSpeed;
            induct -= velocity;
            induct.limit(maxForce);
        }
        return induct;
    }
    else{
        return vec;
    }
    
}


