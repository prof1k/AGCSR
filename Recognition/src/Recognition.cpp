//============================================================================
// Name        : Recognition.cpp
// Author      : Sukhodoev IS
// Version     : 0.3
// Copyright   : Study Project
// Description : Automatic gantry control system by recognition
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
#include "connectMysql.h"
using namespace std;

const string PATH_TO_PATTERNS = "/home/prof1k/LicensePlateGit/Recognition/Debug/config/ru.patterns";

TransformPatterns tr(PATH_TO_PATTERNS); // class for transforming zeros into a letter 'o'

alpr::Alpr openalpr("ru", "/home/prof1k/LicensePlateGit/Recognition/Debug/config/openalpr.conf", "/usr/share/openalpr/runtime_data");
void RecognitionPlate(cv::Mat plate)
{
        if (openalpr.isLoaded())
        {
        //imshow("Input", plate);  //обойдемся дебагом
        openalpr.setTopN(1);
        //openalpr.setDefaultRegion("il");
        std::vector<alpr::AlprRegionOfInterest> regionsOfInterest;
        regionsOfInterest.push_back(alpr::AlprRegionOfInterest(0, 0, plate.cols, plate.rows));
        alpr::AlprResults results = openalpr.recognize(plate.data, plate.elemSize(), plate.cols, plate.rows, regionsOfInterest);
        string transorm;
        // cout << results.plates.size() << endl;
        for (size_t i = 0; i < results.plates.size(); i++)
        {
           alpr::AlprPlateResult plate = results.plates[i];
           std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;
           alpr::AlprPlate candidate;

           for (size_t k = 0; k < plate.topNPlates.size(); k++)
           {
             candidate = plate.topNPlates[k];

             if (candidate.matches_template)
             {
            	 break;
             }

             /*std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
             std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;*/
           }

           if (!candidate.matches_template)
           {
        	   alpr::AlprPlate candi2 = plate.bestPlate;
        	   transorm = "";
        	   transorm = tr.transformation(candi2.characters);
        	   if (transorm != "")
        	   {
            	 std::cout << "    - " << candi2.characters << "\t confidence: " << candi2.overall_confidence;
            	 std::cout << "\t pattern_match: " << candi2.matches_template << std::endl;
        	   }
        	   else
        	   {
            	 std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
            	 std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        	   }
        	   cout << "  After transform. " << transorm << endl;
           }
           else
           {
        	   std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
        	   std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;

        	   // MUTIM CANDIDAT!!!
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
        cap.open("/home/prof1k/LicensePlateGit/Recognition/Debug/ch5.avi");


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
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	//uuid_make(uuid, UUID_MAKE_V1);
	//cout << uuid->uuid_st;


	CameraAndDetect();
	return 0;
}
