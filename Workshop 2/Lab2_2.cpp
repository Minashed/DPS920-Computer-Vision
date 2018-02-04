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

int main()
{
	int trX, trY, blX, blY;//x and y co-ordinates for top right and bottom left points
	cv::Point2i topR, bottomL;//top right and bottom left points
	char colour,exit;
	cv::Vec3b colourVec;//3d vector to hold colour channels
	
	cv::namedWindow("Lab 2-2", cv::WINDOW_AUTOSIZE);
	cv::Mat image(480, 640, CV_8UC3, cv::Vec3b(0, 0, 0));//draw image 480 by 640, all channels to 0 (black)
	cv::imshow("Lab 2-2", image);//draw image on window
	cv::waitKey(33);
	
	for (;;) {

		std::cout << "Please input an x value for the bottom left co-ordinate of a rectangle (0-480): ";
		std::cin >> blX;
		std::cout << "Please input a y value for the bottom left co-ordinate of a rectangle (0-640): ";
		std::cin >> blY;
		std::cout << "Please input an x value for top right co-ordinate of a rectangle (0-480): ";
		std::cin >> trX;
		std::cout << "Please input a y value for the top right co-ordinate of a rectangle (0-640): ";
		std::cin >> trY;

		//create top right and bottom left points of rectangle to be created
		topR = cv::Point2i(trX, trY);
		bottomL = cv::Point2i(blX, blY);

		std::cout << "Please input a letter character for the colour of the rectangle: " << std::endl;
		std::cout << "k: black" << std::endl;
		std::cout << "w: white" << std::endl;
		std::cout << "r: red" << std::endl;
		std::cout << "g: green" << std::endl;
		std::cout << "b: blue" << std::endl;
		std::cout << "c: cyan" << std::endl;
		std::cout << "y: yellow" << std::endl;
		std::cout << "m: magenta" << std::endl;
		std::cout << "x: random" << std::endl<<">>";
		std::cin >> colour;
		
		if (colour == 'k') {//black
			colourVec = cv::Vec3b(0, 0, 0);
		}
		else if (colour == 'w') {//white
			colourVec = cv::Vec3b(255, 255, 255);
		}
		else if (colour == 'r') {//red
			colourVec = cv::Vec3b(0, 0, 255);
		}
		else if (colour == 'g') {//green
			colourVec = cv::Vec3b(0, 255, 0);
		}
		else if (colour == 'b') {//blue
			colourVec = cv::Vec3b(255, 0, 0);
		}
		else if (colour == 'c') {//cyan
			colourVec = cv::Vec3b(255, 255, 0);
		}
		else if (colour == 'y') {//yellow
			colourVec = cv::Vec3b(0, 255, 255);
		}
		else if (colour == 'm') {//magenta
			colourVec = cv::Vec3b(255, 0, 255);
		}
		else if (colour == 'x') {//random
			cv::RNG rng = cv::RNG(static_cast<long int>(time(NULL)));
			colourVec = cv::Vec3b(rng(256), rng(256), rng(256));
		}

		for (int y = trY; y < blY; y++) {//colour in rectangle area in image by accessing pixels individually
			for (int x = blX; x < trX; x++) {
				image.at <cv::Vec3b>(x, y) = colourVec;
			}
		}
		cv::imshow("Lab 2-2", image);//redraw image on window
		cv::waitKey(33);

		cv::Rect rect = cv::Rect(topR, bottomL);//create rectangle object using user specified points
		std::cout << "Area of the rectangle: " << rect.area() << std::endl;
		std::cout << "Width of the rectangle: " << rect.width << std::endl;
		std::cout << "Height of the rectangle: " << rect.height << std::endl << std::endl;

		//Request user for a point
		std::cout << "Please enter an x value for a new point (0-480): ";
		std::cin >> trX;
		std::cout << "Please enter a y value fo a new point(0-649): ";
		std::cin >> trY;
		topR = cv::Point2i(trX, trY);//create new  point (repurpose topR point)
		std::cout << "The point is " << (rect.contains(topR) ? "" : "not ") << "inside the rectangle." << std::endl;
		
		std::cout << "Press q to exit or any other key to try again: "<<std::endl<<">>";
		std::cin >> exit;
		if (exit == 'q') {
			break;
		}
	}
	cv::destroyAllWindows();
	return 0;
}
