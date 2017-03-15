#include <SFML/Graphics.hpp>
#ifndef TextBox_h
#define TextBox_h
#include <stack>
class TextBox
{
    sf::RectangleShape look;
    sf::Text text;
    sf::Text drawableText;
    bool clicked;
    std::stack <char> hiddenChars;
    std::string defaultTxt;
public:
    TextBox();
    void Update(sf::RenderWindow&);
    void EnterText(sf::RenderWindow&, std::string="");
    void isClicked(sf::RenderWindow&);
    void setSize(sf::Vector2f);
    void setPosition(sf::Vector2f);
    void setFont(sf::Font&);
    void setText(sf::RenderWindow&, std::string);
    void setDefault(std::string);
    void setToDefault(sf::RenderWindow&);
    sf::Vector2f getSize();
    std::string getString();
    void Draw(sf::RenderWindow&);
};
#endif
