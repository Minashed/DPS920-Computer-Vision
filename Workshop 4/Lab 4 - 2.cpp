/*
We, Mina Nashed, Eric Suarez, Mithilan Sivanesan declare that the attached assignment is our
own work in accordance with the Seneca Academic Policy.  We have not copied any part
of this assignment, manually or electronically, from any other source including web
sites, unless specified as references. We have not distributed our work to other students.
*/

#include <opencv2/opencv.hpp>

using namespace cv;

#define MIN_V 0
#define MAX_V 255

int main(int argc, char** argv) {
	
	//If no argumemts are passed
	if (argc != 2) {
		std::cout << "No argument for file name";
		return 0;
	}

	//Open imgae and save it in a Mat object
	Mat Img = imread(argv[1], -1);
	Mat spImg = Mat::zeros(Img.size(), Img.type());
	Mat bImg = Mat::zeros(Img.size(), Img.type());

	float prob, x, y;
	cv::RNG rng(0xFFFFFFFF); // Random Number Generator object

	//Check if picture isnt empty
	if (Img.empty()) {
		std::cout << "Couldnt open color img specified in arguments";
		return 1;
	}

	//Asking user for probability value and checking if between 0-1
	std::cout << "Please input a probabilty value of 1 or 0: ";
	std::cin >> prob;
	while (prob > 1 || prob < 0) {
		std::cout << "Incorrect Input: Please input a probabilty value of 1 or 0: ";
		std::cin >> prob;
	}

	//Apply salt and pepper noise with given probability
	for (int row = 0; row < Img.rows; row++) {
		for (int col = 0; col < Img.cols; col++) {
			x = rng.uniform(0.0f, 1.001f);
			y = rng.uniform(0.0f, 1.001f);
			
			if (x < prob) {
				spImg.at<cv::Vec3b>(row, col)[0] = (int)(MIN_V + (y * (MAX_V - MIN_V)));
				spImg.at<cv::Vec3b>(row, col)[1] = (int)(MIN_V + (y * (MAX_V - MIN_V)));
				spImg.at<cv::Vec3b>(row, col)[2] = (int)(MIN_V + (y * (MAX_V - MIN_V)));
			}else{
				spImg.at<Vec3b>(row, col)[0] = Img.at<Vec3b>(row, col)[0];
				spImg.at<Vec3b>(row, col)[1] = Img.at<Vec3b>(row, col)[1];
				spImg.at<Vec3b>(row, col)[2] = Img.at<Vec3b>(row, col)[2];
			}
		}
	}

	//Create a 3-3 grid o go over the spImg and divide the sum by 9 blurring the img
	Matx<float, 3, 3> myKernel = Matx<float, 3, 3>::all(1 / 9.0f);

	//Create blurred img by applying above created kernal to the spImg
	filter2D(spImg,bImg,CV_8U,myKernel);

	//Display Images
	namedWindow("Color Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Salt and Pepper Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Blurred Image", CV_WINDOW_AUTOSIZE);

	imshow("Color Image", Img);
	imshow("Salt and Pepper Image", spImg);
	imshow("Blurred Image", bImg);

	//Wait for any input and destroy windows
	waitKey(0);
	destroyAllWindows();

	return 0;
}