#ifndef PublicFuncsAndEnums_h
#define PublicFuncsAndEnums_h
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
struct Score
{
    int yourScore;
    int enemysScore;
};
PlayerColor convertToPlayerColor(TileState state)
{
    if(state == TileState::REDT)
        return PlayerColor::RED;
    if(state == TileState::BLUET)
        return PlayerColor::BLUE;
    else
        return PlayerColor::PNULL;
}
TileState convertToTileState(PlayerColor col)
{
    if(col == PlayerColor::RED)
        return TileState::REDT;
    if(col == PlayerColor::BLUE)
        return TileState::BLUET;
    else
        return TileState::EMPTY;
}
#endif
