
// This Program is a modification of Example 9-2 in https://github.com/oreillymedia/Learning-OpenCV-3_examples. 
//Toy program for using a mouse to draw boxes on the screen
//Modified to draw circles and ellipses of a user specified colour
//& User can choose to save created image

#include "stdafx.h"
#include <opencv2/opencv.hpp>

// Define our callback which we will install for
// mouse events
//
void my_mouse_callback(

	int event, int x, int y, int flags, void* param
);

cv::Rect box;
cv::RotatedRect rotRect;
cv::Scalar colourScal;//Scalar values set when user specifies colour preference
char colour;//character to hold user colour preference
bool drawing_box = false;


// A little subroutine to draw a box onto an image
//
void draw_box(cv::Mat& img, cv::Rect box) {
	cv::rectangle(
		img,
		box.tl(),//top left(Point2i)
		box.br(),//bottom right(Point(2i)
		colourScal//cv::Scalar storing values for 3 colour channels
	);
}

void draw_circle(cv::Mat& img, cv::Rect rect) {
	int radius,cX,cY;
	cX = (rect.tl().x + rect.br().x) / 2;//mid point xvalue  
	cY = (rect.tl().y + rect.br().y) / 2;//mid point yvalue
	cv::Point2i centre(cX,cY);
	rect.height <= rect.width ? radius = rect.height/2 : radius = rect.width/2;//diameter or circle enclosed in rect is lesser of height or width or rect
																			   //radius = diameter/2
	cv::circle(img, centre, radius, colourScal, 2, 8, 0);
}

void draw_ellipse(cv::Mat& img, cv::Rect rect) {
	int cX, cY;
	cv::Point2i tr(rect.br().x, rect.tl().y);//top right point of rect(required for rotated rect construction)
	cv::RotatedRect rotRect(rect.tl(),tr,rect.br());//create rotated rect object (required for drawing ellipse)	

	cv::Size2i axis(480, 640);
	cv::ellipse(img, rotRect, colourScal, 2, 8);
}


void help(char** argv) {
	std::cout << "Example 9-2. Toy program for using a mouse to draw boxes on the screen"
		<< "\nCall:\n" << argv[0] <<
		"\n\nshows how to use a mouse to draw regions in an image. Esc to quit\n" << std::endl;
}
int main(int argc, char** argv) {
	help(argv);
	box = cv::Rect(-1, -1, 0, 0);
	cv::Mat image(480, 640, CV_8UC3), temp;
	image.copyTo(temp);
	box = cv::Rect(-1, -1, 0, 0);
	image = cv::Scalar::all(0);
	cv::namedWindow("Box Example");
	cv::moveWindow("Box Example", 10, 30);

	std::cout << "Please input a letter character for the colour of the rectangle: " << std::endl;
	std::cout << "k: black" << std::endl;
	std::cout << "w: white" << std::endl;
	std::cout << "r: red" << std::endl;
	std::cout << "g: green" << std::endl;
	std::cout << "b: blue" << std::endl;
	std::cout << "c: cyan" << std::endl;
	std::cout << "y: yellow" << std::endl;
	std::cout << "m: magenta" << std::endl;
	std::cout << "x: random" << std::endl << ">>";
	std::cin >> colour;

	if (colour == 'k') {//black
		colourScal = cv::Scalar(0, 0, 0);
	}
	else if (colour == 'w') {//white
		colourScal = cv::Scalar(255, 255, 255);
	}
	else if (colour == 'r') {//red
		colourScal = cv::Scalar(0, 0, 255);
	}
	else if (colour == 'g') {//green
		colourScal = cv::Scalar(0, 255, 0);
	}
	else if (colour == 'b') {//blue
		colourScal = cv::Scalar(255, 0, 0);
	}
	else if (colour == 'c') {//cyan
		colourScal = cv::Scalar(255, 255, 0);
	}
	else if (colour == 'y') {//yellow
		colourScal = cv::Scalar(0, 255, 255);
	}
	else if (colour == 'm') {//magenta
		colourScal = cv::Scalar(255, 0, 255);
	}
	else if (colour == 'x') {//random
		cv::RNG rng = cv::RNG(static_cast<long int>(time(NULL)));
		colourScal = cv::Scalar(rng(256), rng(256), rng(256));
	}


	
	// Here is the crucial moment where we actually install
	// the callback. Note that we set the value of 'params' to
	// be the image we are working with so that the callback
	// will have the image to edit.
	//
	cv::setMouseCallback(
		"Box Example",//window name
		my_mouse_callback,//custom mouse call back function
		(void*)&image 
	);

	
	// The main program loop. Here we copy the working image
	// to the temp image, and if the user is drawing, then
	// put the currently contemplated box onto that temp image.
	// Display the temp image, and wait 15ms for a keystroke,
	// then repeat.
	//
	for (;;) {
		image.copyTo(temp);
		if (drawing_box) draw_box(temp, box);

		cv::imshow("Box Example", temp);
		if (cv::waitKey(15) == 27) {
			std::cout << "Save image? Press y for yes or any other key to quit" << std::endl << ">>";
			std::cin >> colour;
			if (colour == 'y') {
				int baseLine;//output parameter for cv::getTextSize
				putText(image, "My Drawing Application", cv::Point2i(240, 40), CV_FONT_HERSHEY_SCRIPT_SIMPLEX,1,colourScal,1);//write text to image
				cv::Size textSize = cv::getTextSize("My Drawing Application", CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 1, 1, &baseLine);
				cv::line(image, cv::Point2i(240,baseLine+40), cv::Point2i(240+textSize.width, baseLine+40), cv::Scalar(0, 0, 255), 1, 8, 0);//draw baseline
				cv::imwrite("MyDrawing.jpg", image);
			}
			break;
		}
			
	}
	return 0;
}

// This is our mouse callback. If the user
// presses the left button, we start a box.
// When the user releases that button, then we
// add the box to the current image. When the
// mouse is dragged (with the button down) we
// resize the box.
//
void my_mouse_callback(
	int event, int x, int y, int flags, void* param)
{
	cv::Mat& image = *(cv::Mat*) param;
	switch (event) {
		case cv::EVENT_MOUSEMOVE: {
			if (drawing_box) {
				box.width = x - box.x;
				box.height = y - box.y;
			}
		}
		break;

		case cv::EVENT_LBUTTONDOWN: {
			drawing_box = true;
			box = cv::Rect(x, y, 0, 0);
		}
		break;

		case cv::EVENT_LBUTTONUP: {
			drawing_box = false;
			if (box.width < 0) {

				box.x += box.width;
				box.width *= -1;
			}
			if (box.height < 0) {
				box.y += box.height;
				box.height *= -1;
			}
			if (!flags) {
				draw_box(image, box);
			}
			else if (flags == CV_EVENT_FLAG_SHIFTKEY) {
				draw_circle(image,box);
			}
			else if (flags = CV_EVENT_FLAG_CTRLKEY) {
				draw_ellipse(image, box);
			}
		}
		break;
	}

}