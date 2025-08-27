/*
 * Adnan Amir
 * Spring 2024
 * CS 5330
 * In collaboration with Prem Sukhadwala
 */

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <cstring>
#include <cstdio>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    //check for commandline arguments
    if (argc < 2) {
        printf("usage %s <image filename> \n", argv[0]);
        exit(-1);
    }

    Mat src;
    char path[256];
    strcpy_s(path, argv[1]);
    src= imread(path);
    namedWindow("Image", WINDOW_NORMAL);
    resizeWindow("Image", 1280,720);
    imshow("Image", src);
    while (true)
    {
        int key = waitKey(0);
        if (key == 'q') {
            break;
        }
        if (key == 's') {
            imwrite("../img/saved.jpg", src);
            cout << "saved";

        }
    }
    return 1;
}

