/*
 * generating boids
 * flock.cpp
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

#include "flock.h"

Flock::Flock(){
    boids = vector<Boid>();
    
    regionCoordinate.set(0, 0);
    
    triPoints = vector<int>{15 * 30, 20 * 30, 25 * 30};
    triId = triPoints.size();
    triFrame = 0;
    triOffset = false;
    
    regionRandom = false;
    regionVisible = false;
    holding = false;
    regionCenter = false;
    triFlag = false;
}

void Flock::update(){
    if(regionRandom && !holding){
        if(((int)ofGetFrameNum()) % ((int)ofGetFrameRate() * 5) == 0){
            regionCoordinate.set(ofGetWidth() / 6 + ofRandomWidth() * 2 / 3, ofGetWidth() / 6 + ofRandomHeight() * 2 / 3);
            Boid::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
        }
    }
    else if(regionCenter){
        regionCoordinate.set(ofGetWidth() / 2, ofGetHeight() / 2);
        Boid::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
    }
    else if(triFlag){
        if((triFrame % triPoints[triId] == 0) && (triId < triPoints.size() - 1)){
            regionCoordinate.set(ofGetWidth() / 6 + ofRandomWidth() * 2 / 3, ofGetWidth() / 6 + ofRandomHeight() * 2 / 3);
            Boid::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
            
            if(triOffset){
                triOffset = false;
            }
            else{
                triId++;
            }
            
            triFrame = 0;
        }
        else if((triId >= triPoints.size() - 1) && !csv.check()){
            triFlag = false;
        }
        
        triFrame++;
    }
}

void Flock::run(float separateForce, float alignForce, float cohesionForce,
                float separateRadious, float alignRadious, float cohesionRadious, float maxSpeed, float regionRadious){
    vector<Boid> past;
    copy(boids.begin(), boids.end(), back_inserter(past));
    
    for(int i = 0; i < boids.size(); i++){
        boids[i].run(past, separateForce, alignForce, cohesionForce, separateRadious, alignRadious, cohesionRadious, maxSpeed, regionRadious);
        
        ofVec2f vec = boids[i].getLocation();
        if(csv.check()){
            csv.write("agent", i, vec.x, vec.y, csv.getFrame());
        }
    }
    
    if(csv.check()){
        ofVec2f co = Boid::getRegionCoordinate();
        csv.write("region", -1, co.x, co.y, csv.getFrame());
    }
    
    csv.brunch();
}

void Flock::render(){
    if(regionVisible){
        ofSetColor(0, 255, 0);
        ofFill();
        ofDrawCircle(regionCoordinate.x, regionCoordinate.y, 5);
        ofSetColor(255);
    }
    
    for(int i = 0; i < boids.size(); i++){
        boids[i].render();
    }
}

void Flock::addBoid(Boid b){
    boids.push_back(b);
}

/*
void Flock::setRandom(bool b){
    randomMode = b;
    
    if(!randomMode){
        visibleMode = false;
    }
}

void Flock::setVisible(bool b){
    if(randomMode){
        visibleMode = b;
    }
}
 */

void Flock::mouseAction(int x, int y){
    /*
    Boid::setControl(true);
    randomMode = false;
    visibleMode = false;
    
    for(int i = 0; i < boids.size(); i++){
        boids[i].setCo(x, y);
    }
     */
}

void Flock::keyAction(int key){
    if(key == ' '){ //csv export.
        saveStart();
    }
    
    if(key == OF_KEY_TAB){ //all reset.
        Boid::setRegionControl(false);
        regionRandom = false;
        regionVisible = false;
        holding = false;
        regionCenter = false;
    }
    else if(key == 'g'){ //random mode.
        regionRandom = !regionRandom;
        Boid::setRegionControl(regionRandom);
        Boid::setRegionFlag(regionRandom);
        
        if(regionRandom){
            regionCenter = false;
            regionVisible = true;
        }
        else{
            regionVisible = false;
            holding = false;
        }
    }
    
    if(key == OF_KEY_SHIFT){
        if(regionRandom || regionCenter || triFlag){
            regionVisible = !regionVisible;
        }
    }
    
    if(regionRandom){ //manual trigger setting.
        if(key == 'h'){
            holding = !holding;
        }
        else if(key == 'f'){
            if(holding){
                regionCoordinate.set(ofGetWidth() / 6 + ofRandomWidth() * 2 / 3, ofGetHeight() / 6 + ofRandomHeight() * 2 / 3);
                Boid::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
            }
        }
    }
    
    if(Boid::getRegionControl()){ //another mode.
        if(key == 'r'){
            Boid::setRegionFlag(!Boid::getRegionFlag());
        }
        
        if(key == 'c'){
            regionCenter = !regionCenter;
            regionRandom = regionCenter ? false : true;
        }
    }
}



void Flock::saveStart(){
    regionRandom = false;
    holding = false;
    regionCenter = false;
    triFlag = true;
    
    std::random_shuffle(triPoints.begin(), triPoints.end());
    std::random_shuffle(triPoints.begin(), triPoints.end());
    triId = 0;
    triFrame = 0;
    triOffset = true;
    
    csv.writeStart(1800);
}
