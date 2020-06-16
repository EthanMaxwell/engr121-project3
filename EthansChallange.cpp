#include "robot.hpp"

/* Scans through the provided image strip to find were the center of the white line is
 * It goes through the array and finds where there red wall starts and ends
 * It then returns a number of the collumn with were the center of the red wall is
*/
double redDir(int* imageStrip){
	int redStart = -1;//stores the starting column of the red line pixel block
	int redEnd = -1;//stores the starting column of the red line pixel block
	for (int i = 0; i < cameraView.width*0.75; i++){//cheak through array for red pixels but ingore the last quarter
		if (imageStrip[i] == 1 && i != cameraView.width - 1){
			redStart = (redStart == -1) ? i : redStart;//first time a red pixel is found it must be the start of line
		}
		else if (redStart != -1){//end of the line has been found
			redEnd = i-1;
			return (redStart + redEnd) / 2.0;//robot must go left
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

int* getImageStrip(ImagePPM image, int row, int gape){
	int* strip = new int[image.height];
	int start = 0;//start of the non red pixels past first block of red
	for (int i = 0; i < image.height; i++){
		int red = (int) get_pixel(image, row, i, 0);
		int green = (int) get_pixel(image, row, i, 1);
		int white = (int) get_pixel(image, row, i, 3);
		if (red >= 255 && green < 250){
			//std::cout << "we may have a white pixel?" << std::endl;
			strip[i] = 1;
			start = i;
		} 
		else {
			strip[i] = 0;
		}
		if(start + gape > i){//if there is another red wall less then 50 red pixels after then the first
			if(red >= 255 && green < 250){
				for(int j = 0; j < start; j++){
					strip[j] = 0;//remove the first red line
				}
			}
		}
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
	const double turnSpeed = 10;//The speed of inner wheel while truning to fine a wall
	const double turnMupli = 0.5;//The muliplier for how much to turn per pixel of desired position
	const double wallDist = 34.0;//The distance the robot left most vision and the wall it's following
	const int row = 80;//The row of the image that the robot will see
	const int gape = 20;//The largest possable gap between to red wall for the left wall to be ignored.
	const int contStrght= 16;//The number of frames the robot contines straight after losing a wall
	
	int noLineCount = 0;//amount of frames in a row without a wall
	
    while(1){
		takePicture();//Get the picture
		double vLeft = vMax;//left wheel speed
		double vRight = vMax;//right wheel speed
		int* imageStrip = getImageStrip(cameraView, row, gape);//form the image strip
		double dir = redDir(imageStrip);//find the dirction to turn the robot
		if(dir != -1){//if robot is follwing a wall reset the time spent not follwing a wall
			noLineCount = 0;
		}
		if (dir > 0 && dir <= wallDist){//make the robot turn left
			dir = wallDist - dir;
			vLeft = vMax-dir*turnMupli;//turn left based of how far off desired position
			vRight = vMax;
		}
		else if (dir > 0){//make the robot turn right
			dir = dir-wallDist;//remove the value that was added to signify a right turn
			vLeft = vMax;
			vRight = vMax-dir*turnMupli;//turn right based of how far off desired position
		}
		else if(dir = -1){//no wall was found
			noLineCount++;//increase count for amount of frames with no no wall
			if(noLineCount > contStrght){//if somany frames without following a wall turn left to try and refind the wall
				vLeft = turnSpeed;
				vRight = vMax;
			}
			else{//if the wall hasn't been lost for so many frames, keep going straight so you don't hit it when robot turns
				vLeft = vMax;
				vRight = vMax;
			}
		}
		setMotors(vLeft,vRight);
		delete(imageStrip);//delete the image strip array
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
  } //while

} // main
