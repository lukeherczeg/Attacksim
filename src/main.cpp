#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "controller.h"

using namespace std;

int randomThrough(int start, int num){
	return start + (rand() % num);
}

string toUpper(string input){
	locale loc;
	string newInput = "";
	for(string::size_type i = 0; i < input.length(); ++i)
		newInput += toupper(input[i],loc);
	return newInput;
}

bool affirmInput(string input){
	return (toUpper(input) == "YES" || toUpper(input) == "YEAH" || toUpper(input) == "SOMETHING" || toUpper(input) == "YEP");
}

Controller::Controller(){
	this->damage = 0;
	this->numTimes = 0;
	this->totalHP = 100;
	this->programLoops = 0;
	this->criticalDamage = 0;
	this->attackDamage = 0;
	this->percentHeal = 0;
	this->percentCrit = 0;
	this->attacking = true;
	this->attacked = true;
	this->program = true;
	this->ready = false;
	this->isCritical = false;
	this->input = "";
}

void Controller::damageInit(){
	if(totalHP == 100)
		cout << "HP: " << totalHP << endl;

	percentHeal = randomThrough(1, 100);
	percentCrit = randomThrough(1, 100);
	attackDamage = randomThrough(5, 7);
	criticalDamage = 2 * attackDamage;

	if(percentCrit <= 70){ // normal hit damage
		damage = attackDamage * modifier;
	}
	else if(percentCrit >= 70){ // critical hit damage, is 2 * the attack damage and multiplied by some multiplier.
		damage = criticalDamage * modifier;
		isCritical = true;
	}

	if(!affirmInput(input))
		attacked = false;
}

void Controller::attackSequence(){
	numTimes++;
	if(totalHP < 90 && percentHeal > 85){
		totalHP += heal;
		cout << "Heal: " << heal << " |  HP: " << totalHP << endl;
	}
	totalHP -= damage;
	if(totalHP > 0){
		if(isCritical)
			cout << "Damage: " << damage << " (crit) |  " << "HP: " << totalHP << endl;
		else
			cout << "Damage: " << damage << " |  HP: " << totalHP << endl;
	}
	else{
		cout << "Damage: " << damage << " |  HP: 0" << endl;
		attacking = false;
	}
	isCritical = false;

}

void Controller::scene(int programLoops){
	if(programLoops == 0)
		cout << "Ready?" << endl;
	else{
		cout << "_____________________________________________________________________________________________________________\n\n" << endl;
		cout << "Again?" << endl;
	}
}

void Controller::run(){
	while(program){
		scene(programLoops);
		cin >> input;

		if(affirmInput(input)){
			ready = true;
			attacking = true;
			attacked = true;
		}
		else{
			program = false;
			break;
		}

		cin.clear();

		if(ready){
			cout << "Attack?"<< endl;
			cin >> input;
			cout << endl;
			while(attacking){
				cin.clear();
				damageInit();
				if(attacked)
					this->attackSequence();
				else{
					cout << "Nothing happened" << endl;
					break;
				}
			}
			numTimes = 0;
		}
		damage = 0;
		totalHP = 100;
		programLoops++;
	}
}

int main(){
	srand(time(0));
	Controller * controller = new Controller();
	controller->run();
	return 0;
}
