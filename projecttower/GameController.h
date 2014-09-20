#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"

#include "Tower.h"
#include "BasicUnit.h"
#include "SubController.h"
#include "VortexConvexButton.h"

#include "GameGuiController.h"

class GameController : public SubController
{
public:
	GameController(Vortex * gameEngine);
	~GameController();
	std::vector<Tower*> towers;
	std::vector<Unit*> units;

	GameGuiController * gameGuiController;

	

	void update();
	
private:

	void renderBG();
	void renderTiles();

	VortexSprite bgSprite;

	std::vector<VortexSprite> mapTiles;

<<<<<<< HEAD
	std::vector <Entity *> entityList;
	std::vector <VortexConvexButton> buttonList;
=======
	std::vector <Unit *> unitList;
>>>>>>> c1cab4e80390af29b9c54ea5972f8a7f117ac331

};

