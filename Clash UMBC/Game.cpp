/*  File:    Game.cpp                                                                                                                                                   
    Project: CMSC 202 Project 2, Fall 2017                                                                                                                                      
    Author:  Alcides Chicas                                                                                                                                                     
    Date:    10/19/17                                                                                                                                                                                                                                                                                                                           
    E-mail:  al30@umbc.edu                                                                                                                                                         
    Description: Runs Clash Royale, UMBC version. Executes fight between player and computer. */

#include "Game.h"
const char* PROJ2_TROOPS = "proj2_troops.txt";

int validateInput (int value, int min, int max) {
  while (value < min || value > max) {
    cout << "Please enter a valid number (" << min << "-" << max << ")" << endl;
    cin >> value;
  }
  return value;
}

Game::Game() {
  // Asks user for name and starts the game
  cout << "Welcome to Clash UMBC!" << endl;
  cout << "What is your name?" << endl;
  getline(cin, m_name);

  // Asks for number of troops
  cout << "How many troops would you like? (2-5)" << endl;
  cin >> m_max;
  // Checks bounds for number of troops 
  m_max = validateInput(m_max, 2, 5);

  // Loads/randomizes all available troops
  LoadTroops();
  RandomizeTeam();
  StartGame(); 
}

void Game::LoadTroops() {
  //Opens file
  ifstream input (PROJ2_TROOPS);
  if (input.is_open()) {
    // Troop attributes
    string name;
    int health;
    int damage;
    string target;
    bool isFlying;
    // Inputs data for troop and instantiates it while adding it to m_troop
    while(input >> name) {
      input >> health >> damage >> target >> isFlying;
      m_troop.push_back(Troop(name, health, damage, target, isFlying));
      if (input.peek() == '\n') {
	      input.ignore();
      }  
    }
  }
  input.close();
  cout << "Troops loaded." << endl;
}

void Game::RandomizeTeam() {
  // Player and Computer have random decks
  srand(time(NULL));
  for (int i = 0; i < m_max; i++) {
    // Variable for random number from m_troop
    int player = rand() % m_troop.size();
    int comp = rand() % m_troop.size();
    m_player.push_back(m_troop.at(player));
    m_computer.push_back(m_troop.at(comp));
  }
}

void Game::StartGame() {

  // Variable for main menu choice
  int choice = 1;

  // Game starts with player's turn
  m_curPlayer = 1;
  while (choice != 4 && !m_computer.empty() && !m_player.empty()) {

    // Updates main menu choice
    DisplayTeams();
    MainMenu();
    cin >> choice;
    choice = validateInput(choice, 1, 4);

    switch (choice) {
    case 1:
      DisplayTeams();
      break;
    case 2:
      ChangeTroop();
      break;
    case 3:
      // Switches player turns and attacks twice per round (one per player)
      Attack();
      m_curPlayer = (m_curPlayer == 1) ? 0 : 1; // Switch player attacking
      Attack();
      break;
    }
  }

  // Terminates game once one of the decks is empty
  if ((m_computer.empty()) || (m_player.empty())) {
    // Win condition (one of the decks is empty)
    if (m_computer.empty()) {
      cout << "*******************" << endl;
      cout << "You win!" << endl;
      cout << "You have defeated the enemy troops!" << endl;
    } else if (m_player.empty()) {
      cout << "*******************" << endl;
      cout << "Your troops have been defeated!" << endl;
      cout << "You lose!" << endl;
    }
    cout << "Thank you for playing Clash UMBC!" << endl;
    exit(0);
  }
  cout << "Exiting Game..." << endl;
}

void Game::ChangeTroop() {
  // Current troop being used changes
  cout << "*******************" << endl;
  DisplayTeam();
  
  // Allows user to chooses which of their troops they want to attack first with
  cout << "Which troop do you want to use?" << endl;
  cin >> m_curTroop;
  // Checks bounds for troops
  m_curTroop = validateInput(m_curTroop, 1, m_player.size());
  
  // Switches the troop user chooses with m_player.at(0)
  Troop temp = m_player.at(m_curTroop - 1);
  m_player.at(m_curTroop - 1) = m_player.at(0);
  m_player.at(0) = temp;
}

void Game::MainMenu() {
  cout << "What would you like to do?" << endl;
  cout << "1. Display Teams" << endl;
  cout << "2. Change Current Troop" << endl;
  cout << "3. Attack!" << endl;
  cout << "4. Quit" << endl;
}

void Game::DisplayTeams() {

  DisplayTeam();
  cout << "*******************" << endl;
  cout << "Computer's Team:" << endl;
  
  for (unsigned int i = 0; i < m_computer.size(); i++) {
    cout << i + 1 << ". " << m_computer.at(i).GetName() << " " << m_computer.at(i).GetHealth() << endl;
  }
  cout << "*******************" << endl;
}


void Game::DisplayTeam() {
  // Displays numbered list for changing the current troop of the player
  cout << "*******************" << endl;
  cout << m_name << "'s Team:" << endl;
  for (unsigned int i = 0; i < m_player.size(); i++) {
    cout << i + 1 << ". " << m_player.at(i).GetName() << " " << m_player.at(i).GetHealth() << endl;
  }
}

void Game::Attack() {

  // Player's turn
  if (m_curPlayer == 1 && !m_computer.empty() && !m_player.empty()) {
    // If computer troop dead, remove
    if(m_computer.at(0).GetHealth() <= 0) {
      cout << m_computer.at(0).GetName() << " dies." << endl;
      m_computer.erase(m_computer.begin());
      
    } else {
        // Attack computer troop and check if it's dead
        m_player.at(0).AttackTroop(m_computer.at(0));
        if (m_computer.at(0).GetHealth() <= 0) {
          cout << m_computer.at(0).GetName() << " dies." << endl;
          m_computer.erase(m_computer.begin());
        }
    }
    
  // Computer's turn
  } else if (m_curPlayer == 0 && !m_player.empty() && !m_computer.empty()) {
    // If player troop dead, remove
    if(m_player.at(0).GetHealth() <= 0) {
      cout << m_player.at(0).GetName() << " dies." << endl;
      m_player.erase(m_player.begin());
    
    } else {
      // Attack player troop and check if it's dead
      m_computer.at(0).AttackTroop(m_player.at(0));
      if (m_player.at(0).GetHealth() <= 0) {
        cout << m_player.at(0).GetName() << " dies." << endl;
        m_player.erase(m_player.begin());
      }
    }
  }
}