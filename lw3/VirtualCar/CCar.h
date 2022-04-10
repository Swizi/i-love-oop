#pragma once
#include "string_functions.h"
#include "number_functions.h"
#include <map>

struct SpeedRange
{
	short int minSpeed;
	short int maxSpeed;
};

enum class Direction
{
	Backward,
	None,
	Forward
};

class CCar
{
public:
	CCar();
	~CCar();

	bool isTurnedOn() const;
	Direction GetDirection() const;
	short int GetSpeed() const;
	short int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const short int gear, std::string& errorMsg);
	bool SetSpeed(const short int speed, std::string& errorMsg);

private:
	static const short int MIN_SPEED = 0;
	static const short int MAX_SPEED = 150;

	bool m_isTurnedOn;
	short int m_gear;
	short int m_speed;
	Direction m_direction;

	std::map<short int, SpeedRange> m_availableGears =
	{
		{ -1, SpeedRange{ CCar::MIN_SPEED, 20 } },
		{ 0, SpeedRange{ CCar::MIN_SPEED, CCar::MAX_SPEED } },
		{ 1, SpeedRange{ CCar::MIN_SPEED, 30 } },
	    { 2, SpeedRange{ 20, 50 } },
	    { 3, SpeedRange{ 30, 60 } },
	    { 4, SpeedRange{ 40, 90 } },
		{ 5, SpeedRange{ 50, CCar::MAX_SPEED } }
	};
};
