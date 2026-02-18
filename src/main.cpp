#include<chrono>
#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>

int main(){
   cv::Mat frameMatrix;
   cv::namedWindow("Output", cv::WINDOW_NORMAL);
   cv::resizeWindow("Output", 1920, 1080);
   cv::VideoCapture cap(0);
   if(!cap.isOpened()){ 
      std::cout << "Failed to capture device" << "\n";
      return -1;
   }
   std::vector<cv::Mat> footage;
   float deltaTime = 0.001;
   float timePassed = 0;
   auto frameBegin = std::chrono::high_resolution_clock::now();
   auto frameEnd = std::chrono::high_resolution_clock::now();
   int i = 0; 

   while(true){
      timePassed += deltaTime;
      auto frameBegin = std::chrono::high_resolution_clock::now();
      cap >> frameMatrix;

      if(frameMatrix.empty()) break;

      cv::Mat inverted;
      inverted = ~frameMatrix;

      //I paid for all the ram so im gonna use all the ram!
      footage.push_back(inverted); 
      if(timePassed >= 0.5){
         i++;
         cv::Mat combined;
         double alpha = 0.5;
         cv::addWeighted(frameMatrix, 1.0 - alpha, footage[i], alpha, 0.0, combined);
         cv::imshow("Output", combined);
      }
      if(cv::waitKey(100) == 27) break;

      frameEnd = std::chrono::high_resolution_clock::now();
      deltaTime = std::chrono::duration<float>(frameEnd - frameBegin).count();
   }
   
   cap.release();
   return 0;
}
