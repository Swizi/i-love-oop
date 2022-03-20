// html_decode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp";
#include "html_decode.h";
//::Empty
//% PROGRAM% < % ~dp0\\emptyInput.txt >% OUT% || goto err
//fc% OUT%% ~dp0\\emptyOutputCorrect.txt || goto err
//echo Test 1 passed
//
//::Heavy
//% PROGRAM % < % ~dp0\\heavyInput.txt > % OUT % || goto err
//fc% OUT%% ~dp0\\heavyOutputCorrect.txt || goto err
//echo Test 2 passed
//
//::Standard
//% PROGRAM % < % ~dp0\\standardInput.txt > % OUT % || goto err
//fc% OUT%% ~dp0\\standardOutputCorrect.txt || goto err
//echo Test 3 passed

SCENARIO("Empty")
{
	REQUIRE(html_decode("").empty());
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
