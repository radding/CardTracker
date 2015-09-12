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
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

class Card
{
    
public:
    Card( Mat img, Rect position );
    Mat imgCard;
    Rect cardPosition;
    string str();
    vector<string> characters;
    vector<Rect> charactersPosition;
    string cardNumber;
    string cardExp;
    string cardCVV;
    
};


#endif /* defined(__CardImageProcessor__Card__) */