#include "VortexConvexButton.h"


VortexConvexButton::VortexConvexButton(std::vector<sf::Vector2f> vertices, std::string idleImage, std::string hoverImage, std::string title, Vortex * gameEngine) {
	
	this->gameEngine = gameEngine;
	mouseOverButton = false;

	this->idleImage = gameEngine->loadImageToTexture(idleImage);
	this->hoverImage = (hoverImage != "") ? gameEngine->loadImageToTexture(hoverImage) : nullptr;

	shape.setTexture(gameEngine->loadImageToTexture(idleImage));
	this->title = title;
	font = *gameEngine->loadFont("Fonts/arial.ttf");
	
	// select the font
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString(title);

	// set the character size
	text.setCharacterSize(28); // in pixels, not points!

	// set the color
	text.setColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	float avgX = 0.0f;
	float avgY = 0.0f;
	shape.setPointCount(vertices.size());
	for (uint i = 0; i < vertices.size(); i++) {
		shape.setPoint(i, vertices[i]);
		avgX += vertices[i].x;
		avgY += vertices[i].y;
	}
	avgX /= vertices.size();
	avgY /= vertices.size();
	text.setPosition(avgX, avgY);
	//shape.setFillColor(sf::Color(50, 50, 50, 255));

}


VortexConvexButton::~VortexConvexButton()
{
}

void VortexConvexButton::update(float delta) {

	if (gameEngine->eventMouseMove) {
		if (mouseOver()) {
			//std::cout << "Mouse over button" << std::endl;
			if (!mouseOverButton){
				mouseOverButton = true;
				shape.setOutlineThickness(5.0f);
				shape.setFillColor(sf::Color(200, 200, 200, 255));
				if (hoverImage != nullptr) {
					shape.setTexture(hoverImage);
				}
			}
			

		} else {
			//std::cout << "Mouse not over button" << std::endl;
			if (mouseOverButton){
				mouseOverButton = false;
				shape.setOutlineThickness(0.0f);
				shape.setFillColor(sf::Color(255, 255, 255, 255));
				if (hoverImage != nullptr) {
					shape.setTexture(idleImage);
				}
			}
			
		}
	}


	gameEngine->getWindow()->draw(shape);
	//gameEngine->getWindow()->draw(text);

}

bool VortexConvexButton::buttonClicked(){

	if (gameEngine->eventMouseReleasedLeft)
		return mouseOver();

	return false;

}

bool VortexConvexButton::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

// Winding number test for a point in a polygon
bool VortexConvexButton::hitPoint(float x, float y) {
	int wn = 0;    // the  winding number counter
	sf::Vector2f mouse(x, y);
	

	// Loop through all edges of the polygon
	for (int i = 0; i < shape.getPointCount(); i++) {
		//If the point y pos is greater or equal to the mouse y pos
		if (shape.getPoint(i).y <= mouse.y) {
			//And it is not the last point of the shape
			if (i < shape.getPointCount() - 1) {	
				//And the next point is greater in y than the mouse y pos
				if (shape.getPoint(i + 1).y > mouse.y) {
					//Check if the mouse point is left or right of the line between the two points
					if (isLeft(shape.getPoint(i), shape.getPoint(i + 1), mouse) > 0) {
						++wn;
					}
				}
				//It is the last vertex point in the shape.
			} else {
				//Use the line between the last point and the first point.
				if (shape.getPoint(0).y > mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(0), mouse) > 0) {
						++wn;
					}
				}
			}
		} else {     
			if (i < shape.getPointCount() - 1) {
				if (shape.getPoint(i + 1).y <= mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(i + 1), mouse) < 0) {
						--wn;
					}
				}
			} else {
				if (shape.getPoint(0).y <= mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(0), mouse) < 0) {
						--wn;
					}
				}
			}
		}
	}
	return (wn != 0);
}

// Tests if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2  on the line
//            <0 for P2  right of the line
int VortexConvexButton::isLeft(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2) {
	return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}


bool VortexConvexButton::mouseOver(){

	sf::Vector2i mouse(gameEngine->getMousePosition().x, gameEngine->getMousePosition().y);
	return hitPoint(gameEngine->getMapPixelToCoords(mouse));

}