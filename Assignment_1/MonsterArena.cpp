#include <iostream>
#include <stdlib.h>
using namespace std;

enum MonsterType {
	Goblin,
	Troll,
	Orc
};

class Monster
{
private:
	int Health;
	int MaxHealth;
	int Damage;
	MonsterType Type;

public:
	void decreaseHealth(int decrease) {
		Health = Health <= decrease ? 0 : Health - decrease;
	}
	void increaseHealth(int increase) {
		if (Health == MaxHealth)
			return;
		Health += increase;
		if (Health > MaxHealth)
			Health = MaxHealth;
	}
	int checkHealth() {
		return Health;
	}
	void setHealth(int health) {
		Health = health;
	}
	void setMaxHealth(int maxHealth) {
		MaxHealth = maxHealth;
	}
	MonsterType checkType() {
		return Type;
	}
	void setType(MonsterType type) {
		Type = type;
	}
	int attack() {
		return Damage;
	}
	void setDamage(int damage) {
		Damage = damage;
	}
	void resetHealth() {
		Health = MaxHealth;
	}
};

class Goblin : public Monster
{
private:
	int NumOfAttacks;

public:
	Goblin() {
		setType(MonsterType::Goblin);
		setHealth(50); //Arbitrary Value, MODIFY
		setMaxHealth(100); //Arbitrary Value, MODIFY
		setDamage(10); //Arbitrary Value, MODIFY
		NumOfAttacks = 3; //Arbitrary Value, MODIFY
	}

	int getNumOfAttacks() {
		return NumOfAttacks;
	}
};

class Troll : public Monster
{
private:
	int HealthRegen;

public:
	Troll() {
		setType(MonsterType::Troll);
		setHealth(50); //Arbitrary Value, MODIFY
		setMaxHealth(100); //Arbitrary Value, MODIFY
		setDamage(10); //Arbitrary Value, MODIFY
		HealthRegen = 15; //Arbitrary Value, MODIFY
	}

	int getHealthRegen() {
		return HealthRegen;
	}
};

class Orc : public Monster
{
private:
	int DamageBlock;
	int DamageReflected;

public:
	Orc() {
		setType(MonsterType::Orc);
		setHealth(50); //Arbitrary Value, MODIFY
		setMaxHealth(100); //Arbitrary Value, MODIFY
		setDamage(10); //Arbitrary Value, MODIFY
		DamageBlock = 10; //Arbitrary Value, MODIFY
		DamageReflected = 15; //Arbitrary Value, MODIFY
	}

	int getDamageBlock() {
		return DamageBlock;
	}

	int getDamageReflected() {
		return DamageReflected;
	}
};

int main()
{


	cout << "Hello World!" << endl;
	cout << "Wassup World B)!" << endl;

	return 0;
}
