#include "Menu.h"
int main()
{
    std::cout<<sf::IpAddress::getLocalAddress();
    sf::IpAddress friendIp;
    unsigned short port=52000;
    bool host=true;
    Menu *menu = new Menu;
    menu->Run();
    friendIp = menu->getIpAddress();
    port = menu->getPort();
    host = menu->isHost();
    delete menu;
    Game game(friendIp, port, host);
    game.Run();
    return 0;
}
