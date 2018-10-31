#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "Planet.h"
#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

uint32_t time = 0;
uint32_t score = 0;
uint32_t lives = 0;

uint8_t in_menu = 1;
int8_t in_menu_highlighted = 0;

uint8_t debounce = 0;

static uint16_t window_size_x = 1280;
static uint16_t window_size_y = 720	;
static double offset = double(window_size_y/100);

auto game_window_colour = Gosu::Color(0xFF333333);
auto frame_colour = Gosu::Color(0xFF333333);
auto scoreboard_colour = Gosu::Color(0xFF333333);
auto scoreboard_text_colour = Gosu::Color(0xFFAAAAAA);
auto menu_text_colour = Gosu::Color(0xFFAAAAAA);
auto menu_text_highlight_colour = Gosu::Color(0xFFFFFFFF);
std::string fontname = "SolomonS.ttf";





/*





	struct Planet {
		Vektor2d pos;
		double mass;
		Gosu::Image img;
		Planet(Vektor2d pos, double mass, std::string img);
//		void draw();
		void draw() {
			img.draw_rot(pos.get_x(), pos.get_y(), 0.0, 0.0, 0.5, 0.5, 0.1, 0.1);
		}
	};

	class gameobject {
	public:
		Vektor2d pos;
		Gosu::Image img;
		virtual ~gameobject() {};
		gameobject(Vektor2d pos, std::string img);
		virtual void draw() {};
	};


	class player :public gameobject {
	public:
		uint8_t rad;
		virtual ~player() override {};
		player(Vektor2d pos, std::string img, uint8_t rad);
//		void draw() override;

		void draw() override {
			Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), 2 * rad, 2 * rad, Gosu::Color(0xFFFFFF00), 10);
			//Gosu::Graphics::draw_rect(0, 0, 100, 100, Gosu::Color(0xFFFFFFFF), 100);
		}

	};

	class barrier :public gameobject {
	public:
		uint8_t wid;
		uint8_t hig;
		virtual ~barrier() override {};
		barrier(Vektor2d pos, std::string img, uint8_t wid, uint8_t hig);
//		virtual void draw() override;

		void draw() override {
			Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), wid, hig, Gosu::Color(0xFF0000FF), 10);
		}
	};


	class obstacle :public gameobject {
	public:
		uint8_t val;
		uint8_t wid;
		Gosu::Font font;
		virtual ~obstacle() override {};
		obstacle(Vektor2d pos, std::string img, uint8_t val, uint8_t len, const std::string &);
//		virtual void draw() override;

		void draw() override {
			Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), wid, wid, Gosu::Color(0xFFFF00FF), 10);
		}
	};

	class power_up :public gameobject {
	public:
		virtual ~power_up() {};
		power_up(Vektor2d pos, std::string img);

	};

	class x_up :public power_up {
	public:
		uint8_t val;
		uint8_t rad;
		Gosu::Font font;
		virtual ~x_up() override {};
		x_up(Vektor2d pos, std::string img, uint8_t val, uint8_t rad, const std::string &);
//		virtual void draw() override;
		
		void draw() override {
			Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), 2 * rad, 2 * rad, Gosu::Color(0xFF00FF00), 10);
		}
	};

	class star :public power_up {
	public:
		uint8_t dur;
		uint8_t wid;
		virtual ~star() override {};
		star(Vektor2d pos, std::string img, uint8_t dur, uint8_t wid);
//		virtual void draw() override;

		void draw() override {
			Gosu::Graphics::draw_triangle((pos.get_x() + wid / 2), pos.get_y(), Gosu::Color(0xFFFFFF00), pos.get_x(), (pos.get_y() + wid), Gosu::Color(0xFFFFFF00), (pos.get_x() + wid), (pos.get_y() + wid), Gosu::Color(0xFFFFFF00), 10);
			Gosu::Graphics::draw_triangle((pos.get_x()), pos.get_y(), Gosu::Color(0xFFFFFF00), (pos.get_x() + wid), pos.get_y(), Gosu::Color(0xFFFFFF00), (pos.get_x() + wid / 2), (pos.get_y() + wid), Gosu::Color(0xFFFFFF00), 10);
		}
	};


	*/











	

class GameWindow : public Gosu::Window
{
public:
	Gosu::Font font;
	Gosu::Image img;
	GameWindow()
		: Window(window_size_x, window_size_y)
		, font(window_size_y/10, fontname, 1)
		, img("sfw2.png")
	{
		set_caption("Anime Tiddies");

		/* Erzeuge Planeten
		planets.push_back(Planet({ 200.0, 200.0 }, 0.1, "planet1.png"));
		planets.push_back(Planet({ 600.0, 200.0 }, 0.1, "planet2.png"));*/
		//planets.push_back(Planet({ 400.0, 500.0 }, 0.1, "planet3.png"));
		//test23.push_back(player({ 100.0, 100.0 }, "planet1.png", 15));

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
		lives = 5;
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
				draw_quader(0.0 + offset, 0.0 + offset, (double(window_size_x) * 7 / 10) - (2 * offset), double(window_size_y) - 2 * offset, game_window_colour, 1.0);
				// Scoreboard
				draw_quader(double(window_size_x) * 7 / 10 + offset, 0.0 + offset, (double(window_size_x) * 3 / 10) - (2 * offset), double(window_size_y) - 2 * offset, scoreboard_colour, 1.0);
				// Scoreboard Text
				font.draw("Score " + std::to_string(score), double(window_size_x) * 7 / 10 + 5 * offset, 5 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw("Time " + std::to_string(int(time / 60)), double(window_size_x) * 7 / 10 + 5 * offset, 25 * offset, 10, 1, 1, scoreboard_text_colour);
				font.draw("Lives " + std::to_string(lives), double(window_size_x) * 7 / 10 + 5 * offset, 45 * offset, 10, 1, 1, scoreboard_text_colour);
			}

			// Floating Objects
			{

			}

			// Moveable Object
			{

			}

		}

		//Menu
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
			font.draw("Your score: "+ std::to_string(score), double(window_size_x) * 1 / 10 + 5 * offset, 15 * offset, 10, 1, 1, menu_text_colour);
			font.draw("Add your name and press Return" , double(window_size_x) * 1 / 10 + 5 * offset, 32 * offset, 10, 1, 1, menu_text_colour);
			// Back
			font.draw("Show Highscores", double(window_size_x) * 1 / 10 + 5 * offset, 65 * offset, 10, 1, 1, menu_text_highlight_colour);
		}




		/*
		bild.draw_rot(pos.get_x(), pos.get_y(), 10.0,
			rot, // Rotationswinkel in Grad
			0.5, 0.5 // Position der "Mitte"
		);

		auto g2 = (gravity * 1000000000000.0).log();

		Vektor2d rose(50.0, 50.0);
		auto g = rose - g2;
		auto s = rose + speed * 1000.0;

		graphics().draw_line(pos.get_x(), pos.get_y(), Gosu::Color::GREEN, input().mouse_x(), input().mouse_y(), Gosu::Color::GREEN, -10.0);
		graphics().draw_line(rose.get_x(), rose.get_y(), Gosu::Color::RED, g.get_x(), g.get_y(), Gosu::Color::RED, 10.0);
		graphics().draw_line(rose.get_x(), rose.get_y(), Gosu::Color::BLUE, s.get_x(), s.get_y(), Gosu::Color::BLUE, 10.0);
		*//*
		for (auto player : vec_player*) {
			player.draw();
		}
		for (auto barrier : vec_barrier*) {
			barrier.draw();
		}
		for (auto obstacle : vec_obstacle*) {
			obstacle.draw();
		}
		for (auto star : vec_star*) {
			star.draw();
		}
		for (auto power_up : vec_power_up*) {
			power_up.draw();
		}*/
		/*for (size_t i = 0; i < test23.size(); i++)
		{
			test23.at(i).draw();
		}*/
		//for (auto Planet : planets) {
		//	Planet.draw();}

		//mein_player.draw();
	}

	//std::vector<std::vector<gameobject>> everything_that_moves;
	//std::vector<Planet> planets;

	//player mein_player = { { 100,100 }, "planet1.png", 10 };
	

	std::vector<std::vector<barrier>> vec_barrier;
	std::vector<std::vector<power_up>> vec_power_up;
	std::vector<std::vector<star>> vec_star;
	std::vector<std::vector<obstacle>> vec_obstacle;
	std::vector<std::vector<player>> vec_player;




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
		if(in_menu)
		{

			// Main Menu
			if (in_menu == 1)
			{
				if (input().down(Gosu::KB_UP) && debounce == 0) {
					in_menu_highlighted--;
					debounce = 1;}
				if (input().down(Gosu::KB_DOWN) && debounce == 0) {
					in_menu_highlighted++;
					debounce = 2;}

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
		{
			//if (!time % (100-time/1000)) //to be changed
			{
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


			// Game Lost
			if (!lives) post_game();

			// Things The Player Can Do
			if (input().down(Gosu::KB_RIGHT) && debounce == 0)
			{
				debounce = 4;
			}
			if (input().down(Gosu::KB_LEFT) && debounce == 0)
			{
				debounce = 5;
			}

			// Things The Game Does
			{
				// Compare Stuff
				{

				}

				// Generating Stuff
				{

				}
				// Destroying Stuff
				{

				}
			}


			time++;
			lives--;
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
}	