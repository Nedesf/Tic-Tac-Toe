#include "Menu.h"
#include <iostream>
#include <cstdlib>
Menu::Menu(unsigned short w, unsigned short h)
{
    Width = w;
    Height = h;
    font.loadFromFile("EncodeCondensedRegular.ttf");
    textTemplate.setFont(font);
    state = MAIN;
    port=42042;
    host=true;
    LoadMainMenu();
    Window.create(sf::VideoMode(w, h), "Tic Tac Toe");
}

void Menu::Run()
{
    ///ograniczanie szybkosci dzialania menu nie ma sensu
    while (Window.isOpen())
    {
        Update();
        HandleInputs();
        Draw();
    }
}
void Menu::Update()
{
    if (!buttons.empty())
    {
        for (unsigned int i=0; i<buttons.size(); i++)
        {
            buttons[i].Update(Window);
            if (buttons[i].isClicked())
            {
                switch (buttons[i].getType())
                {
                case EXIT:
                    Window.close();
                    break;
                case START:
                    NextState();
                    LoadIpMenu();
                    break;
                case BACK:
                    PreviousState();
                    break;
                case SETDEFAULT:
                    buttons[i].textBoxPtr->setToDefault(Window);
                    break;
                case ROLE:
                    if (host)
                    {
                        host=false;
                        buttons[i].setText("Client");
                    }
                    else
                    {
                        host=true;
                        buttons[i].setText("Host");
                    }
                    break;
                }
                buttons[i].resetClicked();
            }
        }
    }
    if (!textBoxes.empty())
    {
        for (unsigned int i=0; i<textBoxes.size(); i++)
        {
            textBoxes[i].Update(Window);
        }
    }
}
void Menu::HandleInputs()
{
    sf::Event event;
    while (Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Window.close();
        }
    }
}
void Menu::LoadMainMenu()
{
    texts.clear();
    buttons.clear();
    textBoxes.clear();
    texts.push_back(textTemplate);
    texts[0].setString("Tic Tac Toe");
    texts[0].setPosition(Width/2-texts[0].getGlobalBounds().width/2, Height/8-texts[0].getGlobalBounds().height/2);

    buttons.push_back(Button());
    buttons[0].setText("Play");
    buttons[0].setFont(font);
    buttons[0].setPosition(sf::Vector2f(Width/2-buttons[0].getGlobalBounds().width/2, Height/3.5-buttons[0].getGlobalBounds().height/2), Width, Height);
    buttons[0].setType(ButtonType::START);
}
void Menu::LoadIpMenu()
{
    texts.clear();
    buttons.clear();
    textBoxes.clear();
    texts.push_back(textTemplate);
    texts[0].setString("Enter your friend's IP Adress");
    texts[0].setPosition(Width/2-texts[0].getGlobalBounds().width/2, Height/8-texts[0].getGlobalBounds().height/2);
    texts.push_back(textTemplate);
    texts[1].setString("Enter port");
    texts[1].setPosition(Width/2-texts[1].getGlobalBounds().width/2, Height/1.5-texts[1].getGlobalBounds().height/2);
    texts.push_back(textTemplate);
    texts[2].setString("Change it only when you know what you are doing.");
    texts[2].setColor(sf::Color::Red);
    texts[2].setCharacterSize(12);
    texts[2].setPosition(sf::Vector2f(Width/2-texts[2].getGlobalBounds().width/2, Height/1.25));

    textBoxes.push_back(TextBox());
    textBoxes[0].setFont(font);
    textBoxes[0].setPosition(sf::Vector2f(Width/2-textBoxes[0].getSize().x/2, Height/6));
    textBoxes.push_back(TextBox());
    textBoxes[1].setFont(font);
    textBoxes[1].setPosition(sf::Vector2f(Width/2-textBoxes[1].getSize().x/2, Height/1.4));
    textBoxes[1].setText(Window, "52000");
    textBoxes[1].setDefault("52000");

    buttons.push_back(Button());
    buttons[0].setText("Default");
    buttons[0].setFont(font);
    buttons[0].setPosition(sf::Vector2f(Width/1.5-buttons[0].getGlobalBounds().width/2, Height/1.4), Width, Height);
    buttons[0].setType(ButtonType::SETDEFAULT);
    buttons[0].textBoxPtr = &textBoxes[1];
    buttons.push_back(Button());
    buttons[1].setText("Host");
    buttons[1].setFont(font);
    buttons[1].setPosition(sf::Vector2f(Width/2-buttons[1].getGlobalBounds().width/2, Height/2-buttons[1].getGlobalBounds().height/2), Width, Height);
    buttons[1].setType(ButtonType::ROLE);
    buttons.push_back(Button());
    buttons[2].setText("Play!");
    buttons[2].setFont(font);
    buttons[2].setPosition(sf::Vector2f(Width/1.25-buttons[2].getGlobalBounds().width/2, Height/2-buttons[1].getGlobalBounds().height/2), Width, Height);
    buttons[2].setType(ButtonType::START);
}
void Menu::NextState()
{
    switch(state)
    {
    case MenuState::MAIN:
        state = MenuState::IP;
        break;
    case MenuState::IP:
        friendIp = textBoxes[0].getString();
        port = atoi(textBoxes[1].getString().c_str());
        Window.close();
        break;
    }
}
void Menu::PreviousState()
{
    switch(state)
    {
    case MenuState::IP:
        state = MAIN;
        break;
    }
}
sf::IpAddress Menu::getIpAddress()
{
    return friendIp;
}
unsigned short Menu::getPort()
{
    return port;
}
bool Menu::isHost()
{
    return host;
}
void Menu::Draw()
{
    Window.clear();
    for (unsigned int i=0; i<texts.size(); i++)
    {
        Window.draw(texts[i]);
    }
    for (unsigned int i=0; i<buttons.size(); i++)
    {
        buttons[i].Draw(Window);
    }
    for (unsigned int i=0; i<textBoxes.size(); i++)
    {
        textBoxes[i].Draw(Window);
    }
    Window.display();
}
