#include "Animation.h"


Animation::Animation() : frames(), playSpeed(MIN_PLAY_SPEED), playTime(0.0f),
currentFrame(0), playing(false), looping(false), interruptible(false), animEndCallback(NULL) {

}

Animation::Animation(const std::vector<Texture>& frames, float playSpeed) : playSpeed(playSpeed), playTime(0.0f),
	currentFrame(0), playing(false), looping(false), interruptible(false), animEndCallback(NULL) {
	SetFrames(frames);
}

void Animation::Play() {
	currentFrame = 0;
	playTime = 0.0f;
	playing = true;
}

// TODO: is there a more efficient way to do this?
// Calling update like this is kind of "spinning"
// would it be better to use some sort of event?
// Or either way would there have to be the same
// calculation each frame
void Animation::Update(float dt) {
	if (!playing) return;
	playTime += dt;
	// Calculates index in frame vector
	// TODO: make speed = time per frame
	currentFrame = (int)floor(playTime * playSpeed);
	if (currentFrame >= frames.size()) {
		currentFrame = frames.size() - 1;
		AnimationEnd();
	}
}

void Animation::AnimationEnd() {
	if (looping) { Play(); return; }
	Stop();
}

void Animation::Stop() {
	playing = false;
	// Invoke callback
	(*animator.*animEndCallback)();
}