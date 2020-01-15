#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QString>

class LinearInterpolation
{
public:
    LinearInterpolation();
    int SetPicture(QString path, bool is_mosaic=false);
private:
    cv::Mat img, mosaic_img, demosaic, difference;
    int CreateMosaicImage();
    int ApplyFilters() ;
};


#endif // LINEARINTERPOLATION_H
