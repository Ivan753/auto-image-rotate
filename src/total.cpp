#include "CImg.h"
#include <string>
#include <cmath>
#include <fstream>  

int main(int argc, char* argv[]) {

char sol = 0;

if(argc > 1){
	
	if(strcmp(argv[1], "create") == 0){
		sol = 1;
	}
		
	if(strcmp(argv[1], "rotate") == 0){
		sol = 2;
	}
	
}else{
	return 0;
}


switch(sol){

case 1: {
  
  // Create 3 images: initial, turning and result
  cimg_library::CImg<unsigned char> image("1.bmp"), image1;
  
  int real_size = (int) sqrt(2*image.height()*image.height());
  
  cimg_library::CImg<unsigned char> res(real_size, real_size, 1, 3, 0);
  
	for(char i = 0; i < 36; i++){
		
		std::string name = std::to_string(i*10)+".bmp";
		image1 = image;
		image1.rotate(i*10);
		res.fill(0);
		res.draw_image((real_size - image1.width())/2, (real_size - image1.height())/2, 0, 0, image1);
		res.save(name.c_str());
		
	}
	

}
break;

case 2: {

  std::ifstream file;
  
  // x, y - coordinates of the center rendering
  // sleep - current delay
  // last_sleep - last delay (used for excluding errors)
  int x;
  int y;
  int sleep;
  int last_sleep = 1;
  
  int screen_width = cimg_library::CImgDisplay::screen_width();
  int screen_height = cimg_library::CImgDisplay::screen_height();
  
  cimg_library::CImgDisplay disp(screen_width, screen_height, "Main Window");
  cimg_library::CImg<unsigned char> bg(screen_width, screen_height, 1, 3, 0);
  
  disp.move(0 ,0);
  
  while(true){
  
	for(char i = 0; i < 36; i++){
		
		// Open file for get the parameters display
		file.open("settings.txt");
		
		file>>x;
		file>>y;
		file>>sleep;
		
		// Generate name of current image
		std::string name = std::to_string(i*10);
		std::string after = ".bmp";
		
		// Get current image
		cimg_library::CImg<unsigned char> image((name + after).c_str());
		
		// Fill background of black
		bg.fill(0);
		
		// Display background with drawn image in one hundred percent with gotten center
		disp.display(bg.draw_image((x-image.width())/2, (y-image.height())/2, image));
		
		// Made delay
		if(sleep > 0){
			last_sleep = sleep;
			cimg_library::cimg::sleep(sleep);
		}else{
			cimg_library::cimg::sleep(last_sleep);
		}
		
		// Close file for we can get new values
		file.close();
	}
  }

}  
break;

}


  return 0;
}
