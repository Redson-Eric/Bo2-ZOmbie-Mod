#ifndef FUNC_H
#define FUNC_H

#include <windows.h>
#include<vector>
using namespace std;

DWORD GetPointerAddress(HWND hwnd, DWORD address, vector<DWORD> offsets);
int getValueInt(HWND hwnd, DWORD address);
float getValueFloat(HWND hwnd, DWORD address);
int getValueByte(HWND hwnd, DWORD address);
#endif //FUNC_H
