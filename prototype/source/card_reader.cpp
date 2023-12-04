#include "card_reader.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#ifdef DEBUG
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#endif


CardReader::CardReader()
{}


std::vector<CardPosition> CardReader::findCards(const cv::Mat& image)
{
    std::vector<CardPosition> cardFound;

    cv::Mat grey, mask;
    cv::cvtColor(image, grey, cv::COLOR_BGR2GRAY);

    double minV,maxV;
    cv::Point2i minP, maxP;

    cv::minMaxLoc(grey, &minV, &maxV, &minP, &maxP);
    cv::Scalar mean, stddev;
    cv::meanStdDev(grey,mean, stddev);

    double thresholdValue = mean[0]-1.2*stddev[0];
    cv::threshold(grey, mask, thresholdValue, 255, cv::THRESH_BINARY_INV);
    cv::dilate(mask, mask, cv::Mat());
    cv::erode(mask, mask, cv::Mat());

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    std::vector<cv::Point> biggest;
    float biggestArea = FLT_MIN;
    int contourIndex = 0;

    for(int i = 0; i<contours.size(); i++)
    {

        float area = cv::contourArea(contours[i]);
        if(area > biggestArea)
        {
            biggestArea = area;
            biggest = contours[i];
            contourIndex = i;
        }
    }


    cv::Rect roi = cv::boundingRect(biggest);


    #ifdef DEBUG

        std::cout<<minV<<", "<<mean<<", "<<stddev<<", "<<biggestArea<<std::endl;
        cv::namedWindow("result", cv::WINDOW_NORMAL);
        cv::namedWindow("mask", cv::WINDOW_NORMAL);
        cv::rectangle(image, roi, cv::Scalar(255,0,0),2);
        cv::drawContours(image,contours,contourIndex, cv::Scalar(0,255,0),2);
        cv::imwrite("result.png", image);
        cv::imshow("result", image);
        cv::imshow("mask", mask);
        cv::waitKey();
    #endif


    return cardFound;
}
