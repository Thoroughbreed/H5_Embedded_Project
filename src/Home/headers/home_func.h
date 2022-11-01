//
// Created by Jan Andreasen on 01/11/2022.
//

#ifndef H5_EMBEDDED_PROJECT_HOME_FUNC_H
#define H5_EMBEDDED_PROJECT_HOME_FUNC_H

/************************* Func prototyping *********************************/
void setupHome();

void printOLED(int x, int y, String text, int textSize = 1);
void updateOLED(int interval);

void onMessageReceived(String& topic, String& payload);

void getTime(int interval = 36000000); // 1 hour
void doPing(int interval);
void actionDoor(bool open = false);

#endif //H5_EMBEDDED_PROJECT_HOME_FUNC_H
