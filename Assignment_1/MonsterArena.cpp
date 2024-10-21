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
	int NumOfAttacks;
	int HealthRegen;
	int DamageBlock;
	int DamageReflected;
	MonsterType Type;

public:
	void decreaseHealth(int decrease) {
		Health -= decrease;
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
	void setNumOfAttacks(int num) {
		NumOfAttacks = num;
	}
	int getNumOfAttacks() {
		return NumOfAttacks;
	}
	void setHealthRegen(int num) {
		HealthRegen = num;
	}
	int getHealthRegen() {
		return HealthRegen;
	}
	void setDamageBlock(int num) {
		DamageBlock = num;
	}
	int getDamageBlock() {
		return DamageBlock;
	}
	void setDamageReflected(int num) {
		DamageReflected = num;
	}
	int getDamageReflected() {
		return DamageReflected;
	}
	virtual string listName() = 0;
};

class Goblin : public Monster
{
public:
	Goblin() {
		setType(MonsterType::GoblinType);
		setHealth(40); //Arbitrary Value, MODIFY
		setMaxHealth(40); //Arbitrary Value, MODIFY
		setDamage(10); //Arbitrary Value, MODIFY
		setNumOfAttacks(5); //Arbitrary Value, MODIFY
		setHealthRegen(0);
		setDamageBlock(0);
		setDamageReflected(0);
	}

	string listName() {
		return "Goblin";
	}
};

class Troll : public Monster
{
public:
	Troll() {
		setType(MonsterType::TrollType);
		setHealth(70); //Arbitrary Value, MODIFY
		setMaxHealth(70); //Arbitrary Value, MODIFY
		setDamage(15); //Arbitrary Value, MODIFY
		setNumOfAttacks(0);
		setHealthRegen(6); //Arbitrary Value, MODIFY
		setDamageBlock(0);
		setDamageReflected(0);
	}

	string listName() {
		return "Troll";
	}
};

class Orc : public Monster
{
public:
	Orc() {
		setType(MonsterType::OrcType);
		setHealth(50); //Arbitrary Value, MODIFY
		setMaxHealth(50); //Arbitrary Value, MODIFY
		setDamage(8); //Arbitrary Value, MODIFY
		setNumOfAttacks(0);
		setHealthRegen(0);
		setDamageBlock(6); //Arbitrary Value, MODIFY
		setDamageReflected(5); //Arbitrary Value, MODIFY
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

	string getTeamName() {
		return TeamName;
	}

	string listTeam() {
		string teamRoster = "";
		teamRoster += "[ " + TeamName + " | ";
		for (int i = Roster.size() - 1; i >= LeadMonsterIdx; i--) {
			if (i == LeadMonsterIdx) {
				teamRoster += "(Lead)";
			}
			teamRoster += (*(Roster[i])).listName() + "(" + to_string((*(Roster.at(i))).checkHealth()) + ") ";
		}
		teamRoster += "]";
		return teamRoster;
	}

	string listTeamAlternate() {
		string teamRoster = "";
		teamRoster += "[ ";
		for (int i = LeadMonsterIdx; i < Roster.size(); i++) {
			if (i == LeadMonsterIdx) {
				teamRoster += "(Lead)";
			}
			teamRoster += (*(Roster[i])).listName() + "(" + to_string((*(Roster.at(i))).checkHealth()) + ") ";
		}
		teamRoster += "| " + TeamName + " ]";
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
	int BattleNum;
	bool GameOver;
	Team* Team1;
	Team* Team2;
public:
	Battle(Team* team1, Team* team2) {
		Team1 = team1;
		Team2 = team2;
		Turn = 1;
		BattleNum = 1;
		GameOver = false;
	}

	bool isGameOver() {
		return GameOver;
	}

	string resetGame() {
		GameOver = false;
		Team1->resetTeam();
		Team2->resetTeam();
		Turn = 1;
		return "\nGame resetting...";
	}

	void clearGame(Team* team1, Team* team2) {
		Team1 = team1;
		Team2 = team2;
		Turn = 1;
		GameOver = false;
	}

	string printBattleStart() {
		string start = "";
		for (int i = 0; i < 100; i++) {
			start += "-";
		}
		start += "\nBattle Starting           Game: " + to_string(BattleNum) + "\n\n";
		start += printTeams() + "\n\n";
		BattleNum++;
		return start;
	}

	string printTeams() {
		string matchup = (*Team1).listTeam() + "  vs.  " + (*Team2).listTeamAlternate();
		return matchup;
	}

	string performTurn() {
		string turn = "";
		if (!GameOver) {
			MonsterType team1LeadType = (*(*Team1).getLeadMonster()).checkType();
			MonsterType team2LeadType = (*(*Team2).getLeadMonster()).checkType();
			for (int i = 0; i < 100; i++) {
				turn += "-";
			}
			turn += "\n";
			turn += "Turn " + to_string(Turn) + "\n\n";
			turn += printTeams() + "\n\n";
			if (team1LeadType == MonsterType::GoblinType && team2LeadType == MonsterType::TrollType) {
				for (int i = 0; i < (*Team1).getLeadMonster()->getNumOfAttacks(); i++) {
					turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";
					(*Team2).getLeadMonster()->decreaseHealth((*Team1).getLeadMonster()->attack());
				}
				(*Team1).getLeadMonster()->decreaseHealth((*Team2).getLeadMonster()->attack());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage\n";
				(*Team2).getLeadMonster()->increaseHealth(Team2->getLeadMonster()->getHealthRegen());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " regenerates " + to_string(Team2->getLeadMonster()->getHealthRegen()) + " health\n";
			}
			else if (team1LeadType == MonsterType::GoblinType && team2LeadType == MonsterType::OrcType) {
				for (int i = 0; i < (*Team1).getLeadMonster()->getNumOfAttacks(); i++) {
					turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage, dealing " + to_string(Team1->getLeadMonster()->attack() - Team2->getLeadMonster()->getDamageBlock()) + " damage, and receiving " + to_string(Team2->getLeadMonster()->getDamageReflected()) + " reflected damage\n";
					(*Team2).getLeadMonster()->decreaseHealth(Team1->getLeadMonster()->attack() - Team2->getLeadMonster()->getDamageBlock());
					(*Team1).getLeadMonster()->decreaseHealth(Team2->getLeadMonster()->getDamageReflected());
				}
				(*Team1).getLeadMonster()->decreaseHealth((*Team2).getLeadMonster()->attack());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage\n";
			}
			else if (team1LeadType == MonsterType::GoblinType && team2LeadType == MonsterType::GoblinType) {
				for (int i = 0; i < (*Team1).getLeadMonster()->getNumOfAttacks(); i++) {
					turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";
					(*Team2).getLeadMonster()->decreaseHealth((*Team1).getLeadMonster()->attack());
				}
				for (int i = 0; i < (*Team2).getLeadMonster()->getNumOfAttacks(); i++) {
					turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";
					(*Team1).getLeadMonster()->decreaseHealth((*Team2).getLeadMonster()->attack());
				}
			}
			else if (team1LeadType == MonsterType::TrollType && team2LeadType == MonsterType::GoblinType) {
				(*Team2).getLeadMonster()->decreaseHealth((*Team1).getLeadMonster()->attack());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";

				for (int i = 0; i < (*Team2).getLeadMonster()->getNumOfAttacks(); i++) {
					turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage\n";
					(*Team1).getLeadMonster()->decreaseHealth((*Team2).getLeadMonster()->attack());
				}
				(*Team1).getLeadMonster()->increaseHealth(Team1->getLeadMonster()->getHealthRegen());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " regenerates " + to_string(Team1->getLeadMonster()->getHealthRegen()) + " health\n";
			}
			else if (team1LeadType == MonsterType::TrollType && team2LeadType == MonsterType::OrcType) {
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage, dealing " + to_string(Team1->getLeadMonster()->attack() - Team2->getLeadMonster()->getDamageBlock()) + " damage, and receiving " + to_string(Team2->getLeadMonster()->getDamageReflected()) + " reflected damage\n";
				(*Team2).getLeadMonster()->decreaseHealth(Team1->getLeadMonster()->attack() - Team2->getLeadMonster()->getDamageBlock());
				(*Team1).getLeadMonster()->decreaseHealth(Team2->getLeadMonster()->getDamageReflected());

				(*Team1).getLeadMonster()->decreaseHealth((*Team2).getLeadMonster()->attack());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage\n";
				(*Team1).getLeadMonster()->increaseHealth(Team1->getLeadMonster()->getHealthRegen());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " regenerates " + to_string(Team1->getLeadMonster()->getHealthRegen()) + " health\n";
			}
			else if (team1LeadType == MonsterType::TrollType && team2LeadType == MonsterType::TrollType) {
				(*Team2).getLeadMonster()->decreaseHealth((*Team1).getLeadMonster()->attack());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";
				(*Team1).getLeadMonster()->decreaseHealth((*Team2).getLeadMonster()->attack());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage\n";
				(*Team1).getLeadMonster()->increaseHealth(Team1->getLeadMonster()->getHealthRegen());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " regenerates " + to_string(Team1->getLeadMonster()->getHealthRegen()) + " health\n";
				(*Team2).getLeadMonster()->increaseHealth(Team2->getLeadMonster()->getHealthRegen());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " regenerates " + to_string(Team2->getLeadMonster()->getHealthRegen()) + " health\n";
			}
			else if (team1LeadType == MonsterType::OrcType && team2LeadType == MonsterType::GoblinType) {
				(*Team2).getLeadMonster()->decreaseHealth((*Team1).getLeadMonster()->attack());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";

				for (int i = 0; i < (*Team2).getLeadMonster()->getNumOfAttacks(); i++) {
					turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage, dealing " + to_string(Team2->getLeadMonster()->attack() - Team1->getLeadMonster()->getDamageBlock()) + " damage, and receiving " + to_string(Team1->getLeadMonster()->getDamageReflected()) + " reflected damage\n";
					(*Team1).getLeadMonster()->decreaseHealth(Team2->getLeadMonster()->attack() - Team1->getLeadMonster()->getDamageBlock());
					(*Team2).getLeadMonster()->decreaseHealth(Team1->getLeadMonster()->getDamageReflected());
				}

			}
			else if (team1LeadType == MonsterType::OrcType && team2LeadType == MonsterType::TrollType) {
				(*Team2).getLeadMonster()->decreaseHealth((*Team1).getLeadMonster()->attack());
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage\n";

				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage, dealing " + to_string(Team2->getLeadMonster()->attack() - Team1->getLeadMonster()->getDamageBlock()) + " damage, and receiving " + to_string(Team1->getLeadMonster()->getDamageReflected()) + " reflected damage\n";
				(*Team1).getLeadMonster()->decreaseHealth(Team2->getLeadMonster()->attack() - Team1->getLeadMonster()->getDamageBlock());
				(*Team2).getLeadMonster()->decreaseHealth(Team1->getLeadMonster()->getDamageReflected());
				(*Team2).getLeadMonster()->increaseHealth(Team2->getLeadMonster()->getHealthRegen());
				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " regenerates " + to_string(Team2->getLeadMonster()->getHealthRegen()) + " health\n";
			}
			else if (team1LeadType == MonsterType::OrcType && team2LeadType == MonsterType::OrcType) {
				turn += Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " attacks " + Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " for " + to_string(Team1->getLeadMonster()->attack()) + " damage, dealing " + to_string(Team1->getLeadMonster()->attack() - Team2->getLeadMonster()->getDamageBlock()) + " damage, and receiving " + to_string(Team2->getLeadMonster()->getDamageReflected()) + " reflected damage\n";
				(*Team2).getLeadMonster()->decreaseHealth(Team1->getLeadMonster()->attack() - Team2->getLeadMonster()->getDamageBlock());
				(*Team1).getLeadMonster()->decreaseHealth(Team2->getLeadMonster()->getDamageReflected());

				turn += Team2->getTeamName() + " " + Team2->getLeadMonster()->listName() + " attacks " + Team1->getTeamName() + " " + Team1->getLeadMonster()->listName() + " for " + to_string(Team2->getLeadMonster()->attack()) + " damage, dealing " + to_string(Team2->getLeadMonster()->attack() - Team1->getLeadMonster()->getDamageBlock()) + " damage, and receiving " + to_string(Team1->getLeadMonster()->getDamageReflected()) + " reflected damage\n";
				(*Team1).getLeadMonster()->decreaseHealth(Team2->getLeadMonster()->attack() - Team1->getLeadMonster()->getDamageBlock());
				(*Team2).getLeadMonster()->decreaseHealth(Team1->getLeadMonster()->getDamageReflected());
			}

			if ((*Team1).getLeadMonster()->checkHealth() <= 0) {
				turn += Team1->getTeamName() + " " + (*Team1).getLeadMonster()->listName() + " has died\n";
				Team1->removeLeadMonster();
			}
			if ((*Team2).getLeadMonster()->checkHealth() <= 0) {
				turn += Team2->getTeamName() + " " + (*Team2).getLeadMonster()->listName() + " has died\n";
				Team2->removeLeadMonster();
			}

			if ((*Team1).getLeadMonster() == NULL && (*Team2).getLeadMonster() == NULL) {
				GameOver = true;
				turn += "\nBattle over. It's a tie!\n\n";
				turn += printTeams();
			}
			else if ((*Team1).getLeadMonster() == NULL) {
				GameOver = true;
				turn += "\nBattle over. " + (*Team2).getTeamName() + " team wins!\n\n";
				turn += printTeams();
			}
			else if ((*Team2).getLeadMonster() == NULL) {
				GameOver = true;
				turn += "\nBattle over. " + (*Team1).getTeamName() + " team wins!\n\n";
				turn += printTeams();
			}

			turn += "\n";
			Turn++;
		} else {
			turn += "Battle has already concluded.\n";
		}
		return turn;
	}
};

int main()
{
	// Monsters
	Troll* troll1 = new Troll();
	Troll* troll2 = new Troll();
	Orc* orc1 = new Orc();
	Orc* orc2 = new Orc();
	Goblin* goblin1 = new Goblin();
	Goblin* goblin2 = new Goblin();

	// Teams
	Team team1 = Team("Monster Squad");
	Team team2 = Team("Scary Crew");

	// Game
	Battle game = Battle(&team1, &team2);	
	
	// Game 1: Goblin vs. Troll
	team1.addMonster(goblin1);
	team2.addMonster(troll1);
	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	cout << game.resetGame() << endl;

	// Game 2: Goblin vs. 2 Trolls
	team2.addMonster(troll2);
	game.clearGame(&team1, &team2);
	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	cout << game.resetGame() << endl;

	// Game 3: Troll vs. Orc
	team1.clearTeam();
	team2.clearTeam();
	team1.addMonster(troll1);
	team2.addMonster(orc1);
	game.clearGame(&team1, &team2);
	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	cout << game.resetGame() << endl;

	// Game 4: Troll vs. 2 Orcs
	team2.addMonster(orc2);
	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	cout << game.resetGame() << endl;

	// Game 5: Orc vs. Goblin
	team1.clearTeam();
	team2.clearTeam();
	team1.addMonster(orc1);
	team2.addMonster(goblin1);
	game.clearGame(&team1, &team2);
	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	cout << game.resetGame() << endl;

	// Game 6: Orc vs. 2 Goblins
	team2.addMonster(goblin2);
	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	cout << game.resetGame() << endl;

	// Game 7: 4 Random Monster vs. 4 Random Monsters
	team1.clearTeam();
	team2.clearTeam();

	// generate random monster teams
	srand(time(0));
	int randMonster;
	for (int i = 0; i < 4; i++) {
		randMonster = rand() % 3;
		if (randMonster == 0) {
			team1.addMonster(new Goblin());
		}
		else if (randMonster == 1) {
			team1.addMonster(new Troll());
		}
		else if (randMonster == 2) {
			team1.addMonster(new Orc());
		}
	}
	for (int i = 0; i < 4; i++) {
		randMonster = rand() % 3;
		if (randMonster == 0) {
			team2.addMonster(new Goblin());
		}
		else if (randMonster == 1) {
			team2.addMonster(new Troll());
		}
		else if (randMonster == 2) {
			team2.addMonster(new Orc());
		}
	}

	cout << game.printBattleStart();
	while (!game.isGameOver()) {
		cout << game.performTurn();
	}

	return 0;
}
