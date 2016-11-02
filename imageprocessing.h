#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

class ImageProcessing
{
public:
    void openImage(const string&);
    int getNumberOfImages() const;
    void transform(int, double, double, double, double, double, double, double, bool, bool, bool, bool, bool, double);
private:
    vector<Mat> images;
};

#endif // IMAGEPROCESSING_H
