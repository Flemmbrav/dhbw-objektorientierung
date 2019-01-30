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
player::player(Vektor2d pos, std::string img, uint8_t dia): gameobject(pos,img),dia(dia)
{
}

void player::draw(){
	//Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), 2 * rad, 2 * rad, Gosu::Color(0xFFFFFF00), 10);
	img.draw(pos.get_x(), pos.get_y(), 10, dia/100, dia/100);
}
int8_t player::getval() {
	return 0;
}
int8_t player::getsize() {
	return dia;
}

bool player::is_star() {
	return false;
}


//***************************************** barrier *****************************************
barrier::barrier(Vektor2d pos, std::string img, uint8_t wid, uint8_t hig): gameobject(pos, img), wid(wid), hig(hig)
{
}

void barrier::draw() {
	Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), wid, hig, Gosu::Color(0xFF0000FF), 10);
	
}
int8_t barrier::getval() {
	return 10000;
}
int8_t barrier::getsize() {
	return wid;
}
bool barrier::is_star() {
	return false;
}

//***************************************** obstacle *****************************************
obstacle::obstacle(Vektor2d pos, std::string img, uint8_t val, uint8_t wid, Gosu::Font font) : gameobject(pos, img), val(val), wid(wid), font(font)
{
	
}

void obstacle::draw() {
	//Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), wid, wid, Gosu::Color(0xFFFF00FF), 10);
	Gosu::Color color;
	
	if ((-val) <= 50) {
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
	
	font.draw(std::to_string(-val), pos.get_x()+wid/30, pos.get_y()+wid/4, 11, 1, 1, Gosu::Color(0xFF000000));

}
int8_t obstacle::getval(){
	return val;
}

int8_t obstacle::getsize() {
	return wid;
}

bool obstacle::is_star() {
	return false;
}

//***************************************** power_up *****************************************
power_up::power_up(Vektor2d pos, std::string img): gameobject(pos, img) 
{
}
int8_t power_up::getval() {
	return 10001;
}
int8_t power_up::getsize() {
	return 0;
}

bool power_up::is_star() {
	return false;
}

//***************************************** x_up *****************************************
x_up::x_up(Vektor2d pos, std::string img, uint8_t val, uint8_t dia, Gosu::Font font) : power_up(pos, img), val(val), dia(dia), font(font)
{
}

void x_up::draw() {
	//Gosu::Graphics::draw_rect(pos.get_x(), pos.get_y(), 2 * rad, 2 * rad, Gosu::Color(0xFF00FF00), 10);
	Gosu::Color color;
	//Gosu::Font font(rad, font, 1);
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
	
	img.draw(pos.get_x(), pos.get_y(), 10, dia/100, dia/100, color);

	font.draw(std::to_string(val), pos.get_x()+ dia/10, pos.get_y() + (dia/4), 11, 0.7, 0.7, Gosu::Color(0xFFFFFFFF));
	
}

int8_t x_up::getval() {
	return val;
}

int8_t x_up::getsize() {
	return dia;
}

bool x_up::is_star() {
	return false;
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
int8_t star::getval() {
	return dur;
}

int8_t star::getsize() {
	return wid;
}

bool star::is_star() {
	return true;
}

