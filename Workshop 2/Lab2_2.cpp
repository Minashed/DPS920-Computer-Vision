/*
We, Mina Nashed, Eric Suarez, Mithilan Sivanesan, declare that the attached assignment is our own work in
accordance with the Seneca Academic Policy.  We have not copied any part of this assignment,
manually or electronically, from any other source including web sites, unless specified as references.
We have not distributed our work to other students.
*/
#include <opencv2/opencv.hpp>
#include <iostream>

#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib")

int main() {

	cv::namedWindow("Lab 2-2", cv::WINDOW_AUTOSIZE);

	cv::Mat image(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));

	int x, y;
	char color;

	for (;;) {
		cv::imshow("Lab 2-2", image);

		if ((char)cv::waitKey(33) >= 0) break;

		std::cout << "Please input an x value for the image (1-480): ";
		std::cin >> x;

		std::cout << "Please input an y value for the image (1-640): ";
		std::cin >> y;

		std::cout << "Please input a letter character for a color: " << std::endl;
		std::cout << "k: black" << std::endl;
		std::cout << "w: white" << std::endl;
		std::cout << "r: red" << std::endl;
		std::cout << "g: green" << std::endl;
		std::cout << "b: blue" << std::endl;
		std::cout << "c: cyan" << std::endl;
		std::cout << "y: yellow" << std::endl;
		std::cout << "m: magenta" << std::endl;
		std::cout << "x: random" << std::endl;
		std::cin >> color;

		if (x > 0 && x < 481 && y > 0 && y < 640) {
			if (color == 'k') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(0, 0, 0));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'w') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(255, 255, 255));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'r') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(0, 0, 255));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'g') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(0, 255, 0));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'b') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(255, 0, 0));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'c') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(255, 255, 0));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'y') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(0, 255, 255));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'm') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(255, 0, 255));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
			else if (color == 'x') {
				cv::Mat newImage(x, y, CV_8UC3, cv::Scalar(rand()%255, rand()%255, rand()%255));
				newImage.copyTo(image(cv::Rect(0, 0, x, y)));
			}
		}

		if ((char)cv::waitKey(33) >= 0) break;
	}

	return 0;

}