#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <memory>

#include "Gameobject.h"
#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

// Gameplay variables
	uint32_t time = 0;
	uint32_t score = 0;
	int32_t lives = 0;
	uint32_t star_duration = 0 ;
	double speed = 0;

	uint8_t in_menu = 1;
	int8_t in_menu_highlighted = 0;

	uint8_t debounce = 0;

// Visual constants
	const static uint16_t window_size_x = 1280;
	const static uint16_t window_size_y = 720 ;
	const static double offset = double(window_size_y / 100);

	const auto game_window_colour = Gosu::Color(0xFF333333);
	const auto game_window_colour2 = Gosu::Color(0xFF727272);
	const auto frame_colour = Gosu::Color(0xFF333333);
	const auto scoreboard_colour = Gosu::Color(0xFF333333);
	const auto scoreboard_text_colour = Gosu::Color(0xFFAAAAAA);
	const auto menu_text_colour = Gosu::Color(0xFFAAAAAA);
	const auto menu_text_highlight_colour = Gosu::Color(0xFFFFFFFF);
	const std::string fontname = "font/SolomonS.ttf";

	Gosu::Image scoreboard("scoreboard.png");

class GameWindow : public Gosu::Window
{
public:
	Gosu::Font font;
	Gosu::Image img;
	
	player plyr;
	GameWindow()
		: Window(window_size_x, window_size_y)
		, font(window_size_y / 15, fontname, 1)
		, img("sfw2.png")
		//, plyr({ window_size_x/10*3+2*offset,window_size_y-window_size_x/10+offset, }, "player.png", window_size_x/20+4*offset)
		, plyr({ window_size_x / 10 * 3 + 2 * offset,window_size_y - window_size_x / 10 + offset, }, "player.png", 100)
	{
		set_caption("Anime Tiddies");


	}

	

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt


	void draw_quader(double x, double y, double dx, double dy, Gosu::Color colour, double layer)
	{
		graphics().draw_quad(x, y, colour, x + dx, y, colour, x, y + dy, colour, x + dx, y + dy, colour, layer);

	}

	void start_game()
	{
		score = 0;
		in_menu = 0;
		time = 0;
		lives = 100;
		speed = 0;
		star_duration = 0;
	}
	void highscores()
	{
		in_menu = 2;
	}
	void credits()
	{
		in_menu = 3;
	}
	void post_game()
	{
		in_menu = 4;
	}

	void draw() override
	{

		// Spielhintergrund
		if (!in_menu)
		{
			// Background / Scoreboard
			{
				// Background
				if (star_duration == 0) {
					draw_quader(0.0 + offset, 0.0 + offset, (double(window_size_x) * 7 / 10) - (2 * offset), double(window_size_y) - 2 * offset, game_window_colour, 1.0);
				}
				else {
					if (time%20 <= 10) {
						draw_quader(0.0 + offset, 0.0 + offset, (double(window_size_x) * 7 / 10) - (2 * offset), double(window_size_y) - 2 * offset, game_window_colour, 1.0);
					}
					else {
						draw_quader(0.0 + offset, 0.0 + offset, (double(window_size_x) * 7 / 10) - (2 * offset), double(window_size_y) - 2 * offset, game_window_colour2, 1.0);
					}
				}
				// Scoreboard
				draw_quader(double(window_size_x) * 7 / 10 + offset, 0.0 + offset, (double(window_size_x) * 3 / 10) - (2 * offset), double(window_size_y) - 2 * offset, scoreboard_colour, 1.0);
				// Scoreboard Text
				font.draw("Score ", double(window_size_x) * 7 / 10 + 5 * offset, 5 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw(std::to_string(score/100), double(window_size_x) * 7 / 10 + 5 * offset, 12 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw("Lives ", double(window_size_x) * 7 / 10 + 5 * offset, 25 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw(std::to_string(lives), double(window_size_x) * 7 / 10 + 5 * offset, 32 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw("Star ", double(window_size_x) * 7 / 10 + 5 * offset, 45 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw(std::to_string(star_duration), double(window_size_x) * 7 / 10 + 5 * offset, 52 * offset, 10, 1, 1, scoreboard_text_colour);
				//font.draw("Time ", double(window_size_x) * 7 / 10 + 5 * offset, 45 * offset, 10, 1, 1, scoreboard_text_colour);
				//font.draw(std::to_string(int(time /*/ 60*/)), double(window_size_x) * 7 / 10 + 5 * offset, 52 * offset, 10, 1, 1, scoreboard_text_colour);

			}

			// test
			for (auto& v : vec_gameobject)
			{
				for (auto& g : v)
				{
					g->draw();
				}
			}

			// Floating Objects
			{

			}

			// Moveable Object
			{
				plyr.draw();
			}

		}

		//Menu
		{
			if (in_menu == 1)
			{
				
				// New Game
				if (in_menu_highlighted == 0) font.draw("New Game", double(window_size_x) * 1 / 10 + 5 * offset, 25 * offset, 10, 1, 1, menu_text_highlight_colour);
				else font.draw("New Game", double(window_size_x) * 1 / 10 + 5 * offset, 25 * offset, 10, 1, 1, menu_text_colour);
				// Highscores
				if (in_menu_highlighted == 1) font.draw("Highscores", double(window_size_x) * 1 / 10 + 5 * offset, 45 * offset, 10, 1, 1, menu_text_highlight_colour);
				else font.draw("Highscores", double(window_size_x) * 1 / 10 + 5 * offset, 45 * offset, 10, 1, 1, menu_text_colour);
				// Credits
				if (in_menu_highlighted == 2) font.draw("Credits", double(window_size_x) * 1 / 10 + 5 * offset, 65 * offset, 10, 1, 1, menu_text_highlight_colour);
				else font.draw("Credits", double(window_size_x) * 1 / 10 + 5 * offset, 65 * offset, 10, 1, 1, menu_text_colour);
				// Debugging
				//font.draw(std::to_string(in_menu_highlighted), double(window_size_x) * 1 / 10 + 5 * offset, 85 * offset, 10, 1, 1, menu_text_colour);
				//font.draw(std::to_string(in_menu), double(window_size_x) * 2 / 10 + 5 * offset, 85 * offset, 10, 1, 1, menu_text_colour);
			}
			if (in_menu == 2)
			{
				// Highscores
				font.draw("Highscores", double(window_size_x) * 1 / 10 + 5 * offset, 15 * offset, 10, 1, 1, menu_text_colour);
				font.draw("?XD wer spielt denn sowas", double(window_size_x) * 1 / 10 + 5 * offset, 32 * offset, 10, 1, 1, menu_text_colour);
				// Back
				font.draw("Back", double(window_size_x) * 1 / 10 + 5 * offset, 65 * offset, 10, 1, 1, menu_text_highlight_colour);
			}
			if (in_menu == 3)
			{
				// Credits
				font.draw("Credits", double(window_size_x) * 1 / 10 + 5 * offset, 15 * offset, 10, 1, 1, menu_text_colour);
				font.draw("Enrico Milione", double(window_size_x) * 1 / 10 + 5 * offset, 32 * offset, 10, 1, 1, menu_text_colour);
				font.draw("Nils Hanebuth", double(window_size_x) * 1 / 10 + 5 * offset, 45 * offset, 10, 1, 1, menu_text_colour);
				// Back
				font.draw("Back", double(window_size_x) * 1 / 10 + 5 * offset, 65 * offset, 10, 1, 1, menu_text_highlight_colour);
				img.draw(0.0, 0.0, 0.0, 1, 1);

			}
			if (in_menu == 4)
			{
				// New Score
				font.draw("Your score: " + std::to_string(score/100), double(window_size_x) * 1 / 10 + 5 * offset, 15 * offset, 10, 1, 1, menu_text_colour);
				font.draw("Add your name and press Return", double(window_size_x) * 1 / 10 + 5 * offset, 32 * offset, 10, 1, 1, menu_text_colour);
				// Back
				font.draw("Show Highscores", double(window_size_x) * 1 / 10 + 5 * offset, 65 * offset, 10, 1, 1, menu_text_highlight_colour);


			}
		}


		
	}


	std::vector<std::vector<std::unique_ptr<gameobject>>> vec_gameobject;





		// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		// Debounce
		{
			if (!input().down(Gosu::KB_UP) && debounce == 1) debounce = 0;
			if (!input().down(Gosu::KB_DOWN) && debounce == 2) debounce = 0;
			if (!input().down(Gosu::KB_RETURN) && debounce == 3) debounce = 0;
			if (!input().down(Gosu::KB_RIGHT) && debounce == 4) debounce = 0;
			if (!input().down(Gosu::KB_LEFT) && debounce == 5) debounce = 0;
		}

		// Menu
		if (in_menu)
		{

			// Main Menu
			if (in_menu == 1)
			{
				if (input().down(Gosu::KB_UP) && debounce == 0) {
					in_menu_highlighted--;
					debounce = 1;
				}
				if (input().down(Gosu::KB_DOWN) && debounce == 0) {
					in_menu_highlighted++;
					debounce = 2;
				}

				if (in_menu_highlighted > 2) in_menu_highlighted = 0;
				if (in_menu_highlighted < 0) in_menu_highlighted = 2;

				if (input().down(Gosu::KB_RETURN) && debounce == 0)
				{
					debounce = 3;

					if (in_menu_highlighted == 0)
					{
						start_game();
					}
					if (in_menu_highlighted == 1)
					{
						highscores();
					}
					if (in_menu_highlighted == 2)
					{
						credits();
					}

				}
			}

			// Highsores
			if (in_menu == 2)
			{
				if (input().down(Gosu::KB_RETURN) && debounce == 0)
				{
					debounce = 3;
					in_menu = 1;

				}
			}

			// Credits
			if (in_menu == 3)
			{
				if (input().down(Gosu::KB_RETURN) && debounce == 0)
				{
					debounce = 3;
					in_menu = 1;

				}
			}

			// Post Game
			if (in_menu == 4)
			{
				if (input().down(Gosu::KB_RETURN) && debounce == 0)
				{
					debounce = 3;
					in_menu = 2;

				}
			}
		}

		// Gameplay
		if (!in_menu)
		{	// OBSTACLE SPAWN
			if (time%250==0) //to be changed
			{

				std::vector<std::unique_ptr<gameobject>> v;
				for (int i = 0; i < 7; i++)
				{
					uint8_t a = rand() % 100 + int(time / 10000);
					if (a > 10) {
							// Das Spielfeld ist 7/10 breit, bei 7 Reihen passt das ganz gut. 
						obstacle o1(obstacle({double(2*offset + window_size_x * i / 10) , -window_size_y / 10 }, "box.png", -a, window_size_x/10+2*offset, font));
						auto obstacle_ptr1 = std::make_unique<obstacle>(o1);
						v.push_back(move(obstacle_ptr1));
					}
				}

				vec_gameobject.push_back(move(v));



				//rand() % 6 + 1;
				//std::vector<gameobject> neue_reihe;
				//neue_reihe.push_back();
				//std::vector<std::vector<gameobject>> everything_that_moves;

				/*

				Die Logik:
					Wände:
						Wenn in x Blockreihen nur eine Wand ist => spawne mit y Wahrscheinlichkeit eine neue

						Wenn eine Reihe zuvor eine ist, und drei Reihen zuvor keine => verlängere diese

					Mali:
						Wenn x Blockreihen zuvor keine da sind => spawne neue Reihe

						Spawn:

							Total maximal y Malus

							Maximal z Malus pro Block

					X-Anhängen:
						Werden einfach zufällig verteilt, jedoch y plusminus z mal so viel X-Anhängen wie Mali von der vorherigen Blockreihe zur nächsten

						Können nicht in Mali-Reihen spawnen

					Unverwundbar:
						Spawnen zufällig verteilt

						Können nicht in Mali-Reihen oder X-Anhängen spawnen

				test23.push_back(player({ 100.0, 100.0 }, "planet1.png", 15));


				*/


			}
			// BARRIER SPAWN
			if (time % 125 == 0) //to be changed
			{

				std::vector<std::unique_ptr<gameobject>> v;
				for (int i = 1; i < 7; i++) {
					uint8_t a = rand() % 100 + int(time / 10000);
					uint8_t b = rand() % 4 + 2;
					if (a > 60) {
						// Das Spielfeld ist 7/10 breit, bei 7 Reihen passt das ganz gut. 
						barrier o1(barrier({ double(window_size_x * i / 10)-2*offset , -window_size_y / 10 }, "box.png", 28.8 ,b*100));
						auto barrier_ptr1 = std::make_unique<barrier>(o1);
						v.push_back(move(barrier_ptr1));
					}
				}

				vec_gameobject.push_back(move(v));


			}
			// POWER UP SPAWN 
			if ((time+125)% 250 == 0) //to be changed
			{

				std::vector<std::unique_ptr<gameobject>> v;
				// X_UP SPAWN
				uint8_t a = rand() % 100 + int(time / 10000);
				uint8_t b = rand() % 6 + 0;
				uint8_t c = rand() % 100 + 1;
				if (a > 10 && c > 50) {
					// Das Spielfeld ist 7/10 breit, bei 7 Reihen passt das ganz gut. 

					x_up x1(x_up({ double(2 * offset + window_size_x * b / 10) , -window_size_y / 10 }, "powerup_x_up.png", a, double(window_size_x / 10 + 2 * offset), font));
						
					auto x_up_ptr1 = std::make_unique<x_up>(x1);
					v.push_back(move(x_up_ptr1));
				}
				// STAR SPAWN
				else if (a > 10 && c <= 50) {
					star s1(star({ double(2 * offset + window_size_x * b / 10) , -window_size_y / 10 }, "powerup_star.png", uint8_t(a/10), double(window_size_x / 10 + 2 * offset)));
					
					auto star_ptr1 = std::make_unique<star>(s1);
					v.push_back(move(star_ptr1));
				}
				

				vec_gameobject.push_back(move(v));






			}


			// Game Lost
			if (!lives) post_game();

			// Things The Player Can Do
			if (input().down(Gosu::KB_RIGHT) && debounce == 0)
			{
				if(plyr.pos.get_x() < (2*offset + window_size_x * 6 / 10)) plyr.pos += {6*speed, 0};
				//debounce = 4;
			}
			if (input().down(Gosu::KB_LEFT) && debounce == 0)
			{
				if (plyr.pos.get_x() > 2*offset) plyr.pos -= {6 * speed, 0};
				//debounce = 5;
			}

			// Things The Game Does
			{
				// Compare Stuff
				{
					for (int v = 0; v <vec_gameobject.size();)
					{
						for (int g = 0; g < vec_gameobject[v].size();)
						{
							auto gameobjsize = window_size_x / 14+ 2 * offset;
							if (vec_gameobject[v][g]->pos.get_x() < plyr.pos.get_x() + plyr.getsize() // Hitbox von links
								&& vec_gameobject[v][g]->pos.get_x() > plyr.pos.get_x() - plyr.getsize() // Hitbox von rechts
								&& vec_gameobject[v][g]->pos.get_y() < plyr.pos.get_y() + plyr.getsize() // Hitbox von unten?
								&& vec_gameobject[v][g]->pos.get_y() > plyr.pos.get_y() - plyr.getsize()) // Hitbox von oben? Bruder warum machen diese?
							
							{
								if (vec_gameobject[v][g]->is_star()) {
									star_duration = vec_gameobject[v][g]->getval();
								}
								if (star_duration > 0 && vec_gameobject[v][g]->getval() < 0) {
									vec_gameobject[v].erase(vec_gameobject[v].begin() + g);
								}
								else {
									lives += vec_gameobject[v][g]->getval();
									//score += speed * 100 * vec_gameobject[v][g]->getval();
									vec_gameobject[v].erase(vec_gameobject[v].begin() + g);
								}
								
								
								


							}
							else g++;
						}
						if (vec_gameobject[v].size()) v++;
						else vec_gameobject.erase(vec_gameobject.begin() + v);
						
					}
				}

				// Generating Stuff
				{

				}
				// Destroying Stuff
				{

				}
				// Moving Stuff
				{

					for (auto& v : vec_gameobject)
					{
						for (auto& g : v)
						{
							g->pos += {0, speed};
						}
					}
				}
			}
			if (vec_gameobject.size()) if (vec_gameobject[0].size()) if (vec_gameobject[0][0]->pos.get_y() > window_size_y * 11 / 10)
			{
				vec_gameobject.erase(vec_gameobject.begin());
			}

			time++;
			if (star_duration > 0 && (time%60 == 0)) {
				star_duration--;
			}
			score +=speed;
			speed = 2 + time / 10000 + time * time / 200000000;
			// Spielende
			if (lives < 1 && time) post_game();
		}

		// Variables
		if (in_menu) time = 0;


		// ESC = end the game
		if (input().down(Gosu::KB_ESCAPE)) Gosu::Window::close();
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
	std::cout << "Immer an's ikognito Fenster denken!" << std::endl;
}