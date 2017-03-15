#include "Button.h"
#include "PublicFuncsAndEnums.h"
class Tile: public Button
{
    TileState state;
public:
    Tile();
    void ColorUpdate();
    void StateUpdate(PlayerColor, bool&, PlayerColor, sf::Vector2f, sf::Vector2f&);
    void setState(PlayerColor);
    void setState(TileState);
    TileState getState();
    void Draw(sf::RenderWindow&);
    bool operator !=(TileState);
    void operator =(TileState);
    bool operator ==(PlayerColor);
};
