//
//  Brain_Pirate_built-in_plugins.cpp
//  Brain_Pirate_Beta_Release
//
//  Created by Ehab Hussein on 4/26/14.
//  Copyright (c) 2014 Opencv. All rights reserved.
//

/*
 This class will hold the entire built-in plugins which will be performed via the chosen gesture from Brain_pirate_edulens_Contours_Hull_defects.cpp .
 */

//Headers
#include "Brain_Pirate_built-in_plugins.h"
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp> //boost::filesystem to iterate over plugin directory
                                //$ sudo port install boost
                                // add these libs to Brain_Pirate_lib_Deps:
                                // libboost_signals-mt.dylib , libboost_system-mt.dylib , libboos_filesystem-mt.dylib


/*
 this class is incharge of setting up and using the plugins
 */

//Namespaces
using namespace cv;

Built_in_plugins::Built_in_plugins( void ) //construtor
{
    std::cout << "Setting up plugins" << std::endl;
    boost::filesystem::directory_iterator pluginFinder( string( "./plugins/" ) ); //use this path to enumerate plugins
    for(; pluginFinder != boost::filesystem::directory_iterator(); ++pluginFinder)
    {
        if ( pluginFinder->path().extension() == ".dylib" ) //look for .dylib extentions
            Brain_Pirate_edulensPlugins.push_back( pluginFinder->path().filename().string() ); //push results into vector to add in gesture menu
    }
    if( Brain_Pirate_edulensPlugins.size() <= 0 )
    {
        std::cout << "No plugins found" << std::endl;
          exit( -1 ); // if no plugins found exit
    }
        
    for( int i = 0; i < Brain_Pirate_edulensPlugins.size() ; i++ )
    {
        
        plugindistributer = Brain_Pirate_edulensPlugins[i][0]; //holder for first character of library name (T or I)
        if ( plugindistributer == "T" ) //text processing plugin filenames beginning with T [ex: TcopyTextClipboard.dylib]
        {
            std::cout << "Found Text plugin" << std::endl;
            textProcessingPlugins.push_back( Brain_Pirate_edulensPlugins[i] ); //text plugin names
        }
        else if ( plugindistributer == "I" ) //image processing plugin filenames beging with I [ex: IgoogleImageSearch.dylib]
        {
            std::cout << "Found Image plugin" << std::endl;
            imageProcessingPlugins.push_back( Brain_Pirate_edulensPlugins[i] ); //image plugin names
        }
        else if ( plugindistributer == "S" ) //social media plugin filenames beging with S [ex: Stwitter.dylib]
        {
            std::cout << "Found SocialMedia plugin" << std::endl;
            sharePlugins.push_back( Brain_Pirate_edulensPlugins[i] ); //share plugin names
        }

    }
    textProcessingPlugins.push_back("back"); // add go back navigation
    imageProcessingPlugins.push_back("back");// add go back navigation
    sharePlugins.push_back("back");// add go back navigation
    category.push_back(textProcessingPlugins); // push text plugins
    category.push_back(imageProcessingPlugins); // push image plugins
    category.push_back(sharePlugins); //push share plugins
}

Built_in_plugins::~Built_in_plugins( void ) //deconstructor
{

}

Mat
Built_in_plugins::bp_selectPlugin( int bp_pluginCat, int bp_pluginSubCat, Mat bp_get_text_from_image ) // the magic happens here
{
    
    return bp_get_text_from_image;
}

void Built_in_plugins::selector() //ensure the gesture is done only one time
{
    
    isSelected = 1 ;

}

vector<string> Built_in_plugins::getcat() //get category
{
    return category[cat];
    
}

string
Built_in_plugins::getsubcat()  //get subcategory
{
    return category[cat][subcat];
    
}

void
Built_in_plugins::stepIn() //move to next category
{
    
    if (isSelected)
    {
        cat++;
        isSelected = 0;
    }
    if (cat > category.size() -1)
    {
        cat = 0;
    }
}

void
Built_in_plugins::stepOut() // move to previous category
{
    
    if (isSelected)
    {
        cat--;
        isSelected = 0;
    }
    if (cat < 0)
    {
        cat = (int) category.size() - 1;
    }
}

void
Built_in_plugins::next() //move to next plugin in category
{
    
    if (isSelected)
    {
        subcat++;
        isSelected = 0;
    }
    if (subcat > category[cat].size() -1)
    {
        subcat = 0;
    }
}
void
Built_in_plugins::previous() //move to previous plugin in category
{
    
    if (isSelected)
    {
        subcat--;
        isSelected = 0;
    }
    if (subcat < 0)
    {
        subcat = (int) category[cat].size() - 1;
     }
}
string
Built_in_plugins::getcatname() //get the category name
{
    int cat_checker = 0;
    if (cat > category[cat].size() - 1 || cat < 0 )
    {
        cat_checker = 0;
    }
    else{
        cat_checker = cat;
    }
    return bp_categoryPlugin[cat_checker];
}
void Built_in_plugins::lockselector()
{
    isSelected = 0 ;
}