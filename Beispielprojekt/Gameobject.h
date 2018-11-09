#pragma once

#include <string>
#include <Gosu\Image.hpp>
#include <Gosu\Font.hpp>
#include <Gosu\Graphics.hpp>
#include "Vektor2d.h"
#include <string>

struct Planet {
	Vektor2d pos;
	double mass;
	Gosu::Image img;
	Planet(Vektor2d pos, double mass, std::string img);
	void draw();
};

class gameobject {
public:
	Vektor2d pos;
	Gosu::Image img;
	virtual ~gameobject() {};
	gameobject(Vektor2d pos, std::string img);
	virtual void draw()=0;
	virtual int8_t getval()=0;
};


class player:public gameobject {
public:
	uint8_t rad;
	virtual ~player() override {};
	player(Vektor2d pos, std::string img, uint8_t rad);
	virtual void draw() override;
	virtual int8_t getval() override;
};

class barrier :public gameobject {
public:
	uint8_t wid;
	uint8_t hig;
	virtual ~barrier() override {};
	barrier(Vektor2d pos, std::string img, uint8_t wid, uint8_t hig);
	virtual void draw() override;
	virtual int8_t getval() override;
};


class obstacle :public gameobject {
public:
	uint8_t wid;
	int8_t val;
	Gosu::Font font;
	virtual ~obstacle() override {};
	obstacle(Vektor2d pos, std::string img, uint8_t val, uint8_t len, Gosu::Font font);
	virtual void draw() override;
	virtual int8_t getval() override;
};

class power_up :public gameobject {
public:
	virtual ~power_up() {};
	power_up(Vektor2d pos, std::string img);
	virtual int8_t getval() override;
	
};

class x_up :public power_up {
public:
	uint8_t val;
	uint8_t rad;
	std::string font;
	virtual ~x_up() override {};
	x_up(Vektor2d pos, std::string img, uint8_t val, uint8_t rad, const std::string& f);
	virtual void draw() override;
	virtual int8_t getval() override;
};

class star :public power_up {
public:
	uint8_t dur;
	uint8_t wid;
	virtual ~star() override {};
	star(Vektor2d pos, std::string img, uint8_t dur, uint8_t wid);
	virtual void draw() override;
	virtual int8_t getval() override;
};





