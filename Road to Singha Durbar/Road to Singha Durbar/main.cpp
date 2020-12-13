#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<cstdlib>
#include<vector>
#include "menu.h"
#include "ExitScreen.h"

using namespace sf;

const Vector2f windowsize(800, 600);

class Entity
{
public:
	Sprite sprite;
	Texture texture;
};

class Player :public Entity
{
public:
	int HP;
	int HPmax;

	RectangleShape rect;

	Player()
	{
		this->HPmax = 10;
		this->HP = this->HPmax;
		this->texture.loadFromFile("textures/cartop.png");
		this->sprite.setTexture(texture);
		//this->sprite.rotate(90.f);
		this->sprite.setScale(1.5f, 1.5f);
		this->sprite.setPosition(windowsize.x / static_cast<float>(2) - sprite.getGlobalBounds().width, windowsize.y - 10 - sprite.getGlobalBounds().height);
		std::cout << "Loaded player" << std::endl;
	}
	~Player()
	{
		std::cout << "Deleted Player" << std::endl;
	}
};


class Enemycar :public Entity
{
public:
	Enemycar(Texture* tex)
	{
		this->sprite.setTexture(*tex);
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setPosition(rand() % 500+125, 0.f);
		std::cout << "Enemycar spawned" << std::endl;
	}
};

int main()
{
	//window seetings
	srand(time(NULL));
	RenderWindow window(VideoMode(windowsize.x, windowsize.y), "ROAD TO SINGHA DURBAR");
	Image icon;
	icon.loadFromFile("textures/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setFramerateLimit(60);

	//boolean
	bool gamecomplete = false;

	//time
	Clock time;
	Clock speed_clock;

	//collision sound
	SoundBuffer colllison;
	colllison.loadFromFile("sounds/collision.wav");
	Sound colision_sound;
	colision_sound.setBuffer(colllison);

	//enemycar texture
	Texture enemycar_texture;
	enemycar_texture.loadFromFile("textures/enemycar.png");

	//pithole texture
	Texture pithole_texture;
	pithole_texture.loadFromFile("textures/crack_hole.png");

	//background
	Sprite background;
	Texture background_texture;
	background_texture.loadFromFile("textures/background-1.png");
	background.setTexture(background_texture);
	background.setScale(1.65f, 1.65f);

	//collision animation
	Sprite collisionsp;
	Texture collisiontex;
	collisiontex.loadFromFile("textures/explosionsheet.png");
	collisionsp.setTexture(collisiontex);

	//font and text
	Font font;
	Text text;
	if(font.loadFromFile("Fonts/JungleAdventurer.ttf")== NULL)
		std::cout<<"Font not found";
	text.setFont(font);
	text.setString("Life Damage");
	text.setCharacterSize(50);
	text.setPosition(windowsize.x / 2 - 20, windowsize.y / 2 - 10);

	Text secondss;
	secondss.setFont(font);
	secondss.setCharacterSize(30);
	secondss.setPosition(10.f, 10.f);

	int collided = 0;

	int count = 0;

	int score = 0;

	std::string scored;

	int enemyspawntimer = 0;

	int pithole_spawntimer = 0;

	int line_generator = 0;

	float speed = 3.0f;

	Player player;

	std::vector<Enemycar> enemycars;

	//UI
	Menu ExMenu;

	RectangleShape hpbar, hpbarout;
	hpbarout.setOutlineThickness(2);
	hpbarout.setOutlineColor(Color::White);
	hpbar.setPosition(595.f,10.f);
	hpbarout.setPosition(hpbar.getPosition());
	hpbar.setFillColor(Color::Red);
	hpbarout.setSize(Vector2f(20.f * player.HP, 10.f));

	// Main Menu
	menu menu1(Color::Black, Color::Transparent);
	Texture menuBg;
	if (menuBg.loadFromFile("textures/singhadurbar.png") == NULL)
		std::cout << "Texture not found";
	menu1.loadtex1(menuBg);
	menu1.tecst(font, Color::Red);
	Texture play;
	if (play.loadFromFile("textures/button.png") == NULL)
		std::cout << "Texture not found";
	menu1.loadtex2(play, window);

	//management
	bool Run=false;

	//std::vector<pithole> pitholes;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::MouseMoved)
			{
				if (menu1.ismouseover(window))
					menu1.changebg(sf::Color::White);
				else
					menu1.changebg(sf::Color::Black);
			}
			if (menu1.ismousepressed(window))
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					Run = true;
			}
		}

		//UI
			//retry button press
		if (ExMenu.RetryMouseHover(window) == true) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				player.HP = 10;
				time.restart();
				speed = 3.0f;
				enemycars.clear();
			}
		}

		//exit button press
		if (ExMenu.ExitMouseHover(window) == true) {
			if (Mouse::isButtonPressed(Mouse::Left))
				window.close();
		}
		hpbar.setSize(Vector2f(20.f * player.HP, 10.f));

		if (player.HP > 0 && Run)
		{
			//game completion check
			if (time.getElapsedTime().asSeconds() >= 69)
			{
				gamecomplete = true;
				std::cout << "Game complete" << std::endl;
			}
			score = int(time.getElapsedTime().asSeconds());
			//std::cout << score << std::endl;
			secondss.setFillColor(Color::Red);
			secondss.setString("Score: " + std::to_string(score));
			//player update
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
			{
				player.sprite.move(-5.0f, 0);
				std::cout << "moved left" << std::endl;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
			{
				player.sprite.move(5.0f, 0);
				std::cout << "moved right" << std::endl;
			}
			//player collision with window
			if (player.sprite.getPosition().x <= 127)
			{
				player.sprite.setPosition(127.f, player.sprite.getPosition().y);
				std::cout << "cannot moved left" << std::endl;
			}
			if (player.sprite.getPosition().x >= window.getSize().x - player.sprite.getGlobalBounds().width - 125.f)
			{
				player.sprite.setPosition(window.getSize().x - player.sprite.getGlobalBounds().width - 125.f, player.sprite.getPosition().y);
				std::cout << "cannot moved right" << std::endl;
			}
			if (!gamecomplete)
			{
				//movement update
				if (speed_clock.getElapsedTime().asSeconds() > 5)
				{
					speed += 0.5;
					std::cout << speed_clock.getElapsedTime().asSeconds() << std::endl;
					speed_clock.restart().Zero;
					std::cout << speed_clock.getElapsedTime().asSeconds() << std::endl;
					std::cout << "Speed increased" << std::endl;
				}

				//enmeycar update
				if (enemyspawntimer < 50)
					enemyspawntimer++;
				if (enemyspawntimer >= 50)
				{
					enemycars.push_back(Enemycar(&enemycar_texture));
					enemyspawntimer = 0;
				}
			}
			//collision with player and enemy
			for (size_t i = 0; i < enemycars.size(); i++)
			{
				enemycars[i].sprite.move(0.f, speed);
				if (enemycars[i].sprite.getPosition().y > window.getSize().y)
				{
					enemycars.erase(enemycars.begin() + i);
					std::cout << "Enemycar out of bound" << std::endl;
					break;
				}
				if (enemycars[i].sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
				{
					collided = 1;
					colision_sound.play();
					std::cout << "collison sound playing" << std::endl;
					collisionsp.setPosition(enemycars[i].sprite.getPosition().x, enemycars[i].sprite.getPosition().y);
					enemycars.erase(enemycars.begin() + i);
					std::cout << "Enemycar collided with player" << std::endl;
					player.HP -= 2;
					std::cout << "player HP:" << player.HP << std::endl;
					break;
				}
			}
		}
			//draw
			window.clear();
			window.draw(background);
			window.draw(player.sprite);
			if (!gamecomplete)
			{
				if (collided == 1)
				{
					if (count == 0)
						collisionsp.setTextureRect(IntRect(0, 0, 120, 120));
					if (count == 1)
						collisionsp.setTextureRect(IntRect(120, 0, 120, 120));
					if (count == 2)
						collisionsp.setTextureRect(IntRect(120 * 2, 0, 120, 120));
					if (count == 3)
						collisionsp.setTextureRect(IntRect(120 * 3, 0, 120, 120));
					if (count == 4)
						collisionsp.setTextureRect(IntRect(0, 120, 120, 120));
					if (count == 5)
						collisionsp.setTextureRect(IntRect(120, 120, 120, 120));
					if (count == 6)
						collisionsp.setTextureRect(IntRect(120 * 2, 120, 120, 120));
					if (count == 7)
						collisionsp.setTextureRect(IntRect(120 * 3, 120, 120, 120));
					if (count == 8)
					{
						collisionsp.setTextureRect(IntRect(0, 240, 120, 120));
						collided = 0;
						count = 0;
					}
					count++;
					window.draw(collisionsp);
				}
				for (size_t i = 0; i < enemycars.size(); i++)
				{
					window.draw(enemycars[i].sprite);
				}
				window.draw(secondss);
			}
		if(player.HP <=0)
			ExMenu.drawTo(window);		

		window.draw(hpbarout);
		window.draw(hpbar);

		if (Run == false)
			menu1.drawto(window);
		else
			Run = true;

		window.display();
	}
	return 0;
}