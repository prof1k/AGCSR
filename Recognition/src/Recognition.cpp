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
#include "TransformPatterns.h"
using namespace std;

alpr::Alpr openalpr("ru", "./config/openalpr.conf", "/usr/share/openalpr/runtime_data");
TransformPatterns tr("pathToPattern");
void RecognitionPlate(cv::Mat plate)
{
        if (openalpr.isLoaded())
        {
        //imshow("Input", plate);  //обойдемся дебагом
        openalpr.setTopN(5);
        //openalpr.setDefaultRegion("il");
        std::vector<alpr::AlprRegionOfInterest> regionsOfInterest;
        regionsOfInterest.push_back(alpr::AlprRegionOfInterest(0, 0, plate.cols, plate.rows));
        alpr::AlprResults results = openalpr.recognize(plate.data, plate.elemSize(), plate.cols, plate.rows, regionsOfInterest);
        // cout << results.plates.size() << endl;
        for (int i = 0; i < results.plates.size(); i++)
        {
           alpr::AlprPlateResult plate = results.plates[i];
           std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;

             for (int k = 0; k < plate.topNPlates.size(); k++)
             {
               alpr::AlprPlate candidate = plate.topNPlates[k];
               std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
               std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
             }
        }
        }
        else
        {
                std::cerr << "Fail load openalpr";
        }
}

void CameraAndDetect()
{
        cv::VideoCapture cap;
//      cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G'));


        //cap.open(0);
        //cap.open("./MOVI0005.avi");
        cap.open("./ch5.avi");


//      cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G'));
//      cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//      cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        //cap.set(CV_CAP_PROP_FPS, 5);
        //cv::namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);

        int fps=0;

        while (1)
        {
                cv::Mat frame;
                bool bSuccess = cap.read(frame);
                if (!bSuccess)
                {
                        cout << "Cannot read" << endl;
                        break;
                }
                fps += cap.get(CV_CAP_PROP_FPS);
                //cout << fps << endl;
//              cv::flip(frame, frame, 1);
                //imshow("MyWindow", frame);
                if (fps > 240 )
                {
                        cap >> frame;
                        //if(cascade.load(cascadeName))
                        RecognitionPlate(frame);
                        //DetectAndCut(frame,cascade,scale,tryflip);
                        fps = 0;
                        frame.release();
                }
                if (cvWaitKey(30) == 27)
                {
                        cap.release();
                        break;
                }
        }
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	CameraAndDetect();
	return 0;
}
