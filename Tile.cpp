#include "Tile.h"

Tile::Tile():
    Button()
{
    look.setSize(sf::Vector2f(100,100));
}
void Tile::ColorUpdate()
{
    switch(state)
    {
    case EMPTY:
        look.setFillColor(sf::Color::White);
        break;
    case REDT:
        look.setFillColor(sf::Color::Red);
        break;
    case BLUET:
        look.setFillColor(sf::Color::Blue);
        break;
    }
}
void Tile::StateUpdate(PlayerColor col, bool &madeMove, PlayerColor turn, sf::Vector2f position, sf::Vector2f &lastMove)
{
    if (turn == col)
    {
        if(clicked)
        {
            state = convertToTileState(col);
            madeMove = true;
            lastMove = position;
        }
    }
    resetClicked();
}
void Tile::setState(PlayerColor col)
{
    state = convertToTileState(col);
    ColorUpdate();
}
void Tile::setState(TileState st)
{
    state = st;
}
TileState Tile::getState()
{
    return state;
}
void Tile::Draw(sf::RenderWindow &Window)
{
    Window.draw(look);
}
bool Tile::operator!=(TileState secondTile)
{
    if(state!=secondTile)
        return true;
    else
        return false;
}
void Tile::operator=(TileState secondTile)
{
    state = secondTile;
}
bool Tile::operator==(PlayerColor col)
{
    TileState secondState = convertToTileState(col); ///czytelniej tak zrobic niz np. if(convertToTileState(col) == state); :p
    if(secondState == state)
        return true;
    return false;
}
