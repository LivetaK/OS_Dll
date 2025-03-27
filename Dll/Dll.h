#pragma once
#ifndef _DLL_H_
#define _DLL_H_

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <string>


using namespace std::chrono;


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

using std::cout;
using std::endl;
using std::wcout;
using std::wstring;
using std::cin;
using std::string;

//extern "C"
//DLL_API void NumberList();

extern "C"
DLL_API milliseconds trukmesSkaiciavimas(high_resolution_clock::time_point pradzia, high_resolution_clock::time_point pabaiga);

extern "C"
DLL_API void controlPanel(int choice);

extern "C"
DLL_API int controlPanelMenu();




#endif