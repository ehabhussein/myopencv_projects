//
//  Brain_Pirate_built-in_plugins.h
//  Brain_Pirate_Beta_Release
//
//  Created by Ehab Hussein on 4/26/14.
//  Copyright (c) 2014 Opencv. All rights reserved.
//

#ifndef __Brain_Pirate_Beta_Release__Brain_Pirate_built_in_plugins__
#define __Brain_Pirate_Beta_Release__Brain_Pirate_built_in_plugins__

//Headers
#include <iostream>
#include <opencv2/opencv.hpp>

//Namespaces 
using namespace cv;

class
Built_in_plugins
{
    public:
        Built_in_plugins( void ); //construtor
        ~Built_in_plugins( void ); //deconstructor
        Mat bp_selectPlugin( int bp_pluginCat, int bp_pluginSubCat, Mat bp_get_text_from_image ); //main method to pass to the chosen plugin and holds passed matrix
        vector<std::string> Brain_Pirate_edulensPlugins;

    
    private:
        vector<string> bp_categoryPlugin = {"Text Processing","Image Processing","Share"}; //category of plugins
        vector <vector <std::string> > category;
        vector<std::string> textProcessingPlugins; // holds text processing plugin names
        vector<std::string> imageProcessingPlugins; // holds image processing plugin names
        vector<std::string> sharePlugins; // holds social media plugins
        vector<vector<std::string>> Menu;
        std::string plugindistributer; // arrange plugins into categories
        bool isSelected = 1; // enure that the guesture is done one time
        int cat = 0; // category tracker
        int subcat = 0; // subcategory tracker
        int clickdepth; //counter for closed palm selection
        vector<string> getcat(); // get category
        string getsubcat(); // get subcategory
        string getcatname(); //get category name
        void  stepIn(); // move to next category
        void stepOut(); //move to previous category
        void next(); // move to next plugin in selected category
        void previous(); // move to previous plugin in selected category
        void selector(); //ensure guesture is done one time
        void lockselector();
        friend class bp_contours_hull_defects; //allow access to private from this class
    
    
};

#endif /* defined(__Brain_Pirate_Beta_Release__Brain_Pirate_built_in_plugins__) */
