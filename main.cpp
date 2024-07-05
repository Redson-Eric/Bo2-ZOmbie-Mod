#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include<vector>
#include <cmath>
#include "func.h"

using namespace std;
DWORD pid;

/*
 *ZM_prison  -> 7A 6D 5F 70 72 I69 73 6F 6E 00
 *ZM_transit -> 7A 6D 5F 74 72 I61 6E 73 69 74
 *Zm_nuked   -> 7A 6D 5F 6E 75 I6B 65 64 00 00
 *ZM_ buried -> 7A 6D 5F 62 75 I72 69 65 64 00
 *zm_dieRise -> 7A 6D 5F 68 69 I67 68 72 69 73 65
*/

/*          Transit
 *  python + mtar ( 48, 24)
 *
 *
 */
DWORD mapAddress = 0x30c3679;

struct Player {
    DWORD healthAddress = 0x21c1568;
    DWORD primaryAmmoAddress = 0x2342b90;
    DWORD secondaryAmmoAddress = 0x2342b98;
    DWORD moneyAddress = 0x2347d68;
    DWORD posXAddress = 0x23427c8;
    DWORD posYAddress = 0x23427cc;
    DWORD posZAddress = 0x23427D0;
    DWORD velXAddress = 0x23427D4;
    DWORD velYAddress = 0x23427D8;
    DWORD weapon1Address = 0x2342a04;
    DWORD weapon2Address = 0x2342a3c;

};

struct HackedValue {
    int ammo = 1337;
    int money = 200000;
    int health = 500;
};

struct SavedPos {
    float x;
    float y;
    float z;
};

void removeGun(DWORD processID, Player target) {
    HANDLE tempHandler = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
    BYTE rmv = 00;
    WriteProcessMemory(tempHandler, (void*)target.weapon1Address, &rmv, sizeof(BYTE), NULL);
    WriteProcessMemory(tempHandler, (void*)target.weapon2Address, &rmv, sizeof(BYTE), NULL);
}

int main() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,4);
    std::cout << "RRRRRRRRRRRRRRRRR   EEEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD\n"
                 "R::::::::::::::::R  E::::::::::::::::::::ED::::::::::::DDD\n"
                 "R::::::RRRRRR:::::R E::::::::::::::::::::ED:::::::::::::::DD\n"
                 "RR:::::R     R:::::REE::::::EEEEEEEEE::::EDDD:::::DDDDD:::::D\n"
                 "  R::::R     R:::::R  E:::::E       EEEEEE  D:::::D    D:::::D\n"
                 "  R::::R     R:::::R  E:::::E               D:::::D     D:::::D\n"
                 "  R::::RRRRRR:::::R   E::::::EEEEEEEEEE     D:::::D     D:::::D\n"
                 "  R:::::::::::::RR    E:::::::::::::::E     D:::::D     D:::::D\n"
                 "  R::::RRRRRR:::::R   E:::::::::::::::E     D:::::D     D:::::D\n"
                 "  R::::R     R:::::R  E::::::EEEEEEEEEE     D:::::D     D:::::D\n"
                 "  R::::R     R:::::R  E:::::E               D:::::D     D:::::D\n"
                 "  R::::R     R:::::R  E:::::E       EEEEEE  D:::::D    D:::::D\n"
                 "RR:::::R     R:::::REE::::::EEEEEEEE:::::EDDD:::::DDDDD:::::D\n"
                 "R::::::R     R:::::RE::::::::::::::::::::ED:::::::::::::::DD\n"
                 "R::::::R     R:::::RE::::::::::::::::::::ED::::::::::::DDD\n"
                 "RRRRRRRR     RRRRJuRRREEEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD\n"<<endl;
    SetConsoleTextAttribute(h, 3);
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"|    Link : https://github.com/Redson-Eric/Bo2-ZOmbie-Mod      |"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    SetConsoleTextAttribute(h, 10);
    cout<<  "F2    : Set Money to 200000\n"
            "F3    : Set Ammo to 1023(Max Value) -> F3\n"
            "1     : Save\n"
            "2     : Load\n"
            "3     : Give useful Gun\n"
            "Space : Jump Boost\n"<<endl;


    HWND wind = FindWindowA(NULL, "Call of Duty : Black Ops II - Zombies");
    GetWindowThreadProcessId(wind, &pid);
    HANDLE handler = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    Player myself;
    HackedValue hacked;
    SavedPos save;
    bool saved = false;
    BYTE mapInGame;
    BYTE weap1;
    float speedX, speedY;
    for(;;) {
        mapInGame = getValueByte(wind, mapAddress);
        if(GetKeyState(VK_F1)<0) {
            WriteProcessMemory(handler, (void*)myself.healthAddress, &hacked.health, sizeof(int), NULL);
        }
        if(GetKeyState(VK_F2)<0) {
            WriteProcessMemory(handler, (void*)myself.moneyAddress, &hacked.money, sizeof(int), NULL);
        }
        if(GetKeyState(VK_F3)<0) {
            WriteProcessMemory(handler, (void*)myself.primaryAmmoAddress, &hacked.ammo, sizeof(int), NULL);
            WriteProcessMemory(handler, (void*)myself.secondaryAmmoAddress, &hacked.ammo, sizeof(int), NULL);
        }
        if(GetKeyState('1')<0) {

            save.x = getValueFloat(wind, myself.posXAddress);
            save.y = getValueFloat(wind, myself.posYAddress);
            save.z = getValueFloat(wind, myself.posZAddress);
            saved = true;
        }
        if(GetKeyState('2')<0 && saved) {
            WriteProcessMemory(handler, (void*)myself.posXAddress, &save.x, sizeof(float), NULL);
            WriteProcessMemory(handler, (void*)myself.posYAddress, &save.y, sizeof(float), NULL);
            WriteProcessMemory(handler, (void*)myself.posZAddress, &save.z, sizeof(float), NULL);
        }
        if(GetKeyState('3')<0) {

            if(mapInGame == 97) {
                //transit
                weap1 = 14;
                WriteProcessMemory(handler, (void*)myself.weapon1Address, &weap1, sizeof(BYTE), NULL);
            }
            if(mapInGame == 114) {
                //Buried
                weap1 = 21;
                WriteProcessMemory(handler, (void*)myself.weapon1Address, &weap1, sizeof(BYTE), NULL);
            }
            if(mapInGame == 105) {
                //mob of the dead
                weap1 = 63;
                WriteProcessMemory(handler, (void*)myself.weapon1Address, &weap1, sizeof(BYTE), NULL);
            }

        }
        if(GetKeyState('4')<0) {
            removeGun(pid, myself);
        }
        if(GetKeyState(VK_SPACE)<0) {
            speedX = getValueFloat(wind, myself.velXAddress) * 1.1;
            speedY = getValueFloat(wind, myself.velYAddress) * 1.1;
            WriteProcessMemory(handler, (void*)myself.velXAddress, &speedX, sizeof(float), NULL);
            WriteProcessMemory(handler, (void*)myself.velYAddress, &speedY, sizeof(float), NULL);

        }

        else {
        }

        Sleep(10);
    }

    return 0;
}

