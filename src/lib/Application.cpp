#include "Application.h"
#include "moving.h"
#include "triangle_classic.h"
#include "square_party.h"
#include "pong/pong.h"

#include <iostream>

Application::Application()
{

}

int Application::run()
{
    std::cout << "What do you want to start?\n1. Triangle classic\n2. square party\n3. moving\n4. pong" << std::endl;
    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        triangleClassic();
        break;
    case 2:
        squareParty();
        break;
    case 3:
        moving();
        break;
    case 4:
        pong();
        break;
    default:
        std::cout << "Something went wrong!";
        return 1;
    }
    return 0;
}
