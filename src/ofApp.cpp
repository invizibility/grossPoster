#include "ofApp.h"

using namespace ofxCv;




//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(1);
    setupColors();
    setupFont();
    setupTitle();
    setupSun();
    
    //shader.load("shaders/blend");
    testim.load("testPosterElement2.png");
    testmask.load("testtex.jpg");
    foreMasker.setup(ofGetWidth(), ofGetHeight());
    backMasker.setup(ofGetWidth(), ofGetHeight());
    groundMasker.setup(ofGetWidth(), ofGetHeight());
    
    //layer1 = masker.newLayer();
    //layer2 = masker.newLayer();
    
    //ofDisableDepthTest();
    
    ofDirectory texDir("textures");
    ofDirectory foreDir("shapes/foreground");
    ofDirectory backDir("shapes/background");
    ofDirectory groundDir("shapes/terrain");
    
    texDir.listDir();
    foreDir.listDir();
    backDir.listDir();
    groundDir.listDir();
    
    //int size = texDir.size();
    
    //cout << size;
    
    //TEXTURE POPULATION
    for (int i= 0; i<texDir.size(); i++)
    {
        vector<ofImage> temp;
        if (texDir.getFile(i).isDirectory()==1)
        {
            //cout << texDir.getFile(i).getAbsolutePath();
            ofDirectory inner(texDir.getFile(i).getAbsolutePath());
            inner.listDir();
            for(int k =0; k<inner.size();k++)
            {
                temp.push_back(ofImage(inner.getFile(k).getAbsolutePath()));
                cout << inner.getFile(k).getAbsolutePath() << "\n";
            }
            textures.push_back(temp);
        }
    }
    textureMainIndex = (int)ofRandom(textures.size());
    
    //FOREGROUND POPULATION
    for (int i= 0; i<foreDir.size(); i++)
    {
        vector<ofImage> temp;
        if (foreDir.getFile(i).isDirectory()==1)
        {
            //cout << texDir.getFile(i).getAbsolutePath();
            ofDirectory inner(foreDir.getFile(i).getAbsolutePath());
            inner.listDir();
            for(int k =0; k<inner.size();k++)
            {
                temp.push_back(ofImage(inner.getFile(k).getAbsolutePath()));
                cout << inner.getFile(k).getAbsolutePath() << "\n";
            }
            foreMasks.push_back(temp);
        }
    }
    foreObjects = (int)ofRandom(5, 10);
    for (int i=0;i<foreObjects;i++)
    {
        foreXVal.push_back((int)ofRandom(margin*1.5,ofGetWidth()-margin*3.5));
        foreYVal.push_back((int)ofRandom((ofGetWidth()+margin)/2,ofGetWidth()-4.7*margin));
        i = foreMasker.newLayer();
    }
    textureForeIndex = (int)ofRandom(textures[textureMainIndex].size());
    foreCatIndex = (int)ofRandom(foreMasks.size());
    foreTypeIndex = (int)ofRandom(foreMasks[foreCatIndex].size());
    
    
    
    //BACKGROUND POPULATION
    for (int i= 0; i<backDir.size(); i++)
    {
        vector<ofImage> temp;
        if (backDir.getFile(i).isDirectory()==1)
        {
            //cout << texDir.getFile(i).getAbsolutePath();
            ofDirectory inner(backDir.getFile(i).getAbsolutePath());
            inner.listDir();
            for(int k =0; k<inner.size();k++)
            {
                temp.push_back(ofImage(inner.getFile(k).getAbsolutePath()));
                cout << inner.getFile(k).getAbsolutePath() << "\n";
            }
            backMasks.push_back(temp);
        }
    }
    backObjects = (int)ofRandom(2, 4);
    for (int i=0;i<foreObjects;i++)
    {
        backXVal.push_back((int)ofRandom(margin*1.5,ofGetWidth()-margin*7));
        backYVal.push_back(ofGetWidth() * 3 /8
                           //(int)ofRandom(0,10)
                           );
        i = backMasker.newLayer();
    }
    textureBackIndex = (int)ofRandom(textures[textureMainIndex].size());
    backCatIndex = (int)ofRandom(backMasks.size());
    backTypeIndex = (int)ofRandom(backMasks[backCatIndex].size());
    
    
    //cout << textures.size();
    
    
    //TERRAIN POPULATION
    for (int i= 0; i<groundDir.size(); i++)
    {
        grounds.push_back(ofImage(groundDir.getFile(i).getAbsolutePath()));

    }
    groundMasker.newLayer();
    groundIndex = (int)ofRandom(grounds.size());
    textureGroundIndex = (int)ofRandom(textures[textureMainIndex].size());
    
    
    //DRAW TERRAIN
    groundMasker.beginMask();
    grounds[groundIndex].draw(margin, ofGetWidth() / 8, ofGetWidth()-2*margin, ofGetWidth() * 7 / 8);
    groundMasker.endMask();
    
    groundMasker.beginLayer();
    textures[textureMainIndex][textureGroundIndex].draw(margin, ofGetWidth() / 8, ofGetWidth()-2*margin, ofGetWidth() * 7 / 8);
    groundMasker.endLayer();
    
    //DRAW FOREGROUND
    for(int i =0;i<foreObjects;i++)
    {
        foreMasker.beginMask(i);
        foreMasks[foreCatIndex][foreTypeIndex].draw(foreXVal[i], foreYVal[i], ofGetWidth() / 4, ofGetWidth() / 4);
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofSetColor(ofColor::fromHex(palette[3]), 100);
        ofDrawRectangle(foreXVal[i], foreYVal[i], ofGetWidth() / 4, ofGetWidth() / 4);
        ofDisableBlendMode();
        foreMasker.endMask(i);
        
        foreMasker.beginLayer(i);
        textures[textureMainIndex][textureForeIndex].draw(foreXVal[i], foreYVal[i], ofGetWidth() / 4, ofGetWidth() / 4);
        foreMasker.endLayer(i);
    }
    
    //DRAW BACKGROUND
    for(int i =0;i<backObjects;i++)
    {
        backMasker.beginMask(i);
        backMasks[backCatIndex][backTypeIndex].draw(backXVal[i], backYVal[i], ofGetWidth() * 3 / 8, ofGetWidth() * 3 / 8);
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofSetColor(ofColor::fromHex(palette[1]), 100);
        ofDrawRectangle(backXVal[i], backYVal[i], ofGetWidth() * 3 / 8, ofGetWidth() * 3 / 8);
        ofDisableBlendMode();
        backMasker.endMask(i);
        
        backMasker.beginLayer(i);
        textures[textureMainIndex][textureBackIndex].draw(backXVal[i], backYVal[i], ofGetWidth() * 3 / 8, ofGetWidth() * 3 / 8);
        backMasker.endLayer(i);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawTitle();
    drawScene();

    //masker.draw();
    backMasker.draw();
    groundMasker.draw();
    foreMasker.draw();
    
    //textures[0][0].draw(0,0);
    
    drawGuards();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') {
        groundMasker.toggleOverlay();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::drawTitle() {
    ofSetColor(titleColor);
    titleFont.drawString(title, titleX, titleY);
}

void ofApp::setupFont() {
    ofTrueTypeFont::setGlobalDpi(72);
    
    ofDirectory fontDir;
    // only allow fonts
    fontDir.allowExt("otf");
    fontDir.allowExt("ttf");
    // now list em
    fontDir.listDir("fonts");
    if( fontDir.size() ){
        int randomized = (int)ofRandom(fontDir.size());
        titleFont.load(fontDir.getPath(randomized), ofGetHeight() / 12);
    }
}

void ofApp::drawSun() {
    ofSetColor(ofColor::fromHex(palette[4]));
    ofDrawCircle(sunX, sunY, sunRad);
}

void ofApp::setupSun() {
    int minRad = dpi / 2;
    int maxRad = dpi * 2;
    sunRad = ofRandom(minRad, maxRad);
    
    int minX = sceneX + margin + sunRad;
    int maxX = sceneX + sceneWidth - margin - sunRad;
    sunX = ofRandom(minX, maxX);
    
    int minY = sceneY + sunRad;
    int maxY = sceneY + sceneHeight - sunRad;
    sunY = ofRandom(minY, maxY);
}

string ofApp::generateTitle() {
    string title = "PUBESBURGH";
    ofBuffer buffer = ofBufferFromFile("titles.txt");
    vector <string> titles;
    
    if(buffer.size()) {
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
            string line = *it;
            // copy the line to draw later
            // make sure its not a empty line
            if(line.empty() == false) {
                titles.push_back(line);
            }
        }
    }
    
    bool prefixed = (int)ofRandom(2);
    vector <string> suffix = ofSplitString(titles[1], " ");
    vector <string> prefix = ofSplitString(titles[0], " ");
    vector <string> word = ofSplitString(titles[2], " ");
    
    if (prefixed) {
        title = prefix[(int)ofRandom(prefix.size())] + " " + word[(int)ofRandom(word.size())];
    } else {
        title = word[(int)ofRandom(word.size())] + " " + suffix[(int)ofRandom(suffix.size())];
    }
    return title;
}

void ofApp::setupTitle() {
    title = generateTitle();
    
    // get the width
    ofRectangle bounded = titleFont.getStringBoundingBox(title, 0,0);
    int titleWidth = bounded.width;
    
    // calculate where to start leftwise
    titleX = (ofGetWidth() - titleWidth) / 2;
    titleY = ofGetHeight() * 3 / 4;
}

void ofApp::drawScene() {
    ofSetColor(ofColor::fromHex(palette[1]));
    ofDrawRectangle( margin, margin, ofGetWidth() - (margin * 2), ofGetWidth() - (margin * 2));
    
    drawSun();
}

void ofApp::setupColors() {
    // determine whether bg is dark or light
    colorScheme = (int)ofRandom(2);
    
    ofBuffer buffer = ofBufferFromFile("palettes.txt");
    vector <string> palettes;
    
    if(buffer.size()) {
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
            string line = *it;
            // copy the line to draw later
            // make sure its not a empty line
            if(line.empty() == false) {
                palettes.push_back(line);
            }
        }
    }
    
    int randomized = (int)ofRandom(palettes.size());
    vector <string> strPalette = ofSplitString(palettes[randomized], " ");
    
    // convert to actual palette
    for (int i = 0; i < strPalette.size(); i++) {
        palette.push_back(ofHexToInt(strPalette[i]));
    }
    
    // set background color based on this shit
    if (colorScheme) {
        ofSetBackgroundColorHex(palette[0]);
        titleColor = ofColor::fromHex(palette[4]);
    } else {
        ofSetBackgroundColorHex(palette[4]);
        titleColor = ofColor::fromHex(palette[0]);
    }
}

void ofApp::drawGuards() {
    if (colorScheme) {
        ofSetColor(ofColor::fromHex(palette[0]));
    } else {
        ofSetColor(ofColor::fromHex(palette[4]));
    }
    
    ofDrawRectangle(0, 0, sceneX, sceneY + sceneHeight);
    ofDrawRectangle(sceneX + sceneWidth, 0, sceneX, sceneY + sceneHeight);
}
