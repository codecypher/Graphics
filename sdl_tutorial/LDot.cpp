#include "LDot.h"

LDot::LDot(Lesson *ptr) {
    // Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    mCollider = NULL;

    // Set collision circle size
    mColliderCircle.r = DOT_WIDTH / 2;

    // Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    // Max velocity is reduced to 1 pixel per frame 
    // to make the collision easier to see (Lesson 28)
    //DOT_VEL = 1;

    root = ptr;
}


LDot::LDot(int x, int y, Lesson *ptr, bool useCircles) {
    // Initialize the offsets
    mPosX = x;
    mPosY = y;

    // Set collision circle size
    mColliderCircle.r = DOT_WIDTH / 2;

    if (!useCircles) {
        // Create the necessary SDL_Rects
        mColliders.resize(11);

        // Initialize the collision boxes width and height
        mColliders[1].w = 10;
        mColliders[1].h = 1;

        mColliders[2].w = 14;
        mColliders[2].h = 1;

        mColliders[3].w = 16;
        mColliders[3].h = 2;

        mColliders[4].w = 18;
        mColliders[4].h = 2;

        mColliders[5].w = 20;
        mColliders[5].h = 6;

        mColliders[6].w = 18;
        mColliders[6].h = 2;

        mColliders[7].w = 16;
        mColliders[7].h = 2;

        mColliders[8].w = 14;
        mColliders[8].h = 1;

        mColliders[9].w = 10;
        mColliders[9].h = 1;

        mColliders[10].w = 6;
        mColliders[10].h = 1;
    }

    // Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    shiftColliders(useCircles);    // Initialize colliders relative to position

    root = ptr;
}


// Event handler
// We are calculating the velocity as the amount moved per frame. 
// In most games, the velocity is done per second. 
// We are doing it per frame becuase it is easier,
// but we could update the dot's position based on time. 
// Otherwise, just stick with per frame velocity for now.
void LDot::handleEvent(SDL_Event& e) {
    // If a key was pressed
    // We only care when the key was first pressed (e.key.repeat == 0)
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        // Adjust the velocity
        // By setting the velocity, we only have to press the key once.
        switch (e.key.keysym.sym) {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        // Adjust the velocity
        // We have to undo the velocity change when we first pressed the key.
        switch (e.key.keysym.sym) {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}


// Move the dot
void LDot::move(SDL_Rect* wall) {
    // Move the dot left or right
    mPosX += mVelX;

    if (wall == NULL) {
        // If the dot went too far to the left or right
        if ((mPosX < 0) || (mPosX + DOT_WIDTH > root->ScreenWidth)) {
            //Move back
            mPosX -= mVelX;
        }

        //Move the dot up or down
        mPosY += mVelY;

        // If the dot went too far up or down
        if ((mPosY < 0) || (mPosY + DOT_HEIGHT > root->ScreenHeight)) {
            //Move back
            mPosY -= mVelY;
        }
    }
    // Collision Detection
    // Only make the dot move back if we go off the screen or hit the wall.
    else {
        mCollider->x = mPosX;

        // If the dot collided or went too far to the left or right
        if ((mPosX < 0) || (mPosX + DOT_WIDTH > root->ScreenWidth) || root->checkCollision(mCollider, wall)) {
            //Move back
            mPosX -= mVelX;
            mCollider->x = mPosX;
        }
        // Move the dot up or down
        mPosY += mVelY;

        // If the dot collided or went too far up or down
        if ((mPosY < 0) || (mPosY + DOT_HEIGHT > root->ScreenHeight) || root->checkCollision(mCollider, wall)) {
            //Move back
            mPosY -= mVelY;
            mCollider->y = mPosY;
        }
    }
}


// Pretty much the same as above.
// When we move the dot, we move the collider(s) with it. 
// After we move the dot, we check if it went off screen or hit something. 
// If it did then we move the dot back and move its colliders with it.
void LDot::move(std::vector<SDL_Rect> &otherColliders) {
    // Move the dot left or right
    mPosX += mVelX;
    shiftColliders();

    // If the dot collided or went too far to the left or right
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > root->ScreenWidth) || root->checkPixelCollision(mColliders, otherColliders)) {
        // Move back
        mPosX -= mVelX;
        shiftColliders();
    }

    // Move the dot up or down
    mPosY += mVelY;
    shiftColliders();

    // If the dot collided or went too far up or down
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > root->ScreenHeight) || root->checkPixelCollision(mColliders, otherColliders)) {
        // Move back
        mPosY -= mVelY;
        shiftColliders();
    }
}

// Move the dot for scrolling
// This time when moving the dot, we check if the dot moved off the level 
// instead of checking if it moved off the screen since the screen is going to move around the level.
void LDot::move_scroll(void) {
    // Move the dot left or right
    mPosX += mVelX;

    // If the dot went too far to the left or right
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > root->LEVEL_WIDTH)) {
        // Move back
        mPosX -= mVelX;
    }

    // Move the dot up or down
    mPosY += mVelY;

    // If the dot went too far up or down
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > root->LEVEL_HEIGHT)) {
        // Move back
        mPosY -= mVelY;
    }
}

// Like in previous collision detection tutorials, we move along the x axis,
// check collision against the edges of the screen and check against the other scene objects. 
// If the dot hits something we move back. When the dot moves, its colliders move with it.
// Then we do this again for the y axis.
void LDot::move(SDL_Rect& square, LCircle& circle) {
    // Move the dot left or right
    mPosX += mVelX;
    shiftColliders(true);

    // If the dot collided or went too far to the left or right
    if ((mPosX - mColliderCircle.r < 0) || (mPosX + mColliderCircle.r > root->ScreenWidth) || root->checkCollision(mColliderCircle, square) || root->checkCollision(mColliderCircle, circle)) {
        //Move back
        mPosX -= mVelX;
        shiftColliders(true);
    }

    // Move the dot up or down
    mPosY += mVelY;
    shiftColliders(true);

    // If the dot collided or went too far up or down
    if ((mPosY - mColliderCircle.r < 0) || (mPosY + mColliderCircle.r > root->ScreenHeight) || root->checkCollision(mColliderCircle, square) || root->checkCollision(mColliderCircle, circle)) {
        // Move back
        mPosY -= mVelY;
        shiftColliders(true);
    }
}

// Do not worry too much about how shiftColliders works.
void LDot::shiftColliders(bool useCircles) { 
    int r = 0;  // The row offset

    // bounding circles
    if (useCircles) {
        // Align collider to center of dot
        mColliderCircle.x = mPosX;
        mColliderCircle.y = mPosY;
    }
    // bounding boxes
    else {
        // Go through the dot's collision boxes
        for (int set = 0; set < mColliders.size(); ++set) {
            // Center the collision box
            mColliders[set].x = mPosX + (DOT_WIDTH - mColliders[set].w) / 2;

            // Set the collision box at its row offset
            mColliders[set].y = mPosY + r;

            // Move the row offset down the height of the collision box
            r += mColliders[set].h;
        }
    }
}


std::vector<SDL_Rect>& LDot::getColliders() {
    return mColliders;
}

LCircle& LDot::getCollider() {    
    return mColliderCircle;
}


// Show the dot 
void LDot::render(bool useCircle) {
    LCircle mCollider = mColliderCircle;

    // bounding circles
    if (useCircle) {
        // SDL_Rects have their position at the top left 
        // but our circle structure has the position at the center
        // which means we need to offset the render position to the top left 
        // of the circle by subtracting the radius from the x and y position.
        root->gDotTexture->render(mPosX - mCollider.r, mPosY - mCollider.r);
    }
    // bounding boxes
    else {
        root->gDotTexture->render(mPosX, mPosY);
    }
}

void LDot::render(int camX, int camY) {
    // Show the dot relative to the camera
    // by subtracting the camera offset
    root->gDotTexture->render(mPosX - camX, mPosY - camY);
}


int LDot::getPosX() {
    return mPosX;
}

int LDot::getPosY() {
    return mPosY;
}

