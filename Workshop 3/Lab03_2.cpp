// Lab03_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>


int main()
{
	cv::namedWindow("Lab03_2", CV_WINDOW_AUTOSIZE);
	cv::moveWindow("Lab03_2", 30, 40);
	cv::Mat image = cv::imread("image.jpg",-1);
	if (image.empty()) return -1;
	cv::imshow("Lab03_2", image);
	cvWaitKey(33);

	//Brighten Image
	cv::namedWindow("Brightened", CV_WINDOW_AUTOSIZE);
	image += cv::Scalar(100, 100, 100);
	cv::imshow("Brightened", image);
	cv::waitKey(33);
	
	
	//Increase Contrast
	cv::namedWindow("Increased Contrast", CV_WINDOW_AUTOSIZE);
	image *= 1.5;
	cv::imshow("Increased Contrast", image);

	//Linear Blend
	cv::namedWindow("Linear Blend", CV_WINDOW_AUTOSIZE);
	cv::Mat image2 = cv::imread("image2.jpg", -1);//second image to be blended with first
	
	cv::Mat linearBlend(image.size(),CV_8UC3);//create image with same dimensions as original images
	if (image2.empty()) return -1;
		
	linearBlend = 0.6*image + 0.4*image2;//blend with alpha = 0.4

	cv::imshow("Linear Blend", linearBlend);
	if ((char)cv::waitKey(0) == 13) {
		cv::destroyAllWindows();
	}
		
	
	
	
	
	
	return 0;
}

