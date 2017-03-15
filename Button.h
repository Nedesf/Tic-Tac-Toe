#include <SFML/Graphics.hpp>
#include "PublicFuncsAndEnums.h"
#include "TextBox.h"
#include <iostream>
#ifndef Button_h
#define Button_h
void exit(sf::RenderWindow&);
class Button
{
    ButtonType Type;
protected:
    sf::RectangleShape look;
    sf::Text text;
    bool pressed;
    bool clicked;
public:
    TextBox *textBoxPtr;
    Button();
    void Update(sf::RenderWindow&);
    void setSize(sf::Vector2f);
    void setPosition(sf::Vector2f, unsigned short, unsigned short);
    void setFont(sf::Font &Font);
    void setText(std::string);
    void setType(ButtonType);
    void resetClicked();
    sf::FloatRect getGlobalBounds();
    ButtonType getType();
    bool isPressed();
    bool isHovering(sf::RenderWindow&);
    bool isClicked();
    void whileHovering();
    void whileNotHovering();
    void Draw(sf::RenderWindow&);
};
#endif
