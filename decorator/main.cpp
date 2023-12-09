// decorator.cpp : Домашнее задание к занятию «Структурные шаблоны: Proxy, Decorator, Adapter»
//
#include "decorator.h"
#include <iostream>

int main()
{
    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");
    std::cout << std::endl;

    auto text_block2 = new Paragraph(new Reversed(new Text()));
    text_block2->render("Hello world");
    std::cout << std::endl;

    auto link_block = new Link(new Text());
    link_block->render("netology.ru", "Hello world");
    std::cout << std::endl;

    return 0;
}

