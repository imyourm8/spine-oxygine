#pragma once
#include <res/Resource.h>

namespace oxygine {
	class CreateResourceContext;
	class Resources;
}

namespace spine {
	class SpineResource : public oxygine::Resource
	{
	public:
		static oxygine::Resource* create(oxygine::CreateResourceContext& context);
		static void init();
	protected:
		void loadAnimations(oxygine::CreateResourceContext& context);
		void _load(oxygine::LoadResourcesContext* context = 0);
		void _unload();
	};
}