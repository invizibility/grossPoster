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
    
    int foreCatIndex, forTypeIndex, backCatIndex, backTypeIndex;
    
		
};
