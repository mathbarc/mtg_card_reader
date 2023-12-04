#include "card_reader.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#ifdef DEBUG
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#endif


CardReader::CardReader()
{
    this->keypointsExtractor = cv::SIFT::create();
}


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

    std::vector<cv::KeyPoint> keypoints;
    this->keypointsExtractor->detect(grey, keypoints, mask);




    #ifdef DEBUG

        cv::namedWindow("result", cv::WINDOW_NORMAL);
//        cv::namedWindow("mask", cv::WINDOW_NORMAL);

        cv::drawKeypoints(image, keypoints, image,cv::Scalar(0,255,0));

        cv::imshow("result", image);
//        cv::imshow("mask", mask);
        cv::waitKey();
    #endif


    return cardFound;
}

cv::Mat CardReader::createReferenceCard(int height, int width)
{
    cv::Mat reference = cv::Mat::zeros(height,width,CV_8U);

    int borderWidth = 0.025*std::max(width,height);



    cv::Rect border(width*0.025, height*0.025,width*0.95, borderWidth);
    reference(border) = 255;
    border.y = height*0.95;
    reference(border) = 255;



    border = cv::Rect(width*0.025, height*0.025,borderWidth, height*0.95);
    reference(border) = 255;
    border.x = width * 0.94;
    reference(border) = 255;

    return reference;
}
