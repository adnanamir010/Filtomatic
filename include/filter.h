/*
 * Adnan Amir
 * Spring 2024
 * CS 5330
 * In collaboration with Prem Sukhadwala
 */
#include <opencv2/opencv.hpp>

#ifndef FILTER_H
#define FILTER_H


int grey(cv::Mat &src, cv::Mat &dst);

int alt_grey(cv::Mat &src, cv::Mat &dst);

int sepia(cv::Mat &src, cv::Mat &dst);

int sobel(cv::Mat &src, cv::Mat &dst, const int hk[3],const int vk[3],const int norm[2]);

int sobelY3x3 (cv::Mat &src, cv::Mat &dst);

int sobelX3x3 (cv::Mat &src, cv::Mat &dst);

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );

int negative (cv::Mat &src, cv::Mat &dst);

int emboss (cv::Mat &src, cv::Mat &dst, const float dir[2]);

int blur5x5_1( cv::Mat &src, cv::Mat &dst );

int blur5x5_2( cv::Mat &src, cv::Mat &dst );

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );

int mirror(cv::Mat &src, cv::Mat &dst);

int cartoon(cv::Mat &src, cv::Mat &dst, int levels=8, int magThreshold=60);

int coolmode(cv::Mat &src, cv::Mat &dst);

#endif //FILTER_H
