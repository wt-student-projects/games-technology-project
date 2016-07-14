
#include "OptionsWindowSize.h"

OptionsWindowSize::OptionsWindowSize(Window * window)
{
	resolutions.push_back(new Resolution(800, 600));
	resolutions.push_back(new Resolution(1024, 720));
	resolutions.push_back(new Resolution(1280, 720));
	resolutions.push_back(new Resolution(1280, 800));
	resolutions.push_back(new Resolution(1440, 900));
	resolutions.push_back(new Resolution(1600, 900));
	resolutions.push_back(new Resolution(1680, 1024));
	resolutions.push_back(new Resolution(1920, 1080));

	currentResolution = 2;
	colour = { 255, 255, 255 };

	this->window = window;
}

OptionsWindowSize::~OptionsWindowSize()
{
	for (auto& r : resolutions) {
		delete r;
	}

	resolutions.clear();
}

void OptionsWindowSize::onGamepadButton(int key, int state, int elementID)
{
	if (elementID == 2)
	{
		colour = { 255, 0, 0 };

		if (key == SDL_CONTROLLER_BUTTON_DPAD_LEFT && state == GAMEPAD_BUTTON_PRESSED && !window->isFullscreen()) {
			decreaseResolution();
		}

		if (key == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && state == GAMEPAD_BUTTON_PRESSED && !window->isFullscreen()) {
			increaseResolution();
		}
	}
	else
	{
		colour = { 255, 255, 255 };
	}
}

void OptionsWindowSize::create(LocalAssetManager * package)
{
	this->package = package;

	windowSize.setFont(package->getL("data/fonts/Calibri", 60, { 255, 255, 255 }), "Window Size");
	windowSize.setArea(glm::vec2(650, 550), ALIGNMENT::CENTER);
	
	windowSizeLabel.setFont(package->getL("data/fonts/Calibri", 60, { 255, 255, 255 }), "ERROR");
	windowSizeLabel.setArea(glm::vec2(1250, 550), ALIGNMENT::CENTER);
	
	windowSizeButtons[0].setButtonTexture(package->getT("data/textures/left"));
	windowSizeButtons[0].setArea(glm::vec4(1250 - 300, 500, 70, 100), ALIGNMENT::CENTER);
	windowSizeButtons[1].setButtonTexture(package->getT("data/textures/right"));
	windowSizeButtons[1].setArea(glm::vec4(1250 + 250, 500, 70, 100), ALIGNMENT::CENTER);
}

void OptionsWindowSize::render(Renderer2D * renderer)
{
	renderer->renderLabel(&windowSize);
	renderer->renderLabel(&windowSizeLabel);
	renderer->renderButtons(windowSizeButtons, 2);
}

void OptionsWindowSize::update()
{
	SDL_Rect r = window->getWindowDimensions();
	std::string label = "";

	if (r.w != resolutions[currentResolution]->width || r.h != resolutions[currentResolution]->height)
	{
		label = std::to_string(r.w).append("x").append(std::to_string(r.h));

		for (int i = 0; i < resolutions.size(); i++) {
			if (r.w == resolutions[i]->width && r.h == resolutions[i]->height) {
				currentResolution = i;
			}
		}
	}
	else
	{
		label = resolutions[currentResolution]->to_str();
	}

	windowSizeLabel.setFont(package->getL("data/fonts/Calibri", 60, colour), label.c_str());
	windowSizeLabel.setArea(glm::vec2(1250, 550), ALIGNMENT::CENTER);
}

Resolution OptionsWindowSize::convert(std::string text)
{
	Resolution res = Resolution(0, 0);

	res.height = atoi((text.substr(text.find("x") + 1)).c_str());
	res.width = atoi((text.substr(0, text.find("x") - 1)).c_str());

	return res;
}


void OptionsWindowSize::event(SDL_Event& e)
{
	if (windowSizeButtons[1].isPressed(e) && !window->isFullscreen()) {
		increaseResolution();
	}

	if (windowSizeButtons[0].isPressed(e) && !window->isFullscreen()) {
		decreaseResolution();
	}
}

void OptionsWindowSize::increaseResolution()
{
	if (currentResolution + 1 < resolutions.size()) {
		currentResolution++;

		int newHeight = resolutions[currentResolution]->height;
		int newWidth = resolutions[currentResolution]->width;

		if (newHeight <= window->getMaxHeight() && newWidth <= window->getMaxWidth())
		{
			window->resizeWindow(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, newWidth, newHeight);
			window->adjustViewport();
		}

		update();
	}
}

void OptionsWindowSize::decreaseResolution()
{
	if (currentResolution - 1 >= 0) {
		currentResolution--;
	}

	int newHeight = resolutions[currentResolution]->height;
	int newWidth = resolutions[currentResolution]->width;

	if (newHeight <= window->getMaxHeight() && newWidth <= window->getMaxWidth())
	{
		window->resizeWindow(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, newWidth, newHeight);
		window->adjustViewport();
	}

	update();
}