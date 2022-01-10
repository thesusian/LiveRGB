#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

int clampColor(int color);
void setColor(string device, char hexCol[8]);
int convertQuality(char axis, int simpleQuality);

int main()
{
    // user editable
    int quality = 5;
    float brightness = 1.5;
    int refreshDelay = 10;
    string Device1 = "0";
    string Device2 = "1";

    const unsigned short screenHeight = 1080;
    const unsigned short screenWidth = 1920;

    int yQuality = convertQuality('y', quality);
    int xQuality = convertQuality('x', quality);

    // 0: Red, 1: Green, 2: Blue
    int colors[3][yQuality][xQuality];
    
    Display *d = XOpenDisplay((char *) NULL);
    XImage *image;

    // main loop
    while (true) {
        // get colors from screen
        int y = 0;
        while (y < screenHeight) {
            int x = 0;
            while (x < screenWidth) {
                XColor c;
                image = XGetImage (d, XRootWindow (d, XDefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
                c.pixel = XGetPixel (image, 0, 0);
                XFree (image);
                XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);

                colors[0][y / (screenHeight/yQuality)][x / (screenWidth/xQuality)] = c.red/256;
                colors[1][y / (screenHeight/yQuality)][x / (screenWidth/xQuality)] = c.green/256;
                colors[2][y / (screenHeight/yQuality)][x / (screenWidth/xQuality)] = c.blue/256;

                x += screenWidth/xQuality;
            }
            cout << y << endl;
            y += screenHeight/yQuality;
        }
        
        // add colors and get average
        int rTotal = 0;
        int gTotal = 0;
        int bTotal = 0;
        for (int y = 0; y < yQuality; y++) {
            for (int x = 0; x < xQuality; x++){
                rTotal += colors[0][y][x];
                gTotal += colors[1][y][x];
                bTotal += colors[2][y][x];
            }
        }
        int rAvg = rTotal / (xQuality * yQuality);
        int gAvg = gTotal / (xQuality * yQuality);
        int bAvg = bTotal / (xQuality * yQuality);
        
        // add brightness an limit to 255
        rAvg = clampColor(rAvg * brightness);
        gAvg = clampColor(gAvg * brightness);
        bAvg = clampColor(bAvg * brightness);
        
        // convert RGB color to hex
        char hexAvg[8];
        std::snprintf(hexAvg, sizeof hexAvg, "%02x%02x%02x", rAvg, gAvg, bAvg);

        setColor(Device1, hexAvg);
        setColor(Device2, hexAvg);

        sleep(refreshDelay);
    }

    return 0;
}

int clampColor(int color) {
    if (color > 255) {
        return 255;
    } else if (color < 0) {
        return 0;
    } else {
        return color;
    }
}

void setColor(string device, char hexCol[8]) {
    string cmd("openrgb -d ");
    cmd += device;
    cmd += " -c ";
    cmd += hexCol;

    cout << cmd << endl;

    system(cmd.c_str());
}

int convertQuality(char axis, int simpleQuality) {
    int finalQuality;
    
    if (axis == 'x') {
        switch (simpleQuality) {
        case 10:
            finalQuality = 960;
            break;
        case 9:
            finalQuality = 480;
            break;
        case 8:
            finalQuality = 320;
            break;
        case 7:
            finalQuality = 160;
            break;
        case 6:
            finalQuality = 120;
            break;
        case 5:
            finalQuality = 80;
            break;
        case 4:
            finalQuality = 40;
            break;
        case 3:
            finalQuality = 20;
            break;
        case 2:
            finalQuality = 10;
            break;
        case 1:
            finalQuality = 1;
            break;
        }
    } else if (axis == 'y') {
        switch (simpleQuality) {
        case 10:
            finalQuality = 540;
            break;
        case 9:
            finalQuality = 270;
            break;
        case 8:
            finalQuality = 180;
            break;
        case 7:
            finalQuality = 120;
            break;
        case 6:
            finalQuality = 90;
            break;
        case 5:
            finalQuality = 60;
            break;
        case 4:
            finalQuality = 45;
            break;
        case 3:
            finalQuality = 24;
            break;
        case 2:
            finalQuality = 10;
            break;
        case 1:
            finalQuality = 1;
            break;
        }
    } else {
        cout << "wrong axis in convertQuality" << endl;
    }
    
    return finalQuality;
}
