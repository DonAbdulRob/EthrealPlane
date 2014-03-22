#ifndef _FILEITEMS_H_
#define _FILEITEMS_H_

#include <string>
using namespace std;

class Item;
class ConsumableInventory;
class EquipmentInventory;
class QuestInventory;
class JunkInventory;

class AllInventories
{
protected:
	ConsumableInventory *fiConsumables_;
	EquipmentInventory *fiEquipment_;
	QuestInventory *fiQuestItems_;
	JunkInventory *fiJunkItems_;

public:
	AllInventories();

	ConsumableInventory *getConsumableInvnentory() {return fiConsumables_;}
	EquipmentInventory *getEquipmentInventory() {return fiEquipment_;}
	QuestInventory *getQuestInventory() {return fiQuestItems_;}
	JunkInventory *getJunkInventory() {return fiJunkItems_;}
};

class FileItems : public AllInventories
{
protected:
	string fileLocation;

public:
	FileItems();

	void readAll();
	void readWeapons();
	void readShields();
	void readBodyArmors();
	void readLegArmors();
	void readRings();
	void readNecklaces();
};

#endif


