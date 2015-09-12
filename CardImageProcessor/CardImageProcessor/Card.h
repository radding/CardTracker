//
//  Card.h
//  CardImageProcessor
//
//  Created by Truc Le on 9/12/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __CardImageProcessor__Card__
#define __CardImageProcessor__Card__

#include <stdio.h>
#include <vector>
#include <iostream>
#include <opencv2/text.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>

#include "TextBox.h"


using namespace cv;
using namespace cv::ml;
using namespace cv::text;
using namespace std;



//--------------------------------------------------
// Extract ERStat (Extreme Regions Statistics)
// in parallel for different channels
//
class ParallelExtractCSER: public ParallelLoopBody
{
    
private:
    vector<Mat> &channels;
    vector< vector<ERStat> > &regions;
    vector< Ptr<ERFilter> > ERfilter1;
    vector< Ptr<ERFilter> > ERfilter2;
    
    
public:
    ParallelExtractCSER( vector<Mat> &_channels,
                        vector< vector<ERStat> > &_regions,
                        vector< Ptr<ERFilter> > _ERfilter1,
                        vector< Ptr<ERFilter> > _ERfilter2 )
    : channels( _channels ),
    regions( _regions ),
    ERfilter1( _ERfilter1 ),
    ERfilter2( _ERfilter2 ) {}
    
    
    virtual void operator()( const Range &r ) const
    {
        for ( int i = r.start; i < r.end; i++ )
        {
            ERfilter1[i]->run( channels[i], regions[i] );
            ERfilter2[i]->run( channels[i], regions[i] );
        }
    }
    
    
    ParallelExtractCSER & operator = ( const ParallelExtractCSER &parameter );
    
};



//--------------------------------------------------
// OCR in parallel for different detections
//
template <class T>
class ParallelOCR: public ParallelLoopBody
{
    
private:
    vector<Mat> &detections;
    vector<string> &outputs;
    vector< vector<Rect> > &boxes;
    vector< vector<string> > &words;
    vector< vector<float> > &confidence;
    vector< Ptr<T> > &ocrStr;
    
    
public:
    ParallelOCR( vector<Mat> &_detections,
                vector<string> &_outputs,
                vector< vector<Rect> > &_boxes,
                vector< vector<string> > &_words,
                vector< vector<float> > &_confidence,
                vector< Ptr<T> > &_ocrStr )
    : detections( _detections ),
    outputs( _outputs ),
    boxes( _boxes ),
    words( _words ),
    confidence( _confidence ),
    ocrStr( _ocrStr ) {}
    
    
    virtual void operator()( const Range &r ) const
    {
        for ( int i = r.start; i < r.end; i++ )
        {
            ocrStr[ i % ocrStr.size() ]->run( detections[i],
                                             outputs[i],
                                             &boxes[i],
                                             &words[i],
                                             &confidence[i],
                                             OCR_LEVEL_WORD );
        }
    }
    
    
    ParallelOCR & operator = ( const ParallelOCR &parameter );
    
};



//--------------------------------------------------
// Main Card Detector class
//

class Card
{
    
public:
    Card();
    string filename;
    string cardNumber;

    // Still constructing
    vector<string> potentialExp;
    vector<string> potentialName;
    //! Still constructing
    
    bool downsize;
    bool printSteps;
    bool showSteps;
    bool showOCRsteps;
    bool saveRegions;
    bool saveResult;
    
    void setFilename( string str );
    bool isRepetitive( const string &str );
    void ERdraw( vector<Mat> &channels,
                vector< vector<ERStat> > &regions,
                vector<Vec2i> group,
                Mat &segmentation );
    
    vector<TextBox> detectText( Mat input );
    vector<TextBox> recognizeText( vector<TextBox> regions );
    
};


#endif /* defined(__CardImageProcessor__Card__) */
