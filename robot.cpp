
#include "robot.hpp"
int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 40.0;
    double vRight = 40.0;
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
      cameraView = get_picture(i0); // get pic from file
      rowMid = image.height/2;//takes a row number (middle row)
      int color[image.width];//put all the RGB value from rowMid, col into the array
      //following for loop gets the luminosity value of each pixel in all columns in rowMid
      //store it into color array
      for(int col =0; col <= image.width; col++){
		  color[col] = get_pixel(cameraView, rowMid, col, 3);
	  } 
      
      //following for loop goes through the values in array check if it is > 250 
      // if it is replace value by 1 and also keep count of how many values were changed 1 (count)
      //if it is not replace value to 0
      int count;
      int totalIndex;
      for(int i=0; i < color[image.width]; i++){
		  if(color[i] > 250){
			  color[i] =1;
			  totalIndex += i; // add all the index of value that are replace to 1
			  count++;
		  }
		  else{
			  color[i] = 0;
		  }
	  }
	  int midWhitePoint = totalIndex/count; // calculate the position of the mid white pixel is
	  //following calculate the error
	  signed int error;
	  if(midWhitePoint < image.width/2){
		  if(midWhitePoint < image.width/4){
			  error = -10;
		  }
		  error = -5;
	  }
	  else if(midWhitePoint > image.width/2){
		  if(midWhitePoint > (3*image.width)/4){
			  error = 10;
		  }
		  error = 5;
	  }
	  unsigned char v_go = 40;
	  double kp = 1;
	  double dv = kp * error;
	  vRight = v_go + dv;
	  vLeft = v_go - dv;
	  setMotors(vLeft, vRight);
		  		  	  
       usleep(10000);
  } //while
	
} // main
