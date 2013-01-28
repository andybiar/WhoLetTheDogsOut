#include "testApp.h"

bool locked = false;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(30);
    loadCameras();
    
    // initialize connection
    for(int i = 0; i < NUM_CAMERAS; i++) {
        IPCameraDef& cam = getNextCamera();
        
        ofxSharedIpVideoGrabber c( new ofxIpVideoGrabber());
        
        c->setCameraName(cam.name);
        c->setURI(cam.url);
        c->connect(); // connect immediately

        // if desired, set up a video resize listener
        ofAddListener(c->videoResized, this, &testApp::videoResized);
        
        ipGrabber.push_back(c);

		music.loadSound("dogs.mp3");
    }
}

//--------------------------------------------------------------
IPCameraDef& testApp::getNextCamera() {
    nextCamera = (nextCamera + 1) % ipcams.size();
    return ipcams[nextCamera];
}


//--------------------------------------------------------------
void testApp::loadCameras() {

	ofLog(OF_LOG_NOTICE, "---------------Loading Streams---------------");

	ofxXmlSettings XML;
    
	if( XML.loadFile("streams.xml") ){

        XML.pushTag("streams");
		string tag = "stream";
		
		int nCams = XML.getNumTags(tag);
		
		for(int n = 0; n < nCams; n++) {
            
            IPCameraDef def;

			def.name = XML.getAttribute(tag, "name", "", n);
			def.url = XML.getAttribute(tag, "url", "", n);
			def.username = XML.getAttribute(tag, "username", "", n);
			def.password = XML.getAttribute(tag, "password", "", n);
			
			string logMessage = "STREAM LOADED: " + def.name +
			" url: " +  def.url +
			" username: " + def.username +
			" password: " + def.password;
            
            ofLog(OF_LOG_NOTICE, logMessage);
            
            ipcams.push_back(def);
            
		}
		
		XML.popTag();
		
	} else {
		ofLog(OF_LOG_ERROR, "Unable to load streams.xml.");
	}
	ofLog(OF_LOG_NOTICE, "-----------Loading Streams Complete----------");
    
    
    nextCamera = ipcams.size();
}


//--------------------------------------------------------------
void testApp::videoResized(const void * sender, ofResizeEventArgs& arg) {
    // find the camera that sent the resize event changed
    for(int i = 0; i < NUM_CAMERAS; i++) {
        if(sender == &ipGrabber[i]) {
            stringstream ss;
            ss << "videoResized: ";
            ss << "Camera connected to: " << ipGrabber[i]->getURI() + " ";
            ss << "New DIM = " << arg.width << "/" << arg.height;
            ofLogVerbose("testApp") << ss.str();
        }
    }
}


//--------------------------------------------------------------
void testApp::update(){
    // update the cameras
    for(size_t i = 0; i < ipGrabber.size(); i++) {
        ipGrabber[i]->update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);

	ofSetHexColor(0xffffff);
    
    int row = 0;
    int col = 0;
    
    int x = 0;
    int y = 0;
    
    int w = ofGetWidth() / NUM_COLS;
    int h = ofGetHeight() / NUM_ROWS;
    
    float totalKbps = 0;
    float totalFPS = 0;
    
    for(size_t i = 0; i < ipGrabber.size(); i++) {
        x = col * w;
        y = row * h;

        // draw in a grid
        row = (row + 1) % NUM_ROWS;
        if(row == 0) {
            col = (col + 1) % NUM_COLS;
        }

        
        ofPushMatrix();
        ofTranslate(x,y);
        ofSetColor(255,255,255,255);
        ipGrabber[i]->draw(0,0,w,h); // draw the camera
        
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (music.getIsPlaying()) music.stop();
	else music.play();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
