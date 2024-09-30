#include<opencv2/opencv.hpp>
#include<iostream>

int main(){
   cv::Mat frameMatrix;
   cv::namedWindow("Output");
   cv::VideoCapture cap(0);
   if(!cap.isOpened()){ 
      std::cout << "Failed to capture device" << "\n";
      return -1;
   }
   while(true){ 
      cap >> frameMatrix;
      //std::cout << frameMatrix; 
      if(frameMatrix.empty()){ 
         break;
      }
      imshow("Output", frameMatrix);
      if(cv::waitKey(100) == 27) break;
   }
   cap.release();
   return 0;
}
