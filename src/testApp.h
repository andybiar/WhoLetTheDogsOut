#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxIpVideoGrabber.h"

#define NUM_CAMERAS 2
#define NUM_ROWS 1
#define NUM_COLS 2
#define WIDTH (NUM_COLS * 640)
#define HEIGHT (NUM_ROWS * 480)

class IPCameraDef {
public:
    IPCameraDef() {
    };
    IPCameraDef(string _uri) {
        url = _uri;
    }
    
    IPCameraDef(string _name, string _uri, string _username, string _password) {
        name = _name;
        url = _uri;
        username = _username;
        password = _password;
    }
    
    string name;
    string url;
    string username;
    string password;
};

class testApp : public ofBaseApp{

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		

    vector< ofxSharedIpVideoGrabber > ipGrabber;

    void loadCameras();
    IPCameraDef& getNextCamera();
    vector<IPCameraDef> ipcams; // a list of IPCameras
    int nextCamera;

    // This message occurs when the incoming video stream image size changes. 
    // This can happen if the IPCamera has a single broadcast state (some cheaper IPCams do this)
    // and that broadcast size is changed by another user. 
    void videoResized(const void * sender, ofResizeEventArgs& arg);
    
	ofSoundPlayer music;
};