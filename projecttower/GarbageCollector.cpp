#include "GarbageCollector.h"


GarbageCollector::GarbageCollector() {
}


GarbageCollector::~GarbageCollector() {
}

void GarbageCollector::add(RemovableObject * object) {

	
	removableObjectList.push_front(RemovableObjectContainer(object, 10));

}

void GarbageCollector::update() {

	//FUCK, for auto NOT WORKIN, object remain the same!?!?!?!
	//for (auto currentObject : removableObjectList) {
	for (int i = 0; i < removableObjectList.size(); i ++){
		//std::cout << "for: " << currentObject.remainingCycles;
		//currentObject.remainingCycles--;
		removableObjectList[i].remainingCycles--;
		//::cout << " etter: " << currentObject.remainingCycles << std::endl;
	}

	
	//std::cout << removableObjectList.size() << std::endl;

	while (removableObjectList.size() != 0) {

		

		auto currentRemovableObjectContainer = removableObjectList[removableObjectList.size() - 1];

		//std::cout << "hmm : " << currentRemovableObjectContainer.remainingCycles << std::endl;

		if (currentRemovableObjectContainer.remainingCycles <= 0) {
			currentRemovableObjectContainer.object->killYourself();
			removableObjectList.pop_back();
			//std::cout << "1";
		} else {

			//std::cout << "0";

			break;
			
		}

	}

}