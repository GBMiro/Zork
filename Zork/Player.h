#pragma once
#include "Creature.h"
#include <vector>

class Player : public Creature
{
public:
	Player(string name,string description, int HP, int damage, int defense);
	~Player();

	void showDescription(const vector<string>& obj);
	void go(const vector<string>& dir);
	void take(const vector<string>& object);
	void drop(const vector<string>& object);
	void open(const vector<string>& action);
	void close(const vector<string>& action);
	void attack(const vector<string>& action);
	void equip(const vector<string>& action);
	void unEquip(const vector<string>& action);
	void loot(const vector<string>& action);
	void drink(const vector<string>& action);

	int getTotalDamage() const;
	int getTotalDefense() const;

	void update();

	void talkNPC(const vector<string>& action);
	void answerNPC(const vector<string>& action);

	void showInventory();
	void showStats(const vector<string>& action) const;

public:
	Item* weaponEquipped;
	Item* armorEquipped;

};


