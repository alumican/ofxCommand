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
		(new Tween(1, Quart::Out))->animate(value, 100)
			->atStart([&](Tween& tween) {
				ofLog() << "Tween atStart : time = " << tween.getTimeRatio() << ", value = " << tween.getValueRatio();
			})->atStop([&](Tween& tween) {
				ofLog() << "Tween atStop : time = " << tween.getTimeRatio() << ", value = " << tween.getValueRatio();
			})->atUpdate([&](Tween& tween) {
				ofLog() << "Tween atUpdate : time = " << tween.getTimeRatio() << ", value = " << tween.getValueRatio();
			})->atComplete([&](Tween& tween) {
				ofLog() << "Tween atComplete : time = " << tween.getTimeRatio() << ", value = " << tween.getValueRatio();
			}),

		new Wait(0.5),

		new Log("Start tween from current specified value"),
		(new Tween(1, Expo::In))->animate(value, 50, 100)->atStart([&](Tween& tween) {
			ofLog() << "Tween atStart : value = " << value;
		})->atStop([&](Tween& tween) {
			ofLog() << "Tween atStop : value = " << value;
		})->atUpdate([&](Tween& tween) {
			ofLog() << "Tween atUpdate : value = " << value;
		})->atComplete([&](Tween& tween) {
			ofLog() << "Tween atComplete : value = " << value;
		}),

		new Log("Sequence is completed"),
	});

	sequence->run();
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




