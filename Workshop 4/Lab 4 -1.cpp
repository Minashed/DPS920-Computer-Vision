/*
We, Mina Nashed, Eric Suarez, Mithilan Sivanesan declare that the attached assignment is our 
own work in accordance with the Seneca Academic Policy.  We have not copied any part 
of this assignment, manually or electronically, from any other source including web 
sites, unless specified as references. We have not distributed our work to other students.
*/

//Program to convert a color image to greyscale then apply a histogram equalization to it

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
	
	//If no argumemts are passed
	if (argc != 2) {
		
		std::cout << "No argument for file name";

		return 0;
	}

	//Open imgae and save it in a Mat object
	Mat img = imread(argv[1], -1);
	
	if (img.empty()) return -1;

	//Convert img into a grayscale image and save it into g_img
	Mat g_img;
	cvtColor(img, g_img, CV_BGR2GRAY);
	
	//create a file for the gray_scale image
	imwrite("gforest.jpg",g_img);


	//Convert g_img to hostogram and save it into h_img
	Mat h_img;
	equalizeHist(g_img, h_img);
	imwrite("hforest.jpg", h_img);

	//Open window for greyscale
	namedWindow("Color Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Equalized Image", CV_WINDOW_AUTOSIZE);

	moveWindow("Color Image", 0, 20);
	moveWindow("Equalized Image", 500, 20);

	imshow("Color Image", img);
	imshow("Equalized Image", h_img);

	//Wait for any input and destroy window
	waitKey();

	destroyWindow("Color Image");
	destroyWindow("Equalized Image");


	return 0;
}