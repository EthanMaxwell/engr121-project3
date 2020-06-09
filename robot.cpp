
#include "robot.hpp"
int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 40.0;
    double vRight = 30.0;
    
    while(1){
		takePicture();
		SavePPMFile("i0.ppm",cameraView);
		int* data = new int[cameraView.height*cameraView.width];
		for(int row = 0; row < cameraView.height; row++){
			for(int column = 0; column < cameraView.width ; column++){
				//data[column+cameraView.height*row] = get_pixel(cameraView,row,column, 3);
				if(get_pixel(cameraView,row,column, 3) > 150){
					data[column+cameraView.width*row] = 1;
				}
				else{
					data[column+cameraView.width*row] = 0;
				}
			}
		}
		for(int column = 0; column < cameraView.width; column++){
			for(int row = cameraView.height-1; row > -1; row--){
				std::cout<<data[column+cameraView.width*row];
			}
			std::cout<<std::endl;
		}
      setMotors(vLeft,vRight);   
  } //while

} // main

