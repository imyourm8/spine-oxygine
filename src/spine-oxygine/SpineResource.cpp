#include <spine-oxygine/SpineResource.h>
#include <res/Resources.h>
#include <res/CreateResourceContext.h>
#include <pugixml/pugixml.hpp>

namespace spine {
	oxygine::Resource* SpineResource::create(oxygine::CreateResourceContext& context)
	{
		SpineResource* res = new SpineResource();
		res->setName(context.node.attribute("id").value());
		setNode(res, context.node);
		res->loadAnimations(context);
		context.meta = context.meta.next_sibling();
		return res;
	}

	void SpineResource::init()
	{
		oxygine::Resources::registerResourceType(SpineResource::create, "spine_sprite");
	}

	void SpineResource::_load(oxygine::LoadResourcesContext* context)
	{
	}

	void SpineResource::_unload()
	{
	}

	void SpineResource::loadAnimations(oxygine::CreateResourceContext& context)
	{
		pugi::xml_node animation = context.node.first_child();
	}
}