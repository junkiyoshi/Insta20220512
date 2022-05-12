#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	//ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	// 配色デザイン ビビッドブルー P144
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(18, 85, 163));
	color_palette.push_back(ofColor(0, 165, 231));
	color_palette.push_back(ofColor(93, 177, 186));
	color_palette.push_back(ofColor(44, 121, 191));
	color_palette.push_back(ofColor(136, 185, 79));
	color_palette.push_back(ofColor(246, 221, 80));
	color_palette.push_back(ofColor(200, 59, 57));
	color_palette.push_back(ofColor(255, 255, 255)); 

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 400; i++) {

		if (i % 200 == 0) {

			noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		}

		auto x = ofMap(ofNoise(noise_seed.x, i * 0.01 + ofGetFrameNum() * 0.0015), 0, 1, -300, 300);
		auto y = ofMap(ofNoise(noise_seed.y, i * 0.01 + ofGetFrameNum() * 0.0015), 0, 1, -300, 300);

		ofPushMatrix();
		ofTranslate(x + ofRandom(-15, 15), y + ofRandom(-15, 15));
		ofRotate(ofRandom(360));

		ofMesh mesh;
		mesh.addVertex(glm::vec3());
		mesh.addColor(color_palette[ofRandom(0, 7)]);

		int radius = ofRandom(10, 30);
		for (int k = 0; k < 5; k++) {

			auto deg = k * 72;

			mesh.addVertex(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
			mesh.addVertex(glm::vec3(radius * 0.5 * cos((deg - 36) * DEG_TO_RAD), radius * 0.5 * sin((deg - 36) * DEG_TO_RAD), 0));
			mesh.addVertex(glm::vec3(radius * 0.5 * cos((deg + 36) * DEG_TO_RAD), radius * 0.5 * sin((deg + 36) * DEG_TO_RAD), 0));

			mesh.addIndex(0); mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3);
			mesh.addIndex(0); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);

			mesh.addColor(0);
			mesh.addColor(0);
			mesh.addColor(0);
		}

		mesh.draw();

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}