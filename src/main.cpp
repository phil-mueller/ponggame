#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <Vec2.h>
#include <Ball.h>
#include <Paddle.h>
#include <PlayerScore.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>

// Declare some variables
const int windowWidth = 1280;
const int windowHeight = 720;
const float paddleSpeed = 1.0;
const float ballSpeed = 0.75;

// Enum to indicate movement for paddles
enum Buttons
{
  PaddleOneUp = 0,
  PaddleOneDown,
  PaddleTwoUp,
  PaddleTwoDown,
};

// Function to detect collision of ball with paddles
Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle)
{
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + ball.ballWidth;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + ball.ballHeight;
  float paddleLeft = paddle.position.x;
  float paddleRight = paddle.position.x + paddle.paddleWidth;
  float paddleTop = paddle.position.y;
  float paddleBottom = paddle.position.y + paddle.paddleHeight;

  Contact contact{};

  if (ballLeft >= paddleRight)
  {
    return contact;
  }
  if (ballRight <= paddleLeft)
  {
    return contact;
  }
  if (ballTop >= paddleBottom)
  {
    return contact;
  }
  if (ballBottom <= paddleTop)
  {
    return contact;
  }
  float paddleRangeUpper = paddleBottom - (2.0f*paddle.paddleHeight/3.0f);
  float paddleRangeMiddle = paddleBottom - (paddle.paddleHeight/3.0f);

  if (ball.velocity.x < 0)
  {
    contact.penetration = paddleRight - ballLeft;
  }
  else if (ball.velocity.x > 0)
  {
    contact.penetration = paddleLeft - ballRight;
  }

  if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper))
  {
    contact.type = CollisionType::Top;
  }
  else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle))
  {
    contact.type = CollisionType::Middle;
  }
  else
  {
    contact.type = CollisionType::Bottom;
  }
  return contact;  
}

// Function to detect collision of ball with walls
Contact CheckWallCollision(Ball const& ball)
{
  float ballLeft = ball.position.x;
	float ballRight = ball.position.x + ball.ballWidth;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + ball.ballHeight;

	Contact contact{};

	if (ballLeft < 0.0f)
	{
		contact.type = CollisionType::Left;
	}
	else if (ballRight > windowWidth)
	{
		contact.type = CollisionType::Right;
	}
	else if (ballTop < 0.0f)
	{
		contact.type = CollisionType::Top;
		contact.penetration = -ballTop;
	}
	else if (ballBottom > windowHeight)
	{
		contact.type = CollisionType::Bottom;
		contact.penetration = windowHeight - ballBottom;
	}
	return contact;
}

int main() {
  // Initialize SDL libraries
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  TTF_Init();
  SDL_Window* window = SDL_CreateWindow("Pong",0,0,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
  TTF_Font* scoreFont = TTF_OpenFont("DejaVuSansMono.ttf",40);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  // Open audio files for game
  Mix_Chunk* wallHitSound = Mix_LoadWAV("WallHit.wav");
  Mix_Chunk* paddleHitSound = Mix_LoadWAV("PaddleHit.wav");

  // Initialize player scores
  PlayerScore playerOneScore(Vec2(windowWidth/4,20),renderer,scoreFont);
  PlayerScore playerTwoScore(Vec2(3*windowWidth/4,20),renderer,scoreFont);
  int OneScore = 0;
  int TwoScore = 0;

  // Add ball object
  Ball ball(windowWidth,windowHeight,Vec2(ballSpeed,0.0));

  // Add paddle objects
  Paddle paddleOne(windowWidth,windowHeight,Vec2(0.0f,0.0f),"left");
  Paddle paddleTwo(windowWidth,windowHeight,Vec2(0.0f,0.0f),"right");

  // Game status variables
  bool running = true;
  bool buttons[4] = {};

  // Initialize time increment for game loop timing
  float dt = 0.0f;

  // Starting main game loop
  std::cout << "Starting Pong Game" << std::endl;
  while(running)
  {

    auto startTime = std::chrono::high_resolution_clock::now();

    // Listen for keyboard events
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      if(event.type==SDL_QUIT)
      {
        running = false;
      }
      else if(event.type==SDL_KEYDOWN)
      {
        if(event.key.keysym.sym==SDLK_ESCAPE)
        {
          running = false;
        }
        else if(event.key.keysym.sym==SDLK_w)
        {
          buttons[Buttons::PaddleOneUp] = true;
        }
        else if(event.key.keysym.sym==SDLK_s)
        {
          buttons[Buttons::PaddleOneDown] = true;
        }
        else if(event.key.keysym.sym==SDLK_UP)
        {
          buttons[Buttons::PaddleTwoUp] = true;
        }
        else if(event.key.keysym.sym==SDLK_DOWN)
        {
          buttons[Buttons::PaddleTwoDown] = true;
        }
      }
      else if(event.type==SDL_KEYUP)
      {
        if(event.key.keysym.sym==SDLK_w)
        {
          buttons[Buttons::PaddleOneUp] = false;
        }
        else if(event.key.keysym.sym==SDLK_s)
        {
          buttons[Buttons::PaddleOneDown] = false;
        }
        else if(event.key.keysym.sym==SDLK_UP)
        {
          buttons[Buttons::PaddleTwoUp] = false;
        }
        else if(event.key.keysym.sym==SDLK_DOWN)
        {
          buttons[Buttons::PaddleTwoDown] =false;
        }
      }
    }

    // Update paddles according to input
    if(buttons[Buttons::PaddleOneUp])
    {
      paddleOne.velocity.y = -paddleSpeed;
    }
    else if(buttons[Buttons::PaddleOneDown])
    {
      paddleOne.velocity.y = paddleSpeed;
    }
    else
    {
      paddleOne.velocity.y = 0.0;
    }
    if(buttons[Buttons::PaddleTwoUp])
    {
      paddleTwo.velocity.y = -paddleSpeed;
    }
    else if(buttons[Buttons::PaddleTwoDown])
    {
      paddleTwo.velocity.y = paddleSpeed;
    }
    else
    {
      paddleTwo.velocity.y = 0.0;
    }
    paddleOne.Update(dt);
    paddleTwo.Update(dt);  

    // Update ball
    ball.Update(dt);  

    // Check for collision
    if (Contact contact = CheckPaddleCollision(ball, paddleOne);
        contact.type != CollisionType::None)
    {
      ball.CollideWithPaddle(contact, ballSpeed);
      Mix_PlayChannel(-1, paddleHitSound, 0);
    }
    else if (contact = CheckPaddleCollision(ball, paddleTwo);
          contact.type != CollisionType::None)
    {
      ball.CollideWithPaddle(contact, ballSpeed);
      Mix_PlayChannel(-1, paddleHitSound, 0);
    }
    else if (contact = CheckWallCollision(ball);
          contact.type != CollisionType::None)
    {
      ball.CollideWithWall(contact, ballSpeed);
      if (contact.type == CollisionType::Left)
      {
        ++TwoScore;
        playerTwoScore.SetScore(renderer,scoreFont,TwoScore);
      }
      else if (contact.type == CollisionType::Right)
      {
        ++OneScore;
        playerOneScore.SetScore(renderer,scoreFont,OneScore);
      }
      else
      {
        Mix_PlayChannel(-1, wallHitSound, 0);
      }
      
    }
    // Create black window
    SDL_SetRenderDrawColor(renderer,0x0,0x0,0x0,0xFF);
    SDL_RenderClear(renderer);
    
    // Draw net
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    for(int y=0; y<windowHeight;++y)
    {
      if (y%20>3)
      {
        SDL_RenderDrawPoint(renderer,windowWidth/2,y);
      }
    }

    // Draw ball and paddles
    ball.Draw(renderer);
    paddleOne.Draw(renderer);
    paddleTwo.Draw(renderer);

    // Display the scores
    playerOneScore.Draw(renderer);
    playerTwoScore.Draw(renderer);

    // Present new window
    SDL_RenderPresent(renderer);

    // Calculate update time
    auto stopTime = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime-startTime).count();
  }

  // Cleanup
  Mix_FreeChunk(wallHitSound);
  Mix_FreeChunk(paddleHitSound);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(scoreFont);
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
  std::cout << "Game exited successfully" << std::endl;
  return 0;
}