#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "card_reader.hpp"

int main(int argv, char** args)
{
    if(argv < 2)
    {
        std::cout<<"usage: "<<args[0]<<" image_path"<<std::endl;
        return -1;
    }

    cv::Mat image = cv::imread(args[1]);

    CardReader reader;

    std::vector<CardPosition> cardPositions = reader.findCards(image);

    for(CardPosition& position : cardPositions)
    {
        cv::circle(image, position.topLeft, 2, cv::Scalar(0,255,0), -1);
        cv::circle(image, position.topRight, 2, cv::Scalar(0,255,0), -1);
        cv::circle(image, position.bottomRight, 2, cv::Scalar(0,255,0), -1);
        cv::circle(image, position.bottomLeft, 2, cv::Scalar(0,255,0), -1);
    }

    cv::namedWindow("card", cv::WINDOW_NORMAL);
    cv::imshow("card", image);
    cv::waitKey();

}
