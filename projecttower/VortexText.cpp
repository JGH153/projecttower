#include "VortexText.h"


VortexText::VortexText() {
}


VortexText::~VortexText() {
}


void VortexText::update() {


}


std::vector<RenderData>  VortexText::getRenderData() {

	std::vector<RenderData> returnVector;
	returnVector.push_back(RenderData(this));
	return returnVector;

}