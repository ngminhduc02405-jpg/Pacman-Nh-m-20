#include <iostream>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

bool isMusicOn = true;

void drawMenu(int hover) {
    readimagefile("Hinh anh\\background.bmp", 0, 0, 700, 700);
    readimagefile("Hinh anh\\Pacman1.bmp", 100, 50, 600, 200);

    if (hover == 1) readimagefile("Hinh anh\\play.bmp", 290, 240, 410, 360);
    else readimagefile("Hinh anh\\play.bmp", 300, 250, 400, 350);

    if (hover == 2) readimagefile("Hinh anh\\ranking.bmp", 290, 365, 410, 485);
    else readimagefile("Hinh anh\\ranking.bmp", 300, 375, 400, 475);

    if (hover == 3) readimagefile("Hinh anh\\exit.bmp", 290, 490, 410, 610);
    else readimagefile("Hinh anh\\exit.bmp", 300, 500, 400, 600);

    readimagefile("Hinh anh\\help.bmp",25,625,75,675);
	if (isMusicOn)
        readimagefile("Hinh anh\\volumeon.bmp",25,565,75,615);
    else
        readimagefile("Hinh anh\\volumeoff1.bmp",25,565,75,615);
}

void drawSubScreen(const char* title) {
    readimagefile("Hinh anh\\background.bmp", 0, 0, 700, 700);
    readimagefile("Hinh anh\\exit.bmp", 625, 25, 675, 75);
}

void menu(int &thoat) {
    int x = 0, y = 0;
    int hover = 0;
    int page = 0;
    bool inSubMenu = false;
    int currentSub = 0; 
	clearmouseclick(WM_MOUSEMOVE);
    clearmouseclick(WM_LBUTTONDOWN);
    while (kbhit()) getch();
	while (thoat == 0) {
        if (kbhit()) {
            int ch = getch();
            if (ch == 27) {
                if (inSubMenu) {
                    inSubMenu = false;
                    currentSub = 0;
                    clearmouseclick(WM_LBUTTONDOWN);
                } 
            }
        }
		setactivepage(page);
        cleardevice();
		if (ismouseclick(WM_MOUSEMOVE)) {
            getmouseclick(WM_MOUSEMOVE, x, y);
            clearmouseclick(WM_MOUSEMOVE);
            if ((y >= 250 && y <= 350) && (x >= 300 && x <= 400)) hover = 1;
            else if ((y >= 375 && y <= 475) && (x >= 300 && x <= 400)) hover = 2;
            else if ((y >= 500 && y <= 600) && (x >= 300 && x <= 400)) hover = 3;
            else hover = 0;
        }

        if (!inSubMenu) {
            drawMenu(hover);
        } else {
            if (currentSub == 1) drawSubScreen("PLAY - Pacman");
            else if (currentSub == 2) drawSubScreen("RANKING");
            else if (currentSub == 3) drawSubScreen("HELP");
        }

        setvisualpage(page);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            clearmouseclick(WM_LBUTTONDOWN);

            if (!inSubMenu) {
                if ((y >= 250 && y <= 350) && (x >= 300 && x <= 400)) {
                    inSubMenu = true;
                    currentSub = 1;

                    if (isMusicOn) {
                        PlaySound(TEXT("Hinh anh\\theme1.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    }

                } else if ((y >= 375 && y <= 475) && (x >= 300 && x <= 400)) {
                    inSubMenu = true;
                    currentSub = 2;
				} else if ((y >= 625 && y <= 675) && (x >=25 && x <= 75)) {
					inSubMenu = true;
					currentSub = 3;
				}
				 else if ((y >= 500 && y <= 600) && (x >= 300 && x <= 400)) {
                    thoat = 1;

                } else if ((x >= 25 && x <= 75) && (y >= 565 && y <= 615)) {
                    isMusicOn = !isMusicOn;
                    if (!isMusicOn) {
                        PlaySound(NULL, 0, 0);
                    }
                }
            } else {
                if ((x >= 625 && x <= 675) && (y >= 25 && y <= 75)) {
                    inSubMenu = false;
                    currentSub = 0;
                }
            }
        }
		page = 1 - page;
        delay(10);
    }
    closegraph();
}
