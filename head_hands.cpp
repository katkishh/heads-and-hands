#include "Creature.h"

bool isCorrect() {
	if ( !std::cin )
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

Player PlayerCreation() {
	int attack, defence, health, minDMG, maxDMG;
	std::cout << "\t" << "сила атаки: ";
	std::cin >> attack;
	while ( !isCorrect() ) {
		std::cout << std::endl << "Неверное значение атаки, повторите еще раз" << std::endl;
		std::cin >> attack;
	}

	std::cout << "\t" << "показатель защиты: ";
	std::cin >> defence;
	while ( !isCorrect() ) {
		std::cout << std::endl << "Неверное значение защиты, повторите еще раз" << std::endl;
		std::cin >> defence;
	}

	std::cout <<  "\t" << "показатель здоровья: ";
	std::cin >> health;
	while ( !isCorrect() ) {
		std::cout << std::endl << "Неверное значение здоровья, повторите еще раз" << std::endl;
		std::cin >> health;
	}

	std::cout <<  "\t" << "минимальный наносимый урон: ";
	std::cin >> minDMG;
	while ( !isCorrect() ) {
		std::cout << std::endl << "Неверное значение минимального урона, повторите еще раз" << std::endl;
		std::cin >> minDMG;
	}

	std::cout <<  "\t" << "максимальный наносимый урон: ";
	std::cin >> maxDMG;
	while ( !isCorrect() ) {
		std::cout << std::endl << "Неверное значение максимального урона, повторите еще раз" << std::endl;
		std::cin >> maxDMG;
	}

	Player yourPlayer = Player(attack, defence, health, minDMG, maxDMG);
	return yourPlayer;
}

Monster MonsterCreation() {
	std::cout << std::endl << "Желаете подобрать противника? Введите 0, если да: ";
	int attack, defence, health, minDMG, maxDMG;
	std::string ans;
	std::cin >> ans;

	if ( ans == "0" ) {
		std::cout << "Сила атаки: ";
		std::cin >> attack;
		while ( !isCorrect() ) {
			std::cout << std::endl << "Неверное значение атаки, повторите еще раз" << std::endl;
			std::cin >> attack;
		}

		std::cout << "Показатель защиты: ";
		std::cin >> defence;
		while ( !isCorrect() ) {
			std::cout << std::endl << "Неверное значение защиты, повторите еще раз" << std::endl;
			std::cin >> defence;
		}

		std::cout << "Показатель здоровья: ";
		std::cin >> health;
		while ( !isCorrect() ) {
			std::cout << std::endl << "Неверное значение здоровья, повторите еще раз" << std::endl;
			std::cin >> health;
		}

		std::cout << "Минимальный наносимый урон: ";
		std::cin >> minDMG;
		while ( !isCorrect() ) {
			std::cout << std::endl << "Неверное значение минимального урона, повторите еще раз" << std::endl;
			std::cin >> minDMG;
		}

		std::cout << "Максимальный наносимый урон: ";
		std::cin >> maxDMG;
		while ( !isCorrect() ) {
			std::cout << std::endl << "Неверное значение максимального урона, повторите еще раз" << std::endl;
			std::cin >> maxDMG;
		}
	}
	else {
		srand(time(NULL));
		attack = rand() % 20 + 1;
		defence = rand() % 20 + 1;
		health = rand() % 50 + 1;
		minDMG = rand() % 25 + 1;
		maxDMG = rand() % 25 + 1;
		int save = minDMG;
		if ( minDMG > maxDMG ) {
			minDMG = maxDMG;
			maxDMG = save;
		}
		std::cout << "Сила атаки: " << attack << std::endl;
		std::cout << "Показатель защиты: " << defence << std::endl;
		std::cout << "Показатель здоровья: " << health << std::endl;
		std::cout << "Минимальный наносимый урон: " << minDMG << std::endl;
		std::cout << "Максимальный наносимый урон: " << maxDMG << std::endl;
	}

	Monster mon = Monster(attack, defence, health, minDMG, maxDMG);

	return mon;
}

void PerformMove(Player& player, Monster& mon1, Monster& mon2, Monster& mon3, int& monsterCounter) {

	std::cout << std::endl << "Текущий уровень здоровья равен " << player.getCurrentHealth() << ". Использовать лечащий пузырек? Введите 0, если хотите излечиться: ";
	std::string ans;
	std::cin >> ans;
	if ( ans == "0" ) player.Cure();
	std::cout << "Вы нападаете на противника" << std::endl;
	if ( mon1.isAlive() ) { 
		player.Attack(mon1);
		if ( !mon1.isAlive() ) { 
			std::cout << "Первый противник повержен!"  << std::endl;
			monsterCounter -= 1;
		}
		else {
			std::cout << "Монстр атакует вас!" << std::endl;
			mon1.Attack(player);
		}
	}
	else {
		if ( mon2.isAlive() ) {
			player.Attack(mon2);
			if ( !mon2.isAlive() ) { 
				std::cout << "Второй противник повержен!" << std::endl;
				monsterCounter -= 1;
			}
			else {
				std::cout << "Монстр атакует вас!" << std::endl;
				mon2.Attack(player);
			}
		}
		else {
			player.Attack(mon3);
			if ( !mon3.isAlive() ) { 
				std::cout << "Третий противник повержен!" << std::endl;
				monsterCounter -= 1;
			}
			else {
				std::cout << "Монстр атакует вас!" << std::endl;
				mon3.Attack(player);
			}
		}
	}

}

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "Добро пожаловать в игру P&M!" << std::endl << "Пожалуйста, создайте своего игрока, для этого вам нужно ввести следующие показатели:" << std::endl;
	Player yourPlayer = PlayerCreation();

	std::cout << std::endl << "Отлично! Вы выступаете против трёх монстров." << std::endl;
	int monsterCounter = 3;
	Monster mon1 = MonsterCreation();
	Monster mon2 = MonsterCreation();
	Monster mon3 = MonsterCreation();

	std::cout << "Да начнется игра. И пусть удача всегда будет на вашей стороне!" << std::endl;
	do {
		PerformMove(yourPlayer, mon1, mon2, mon3, monsterCounter);
	} while ( yourPlayer.isAlive() && (monsterCounter > 0) );

	if ( yourPlayer.isAlive() ) std::cout << std::endl << "Поздравляем вас с победой!";
	else std::cout << std::endl << "Игра окончена, вы проиграли";

	return 0;
}
