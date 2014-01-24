#pragma once
#include <Sprite.h>
#include <spine/spine.h>

namespace oxygine {
	class ResAnim;
}

namespace spine {
	DECLARE_SMART(SpineSkeleton, spSpineSkeleton)
	class SpineSkeleton : public oxygine::Sprite
	{
	public:
		SpineSkeleton(const char* skeletonDataFile, const char* atlasFile, float scale = 1);
		~SpineSkeleton();
		spSkeleton* getSkeleton(){ return skeleton; }
		spBone* getRootBone(){ return rootBone; }
		void setToSetupPose();
        void setBonesToSetupPose();
        void setSlotsToSetupPose();
		void updateWorldTransform();
		spBone* findBone(const char* boneName)const;
		spSlot* findSlot(const char* slotName)const;
		bool setSkin(const char* skinName);
		spAttachment* getAttachment(const char* slotName, const char* attachmentName)const;
		bool setAttachment(const char* slotName, const char* attachmentName);
		void doRender(const oxygine::RenderState& rs);
		void doUpdate(const oxygine::UpdateState& us);
	protected:
		oxygine::ResAnim* const getTextureAtlas(spRegionAttachment* regionAttachment)const;
		spSkeleton* skeleton;
		spBone* rootBone;
		spAtlas* atlas;
		bool premultipliedAlpha;
	};
}