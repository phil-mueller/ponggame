#include <Game.h>

// Declare variables
const int windowWidth = 1600;
const int windowHeight = 900;

// Main function
int main() {

  // Intro for the game
  std::string playerOneName, playerTwoName, difficulty;
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
  )" << std::endl;
  std::cout << "Press Enter to continue" << std::endl;
  std::cin.get();
  std::cout << "Please enter player one name: " << std::endl;
  std::cin >> playerOneName;
  std::cout << "Please enter player two name (or input \"Computer\" for single-player mode): " << std::endl;
  std::cin >> playerTwoName;
  std::cout << "Please specify difficulty level. " << "Available: \"easy\" (slow), \"medium\" (fast) and \"hard\" (fast & randomness):" << std::endl;
  std::cin >> difficulty;

  if (difficulty == "easy" || difficulty == "medium" || difficulty == "hard")
  {
    Game Pong(windowWidth,windowHeight,difficulty,playerOneName,playerTwoName);
    Pong.Run();
    std::cout << "Game exited successfully" << std::endl;
  }
  else
  {
    std::cout << "No valid input detected, terminating program" << std::endl;
  }
  
  return 0;
}