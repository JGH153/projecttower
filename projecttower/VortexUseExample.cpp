#include "VortexUseExample.h"


VortexUseExample::VortexUseExample(Vortex * gameEngine){

	this->gameEngine = gameEngine;



	texImage = gameEngine->loadImageToTexture("Graphics/tile_1.png");


	//particles = new VortexParticleSystem(50000);
	font = gameEngine->loadFont("Fonts/arial.ttf");

	// select the font
	text.setFont(*font); // font is a sf::Font

	text.setPosition(150, 150);

	// set the string to display
	text.setString("Hello world");

	// set the character size
	text.setCharacterSize(28); // in pixels, not points!

	// set the color
	text.setColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);





	testAnimation = new VortexAnimation(300, 300, 112, 170, 24, gameEngine);
	testAnimation->assembleAnimation("Graphics/testAnimation/Boss8_black_hole2_", ".png", 1, 53);

	uint x, y;

	x = 0;
	y = 0;

	uint width = 112;
	uint height = 170;
	uint border = 10;

	for (uint i = 0; i < 30; i++){

		VortexAnimation * temp = new VortexAnimation(x, y, width, height, 25, gameEngine);
		temp->assembleAnimation("Graphics/testAnimation/Boss8_black_hole2_", ".png", 1, 53);
		animations.push_back(temp);

		x += width + border;
		if (x > gameEngine->getWindow()->getSize().x + width){
			x = 0;
			y += height + border;
		}



	}

	sprit = new VortexSprite(*texImage);


	testButton = new VortexButtonRectangle(400, 400, 150, 55, "Graphics/button.png", "Button", gameEngine);













	// first check if an input audio device is available on the system
	if (!sf::SoundBufferRecorder::isAvailable()) {
		// error: audio capture is not available on this system
		std::cout << "NO MICE ON SYSTEM!";
		std::cin.get();
	}


	// start the capture
	recorder.start();

	// wait...
	sf::Time t1 = sf::seconds(2.0f);

	sleep(t1);

	// stop the capture
	recorder.stop();

	// retrieve the buffer that contains the captured audio data
	bufferRecord = recorder.getBuffer();

	

	soundRec.setBuffer(bufferRecord);
	soundRec.setPitch(1.f);
	soundRec.setVolume(100.f);
	soundRec.play();

	bufferRecord.saveToFile("my_record.ogg");


















	//bufferLoadSound = *gameEngine->loadSound("Sound/sound1.wav");
	//sound.setBuffer(bufferLoadSound);
	//sound.play();

	//if (!music.openFromFile("Sound/gameMusic.wav")){
	//	std::cout << "Music error";
	//	std::cin.get();
	//}

	//music.setPitch(1.5);
	//music.setVolume(100);

	////music.play();






	/*testList.push_back(sVar("Greger"));
	testList.push_back(sVar(1.f));
	testList.push_back(sVar('U'));
	testList.push_back(sVar(1));
	testList.push_back(sVar('G'));

	testList[1] = "Sweet";
	testList[2] = 5.98f;

	std::cout << (std::string)testList[1] << " " << (std::string)testList[2];*/








	




}


VortexUseExample::~VortexUseExample()
{
}


void VortexUseExample::update(){

	for (uint i = 0; i < animations.size(); i++){
		animations[i]->update();
	}

	sf::Vector2i mouse = gameEngine->getMousePosition();


	if (testButton->buttonClicked()){
		std::cout << "KNAPP TREYKKET" << std::endl;
		testButton->setPosition(rand() % gameEngine->getWindowSize().x, rand() % gameEngine->getWindowSize().y);
	}


	particles->setEmitter(gameEngine->getMapPixelToCoords(mouse));

	sf::Time elapsed = clock.restart();
	particles->update(elapsed);

	gameEngine->getWindow()->draw(text);

	testButton->update();

	gameEngine->getWindow()->draw(*particles);

	gameEngine->getWindow()->draw(*sprit);

}
