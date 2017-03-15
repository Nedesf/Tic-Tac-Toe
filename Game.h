#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "Level.h"
class Game
{
    const sf::Time TimeStep;
    sf::IpAddress friendIp;
    unsigned short port;
    bool host;
    PlayerColor color;
    PlayerColor enemy;
    PlayerColor turn;
    PlayerColor startingPlayer;
    Score score;
    sf::UdpSocket socket;
    unsigned short Width, Height;
    sf::RenderWindow Window;
    Level level;
    bool madeMove;
    sf::Vector2f lastMove;
public:
    Game(sf::IpAddress, unsigned short, bool, unsigned short=640, unsigned short=480);
    void Run();
    void Update();
    void HandleInputs();
    void Exchange();
    void ConfigureNextRound();
    bool isRoundOver();
    void Draw();
};
