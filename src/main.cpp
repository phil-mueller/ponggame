#include <Game.h>
#include <vector>
#include <algorithm>
#include <fstream>

// Declare variables
const int windowWidth = 1600;
const int windowHeight = 900;

// Main function
int main() {

  // Load last games from file
  bool lastGamesFound = false;
  std::vector<GameResult> results;
  std::string line;
  std::string n1,n2;
  int p1,p2,d,m,y;
  try
  {
    std::string line;
    std::ifstream f("lastgames.txt");
    while (std::getline(f, line))
    {
      // Split line into parts
      std::stringstream ss(line);
      std::string segment;
      std::vector<std::string> seglist;
      while(std::getline(ss, segment, ';'))
      {
        seglist.push_back(segment);
      }
      n1 = seglist[0];
      n2 = seglist[1];
      p1 = std::stoi(seglist[2]);
      p2 = std::stoi(seglist[3]);
      d = std::stoi(seglist[4]);
      m = std::stoi(seglist[5]);
      y = std::stoi(seglist[6]);
      GameResult result = GameResult(p1,p2,n1,n2,d,m,y);
      results.push_back(result);
    }
    f.close();
    lastGamesFound = true;
  }
  catch(const std::exception& e)
  {
    std::cerr  << "Error while reading the last games database" << std::endl;
    std::cerr  << e.what() << '\n';
  }

  // Intro for the game
  std::string playerOneName, playerTwoName, difficulty;
  std::cout << std::endl << std::endl << std::endl;
  std::cout << R"( __          __  _                            _        
 \ \        / / | |                          | |       
  \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___  
   \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \ 
    \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |
  ___\/  \/ \___|_|\___\___/|_|_|_| |_|\___|  \__\___/ 
 |  __ \                   / ____|                     
 | |__) |__  _ __   __ _  | |  __  __ _ _ __ ___   ___ 
 |  ___/ _ \| '_ \ / _` | | | |_ |/ _` | '_ ` _ \ / _ \
 | |  | (_) | | | | (_| | | |__| | (_| | | | | | |  __/
 |_|   \___/|_| |_|\__, |  \_____|\__,_|_| |_| |_|\___|
                    __/ |                              
                   |___/                               
  )" << std::endl << std::endl << std::endl;

  // Output latest games (if available)
  if (lastGamesFound == true)
  {
    std::cout << "The last games played were:" << std::endl << std::endl;
    for(const GameResult& result: results)
    {
      std::cout << result.playerOneName << " vs. " << result.playerTwoName << ". Result " << result.playerOneScore << " : " << result.playerTwoScore << " on " << result.day << "." << result.month << "." << result.year << std::endl;
    }
  }

  std::cout << std::endl << std::endl << "Press Enter to continue" << std::endl;
  std::cin.get();

  // Loop to spawn new games
  bool running = true;
  while (running)
  {
    std::cout << "Please enter player one name: " << std::endl;
    std::cin >> playerOneName;
    std::cout << "Please enter player two name (or input \"Computer\" for single-player mode): " << std::endl;
    std::cin >> playerTwoName;
    std::cout << "Please specify difficulty level. " << "Available: \"easy\" (slow), \"medium\" (fast) and \"hard\" (fast & randomness):" << std::endl;
    std::cin >> difficulty;

    if (difficulty == "easy" || difficulty == "medium" || difficulty == "hard")
    {
      Game Pong(windowWidth,windowHeight,difficulty,playerOneName,playerTwoName);
      GameResult game = Pong.Run();
      std::cout << "Please type either \"n\" for new game or \"q\" to quit" << std::endl;
      std::string input;
      std::cin >> input;
      if (input == "n")
      {
        running = true;
      }
      else
      {
        std::cout << "Game exited successfully" << std::endl;
        running = false;
      }
      results.insert(results.begin(), game);
      if(results.size()>3)
      {
        results.pop_back();
      }
    }
    else
    {
      std::cout << "No valid input detected, terminating program" << std::endl;
      running = false;
    }
  }

  // Save latest games from vector to file
  std::ofstream f("lastgames.txt");
  for(const GameResult& result: results)
  {
    f << result.playerOneName << ";" << result.playerTwoName << ";" << result.playerOneScore << ";" << result.playerTwoScore << ";" << result.day << ";" << result.month << ";" << result.year << ";" << std::endl;
  }

  // End of main function
  return 0;
}