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
    
    //-------------------------
    // Detect Logo
    //
    Mat OCRoutput = image.clone();
    Card card;
    card.setFilename( imageFilename );
    
    
    vector<TextBox> sceneTextRegions = card.detectText( image );
    vector<TextBox> OCRregions = card.recognizeText( sceneTextRegions );
    
    
    
    //-------------------------
    // Show OCR regions on Image
    //
    if ( drawOCR )
    {
        for ( int i = 0; i < OCRregions.size(); i++ )
        {
            TextBox textBox = OCRregions[i];
            string text = textBox.str();
            
            
            if ( card.downsize )
            resize( image, OCRoutput, Size( 450, 287 ) ); //size = credit card's w:h ration
            
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

    
    
    
    
    //-------------------------
    // Print strings of each category
    //
    cout << "Cardholder Name: ";
    for ( int i = 0; i < card.cardholderName.size();  ++i )
    {
        if ( i != card.cardholderName.size() - 1 )
            cout << card.cardholderName[i] << ", ";
        else
            cout << card.cardholderName[i];
    }
    cout << endl;
    
    
    
    cout << "Expiriation Date: ";
    for ( int i = 0; i < card.cardExp.size();  ++i )
    {
        if ( i != card.cardExp.size() - 1 )
            cout << card.cardExp[i] << ", ";
        else
            cout << card.cardExp[i];
    }
    cout << endl;
    
    
    
    cout << "Serial Number: ";
    for ( int i = 0; i < card.cardNumber.size();  ++i )
    {
        if ( i != card.cardNumber.size() - 1 )
            cout << card.cardNumber[i] << ", ";
        else
            cout << card.cardNumber[i];
    }
    cout << endl;
    
    
    
    
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
