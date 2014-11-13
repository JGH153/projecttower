#include "GarbageCollector.h"


GarbageCollector::GarbageCollector() {
}


GarbageCollector::~GarbageCollector() {
}

void GarbageCollector::add(RemovableObject * object) {

	try {

		//std::cout << "ADDER\n";

		//std::lock_guard<std::mutex> garbageLockGuard(garbageMutex);
		garbageMutex.lock();

		removableObjectListTemp.push_front(RemovableObjectContainer(object));

		garbageMutex.unlock();

		//std::cout << "SLIPPER\n";;

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

	//std::cout << "lol\n";

	garbageMutex.lock();

	while (removableObjectListTemp.size() > 0) {

		//std::cout << "LOOOOOOOOOOOOOOOP\n";
		removableObjectList.push_front(removableObjectListTemp[0]);
		removableObjectListTemp.pop_front();

	}

	garbageMutex.unlock();

	//FUCK, for auto NOT WORKIN, object remain the same!?!?!?!
	//for (auto currentObject : removableObjectList) {
	//for (int i = 0; i < removableObjectList.size(); i ++){
	//	//std::cout << "for: " << currentObject.remainingCycles;
	//	//currentObject.remainingCycles--;
	//	removableObjectList[i].remainingCycles--;
	//	//::cout << " etter: " << currentObject.remainingCycles << std::endl;
	//}

	
	//std::cout << removableObjectList.size() << std::endl;

	while (removableObjectList.size() != 0) {

		//std::cout << "LETER\n";

		auto currentRemovableObjectContainer = removableObjectList[removableObjectList.size() - 1];

		//std::cout << "hmm : " << currentRemovableObjectContainer.remainingCycles << std::endl;

		if (currentRemovableObjectContainer.remainingClock.getElapsedTime().asMilliseconds() > 1000) {

			//std::cout << "SLETTER\n";

			//std::cout << removableObjectList.size() << std::endl;

			currentRemovableObjectContainer.object->killYourself();

			removableObjectList.pop_back();
			//std::cout << "1";
		} else {

			//std::cout << "0";

			break;
			
		}

	}

	


}

int GarbageCollector::getRemovableObjectListSize() {

	return removableObjectList.size();

}