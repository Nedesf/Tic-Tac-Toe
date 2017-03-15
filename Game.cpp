#include "Game.h"

Game::Game(sf::IpAddress _ip, unsigned short _port, bool _host, unsigned short w, unsigned short h):
    TimeStep(sf::seconds(1.f/60)),
    Width(w),
    Height(h),
    level(Width, Height)
{
    Width = w;
    Height = h;
    friendIp = _ip;
    port = _port;
    host = _host;
    socket.bind(port);
    Window.create(sf::VideoMode(Width,Height),"Tic Tac Toe");
    if(host)
    {
        color = PlayerColor::RED;
        enemy = PlayerColor::BLUE;
        Window.setTitle("HOST");
    }
    else
    {
        color = PlayerColor::BLUE;
        enemy = PlayerColor::RED;
    }
    startingPlayer = PlayerColor::PNULL;
    turn = PlayerColor::RED;
    ConfigureNextRound();
    startingPlayer = PlayerColor::RED;
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
            socket.close();
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
        std::cout<<"Sending";
        socket.send(packet, friendIp, port);
        std::cout<<"        Sent"<<std::endl;
        madeMove = false;
        turn = enemy;
    }
    else if(turn == enemy)
    {
        float temp1, temp2;
        socket.setBlocking(false);
        if(socket.receive(packet, friendIp, port) == sf::Socket::Done)
        {
            std::cout<<"RECEIVED :P";
            packet >> temp1 >> temp2;
            std::cout<<"TEST: "<<temp1<<", "<<temp2<<std::endl;
            level.getTile(temp1, temp2).setState(enemy);
            if(enemy == PlayerColor::BLUE)
                std::cout<<"Kolor niebieski ;p"<<std::endl;
            turn = color;
        }
    }
}
void Game::ConfigureNextRound()
{
    level.clear();
    lastMove = sf::Vector2f(-1,-1);
    madeMove = false;
    if(startingPlayer == PlayerColor::RED)
    {
        startingPlayer = PlayerColor::BLUE;
        turn = PlayerColor::BLUE;
    }
    else
    {
        startingPlayer = PlayerColor::RED;
        turn = PlayerColor::RED;
    }
}
bool Game::isRoundOver()
{
    for(int i=0; i<3; i++)
    {
        if(level.getTile(0, i).getState() == level.getTile(1, i).getState() == level.getTile(2, i).getState())
        {
            if(level.getTile(0,1) == color)
                score.yourScore++;
            else
                score.enemysScore++;
            return true;
        }
        else if(level.getTile(i, 0).getState() == level.getTile(i, 1).getState() == level.getTile(i, 2).getState())
        {
            if(level.getTile(i, 0) == color)
                score.yourScore++;
            else
                score.enemysScore++;
            return true;
        }

    }
    return false;
}
void Game::Draw()
{
    Window.clear();
    level.Draw(Window);
    Window.display();
}
