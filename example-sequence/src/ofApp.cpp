#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	param = "initial";
	value = 10;

	sequence = new Serial({
		new Log("Click to start"),
		new Listen<void>(onClick),

		new Log("Start and wait 0.5 second"),
		new Wait(0.5),

		new Log("Update param"),
		new Var<string>(param, "changed"),

		new Parallel({

			new Serial({
				new Wait(3),
				new Log("Eager elaluation : param = " + param),
				new Log("Serial in parallel is completed"),
			}),

			new Function([&] {
				ofLog() << "Lazy elaluation : param = " << param;
				sequence->insert({
					new Log("Wait command is inserted"),
					new Wait(1),
					new Log("Wait command is completed"),
				});
			})
		}),

		new Wait(0.5),

		new Log("Start tween from current value"),
		(new Tween(1, Quart::Out))->animate(value, 100)->onStart([&] {
			ofLog() << "Tween onStart : value = " << value;
		})->onStop([&] {
			ofLog() << "Tween onStop : value = " << value;
		})->onUpdate([&] {
			ofLog() << "Tween onUpdate : value = " << value;
		})->onComplete([&] {
			ofLog() << "Tween onComplete : value = " << value;
		}),

		new Wait(0.5),

		new Log("Start tween from current specified value"),
		(new Tween(1, Expo::In))->animate(value, 50, 100)->onStart([&] {
			ofLog() << "Tween onStart : value = " << value;
		})->onStop([&] {
			ofLog() << "Tween onStop : value = " << value;
		})->onUpdate([&] {
			ofLog() << "Tween onUpdate : value = " << value;
		})->onComplete([&] {
			ofLog() << "Tween onComplete : value = " << value;
		}),

		new Log("Sequence is completed"),
	});

	sequence->execute();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawBitmapString("Click to start commands, see output window.", 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	ofNotifyEvent(onClick);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}



