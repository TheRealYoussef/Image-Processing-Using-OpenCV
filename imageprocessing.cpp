#include "imageprocessing.h"
#include <cmath>
#include <QString>

int ImageProcessing::getNumberOfImages() const {
    return images.size();
}

void ImageProcessing::openImage(const string& file) {
    images.push_back(cv::imread(file, CV_LOAD_IMAGE_GRAYSCALE));
    cv::imshow("Image " + QString::number(images.size()).toStdString(), images[images.size() - 1]);
}

void ImageProcessing::transform(int imageNumber, double sx, double sy, double rot, double px, double py, double tx, double ty, bool histogram, bool negative, bool log, bool inverseLog, bool nthPower, double n) {
    if (imageNumber < 0 || imageNumber >= images.size())
        return;
    double h[256];
    int totalPixels = images[imageNumber].rows * images[imageNumber].cols;
    if (histogram) {
        memset(h, 0, sizeof h);
        for (int i = 0; i < images[imageNumber].rows; ++i) {
            for (int j = 0; j < images[imageNumber].cols; ++j) {
                ++h[images[imageNumber].at<uchar>(i, j)];
            }
        }
        for (int i = 1; i < 256; ++i) {
            h[i] += h[i - 1];
        }
        for (int i = 1; i < 256; ++i) {
            h[i] = h[i] / totalPixels * 255;
        }
    }
    double rotRad = rot * M_PI / 180.0;
    double sinRot = std::sin(rotRad);
    double cosRot = std::cos(rotRad);
    double calcJ = (cosRot * -tx + sinRot * ty - cosRot * px + sinRot * py + px) / sx;
    double calcI = (sinRot * -tx + cosRot * -ty - sinRot * px - cosRot * py + py) / sy;
    double logC = 255.0 / std::log(256);
    double powC = 255.0 / pow(255, n);
    double newI, newJ, newVal;
    images.push_back(Mat(images[imageNumber].rows * sy, images[imageNumber].cols * sx, CV_8UC1, Scalar(0)));
    for (int i = 0; i < images[images.size() - 1].rows; ++i) {
        for (int j = 0; j < images[images.size() - 1].cols; ++j) {
            newJ = (cosRot * j - sinRot * i) / sx + calcJ;
            newI = (sinRot * j + cosRot * i) / sy + calcI;
            if (newJ < images[imageNumber].cols && newI < images[imageNumber].rows && newI >= 0 && newJ >= 0) {
                newVal = images[imageNumber].at<uchar>(newI, newJ);
                if (histogram)
                    newVal = h[(int)newVal];
                if (negative)
                    newVal = 255 - newVal;
                if (log)
                    newVal = logC * std::log(1 + newVal);
                if (inverseLog)
                    newVal = exp(newVal / logC) - 1;
                if (nthPower)
                    newVal = powC * pow(newVal, n);
                images[images.size() - 1].at<uchar>(i, j) = newVal;
            }
        }
    }
    cv::imshow("Image " + QString::number(images.size()).toStdString(), images[images.size() - 1]);
}
