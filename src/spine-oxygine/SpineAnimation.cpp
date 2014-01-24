#include <spine-oxygine/SpineAnimation.h>

namespace spine {
	static void callback(spAnimationState* state, int trackIndex, spEventType type, spEvent* event, int loopCount) 
	{
		(reinterpret_cast<SpineAnimation*>(state->context))->onAnimationStateEvent(trackIndex, type, event, loopCount);
	}

	SpineAnimation::SpineAnimation(const char* skeletonDataFile, const char* atlasFile, float scale)
		:SpineSkeleton(skeletonDataFile, atlasFile, scale)
	{
		state = spAnimationState_create(spAnimationStateData_create(skeleton->data));
        state->context = this;
        state->listener = callback;
	}

	SpineAnimation::~SpineAnimation()
	{
		spAnimationStateData_dispose(state->data);
		spAnimationState_dispose(state);
	}

	void SpineAnimation::doUpdate(const oxygine::UpdateState& us)
	{
		SpineSkeleton::doUpdate(us);
		spAnimationState_update(state, (float)us.dt / 1000);
        spAnimationState_apply(state, skeleton);
        spSkeleton_updateWorldTransform(skeleton);
	}

	void SpineAnimation::setAnimationStateData(spAnimationStateData* stateData)
	{
		spAnimationStateData_dispose(state->data);
	}

    void SpineAnimation::setMix(const char* fromAnimation, const char* toAnimation, float duration)
	{
		spAnimationStateData_setMixByName(state->data, fromAnimation, toAnimation, duration);
	}

	spTrackEntry* SpineAnimation::setAnimation(int trackIndex, const char* name, bool loop)
	{
		spAnimation* animation = spSkeletonData_findAnimation(skeleton->data, name);
		if (!animation) {
            return 0;
        }
		return spAnimationState_setAnimation(state, trackIndex, animation, loop);
	}

    spTrackEntry* SpineAnimation::addAnimation(int trackIndex, const char* name, bool loop, float delay)
	{
		spAnimation* animation = spSkeletonData_findAnimation(skeleton->data, name);
        if (!animation) {
            return 0;
        }
        return spAnimationState_addAnimation(state, trackIndex, animation, loop, delay);
	}

    spTrackEntry* SpineAnimation::getCurrent(int trackIndex)
	{
		return spAnimationState_getCurrent(state, trackIndex);
	}

    void SpineAnimation::clearTracks()
	{
		spAnimationState_clearTracks(state);
	}

    void SpineAnimation::clearTrack(int trackIndex)
	{
		spAnimationState_clearTrack(state, trackIndex);
	}

	void SpineAnimation::onAnimationStateEvent(int trackIndex, spEventType type, spEvent* event, int loopCount)
	{
		 //if (listenerInstance) (listenerInstance->*listenerMethod)(this, trackIndex, type, event, loopCount);
	}
}