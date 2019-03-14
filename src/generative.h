/*
 * generating boids
 * generative.h
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

#ifndef generative_h
#define generative_h

#include "ofMain.h"
#include "boid.h"
#include "flock.h"
#include "ofxGui.h"

class generative{
private:
    Flock flock;
    
    ofxPanel gui;
    ofxFloatSlider separateForce;
    ofxFloatSlider alignForce;
    ofxFloatSlider cohesionForce;
    ofxFloatSlider separateRadious;
    ofxFloatSlider alignRadious;
    ofxFloatSlider cohesionRadious;
    ofxFloatSlider maxSpeed;
    ofxFloatSlider regionRadious;
    
public:
    generative();
    
    void updating();
    void drawing();
    void mouseAction(int x, int y);
    void keyAction(int key);
};

#endif /* generative_h */
