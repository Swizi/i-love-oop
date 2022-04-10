#include <iostream>
#include "CCar.h"

void PrintVirtualCarInfo(const CCar& car)
{
    std::cout << "Is Engine Turned On: " << car.isTurnedOn() << std::endl;
    std::cout << "Movement direction: ";
    switch (car.GetDirection())
    {
    case Direction::Backward: 
        std::cout << "backward";
        break;
    case Direction::None:
        std::cout << "none";
        break;
    case Direction::Forward:
        std::cout << "forward";
        break;
    default:
        break;
    }
    std::cout << std::endl;
    std::cout << "Speed: " << car.GetSpeed() << std::endl;
    std::cout << "Gear: " << car.GetGear() << std::endl;
}

int main()
{
    std::string inputData = "";
    std::string errorMsg = "";
    int number = 0;
    CCar virtualCar = CCar();

    while (std::cin >> inputData)
    {
		errorMsg = "";
        inputData = GetLowercasedString(inputData);

        if (inputData == "info")
        {
            PrintVirtualCarInfo(virtualCar);
        }
        if (inputData == "engineon")
        {
            virtualCar.TurnOnEngine();
        }
        if (inputData == "engineoff")
        {
            virtualCar.TurnOffEngine();
        }
        if (inputData == "setgear")
        {
            std::cin >> number;
            
            virtualCar.SetGear(number, errorMsg);
            
            if (errorMsg != "")
            {
                std::cout << errorMsg << std::endl;
            }
        }
        if (inputData == "setspeed")
        {
            std::cin >> number;

            virtualCar.SetSpeed(number, errorMsg);

            if (errorMsg != "")
            {
                std::cout << errorMsg << std::endl;
            }
        }
    }
}
