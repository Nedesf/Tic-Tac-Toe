#include "Button.h"
#include <math.h>
Button::Button()
{
    textBoxPtr = NULL;
    Type = ButtonType::EXIT;
    look.setSize(sf::Vector2f(70,30));
    look.setFillColor(sf::Color::White);
    look.setOutlineColor(sf::Color::Blue);
    look.setOutlineThickness(3);
    text.setFillColor(sf::Color::Blue);
    text.setCharacterSize(sqrt(look.getSize().x*2+look.getSize().y*2)*1.3);
    text.setString("error");
    pressed=false;
    clicked=false;
}
void Button::Update(sf::RenderWindow &Window)
{
    //std::cout<<"Text("<<text.getPosition().x<<", "<<text.getPosition().y<<std::endl;
    if (isHovering(Window))
    {
        whileHovering();

    if (isPressed())
        pressed=true;
    else if (pressed)
    {
        clicked=true;
        pressed=false;
    }

    return;
    }
    pressed=false;
    whileNotHovering();
}
void Button::setSize(sf::Vector2f size)
{
    look.setSize(size);
    text.setCharacterSize(sqrt(look.getSize().x*2+look.getSize().y*2)/2);
}
void Button::setPosition(sf::Vector2f pos, unsigned short Width, unsigned short Height)
{
    look.setPosition(pos);
    text.setPosition(sf::Vector2f(look.getPosition().x+look.getGlobalBounds().width/2-text.getGlobalBounds().width/2-look.getOutlineThickness(), look.getPosition().y+look.getGlobalBounds().height/2-text.getGlobalBounds().height));
}
void Button::setFont (sf::Font &Font)
{
    text.setFont(Font);
}
void Button::setText (std::string string)
{
    text.setString(string);
}
void Button::setType(ButtonType type)
{
    Type = type;
}
void Button::resetClicked()
{
    clicked = false;
}
sf::FloatRect Button::getGlobalBounds()
{
    return look.getGlobalBounds();
}
ButtonType Button::getType()
{
    return Type;
}
bool Button::isHovering(sf::RenderWindow& Window)
{
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(Window).x,sf::Mouse::getPosition(Window).y);
    if (look.getGlobalBounds().contains(mouse))
        return true;

    return false;
}
bool Button::isPressed()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return 1;
    return 0;

}
bool Button::isClicked()
{
    return clicked;
}
void Button::whileHovering()
{
    look.setOutlineColor(sf::Color::Red);
}
void Button::whileNotHovering()
{
    look.setOutlineColor(sf::Color::Blue);
}
void Button::Draw(sf::RenderWindow &Window)
{
    Window.draw(look);
    Window.draw(text);
}
