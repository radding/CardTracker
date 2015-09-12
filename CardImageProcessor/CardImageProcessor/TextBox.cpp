//
//  TextBox.cpp
//  CardImageProcessor
//
//  Created by Truc Le on 9/12/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "TextBox.h"



//--------------------------------------------------
// Constructor
//
TextBox::TextBox( Mat img, Rect position )
{
    imgTextBox         = img;
    textBoxPosition    = position;
}



//--------------------------------------------------
// OCR string. Use this to display string because
// putText displays in up-side-down reverse order.
//
string TextBox::str()
{
    string result = "";
    
    vector<int> orderIndex, xPos;
    for ( int i = 0; i < charactersPosition.size(); i++ )
    {
        orderIndex.push_back( i );
        xPos.push_back( charactersPosition[i].x );
    }
    
    
    // Re-arrange characters from leftmost
    // to rightmost for displaying
    float min   = xPos[0];
    int minIdx  = 0;
    for ( int i = 0; i < xPos.size(); i++ )
    {
        min     = xPos[i];
        minIdx  = i;
        
        for ( int j = i; j < xPos.size(); j++ )
        {
            if  ( xPos[j] < min )
            {
                min     = xPos[j];
                minIdx  = j;
            }
        }
        
        int aux_i           = orderIndex[i];
        int aux_min         = orderIndex[ minIdx ];
        orderIndex[i]       = aux_min;
        orderIndex[minIdx]  = aux_i;
        
        float aux_xi    = xPos[i];
        float aux_xmin  = xPos[minIdx];
        xPos[i]         = aux_xmin;
        xPos[minIdx]    = aux_xi;
    }
    
    
    for  ( int i = 0; i < orderIndex.size(); i++ )
    {
        result = result + characters[ orderIndex[i] ];
    }
    
    
    return result;
}