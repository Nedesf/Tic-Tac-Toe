#include "Level.h"
Level::Level(unsigned short width, unsigned short height)
{
    setTilesPositions(width, height);
}
void Level::clear()
{
    for(int y=0; y<3; y++)
    {
        for(int x=0; x<3; x++)
        {
            tiles[x][y].setState(EMPTY);
        }
    }
}
void Level::Update(PlayerColor col, sf::RenderWindow &Window, PlayerColor &turn, bool &madeMove, sf::Vector2f &lastMove)
{
    for (int y=0; y<3; y++)
    {
        for (int x=0; x<3; x++)
        {
            if(tiles[x][y].getState() == TileState::EMPTY)
                tiles[x][y].StateUpdate(col, madeMove, turn, sf::Vector2f(x,y), lastMove);
            tiles[x][y].Update(Window);
            tiles[x][y].ColorUpdate();
        }
    }
}
bool Level::isFull()
{
    for(int y=0; y<3; y++)
    {
        for(int x=0; x<3; x++)
        {
            if(tiles[x][y].getState() == TileState::EMPTY)
                return false;
        }
    }
    return true;
}
void Level::setTilesPositions(unsigned short width, unsigned short height)
{
    for (int y=0; y<3; y++)
    {
        for (int x=0; x<3; x++)
        {
            tiles[x][y].setPosition(sf::Vector2f(width/10+110*x, height/10+110*y), width, height);
        }
    }
}
Tile& Level::getTile(int x, int y)
{
    return tiles[x][y];
}
void Level::Draw(sf::RenderWindow &Window)
{
    for (int y=0; y<3; y++)
    {
        for (int x=0; x<3; x++)
        {
            tiles[x][y].Draw(Window);
        }
    }
}
