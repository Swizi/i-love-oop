#include "Car.h"
#include "Controller.h"

CController::CController(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](std::istream& strm) {
			   return TurnOn(strm);
		   } },
		  { "TurnOff", bind(&CController::TurnOff, this, std::placeholders::_1) },
		  { "PrintInfo", bind(&CController::PrintInfo, this, std::placeholders::_1) },
		  { "SetGear", bind(&CController::SetGear, this, std::placeholders::_1) },
		  { "SetSpeed", bind(&CController::SetSpeed, this, std::placeholders::_1) }
	  })
{
}

bool CController::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CController::TurnOn(std::istream& /*args*/)
{
	m_car.TurnOnEngine();

	m_output << "Car engine is turned on" << std::endl;

	return true;
}

bool CController::TurnOff(std::istream& /*args*/)
{
	std::string errorMsg = "";

	m_car.TurnOffEngine(errorMsg);

	m_output << "Car engine is turned off" << std::endl;

	return true;
}

bool CController::SetGear(std::istream& args)
{
	int gear = 0;
	std::string errorMsg = "";
	args >> gear;

	m_car.SetGear(gear, errorMsg);

	if (errorMsg != "")
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CController::SetSpeed(std::istream& args)
{
	int velocity = 0;
	std::string errorMsg = "";
	args >> velocity;

	m_car.SetSpeed(velocity, errorMsg);

	if (errorMsg != "")
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CController::PrintInfo(std::istream& /*args*/)
{
	m_output << "Is Engine Turned On: " << (m_car.IsTurnedOn() ? "yes" : "no") << std::endl;
	m_output << "Movement direction: ";
	switch (m_car.GetDirection())
	{
	case Direction::Backward:
		m_output << "backward";
		break;
	case Direction::None:
		m_output << "none";
		break;
	case Direction::Forward:
		m_output << "forward";
		break;
	default:
		break;
	}
	m_output << std::endl;
	m_output << "Speed: " << m_car.GetSpeed() << std::endl;
	m_output << "Gear: " << m_car.GetGear() << std::endl;

	return true;
}

