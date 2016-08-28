#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <SerialClass.h>

Serial s("COM6"); // object of the class Serial from Serial.h library that completes the Serial communication support for my computer


using namespace cv;
using namespace std;

int r=0,c=0;
unsigned char* ptrimg;  // will be used to parse the image
unsigned char* ptrfilter; // will be used to create the filter image pixel by pixel
float H;
float S;
float V;

float Hmin=11,Hmax=37;
float Smin=75,Smax=188;
float Vmin=202,Vmax=256; // HSV values to be according to your Camera and the object

int x=0;
int y=0;
int n=0; // n= the no of pixels that have been identifies of being an object
// x and y will be used to get the final coordinates of the Center of object in pixels

int Sendapprocommand()  // this function when invoked will send the required command for controlling the camera
{
    /*
        this function sends a 4 byte integer to inform the uC to go in a particular direction
        120-left
        130-right
        140-up
        150-down
        the uC then reacts to the commands by moving servo in particular direction by certain degrees
        for better support you can improve the setup by moving the servo propotional to
            the ammount to pixels the object is away from the center position
        the Sleep command turns the code down(not do anything) for a certain millis
    */

     if(x>0)
     {



            s.write_uint_serial(120);  // 120 is sent for uC to go left
            cout<<"left"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==125)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);


     }
     else if(x<0)
     {

            s.write_uint_serial(130); // 130 is sent for uC to go right
            cout<<"right"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==135)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);


     }

     if(y>0)
     {


            s.write_uint_serial(140);  // 140 refers to up direction
            cout<<"up"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==145)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);



     }
     else if(y<0)
     {


            s.write_uint_serial(150);  // 150 refers to down direction on the uC
            cout<<"down"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==155)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);
     }


}


int main()
{
    CvCapture* cam = cvCreateCameraCapture(1);  // mandatory step if we want to get frames from camera
    IplImage* img=cvQueryFrame(cam);  //  this img object will store the image frame from the camera
    IplImage* hav=cvCreateImage(cvGetSize(img), 8, 3); // this object will store the hsv converted image
    IplImage* filterimage=cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,1);
    cvNamedWindow("camera input",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("HSV Image",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("filtered image",CV_WINDOW_AUTOSIZE);

    while(cvWaitKey(3)!=27) // ESC is char byte 27, on pressing escape the program exits
    {


        img=cvQueryFrame(cam);  // getting image frame
        cvShowImage("camera input",img);  // showing image to see what is happing in front of camera


        cvCvtColor(img,hav,CV_BGR2HSV); //  getting hsv image in the hav object

        cvShowImage("HSV Image",hav); // watch this shit image feel like god


        n=0; // no of pixels with same color as object
        x=0; // x coordinate of object initialized to 0
        y=0; // y coordinate of object initialized to 0

        for(r=0;r<(hav->height);r++) // loop for parsing the rows from 0 to (hav->height)-1
        {
            ptrimg=(unsigned char*)((hav->imageData)+r*(hav->widthStep));
            ptrfilter=(unsigned char*)((filterimage->imageData)+r*(filterimage->widthStep));



            for(c=0;c<(hav->width);c++)
            {
                H=*(ptrimg+(3*c)+0);
                S=*(ptrimg+(3*c)+1);
                V=*(ptrimg+(3*c)+2);  // this 3 lines will provide us with the hsv values of the pixel

                /*
                    if the hsv values of the pixels are well within the range then the pixel coordinates
                    will be summed to x and y correspondingly and the corresponding pixel coordinate will
                    be made white (255) on a grayscale image filter image
                    filter image has only one channel
                */
                if(Hmin<=H && H<=Hmax && Smin<=S && S<=Smax && Vmin<=V && V<=Vmax)
                {
                    *(ptrfilter+(c)+0)=255;

                    n++;
                    x=x+c;
                    y=y+r;

                }
                else
                {
                    *(ptrfilter+(c)+0)=0;
                }



            }





        }

        cvShowImage("filtered image",filterimage); // show the filter image checking if it is detecting correct region



        /*
            here in case the object is not present to avoid disturbance the no of pixels detected should be made to a certain value
            for me 100 was a fair enough number to detecting the proper presence of object in front of camera up to a ceratin distance
            this number may vary for you
        */



        if(n>100)
        {
            x=350-x/n;
            y=230-y/n;
            //the center (x,y) of the screen for me is (350,230) this is the same number at which we want the coordinates of the object to line up
            // if dont know the image resolution you are using you can use 350?=(hav->width)/2 and 230?=(hav->height)/2


            cout<<"x = "<<x<<" & "<<"y = "<<y<<endl;

            Sendapprocommand(); // once we have thee coordinates we send the command to the uC

        }
        else
        {
            cout<<"ball not there"<<endl; // else print ball is not present
        }


    }

    return 0;
}
