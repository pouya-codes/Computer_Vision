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
    cv::Mat c_r = cv::Mat::zeros(img.rows, img.cols, CV_32FC1);
    cv::Mat c_g = cv::Mat::zeros(img.rows, img.cols, CV_32FC1);
    cv::Mat c_b = cv::Mat::zeros(img.rows, img.cols, CV_32FC1);

    for (int r=0; r < img.rows; r++ ) {
        for (int c=0; c < img.cols; c++) {

            if (r % 2 == 0) { //ever rows
                if(c % 2 == 0 ) //even columns
                    // blue
                    c_b.at<float>(r,c) = img.at<uchar>(r,c) ;
                else // odd colums
                    // red
                    c_r.at<float>(r,c) = img.at<uchar>(r,c) ;
            }
            else { //odd rows
                if(c % 2 == 0 ) //even columns
                    // red
                    c_r.at<float>(r,c) = img.at<uchar>(r,c) ;
                else // odd colums
                    // green
                    c_g.at<float>(r,c) = img.at<uchar>(r,c) ;
            }
        }
    }

    cv::imshow("sa",c_r) ;
    cv::waitKey(0);

    cv::Mat kernel_r = ( cv::Mat_<double>(3,3) << 0.25, 0.5,  0.25, 0.5,  1, 0.5,  0.25, 0.5,   0.25);
    cv::Mat kernel_g = ( cv::Mat_<double>(3,3) << 0,    0.25, 0,    0.25, 1, 0.25, 0,    0.25,  0);
    cv::Mat kernel_b = ( cv::Mat_<double>(3,3) << 0.25, 0.5,  0.25, 0.5,  1, 0.5,  0.25, 0.5,   0.25);

    cv::filter2D(c_r,c_r,-1,kernel_r);
    cv::filter2D(c_g,c_g,-1,kernel_g);
    cv::filter2D(c_b,c_b,-1,kernel_b);

    std::vector<cv::Mat> channels;
    channels.push_back(c_r);
    channels.push_back(c_g);
    channels.push_back(c_b);
    cv::Mat result;
    merge(channels,result);


    cv::imshow("results",result);
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
                    mosaic_img.at<uchar>(r,c) = channels[2].at<cv::uint8_t>(r,c);
                else // odd columns
                    // red channel
                    mosaic_img.at<uchar>(r,c) = channels[0].at<cv::uint8_t>(r,c);
            }
            else { // odd rows (1,3,5,7...)
                if( c % 2 == 0)  // even columns (0,2,4,6,...)
                    // red channel
                    mosaic_img.at<uchar>(r,c) = channels[0].at<cv::uint8_t>(r,c);
                else // odd columns
                    // green channel
                    mosaic_img.at<uchar>(r,c) = channels[1].at<cv::uint8_t>(r,c);

            }
        }
    }
    mosaic_img.copyTo(img);
    cv::imshow("mosaic_img",mosaic_img);
    cv::waitKey(0) ;
    return 0;
}
int LinearInterpolation::SetPicture(QString path, bool is_mosaic){
   img = cv::imread(path.toStdString()) ;
   if(is_mosaic){
       cv::cvtColor(img,img,cv::COLOR_BGR2GRAY) ;
   }
   else {
       cv::cvtColor(img,img,cv::COLOR_BGR2RGB) ;
       CreateMosaicImage();
       cv::cvtColor(img,img,cv::COLOR_BGR2GRAY) ;
   }
//   img.convertTo(img, CV_32F);
//   img /= 255.0 ;

   ApplyFilters() ;
   cv::waitKey(0);
   return 0 ;
}
