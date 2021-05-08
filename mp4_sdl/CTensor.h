/*
 * Lesson 4: Key Presses
 * We learn to handle keyboard input.
 */
#pragma once

#ifndef __CTENSOR_H__
#define __CTENSOR_H__

#include <SDL2/SDL.h>

#include <stdio.h>
#include <string>

#include <iostream>

#include "xtensor-blas/xlinalg.hpp"

 //#include <xtensor/xarray.hpp>
 //#include <xtensor/xio.hpp>
 //#include <xtensor/xview.hpp>

// Global Variables


class CTensor {
public:
	// Constants
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;
	const float ScaleFactor = 0.015f;
	const int WorldSize = 1000;

	std::vector<std::vector<int>> vPoints;        // vector list

private:
	int hello_xtensor();
	int xtensor_tutorial();
	int la_review();

public:
	CTensor();
	int main(int argc, char** argv);
};

#endif