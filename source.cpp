
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/gpu/gpu.hpp>

#include<iostream>
#include<conio.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include<stdio.h>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iomanip>  




template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}


std::string tail(std::string const& source, size_t const length) {
	if (length >= source.size()) { return source; }
	return source.substr(source.size() - length);
} // tail





double ColourDistance(cv::Scalar e1, cv::Scalar e2)
{
	long rmean = ((long)e1[2] + (long)e2[2]) / 2;
	long r = (long)e1[2] - (long)e2[2];
	long g = (long)e1[1] - (long)e2[1];
	long b = (long)e1[0] - (long)e2[0];
	return sqrt((((512 + rmean)*r*r) >> 8) + 4 * g*g + (((767 - rmean)*b*b) >> 8));
}



//to obtain the RGB-approx euclidean distance measure
int main()
{

	std::stringstream ss;
	std::ofstream myfile;
	//myfile.open("LAB_distance.txt");
	myfile.open("colorIndexes.txt");




	// writing into HTML table file format
	myfile << "<head><body>\n";
	myfile << "<table><tr><th>Color Ref</th><th>H, S, V</th><th>Distance Mode</th><th>Black</th><th>Blue</th><th>Brown</th><th>Gray</th><th>Green</th><th>Orange</th><th>Pink</th><th>Purple</th><th>Red</th><th>White</th><th>Yellow</th></tr>\n";



	cv::Mat temp_mat1 = cv::Mat::zeros(10, 10, CV_8UC3);
	cv::Mat temp_mat2 = cv::Mat::zeros(10, 10, CV_8UC3);


	cv::Mat temp_mat3 = cv::Mat::zeros(10, 10, CV_8UC3);
	cv::Mat temp_mat4 = cv::Mat::zeros(10, 10, CV_8UC3);



	int postiveCount = 0;


	//cv::Scalar avg_scalar1 = Black;
	//cv::Scalar avg_scalar2 = White;

	cv::Scalar avg_scalar1 = (255,255,255);
	cv::Scalar avg_scalar2 = (0,0,0);


	double L1, L2, a1, a2, b1, b2;

	L1 = avg_scalar1[0];
	L2 = avg_scalar2[0];

	a1 = avg_scalar1[1];
	a2 = avg_scalar2[1];

	b1 = avg_scalar1[2];
	b2 = avg_scalar2[2];


	double thisL, thisA, thisB;
	double max_distance = sqrt(pow((L1 - L2), 2) + pow((a1 - a2), 2) + pow((b1 - b2), 2));

	std::cout << "*****************************************" << std::endl;
	std::cout << "Max_distance: " << max_distance << std::endl;
	std::cout << "*****************************************" << std::endl;

	std::cout << std::endl;

	//make a loop for all the various HSV colors possibilities & compare the colors

	//H loop
	for (int h = 0; h < 15; h++)
	{
		for (int s = 0; s < 8; s++)
		{
			for (int v = 0; v < 8; v++)
			{
				// set "ground truth" of values based on the values from https://blog.xkcd.com/2010/05/03/color-survey-results/
				
				cv::Scalar Black = cv::Scalar(0.0, 0.0, 0.0);					   // Black	
				cv::Scalar White = cv::Scalar(255.0, 255.0, 255.0);				   // White	
				cv::Scalar Gray = cv::Scalar(145.0, 149.0, 146.0);				   // Gray		
				cv::Scalar Red = cv::Scalar(0.0, 0.0, 229.0);					   // Red		
				cv::Scalar Green = cv::Scalar(26.0, 176.0, 21.0);				   // Green	
				cv::Scalar Blue = cv::Scalar(223.0, 67.0, 3.0);					   // Blue		
				cv::Scalar Yellow = cv::Scalar(20.0, 255.0, 255.0);				   // Yellow	
				cv::Scalar Orange = cv::Scalar(6.0, 115.0, 249.0);				   // Orange	
				cv::Scalar Pink = cv::Scalar(192.0, 129.0, 255.0);				   // Pink		
				cv::Scalar Purple = cv::Scalar(156.0, 30.0, 126.0);				   // Purple	
				cv::Scalar Brown = cv::Scalar(0.0, 55.0, 101.0);				   // Brown	

				cv::Scalar thisColor, AvgColorScalar;
				thisColor[0] = h*12 + 6;
				thisColor[1] = s*32 + 16;
				thisColor[2] = v*32 + 16;

				temp_mat1 = thisColor;

				cvtColor(temp_mat1, temp_mat3, CV_HSV2BGR);

				thisColor = cv::mean(temp_mat3);

				thisL = thisColor[0];
				thisA = thisColor[1];
				thisB = thisColor[2];

				
				//RGB distance
				// ***********************************************************************************************************************
				double RGBdistance_to_Black	= ((max_distance - ColourDistance(Black	, thisColor)	)	/ max_distance)*100;
				double RGBdistance_to_White	= ((max_distance - ColourDistance(White	, thisColor)	)	/ max_distance)*100;
				double RGBdistance_to_Gray		= ((max_distance - ColourDistance(Gray		, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Red		= ((max_distance - ColourDistance(Red		, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Green	= ((max_distance - ColourDistance(Green	, thisColor)	)	/ max_distance)*100;
				double RGBdistance_to_Blue		= ((max_distance - ColourDistance(Blue		, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Yellow	= ((max_distance - ColourDistance(Yellow	, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Orange	= ((max_distance - ColourDistance(Orange	, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Pink		= ((max_distance - ColourDistance(Pink		, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Purple	= ((max_distance - ColourDistance(Purple	, thisColor))	/ max_distance)*100;
				double RGBdistance_to_Brown	= ((max_distance - ColourDistance(Brown	, thisColor)	)	/ max_distance)*100;


				if( RGBdistance_to_Black	   < 0) {	RGBdistance_to_Black = 0.0; }
				if (RGBdistance_to_White	   < 0) {	RGBdistance_to_White = 0.0; }
				if (RGBdistance_to_Gray	   < 0) {		RGBdistance_to_Gray = 0.0; }
				if (RGBdistance_to_Red		   < 0) {	RGBdistance_to_Red = 0.0; }
				if (RGBdistance_to_Green	   < 0) {	RGBdistance_to_Green = 0.0; }
				if (RGBdistance_to_Blue	   < 0) {		RGBdistance_to_Blue = 0.0; }
				if (RGBdistance_to_Yellow	   < 0) {	RGBdistance_to_Yellow = 0.0; }
				if (RGBdistance_to_Orange	   < 0) {	RGBdistance_to_Orange = 0.0; }
				if (RGBdistance_to_Pink	   < 0) {		RGBdistance_to_Pink = 0.0; }
				if (RGBdistance_to_Purple	   < 0) {	RGBdistance_to_Purple = 0.0; }
				if (RGBdistance_to_Brown	   < 0) {	RGBdistance_to_Brown =0.0; }
				// ***********************************************************************************************************************




				//HSV distance
				// ***********************************************************************************************************************

				thisColor = cv::mean(temp_mat1);
				max_distance = sqrt(pow((179), 2) + pow((255), 2) + pow((255), 2));

				thisL = thisColor[0];
				thisA = thisColor[1];
				thisB = thisColor[2];


				cv::Mat temp_mat99 = cv::Mat::zeros(10, 10, CV_8UC3);
				cv::Mat temp_mat99_new = cv::Mat::zeros(10, 10, CV_8UC3);

				temp_mat99 = Black	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Black = cv::mean(temp_mat99_new);

				temp_mat99 = White	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				White = cv::mean(temp_mat99_new);

				temp_mat99 = Gray	;	
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Gray = cv::mean(temp_mat99_new);
				
				temp_mat99 = Red	;	
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Red = cv::mean(temp_mat99_new);

				temp_mat99 = Green	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Green = cv::mean(temp_mat99_new);

				temp_mat99 = Blue	;	
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Blue = cv::mean(temp_mat99_new);

				temp_mat99 = Yellow	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Yellow = cv::mean(temp_mat99_new);
				
				temp_mat99 = Orange	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Orange = cv::mean(temp_mat99_new);
				
				temp_mat99 = Pink	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Pink = cv::mean(temp_mat99_new);
				
				temp_mat99 = Purple	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Purple = cv::mean(temp_mat99_new);
				
				temp_mat99 = Brown	;
				cvtColor(temp_mat99, temp_mat99_new, CV_BGR2HSV);
				Brown = cv::mean(temp_mat99_new);




				double newBlack = std::min(abs(Black[0] - thisL), 180 - abs(Black[0] - thisL));
				double newWhite = std::min(abs(White[0] - thisL), 180 - abs(White[0] - thisL));
				double newGray = std::min(abs(Gray[0] - thisL), 180 - abs(Gray[0] - thisL));
				double newRed = std::min(abs(Red[0] - thisL), 180 - abs(Red[0] - thisL));
				double newGreen = std::min(abs(Green[0] - thisL), 180 - abs(Green[0] - thisL));
				double newBlue = std::min(abs(Blue[0] - thisL), 180 - abs(Blue[0] - thisL));
				double newYellow = std::min(abs(Yellow[0] - thisL), 180 - abs(Yellow[0] - thisL));
				double newOrange = std::min(abs(Orange[0] - thisL), 180 - abs(Orange[0] - thisL));
				double newPink = std::min(abs(Pink[0] - thisL), 180 - abs(Pink[0] - thisL));
				double newPurple = std::min(abs(Purple[0] - thisL), 180 - abs(Purple[0] - thisL));
				double newBrown = std::min(abs(Brown[0] - thisL), 180 - abs(Brown[0] - thisL));

				double HSVdistance_to_Black = pow(((max_distance - sqrt(pow((newBlack), 2) + pow((Black[1] - thisA), 2) + pow((Black[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_White = pow(((max_distance - sqrt(pow((newWhite), 2) + pow((White[1] - thisA), 2) + pow((White[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Gray = pow(((max_distance - sqrt(pow((newGray), 2) + pow((Gray[1] - thisA), 2) + pow((Gray[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Red = pow(((max_distance - sqrt(pow((newRed), 2) + pow((Red[1] - thisA), 2) + pow((Red[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Green = pow(((max_distance - sqrt(pow((newGreen), 2) + pow((Green[1] - thisA), 2) + pow((Green[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Blue = pow(((max_distance - sqrt(pow((newBlue), 2) + pow((Blue[1] - thisA), 2) + pow((Blue[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Yellow = pow(((max_distance - sqrt(pow((newYellow), 2) + pow((Yellow[1] - thisA), 2) + pow((Yellow[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Orange = pow(((max_distance - sqrt(pow((newOrange), 2) + pow((Orange[1] - thisA), 2) + pow((Orange[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Pink = pow(((max_distance - sqrt(pow((newPink), 2) + pow((Pink[1] - thisA), 2) + pow((Pink[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Purple = pow(((max_distance - sqrt(pow((newPurple), 2) + pow((Purple[1] - thisA), 2) + pow((Purple[2] - thisB), 2))) / max_distance), 1) * 100;
				double HSVdistance_to_Brown = pow(((max_distance - sqrt(pow((newBrown), 2) + pow((Brown[1] - thisA), 2) + pow((Brown[2] - thisB), 2))) / max_distance), 1) * 100;

				if (HSVdistance_to_Black	   < 0) { HSVdistance_to_Black = 0.0; }
				if (HSVdistance_to_White	   < 0) { HSVdistance_to_White = 0.0; }
				if (HSVdistance_to_Gray	   < 0) { HSVdistance_to_Gray = 0.0; }
				if (HSVdistance_to_Red		   < 0) { HSVdistance_to_Red = 0.0; }
				if (HSVdistance_to_Green	   < 0) { HSVdistance_to_Green = 0.0; }
				if (HSVdistance_to_Blue	   < 0) { HSVdistance_to_Blue = 0.0; }
				if (HSVdistance_to_Yellow	   < 0) { HSVdistance_to_Yellow = 0.0; }
				if (HSVdistance_to_Orange	   < 0) { HSVdistance_to_Orange = 0.0; }
				if (HSVdistance_to_Pink	   < 0) { HSVdistance_to_Pink = 0.0; }
				if (HSVdistance_to_Purple	   < 0) { HSVdistance_to_Purple = 0.0; }
				if (HSVdistance_to_Brown	   < 0) { HSVdistance_to_Brown = 0.0; }
				// ***********************************************************************************************************************



				//LAB
				// ***********************************************************************************************************************


				cvtColor(temp_mat3, temp_mat1, CV_BGR2Lab);

				thisColor = cv::mean(temp_mat1);
				max_distance = sqrt(pow((255), 2) + pow((255), 2) + pow((255), 2));

				thisL = thisColor[0];
				thisA = thisColor[1];
				thisB = thisColor[2];

				Black = cv::Scalar(0.0, 0.0, 0.0);						// Black	
				White = cv::Scalar(255.0, 255.0, 255.0);				   // White	
				Gray = cv::Scalar(145.0, 149.0, 146.0);				   // Gray		
				Red = cv::Scalar(0.0, 0.0, 229.0);					   // Red		
				Green = cv::Scalar(26.0, 176.0, 21.0);				   // Green	
				Blue = cv::Scalar(223.0, 67.0, 3.0);					   // Blue		
				Yellow = cv::Scalar(20.0, 255.0, 255.0);				   // Yellow	
				Orange = cv::Scalar(6.0, 115.0, 249.0);				   // Orange	
				Pink = cv::Scalar(192.0, 129.0, 255.0);				   // Pink		
				Purple = cv::Scalar(156.0, 30.0, 126.0);				   // Purple	
				Brown = cv::Scalar(0.0, 55.0, 101.0);						// Brown	

				cv::Mat temp_mat88 = cv::Mat::zeros(10, 10, CV_8UC3);
				cv::Mat temp_mat88_new = cv::Mat::zeros(10, 10, CV_8UC3);

				temp_mat88 = Black;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Black = cv::mean(temp_mat88_new);

				temp_mat88 = White;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				White = cv::mean(temp_mat88_new);

				temp_mat88 = Gray;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Gray = cv::mean(temp_mat88_new);

				temp_mat88 = Red;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Red = cv::mean(temp_mat88_new);

				temp_mat88 = Green;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Green = cv::mean(temp_mat88_new);

				temp_mat88 = Blue;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Blue = cv::mean(temp_mat88_new);

				temp_mat88 = Yellow;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Yellow = cv::mean(temp_mat88_new);

				temp_mat88 = Orange;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Orange = cv::mean(temp_mat88_new);

				temp_mat88 = Pink;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Pink = cv::mean(temp_mat88_new);

				temp_mat88 = Purple;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Purple = cv::mean(temp_mat88_new);

				temp_mat88 = Brown;
				cvtColor(temp_mat88, temp_mat88_new, CV_BGR2Lab);
				Brown = cv::mean(temp_mat88_new);




				double LABdistance_to_Black = pow(((max_distance - sqrt(pow((	Black[0] - thisL	), 2) + pow((Black[1] - thisA), 2) + pow((Black[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_White = pow(((max_distance - sqrt(pow((	White[0] - thisL	), 2) + pow((White[1] - thisA), 2) + pow((White[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Gray = pow(((max_distance - sqrt(pow((	Gray[0] - thisL		), 2) + pow((Gray[1] - thisA), 2) + pow((Gray[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Red = pow(((max_distance - sqrt(pow((		Red[0] - thisL		), 2) + pow((Red[1] - thisA), 2) + pow((Red[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Green = pow(((max_distance - sqrt(pow((	Green[0] - thisL	), 2) + pow((Green[1] - thisA), 2) + pow((Green[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Blue = pow(((max_distance - sqrt(pow((	Blue[0] - thisL		), 2) + pow((Blue[1] - thisA), 2) + pow((Blue[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Yellow = pow(((max_distance - sqrt(pow((	Yellow[0] - thisL	), 2) + pow((Yellow[1] - thisA), 2) + pow((Yellow[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Orange = pow(((max_distance - sqrt(pow((	Orange[0] - thisL	), 2) + pow((Orange[1] - thisA), 2) + pow((Orange[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Pink = pow(((max_distance - sqrt(pow((	Pink[0] - thisL		), 2) + pow((Pink[1] - thisA), 2) + pow((Pink[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Purple = pow(((max_distance - sqrt(pow((	Purple[0] - thisL	), 2) + pow((Purple[1] - thisA), 2) + pow((Purple[2] - thisB), 2))) / max_distance), 1) * 100;
				double LABdistance_to_Brown = pow(((max_distance - sqrt(pow((	Brown[0] - thisL	), 2) + pow((Brown[1] - thisA), 2) + pow((Brown[2] - thisB), 2))) / max_distance), 1) * 100;

				if (LABdistance_to_Black	   < 0) { LABdistance_to_Black = 0.0; }
				if (LABdistance_to_White	   < 0) { LABdistance_to_White = 0.0; }
				if (LABdistance_to_Gray	   < 0) { LABdistance_to_Gray = 0.0; }
				if (LABdistance_to_Red		   < 0) { LABdistance_to_Red = 0.0; }
				if (LABdistance_to_Green	   < 0) { LABdistance_to_Green = 0.0; }
				if (LABdistance_to_Blue	   < 0) { LABdistance_to_Blue = 0.0; }
				if (LABdistance_to_Yellow	   < 0) { LABdistance_to_Yellow = 0.0; }
				if (LABdistance_to_Orange	   < 0) { LABdistance_to_Orange = 0.0; }
				if (LABdistance_to_Pink	   < 0) { LABdistance_to_Pink = 0.0; }
				if (LABdistance_to_Purple	   < 0) { LABdistance_to_Purple = 0.0; }
				if (LABdistance_to_Brown	   < 0) { LABdistance_to_Brown = 0.0; }
				// ***********************************************************************************************************************




				
							
				
								AvgColorScalar = cv::mean(temp_mat3);
								cv::resize(temp_mat3, temp_mat3, cv::Size(), 10, 10, cv::INTER_LINEAR);
								
								/*std::cout << h << "," << s << "," << v << std::endl;*/
								std::cout << "Current HSV: " << h << ", " << s << ", " << v << std::endl;
								//std::cout << std::setw(5) << "ASM" << std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Black:	" << RGBdistance_to_Black	<<"	,	" << LABdistance_to_Black	<< "	,	" << HSVdistance_to_Black		<< "	[ " <<(RGBdistance_to_Black + LABdistance_to_Black + HSVdistance_to_Black) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_White:	" << RGBdistance_to_White	<<"	,	" << LABdistance_to_White	<< "	,	" << HSVdistance_to_White		<< "	[ " <<(RGBdistance_to_White + LABdistance_to_White + HSVdistance_to_White) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Gray:	" << RGBdistance_to_Gray		<<"	,	" << LABdistance_to_Gray	<< "	,	" << HSVdistance_to_Gray	<< "	[ " <<(RGBdistance_to_Gray + LABdistance_to_Gray + HSVdistance_to_Gray) / 3<< " ]" <<std::endl << std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Pink:	" << RGBdistance_to_Pink		<<"	,	" << LABdistance_to_Red	<< "	,	" << HSVdistance_to_Red			<< "	[ " <<(RGBdistance_to_Pink + LABdistance_to_Red + HSVdistance_to_Red) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Red:		" << RGBdistance_to_Red			<<"	,	" << LABdistance_to_Green	<< "	,	" << HSVdistance_to_Green	<< "	[ " <<(RGBdistance_to_Red + LABdistance_to_Green + HSVdistance_to_Green) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Brown:	" << RGBdistance_to_Brown	<<"	,	" << LABdistance_to_Blue	<< "	,	" << HSVdistance_to_Blue		<< "	[ " <<(RGBdistance_to_Brown + LABdistance_to_Blue + HSVdistance_to_Blue) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Orange:	" << RGBdistance_to_Orange	<<"	,	" << LABdistance_to_Yellow	<< "	,	" << HSVdistance_to_Yellow	<< "	[ " <<(RGBdistance_to_Orange + LABdistance_to_Yellow + HSVdistance_to_Yellow) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Yellow:	" << RGBdistance_to_Yellow	<<"	,	" << LABdistance_to_Orange	<< "	,	" << HSVdistance_to_Orange	<< "	[ " <<(RGBdistance_to_Yellow + LABdistance_to_Orange + HSVdistance_to_Orange) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Green:	" << RGBdistance_to_Green	<<"	,	" << LABdistance_to_Pink	<< "	,	" << HSVdistance_to_Pink		<< "	[ " <<(RGBdistance_to_Green + LABdistance_to_Pink + HSVdistance_to_Pink) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Blue:	" << RGBdistance_to_Blue		<<"	,	" << LABdistance_to_Purple	<< "	,	" << HSVdistance_to_Purple	<< "	[ " <<(RGBdistance_to_Blue + LABdistance_to_Purple + HSVdistance_to_Purple) / 3<< " ]" <<std::endl;
								std::cout << "[RGB, LAB, HSV, [AVG]] distance_to_Purple:	" << RGBdistance_to_Purple	<<"	,	" << LABdistance_to_Brown	<< "	,	" << HSVdistance_to_Brown	<< "	[ " <<(RGBdistance_to_Purple + LABdistance_to_Brown + HSVdistance_to_Brown) / 3<< " ]" <<std::endl;
								

								
								std::string name = "img_";
								std::string type = ".jpg";

								ss << "960HSVimages" << "/" << name << h << "_" << s << "_" << v << type;
								std::string fullPath = ss.str();
								ss.str("");

								std::string temp_hsvVal;

								temp_hsvVal = std::to_string(h) + "," + std::to_string(s) + "," + std::to_string(v);

								imwrite(fullPath, temp_mat3);
								
								myfile << "<tr><td rowspan='4'><img src='" + fullPath + "'>			</td><td rowspan='4'>" + temp_hsvVal + "			</td><td>RGB			</td><td>" + std::to_string(RGBdistance_to_Black) + "	</td>        <td>" + std::to_string(RGBdistance_to_Blue) + "	</td>        <td>" + std::to_string(RGBdistance_to_Brown) + "		</td>        <td>" + std::to_string(RGBdistance_to_Gray) + "	</td>        <td>" + std::to_string(RGBdistance_to_Green) + "		</td>        <td>" + std::to_string(RGBdistance_to_Orange) + "		</td>        <td>" + std::to_string(RGBdistance_to_Pink) + "	</td>        <td>" + std::to_string(RGBdistance_to_Purple) + "		</td>        <td>" + std::to_string(RGBdistance_to_Red) + "	</td>        <td>" + std::to_string(RGBdistance_to_White) + "		</td>        <td>" + std::to_string(RGBdistance_to_Yellow) + "		</td>    </tr>    <tr>    	<td>Lab			</td>        <td>" + std::to_string(LABdistance_to_Black) + "		</td>        <td>" + std::to_string(LABdistance_to_Blue) + "	</td>        <td>" + std::to_string(LABdistance_to_Brown) + "		</td>        <td>" + std::to_string(LABdistance_to_Gray) + "	</td>        <td>" + std::to_string(LABdistance_to_Green) + "		</td>        <td>" + std::to_string(LABdistance_to_Orange) + "		</td>        <td>" + std::to_string(LABdistance_to_Pink) + "	</td>        <td>" + std::to_string(LABdistance_to_Purple) + "		</td>        <td>" + std::to_string(LABdistance_to_Red) + "	</td>        <td>" + std::to_string(LABdistance_to_White) + "		</td>        <td>" + std::to_string(LABdistance_to_Yellow) + "		</td>    </tr>    <tr>    	<td>HSV			</td>        <td>" + std::to_string(HSVdistance_to_Black) + "		</td>        <td>" + std::to_string(HSVdistance_to_Blue) + "	</td>        <td>" + std::to_string(HSVdistance_to_Brown) + "		</td>        <td>" + std::to_string(HSVdistance_to_Gray) + "	</td>        <td>" + std::to_string(HSVdistance_to_Green) + "		</td>        <td>" + std::to_string(HSVdistance_to_Orange) + "		</td>        <td>" + std::to_string(HSVdistance_to_Pink) + "	</td>        <td>" + std::to_string(HSVdistance_to_Purple) + "		</td>        <td>" + std::to_string(HSVdistance_to_Red) + "	</td>        <td>" + std::to_string(HSVdistance_to_White) + "		</td>        <td>" + std::to_string(HSVdistance_to_Yellow) + "		</td>    </tr>    <tr>    	<td>Average			</td>        <td>" + std::to_string((RGBdistance_to_Black + LABdistance_to_Black + HSVdistance_to_Black) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Blue + LABdistance_to_Blue + HSVdistance_to_Blue) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Brown + LABdistance_to_Brown + HSVdistance_to_Brown) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Gray + LABdistance_to_Gray + HSVdistance_to_Gray) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Green + LABdistance_to_Green + HSVdistance_to_Green) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Orange + LABdistance_to_Orange + HSVdistance_to_Orange) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Pink + LABdistance_to_Pink + HSVdistance_to_Pink) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Purple + LABdistance_to_Purple + HSVdistance_to_Purple) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Red + LABdistance_to_Red + HSVdistance_to_Red) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_White + LABdistance_to_White + HSVdistance_to_White) / 3) + "	</td>        <td>" + std::to_string((RGBdistance_to_Yellow + LABdistance_to_Yellow + HSVdistance_to_Yellow) / 3) + "	</td>    </tr>\n";



								std::cout << "**********************************" <<  std::endl;
								/*cv::imshow("color", temp_mat3);
								cv::waitKey(1);*/


			}
			
		}
	}

	myfile << postiveCount << "\n";



	myfile.close();


	return 0;
}
