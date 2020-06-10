
#include "robot.hpp"

int whiteDir(int* imageStrip){ // -1 for not found, 0 for left, 1 for right, 2 for already centered
	int whiteStart = -1;
	int whiteEnd = -1;
	for (int i = 0; i < cameraView.width; i++){
		if (imageStrip[i] == 1 && i != cameraView.width - 1){
			whiteStart = (whiteStart == -1) ? i : whiteStart;			
		} else if (whiteStart != -1){
			whiteEnd = i-1;
			if (((whiteStart + whiteEnd) / 2.0) > (cameraView.width / 2.0 - 2.5) && ((whiteStart + whiteEnd) / 2.0) < (cameraView.width / 2.0 + 2.5))
				return 2;
			else if ((whiteStart + whiteEnd) / 2.0 < (cameraView.width / 2.0))
				return 0;
			else
				return 1;
		}
	}
	return -1;
}

int* getImageStrip(ImagePPM image){
	int* strip = new int[image.width];
	int count = 1;
	int row = 99; // image.height / 2
	for (int i = row; i < (image.width * image.height); i+= image.height){
		int r = (int) get_pixel(image, row, count, 0);
		int g = (int) get_pixel(image, row, count, 1);
		int b = (int) get_pixel(image, row, count, 2);
		if (r >= 255 && g >= 255 && b >= 255){
			//std::cout << "we may have a white pixel?" << std::endl;
			strip[count-1] = 1;
		} else {
			strip[count-1] = 0;
		}
		count++;
	}
	std::cout << "Count: " << count << std::endl;
	return strip;
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	double vLeft = 10.0;
	double vRight = 10.0;
	double vMin = 2.5;
	double vMax = 10.0;
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
		takePicture();
		int* imageStrip = getImageStrip(cameraView);
		//bool centered = imageStrip[(int) (cameraView.width / 2.0)] == 1;
		int dir = whiteDir(imageStrip);
		if (dir == 0){
			vLeft = vMin;
			vRight = vMax;
		} else if (dir == 1){
			vLeft = vMax;
			vRight = vMin;	
		} else if (dir == 2 || dir == -1){
			vLeft = 10;
			vRight = 10;
		}
		std::cout << "White pixel?" << imageStrip[(int) (cameraView.width / 2.0)] << std::endl;
		std::cout << "White dir" << whiteDir(imageStrip) << std::endl;
		std::cout << "Height: " << cameraView.height <<", " << "Width: " << cameraView.height << std::endl;
		setMotors(vLeft,vRight);   
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10);
  } //while

} // main
