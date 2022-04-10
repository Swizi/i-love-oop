#include "CCar.h"

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

bool CCar::isTurnedOn() const
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
	}

	m_isTurnedOn = true;
	return m_isTurnedOn;
}

bool CCar::TurnOffEngine()
{
	if (m_isTurnedOn && m_gear == 0 && m_speed == 0)
	{
		m_isTurnedOn = false;
	}
	return !m_isTurnedOn;
}

bool CCar::SetGear(short int gear, std::string& errorMsg)
{
	bool isGearSwitched = false;

	if (m_isTurnedOn)
	{
		if (m_availableGears.count(gear) != 0)
		{
			SpeedRange availableSpeedRange = m_availableGears[gear];

			if ((gear == -1 || (m_gear == -1 && gear == 1) || (m_gear == 0 && gear > 0 && m_direction == Direction::Backward)) && m_speed == 0)
			{
				if (m_speed >= availableSpeedRange.minSpeed && m_speed <= availableSpeedRange.maxSpeed)
				{
					m_gear = gear;
					isGearSwitched = true;

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
				else
				{
					errorMsg = "Cannot switch to switch to this gear. Speed should be in ";
					errorMsg.append(std::to_string(availableSpeedRange.minSpeed));
					errorMsg.append(" .. ");
					errorMsg.append(std::to_string(availableSpeedRange.maxSpeed));
				}
			}
			else
			{
				errorMsg = "Speed should be equals to 0. Current speed is: ";
				errorMsg.append(std::to_string(m_speed));
			}
		}
		else
		{
			errorMsg = "Incorrect gear";
		}
	}
	else
	{
		errorMsg = "Car is not turned on";
	}

	return isGearSwitched;
}

bool CCar::SetSpeed(const short int speed, std::string& errorMsg)
{
	bool isSpeedSwitched = false;

	if (m_isTurnedOn)
	{
		if (speed >= MIN_SPEED && speed <= MAX_SPEED)
		{
			SpeedRange availableSpeedRange = m_availableGears[m_gear];

			if (speed >= availableSpeedRange.minSpeed && speed <= availableSpeedRange.maxSpeed)
			{
				if (!(m_gear == 0 && speed > m_speed))
				{
					m_speed = speed;
					isSpeedSwitched = true;

					if (m_speed == 0)
					{
						m_direction = Direction::None;
					}
				}
				else
				{
					errorMsg = "Speed can not be increased on 0(neutral) gear. Current speed is ";
					errorMsg.append(std::to_string(m_speed));
				}
			}
			else
			{
				errorMsg = "Cannot switch to this speed. At ";
				errorMsg.append(std::to_string(m_gear));
				errorMsg.append(" gear speed should be in ");
				errorMsg.append(std::to_string(availableSpeedRange.minSpeed));
				errorMsg.append(" .. ");
				errorMsg.append(std::to_string(availableSpeedRange.maxSpeed));
			}
		}
		else
		{
			errorMsg = "Speed should be in ";
			errorMsg.append(std::to_string(MIN_SPEED));
			errorMsg.append(" .. ");
			errorMsg.append(std::to_string(MAX_SPEED));
		}
	}
	else
	{
		errorMsg = "Car is not turned on";
	}

	return isSpeedSwitched;
}