/*
* @file SURF_FlannMatcher
* @brief SURF detector + descriptor + FLANN Matcher
* @author A. Huaman
*/
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
void readme();
/*
* @function main
* @brief Main function
*/
int main(int argc, char** argv)
{
	if (argc != 3)
	{
		readme(); return -1;
	}
	Mat query_img = imread(argv[1], IMREAD_GRAYSCALE);
	Mat query_rot;
	Mat rot_mat = getRotationMatrix2D(cv::Point2f(query_img.cols / 2.0, query_img.rows / 2.0), 30, 1);
	warpAffine(query_img, query_rot, rot_mat, query_img.size());//rotate image*/
	Mat template_img = imread(argv[2], IMREAD_GRAYSCALE);
	Mat matching_space,gt_matching_space;
	
	const char* gtimage_window = "Ground Truth Image";
	const char* rimage_window = "Rotated Image Window";
	const char* gtresult_window = "Ground Truth Match Space";
	const char* result_window = " Rotated Image Match Space";
	
	namedWindow(gtimage_window, WINDOW_AUTOSIZE);
	namedWindow(gtresult_window, WINDOW_AUTOSIZE);
	namedWindow(rimage_window, WINDOW_AUTOSIZE);
	namedWindow(result_window, WINDOW_AUTOSIZE);


	if (!query_img.data || !template_img.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//Create Match Space Vector for Ground Truth
	gt_matching_space.create(
		query_img.cols - template_img.cols + 1,
		query_img.rows - template_img.rows + 1,
		CV_32FC1);

	matchTemplate(query_img, template_img, gt_matching_space, CV_TM_CCORR_NORMED);
	normalize(gt_matching_space, gt_matching_space, 0, 1, NORM_MINMAX, -1, Mat());
	
	//Create MatchSpace Vector for Rotated Image
	matching_space.create(
		query_rot.cols - template_img.cols + 1,
		query_rot.rows - template_img.rows + 1,
		CV_32FC1);
	
	matchTemplate(query_rot, template_img, matching_space, CV_TM_CCORR_NORMED);
	normalize(matching_space, matching_space, 0, 1, NORM_MINMAX, -1, Mat());
	
	
	//Find ground truth rect using highest match location
	double gtminVal; double gtmaxVal; Point gtminLoc; Point gtmaxLoc;
	Point gtmatchLoc;
	minMaxLoc(gt_matching_space, &gtminVal, &gtmaxVal, &gtminLoc, &gtmaxLoc, Mat());
	gtmatchLoc = gtmaxLoc;
	Rect gtRect = Rect(gtmatchLoc, Point(gtmatchLoc.x + template_img.cols, gtmatchLoc.y + template_img.rows));
	rectangle(query_img,gtRect, Scalar::all(0), 2, 8, 0);//draw rectangle with template dimensions on rotated image
	rectangle(gt_matching_space, gtRect, Scalar::all(0), 2, 8, 0);//draw rectange with template dimensions on ground truth matchspace matrix

	//Create rotated image rect using highest match Point
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc(matching_space, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	matchLoc = maxLoc;
	Rect rRect = Rect(matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows));
	rectangle(query_rot, rRect, Scalar::all(175), 2, 8, 0);//draw rectangle with template dimensions on rotated image
	rectangle(matching_space, rRect, Scalar::all(0), 2, 8, 0);//draw rectange with template dimensions on rotated image matchspace matrix

	//Find TP,FP,FN,TN
	float TP = 0, TN = 0, FP = 0, FN = 0;	
	for (int i = 0; i < query_img.size().height; i++) {
		for (int j = 0; j < query_img.size().width; j++) {
			Point2i point(j,i);//point in query image matrix 
			//GT contains does not contain point and a A does not contain point
			if (gtRect.contains(point) == false && rRect.contains(point) == false) {
				TN++;
			}
			//GT contains point but A does not
			else if (gtRect.contains(point) && rRect.contains(point) == false) {
				FN++;
			}
			//if GT contains point and A contains Point
			else if (gtRect.contains(point) && rRect.contains(point)) {
				TP++;
			}
			//if A contains point but gt does not
			else if (gtRect.contains(point) == false && rRect.contains(point)) {
				FP++;
			}
		}
	}

	//calculate recall and precision
	float recall = 0, precision = 0;
	recall = TP / (TP + FN);
	precision = TP / (TP + FP);
	
	std::cout << "TP: " << TP << std::endl
		<< "FN: " << FN << std::endl
		<< "FP: " << FP << std::endl
		<< "TN: " << TN << std::endl
		<< "Recall: " << recall << std::endl
		<< "Precision: " << precision << std::endl
		<< " TP + FN: " << TP + FN << std::endl
		<< "Area of GT: " << gtRect.area() << std::endl;
	
	imshow(gtimage_window, query_img);
	imshow(gtresult_window, gt_matching_space);

	imshow(rimage_window, query_rot);
	imshow(result_window, matching_space);
	waitKey(0);
	return 0;
}
/*
* @function readme
*/
void readme()
{
	std::cout << " Usage: ./Lab09_02 <query_image> <template image>" << std::endl;
}