//
//  main.cpp
//  Brain_Pirate_Beta_Release : EDU Lens
//
//  Created by Ehab Hussein on 4/19/14.
//  Twitter: @__Obzy__
//  Copyright (c) 2014 BrainPirate. All rights reserved.
//

// For the best results, use optimized compiler option of -O3
//http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
//Optimize yet more. -O3 turns on all optimizations specified by -O2 and also turns on the -finline-functions, -funswitch-loops, -fpredictive-commoning,
//-fgcse-after-reload, -ftree-loop-vectorize, -ftree-slp-vectorize, -fvect-cost-model, -ftree-partial-pre and -fipa-cp-clone options.


/*
OverView:
 
BrainPirate's Edu-Lens is a CONCEPT(needs alot of improvment since im working on this alone with limited time on my hands). This is a project that is aimed at making education more easier by optimizing how people learn from paper books. When i first thought of how i could of made google glass .. This is how i think i could of made it.
 
 EDU-Lens empowers people with :
 
    [-] Faster researching on topics
    [-] Turning Paper books into an augmeted experience
    [-] Futuristic capabilities
    [-] Voice commands and dictations allowing free hands
    [-] Checkout http://www.brainpirate.net
 
 

 Thanks to these people that helped in answering some questions:
 
 Ahmed abd el rahman
 Amr Ali
 Ilja van sprundel
 Michael Milvich
 Mike Davis
 Razib Chandra Deb
 Vincent berg
 
*/


/*
 This handles the call to the class that does skin extraction and then passes the extracted skin color and frame to the class that 
 will be incharge of drawing contours , convexhull and gesture menus
 */


//Headers
#include <iostream>
#include <opencv2/opencv.hpp> //Include all opencv headers
#include "Brain_pirate_edulens_skinextraction.h" // skin color extraction header
#include "Brain_pirate_edulens_Contours_Hull_Defects.h" //returns contours, convexhull ,defect points drawn on frame

//NameSpaces
using namespace cv;


int
main (int argc, char** argv)
{
    
    VideoCapture eduLens_capture_camera_1; //camera external
    Mat eduLens_camerafeed_1; // Used for camera 1 ( external usb cam) to make use to gesture selection
    Mat eduLens_extractedSkin_Mat_1; // Matrix holding the return value of skin color extraction from camera 1
    Mat final_contoured_frame; //will have fully drawn contours,hull,defects after return from Brain_pirate_edulens_Contours_Hull_Defects.h
    Bp_eduLens_skinExtraction Bp_eduLens_skinextract_call; // See Brain_pirate_edulens_skinextraction.h
    bp_contours_hull_defects contoured_frame; //holds return from Brain_pirate_edulens_Contours_Hull_Defects.h
    
    //set capture device to 800*600
    eduLens_capture_camera_1.set( CV_CAP_PROP_FRAME_WIDTH,800 );
    eduLens_capture_camera_1.set( CV_CAP_PROP_FRAME_HEIGHT,600 );
    
    //check camera if it could be opened
    if ( !eduLens_capture_camera_1.open(1) )  //try to open our camera 1
    {
        std::cout << "Please ensure external camera is plugged in.\nExiting...." << std::endl;
        exit( 1 ); // will force app termination
    }
    
    for ( ; ; ) 
    {
        eduLens_capture_camera_1.read( eduLens_camerafeed_1 ); //save frame to Mat from camera 1
        eduLens_extractedSkin_Mat_1 = Bp_eduLens_skinextract_call.extractskin( eduLens_camerafeed_1 ); //fetch skin color CAM 1
        final_contoured_frame = contoured_frame.return_of_the_draw( eduLens_camerafeed_1 ,eduLens_extractedSkin_Mat_1 ); //contours,convexhull,defects
        imshow("Guesture Window",eduLens_camerafeed_1); // show current frame, kills the lag when no hand is detected.
        
        if( waitKey( 30 ) == 27 ) { break; } // exit application if escape key pressed
    }
    
    return 0;
}


