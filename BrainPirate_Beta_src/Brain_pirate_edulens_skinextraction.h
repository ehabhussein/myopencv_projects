//
//  Brain_pirate_edulens_skinextraction.h
//  Brain_Pirate_Beta_Release
//
//  Created by Ehab Hussein on 4/19/14.
//  Copyright (c) 2014 Opencv. All rights reserved.
//

#ifndef __Brain_Pirate_Beta_Release__Brain_pirate_edulens_skinextraction__
#define __Brain_Pirate_Beta_Release__Brain_pirate_edulens_skinextraction__


//Headers
#include <iostream>
#include <opencv/cv.h>


//Namespaces
using namespace cv;


//the class to extract skin color
class
Bp_eduLens_skinExtraction
{
    
    public:
        Bp_eduLens_skinExtraction( void ); //class constructor
        ~Bp_eduLens_skinExtraction( void ); //class deconstructor
        Mat extractskin( Mat cam1_feed ); //extract skin method prototype
    
    private:
        //Matrix that will be returned to main.cpp after skin extraction is complete
        Mat skinextraction;
};

#endif /* defined(__Brain_Pirate_Beta_Release__Brain_pirate_edulens_skinextraction__) */
