#include "RenderObject.h"


RenderObject::RenderObject() {
	zIndex = zIndexlayer::background;
}


RenderObject::~RenderObject() {
}


void RenderObject::setZIndex(zIndexlayer z) {

	zIndex = z;

}
zIndexlayer RenderObject::getZIndex() {

	return zIndex;

}