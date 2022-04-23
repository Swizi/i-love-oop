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

	// Избавляемся от предупреждения компилятора о том, что он не сможет сгенерировать оператор присваивания
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool PrintInfo(std::istream& args);
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

private:
	// функция-обработчик команды пользователя.
	// Возвращает true, если команда распознана и false, если были ошибки
	using Handler = std::function<bool(std::istream& args)>;

	// Отображает название команды на её обработчик
	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};