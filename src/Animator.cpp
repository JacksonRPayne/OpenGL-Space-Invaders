#include "Animator.h"

Animator::Animator() : animMap(), animQueue(), currentAnimation(), playingAnimation(false), interruptible(true) {}


void Animator::AnimEndCallback() {
	interruptible = true;
	// No queued animations
	if (animQueue.empty()) {
		playingAnimation = false;
		return;
	}
	// Play top member of animation queue
	Animation* queuedAnim = &animMap[animQueue.front()];
	ActivateAnimation(queuedAnim, queuedAnim->Interruptible());
	animQueue.pop();
}


void Animator::AddAnimation(const std::string name, Animation& animation) {
	animation.SetAnimator(this);
	animation.SetAnimEndCallback(&Animator::AnimEndCallback);
	animMap[name] = animation;
}

void Animator::PlayOnce(const std::string& animation, bool looping, bool interruptible) {
	if (currentAnimation != &animMap[animation]) PlayAnimation(animation, looping, interruptible);
}

void Animator::PlayAnimation(const std::string& animation, bool looping=false, bool interruptible=true) {
	if (looping && !interruptible) {
		std::cout << "WARNING: animation " << animation << " is looping and uninterruptable" << std::endl; 
	}
	// Animation doesn't exist in the map
	if (animMap.find(animation) == animMap.end()) {
		std::cout << "ERROR: could not find animation: " << animation << std::endl;
		return;
	}
	// Set animation properties
	// Pitfall of this is that you can't queue two
	// of the same animation with different settings
	Animation* anim = &(animMap[animation]);
	anim->SetLooping(looping);
	anim->SetInterruptible(interruptible);
	// An uninterruptible animation is playing
	if (playingAnimation && !this->interruptible) {
        animQueue.push(animation);
		return;
	}
	if (playingAnimation) currentAnimation->Stop();

	ActivateAnimation(anim, interruptible);
}

void Animator::ActivateAnimation(Animation* animation, bool interruptible) {
	// Activate the animation
	playingAnimation = true;
	currentAnimation = animation;
	this->interruptible = interruptible;
	animation->Play();
}


void Animator::Update(float dt) {
	currentAnimation->Update(dt);
}

const Texture& Animator::GetCurrentFrame() { return currentAnimation->GetCurrentFrame(); }
