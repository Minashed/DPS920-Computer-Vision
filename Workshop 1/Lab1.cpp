// Example 2-2. Same as Example 2-1 but employing the “using namespace” directive

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib" )

using namespace cv;

void help(char** argv) {
	std::cout << "\n"
		<< "2.2: Like 2.1, but 'using namespace cv: \n"
		<< argv[0] << " <path/image>\n"
		<< "For example:\n"
		<< argv[0] << " ../fruits.jpg\n"
		<< std::endl;
}


int main(int argc, char** argv) {

	if (argc != 2) {
		help(argv);
		return 0;
	}

	Mat img = imread(argv[1], -1);

	if (img.empty()) return -1;

	namedWindow("Group 12", cv::WINDOW_AUTOSIZE);

	imshow("Group 12", img);

	waitKey(3000);

	destroyWindow("Group 12");
}