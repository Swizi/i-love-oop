#pragma once
#include <istream>
#include <functional>
#include <map>

class CCar;

class CController
{
public:
	class CController(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool PrintInfo(std::istream& args);
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

private:
	// �������-���������� ������� ������������.
	// ���������� true, ���� ������� ���������� � false, ���� ���� ������
	using Handler = std::function<bool(std::istream& args)>;

	// ���������� �������� ������� �� � ����������
	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};