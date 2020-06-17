#include "robot.hpp"

/* Scans through the provided image strip to find were the center of the white line is
 * It goes through the array and finds where there red wall starts and ends
 * It then returns a number of the collumn with were the center of the red wall is
*/
double redDir(int* imageStrip, double camView){
	int redStart = -1;//stores the starting column of the red line pixel block
	int intCheck = imageStrip[cameraView.width];
	int length = (intCheck == 2) ? cameraView.width*camView : cameraView.width;
	for(int i = 0; i < length; i++){//cheak through array for red pixels but ingore the last quarter
		if(imageStrip[i] == intCheck && i != length - 1){
			redStart = (redStart == -1) ? i : redStart;//first time a red pixel is found it must be the start of line
		}
		else if(redStart != -1){//end of the line has been found
			if(intCheck == 2){
				return i;
			}
			else{
				return (redStart + i) / 2.0;
			}
		}
	}
	return -1;//no red pixels found in the array
}

/* When given an image it will process it into an array
 * It takes a strip through the middle of the image
 * Then returns it as an array of 1 for red pixel
 * and 0 for nonred pixels
 * As a extra it will ingore the first wall if a second one is
 * found with 50 pixels
*/

int* getImageStrip(ImagePPM image, int row, int gape, double camView){
	int* strip = new int[image.width+1];
	strip[image.width] = 1;
	for(int j = 0; j < 1; j++){
		int start = 0;//start of the non red pixels past first block of red
		bool lastBlank = true;
		bool empty = true;
		for (int i = 0; i < image.width; i++){
			int red = (int) get_pixel(image, row, i, 0);
			int green = (int) get_pixel(image, row, i, 1);
			int white = (int) get_pixel(image, row, i, 3);
			bool isRed = red >= 255 && green < 250;
			if (isRed && i < image.width*camView){
				if(lastBlank && strip[image.width] == 2 && start + gape > i){
					for(int k = 0; k < start+1; k++){
						strip[k] = 0;//remove the first red line
					}
				}
				strip[i] = 2;
				strip[image.width] = 2;
				start = i;
				lastBlank = false;
				empty = false;
			} 
			else if (white >= 255){
				strip[i] = 1;
				lastBlank = false;
				empty = false;
			}
			else {
				strip[i] = 0;
				lastBlank = true;
			}
		}
		if(empty && row < image.height){
			j = -1;
			row++;
		}
	}
	for (int i = 0; i < image.width; i++){
		std::cout<<strip[i];//print the strip
	}
	return strip;
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	//Constent values used
	const double vMax = 20.0;//max wheel speed
	const double turnSpeed = 11;//The speed of inner wheel while truning to fine a wall
	const double turnMupli = 0.65;//The muliplier for how much to turn per pixel of desired position
	const double wallDist = 30.0;//The distance the robot left most vision and the wall it's following
	const int row = 85;//The row of the image that the robot will see
	const int gape = 50;//The largest possable gap between to red wall for the left wall to be ignored.
	const int contStrght= 10;//The number of frames the robot contines straight after losing a wall
	const double camView = 0.50;
	
	int noLineCount = 0;//amount of frames in a row without a wall
	int curFol = 1;
	
    while(1){
		takePicture();//Get the picture
		double vLeft = vMax;//left wheel speed
		double vRight = vMax;//right wheel speed
		int* imageStrip = getImageStrip(cameraView, row, gape, camView);//form the image strip
		double dir = redDir(imageStrip, camView);//find the dirction to turn the robot
		double dist = cameraView.width/2;
		if(imageStrip[cameraView.width] == 2){
			dist = wallDist;
		}
		if(dir != -1){//if robot is follwing a wall reset the time spent not follwing a wall
			noLineCount = 0;
			curFol = imageStrip[cameraView.width];
		}
		if (dir > 0 && dir <= dist){//make the robot turn left
			dir = dist - dir;
			vLeft = vMax-dir*turnMupli;//turn left based of how far off desired position
			vRight = vMax;
		}
		else if (dir > 0){//make the robot turn right
			dir = dir-dist;//remove the value that was added to signify a right turn
			vLeft = vMax;
			vRight = vMax-dir*turnMupli;//turn right based of how far off desired position
		}
		else if(dir = -1){//no wall was found
			noLineCount++;//increase count for amount of frames with no no wall
			if(noLineCount > contStrght){//if somany frames without following a wall turn left to try and refind the wall
				vLeft = (curFol == 2) ? turnSpeed : -vMax;
				vRight = vMax;
			}
			else{//if the wall hasn't been lost for so many frames, keep going straight so you don't hit it when robot turns
				vLeft = vMax;
				vRight = vMax;
			}
		}
		setMotors(vLeft,vRight);
		delete(imageStrip);//delete the image strip array
		std::cout<<"\n"<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		std::cout<<"Distance from object: "<<dir<<std::endl;
		std::cout<<"Robot is following: "<<imageStrip[cameraView.height]<<" Last line followed "<<curFol<<std::endl;
		std::cout<<std::endl;
  } //while

} // main
