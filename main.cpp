#include "Menu.h"
int main()
{
    std::cout<<sf::IpAddress::getLocalAddress();
    sf::IpAddress friendIp;
    unsigned short port=52000;
    PlayerNumber player = PlayerNumber::Player1;
    Menu *menu = new Menu;
    menu->Run();
    friendIp = menu->getIpAddress();
    port = menu->getPort();
    delete menu;
    Game game(friendIp, port);
    game.Run();
    return 0;
}
