

#include <bits/stdc++.h>
#include "objects.h"
/*----------------------------------------------------------------------------
//TODO
//Add shop
//Add items
//Alt prob got more stuff
//rebalancing
//new mob mechanics
----------------------------------------------------------------------------*/


void levelPlayer();
void healthChecker() {
	if (charc->Player->hp <= 0) {
		std::cout << "Game Over... your health has been restored";
		charc->Player->hp = charc->Player->vitality ;

		
	}

}

void levelUpChecker() {
	if (charc->exp >= (charc->level * charc->expReq)) {
		std::cout << "You leveled up to level " << charc->level + 1 << "(was " << charc->level << ")!\nNext level up requires " << charc->level * charc->expReq << "XP\n";
		charc->exp -= (charc->level * charc->expReq);
		charc->level += 1;
		levelPlayer();
	}
}






void encounter::fight() {
	Game->battle(this);
}


Player::Player() {
	entity* player = new entity;
	std::cout << "Your character is randomize in stat distribution.\n";
	int rollMulti = 30;
	int backRoll = (rand() % 20) + 5;
	int roll = rand() % rollMulti;
	player->str += roll + backRoll;
	std::cout << "You have " << player->str << " Strength\n";
	 backRoll = (rand() % 20) + 5;

	roll = rand() % rollMulti;
	player->vitality += 1.2*(((rand() % 2) + 1) * (roll + 10 + backRoll));
	std::cout << "You have " << player->vitality << " Vitality\n";
	player->hp = player->vitality;
	 backRoll = (rand() % 20) + 5;

	roll = rand() % rollMulti + backRoll;
	player->dex += roll;
	std::cout << "You have " << player->dex << " Dexterity\n";
	 backRoll = (rand() % 20) + 5;

	roll = rand() % rollMulti + backRoll;
	player->charisma += roll;
	std::cout << "You have " << player->charisma << " Charisma\n";
	 backRoll = (rand() % 20) + 5;

	roll = rand() % rollMulti + backRoll;
	player->endurance += roll;
	std::cout << "You have " << player->endurance << " Endurance\n";

	backRoll = (rand() % 20) + 5;

	roll = rand() % rollMulti + backRoll;
	player->Agility += roll;
	std::cout << "You have " << player->Agility << " Agility\n";

	player->critc = 100 * ((player->Agility * log(player->dex+1)) / 1000);
	player->critd = (player->dex / 150);
	if (player->critc >= 85) {
		player->critc = 85;
	}

	charc->Player = player;
	Game->player = player;
}

void levelPlayer() {

	int rollMulti = 4 * ((charc->level / 10) + 1);
	int roll = rand() % rollMulti + 1;
	charc->Player->str += roll;





	roll = rand() % rollMulti + 1;
	charc->Player->str += roll;
	charc->Player->hp = charc->Player->vitality;


	roll = rand() % rollMulti + 1;
	charc->Player->dex += roll;


	roll = rand() % rollMulti + 1;
	charc->Player->charisma += roll;


	roll = rand() % rollMulti + 1;
	charc->Player->endurance += roll;


	roll = rand() % rollMulti + 1;
	charc->Player->Agility += roll;

	charc->Player->critc = 100 * (((charc->Player->Agility) * log((charc->Player->dex) + 1)) / 1000);
	charc->Player->critd = ((charc->Player->dex) / 150);
	if (charc->Player->critc >= 85) {
		charc->Player->critc = 85;
	}


}

encounter::encounter(int level) {
	entity* enemy = new entity;
	int eliteRoll = rand() % 20;
	if (eliteRoll <= 1) {
		this->elite = true;
	}
	std::cout << "Oh no you encounter a lvl->" << level << " enemy!\n";
	int attributepoints = 10 * (0.5*(log(level+1)) + 1);
	int eliteBonus = 0;
	if (this->elite) {
		eliteBonus = ((level/2)+1)*((rand() % attributepoints) * 2);
	}
		enemy->level = level;
	int roll = rand() % attributepoints;
	enemy->str += roll + eliteBonus;
	std::cout << "They have " << enemy->str << " Strength\n";
	roll = rand() % attributepoints;
	enemy->vitality += roll + (10 * (level/4) + 20) + (3*eliteBonus);
	std::cout << "They have " << enemy->vitality << " Vitality\n";
	enemy->hp = enemy->vitality ;
	roll = rand() % attributepoints;
	enemy->dex += roll + eliteBonus;
	std::cout << "They have " << enemy->dex << " Dexterity\n";
	roll = rand() % attributepoints;
	enemy->charisma += roll + eliteBonus;
	std::cout << "They have " << enemy->charisma << " Charisma\n";
	roll = rand() % attributepoints;
	enemy->endurance += roll + eliteBonus;
	std::cout << "They have " << enemy->endurance << " Endurance\n";
	roll = rand() % attributepoints;
	enemy->Agility += roll + eliteBonus;
	std::cout << "They have " << enemy->Agility << " Agility\n";
	enemy->critc = 100 * ((enemy->Agility * log(enemy->dex+1)) / 1000);
	if (enemy->critc >= 85) {
		enemy->critc = 85;
	}
	enemy->critd = enemy->dex / static_cast<double>(145);
	int nameRoll  = (rand() % 5);
	enemy->name = nameRoll;
	this->enemy = enemy;

	
	//Game->encounter = this;
	
}


double DamageCalc(entity e1, entity e2) {
	double damage;
	damage = e1.str;
	damage = damage * abs(1 - ((3 * log((e2.endurance) + 1) / 100)));
	float crit = rand() % 100;
	if (crit <= e1.critc) {
		damage *= (1.5 + e1.critd);
		std::cout << "CRITICAL HIT\n";
	}


	return damage;
}

void dropRoll(encounter* enemy);

void game::battle(encounter* enemy) {
	
	Game->player = charc->Player;
	
	entity* e1 = Game->player;
	entity* e2 = enemy->enemy;
	bool elite = enemy->elite;
	//implement later
	int tooWeak = 0;
	bool turn = true;

	bool endBattle = false;
	int attack1, attack0;
	if (e1->Agility <= e2->Agility)
		turn = false;
	while (endBattle == 0) {
		switch (turn) {
		case 0:
			attack0 = DamageCalc(*e2,*e1);
			if (attack0 <= 0) {
				attack0 = 0;
				std::cout <<"You have too much endurance for the enemy to handle\nthey aren't able to damage you\n";
				turn = 1;
			}
			else {
				e1->hp -= attack0;
				if (e1->hp <= 0) {
					std::cout << "The enemy attacked you for: " << attack0 << "\n" << "You have " << "0" << " HP left \n";
				}
				else {
					std::cout << "The enemy attacked you for: " << attack0 << "\n" << "You have " << e1->hp << " HP left \n";
				}
			}
			turn = 1;

			break;
		case 1:


			attack1 = DamageCalc(*e1, *e2);
			if (attack1 <= 0) {
				attack1 = 0;
				std::cout << "Your opponent has too much endurance to be able to damage them\n";
				tooWeak += 1;

				std::cout << "if this happens " << (10 - tooWeak) << " more times you will be kicked from the battle\n";
			}
			else {


				e2->hp -= attack1;
				if (e2->hp <= 0) {
					std::cout << "You attacked the enemy for: " << attack1 << "\n" << "They have " << "0" << " HP left \n";
				}
				else
				{
					std::cout << "You attacked the enemy for: " << attack1 << "\n" << "They have " << e2->hp << " HP left \n";
				}
			}	
				turn = 0;
			break;
		}

		if (e1->hp <= 0 or e2->hp <= 0) {
			if (turn == 0) {
				std::cout << "You won! ";
				int goldRoll;
					int expRoll;
				if (elite) {
					goldRoll = 10*(((1 + (rand() % 35)) * ((e2->charisma + e2->level) / 3)) + 10);
					expRoll = 10*(((1 + (rand() % 15)) * ((e2->charisma + e2->level) / 3)) + 5);

				}
				else {
					goldRoll = ((1 + (rand() % 35)) * ((e2->charisma + e2->level) / 3)) + 10;
					expRoll = ((1 + (rand() % 15)) * ((e2->charisma + e2->level) / 3)) + 5;
				}
				charc->gold += goldRoll;
				charc->exp += expRoll;
				std::cout << "Recived " << goldRoll << "$ Gold, " << expRoll << "XP!\n";
				if (elite) {
					std::cout << "The elite healed you!";
					charc->Player->hp = charc->Player->vitality;
				}
				dropRoll(enemy);
				Game->player = NULL;
				enemy->endBattle = true;
				return;
			}
			std::cout << "You lost.";
			std::cout <<std::fixed << std::setprecision(2) << " 10% of your gold (" << charc->gold * 0.1  << ") and xp (" << charc->exp * 0.1 << ") has been taken\n";
			charc->gold -= charc->gold*0.1;
			charc->exp -= charc->exp*0.1;
			enemy->endBattle = true;
			Game->player = NULL;
			return;
		}
		if (tooWeak >= 10 and turn == 0) {
			std::cout << "You are unable to damage the opponent";
			enemy->endBattle = true;
			Game->player = NULL;
			return;
		}
	}
}




void dropRoll(encounter* enemy) {
	std::string EnemyTypes[5] = { "RAT", "Worm", "Virus", "Warthog", "Fairy" };
	int eliteMultiplier = 1;
	if (enemy->elite) {
		eliteMultiplier = 2.5;
	}
	float roll = rand() % 100;
	if (EnemyTypes[enemy->enemy->name] == "RAT") {
		if (roll <= 10 * eliteMultiplier) {
			std::cout << "You got a Sword from that RAT!";
			item Item(0);
			charc->inv->items.push_back(Item);
		}
	} 
	if (EnemyTypes[enemy->enemy->name] == "Warthog") {
		if (roll <= 10 * eliteMultiplier) {
			std::cout << "You got a Void Necklace from that Warthhog!";
			item Item(1);
			charc->inv->items.push_back(Item);
		}
	}

	if (EnemyTypes[enemy->enemy->name] == "Fairy") {
		if (roll <= 10 * eliteMultiplier) {
			std::cout << "You got a Swift Brace from that Fairy!";
			item Item(2);
			charc->inv->items.push_back(Item);
		}
	}
	if (EnemyTypes[enemy->enemy->name] == "Worm") {
		if (roll <= 10 * eliteMultiplier) {
			std::cout << "You got a Lucky Rock from that Fairy!";
			item Item(3);
			charc->inv->items.push_back(Item);
		}
	}

}