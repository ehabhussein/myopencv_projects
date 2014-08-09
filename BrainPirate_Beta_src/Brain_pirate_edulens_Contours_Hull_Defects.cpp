//
//  Brain_pirate_edulens_Contours_Hull_Defects.cpp
//  Brain_Pirate_Beta_Release
//
//  Created by Ehab Hussein on 4/21/14.
//  Copyright (c) 2014 Opencv. All rights reserved.
//

/*
 this class is responsible for drawing convexhull , contours , handgesture detection , finger counting and gesture menu . upon choice from menu
 the frame and pluginID will be sent to the class that will do the specific plugin(Brain_Pirate_built-in_plugins.h) .
 */


//Headers
#include "Brain_pirate_edulens_Contours_Hull_Defects.h"
#include <opencv2/opencv.hpp>


//Namespaces
using namespace cv;

bp_contours_hull_defects::bp_contours_hull_defects( void ) //constructor
{
}

bp_contours_hull_defects::~bp_contours_hull_defects( void ) //deconstructor
{
}

Mat
bp_contours_hull_defects::return_of_the_draw( Mat Original_cam1_feed, Mat return_contours_frame ) //#1 main method to be passed to private methods to return drawn contours
{
    //Apply a fixed-level threshold to each array element and then find the contours
    threshold( return_contours_frame, Thresholding_for_contours, 200, 255, THRESH_BINARY );
    findContours( Thresholding_for_contours, Found_contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    if ( Found_contours.size() < 1500) // if a hand is detected start the magic
    {
        for( int i = 0; i < Found_contours.size(); i++ ) // iterate through each contour if found_contour's size is > 1500.
            {
                vector<vector<Point>> hull2 ( Found_contours.size()  ); //to store points of hull
                vector<vector<Vec4i>> defects (Found_contours.size() ); //to store defect points
                vector<vector<int>> hull ( Found_contours.size() );   //  index of the convex hull points in the original array
                double needed_area=contourArea( Found_contours[i] );  //  Find the area of contour
                if(needed_area>=30000) //only draw on the detected object thats greater that this area calculated
                {
                    largest_area=needed_area; //set largest_area to be equal to the largest found area
                    largest_contour_found=i;  //Store the index of largest contour and work on it only

                    //http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=convexhull#convexhull
                    convexHull( Mat(Found_contours[largest_contour_found] ), hull[largest_contour_found], false);
             //       convexHull( Mat(Found_contours[largest_contour_found] ), hull2[largest_contour_found], false);
                
                    if ( Found_contours[largest_contour_found].size() > 3 )
                    {
                        convexityDefects( Mat( Found_contours[largest_contour_found] ), hull[largest_contour_found], defects[largest_contour_found] );
                        /*convexityDefects – The output vector of convexity defects. In C++ and the new Python/Java interface each convexity defect is represented as 4-element integer vector (a.k.a. cv::Vec4i): (start_index, end_index, farthest_pt_index, fixpt_depth), where indices are 0-based indices in the original contour of the convexity defect beginning, end and the farthest point, and fixpt_depth is fixed-point approximation (with 8 fractional bits) of the distance between the farthest contour point and the hull. That is, to get the floating-point value of the depth will be fixpt_depth/256.0. In C interface convexity defect is represented by CvConvexityDefect structure. */
                        
                    }
                    
                    for( int defectIndex=0; defectIndex < hull[largest_contour_found].size(); defectIndex++ )
                    {
                        hull_defect_index=hull[largest_contour_found][defectIndex]; // returns points of convexhull
                        hull2[largest_contour_found].push_back( Found_contours[largest_contour_found][hull_defect_index] ); //push back the points into hull2
                    }
                    
                    counter = 0; // number of fingers
                    Largest_value_FingerID = 0; //which finger
                    fingers_found = 0 ; // holds value of fingers to be used to detected closed palm if remains at value 0
                    
                    for( int defectIndex=0; defectIndex < defects[largest_contour_found].size() ; defectIndex++ )
                    {
                        
                        
                       if( defects[largest_contour_found][defectIndex][3]>20*256 ) //fixpt_depth
                        {
                            start = defects[largest_contour_found][defectIndex][0]; //start_index
                            end = defects[largest_contour_found][defectIndex][1]; //end_index
                            farthest = defects[largest_contour_found][defectIndex][2]; //farthest_pt_index

                            if ( defectIndex >= Largest_value_FingerID) //has the number of fingers increased or decreased
                            {
                                try
                                {
                                    Largest_value_FingerID = defectIndex; // set the finger with its value
                                    largest_array[counter] = Largest_value_FingerID ; //which finger is it
                                    fingerpoint_array[counter] = Found_contours[largest_contour_found][start]; // location of fingers written on end_index
                                    counter++;
                                }catch(...){std::cout << "we hate empty catch statements" << std::endl;}
                            }
                            if (defectIndex == largest_array[0]){ // First finger
                                putText( Original_cam1_feed, "First", fingerpoint_array[0], CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, 8, false );
                                fingers_found = 1;
                            }
                           else if (defectIndex == largest_array[1] ){ // Second Finger
                                putText( Original_cam1_feed, "Second", fingerpoint_array[1], CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, 8, false );
                                fingers_found = 1;
                            }
                            else if (defectIndex == largest_array[2] ){ // Third finger
                                putText( Original_cam1_feed, "Third", fingerpoint_array[2], CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, 8, false );
                                fingers_found = 1;
                            }
                            else if (defectIndex == largest_array[3] ){ // Fourth finger
                                putText( Original_cam1_feed, "Fourth", fingerpoint_array[3], CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, 8, false );
                                fingers_found = 1;
                            }
                            else if (defectIndex == largest_array[4]){ // Fifth finger
                                putText( Original_cam1_feed, "Fifth", fingerpoint_array[4], CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, 8, false );
                                fingers_found = 1;
                                circle(Original_cam1_feed, Point(1180,100), 100, color); // draw circle upper right for menu navigation
                                circle(Original_cam1_feed, Point(100,800), 100, color); // draw circle lower left for menu navigation
                                if (subcategoryTracker) // if true put subcategory name on screen
                                {
                                    putText( Original_cam1_feed, construct_plugins.getsubcat() , Point(1100,100),
                                            CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false);
                                    
                                }
                                else // get category name
                                {
                                    
                                    putText( Original_cam1_feed, construct_plugins.getcatname() , Point(1100,100),
                                            CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false);
                                }
                                if(bp_doRectangle == 1 && construct_plugins.clickdepth >=2) // draw the SELECTION on a new namedwindow that will be cropped for the plugins
                                {
                                    
                                    construct_plugins.lockselector();
                                    cp_CropdMat_toPlugins = Original_cam1_feed.clone(); //take a clone of the main frame
                                    Rect myROI(0,0,fingerpoint_array[2].x,fingerpoint_array[2].y); // select the reigon of intrest 3rd finger (x,y)
                                    cp_CropdMat_toPlugins = cp_CropdMat_toPlugins(myROI); //crop the frame
                                    imshow("Cropping area",cp_CropdMat_toPlugins); //show real-time crop area while moving hand with 5 fingers
                                    if (defectIndex < largest_array[3] && construct_plugins.clickdepth >= 4) // if less than three fingers stop cropping actions
                                                                                                             // and click depth is 4 (aka closed hand 4 times)
                                    {
                                        bp_doRectangle = 0; // lock the plugin action menu
                                        construct_plugins.selector(); // allow next menu navigation
                                        subcategoryTracker = 0; // set the subcategory index to 0
                                        construct_plugins.clickdepth = 0; // reset number of closed hand
                                    }
                                }
                            }
                            circle( Original_cam1_feed, Found_contours[largest_contour_found][start], 5, Scalar(255,0,0),-1 ); //put a circle on start_index
                            
                            circle( Original_cam1_feed, Found_contours[largest_contour_found][farthest], 5,Scalar(0,0,255),-1); //put a circle on farthest_index
                            
                            putText( Original_cam1_feed, std::to_string(defectIndex), Found_contours[largest_contour_found][farthest] , CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 1, 8, false ); // show defected index number on the farthest point
                            
                            circle( Original_cam1_feed, Found_contours[largest_contour_found][end], 5, Scalar(0,255,0),-1 ); //put a circle on end_index
                            
                            line( Original_cam1_feed, Found_contours[largest_contour_found][farthest], //draw line from farthest to start
                                 Found_contours[largest_contour_found][start], Scalar(0,0,255), 1 );
                            
                            line( Original_cam1_feed, Found_contours[largest_contour_found][farthest], // draw line from farthest to end
                                 Found_contours[largest_contour_found][end], Scalar(0,0,255), 1 );
                            
                            drawContours( Original_cam1_feed, hull2, largest_contour_found, color, 1, 8,
                                         vector<Vec4i>(), 0, Point() ); //draw the hull on the hand
                            
                        }
                        
                    }
                    std::cout << " +++++++++++++++++++++>"<<construct_plugins.clickdepth << std::endl; // how many clicks
                    if (counter <=3 ) //if 3 or less fingers detected
                    {
                        subcategoryTracker = 0; // subcategory index set to 0
                        construct_plugins.clickdepth++; // increment click
                        putText( Original_cam1_feed, construct_plugins.getsubcat() , Point(1100,100),
                                CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false); // put subcat on screen
                        drawContours( Original_cam1_feed, hull2, largest_contour_found, color, 1, 8, vector<Vec4i>(), 0, Point() ); // draw contors on hand
                        subcategoryTracker = 1;
                        if (construct_plugins.getsubcat() == "back") // when back is selected it will move back one step
                        {
                            subcategoryTracker = 0;
                        }
                        if(construct_plugins.getsubcat() != "back" && bp_doRectangle == 0)  // call the main rectangle to crop the selected area
                        {
                            construct_plugins.clickdepth++; // counter of closed hand gesture # has been done
                            construct_plugins.lockselector(); // unlock the menu
                            bp_doRectangle = 1; // set the action plugin
                        }
                        else
                        {
                            bp_doRectangle = 0; // dont do any actions
                            construct_plugins.clickdepth = 0; // reset click depths to 0
                        }
                        
                    }

                    putText( Original_cam1_feed, std::to_string(needed_area) , Point(1100,600),
                            CV_FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0,0,0), 1, 8, false ); // hand depth on screen . can be used later as Z-axis
                    putText(Original_cam1_feed,std::to_string(Found_contours[largest_contour_found].size()),
                            Point(1100,700), CV_FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0,0,0), 1, 8, false ); // size of largest_contour size should
                                                                                                        //be used later for stabilizing the contour area of hand
                    
                    if (needed_area > 310000) //if hand is moved upwards select item consuming a larger contour area
                    {
                        construct_plugins.selector(); // ensure its a one time selection
                        putText( Original_cam1_feed, "Next" , Point(1100,700),
                                CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false); //put next on top right circle
                    }

                    if (Found_contours[largest_contour_found][0].x >= 800) // if hand has moved left
                    {
                        if (construct_plugins.isSelected == 0 && comingFrom == "previous")
                        {
                            construct_plugins.selector(); // unlock menu naviagtion
                            comingFrom = "Next";

                        }
                        else
                        {
                            
                                if (subcategoryTracker) // put subcategory name
                                {
                                    putText( Original_cam1_feed, construct_plugins.getsubcat() , Point(1100,100),
                                            CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false);

                                    construct_plugins.next(); // move to next plugin name
                                }
                                else //put category item on upper circle
                                {
                                    
                                    putText( Original_cam1_feed, construct_plugins.getcatname() , Point(1100,100),
                                            CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false);
                                    subcategoryTracker = 0;
                                    construct_plugins.stepIn(); //move to next category
                                }
                        }
                    }

 
                    else if (Found_contours[largest_contour_found][0].x <= 500) // if hand moved right
                    {
                        if (construct_plugins.isSelected == 0 && comingFrom == "Next")
                        {
                            construct_plugins.selector(); // unlock menu naviagtion
                            comingFrom = "previous";

                        }
                        else
                        {
                            
                            if (subcategoryTracker) // put subcategory name
                            {
                                putText( Original_cam1_feed, construct_plugins.getsubcat() , Point(1100,100),
                                        CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false);
                                
                                construct_plugins.previous(); // move to next plugin name
                            }
                            else //put category item on upper circle
                            {
                                
                                putText( Original_cam1_feed, construct_plugins.getcatname() , Point(1100,100),
                                        CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 14, false);
                                subcategoryTracker = 0;
                                construct_plugins.stepOut(); //move to next category
                            }
                        }

                    }
                    imshow("Guesture Window",Original_cam1_feed);
                    
                }
            }
    }
    if (Found_contours.size() == 0){} // fixes a bug, when trying to free Found_contours crashes whole app. Sofinae Talmat
    else
    {
    Found_contours.clear(); // prevent from crashing when no hand isnt in screen
    }
    return Original_cam1_feed;
}
