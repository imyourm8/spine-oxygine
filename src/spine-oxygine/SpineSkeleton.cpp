#include <spine-oxygine/SpineSkeleton.h>
#include <oxygine_include.h>
#include <RenderState.h>

namespace spine {
	SpineSkeleton::SpineSkeleton(const char* skeletonDataFile, const char* atlasFile, float scale):atlas(0),premultipliedAlpha(true)
	{
		atlas = spAtlas_readAtlasFile(atlasFile);
        OX_ASSERT(atlas);

        spSkeletonJson* json = spSkeletonJson_create(atlas);
        json->scale = scale;
        spSkeletonData* skeletonData = spSkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
        OX_ASSERT(skeletonData);
        spSkeletonJson_dispose(json);

        skeleton = spSkeleton_create(skeletonData);
		rootBone = skeleton->bones[0];

		setScale(1, -1);
	}

	SpineSkeleton::~SpineSkeleton()
	{
        if (atlas) 
			spAtlas_dispose(atlas);
		spSkeletonData_dispose(skeleton->data);
        spSkeleton_dispose(skeleton);
	}

	void SpineSkeleton::doRender(const oxygine::RenderState& rs)
	{
		_vstyle._apply(rs);
		{
			const oxygine::Color& color = rs.renderer->getPrimaryColor();
			skeleton->r = color.r / (float)255;
			skeleton->g = color.g / (float)255;
			skeleton->b = color.b / (float)255;
			skeleton->a = getAlpha() / (float)255;

			if (premultipliedAlpha) {
				skeleton->r *= skeleton->a;
				skeleton->g *= skeleton->a;
				skeleton->b *= skeleton->a;
			}
		}
		oxygine::vertexPCT2 vertices[4];
		oxygine::vertexPCT2* pv = vertices;
		float att_vertices[8];
		using namespace oxygine;
		typedef unsigned char GLubyte;
		oxygine::Color color;
		oxygine::Vector2 transform_point;
		for (int i = 0, n = skeleton->slotCount; i < n; i++) {
			spSlot* slot = skeleton->drawOrder[i];
			if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) 
				continue;

			spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;
			oxygine::ResAnim* const anim = reinterpret_cast<oxygine::ResAnim*>(getTextureAtlas(attachment));
			setResAnim(anim);
			const oxygine::Diffuse& df = _frame.getDiffuse();

			if (!df.base) 
				continue;

			rs.renderer->setDiffuse(df);
			spRegionAttachment_computeWorldVertices(attachment, slot->skeleton->x, slot->skeleton->y, slot->bone, att_vertices);
			GLubyte r = slot->skeleton->r * slot->r * 255;
			GLubyte g = slot->skeleton->g * slot->g * 255;
			GLubyte b = slot->skeleton->b * slot->b * 255;
			float normalizedAlpha = slot->skeleton->a * slot->a;
			if (df.premultiplied) {
				r *= normalizedAlpha;
				g *= normalizedAlpha;
				b *= normalizedAlpha;
			}
			GLubyte a = normalizedAlpha * 255;
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
			vertices[0].u = attachment->uvs[0];
			vertices[0].v = attachment->uvs[1];
			transform_point.x = att_vertices[0];
			transform_point.y = att_vertices[1];
			transform_point = rs.transform.transform(transform_point);
			vertices[0].x = transform_point.x;
			vertices[0].y = transform_point.y;
			vertices[0].z = 0;
			vertices[0].color = color.rgba();

			vertices[1].u = attachment->uvs[6];
			vertices[1].v = attachment->uvs[7];
			transform_point.x = att_vertices[6];
			transform_point.y = att_vertices[7];
			transform_point = rs.transform.transform(transform_point);
			vertices[1].x = transform_point.x;
			vertices[1].y = transform_point.y;
			vertices[1].z = 0;
			vertices[1].color = color.rgba();

			vertices[2].u = attachment->uvs[2];
			vertices[2].v = attachment->uvs[3];
			transform_point.x = att_vertices[2];
			transform_point.y = att_vertices[3];
			transform_point = rs.transform.transform(transform_point);
			vertices[2].x = transform_point.x;
			vertices[2].y = transform_point.y;
			vertices[2].z = 0;
			vertices[2].color = color.rgba();

			vertices[3].u = attachment->uvs[4];
			vertices[3].v = attachment->uvs[5];
			transform_point.x = att_vertices[4];
			transform_point.y = att_vertices[5];
			transform_point = rs.transform.transform(transform_point);
			vertices[3].x = transform_point.x;
			vertices[3].y = transform_point.y;
			vertices[3].z = 0;
			vertices[3].color = color.rgba();
			rs.renderer->draw(vertices, sizeof(vertices), VERTEX_PCT2);
		}
	}

	void SpineSkeleton::doUpdate(const oxygine::UpdateState& us)
	{
		spSkeleton_update(skeleton, (float)us.dt / 1000);
	}

	void SpineSkeleton::updateWorldTransform () {
		spSkeleton_updateWorldTransform(skeleton);
	}

	void SpineSkeleton::setToSetupPose() {
		spSkeleton_setToSetupPose(skeleton);
	}

	void SpineSkeleton::setBonesToSetupPose() {
		spSkeleton_setBonesToSetupPose(skeleton);
	}

	void SpineSkeleton::setSlotsToSetupPose() {
		spSkeleton_setSlotsToSetupPose(skeleton);
	}

	spBone* SpineSkeleton::findBone(const char* boneName)const {
		return spSkeleton_findBone(skeleton, boneName);
	}

	spSlot* SpineSkeleton::findSlot(const char* slotName)const {
		return spSkeleton_findSlot(skeleton, slotName);
	}

	bool SpineSkeleton::setSkin(const char* skinName) {
		return spSkeleton_setSkinByName(skeleton, skinName) ? true : false;
	}

	spAttachment* SpineSkeleton::getAttachment(const char* slotName, const char* attachmentName)const {
		return spSkeleton_getAttachmentForSlotName(skeleton, slotName, attachmentName);
	}

	bool SpineSkeleton::setAttachment(const char* slotName, const char* attachmentName) {
		return spSkeleton_setAttachment(skeleton, slotName, attachmentName) ? true : false;
	}

	oxygine::ResAnim* const SpineSkeleton::getTextureAtlas(spRegionAttachment* regionAttachment)const
	{
		return reinterpret_cast<oxygine::ResAnim*>(((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject);
	}
}