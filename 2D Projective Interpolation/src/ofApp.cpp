#include "ofApp.h"

GLuint VBO, VAO;

void calculateQ(ofVec2f p0, ofVec2f p1, ofVec2f p2, ofVec2f p3,
	float& q0, float& q1, float &q2, float & q3)
{
    float ax = p2.x - p0.x;
    float ay = p2.y - p0.y;
    float bx = p3.x - p1.x;
    float by = p3.y - p1.y;

	float cross = ax * by - ay * bx;

	if (cross != 0) {
        float cy = p0.y - p1.y;
        float cx = p0.x - p1.x;

		float s = (ax * cy - ay * cx) / cross;

		if (s > 0 && s < 1) {
			float t = (bx * cy - by * cx) / cross;

			if (t > 0 && t < 1) {
				q0 = 1 / (1 - t);
				q1 = 1 / (1 - s);
				q2 = 1 / t;
				q3 = 1 / s;

				// you can now pass (u * q, v * q, q) to OpenGL
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::setup(){
	shader.load("calibrate");
	shader.printActiveAttributes();

    w = ofGetWidth();
    h = ofGetHeight();
    q0 = q1 = q2 = q3 = 1.0;
    p0.set(w*0.25f, 0);
    p1.set(w*0.75f, 0);
    p2.set(w, h);
    p3.set(0, h);

    setupVertexArray();

    ofDisableArbTex();
    //grid.load("grid.png");
    grid.load("test.jpg");

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
	ofSetColor(255);

	shader.begin();
    shader.setUniformTexture("grid", grid.getTexture(), 0);
	
	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // 0 = the starting index in the enabled arrays; 4 = the number of indices to be rendered.
	glBindVertexArray(0);

	shader.end();

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
	{
        calculateQ(p0, p1, p2, p3, q0, q1, q2, q3);
        updateVertexBuffer();
	}

	if (key == 'b')
	{
		q0 = q1 = q2 = q3 = 1.0;
        updateVertexBuffer();
	}
}

//--------------------------------------------------------------
void ofApp::setupVertexArray()
{
    GLfloat  v[] = { p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y,
                    0*q0, 0*q0, q0,
                    1*q1, 0*q1, q1,
                    1*q2, 1*q2, q2,
                    0*q3, 1*q3, q3 };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(8*sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

//--------------------------------------------------------------
void ofApp::updateVertexBuffer()
{
    GLfloat  v[] = { p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y,
        0 * q0, 0 * q0, q0,
        1 * q1, 0 * q1, q1,
        1 * q2, 1 * q2, q2,
        0 * q3, 1 * q3, q3 };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
 p0 = ofVec2f(x,y);
 calculateQ(p0, p1, p2, p3, q0, q1, q2, q3);
 updateVertexBuffer();
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
