#include "csgo_auto.h"
#include <iostream>

void auto_accepter::GetWindowResolution() {
    window_width = GetSystemMetrics(SM_CXSCREEN);
    window_height = GetSystemMetrics(SM_CYSCREEN);
}


void auto_accepter::CalculateButtonCoordinates() {
    button_width = 513; //every time set to default
    button_height = 414;

    double ratio = 1024.0 / window_width; //find ratio of default window resolution 1024x768 and current

    if (ratio == 1.0) //if default window resolution = current window resolution
        return;

    button_width /= ratio; //find current window button coordinates
    button_height /= ratio;
}


void auto_accepter::SimMouseClick() {
    INPUT    Input = { 0 };

    Input.type = INPUT_MOUSE; //indicates MOUSE input
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; //press left mouse button
    ::SendInput(1, &Input, sizeof(INPUT)); //send input

    ::ZeroMemory(&Input, sizeof(INPUT)); //clear input info
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP; //release left mouse button
    ::SendInput(1, &Input, sizeof(INPUT)); //send input
}


void auto_accepter::GetCursorPosition(DWORD& posx, DWORD& posy) {
    POINT point;
    if (GetCursorPos(&point)) {
        posx = point.x;
        posy = point.y;
    }
}


void auto_accepter::Start() {
    while (true) {
        Sleep(1000);
        GetWindowResolution();
        CalculateButtonCoordinates();

        if (CheckIfButtonReady()) {
            DWORD cpos_x = 0, cpos_y = 0; //cursor coordinates

            GetCursorPosition(cpos_x, cpos_y); //first get current cursor position

            SetCursorPos(button_width, button_height); //second set cursor position to button coordinates

            SimMouseClick();

            SetCursorPos(cpos_x, cpos_y); //third set cursor position to previous coordinates

            break;
        }
    }
}


bool auto_accepter::CheckIfButtonReady() {
    HDC dc = GetDC(NULL);
    COLORREF colour = GetPixel(dc, button_width, button_height); //get the colour of the pixel

    if (colour == 6212442 || colour == 5287756) { //if the button has the needed colour
        return 1;
    }

    ReleaseDC(NULL, dc);

    return 0;
}