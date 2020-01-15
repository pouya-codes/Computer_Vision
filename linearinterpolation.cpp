#include "linearinterpolation.h"
#include "QDebug"
#include "stdio.h"
#include <iostream>

LinearInterpolation::LinearInterpolation()
{
    cv::imread("image_set/crayons.jpg") ;

}
int LinearInterpolation::ApplyFilters() {
    // create channels
    cv::Mat c_r(img), c_g(img), c_b(img) ;

    cv::imshow("sa",channels);
    cv::waitKey(0);
//    cv::filter2D()
    return 0;
}
// create Mosaic Image
int LinearInterpolation::CreateMosaicImage(){


    mosaic_img = cv::Mat::zeros(img.rows,img.cols,CV_8U) ;
    cv::Mat channels[3];
    cv::split(img,channels); // split channels
    for (int r = 0; r < img.rows; ++r) {
        for (int c = 0; c < img.cols; ++c) {
            if( r % 2 == 0) { // even rows (0,2,4,6...)
                if( c % 2 == 0)  // even columns (0,2,4,6,...)
                    // blue channel
                    mosaic_img.at<cv::uint8_t>(r,c) = channels[2].at<cv::uint8_t>(r,c);
                else // odd columns
                    // red channel
                    mosaic_img.at<cv::uint8_t>(r,c) = channels[0].at<cv::uint8_t>(r,c);
            }
            else { // odd rows (1,3,5,7...)
                if( c % 2 == 0)  // even columns (0,2,4,6,...)
                    // red channel
                    mosaic_img.at<cv::uint8_t>(r,c) = channels[0].at<cv::uint8_t>(r,c);
                else // odd columns
                    // green channel
                    mosaic_img.at<cv::uint8_t>(r,c) = channels[1].at<cv::uint8_t>(r,c);

            }
        }
    }
    cv::imshow("mosaic_img",mosaic_img);
    cv::waitKey(0) ;
    return 0;
}
int LinearInterpolation::SetPicture(QString path, bool is_mosaic){
   img = cv::imread(path.toStdString()) ;
   cv::cvtColor(img,img,cv::COLOR_BGR2RGB) ;
   if(is_mosaic)
       img.copyTo(mosaic_img) ;
   else
       CreateMosaicImage();
   ApplyFilters() ;
   cv::waitKey(0);
   return 0 ;
}
