/*
 * LCircle.h
 * A circle stucture
 * SDL has a built in rectangle structure but we have to make our own circle structure.
 */
#pragma once

#ifndef __LCIRCLE_H__
#define __LCIRCLE_H__
 
struct LCircle {
	int x, y;	// position
	int r;		// radious
};

#endif