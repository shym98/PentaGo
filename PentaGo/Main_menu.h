#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;

void menu(RenderWindow &window)
{
	/*Background*/

	Texture Reich;
	Reich.loadFromFile("zighail.png");
	Sprite Fuhrer;
	Fuhrer.setTexture(Reich);
	Fuhrer.setTextureRect(IntRect(0, 0, 830, 800));
	Fuhrer.setPosition(0, 0);

	Font font1;
	font1.loadFromFile("COPRGTL.ttf");
	Text text1("New game", font1, 60);
	text1.setColor(Color::Blue);
	text1.setStyle(sf::Text::Bold | sf::Text::Italic);
	Text text2("Quit", font1, 60);
	text2.setColor(Color::Blue);
	text2.setStyle(sf::Text::Bold | sf::Text::Italic);
	text1.setPosition(220, 200);
	text2.setPosition(300, 600);

	bool isMenu = true;

	int menuNum;

	while (isMenu)
	{
		Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		menuNum = 0;
		
		window.clear();

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			if (text1.getGlobalBounds().contains(pos.x,pos.y)) isMenu = false; 
			if (text2.getGlobalBounds().contains(pos.x, pos.y))  { window.close(); isMenu = false; }
		}

		window.draw(Fuhrer);
		window.draw(text1);
		window.draw(text2);
		window.display();
	}

}

string itos(int a)
{
	string res;
	while (a)
		res += char(a % 10 + 48), a /= 10;
	reverse(res.begin(), res.end());
	return res;
}

int ftoi(string a)
{
	int res = 0;
	for (int i = 0; i < a.size(); i++)
	{
		res *= 10;
		res += a[i] - '0';
	}
	return res;
}