#include "robot.hpp"

/* Scans through the provided image strip to find red wall or white line
 * It goes through the array and finds where the block of red or white starts and ends
 * What if looks for is dictated by last extra value in the array
 * It then returns the distance between left of the robot vision and the right side of
 * the red wall or the center of the white line, -1 is returned if nothing is found
*/
double findLine(int* imageStrip, double camView){
	int lineStart = -1;//Stores the starting column of the block of found pixels
	int intCheck = imageStrip[cameraView.width];//Extract the value to search the array for
	int length = (intCheck == 2) ? cameraView.width*camView : cameraView.width;//If looking for red don't check whole array
	for(int i = 0; i < length; i++){
		if(imageStrip[i] == intCheck && i != length - 1){//Check the pixels, last pixel of array is assume to be 0
			lineStart = (lineStart == -1) ? i : lineStart;//first time a red pixel is found it must be the start of line
		}
		else if(lineStart != -1){//End of the block of coloured pixels has been found
			if(intCheck == 2){
				return i;//If looking for red return coloumn of the end of the red
			}
			else{
				return (lineStart + i) / 2.0;//If not looking for red return the average colloumn
			}
		}
	}
	return -1;//No pixels found for the colour searched for
}

/* When given an image it will process it into an array
 * It takes a strip through the requested row then returns it as an array
 * of 2 for red pixels, 1 for white pixels and 0 for everything else
 * It will ignore the first block of red pixels if a second one is found after it
 * Last int in array will store the value to follow, will be 2 if ANY red is found
 * If nothing is detected in row it will check rows closer to the robot
*/

int* getImageStrip(ImagePPM image, int row, int gape, double camView){
	int* strip = new int[image.width+1];//Array has an extra int to store number to follow
	strip[image.width] = 1;//By default the robot assumes if following a white line
	for(int j = 0; j < 1; j++){
		int redEnd = 0;//End position of the first block of red
		bool empty = true;//Tracks if current array is empty
		for (int i = 0; i < image.width; i++){//Make the strip
			//Get the colour of each of the pixels
			int red = (int) get_pixel(image, row, i, 0);
			int green = (int) get_pixel(image, row, i, 1);
			int white = (int) get_pixel(image, row, i, 3);
			if (red >= 255 && green < 250 && i < image.width*camView){//If the pixel is red and in robots vision
				//If a second block of red pixel is found just after the first
				if((i != 0 && strip[i-1] != 2) && strip[image.width] == 2 && redEnd + gape > i){
					for(int k = 0; k < redEnd+1; k++){//remove the first red line
						strip[k] = 0;
					}
				}
				strip[i] = 2;//Mark pixel as red
				strip[image.width] = 2;//Mark the red is the colour to follow
				redEnd = i;//Keep track of the end of the red pixels
				empty = false;//Array has something in it
			} 
			else if (white >= 255){//Check if the pixel is white
				strip[i] = 1;//Mark the pixels as white
				empty = false;//Array has something in it
			}
			else {
				strip[i] = 0;//The pixel isn't red or white
			}
		}
		if(empty && row < image.height - 1){//If the array is empty and there's another row to check 
			j = -1;//Make another array
			row++;//Check next row towards robot
		}
	}
	for (int i = 0; i < image.width; i++){//Print the strip created
		std::cout<<strip[i];//print the strip
	}
	return strip;
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	//Constant values used
	const double vMax = 20.0;//max wheel speed
	const double turnSpeed = 11.0;//The speed of inner wheel while turning to find a wall
	const double turnMupli = 0.65;//The multiplier  for how much to turn per pixel off desired position
	const double wallDist = 30.0;//The desired distance from the left of ther vision and the wall
	const int row = 85;//The row of the image that the robot will see
	const int gape = 50;//The largest possible gap between to red pixel blocks for the first to be deleted
	const int contStrght= 10;//Frames the robot continues straight after losing a wall
	const double camView = 0.50;//Amount of vision robot uses to find red walls
	
	//Varables the need to be stored between frames
	int noLineCount = 0;//amount of frames in a row without a wall
	int curFol = 1;//Last colour that the robot followed
	
    while(1){
		takePicture();//Get the picture
		double vLeft = vMax;//left wheel speed
		double vRight = vMax;//right wheel speed
		int* imageStrip = getImageStrip(cameraView, row, gape, camView);//form the image strip
		double linePos = findLine(imageStrip, camView);//Find the position of thing robot is following
		double dist = cameraView.width/2;//Distance to keep between left side of vision and robot
		if(imageStrip[cameraView.width] == 2){
			dist = wallDist;//If the robot is following red drive to the right of it
		}
		if(linePos != -1){
			noLineCount = 0;//If follwing something reset the time spent not follwing anything
			curFol = imageStrip[cameraView.width];//Record colour being followed
		}
		if (linePos >= 0 && linePos <= dist){//Make the robot turn left
			linePos = dist - linePos;
			vLeft = vMax-linePos*turnMupli;//turn left based of how far off desired position
			vRight = vMax;
		}
		else if (linePos > 0){//make the robot turn right
			linePos = linePos-dist;
			vLeft = vMax;
			vRight = vMax-linePos*turnMupli;//turn right based of how far off desired position
		}
		else if(linePos = -1){//Nothing to follow was found
			noLineCount++;//Increase count for amount of frames not following anything
			if(noLineCount > contStrght){//If so many frames without following something turn left
				vLeft = (curFol == 2) ? turnSpeed : -vMax;//If following red turn left slowly, otherwise turn on the spot
				vRight = vMax;
			}
			else{//If the wall hasn't be lost for long just go straight
				vLeft = vMax;
				vRight = vMax;
			}
		}
		setMotors(vLeft,vRight);
		delete(imageStrip);//delete the image strip array
		std::cout<<"\n"<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		std::cout<<"Distance from object: "<<linePos<<std::endl;
		std::cout<<"Robot is following: "<<imageStrip[cameraView.height]<<" Last line followed "<<curFol<<std::endl<<std::endl;
  } //while
} // main
