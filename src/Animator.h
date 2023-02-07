#pragma once
#include "Animation.h"
#include <map>
#include <string>
#include <queue>
#include <iostream>

class Animation;

class Animator {

public:
	Animator();
	
	void AddAnimation(const std::string name, Animation& animation);
	void Update(float dt);
	void PlayAnimation(const std::string& animation, bool looping, bool interruptible);
	void PlayOnce(const std::string& animation, bool looping, bool interruptible);

	bool PlayingAnimation() { return playingAnimation; }

	const Texture& GetCurrentFrame();

private:
	// Map of animations to their name
	std::map<std::string, Animation> animMap;
	// Stores animations on deck to be played
	// If one animation is not interruptable, the next
	// will play when it's finished.
	std::queue<std::string> animQueue;
	Animation* currentAnimation;
	bool playingAnimation;
	bool interruptible;
	// Invoked at end of animation
	void AnimEndCallback();
	void ActivateAnimation(Animation* animation, bool interruptible);
};
