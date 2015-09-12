//
//  TextBox.h
//  CardImageProcessor
//
//  Created by Truc Le on 9/12/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __CardImageProcessor__TextBox__
#define __CardImageProcessor__TextBox__

#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

class TextBox
{
    
public:
    TextBox( Mat img, Rect position );
    Mat imgTextBox;         //imgCard;
    Rect textBoxPosition;   //cardPosition;
    string str();
    vector<string> characters;
    vector<Rect> charactersPosition;
    
};

#endif /* defined(__CardImageProcessor__TextBox__) */
