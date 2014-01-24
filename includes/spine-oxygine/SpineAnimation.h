#pragma once
#include <spine-oxygine/SpineSkeleton.h>

namespace spine {
	DECLARE_SMART(SpineAnimation, spSpineAnimation)
	class SpineAnimation : public SpineSkeleton
	{
	public:
		SpineAnimation(const char* skeletonDataFile, const char* atlasFile, float scale = 1);
		~SpineAnimation();
		spAnimationState* getAnimationState(){ return state; }
		void doUpdate(const oxygine::UpdateState& us);
		void setAnimationStateData(spAnimationStateData* stateData);
        void setMix(const char* fromAnimation, const char* toAnimation, float duration);
		spTrackEntry* setAnimation(int trackIndex, const char* name, bool loop);
        spTrackEntry* addAnimation(int trackIndex, const char* name, bool loop, float delay = 0);
        spTrackEntry* getCurrent(int trackIndex = 0);
        void clearTracks();
        void clearTrack(int trackIndex = 0);
		void onAnimationStateEvent(int trackIndex, spEventType type, spEvent* event, int loopCount);
	private:
		spAnimationState* state;
	};
}