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

    // convert from uchar to float
    img.convertTo(img, CV_32F);
    // convert from [0-255] to [0-1]
    img /= 255.0 ;

    // create RGB channels
    for (int r=0; r < img.rows; r++ ) {
        for (int c=0; c < img.cols; c++) {

            if (r % 2 == 0) { //ever rows
                if(c % 2 == 0 )  //even columns
                    // blue
                    c_b.at<float>(r,c) = img.at<float>(r,c) ;
                else // odd colums
                    // red
                    c_r.at<float>(r,c) = img.at<float>(r,c) ;
            }
            else { //odd rows
                if(c % 2 == 0 ) //even columns
                    // red
                    c_r.at<float>(r,c) = img.at<float>(r,c) ;
                else // odd colums
                    // green
                    c_g.at<float>(r,c) = img.at<float>(r,c) ;
            }
        }
    }

    // create kernels for different channels
    cv::Mat kernel_r = ( cv::Mat_<double>(3,3) << 0   , 0.25, 0   ,
                                                  0.25, 1   , 0.25,
                                                  0   , 0.25, 0    );
    cv::Mat kernel_g = ( cv::Mat_<double>(3,3) << 0.25, 0.5 , 0.25,
                                                  0.5 , 1   , 0.5 ,
                                                  0.25, 0.5 , 0.25);
    cv::Mat kernel_b = ( cv::Mat_<double>(3,3) << 0.25, 0.5 , 0.25,
                                                  0.5 , 1   , 0.5 ,
                                                  0.25, 0.5 , 0.25);

    // aplly kernels on channels
    cv::filter2D(c_b,c_b,-1,kernel_b);
    cv::filter2D(c_g,c_g,-1,kernel_g);
    cv::filter2D(c_r,c_r,-1,kernel_r);


    // merge channels to create an Image
    std::vector<cv::Mat> channels;
    channels.push_back(c_b);
    channels.push_back(c_g);
    channels.push_back(c_r);
    cv::merge(channels,demosaic);

    cv::Mat difference, output ;

    // convert from uchar to float
    org_img.convertTo(org_img, CV_32F);
    // convert from [0-255] to [0-1]
    org_img /= 255.0 ;


    cv::hconcat(org_img,demosaic,output) ;
    cv::hconcat(output,CalculateDiffrence(org_img,demosaic),output) ;

    cv::imshow("result",output);
    cv::waitKey(0);

    // part B
    channels.clear();
    // subtract R from b and g
    channels.push_back(c_b - c_r);
    channels.push_back(c_g - c_r);
    channels.push_back(c_r);

    // apply median filter
    cv::medianBlur(channels[0],channels[0],5);
    cv::medianBlur(channels[1],channels[1],5);

    // add R channel to B and G
    channels[0]+=channels[2];
    channels[1]+=channels[2];

    cv::Mat freeman;
    cv::merge(channels,freeman);

    cv::hconcat(org_img,freeman,output) ;
    cv::hconcat(output,CalculateDiffrence(org_img,freeman),output) ;

    cv::imshow("result freeman",output);
    cv::waitKey(0);


    return 0;
}

cv::Mat LinearInterpolation::CalculateDiffrence(cv::Mat org, cv::Mat res){

    // split RGB channels
    cv::Mat org_bgr[3],res_bgr[3],diff_bgr[3] ;
    cv::split(org,org_bgr) ;
    cv::split(res,res_bgr) ;

    // calculate root diffrence for each channel
    cv::pow(res_bgr[0]-org_bgr[0],2,diff_bgr[0]) ;
    cv::pow(res_bgr[1]-org_bgr[1],2,diff_bgr[1]) ;
    cv::pow(res_bgr[2]-org_bgr[2],2,diff_bgr[2]) ;
    difference = diff_bgr[0] + diff_bgr[1] + diff_bgr[2] ;

    // create and show output
    cv::cvtColor(difference,difference,cv::COLOR_GRAY2BGR) ;
    return difference ;

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
                    mosaic_img.at<uchar>(r,c) = channels[2].at<uchar>(r,c);
                else // odd columns
                    // red channel
                    mosaic_img.at<uchar>(r,c) = channels[0].at<uchar>(r,c);
            }
            else { // odd rows (1,3,5,7...)
                if( c % 2 == 0)  // even columns (0,2,4,6,...)
                    // red channel
                    mosaic_img.at<uchar>(r,c) = channels[0].at<uchar>(r,c);
                else // odd columns
                    // green channel
                    mosaic_img.at<uchar>(r,c) = channels[1].at<uchar>(r,c);

            }
        }
    }
    mosaic_img.copyTo(img);
    return 0;
}
int LinearInterpolation::SetPicture(QString path, bool is_mosaic){
   img = cv::imread(path.toStdString()) ;


   if(is_mosaic){
       org_img = cv::imread(path.replace("_mosaic.bmp",".jpg").toStdString()) ;
       cv::cvtColor(img,img,cv::COLOR_BGR2GRAY) ;
   }
   else {
       img.copyTo(org_img) ;
       cv::cvtColor(img,img,cv::COLOR_BGR2RGB) ;
       CreateMosaicImage();
   }

   ApplyFilters() ;
   cv::destroyAllWindows() ;
   return 0 ;
}
