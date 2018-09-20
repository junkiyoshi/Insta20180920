#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);

	ofSetDepthTest(true);

	for (int i = 0; i < this->number_of_target; i++) {

		ofPoint noise_seed = ofPoint(ofRandom(10), ofRandom(10), ofRandom(10));
		this->noise_seeds.push_back(noise_seed);

		deque<ofPoint> log;
		this->logs.push_back(log);
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int i = 0; i < this->number_of_target; i++) {

		ofPoint point(ofMap(ofNoise(this->noise_seeds[i].x), 0, 1, -100, 100), ofMap(ofNoise(this->noise_seeds[i].y), 0, 1, -100, 100), ofMap(ofNoise(this->noise_seeds[i].z), 0, 1, -100, 100));
		this->logs[i].push_front(point);
		while (this->logs[i].size() > 30) { this->logs[i].pop_back(); }

		this->noise_seeds[i].x += ofNoise(ofRandom(10), ofGetFrameNum() * 0.005) * 0.05;
		this->noise_seeds[i].y += ofNoise(ofRandom(10), ofGetFrameNum() * 0.005) * 0.05;
		this->noise_seeds[i].z += ofNoise(ofRandom(10), ofGetFrameNum() * 0.005) * 0.05;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->number_of_target; i++) {


		ofPushMatrix();
		int layer = i / 16;
		int x = (i - layer * 16) % 4 * 200 - ofGetWidth() * 0.5 + 50;
		int y = (i - layer * 16) / 4 * 200 - ofGetHeight() * 0.5 + 50;
		int z = layer * 300 - 300;
		ofTranslate(x, y, z);

		ofNoFill();
		ofBeginShape();
		for (int l = 0; l < this->logs[i].size(); l++) {

			ofVertex(this->logs[i][l]);
		}
		ofEndShape();

		ofFill();
		ofDrawSphere(this->logs[i][0], 5);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}