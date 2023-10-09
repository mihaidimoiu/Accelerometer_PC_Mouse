#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include "Serial.cpp"
#include <cstdint>
#include <windows.h>
#include <stdlib.h>
void LeftClickDown()    // Click stanga
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
}
void leftClickUp()
{
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void RightClickDown()    // Click stanga
{

    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
}
void RightClickUp()
{
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void MoveWheel()    // Rotita in jos cu un ecran
{
    mouse_event(MOUSEEVENTF_WHEEL,0,0,-850,0);
}

int _tmain(int argc, _TCHAR* argv[])
{
    printf("Inceperea citirii . . . \n\n");

    Serial* SP = new Serial("COM3");    //Portul

    if (SP->IsConnected())
        printf("Conectat");

    char incomingData[256];			//Prealocarea memoriei
    for(int i = 0 ; i<256; i++)
        incomingData[i] = 0;

    int dataLength = 6;
    int readResult = 0;
    int x=0,y=0,z=0;
    POINT p;    //variabila pentru recuperarea pozitiei curente a mouse-ului
                //respectiv pentru actualizarea pozitiei
    int leftGap = 35;
    int rightGap = -35;

    while(SP->IsConnected())
    {

        system ("cls");
        readResult = SP->ReadData(incomingData,dataLength);
        GetCursorPos(&p);
        // printf("Bytes cititi: (0 = nu sunt date disponibile) %i\n",readResult);
        incomingData[readResult] = 0;

        x = (int)incomingData[0];
        y = (int)incomingData[1];
        z = (int)incomingData[2];


        //Citirea valorilor :
        printf("x = %d\n",x);
        printf("y = %d\n",y);
        printf("z = %d\n\n",z);

        if( (int)incomingData[2] > 'M') //Codul ascii pentru comparare M = 77
        {
            LeftClickDown();
            leftClickUp();

        }
        if( (int)incomingData[1] > '(') //Codul ascii pentru comparare ( = 40
        {
            RightClickDown();
            RightClickUp();
        }
        if( (int)incomingData[0] > '(') //Codul ascii pentru comparare ( = 40
        {
            MoveWheel();
        }
        SetCursorPos( p.x-y, p.y-x );
    }

    return 0;
}
