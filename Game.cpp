#include "Game.h"
#include <iostream>
Game::Game(sf::IpAddress _ip, unsigned short _port, unsigned short w, unsigned short h):
    TimeStep(sf::seconds(1.f/60)),
    Width(w),
    Height(h),
    level(Width, Height)
{
    Width = w;
    Height = h;
    friendIp = _ip;
    port = _port;
    socket.bind(port);
    srand(time(NULL));
    short temp = rand()%2;
    if(temp == 0)
        player = PlayerNumber::Player1;
    else
        player = PlayerNumber::Player2;
    Window.create(sf::VideoMode(Width, Height), "Tic Tac Toe");
    color = PlayerColor::PNULL;
    ConfigureNextRound();
    if(player == PlayerNumber::Player1)
    {
        color = PlayerColor::RED;
        enemy = PlayerColor::BLUE;
    }
    else
    {
        color = PlayerColor::BLUE;
        enemy = PlayerColor::RED;
    }
}

void Game::Run()
{
    sf::Clock delta;
    sf::Time deltaTime = sf::seconds(0);
    while (Window.isOpen())
    {
        deltaTime+=delta.restart();
        while (deltaTime>TimeStep)
        {
            deltaTime-=TimeStep;
            Update();
        }
        HandleInputs();
        Draw();
    }
}
void Game::Update()
{
    level.Update(color, Window, turn, madeMove, lastMove);
    Exchange();
    if(isRoundOver())
        ConfigureNextRound();
}
void Game::HandleInputs()
{
    sf::Event event;
    while (Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Window.close();
            socket.unbind();
        }
    }
}
void Game::Exchange()
{
    sf::Packet packet;
    if(madeMove)
    {
        socket.setBlocking(true);
        packet << lastMove.x << lastMove.y;
        socket.send(packet, friendIp, port);
        madeMove = false;
        turn = enemy;
    }
    else if(turn == enemy)
    {
        float temp1, temp2;
        socket.setBlocking(false);
        if(socket.receive(packet, friendIp, port) == sf::Socket::Done)
        {
            packet >> temp1 >> temp2;
            level.getTile(temp1, temp2).setState(enemy);
            turn = color;
        }
    }
}
void Game::ConfigureNextRound()
{
    level.clear();
    lastMove = sf::Vector2f(-1,-1);
    madeMove = false;
    if(color == PlayerColor::RED)
    {
        color = PlayerColor::BLUE;
        enemy = PlayerColor::RED;
    }
    else if(color == PlayerColor::BLUE)
    {
        color = PlayerColor::RED;
        enemy = PlayerColor::BLUE;
    }
    turn = PlayerColor::RED;
}
bool Game::isRoundOver()
{
    if(level.isFull())
        return true;
    for(int i=0; i<3; i++)
    {
        if((level.getTile(0, i).getState() != TileState::EMPTY) && (level.getTile(0, i).getState() == level.getTile(1, i).getState()) && (level.getTile(1, i).getState() == level.getTile(2, i).getState()))
        {
            //std::cout<<"OS X";
            if(level.getTile(0,1) == color)
                score.yourScore++;
            else
                score.enemysScore++;
            return true;
        }
        else if((level.getTile(i, 0).getState() != TileState::EMPTY) && (level.getTile(i, 0).getState() == level.getTile(i, 1).getState()) && (level.getTile(i, 1).getState() == level.getTile(i, 2).getState()))
        {
            std::cout<<"OS Y";
            if(level.getTile(i, 0) == color)
                score.yourScore++;
            else
                score.enemysScore++;
            return true;
        }

    }
    if(level.getTile(1, 1).getState() != TileState::EMPTY)
    {
        if(!((level.getTile(0, 0).getState() == level.getTile(1, 1).getState()) && (level.getTile(1, 1).getState() == level.getTile(2, 2).getState())))
            if(!((level.getTile(2, 0).getState() == level.getTile(1, 1).getState()) && (level.getTile(1, 1).getState() == level.getTile(0, 2).getState())))
                return false;
        if(level.getTile(1, 1) == color)
            score.yourScore++;
        else
            score.enemysScore++;
        return true;
    }
    return false;
}
void Game::Draw()
{
    Window.clear();
    level.Draw(Window);
    Window.display();
}
