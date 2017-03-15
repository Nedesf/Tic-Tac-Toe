#include <SFML/Network.hpp>
#include "Game.h"
#include "Button.h"
#include "PublicFuncsAndEnums.h"
#include "TextBox.h"
#include <vector>
class Menu
{
    std::vector <Button> buttons;
    std::vector <sf::Text> texts;
    std::vector <TextBox> textBoxes;
    sf::Font font;
    sf::Text textTemplate;
    enum MenuState{MAIN, IP};
    MenuState state;
    sf::IpAddress friendIp;
    unsigned short port;
    bool host;
    unsigned short Width, Height;
    sf::RenderWindow Window;
public:
    Menu(unsigned short=640, unsigned short=480);
    void Run();
    void Update();
    void HandleInputs();
    void LoadMainMenu();
    void LoadIpMenu();
    void NextState();
    void PreviousState();
    sf::IpAddress getIpAddress();
    unsigned short getPort();
    bool isHost();
    void Draw();
};
