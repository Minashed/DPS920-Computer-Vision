/*
We, Mina Nashed, Eric Suarez, Mithilan Sivanesan declare that the attached assignment is our
own work in accordance with the Seneca Academic Policy.  We have not copied any part
of this assignment, manually or electronically, from any other source including web
sites, unless specified as references. We have not distributed our work to other students.
*/

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

	float prob;

	std::cout << "Please input a probabilty value of 1 or 0: ";
	std::cin >> prob;

	while (prob > 1 || prob < 0) {
		std::cout << "Incorrect Input: Please input a probabilty value of 1 or 0: ";
		std::cin >> prob;
	}

	

	Mat g_img;
	cvtColor(img, g_img, CV_BGR2GRAY);

	namedWindow("Grey Image", CV_WINDOW_AUTOSIZE);
	imshow("Grey Image", g_img);

	imwrite("gforest.jpg", g_img);

	Mat sp_img;
	normalize(g_img, sp_img, 0.0, 1.0, CV_MINMAX, CV_64F);
	
	sp_img = sp_img + prob;
	
	normalize(sp_img, sp_img, 0.0, 1.0, CV_MINMAX, CV_64F);
	
	imwrite("spforest.jpg", sp_img);


	namedWindow("Salt and Pepper Image", CV_WINDOW_AUTOSIZE);
	imshow("Salt and Pepper Image", sp_img);

	//Wait for any input and destroy window
	waitKey();

	destroyWindow("Grey Image");
	destroyWindow("Salt and Pepper Image");

	return 0;
}