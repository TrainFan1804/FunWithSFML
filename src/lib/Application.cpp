#include "Application.h"
#include "triangle_classic.h"
#include "square_party.h"

#include <iostream>

Application::Application()
{

}

int Application::run()
{
    std::cout << "What do you want to start?\n1. Triangle classic\n2. square party" << std::endl;
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
    default:
        std::cout << "Something went wrong!";
        return 1;
    }
    return 0;
}
