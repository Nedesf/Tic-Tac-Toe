#include "Tile.h"
class Level
{
    Tile tiles[3][3];
    sf::Text yoursScore;
    sf::Text enemysScore;
public:
    Level(unsigned short, unsigned short);
    void clear();
    void Update(PlayerColor, sf::RenderWindow&, PlayerColor&, bool&, sf::Vector2f&);
    bool isFull();
    void setTilesPositions(unsigned short, unsigned short);
    Tile& getTile(int, int);
    void Draw(sf::RenderWindow&);
};
