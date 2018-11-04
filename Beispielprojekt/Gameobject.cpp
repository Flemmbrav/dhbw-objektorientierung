#include "stdafx.h"
#include "Gameobject.h"
#include <Gosu\Image.hpp>
#include <Gosu\Font.hpp>
#include <Gosu\Graphics.hpp>

Planet::Planet(Vektor2d pos, double mass, std::string img)
	: pos(pos)
	, mass(mass)
	, img(img)
{

}

void Planet::draw() {
	
	img.draw_rot(pos.get_x(), pos.get_y(), 0.0, 0.0, 0.5, 0.5, 0.1, 0.1);
}
//***************************************** gameobject *****************************************
gameobject::gameobject(Vektor2d pos, std::string img): pos(pos), img(img)
{
}


//***************************************** player *****************************************
player::player(Vektor2d pos, std::string img, uint8_t rad): gameobject(pos,img),rad(rad)
{
}

void player::draw(){
	//Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), 2 * rad, 2 * rad, Gosu::Color(0xFFFFFF00), 10);
	img.draw(pos.get_x(), pos.get_y(), 10, rad/50, rad/50);
}

//***************************************** barrier *****************************************
barrier::barrier(Vektor2d pos, std::string img, uint8_t wid, uint8_t hig): gameobject(pos, img), wid(wid), hig(hig)
{
}

void barrier::draw() {
	Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), wid, hig, Gosu::Color(0xFF0000FF), 10);
	
}

//***************************************** obstacle *****************************************
obstacle::obstacle(Vektor2d pos, std::string img, uint8_t val, uint8_t wid, const std::string& f) : gameobject(pos, img), val(val), wid(wid), font(f)
{
}

void obstacle::draw() {
	//Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), wid, wid, Gosu::Color(0xFFFF00FF), 10);
	Gosu::Color color;
	Gosu::Font font(wid / 2, font, 1);	
	/* alternatives Farbschema
	0xFF00FFFF cyan
	0xFF0000FF blau
	0xFFFF00FF magenta? Bruder was ist magenta?
	
	standard Farbschema
	0xFF00FF00 grün
	0xFFFFFF00 gelb
	0XFFFF0000 rot
	*/

	if (val <= 50) {
		/* Standard
		color = 0xFF00FF00; // grün
		color.set_red(255 / 50 * val); // addiert bei maximalem wert maximal rot -> farbe wird gelb
		*/
		// alternativ
		color = 0xFF00FFFF; // cyan
		color.set_green(255 - 255 / 50 * val); // subtrahiert je nach wert maximal grün -> farbe wird blau
	}
	else {
		/* Standard
		color = 0xFFFFFF00; // gelb
		color.set_green(255 - 255 / 50 * val); // subtrahiert je nach wert maximal grün -> farbe wird rot
		*/
		// alternativ
		color = 0xFF0000FF; // blau
		color.set_red(255 / 50 * val); // addiert bei maximalem wert maximal rot -> farbe wird MAGENTA BRUDER MAGENTA!!!!!!111

	}
	img.draw(pos.get_x(), pos.get_y(), 10, wid/100, wid/100, color);
	
	font.draw(std::to_string(val), pos.get_x()+wid/40, pos.get_y()+wid/3, 11, 1, 1, Gosu::Color(0xFFFFFFFF));

}

//***************************************** power_up *****************************************
power_up::power_up(Vektor2d pos, std::string img): gameobject(pos, img) 
{
}

//***************************************** x_up *****************************************
x_up::x_up(Vektor2d pos, std::string img, uint8_t val, uint8_t rad, const std::string& f) : power_up(pos, img), val(val), rad(rad), font(f)
{
}

void x_up::draw() {
	//Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), 2 * rad, 2 * rad, Gosu::Color(0xFF00FF00), 10);
	Gosu::Color color;
	Gosu::Font font(rad, font, 1);
	if (val <= 50) {
		/* Standard
		color = 0xFF00FF00; // grün
		color.set_red(255 / 50 * val); // addiert bei maximalem wert maximal rot -> farbe wird gelb
		*/
		// alternativ
		color = 0xFF00FFFF; // cyan
		color.set_green(255 - 255 / 50 * val); // subtrahiert je nach wert maximal grün -> farbe wird blau
	}
	else {
		/* Standard
		color = 0xFFFFFF00; // gelb
		color.set_green(255 - 255 / 50 * val); // subtrahiert je nach wert maximal grün -> farbe wird rot
		*/
		// alternativ
		color = 0xFF0000FF; // blau
		color.set_red(255 / 50 * val); // addiert bei maximalem wert maximal rot -> farbe wird MAGENTA BRUDER MAGENTA!!!!!!111

	}
	
	img.draw(pos.get_x(), pos.get_y(), 10, rad/50, rad/50, color);

	font.draw(std::to_string(val), pos.get_x()+ rad/100, pos.get_y() + (2*rad/3), 11, 1, 1, Gosu::Color(0xFFFFFFFF));
	
}

//***************************************** star *****************************************
star::star(Vektor2d pos, std::string img, uint8_t dur, uint8_t wid) : power_up(pos, img), dur(dur), wid(wid)
{
}

void star::draw() {
	img.draw(pos.get_x(), pos.get_y(), 10, wid/100, wid/100);
	//Gosu::Graphics::draw_triangle(pos.get_x(), pos.get_y()+(wid*2/10), Gosu::Color(0xFFFFFFFF), pos.get_x()+ wid, pos.get_y()+(wid * 2 / 10), Gosu::Color(0xFFFFFFFF), pos.get_x() + wid/2, pos.get_y() + wid, Gosu::Color(0xFFFFFFFF), 10);
	//Gosu::Graphics::draw_triangle(pos.get_x()+wid/2, pos.get_y(), Gosu::Color(0xFFFFFFFF), pos.get_x(), pos.get_y()+ (wid * 8 / 10), Gosu::Color(0xFFFFFFFF), pos.get_x() + wid, pos.get_y()+ (wid * 8 / 10), Gosu::Color(0xFFFFFFFF), 10);
}


