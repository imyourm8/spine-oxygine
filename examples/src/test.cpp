#include <oxygine-framework.h>
#include <spine-oxygine/SpineSprite.h>

DECLARE_SMART(SpineTest, spSpineTest)
class SpineTest : public oxygine::Actor
{
public:
	SpineTest()
	{
		setSize(oxygine::RootActor::instance->getSize());
		spine::spSpineAnimation anim = new spine::SpineAnimation("spineboy-skeleton.json", "spineboy.atlas");
		anim->setMix("walk", "jump", 0.2f);
        anim->setMix("jump", "walk", 0.4f);
		anim->setAnimation(0, "walk", false);
        anim->addAnimation(0, "jump", false);
        anim->addAnimation(0, "walk", true);
        anim->addAnimation(0, "jump", true);
		anim->setAnchor(0.5, 0.5);
		anim->setPosition(getSize()/2);
		addChild(anim);
	}
private:
	oxygine::Resources res;
};


oxygine::Renderer renderer;
oxygine::Rect viewport;

int main(int argc, char* argv[])
{
	oxygine::Point stage_size(640, 480);

	oxygine::core::init_desc desc;
	oxygine::core::init(&desc);
	oxygine::RootActor::instance = new oxygine::RootActor();
	oxygine::Point size = oxygine::core::getDisplaySize();
	oxygine::RootActor::instance->init(size, stage_size);
	viewport = oxygine::Rect(0, 0, size.x, size.y);
	renderer.setDriver(oxygine::IVideoDriver::instance);
	renderer.initCoordinateSystem(size.x, size.y);

	bool done = false;	

	oxygine::DebugActor::initialize();
	oxygine::RootActor::instance->addChild(new oxygine::DebugActor());

	spSpineTest test = new SpineTest();
	oxygine::RootActor::instance->addChild(test);

	while (!done)
    {
		oxygine::RootActor::instance->update();
		oxygine::Color clear(0, 255, 0, 255);
		if (renderer.begin(0, viewport, &clear)) {
			oxygine::RootActor::instance->render(renderer);
			renderer.end();
			oxygine::core::swapDisplayBuffers();
		}
		done = oxygine::core::update();
    }
	oxygine::ObjectBase::dumpCreatedObjects();
	renderer.cleanup();
	oxygine::core::release();
	oxygine::ObjectBase::dumpCreatedObjects();

	return 0;
}