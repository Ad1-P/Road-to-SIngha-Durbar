#pragma once

#include "SFML/Graphics.hpp"
#include<iostream>

using namespace sf;

class Menu
{
private:
	CircleShape Recir;
	CircleShape Excir;
	Texture RetryTex;
	Texture ExitTex;
	Sprite Retry;
	Sprite Exit;

	//UI
	Font font;
	
	Text gotext;
	Text etext;
	Text rtext;
public:
	Menu() {
		//Loading Textures
		if (RetryTex.loadFromFile("textures/Retry.png") == NULL)
			std::cout << "Texture not Found";
		if (ExitTex.loadFromFile("textures/Exit.png") == NULL)
			std::cout << "Texture not found";
		
		//Circle for retry button
		Recir.setRadius(55.f);
		Recir.setPosition(355.f,200.f);
		Recir.setFillColor(Color(134,136,138,180));
		
		//Circle for exit button
		Excir.setRadius(55.f);
		Excir.setPosition(355.f,350.f);
		Excir.setFillColor(Color(134, 136, 138, 180));

		//Retry button Texture
		Retry.setTexture(RetryTex);
		Retry.setScale(0.4f, 0.4f);
		Retry.setPosition(Recir.getPosition().x - 48.f, Recir.getPosition().y - 47.f);

		//Exit button texture
		Exit.setTexture(ExitTex);
		Exit.setScale(0.1f, 0.1f);
		Exit.setPosition(Excir.getPosition().x + 5.f, Excir.getPosition().y + 5.f);

	
		//texts
		if (font.loadFromFile("Fonts/JungleAdventurer.ttf") == NULL)
			std::cout << "Font not found";

		//Game over Text
		gotext.setFont(font);
		gotext.setCharacterSize(50);
		gotext.setPosition(300.f,100.f);
		gotext.setString("Game Over!");

		//exit text
		etext.setFont(font);
		etext.setCharacterSize(30);
		etext.setPosition(Excir.getPosition().x+20.f,Excir.getPosition().y+Excir.getRadius()*1.7+20.f);
		etext.setString("Exit");

		//retry text
		rtext.setFont(font);
		rtext.setCharacterSize(30);
		rtext.setPosition(Recir.getPosition().x+20.f, Recir.getPosition().y + Recir.getRadius() * 1.7 + 20.f);
		rtext.setString("Retry");
	}

	bool rhover=false;
	bool ehover = false;

	bool RetryMouseHover(RenderWindow &window) {
		if (Mouse::getPosition(window).x <= Recir.getPosition().x + Recir.getRadius()*2 && Mouse::getPosition(window).x >= Recir.getPosition().x && Mouse::getPosition(window).y <= Recir.getPosition().y + Recir.getRadius()*2 && Mouse::getPosition(window).y >= Recir.getPosition().y) {
			Recir.setFillColor(Color(140, 212, 122, 180));
			rhover = true;
			return true;
		}
		else {
			Recir.setFillColor(Color(134, 136, 138, 180));
			rhover = false;
			return false;
		}
	}

	bool ExitMouseHover(RenderWindow& window) {
		if (Mouse::getPosition(window).x <= Excir.getPosition().x + Excir.getRadius() * 2 && Mouse::getPosition(window).x >= Excir.getPosition().x && Mouse::getPosition(window).y <= Excir.getPosition().y + Excir.getRadius() * 2 && Mouse::getPosition(window).y >= Excir.getPosition().y) {
			Excir.setFillColor(Color(140, 212, 122, 180));
			ehover = true;
			return true;
			
		}
		else {
			Excir.setFillColor(Color(134, 136, 138, 180));
			ehover = false;
			return false;
		}
	}

	void drawTo(RenderWindow &window) {
		window.draw(Recir);
		window.draw(Excir);
		window.draw(Retry);
		window.draw(Exit);
		window.draw(gotext);
		if (ehover)
			window.draw(etext);
		if (rhover)
			window.draw(rtext);
	}
};