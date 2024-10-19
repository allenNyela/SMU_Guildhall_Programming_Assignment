#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

enum MonsterType {
	GoblinType,
	TrollType,
	OrcType
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
	virtual string listName() = 0;
};

class Goblin : public Monster
{
private:
	int NumOfAttacks;

public:
	Goblin() {
		setType(MonsterType::GoblinType);
		setHealth(30); //Arbitrary Value, MODIFY
		setMaxHealth(100); //Arbitrary Value, MODIFY
		setDamage(10); //Arbitrary Value, MODIFY
		NumOfAttacks = 3; //Arbitrary Value, MODIFY
	}

	int getNumOfAttacks() {
		return NumOfAttacks;
	}

	string listName() {
		return "Goblin";
	}
};

class Troll : public Monster
{
private:
	int HealthRegen;

public:
	Troll() {
		setType(MonsterType::TrollType);
		setHealth(12); //Arbitrary Value, MODIFY
		setMaxHealth(100); //Arbitrary Value, MODIFY
		setDamage(10); //Arbitrary Value, MODIFY
		HealthRegen = 15; //Arbitrary Value, MODIFY
	}

	int getHealthRegen() {
		return HealthRegen;
	}

	string listName() {
		return "Troll";
	}
};

class Orc : public Monster
{
private:
	int DamageBlock;
	int DamageReflected;

public:
	Orc() {
		setType(MonsterType::OrcType);
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

	string listName() {
		return "Orc";
	}
};

class Team
{
private:
	vector<Monster*> Roster;
	int LeadMonsterIdx;
	string TeamName;

public:
	Team(string name) {
		LeadMonsterIdx = 0;
		TeamName = name;
	}

	void addMonster(Monster* monster) {
		Roster.push_back(monster);
	}

	void removeLeadMonster() {
		LeadMonsterIdx++;
	}

	Monster* getLeadMonster() {
		if (LeadMonsterIdx > Roster.size() - 1) {
			return NULL;
		}
		else {
			return Roster.at(LeadMonsterIdx);
		}
	}

	string listTeam() {
		string teamRoster = "";
		teamRoster += "[ " + TeamName + " | ";
		for (int i = LeadMonsterIdx; i < Roster.size(); i++) {
			if (i == LeadMonsterIdx) {
				teamRoster += "(Lead)";
			}
			teamRoster += (*(Roster[i])).listName() + "(" + to_string((*(Roster.at(i))).checkHealth()) + ") ";
		}
		teamRoster += "]";
		return teamRoster;
	}

	void resetTeam() {
		LeadMonsterIdx = 0;
		for (int i = 0; i < Roster.size(); i++) {
			(*(Roster[i])).resetHealth();
		}
	}

	void clearTeam() {
		Roster.clear();
		LeadMonsterIdx = 0;
	}
};

class Battle
{
private:
	int Turn;
	bool GameOver;
	Team* Team1;
	Team* Team2;
public:
	Battle(Team* team1, Team* team2) {
		Team1 = team1;
		Team2 = team2;
		Turn = 1;
		GameOver = false;
	}

	string printBattleStart() {
		string start = "Battle Starting\n\n";
		start += printTeams() + "\n\n";
		return start;
	}

	string printTeams() {
		string matchup = (*Team1).listTeam() + "  vs.  " + (*Team2).listTeam();
		return matchup;
	}

	string performTurn() {
		MonsterType team1LeadType = (*(*Team1).getLeadMonster()).checkType();
		MonsterType team2LeadType = (*(*Team2).getLeadMonster()).checkType();
		if (team1LeadType == MonsterType::GoblinType && team2LeadType == MonsterType::TrollType) {
			for (int i = 0; i < (Goblin)(*(*Team1).getLeadMonster())) {

			}
		}
	}
};

int main()
{
	Troll* troll1 = new Troll();
	Orc* orc1 = new Orc();
	Goblin* goblin1 = new Goblin();
	Team team1 = Team("BestMonsters!");
	team1.addMonster(troll1);
	team1.addMonster(orc1);
	team1.addMonster(goblin1);

	Troll* troll2 = new Troll();
	Orc* orc2 = new Orc();
	Goblin* goblin2 = new Goblin();
	Team team2 = Team("BetterMonsters!");
	team2.addMonster(goblin2);
	team2.addMonster(troll2);
	team2.addMonster(orc2);	
	//team1.removeLeadMonster();
	//team1.removeLeadMonster();
	//team1.removeLeadMonster();
	Battle game = Battle(&team1, &team2);
	
	cout << "Hello World!" << endl;
	cout << game.printBattleStart() << endl;
	//cout << team2.listTeam() << endl;

	return 0;
}
