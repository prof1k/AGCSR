//============================================================================
// Name        : Recognition.cpp
// Author      : Sukhodoev IS
// Version     :
// Copyright   : Study Project
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <tesseract/strngs.h>
#include <alpr.h>
using namespace std;

alpr::Alpr openalpr("ru", "./config/openalpr.conf", "/usr/share/openalpr/runtime_data");

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
