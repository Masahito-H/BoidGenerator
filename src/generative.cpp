/*
 * generating boids
 * generative.cpp
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

#include "generative.h"

generative::generative(){
    ofSetVerticalSync(true);
    ofBackground(50);
    flock = Flock();
    for(int i = 0; i < 800; i++){
        flock.addBoid(Boid(ofGetWidth() / 2.0, ofGetHeight() / 2.0));
    }
    
    gui.setup();
    gui.add(separateForce.setup("separation force", 22.5, 0, 50));
    gui.add(alignForce.setup("alignment force", 16.5, 0, 50));
    gui.add(cohesionForce.setup("cohesion force", 23, 0, 50));
    gui.add(separateRadious.setup("separation radius", 127.5, 0, 300));
    gui.add(alignRadious.setup("alignment radius", 61.5, 0, 300));
    gui.add(cohesionRadious.setup("cohesion radius", 81, 0, 300));
    gui.add(maxSpeed.setup("max speed", 20, 0, 20));
    gui.add(regionRadious.setup("region radius", 62.5, 0, 500));
}
//
void generative::updating(){
    flock.update();
    
    flock.run(separateForce, alignForce, cohesionForce,
              separateRadious, alignRadious, cohesionRadious, maxSpeed, regionRadious);
}

void generative::drawing(){
    flock.render();
    
    gui.draw();
}

void generative::mouseAction(int x, int y){
    flock.mouseAction(x, y);
}

void generative::keyAction(int key){
    flock.keyAction(key);
}
