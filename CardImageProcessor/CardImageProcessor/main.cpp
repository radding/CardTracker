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
#include "CardDetector.h"

#include "Card.cpp"
#include "CardDetector.cpp"


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
    
    //-------------------------
    // Detect Logo
    //
    Mat OCRoutput = image.clone();
    CardDetector cardDetector;
    cardDetector.setFilename( imageFilename );
    cardDetector.downsize       = false;
    cardDetector.showRegions    = false;
    cardDetector.saveRegions    = false;
    cardDetector.saveResult     = true;
    
    
    vector<Card> sceneTextRegions = cardDetector.detectText( image );
    vector<Card> OCRregions = cardDetector.recognizeText( sceneTextRegions );
    
    
    
    //-------------------------
    //
    //
    for ( int i = 0; i < OCRregions.size(); i++ )
    {
        Card card = OCRregions[i];
        
        string cardText = card.str();
        
        
        if ( cardDetector.downsize )
            resize( image, OCRoutput, Size( 450, 287 ) ); //size = credit card's w:h ration
        
        
        // Show OCR regions on Image
        rectangle( OCRoutput, card.cardPosition, Scalar( 255, 0, 255 ), 3 );
        putText( OCRoutput,
                cardText,
                Point( card.cardPosition.x, card.cardPosition.y - 10 ),
                FONT_HERSHEY_PLAIN,
                2,
                Scalar( 255, 0, 255 ),
                5 );
        
        
        // Check each character,
        // increment digitCounter each time found a digit
        // use digitCounter to check whether found string represents
        // cardNumber, cardExp, cardholderName
        int digitCounter = 0;
        for ( int j = 0; j < cardText.size(); ++j )
        {
            if ( cardText[j] == '0' || cardText[j] == '1' ||
                 cardText[j] == '2' || cardText[j] == '3' ||
                 cardText[j] == '4' || cardText[j] == '5' ||
                 cardText[j] == '6' || cardText[j] == '7' ||
                 cardText[j] == '8' || cardText[j] == '9' )
                ++digitCounter;
        }
    
        
        
        if ( digitCounter < 2 )
            cardDetector.cardholderName = cardText;
        else if ( digitCounter > 2 && digitCounter < 6 )
            cardDetector.cardExp = cardText;
        else
            cardDetector.cardNumber = cardText;
        
    }
    
    
    cout << "Cardholder Name: " << cardDetector.cardholderName << endl;
    cout << "Expiriation Date: " << cardDetector.cardExp << endl;
    cout << "Serial Number: " << cardDetector.cardNumber << endl;
    
    
    
    if ( cardDetector.saveResult )
    {
        string outputFilename = "result/" + cardDetector.filename + "-OCR.JPG";
        imwrite( outputFilename, OCRoutput );
    }
    
    
    
    return OCRoutput;
}



//--------------------------------------------------
// Main
//
int main(int argc, const char * argv[])
{
    
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
    
    
    
    //-------------------------
    // Show result
    //
    imshow( inputFilename , outputImage );
    waitKey( 0 );
    
    
    
    
    return 0;
}
