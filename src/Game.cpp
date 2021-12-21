#include <Game.h>

// Constructor
Game::Game(int windowWidthInput, int windowHeightInput, std::string difficultyInput, std::string playerOneNameInput, std::string playerTwoNameInput)
{
  windowWidth = windowWidthInput;
  windowHeight = windowHeightInput;
  difficulty = difficultyInput;
  playerOneName = playerOneNameInput;
  playerTwoName = playerTwoNameInput;
  std::cout << "Game initialized" << std::endl;
}

// Function to detect collision of ball with paddles
Contact Game::CheckPaddleCollision(Ball const& ball, Paddle const& paddle)
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
Contact Game::CheckWallCollision(Ball const& ball)
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

GameResult Game::Run()
{
  std::cout << "Starting the game: " << playerOneName << " vs. " << playerTwoName << std::endl;
  // Initialize SDL libraries
  SDL_Init(SDL_INIT_VIDEO); // | SDL_INIT_AUDIO);
  TTF_Init();
  SDL_Window* window = SDL_CreateWindow("Pong",0,0,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
  TTF_Font* scoreFont = TTF_OpenFont("DejaVuSansMono.ttf",40);
  // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  // Open audio files for game
  // Mix_Chunk* wallHitSound = Mix_LoadWAV("WallHit.wav");
  // Mix_Chunk* paddleHitSound = Mix_LoadWAV("PaddleHit.wav");

  // Initialize player scores
  PlayerScore playerOneScore(Vec2(windowWidth/4,20),renderer,scoreFont);
  PlayerScore playerTwoScore(Vec2(3*windowWidth/4,20),renderer,scoreFont);
  int OneScore = 0;
  int TwoScore = 0;

  // Initialize player names
  PlayerName nameOne(Vec2(windowWidth/4.5,windowHeight-50),renderer,scoreFont,playerOneName);
  PlayerName nameTwo(Vec2(2.75*windowWidth/4,windowHeight-50),renderer,scoreFont,playerTwoName);

  // Game status variables
  bool running = true;
  bool buttons[4] = {};
  bool enemy = false;
  if (playerTwoName == "Computer")
  {
    enemy = true;
  }
  bool sleep = false;

  // Difficulty and speed adjustments
  float paddleOneSpeed = 0;
  float paddleTwoSpeed = 0;
  float ballSpeed = 0;
  float ballAcceleration = 0;
  if (difficulty == "easy")
  {
    paddleOneSpeed = 1.0;
    paddleTwoSpeed = 1.0;
    ballSpeed = 0.75;
    ballAcceleration = 1.02;
    if (enemy == true)
    {
      paddleTwoSpeed = 0.6;
    }
  }
  else if (difficulty == "medium" || difficulty == "hard")
  {
    paddleOneSpeed = 1.2;
    paddleTwoSpeed = 1.2;
    ballSpeed = 0.8;
    ballAcceleration = 1.05;
    if (enemy == true)
    {
      paddleTwoSpeed = 1.1;
    }
  }

  // Add ball object
  Ball ball(windowWidth,windowHeight,Vec2(ballSpeed,0.0));

  // Add paddle objects
  Paddle paddleOne(windowWidth,windowHeight,Vec2(0.0f,0.0f),"left");
  Paddle paddleTwo(windowWidth,windowHeight,Vec2(0.0f,0.0f),"right");

  // Initialize time variables for game loop timing
  float targetDuration = 1000/60;
  float dt = 0.0f;
  int frameCount = 0;
  auto titleTime = std::chrono::high_resolution_clock::now();

  // Starting main game loop
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
        else if(enemy==false && event.key.keysym.sym==SDLK_UP)
        {
          buttons[Buttons::PaddleTwoUp] = true;
        }
        else if(enemy==false && event.key.keysym.sym==SDLK_DOWN)
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
        else if(enemy==false && event.key.keysym.sym==SDLK_UP)
        {
          buttons[Buttons::PaddleTwoUp] = false;
        }
        else if(enemy==false && event.key.keysym.sym==SDLK_DOWN)
        {
          buttons[Buttons::PaddleTwoDown] =false;
        }
      }
    }

    // Enemy computer movement
    if (enemy == true)
    {
      buttons[Buttons::PaddleTwoDown] = false;
      buttons[Buttons::PaddleTwoUp] = false;
      if (ball.velocity.x > 0 && (ball.position.x > 0.5*windowWidth))
      {
        if ((ball.position.y+ball.ballHeight/2.0) > (paddleTwo.position.y+paddleTwo.paddleHeight/2.0))
        {
          if ((ball.position.y+ball.ballHeight/2.0)-(paddleTwo.position.y+paddleTwo.paddleHeight/2.0)>10)
          {
            buttons[Buttons::PaddleTwoDown] = true;
          }
        }
        else if ((ball.position.y+ball.ballHeight/2.0) < (paddleTwo.position.y + paddleTwo.paddleHeight/2.0))
        {
          if ((paddleTwo.position.y + paddleTwo.paddleHeight/2.0)-(ball.position.y+ball.ballHeight/2.0)>10)
          {
            buttons[Buttons::PaddleTwoUp] = true;
          } 
        }
      }
    }

    // Update paddles according to input
    if(buttons[Buttons::PaddleOneUp])
    {
      paddleOne.velocity.y = -paddleOneSpeed;
    }
    else if(buttons[Buttons::PaddleOneDown])
    {
      paddleOne.velocity.y = paddleOneSpeed;
    }
    else
    {
      paddleOne.velocity.y = 0.0;
    }
    if(buttons[Buttons::PaddleTwoUp])
    {
      paddleTwo.velocity.y = -paddleTwoSpeed;
    }
    else if(buttons[Buttons::PaddleTwoDown])
    {
      paddleTwo.velocity.y = paddleTwoSpeed;
    }
    else
    {
      paddleTwo.velocity.y = 0.0;
    }
    paddleOne.Update(dt);
    paddleTwo.Update(dt);  

    // Update ball
    ball.Update(dt); 

    // Check for sleep after point has been made
    if (sleep == true)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
      sleep = false;
    } 

    // Check for collision
    if (Contact contact = CheckPaddleCollision(ball, paddleOne);
        contact.type != CollisionType::None)
    {
      ball.CollideWithPaddle(contact, ballAcceleration);
      // Mix_PlayChannel(-1, paddleHitSound, 0);
    }
    else if (contact = CheckPaddleCollision(ball, paddleTwo);
          contact.type != CollisionType::None)
    {
      ball.CollideWithPaddle(contact, ballAcceleration);
      // Mix_PlayChannel(-1, paddleHitSound, 0);
    }
    else if (contact = CheckWallCollision(ball);
          contact.type != CollisionType::None)
    {
      ball.CollideWithWall(contact, ballSpeed, difficulty);
      if (contact.type == CollisionType::Left)
      {
        ++TwoScore;
        playerTwoScore.SetScore(renderer,scoreFont,TwoScore);
        paddleOne.position.y = (windowHeight/2.0)-(paddleOne.paddleHeight/2.0);
        paddleTwo.position.y = (windowHeight/2.0)-(paddleTwo.paddleHeight/2.0);
        sleep = true;
      }
      else if (contact.type == CollisionType::Right)
      {
        ++OneScore;
        playerOneScore.SetScore(renderer,scoreFont,OneScore);
        paddleOne.position.y = (windowHeight/2.0)-(paddleOne.paddleHeight/2.0);
        paddleTwo.position.y = (windowHeight/2.0)-(paddleTwo.paddleHeight/2.0);
        sleep = true;
      }
      else
      {
        // Mix_PlayChannel(-1, wallHitSound, 0);
      }
    }

    if (OneScore >= 10 || TwoScore >= 10)
    {
      if ((OneScore-TwoScore)*(OneScore-TwoScore) >= 4)
      {
        running = false;
        if (OneScore > TwoScore)
        {
          std::cout << playerOneName << " has won the game" << std::endl;
        }
        else
        {
          std::cout << playerTwoName << " has won the game" << std::endl;
        }
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
    SDL_SetRenderDrawColor(renderer,225,225,0,255);
    ball.Draw(renderer);
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    paddleOne.Draw(renderer);
    paddleTwo.Draw(renderer);

    // Display the scores
    playerOneScore.Draw(renderer);
    playerTwoScore.Draw(renderer);

    // Display the names
    nameOne.Draw(renderer);
    nameTwo.Draw(renderer);

    // Present new window
    SDL_RenderPresent(renderer);

    // Calculate update time and delay execution
    auto stopTime = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime-startTime).count();
    if (dt < targetDuration)
    {
      SDL_Delay(targetDuration - dt);
    }
    frameCount++;
    if (std::chrono::duration<float,std::chrono::milliseconds::period>(stopTime-titleTime).count() >= 1000)
    {
      std::stringstream ss;
      ss << "Pong Game running at " << frameCount << " FPS";
      SDL_SetWindowTitle(window,ss.str().c_str());
      titleTime = stopTime;
      frameCount = 0;
    }
  }
  // Cleanup
  // Mix_FreeChunk(wallHitSound);
  // Mix_FreeChunk(paddleHitSound);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(scoreFont);
  // Mix_Quit();
  TTF_Quit();
  SDL_Quit();

  // Create return object with time-stamp
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  int year = static_cast<int>(1900+parts->tm_year);
  int month = static_cast<int>(1+parts->tm_mon);
  int day = static_cast<int>(parts->tm_mday);  

  GameResult game = GameResult(OneScore,TwoScore,playerOneName,playerTwoName,day,month,year);
  return game;
}