//
//  CardDetector.h
//  CardImageProcessor
//
//  Created by Truc Le on 9/12/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "CardDetector.h"



//--------------------------------------------------
// Constructor
//
CardDetector::CardDetector()
{
    downsize    = false;
    showRegions = false;
    saveRegions = false;
    saveResult  = false;
}



//--------------------------------------------------
// Set Filename
//
void CardDetector::setFilename( string str )
{
    filename = str;
}



//--------------------------------------------------
// Check if string is repetitive
//
bool CardDetector::isRepetitive( const string& str )
{
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int first = (int) str[0];
    int last = (int) str[(int) str.size() - 1];
    
    
    for ( int i = 0; i < (int) str.size(); ++i )
    {
        if ( ( str[i] == 'i' ) || ( str[i] == 'l' ) || ( str[i] == 'I' ) )
        {
            ++count1;
        }
        
        if ( (int) str[i] == first )
        {
            ++count2;
        }
        
        if ( (int) str[i] == last )
        {
            ++count3;
        }
    }
    
    
    if ( ( count1 > ( (int) str.size() + 1 ) / 2 ) ||
        ( count2 == (int) str.size() ) ||
        ( count3 > ( (int) str.size() * 2 ) / 3 ) )
    {
        return true;
    }
    
    
    return false;
}



//--------------------------------------------------
// Extremal Regions drawing to highlight text from black background
//
void CardDetector::ERdraw( vector<Mat> &channels,
                          vector< vector<ERStat> > &regions,
                          vector<Vec2i> group,
                          Mat &segmentation )
{
    for ( int i = 0; i < (int) group.size(); ++i )
    {
        ERStat ER = regions[group[i][0]][group[i][1]];
        if ( ER.parent != NULL )
        {
            int newMaskVal = 255;
            int flags = 4 + (newMaskVal << 8) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;
            
            floodFill( channels[group[i][0]],
                      segmentation,
                      Point( ER.pixel % channels[group[i][0]].cols,
                            ER.pixel / channels[group[i][0]].cols),
                      Scalar( 255 ),
                      0,
                      Scalar( ER.level ),
                      Scalar( 0 ),
                      flags );
            
        }
    }
    
}



//--------------------------------------------------
// Detect Text
//
vector<Card> CardDetector::detectText( Mat input )
{
    
    //-------------------------
    // Create ERFilter objects with
    // the 1st and 2nd stage default classifiers.
    // Since ER algorithm is no reentrant,
    // we need 1 filter per channel.
    //
    
    vector< Ptr<ERFilter> > ERfilters1;
    vector< Ptr<ERFilter> > ERfilters2;
    
    for ( int i = 0; i < 2; i++ )
    {
        Ptr<ERFilter> ERfilter1 = createERFilterNM1( loadClassifierNM1( "classifiers/trained_classifierNM1.xml"),
                                                    8,
                                                    0.00015f,
                                                    0.13f,
                                                    0.2f,
                                                    true,
                                                    0.1f );
        
        Ptr<ERFilter> ERfilter2 = createERFilterNM2( loadClassifierNM1( "classifiers/trained_classifierNM2.xml" ), 0.5 );
        
        ERfilters1.push_back( ERfilter1 );
        ERfilters2.push_back( ERfilter2 );
    }
    
    
    
    //-------------------------
    cout << "● Detecting Scene Text" << endl;
    
    Mat grey;
    vector<Mat> channels;
    vector< vector<ERStat> > regions( 2 ); // 2 channels
    vector<Card> characterBoxes;
    
    
    // 1. Resize
    Mat inputResized = input.clone();
    if ( downsize )
    {
        resize( input, inputResized, Size( 450, 287 ) );
    }
    
    
    // 2. Convert color
    cvtColor( inputResized, grey, COLOR_BGR2GRAY );
    
    
    // 3. Extract channels to be processed individually
    channels.clear();
    channels.push_back( grey );
    channels.push_back( 255 - grey );
    
    regions[0].clear();
    regions[1].clear();
    
    
    // 4. Extract regions in parallel using
    //    Class-specific Extremal Regions
    parallel_for_( Range( 0, (int) channels.size() ),
                   ParallelExtractCSER( channels, regions, ERfilters1, ERfilters2 ) );
    
    
    // 5. Detect Character Groups using Arbitrary Oriented Grouping
    vector< vector<Vec2i> > nmRegionGroups; // nm = Lukás Neumann & Jiri Matas
    vector<Rect> nmBoxes;
    erGrouping( inputResized,
                channels,
                regions,
                nmRegionGroups,
                nmBoxes,
                ERGROUPING_ORIENTATION_ANY,
                "classifiers/trained_classifier_erGrouping.xml",
                0.5 );
    
    
    // 6. Crop, resize, and save regions
    cout << "● Extracting Scene Text" << endl;
    
    for ( int i = 0; i < (int) nmBoxes.size(); ++i )
    {
        Mat boxCrop;
        Mat boxResized;
        Point2f nmBoxCenter = Point2f( nmBoxes[i].tl().x + nmBoxes[i].width / 2,
                                      nmBoxes[i].tl().y + nmBoxes[i].height / 2 );
        float minSize = ( nmBoxes[i].width < nmBoxes[i].height ) ? nmBoxes[i].width : nmBoxes[i].height;
        float maxSize = ( nmBoxes[i].width > nmBoxes[i].height ) ? nmBoxes[i].width : nmBoxes[i].height;
        
        
        getRectSubPix( inputResized, nmBoxes[i].size(), nmBoxCenter, boxCrop );
        boxResized.create( minSize, maxSize, boxCrop.type() );
        
        
        resize( boxCrop, boxResized, Size( 1000, 100 ), 0, 0, INTER_CUBIC ); //size = number w:h ratio
        
        
        // Save regions to nmBoxes folder
        if ( saveRegions )
        {
            stringstream ss( stringstream::in | stringstream::out );
            
            ss << "nmBoxes/" << filename << "_cardNumber_" << i << ".JPG";
            imwrite( ss.str(), boxResized );
        }
        
        
        characterBoxes.push_back( Card( boxResized, nmBoxes[i] ) );
    }

    
    
    //-------------------------
    cout << "   • Scene Text Regions: " << characterBoxes.size() << endl;

    if ( showRegions )
    {
        for ( int i = 0; i < characterBoxes.size(); ++i )
        {
            imshow( "Scene Text Regions", characterBoxes[i].imgCard );
            waitKey( 2000 );
        }
        
    }
    
    
    
    return characterBoxes;
}



//--------------------------------------------------
// Recognize Text using OCR Tesseract
vector<Card> CardDetector::recognizeText( vector<Card> possibleRegions )
{
    
    //-------------------------
    // Create ERFilter objects with
    // the 1st and 2nd stage default classifiers.
    // Since ER algorithm is no reentrant,
    // we need 1 filter per channel.
    //
    
    vector< Ptr<ERFilter> > ERfilters1;
    vector< Ptr<ERFilter> > ERfilters2;
    
    for ( int i = 0; i < 2; i++ )
    {
        Ptr<ERFilter> ERfilter1 = createERFilterNM1( loadClassifierNM1( "classifiers/trained_classifierNM1.xml"),
                                                    8,
                                                    0.00015f,
                                                    0.13f,
                                                    0.2f,
                                                    true,
                                                    0.1f );
        
        Ptr<ERFilter> ERfilter2 = createERFilterNM2( loadClassifierNM1( "classifiers/trained_classifierNM2.xml" ), 0.5 );
        
        ERfilters1.push_back( ERfilter1 );
        ERfilters2.push_back( ERfilter2 );
    }
    
    
    
    //-------------------------
    // Initialize 1 instance of OCR Tesseract
    //
    Ptr<OCRTesseract> ocr = OCRTesseract::create();
    
    
    
    //-------------------------
    // Detect and Recognize Text
    //
    cout << "● Applying OCR" << endl;
    
    Mat grey;
    vector<Mat> channels;
    vector< vector<ERStat> > regions( 2 );
    vector<Card> OCRregions;
    
    
    float minConfidence1 = 51.f; //51.f
    float minConfidence2 = 60.f; //60.f
    
    
    for ( int i = 0; i < possibleRegions.size(); ++i )
    {
        Mat region = possibleRegions[i].imgCard;
        
        
        // 1. Convert color
        cvtColor( region, grey, COLOR_BGR2GRAY );
        
        
        // 2. Extract channels to be processed individually
        channels.clear();
        channels.push_back( grey );
        channels.push_back( 255 - grey );
        
        regions[0].clear();
        regions[1].clear();
        
        
        // 3. Extract regions in parallel using
        //    Class-specific Extremal Regions
        parallel_for_( Range( 0, (int) channels.size() ),
                       ParallelExtractCSER( channels, regions, ERfilters1, ERfilters2 ) );
        
        
        // 4. Detect Character Groups using Arbitrary Oriented Grouping
        vector< vector<Vec2i> > nmRegionGroups; // nm = Lukás Neumann & Jiri Matas
        vector<Rect> nmBoxes;
        erGrouping( region,
                    channels,
                    regions,
                    nmRegionGroups,
                    nmBoxes,
                    ERGROUPING_ORIENTATION_ANY,
                    "classifiers/trained_classifier_erGrouping.xml",
                    0.5 );
        
        
        // 5. Group image (input region is already 1 group, but don't know
        // how to skip erGrouping above to jump directly to this below loop yet.
        // If figured out, then we can recognize text in parallel.
        vector<Mat> detections;
        for ( int j = 0; j < (int) nmBoxes.size(); ++j )
        {
            Mat groupImg = Mat::zeros( region.rows + 2, region.cols + 2, CV_8UC1 );
            ERdraw( channels, regions, nmRegionGroups[j], groupImg );
            groupImg( nmBoxes[j] ).copyTo( groupImg );
            copyMakeBorder( groupImg, groupImg, 15, 15, 15, 15, BORDER_CONSTANT, Scalar( 0 ) );
            
            detections.push_back( groupImg );
            
        }

        
        // 6. Read detected text
        vector<Rect> boxes;
        vector<string> words;
        vector<float>  confidences;
        vector<string> wordsDetection;
        
        for ( int j = 0; j < detections.size(); ++j )
        {
            string output;
            
            
            // The "Empty page!!" respond results from the
            // algorithm pushing incorrect Mat to detections.
            ocr->run( detections[j], output, &boxes, &words, &confidences, OCR_LEVEL_WORD );
            output.erase( remove( output.begin(), output.end(), '\n'), output.end() );
            
            
            // Save characters position of each region
            possibleRegions[i].charactersPosition = boxes;
            
            for ( int z = 0; z < words.size(); ++z )
            {
                
                if ( ( confidences[z] < minConfidence1 ) ||
                    ( ( words[z].size() == 2 ) && ( words[z][0] == words[z][1] ) ) ||
                    ( ( words[z].size() < 4 ) && ( confidences[z] < minConfidence2 ) ) ||
                    isRepetitive( words[z] ) )
                {
                    continue;
                }
                wordsDetection.push_back( words[z] );

            }
            
            
            
        }
        
        
        // Ignore images with no text
        if ( wordsDetection.size() == 0 )
        {
            continue;
        }
        
        
        // Save string's characters of each region
        possibleRegions[i].characters = wordsDetection;
        
        
        // 7. Concatenate strings
        string concatenatedString;
        
        for ( int j = 0; j < wordsDetection.size(); ++j )
            concatenatedString = concatenatedString + wordsDetection[j];
   
        
        
        cout << "       ⦿ OCR result: " << concatenatedString << endl;
        
        
        
        // Accept all OCR results
        OCRregions.push_back( possibleRegions[i] );
        
    }
    
    
    
    //-------------------------
    cout << "   • OCR Regions: " << OCRregions.size() << endl;

    if ( showRegions )
    {
        for ( int i = 0; i < OCRregions.size(); i++ )
        {
            imshow( "OCR Regions", OCRregions[i].imgCard );
            waitKey( 2000 );
        }
    }
    
    
    return OCRregions;
}