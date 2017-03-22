#ifndef PUBLICFUNCSANDENUMS_H
#define PUBLICFUNCSANDENUMS_H
enum ButtonType
{
    EXIT,
    START,
    BACK,
    SETDEFAULT,
    ROLE
};

enum TileState
{
    REDT,
    BLUET,
    EMPTY
};
enum PlayerColor
{
    RED,
    BLUE,
    PNULL
};
enum PlayerNumber
{
    Player1,
    Player2
};
struct Score
{
    int yourScore;
    int enemysScore;
};
inline PlayerColor convertToPlayerColor(TileState state)
{
    if(state == TileState::REDT)
        return PlayerColor::RED;
    if(state == TileState::BLUET)
        return PlayerColor::BLUE;
    else
        return PlayerColor::PNULL;
}
inline TileState convertToTileState(PlayerColor col)
{
    if(col == PlayerColor::RED)
        return TileState::REDT;
    if(col == PlayerColor::BLUE)
        return TileState::BLUET;
    else
        return TileState::EMPTY;
}
#endif
