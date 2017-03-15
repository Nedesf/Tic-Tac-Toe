#include "TextBox.h"
#include <iostream>
TextBox::TextBox()
{
    look.setSize(sf::Vector2f(150,30));
    look.setFillColor(sf::Color::White);
    look.setOutlineColor(sf::Color::Blue);
    look.setOutlineThickness(3);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(sqrt(look.getSize().x*2+look.getSize().y*2)*1.3);
    text.setColor(sf::Color::Red);
    text.setString("");
    drawableText = text;
    clicked=false;
    defaultTxt = "error";
}
void TextBox::Update(sf::RenderWindow &Window)
{
    isClicked(Window);
    if(clicked)
        EnterText(Window);
}
void TextBox::EnterText(sf::RenderWindow &Window, std::string manual)
{
    std::string textStr = text.getString();
    std::string drawableTextStr = drawableText.getString();
    sf::Event event;
    while(Window.pollEvent(event) || !(manual.empty()))
    {
        if(event.type == sf::Event::TextEntered || !(manual.empty()))
        {
            if (event.text.unicode != '\b')
            {
                if (manual.empty())
                {
                    textStr+=(char)event.text.unicode;
                    drawableTextStr += (char)event.text.unicode;
                }
                else
                {
                    textStr+=manual;
                    drawableTextStr+=manual;
                }
                text.setString(textStr);
                drawableText.setString(drawableTextStr);
                while (!(look.getPosition().x + look.getSize().x > drawableText.getGlobalBounds().left + drawableText.getGlobalBounds().width))
                {
                    hiddenChars.push(drawableTextStr.front());
                    drawableTextStr.erase(drawableTextStr.begin());
                    drawableText.setString(drawableTextStr);
                }
                manual.clear();
            }
            if ((event.text.unicode == '\b' && !(drawableText.getString().isEmpty() )) || !(manual.empty()))
            {
                std::cout<<"do";
                text.setString(textStr.erase(textStr.length()-1));
                drawableText.setString(drawableTextStr.erase(drawableTextStr.length()-1));
                while (look.getPosition().x + look.getSize().x > drawableText.getGlobalBounds().left + drawableText.getGlobalBounds().width && !(hiddenChars.empty()))
                {
                    drawableTextStr = hiddenChars.top() + drawableTextStr;
                    drawableText.setString(drawableTextStr);
                    if (look.getPosition().x + look.getSize().x < drawableText.getGlobalBounds().left + drawableText.getGlobalBounds().width)
                    {
                        drawableTextStr.erase(drawableTextStr.begin());
                        drawableText.setString(drawableTextStr);
                        break;
                    }

                        hiddenChars.pop();

                }
            }
        }
    }
}
void TextBox::isClicked(sf::RenderWindow &Window)
{
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y);
    if(look.getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        clicked = true;
    else if (clicked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        clicked = false;


}
void TextBox::setSize(sf::Vector2f boxSize)
{
    look.setSize(boxSize);
    text.setCharacterSize(sqrt(look.getSize().x*2+look.getSize().y*2)*1.3);
    drawableText.setCharacterSize(sqrt(look.getSize().x*2+look.getSize().y*2)*1.3);
}
void TextBox::setPosition(sf::Vector2f boxPos)
{
    look.setPosition(boxPos);
    text.setPosition(sf::Vector2f(look.getPosition().x, look.getPosition().y));
    drawableText.setPosition(sf::Vector2f(look.getPosition().x, look.getPosition().y));
}
void TextBox::setFont(sf::Font &Font)
{
    text.setFont(Font);
    drawableText.setFont(Font);
}
void TextBox::setText(sf::RenderWindow &Window, std::string txt)
{
    text.setString("");
    drawableText.setString("");
    EnterText(Window, txt);
}
void TextBox::setDefault(std::string txt)
{
    defaultTxt = txt;
}
void TextBox::setToDefault(sf::RenderWindow &Window)
{
    setText(Window, defaultTxt);
}
sf::Vector2f TextBox::getSize()
{
    return look.getSize();
}
std::string TextBox::getString()
{
    return text.getString();
}
void TextBox::Draw(sf::RenderWindow &Window)
{
    Window.draw(look);
    Window.draw(drawableText);
}
