#pragma once
#include "Creature.h"
#include <vector>

class Player : public Creature
{
public:
	Player(const string& name, const string& description, int HP, int damage, int defense);
	~Player();

	void showDescription(const vector<string>& action) const;
	void go(const vector<string>& action);
	void take(const vector<string>& action);
	void drop(const vector<string>& action);
	void unLock(const vector<string>& action);
	void lock(const vector<string>& action);
	void attack(const vector<string>& action);
	void equip(const vector<string>& action);
	void unEquip(const vector<string>& action);
	void loot(const vector<string>& action);
	void drink(const vector<string>& action);

	int getTotalDamage() const;
	int getTotalDefense() const;

	void update();

	void talkNPC(const vector<string>& action) const;
	void answerNPC(const vector<string>& action);

	void showInventory() const;
	void showStats(const vector<string>& action) const;

	void showHelp() const;

public:
	Item* weaponEquipped;
	Item* armorEquipped;
	bool victory;

};


