#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage testim,testmask, drawresult;
    cv::Mat matIm, matMask, testresult;
    
    //ofShader shader;
    
    ofxLayerMask foreMasker,backMasker,groundMasker;
    
    
    vector<vector<ofImage>> textures,foreMasks,backMasks;
    
    vector<ofImage> grounds;
    
    vector<int> foreXVal;
    vector<int> foreYVal;
    
    vector<int> backXVal;
    vector<int> backYVal;
    int foreObjects, backObjects;
    int groundIndex;
    int textureMainIndex,textureForeIndex,textureBackIndex,textureGroundIndex;
    
    int foreCatIndex, foreTypeIndex, backCatIndex, backTypeIndex;
    
    // printing info
    int dpi = 50;
    int margin = dpi / 2;
    
    // title
    string generateTitle();
    string title;
    int titleX;
    int titleY;
    ofTrueTypeFont titleFont;
    ofColor titleColor;
    
    // color
    bool colorScheme;
    vector <int> palette;
    void setupColors();
    void setupFont();
    void setupTitle();
    void drawTitle();
    
    // scenery
    void drawScene();
    int sceneWidth = ofGetWidth() - (margin * 2);
    int sceneHeight = sceneWidth;
    int sceneX = margin;
    int sceneY = sceneX;
    
    // sun
    int sunX;
    int sunY;
    int sunRad;
    void setupSun();
    void drawSun();
    
    //side guards
    void drawGuards();
};
