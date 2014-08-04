//
//  Brain_pirate_edulens_Contours_Hull_Defects.h
//  Brain_Pirate_Beta_Release
//
//  Created by Ehab Hussein on 4/21/14.
//  Copyright (c) 2014 Opencv. All rights reserved.
//

#ifndef __Brain_Pirate_Beta_Release__Brain_pirate_edulens_Contours_Hull_Defects__
#define __Brain_Pirate_Beta_Release__Brain_pirate_edulens_Contours_Hull_Defects__

//Headers
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Brain_Pirate_built-in_plugins.h" //plugins setup and usage


//Namespace
using namespace cv;

class
bp_contours_hull_defects
{
    
    public:
        bp_contours_hull_defects( void ); //class constructor
        ~bp_contours_hull_defects( void ); //class deconstructor
        Mat return_of_the_draw( Mat Original_cam0_feed, Mat return_contours_frame ); //class to return a matrix with convexhull, defects & contours
    
    private:
        RNG rng = rng( 31337 ); //random colorize for contour drawing
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) ); // colorize
        Point fingerpoint_array[100]; //store points of fingertips
        Point last_contour; //last found largest contour
        Mat threshold_output; //set by threshold()
        Mat final_processed_matrix_with_drawing; //final matrix with contours returned to main.cpp
        Mat Thresholding_for_contours; //output for threshold()
        Mat cp_CropdMat_toPlugins; // final cropped img matrix that will be sent to plugins 
        vector< vector<Point> >  Found_contours; // vector container of Points to hold contours
        vector< Vec4i > hierarchy; // vector containing information about the frame topology
        vector<string> bp_categoryPlugin = {"Text Processing","Image Processing","Share"}; //category of plugins
        int counter = 0; // count the fingers
        int Largest_value_FingerID =  0; // FingerID (first,second,third,fourth,fifth)
        int largest_area; // largest contour found
        int largest_contour_found; //largest contour area found
        int hull_defect_index; // index of defects
        int fingers_found; // number of fingers found
        int largest_array[10]; // which fingers found
        int start; // defect points start_index
        int end; // defect points end_index
        int farthest; //defect point farthest point from hull
        bool bp_doRectangle; // main rectangle task is to crop frames to be sent to plugins
        bool subcategoryTracker = 0 ; // index of subcategory plugin
        Built_in_plugins construct_plugins; //setup and use plugins
        std::string comingFrom = "Next"; //where did i come from next or previous (locking mechanism)
    
};

#endif /* defined(__Brain_Pirate_Beta_Release__Brain_pirate_edulens_Contours_Hull_Defects__) */
