//
//  Brain_pirate_edulens_skinextraction.cpp
//  Brain_Pirate_Beta_Release
//
//  Created by Ehab Hussein on 4/19/14.
//  Copyright (c) 2014 Opencv. All rights reserved.
//


/*
 This class is incharge of skin extraction and returns to main with the frame that has the detected skin that will be sent to contours, hull, defects, plugins
 */

//Headers
#include "Brain_pirate_edulens_skinextraction.h"
#include <opencv2/opencv.hpp>


//NameSpaces
using namespace cv;

//Constructor
Bp_eduLens_skinExtraction::Bp_eduLens_skinExtraction(void)
{
}


//Deconstructor
Bp_eduLens_skinExtraction::~Bp_eduLens_skinExtraction( void )
{
}

//Skin extraction method
Mat
Bp_eduLens_skinExtraction::extractskin( Mat cam1_feed )
{
    
    //convert frame to YCrCb
    cvtColor( cam1_feed, skinextraction, COLOR_BGR2YCrCb );
    
    //get skin color value which falls in this range
    inRange( skinextraction, Scalar( 0, 133, 77 ),
            Scalar( 255, 173 ,127 ), skinextraction );
    
    
    /*
    cvtColor(cam1_feed, skinextraction, COLOR_BGR2HSV);
    //get skin color value which falls in this range
    inRange( skinextraction, Scalar( 0, 150, 0 ),
            Scalar( 5, 255 ,255 ), skinextraction );*/
    
    /*
     //to create a trackbar to play with these values to adjust skin detection to your environment you can do something like:
     
     //created a window
     cv::namedWindow("ycrcb values");
     
     Mat skinextraction;
     
     //create a trackbar
     cv::createTrackbar("Y_MAX", "window", 0, 255);
     cv::createTrackbar("Y_MIN", "window", 0, 255);
     cv::createTrackbar("Cr_MIN", "window", 0, 255);
     cv::createTrackbar("Cr_MAX", "window", 0, 255);
     cv::createTrackbar("Cb_MIN", "window", 0, 255);
     cv::createTrackbar("Cb_MAX", "window", 0, 255);
     
     // in your main app's for( ; ; ){} loop you'd have something like
    int Y_MIN  = cv::getTrackbarPos("Y_MIN", "window");
    int Y_MAX  = cv::getTrackbarPos("Y_MAX", "window");
    int Cr_MIN = cv::getTrackbarPos("Cr_MIN", "window");
    int Cr_MAX = cv::getTrackbarPos("Cr_MAX", "window");
    int Cb_MIN = cv::getTrackbarPos("Cb_MIN", "window");
    int Cb_MAX = cv::getTrackbarPos("Cb_MAX", "window");
     
     cvtColor(from_extraction_camera_1, skinextraction, COLOR_BGR2YCrCb);
     inRange(from_extraction_camera_1, Scalar( Y_MIN, Cr_MIN, Cb_MIN ),
             Scalar( Y_MAX, Cr_MAX ,Cb_MAX ), skinextraction);
     imshow("ycrcb values",skinextraction);
     */

    //return mat with extracted skin color to be sent to contours , hull and get defect points
    return skinextraction;
}
