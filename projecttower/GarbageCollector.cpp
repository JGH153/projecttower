#include "GarbageCollector.h"


GarbageCollector::GarbageCollector() {
}


GarbageCollector::~GarbageCollector() {
}

void GarbageCollector::add(RemovableObject * object) {

	try {

		std::lock_guard<std::mutex> garbageLockGuard(garbageMutex);

		removableObjectList.push_front(RemovableObjectContainer(object, 10));


	} catch (const std::system_error& e) {
		std::cout << "Caught system_error with code " << e.code()
			<< " meaning " << e.what() << '\n';
		std::cin.get();
	}

}

int GarbageCollector::elementsInList() {

	return removableObjectList.size();

}

void GarbageCollector::update() {

	std::lock_guard<std::mutex> garbageLockGuard(garbageMutex);

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