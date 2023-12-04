#ifndef CARD_READER_CPP
#define CARD_READER_CPP

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

enum class Type
{
    MONSTER = 0,
    FIELD = 1,
    ARTIFACT = 2,   
    SPELL = 3
};

enum class ManaColor
{
    RED = 0,
    BLUE = 1,
    GREEN = 2,
    BLACK = 3,   
    WHITE = 4,
    NOCOLOR = 5
};


struct CardData
{
    Type type;
    ManaColor color;
    std::string name;
};

struct CardPosition
{
    cv::Point2d topLeft;
    cv::Point2d topRight;
    cv::Point2d bottomRight;
    cv::Point2d bottomLeft;
};


class CardReader
{
    public:
        
        CardReader();
        std::vector<CardPosition> findCards(const cv::Mat& image);
        std::vector<cv::Mat> extractCards(const cv::Mat& image, const std::vector<cv::Rect>& rois);
        CardData getCardData(const cv::Mat& cardImage);
        cv::Mat createReferenceCard(int height=900, int width=600);

    private:
        cv::Ptr<cv::SIFT> keypointsExtractor;
};


#endif
