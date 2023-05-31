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
    Нарисовать при помощи функции Draw домик с котиком рядом с ним:
        /\
       /  \
      / O  \
     --------
      |    |
      |    |
      ------
      до 8 баллов (8-6-4)
    */
    CCoutCanvas canvas;

    std::cout << "Home" << std::endl;
    // Дом
    CRectangle wall;
    CTriangle roof;
    CEllipse window;
    roof.Draw(canvas);
    window.Draw(canvas);
    wall.Draw(canvas);
    std::cout << "Cat" << std::endl;
    // Кот
    CEllipse body;
    CEllipse head;
    body.Draw(canvas);
    head.Draw(canvas);


    /* Создать прямоугольник.
     Скопировать в него при помощи CopyState состояние из прямоугольника,
     задающего стены дома
      до 6 баллов (6-5-3)
    */
    //CRectangle rect;
    //rect.CopyState(wall);

    /*
    Создать человека по имени Ivanov Ivan 1980 года рождения.
    При помощи SmallTalk побеседовать с этим человеом и вышесозданным котом
      до 6 баллов (6-5-3)
    */
    CPerson person("Ivanov Ivan", 1980);
    CCat cat("Bob");
    person.SmallTalk(cat);

    return 0;
}