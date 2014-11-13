#pragma once
class RemovableObject {
public:
	RemovableObject();
	~RemovableObject();

	virtual void killYourself() = 0;
};

