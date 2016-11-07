#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>

class Animation {
public:
	Animation();
	void Animate();
	void SetFrameRate(int rate);
	void SetCurrentFrame(int Frame);
	int GetCurrentFrame();
	int maxFrames;
	bool oscillate;
private:
	int currentFrame;
	int frameInc;
	int frameRate;
	long oldTime;
};

#endif
