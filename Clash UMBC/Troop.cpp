/*  File:    Troop.cpp                                                                                                                                                       
    Project: CMSC 202 Project 2, Fall 2017                                                                                                                                   
    Author:  Alcides Chicas                                                                                                                                                     
    Date:    10/19/17                                                                                                                                                                                                                                                                                                                           
    E-mail:  al30@umbc.edu                                                                                                                                                         
    Description: Accessors and mutators for troops, as well as attack. */

#include "Troop.h"

Troop::Troop(string name, int health, int damage, string target, bool isFlying) {
  m_name = name;
  m_health = health;
  m_damage = damage;
  m_target = target;
  m_isFlying = isFlying;
}

string Troop::GetName() {
  return m_name;
}

void Troop::SetName(string name) {
  m_name = name;
}

int Troop::GetHealth() {
  return m_health;
}

void Troop::SetHealth(int health) {
  m_health = health;
}

int Troop::GetDamage() {
  return m_damage;
}

string Troop::GetTarget() {
  return m_target;
}

bool Troop::GetIsFlying() {
  return m_isFlying;
}

void Troop::AttackTroop(Troop& enemy) {

  // Attacks enemy troop and sets health
  if (m_target == "Both" && m_isFlying) {
    cout << m_name << " attacks " << enemy.GetName() << " from the air!" << endl;
    enemy.SetHealth(enemy.GetHealth() - m_damage);
    cout << "Damage Occuring " << m_damage << endl;

  } else if (m_target == "Both" && !m_isFlying) {
    cout << m_name << " attacks " << enemy.GetName() << " from the ground!" << endl;
    enemy.SetHealth(enemy.GetHealth() - m_damage);
    cout << "Damage Occuring " << m_damage << endl;

  } else if (m_target == "Ground" && enemy.GetIsFlying()) {
    cout << m_name << " cannot attack air troop " << enemy.GetName() << "!" << endl; 

  } else if (m_target == "Ground" && !enemy.GetIsFlying()) {
    cout << m_name << " attacks " << enemy.GetName() << " from the ground!" << endl;
    enemy.SetHealth(enemy.GetHealth() - m_damage);
    cout << "Damage Occuring " << m_damage << endl;
  }
}
