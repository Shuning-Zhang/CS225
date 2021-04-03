/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{//create class
  public:
    HSLAPixel(); //first public member functions
    HSLAPixel(double hue, double saturation, double luminance);//second functions
    HSLAPixel(double hue, double saturation, double luminance, double alpha);//third function

    double h;//hue of th epixel [0,360]
    double s;//saturation [0,1]
    double l; //luminance [0,1]
    double a;// alpha [0,1]
  };
}
