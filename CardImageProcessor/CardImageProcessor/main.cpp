//
//  main.cpp
//  CardImageProcessor
//
//  Created by Truc Le on 9/12/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include <iostream>
#include <vector>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


#include "Card.h"
#include "TextBox.h"

#include "Card.cpp"
#include "TextBox.cpp"


using namespace std;
using namespace cv;



//--------------------------------------------------
// Print Usage
//
void printUsage()
{
    cout << "$ ./main <image path>" << endl;
}



//--------------------------------------------------
// Get filename
//
string getFilename( string filename )
{
    char separator = '/';
    char extension = '.';
    
#ifdef _WIN32
    separator = '\\';
#endif
    
    size_t i = filename.rfind( separator, filename.length() ); // Find location of the '/'
    if ( i != string::npos ) // npos = max value for size_t, which represents size of any object in bytes
    {
        string name = ( filename.substr( i + 1, filename.length() - i ) );
        size_t j = name.rfind( extension, name.length() );
        if ( i != string::npos )
        {
            return name.substr( 0, j );
        }
        else
        {
            return name;
        }
    }
    else
    {
        return "";
    }
}



//--------------------------------------------------
// Process Image
//
Mat processImage( Mat image, string imageFilename )
{
    bool drawOCR = false; //set to false when combine program because drawing textboxes are still buggy
    int maxRunningTime = 0;
    
    //-------------------------
    // Detect Logo
    //
    Mat sceneTextOutput = image.clone();
    Mat OCRoutput       = image.clone();
    Card card;
    card.setFilename( imageFilename );
    
    card.printSteps = true;
    card.showSteps = false;
    card.showOCRsteps = false;
    
    vector<TextBox> sceneTextRegions;
    vector<TextBox> OCRregions;
    
    
    do
    {
        sceneTextRegions = card.detectText( image );
        OCRregions = card.recognizeText( sceneTextRegions );
        ++maxRunningTime;
    } while ( card.cardNumber.size() != 16 && maxRunningTime != 20 );
    
    
    
    //-------------------------
    // Show OCR regions on image
    //
    if ( drawOCR && OCRregions.size() != 0)
    {
        TextBox cardNumberBox( OCRregions[0] );

        for ( int i = 0; i < OCRregions.size(); i++ )
        {
            TextBox textBox = OCRregions[i];
            string text = textBox.str();
            
            
            if ( card.downsize )
            resize( image, OCRoutput, Size( 450, 287 ) ); //size = credit card's w:h ratio
            
            rectangle( OCRoutput, textBox.textBoxPosition, Scalar( 255, 0, 255 ), 3 );
            putText( OCRoutput,
                    text,
                    Point( textBox.textBoxPosition.x, textBox.textBoxPosition.y - 10 ),
                    FONT_HERSHEY_PLAIN,
                    2,
                    Scalar( 255, 0, 255 ),
                    5 );
            
        }
    }
    
    
    // Print card number
    cout << "Card Number: " << card.cardNumber << endl;

    
    // Machine learning purpose, not really
    // used but I leave it here just in case
    if ( card.saveResult )
    {
        string outputFilename = "result/" + card.filename + "-OCR.JPG";
        imwrite( outputFilename, OCRoutput );
    }
    
    
    
    return OCRoutput;
}



//--------------------------------------------------
// Main
//
int main(int argc, const char * argv[])
{
    bool showOCR = false;
    
    //-------------------------
    // Retrieve image
    //
    cout << endl;
    cout << "=== Card Image Processor ===" << endl;
    
    
    if ( argc != 2 )
    {
        printUsage();
        return 0;
    }
    
    
    string inputPath = argv[1];
    string inputFilename = getFilename( inputPath );
    
    
    Mat image;
    image = imread( inputPath, 1 );
    
    
    if ( !image.data )
    {
        cerr << "(!) Error opening " << argv[2] << endl;
        return 0;
    }
    cout << "● Processing Image " << inputFilename << "..." << endl;
    
    
    
    Mat outputImage = processImage( image, inputFilename );
    
    
    
    // Show result
    if ( showOCR )
    {
        imshow( inputFilename , outputImage );
        waitKey( 0 );
    }
    
    
    
    
    return 0;
}
