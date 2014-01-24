#include <spine/spine.h>
#include <spine/extension.h>
#include <oxygine-framework.h>

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path) {
		oxygine::MemoryTexture mt;
		oxygine::file::buffer bf;
		oxygine::file::read(path, bf);
		oxygine::TextureFormat tf = oxygine::string2TextureFormat("8888");
		mt.init(bf, true, tf);
		oxygine::ResAnim* textureAtlas = new oxygine::ResAnim();
		textureAtlas->init(&mt);
		//oxygine::spSprite renderer = new oxygine::Sprite();
		//renderer->setResAnim(textureAtlas);
		self->rendererObject = textureAtlas;
		self->width = textureAtlas->getFrame(0).getFrameSize().x;
		self->height = textureAtlas->getFrame(0).getFrameSize().y;
}

void _spAtlasPage_disposeTexture(spAtlasPage* self) {
		delete self->rendererObject;
}

char* _spUtil_readFile(const char* path, int* length) {
		unsigned int size;
		oxygine::file::buffer bf;
		oxygine::file::read(path, bf);
		size = bf.getSize();
		char* data = new char[size];
		std::copy(bf.data.begin(), bf.data.begin()+size, data);
		*length = size;
		return data;
}
