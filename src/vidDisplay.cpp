/*
 * Adnan Amir
 * Spring 2024
 * CS 5330
 * In collaboration with Prem Sukhadwala
 */

#include "opencv2/opencv.hpp"
#include "../include/filter.h"
#include "../include/faceDetect.h"
#include "opencv2/videoio.hpp"

using namespace cv;

enum effect {
    ORIGIN = 1,
    GRAYSCALE = 2,
    ALT_GRAYSCALE = 3,
    SEPIA = 4,
    X_SOBEL = 5,
    Y_SOBEL = 6,
    MAGNITUDE = 7,
    BLUR = 8,
    BLUR_QUANTIZE = 9,
    CARTOON = 10,
    NEGATIVE = 11,
    EMBOSS = 12,
    FACE_DETECTION=13,
    PENCIL=14,
    MIRROR=15,
    COOLMODE=16,
} effect;


int main(int argc, char *argv[]) {

//    if (argc < 2) {
//        printf("usage %s <image filename> \n", argv[0]);
//        exit(-1);
//    }

    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if( !capdev->isOpened() ) {
        printf("Unable to open video device\n");
        return(-1);
    }

    // get some properties of the image
    cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                   (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::Mat src;
    cv::Mat dst(refS.height, refS.width, CV_8UC3);
    cv::Mat gr;
    std::vector<cv::Rect> faces;
    std::string name="Original";
    std::string meme;
    bool memeflag=0;
    bool vidflag=0;
    VideoWriter vid("../img/snippet.avi",cv::VideoWriter::fourcc('M','J','P','G'),capdev->get(CAP_PROP_FPS),refS);
    cv::Rect last(0, 0, 0, 0);
    effect = ORIGIN;

    for(;;) {
        *capdev >> src; // get a new frame from the camera, treat as a stream
        if( src.empty() ) {
            printf("frame is empty\n");
            break;
        }
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);

        if( key == 'q') {
            capdev->release();
            vid.release();
            break;
        }
        if (key == 's') {
                cv::imwrite("../img/screenshot.png", dst);
        }

        switch (key) {
            case 'g':effect = GRAYSCALE;
                break;
            case 'h':effect = ALT_GRAYSCALE;
                break;
            case 'i':effect = SEPIA;
                break;
            case 'x':effect = X_SOBEL;
                break;
            case 'y':effect = Y_SOBEL;
                break;
            case 'm':effect = MAGNITUDE;
                break;
            case 'b':effect = BLUR;
                break;
            case 'l':effect = BLUR_QUANTIZE;
                break;
            case 'f':effect = FACE_DETECTION;
                break;
            case 'n':effect = NEGATIVE;
                break;
            case 'c':effect = CARTOON;
                break;
            case 'e':effect = EMBOSS;
                break;
            case 'p':effect = PENCIL;
                break;
            case ',':effect = MIRROR;
                break;
            case 'k':effect = COOLMODE;
                break;
            case 'w':{//extension
                    memeflag=1;
                    std::cout << "Enter Caption" << std::endl;
                    std::getline(std::cin, meme);
            };
                break;
            case 'r':{//extension
                vidflag=1;
                break;
            }
            case 't':{//extension
                vidflag=0;
                vid.release();
                break;
            }
            case 'o':effect = ORIGIN;
                break;
            case ' ':effect = ORIGIN;
                break;
        }

        switch (effect) {
            case ORIGIN:{
                src.copyTo(dst);
                name="Original";
                break;
            }
            case GRAYSCALE: {
                grey(src,dst);
                name="Greyscale";
                break;
            }
            case ALT_GRAYSCALE:{
                alt_grey(src,dst);
                name="Alternate Greyscale";
                break;
            }
            case SEPIA:{
                sepia(src,dst);
                name="Sepia";
                break;
            }
            case Y_SOBEL:{
                Mat sob;
                sobelY3x3(src,sob);
                convertScaleAbs(sob,dst);
                name="Y Sobel";
                break;
            }
            case X_SOBEL:{
                Mat sob;
                sobelX3x3(src,sob);
                convertScaleAbs(sob,dst);
                name="X Sobel";
                break;
            }
            case MAGNITUDE:{
                Mat sx,sy,sob;
                sobelX3x3(src,sx);
                sobelY3x3(src,sy);
                magnitude(sx,sy,sob);
                convertScaleAbs(sob,dst);
                name="Magnitude";
                break;
            }
            case FACE_DETECTION:{
                cv::cvtColor( src, gr, cv::COLOR_BGR2GRAY, 0);
                detectFaces( gr, faces );
                drawBoxes( src, faces );
                src.copyTo(dst);

                // add a little smoothing by averaging the last two detections
                if( faces.size() > 0 ) {
                    last.x = (faces[0].x + last.x)/2;
                    last.y = (faces[0].y + last.y)/2;
                    last.width = (faces[0].width + last.width)/2;
                    last.height = (faces[0].height + last.height)/2;
                }
                name="Face Detection";
                break;
            }
            case NEGATIVE:{
                negative(src,dst);
                name="Negative";
                break;
            }
            case EMBOSS:{
                Mat em;
                float dir[2]={0.7071,0.7071};
                emboss(src,em,dir);
                convertScaleAbs(em,dst);
                name="Emboss";
                break;
            }
            case BLUR:{
                blur5x5_2(src,dst);
                name="Fast Blur";
                break;
            }
            case BLUR_QUANTIZE:{
                blurQuantize(src,dst,10);
                name="Blur Quantize";
                break;

            }
            case PENCIL:{//extension
                Mat gr;
                pencilSketch(src,gr,dst);
                name = "Pencil Sketch (WARNING: SLOW)";
                break;
            }
            case MIRROR:{
                mirror(src,dst);
                name="Mirror";
                break;
            }
            case CARTOON:{//extension
                //You can pass in Blur Levels and Quantize Threshold Optionally
                cartoon(src,dst);
                name="cartoon";
                break;
            }
            case COOLMODE:{
                coolmode(src,dst);
                name= "Cool Mode";
                break;
            }
        }
        cv::namedWindow("Filtomatic v1", 1); // identifies a window
        putText(dst, //target image
                name, //text
                cv::Point(10, dst.rows / 10), //top-left position
                cv::FONT_HERSHEY_TRIPLEX,
                1.0,
                CV_RGB(118, 185, 0), //font color
                2);
        if (memeflag){
            putText(dst, //target image
                    meme, //text
                    cv::Point(dst.cols/10, 9*dst.rows / 10), //top-left position
                    cv::FONT_HERSHEY_TRIPLEX,
                    1.0,
                    CV_RGB(255, 185, 0), //font color
                    2);
        }
        if (vidflag){
            vid.write(dst);
            putText(dst, //target image
                    "Rec", //text
                    cv::Point(8*dst.cols/10, dst.rows / 10), //top-left position
                    cv::FONT_HERSHEY_TRIPLEX,
                    1.0,
                    CV_RGB(255, 0, 0), //font color
                    2);
        }
        cv::imshow("Filtomatic v1", dst);

    }

    delete capdev;
    return(0);
}