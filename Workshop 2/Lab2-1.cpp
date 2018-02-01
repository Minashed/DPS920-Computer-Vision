// Example 2-10. The same object can load videos from a camera or a file
/*
We, Mina Nashed, Eric Suarez, Mithilan Sivanesan, declare that the attached assignment is our own work in 
accordance with the Seneca Academic Policy.  We have not copied any part of this assignment, 
manually or electronically, from any other source including web sites, unless specified as references.
We have not distributed our work to other students.
*/

#include <opencv2/opencv.hpp>
#include <iostream>

#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib" )

void help(char** argv) {
	std::cout << "\n"
		<< "\nxample 2-10. The same object can load videos from a camera or a file"
		<< "\nCall:\n"
		<< argv[0] << " [path/image]\n"
		<< "\nor, read from camera:\n"
		<< argv[0]
		<< "\nFor example:\n"
		<< argv[0] << " ../tree.avi\n"
		<< std::endl;
}


int main(int argc, char** argv) {

	help(argv);



	cv::namedWindow("Example 2-10", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;

	if (argc == 1) {
		cap.open(0); // open the first camera
	}
	else {
		cap.open(argv[1]);
	}

	if (!cap.isOpened()) { // check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	cv::Mat frame;
	
	cv::Mat image(480, 640, CV_8UC3, cv::Scalar(255, 0, 0));

	int fileNum = 1;

	for (;;) {

		cap >> frame;

		if (frame.empty()) break; // Ran out of film

		cv::imshow("Example 2-10", frame);
		
		if ((char)cv::waitKey(33) == 'x') {
			
			std::string imageName = "image" + std::to_string(fileNum) + ".jpg";

			cv::imwrite(imageName, frame);

			cv::waitKey(1000);

			fileNum++;
		};
		
		if ((char)cv::waitKey(33) == 13) break;

		//13 is the value for enter

	}

	return 0;

}