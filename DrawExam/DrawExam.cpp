#include <iostream>
#include <string>
#include "CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include "CPerson.h"
#include "CCat.h";

int main()
{
    /*
    ���������� ��� ������ ������� Draw ����� � ������� ����� � ���:
        /\
       /  \
      / O  \
     --------
      |    |
      |    |
      ------
      �� 8 ������ (8-6-4)
    */
    CCoutCanvas canvas;

    std::cout << "Home" << std::endl;
    // ���
    CRectangle wall;
    CTriangle roof;
    CEllipse window;
    roof.Draw(canvas);
    window.Draw(canvas);
    wall.Draw(canvas);
    std::cout << "Cat" << std::endl;
    // ���
    CEllipse body;
    CEllipse head;
    body.Draw(canvas);
    head.Draw(canvas);


    /* ������� �������������.
     ����������� � ���� ��� ������ CopyState ��������� �� ��������������,
     ��������� ����� ����
      �� 6 ������ (6-5-3)
    */
    //CRectangle rect;
    //rect.CopyState(wall);

    /*
    ������� �������� �� ����� Ivanov Ivan 1980 ���� ��������.
    ��� ������ SmallTalk ������������ � ���� �������� � ������������� �����
      �� 6 ������ (6-5-3)
    */
    CPerson person("Ivanov Ivan", 1980);
    CCat cat("Bob");
    person.SmallTalk(cat);

    return 0;
}