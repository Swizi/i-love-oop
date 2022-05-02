#include "CCar.h"
#include <iostream>

CCar::CCar()
	: m_isTurnedOn(false)
	, m_gear(0)
	, m_speed(0)
	, m_direction(Direction::None)
{
}

CCar::~CCar()
{
}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

short int CCar::GetSpeed() const
{
	return m_speed;
}

short int CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	if (!m_isTurnedOn)
	{
		m_gear = 0;
		m_speed = 0;
		m_direction = Direction::None;
		m_isTurnedOn = true;
	}

	return m_isTurnedOn;
}

bool CCar::TurnOffEngine(std::string& errorMsg)
{
	if (m_isTurnedOn)
	{
		if (m_gear == 0 && m_speed == 0)
		{
			m_isTurnedOn = false;
		}
		else
		{
			errorMsg = "Gear should be 0. Speed should be 0. Current gear is ";
			errorMsg.append(std::to_string(m_gear));
			errorMsg.append(". Current speed is ");
			errorMsg.append(std::to_string(m_speed));

			return false;
		}
	}

	return !m_isTurnedOn;
}

bool CCar::SetGear(short int gear, std::string& errorMsg)
{
	if (m_gear == gear)
	{
		return true;
	}
	if (!m_isTurnedOn)
	{
		errorMsg = "Car is not turned on";

		return false;
	}
	if (m_availableGears.count(gear) == 0)
	{
		errorMsg = "Incorrect gear";

		return false;
	}
	// Сделать читабельнее
	if ((gear == -1 || (m_gear == -1 && gear == 1) || (m_gear == 0 && gear > 0 && m_direction == Direction::Backward)) && m_speed != 0)
	{
		errorMsg = "Speed should be equals to 0. Current speed is ";
		errorMsg.append(std::to_string(m_speed));

		return false;
	}
	SpeedRange availableSpeedRange = m_availableGears[gear];
	if (!(m_speed >= availableSpeedRange.minSpeed && m_speed <= availableSpeedRange.maxSpeed))
	{
		errorMsg = "Cannot switch to switch to this gear. Speed should be in ";
		errorMsg.append(std::to_string(availableSpeedRange.minSpeed));
		errorMsg.append(" .. ");
		errorMsg.append(std::to_string(availableSpeedRange.maxSpeed));

		return false;
	}

	m_gear = gear;
	if (m_speed != 0)
	{
		if (m_gear == -1)
		{
			m_direction = Direction::Backward;
		}
		else
		{
			if (m_gear > 0)
			{
				m_direction = Direction::Forward;
			}
		}
	}

	return true;
}

bool CCar::SetSpeed(const short int speed, std::string& errorMsg)
{
	if (!m_isTurnedOn)
	{
		errorMsg = "Car is not turned on";

		return false;
	}
	if (!(speed >= MIN_SPEED && speed <= MAX_SPEED))
	{
		errorMsg = "Speed should be in ";
		errorMsg.append(std::to_string(MIN_SPEED));
		errorMsg.append(" .. ");
		errorMsg.append(std::to_string(MAX_SPEED));

		return false;
	}
	SpeedRange availableSpeedRange = m_availableGears[m_gear];
	if (!(speed >= availableSpeedRange.minSpeed && speed <= availableSpeedRange.maxSpeed))
	{
		errorMsg = "Cannot switch to this speed. At ";
		errorMsg.append(std::to_string(m_gear));
		errorMsg.append(" gear speed should be in ");
		errorMsg.append(std::to_string(availableSpeedRange.minSpeed));
		errorMsg.append(" .. ");
		errorMsg.append(std::to_string(availableSpeedRange.maxSpeed));

		return false;
	}
	if (m_gear == 0 && speed > m_speed)
	{
		errorMsg = "Speed can not be increased on 0(neutral) gear. Current speed is ";
		errorMsg.append(std::to_string(m_speed));

		return false;
	}

	m_speed = speed;
	if (m_speed == 0)
	{
		m_direction = Direction::None;
	}
	else
	{
		if (m_direction == Direction::None)
		{
			if (m_gear == -1)
			{
				m_direction = Direction::Backward;
			}
			if (m_gear >= 1)
			{
				m_direction = Direction::Forward;
			}
		}
	}

	return true;
}