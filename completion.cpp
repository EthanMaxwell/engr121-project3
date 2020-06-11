#include "robot.hpp"

/* Scans through the previded image strip to find were the center of the white line is
 * It goes through the array and finds were there white line starts and ends
 * It then returns a value based on were abouts it is relitive to the center line
 * -1 for not found, 0 for left, 1 for right, 2 for already centered
*/
int whiteDir(int* imageStrip){
	int whiteStart = -1;//stores the starting column of the white line pixel block
	int whiteEnd = -1;//stores the starting column of the white line pixel block
	for (int i = 0; i < cameraView.height; i++){//cheak through array for white pixels
		if (imageStrip[i] == 1 && i != cameraView.height - 1){
			whiteStart = (whiteStart == -1) ? i : whiteStart;//first time a white pixel is found it must be the start of line			
		}
		else if (whiteStart != -1){//end of the line has been found
			whiteEnd = i-1;
			double lineCol = (whiteStart + whiteEnd) / 2.0;//column number of the line
			std::cout<<lineCol<<" out of "<<cameraView.height;
			if (lineCol > (cameraView.height / 2.0 - 10) && lineCol < (cameraView.height / 2.0 + 10)){
				return 2;//already on course
			}
			else if ((whiteStart + whiteEnd) / 2.0 < (cameraView.height / 2.0)){
				return 0;//robot must go left
			}
			else{
				return 1;//robot must go right
			}
		}
	}
	return -1;//no white pixels found in the array
}

/* When given an image it will process it into an array
 * It takes a strip through the middle of the image
 * Then returns it as an array of 1 for white pixels
 * and 0 for a nonwhite pixel
*/

int* getImageStrip(ImagePPM image){
	int* strip = new int[image.height];
	int row = 99; // image.height / 2
	for (int i = 0; i < (image.height); i++){
		int r = (int) get_pixel(image, row, i, 0);
		int g = (int) get_pixel(image, row, i, 1);
		int b = (int) get_pixel(image, row, i, 2);
		if (r >= 255 && g >= 255 && b >= 255){
			//std::cout << "we may have a white pixel?" << std::endl;
			strip[i] = 1;
		} else {
			strip[i] = 0;
		}
		std::cout<<strip[i];
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
    	while(1){
		takePicture();
		int* imageStrip = getImageStrip(cameraView);
		int dir = whiteDir(imageStrip);
		if (dir == 0){//make the robot turn left
			vLeft = vMin;
			vRight = vMax;
		} else if (dir == 1){//make the robot turn right
			vLeft = vMax;
			vRight = vMin;	
		} else if (dir == 2){//make the robot drive straight
			vLeft = vMax;
			vRight = vMax;
		} else if (dir == -1){//make the robot turn on the spot
			vLeft = vMax;
			vRight = -vMax;
		}
		std::cout << "White pixel?" << imageStrip[(int) (cameraView.height / 2.0)] << std::endl;
		std::cout << "White dir" << dir << std::endl;
		std::cout << "Height: " << cameraView.height <<", " << "Width: " << cameraView.height << std::endl;
		setMotors(vLeft,vRight);   
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
  } //while

} // main
