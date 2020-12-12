#pragma once

#include<iostream>
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

#include<cstdlib>

class menu
{
public:
	menu() {}
	menu(sf::Color bgcolor,sf::Color color)
	{

		rect.setSize(sf::Vector2f(125.f, 100.f));
		rect.setOutlineColor(bgcolor);
		rect.setFillColor(color);
		rect.setOutlineThickness(5.f);
		rect.setPosition(sf::Vector2f(325.f, 270.f));


	}
	void changebg(sf::Color color)
	{
		rect.setOutlineColor(color);
	}
	
	void loadtex1(sf::Texture& texture)
	{
		durbar.setTexture(texture);
		durbar.setScale(sf::Vector2f(1.f, 1.5f));
	}
	void loadtex2(sf::Texture& texture, sf::RenderWindow &window)
	{
		playbutton.setTexture(texture);
		playbutton.setScale(sf::Vector2f(0.12f,0.12f));
		playbutton.setPosition(sf::Vector2f(window.getSize().x / 2-80.f, window.getSize().y / 2-50.f));

	}
	void tecst(sf::Font& font, sf::Color color)
	{
		text.setFont(font);
		text.setCharacterSize(35);
		text.setPosition(sf::Vector2f(175.f, 125.f));
		text.setStyle(sf::Text::Bold);
		text.setString("ROAD TO SINGHADURBAR");
		text.setFillColor(color);

	}
	void drawto(sf::RenderWindow& window)
	{
		window.draw(durbar);
		window.draw(text);
		window.draw(playbutton);
		window.draw(rect);
	}
	bool ismouseover(sf::RenderWindow& window)
	{
		float mousex = sf::Mouse::getPosition(window).x;
		float mousey = sf::Mouse::getPosition(window).y;

		float rectx = rect.getPosition().x;
		float recty = rect.getPosition().y;

		float wholex = rect.getPosition().x + rect.getLocalBounds().width;
		float wholey = rect.getPosition().y + rect.getLocalBounds().height;

		if (mousex < wholex && mousex > rectx && mousey<wholey && mousey>recty)
		{
			return true;
		}
		return false;
	}
	bool ismousepressed(sf::RenderWindow& window)
	{
		float mousex = sf::Mouse::getPosition(window).x;
		float mousey = sf::Mouse::getPosition(window).y;

		float rectx = rect.getPosition().x;
		float recty = rect.getPosition().y;

		float wholex = rect.getPosition().x + rect.getLocalBounds().width;
		float wholey = rect.getPosition().y + rect.getLocalBounds().height;

		if (mousex < wholex && mousex > rectx && mousey<wholey && mousey>recty)
		{
			return true;
		}
		return false;
	}
private:
	sf::Sprite durbar;
	sf::Sprite playbutton;

	sf::RectangleShape rect;
	sf::Text text;

};