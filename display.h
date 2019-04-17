#pragma once
class Grid;

void updateWorldGrid(Grid * worldGrid);
void displayWindow();
void testDisplay();
void renderScene();
static void displayGrid(void);
void setOrtho();
void resetPerspectiveProjection();
void update(int value);
void resize(int width, int height);
void renderBitmapString(float x, float y, void *font, const char *string);