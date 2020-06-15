#include "robot.hpp"

/* Scans through the provided image strip to find were the center of the white line is
 * It goes through the array and finds where there red wall starts and ends
 * It then returns a number based of the disance from the center of the red wall
 * to were the robot wants to keep the center of the red wall
 * -1 for not found, 0 for straight, 1 to 100 for left, 100+ for right
 * 
*/
int whiteDir(int* imageStrip){
	int whiteStart = -1;//stores the starting column of the white line pixel block
	int whiteEnd = -1;//stores the starting column of the white line pixel block
	for (int i = 0; i < cameraView.width*0.75; i++){//cheak through array for white pixels but ingore the last quarter
		if (imageStrip[i] == 1 && i != cameraView.width - 1){
			whiteStart = (whiteStart == -1) ? i : whiteStart;//first time a white pixel is found it must be the start of line
		}
		else if (whiteStart != -1){//end of the line has been found
			whiteEnd = i-1;
			int lineCol = (int)((whiteStart + whiteEnd) / 2.0);//column number of the line
			std::cout<<lineCol<<" out of "<<cameraView.width;
			if(lineCol > 36 && lineCol < 38){//robot is straight enough so can go straight
				return 0;
			}
			else if ((whiteStart + whiteEnd) / 2.0 < 37){
				return lineCol;//robot must go left
			}
			else{
				return lineCol + 100;//robot must go right, 100 is added to make it as a right turn
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

int* getImageStrip(ImagePPM image){
	int* strip = new int[image.height];
	int row = 75;//check the 75 row of the image
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
		else if(white >= 255){//check if there is a white line is there is no red wall
			strip[37] = 1;//if there is a white line make it just drive straight
		}
		else {
			strip[i] = 0;
		}
		if(start + 50 > i){//if there is another red wall less then 50 red pixels after then the first
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
	double vLeft = 10.0;//left wheel speed
	double vRight = 10.0;//right wheel speed
	double vMin = 10.0;//min wheel speed
	double vMax = 20.0;//max wheel speed
	int noLineCount = 0;//amount of frames in a row without a wall
    while(1){
		takePicture();
		int* imageStrip = getImageStrip(cameraView);
		int dir = whiteDir(imageStrip);
		if(dir != -1){//if robot is follwing a wall rest the time spent not follwing a wall
			noLineCount = 0;
		}
		if (dir > 0 && dir < 100){//make the robot turn left
			vLeft = vMax-(35 - dir)*0.25;//turn left based of how far off desired position
			vRight = vMax;
		} else if (dir >= 30){//make the robot turn right
			dir = dir-100;//remove the 100 that was added to signify a right turn
			vLeft = vMax;
			vRight = vMax-dir*0.25;//turn right based of how far off desired position
		} else if (dir == 0){//make the robot drive straight
			vLeft = vMax;
			vRight = vMax;
		}
		else if(dir = -1){//no wall was found
			noLineCount++;//increase count for amount of frames with no no wall
			if(noLineCount > 14){//if ___ frames without following a wall turn left to try and refind the wall
				vLeft = 11.0;
				vRight = vMax;
			}
			else{//if the wall hasn't been lost for ___ frames, keep going straight so you don't hit it when robot turns
				vLeft = vMax;
				vRight = vMax;
			}
		}
		setMotors(vLeft,vRight);
		
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
  } //while

} // main
