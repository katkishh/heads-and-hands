#pragma once
#include<iostream>
#include <stdlib.h>
#include<string>
#include<cmath>
#include <time.h>

class Creature {
public:

	Creature(int attack, int defence, int health,int minDamage, int maxDamage) {
		m_attack = attack;
		if ( attack < 1 ) {
			std::cerr << "Неверное значение минимальной атаки. Минимальная атака по умолчанию: 1" << std::endl;
			m_attack = 1;
		}
		if ( attack > 20 ) {
			std::cerr << "Неверное значение максимальной атаки. Максимальная атака по умолчанию: 20" << std::endl;
			m_attack = 20;
		}

		m_defence = defence;
		if ( defence < 1 ) {
			std::cerr << "Неверное значение защиты, введено слишком малое значение. Защита по умолчанию: 1" << std::endl;
			m_defence = 1;
		}
		if ( defence > 20 ) {
			std::cerr << "Неверное значение защиты, введено слишком большое значение. Защита по умолчанию: 20" << std::endl;
			m_defence = 20;
		}

		m_maxHealth = health;
		if ( health < 1 ) { 
			std::cerr << "Неверное значение здоровья. Здоровье по умолчанию: 1" << std::endl;
			m_maxHealth = 1;
		}
		m_currentHealth = m_maxHealth;
		
		m_minDamage = minDamage;
		m_maxDamage = maxDamage;
		if ( minDamage < 1 ) {
			std::cerr << "Неверное значение минимального урона, введено слишком малое значение. Минимальный урон по умолчанию: 1" << std::endl;
			m_minDamage = 1;
			minDamage = 1;
		}
		if ( maxDamage < 1 ) {
			std::cerr << "Неверное значение максимального урона, введено слишком малое значение. Максимальный урон по умолчанию: 1" << std::endl;
			m_maxDamage = 1;
			maxDamage = 1;
		}
		if ( minDamage > maxDamage ) {
			std::cerr << "Ошибка ввода минимального и максимального уронов. Значения поменялись местами" << std::endl;
			m_maxDamage = minDamage;
			m_minDamage = maxDamage;
		}
	};
	~Creature() {};

	bool isAlive() {
		return ( m_currentHealth > 0 ) ? true : false;
	}

	void Attack( Creature& victim ) {
		int modAtk = m_attack - victim.m_defence + 1;
		bool flag = false;
		srand(time(NULL));
		int number = rand() % 6 + 1;
		flag = ( number == 5 || number == 6 ) ? true : false;
		if ( !flag ) {
			for ( int i = 1; i < modAtk; ++i ) {
				number = rand() % 6 + 1;
				flag = ( number == 5 || number == 6 ) ? true : false;
				if ( flag ) break;				//зачем генерировать все остальные, если наткнулись на 5 или 6?
			}
		}
		if (flag) {
			int damage = rand() % (m_maxDamage - m_minDamage + 1) + m_minDamage + 1;
			std::cout << "Нанесено урона: " << damage << std::endl;
			victim.m_currentHealth -= damage;
		}
		else std::cout << "Попытка нанесения урона не увенчалась успехом" << std::endl;
	}

	int getAttack() {
		return m_attack;
	}

	int getDefence() {
		return m_defence;
	}

	int getMaxHealth() {
		return m_maxHealth;
	}

	int getCurrentHealth() {
		return m_currentHealth;
	}

	int getMinDMG() {
		return m_minDamage;
	}

	int getMaxDMG() {
		return m_maxDamage;
	}

protected:
	int m_attack;
	int m_defence;
	int m_maxHealth;
	int m_currentHealth;
	int m_minDamage;
	int m_maxDamage;
};

class Player : public Creature {
	
public:
	Player(int attack, int defence, int health, int minDamage, int maxDamage) : Creature(attack, defence, health, minDamage, maxDamage) {};
	~Player() {};

	void Cure() {
		if ( m_cureCounter < 3 ) {
			m_cureCounter += 1;
			m_currentHealth += round(0.5 * m_maxHealth);
			m_currentHealth = (m_currentHealth < m_maxHealth) ? m_currentHealth : m_maxHealth;			//поправка на пере-хилл
		}
		else std::cout << "Вы достигли лимита лечения" << std::endl;
	}

private:
	uint32_t m_cureCounter{};
};

class Monster : public Creature {
public:
	Monster(int attack, int defence, int health, int minDamage, int maxDamage) : Creature(attack, defence, health, minDamage, maxDamage) {};
	~Monster() {};
};
