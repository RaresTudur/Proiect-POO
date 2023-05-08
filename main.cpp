#include <iostream>
#include <climits>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;



// Attack functions

int calculate_attack_ability(int damage_ability,int protection)
{
    float damage_multiplier = 0.2;
    if (rand() % 100 < 10)
    {
        damage_multiplier = 0.4;
    }
    else if (rand() % 100 < 7)
    {
        return 0;
    }
    int dmg_ability = int(damage_ability * damage_multiplier) - protection;
    return dmg_ability > 0 ? dmg_ability : 0;
}

class Mob
{
    double health;
    int protection;
    int magic_protection;
    int damage;
public:
    Mob():health(0),damage(0),protection(0),magic_protection(0){}
    Mob(int hp,int dmg): health(hp),damage(dmg),protection(0),magic_protection(0){}
    Mob(int hp,int dmg,int prot,int magic_prot): health(hp),damage(dmg),protection(prot),magic_protection(magic_prot){}
    int get_hp() const;
    int get_dmg() const;
    int get_protection() const;
    int get_magic_protection() const;
    void modify_health(const double &value);
};

void Mob::modify_health(const double &value)
{
    this->health = value;
}

int Mob::get_hp() const
{
    return this->health;
}

int Mob::get_dmg() const
{
    return this->damage;
}

int Mob::get_protection() const
{
    return this->protection;
}

int Mob::get_magic_protection() const
{
    return this->magic_protection;
}

string enter_name()
{
    cout << "Enter your character's name\n";
    string nume;
    cin >> ws >> nume;
    return nume;
}

class Item {
public:
    virtual ~Item() = 0;
    virtual string getName() const = 0;
    virtual string getDescription() const = 0;
    virtual string requiredClass() const = 0;
};

Item::~Item()
{}

class Inventory {
    
    static int MAX_CAPACITY;
protected:
    vector <Item*> items;

public:
    int get_size() const;
    Item* getItem(int poz);
    vector <Item*> getitems();
    bool add_item(Item* item);
    bool remove_item(Item* item);
};

int Inventory::MAX_CAPACITY = 10;

vector <Item*> Inventory::getitems()
{
    return this->items;
}

Item* Inventory::getItem(int poz)
{
    if (poz < 0 || poz >= items.size())
    {
            return nullptr;
    }
    return this->items[poz];
}

int Inventory::get_size() const
{
    return this->MAX_CAPACITY;
}

bool Inventory::add_item(Item* item)
{
    if (this->items.size() < this->MAX_CAPACITY)
    {
        this->items.push_back(item);
        return true;
    }
    else
    {
        cout << "Inventory is full\n";
        return false;
    }
}

bool Inventory::remove_item(Item* item)
{
    auto it = find(this->items.begin(), this->items.end(), item);
    if (it != this->items.end())
    {
        this->items.erase(it);
        return true;
    }
    return false;
}



class Ability
{
    string ability_name;
    int damage;
public:
    Ability();
    Ability(const string name,int dmg);
    string get_name() const
    {
        return this->ability_name;
    }
    int get_damage() const
    {
        return this->damage;
    }
    void setdmg(const int dmg = 0)
    {
        this->damage = dmg;
    }
    void setname(const char* &name)
    {
        this->ability_name = name;
    }
    void setname(const string &name)
    {
        this->ability_name = name;
    }
    friend ostream & operator << (ostream &out, const Ability &x);
    friend istream & operator >> (istream &in, Ability &x);
    friend ifstream & operator >> (ifstream &input, Ability &x);
    ~Ability() = default;
};

ostream & operator <<(ostream &out,const Ability &x)
{
    out << x.ability_name << " " << x.damage << "\n";
    return out;
}

istream & operator >> (istream &in, Ability &x)
{
    cout << "Enter your ability's name\n";
    cin >> ws >> x.ability_name;
    cout << "Enter your ability's damage\n";
    while (!(cin >> x.damage) || x.damage < 1 || x.damage > INT_MAX)
    {
        cout << "Invalid input. The ability's damage must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter your ability's damage\n";
    }
    return in;
}

ifstream & operator >> (ifstream &input, Ability &x)
{
    input >> ws >> x.ability_name;
    input >> x.damage;
    return input;
}

Ability::Ability()
{
    this->ability_name = "Simple";
    this->damage = 0;
}

Ability::Ability(const string name,int dmg)
{
    this->ability_name = name;
    this->damage = dmg;
}

class Armor: public Item
{
    string armor_name;
    string description;
    int armor_value;
    string requiredclass;
public:
    Armor(string name = "", string description = "",int value = 0, string rC = ""): armor_name(name),description(description),armor_value(value),requiredclass(rC){}
    string getName() const override;
    int get_armor_value() const;
    string getDescription() const override;
    string requiredClass() const override;
    friend ostream & operator << (ostream &out, const Armor &x);
    friend ofstream & operator << (ofstream &output, const Armor &x);
    friend istream & operator >> (istream &in, Armor &x);
    friend ifstream & operator >> (ifstream &input, Armor &x);
    virtual ~Armor() override = default;
};

string Armor::getDescription() const
{
    return this->description;
}

string Armor::requiredClass() const
{
    return this->requiredclass;
}

string Armor::getName() const
{
    return this->armor_name;
}

int Armor::get_armor_value() const
{
    return this->armor_value;
}

ostream & operator << (ostream &out, const Armor &x)
{
    out << "The name and the armor value of your armor is\n";
    out << x.armor_name << " " << x.armor_value << "\n";
    return out;
}
ofstream & operator << (ofstream &output, const Armor &x)
{
    output << x.armor_name.c_str() << " " << x.armor_value << "\n";
    return output;
}

istream & operator >> (istream &in, Armor &x)
{
    cout << "Enter the name of your armor\n";
    in >> ws >> x.armor_name;
    cout << "Enter the defensive value of your armor\n";
    while (!(in >> x.armor_value) || x.armor_value < 1 || x.armor_value > INT_MAX)
    {
        cout << "Invalid input. The defensive value of your armor must be a positive integer between 1 and 40000." << "\n";
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "Enter the defensive value of your armor\n";
    }
    return in;
}

ifstream & operator >> (ifstream &input, Armor &x)
{
    input >> ws >> x.armor_name;
    input >> ws >> x.armor_value;
    return input;
}

class Weapon :public Item
{
    string name_weapon;
    string description;
    int attack;
    string reqClass;
public:
    Weapon(string name = "", string description = "", int atk = 0, string rC = ""): name_weapon(name),description(description),attack(atk),reqClass(rC){}
    string getName() const override
    {
            return this->name_weapon;
    }
    int get_attack_value() const;
    string getDescription() const override;
    string requiredClass() const override;
    friend ostream & operator << (ostream &out, const Weapon &x);
    friend ofstream & operator << (ofstream &output, const Weapon &x);
    friend istream & operator >> (istream &in, Weapon &x);
    friend ifstream & operator >> (ifstream &input, Weapon &x);
    ~Weapon() override = default;
};

string Weapon::getDescription() const
{
    return this->description;
}

string Weapon::requiredClass() const
{
    return this->reqClass;
}

ostream & operator << (ostream &out, const Weapon &x)
{
    out << "The name and the attack of your weapon is\n";
    out << x.name_weapon << " " << x.description << " " << x.attack << " " << x.requiredClass() << "\n";
    return out;
}

ofstream & operator << (ofstream &output, const Weapon &x)
{
    output << x.name_weapon.c_str() << " " << x.attack << "\n";
    return output;
}


istream & operator >> (istream &in, Weapon &x)
{
    cout << "Enter the name of your weapon\n";
    cin >> ws >> x.name_weapon;
    cout << "Enter the attack of your weapon\n";
    while (!(cin >> x.attack) || x.attack < 1 || x.attack > INT_MAX)
    {
        cout << "Invalid input. The attack of your weapon must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the attack of your weapon\n";
    }
    return in;
}

ifstream & operator >> (ifstream &input, Weapon &x)
{
    input >> ws >> x.name_weapon;
    input >> ws >> x.attack;
    return input;
}


int Weapon::get_attack_value() const
{
    return this->attack;
}

class Player
{
    int health,defense,magic,strength,speed,intelligence;
    string name;
    Weapon weapon;
    Inventory inventory;
    int num_abilities;
    Ability *abilities;
public:
    Player():name(""),health(0),defense(0),magic(0),strength(0),speed(0),intelligence(0),weapon(),num_abilities(1)
    {
        this->abilities = new Ability[num_abilities];
        add_ability(0, "Basic",0);
    }
    Player(const string nume,const int& hp,const int & df,const int& Mp,const int& St,const int& Sp,const int& It, const char* name_weapon, string description,int atk,int num_ab):name(nume),health(hp),magic(Mp),strength(St),speed(Sp),intelligence(It),weapon(name_weapon,description,atk),num_abilities(num_ab)
    {
        if (num_abilities <= 0)
        {
            cout << "Invalid number of abilities.\n";
            return;
        }
        this->abilities = new Ability[num_abilities];
    }
    string get_mume() const;
    int get_hp() const;
    int get_defense() const;
    int get_magic() const;
    int get_strength() const;
    int get_speed() const;
    int get_intelligence() const;
    int get_number_of_abilities() const;
    Inventory getInventory() const;
    Ability get_ability(int index) const;
    void set_name(const char name[]);
    void set_magic(const int& magic = 0);
    void set_hp(const int& hp = 0);
    void set_defense(const int& defense = 0);
    void set_strength(const int& strength = 0);
    void set_intelligence(const int& intelligence = 0);
    void set_speed(const int& speed = 0);
    void set_num_abilities(const int num);
    void add_ability(const int index,const char* name,const int damage);
    friend ostream & operator << (ostream &out, const Player &x);
    friend ofstream & operator << (ofstream &output, const Player &x);
    friend istream & operator >> (istream &in,  Player &x);
    friend ifstream& operator>>(ifstream& input, Player &x);
    ~Player()
    {
        int Size_inv = inventory.get_size();
        for (int i = 0; i < Size_inv; i++)
        {
            Item* item = inventory.getItem(i); // reference to the pointer so no new item
            if(item != nullptr)
            {
                delete item;
            }
        }
        if(abilities != nullptr)
        {
            delete [] abilities;
        }
    }
};

void Player::add_ability(const int index, const char* name, const int damage)
{
    if(abilities != nullptr)
    {
        abilities[index].setname(name);
        abilities[index].setdmg(damage);
    }
}

ofstream & operator << (ofstream &output, const Player &x)
{
    output << x.name.c_str() << "\n";
    output << x.health << "\n";
    output << x.defense << "\n";
    output << x.strength << "\n";
    output << x.magic << "\n";
    output << x.speed << "\n";
    output << x.intelligence << "\n";
    output << x.weapon;
    output << x.num_abilities << "\n";
    for(int i = 0; i < x.num_abilities; i++)
    {
        output << x.abilities[i];
    }
    return output;

}

ostream & operator << (ostream &out, const Player &x)
{
    out << "Name: " << x.name << "\n";
    out << "Health: " << x.health << "\n";
    out << "Defense: " << x.defense << "\n";
    out << "Strength: " << x.strength << "\n";
    out << "Magic Damage: " << x.magic << "\n";
    out << "Speed: " << x.speed << "\n";
    out << "Intelligence: " << x.intelligence << "\n";
    out << x.weapon;
    out << "Number of abilities: " << x.num_abilities << "\n";
    out << "The name and damage of each ability : \n";
    for(int i = 0; i < x.num_abilities; i++)
    {
        cout << x.abilities[i];
    }
    out << "Items in inventory:\n";
    for(auto item: x.getInventory().getitems())
    {
        out << item << "\n";
    }
    return out;
}
istream & operator >> (istream &cin,  Player &x)
{
    cout << "Enter this values for your character\n";
    cout << "Enter the name of your character\n";
    getline (cin, x.name);
    cout << "Enter the health of your character\n";
    while (!(cin >> x.health) || x.health < 1 || x.health > INT_MAX)
    {
        cout << "Invalid input. Health must be a positive integer between 1 and 1000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the health of your character\n";
    }
    cout << "Enter the defense of your character\n";
    while (!(cin >> x.defense) || x.defense < 1 || x.defense > INT_MAX)
    {
        cout << "Invalid input. Defense must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the defense of your character\n";
    }
    cout << "Enter the magic of your character\n";
    while (!(cin >> x.magic) || x.magic < 1 || x.magic > INT_MAX)
    {
        cout << "Invalid input. Magic must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the magic of your character\n";
    }
    cout << "Enter the speed of your character\n";
    while (!(cin >> x.speed) || x.speed < 1 || x.speed > INT_MAX) {
        cout << "Invalid input. Speed must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the speed of your character\n";
    }
    cout << "Enter the strength of your character\n";
    while (!(cin >> x.strength) || x.strength < 1 || x.strength > INT_MAX)
    {
        cout << "Invalid input. Strength must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the strength of your character\n";
    }
    cout << "Enter the intelligence of your character\n";
    while (!(cin >> x.intelligence) || x.intelligence < 1 || x.intelligence > INT_MAX)
    {
        cout << "Invalid input. Intelligence must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the intelligence of your character\n";
    }
    cout << "Enter the weapon of your character\n";
    cin >> x.weapon;
    cout << "Enter the number of abilities your character has\n";
    while (!(cin >> x.num_abilities) || x.num_abilities < 1 || x.num_abilities > INT_MAX)
    {
        cout << "Invalid input. The number of abilities must be a positive integer between 1 and 40000." << "\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter the number of abilities your character has\n";
    }
    if(x.abilities != nullptr)
    {
        delete [] x.abilities;
    }
    x.abilities = new Ability[x.num_abilities];
    for(int i = 0; i < x.num_abilities; i++)
    {
        cin >> x.abilities[i];
    }
    return cin;
}

ifstream& operator>>(ifstream& input, Player &x)
{
    getline(input,x.name);
    cout << x.name;
    input >> x.health;
    cout << x.health;
    input >> x.defense;
    input >> x.magic;
    input >> x.speed;
    input >> x.strength;
    input >> x.intelligence;
    input >> x.weapon;
    input >> x.num_abilities;
    if(x.abilities != nullptr)
    {
        delete [] x.abilities;
    }
    x.abilities = new Ability[x.num_abilities];
    for(int i = 0; i < x.num_abilities; i++)
    {
        input >> x.abilities[i];
    }
    return input;
}


void Player::set_name(const char name[])
{
    this->name = name;
}

void Player::set_hp(const int &hp)
{
    this->health = hp;
}

void Player::set_magic(const int &magic)
{
    this->magic = magic;
}

void Player::set_speed(const int &speed)
{
    this->speed = speed;
}

void Player::set_defense(const int &defense)
{
    this->defense = defense;
}

void Player::set_intelligence(const int& intelligence)
{
    this->intelligence = intelligence;
}

void Player::set_num_abilities(const int num)
{
    if(num < this->num_abilities)
    {
        return;
    }
    if(this->abilities != nullptr)
    {
        Ability *temp = new Ability[num];
        for(int i = 0; i < this->num_abilities; i++)
        {
            temp[i].setdmg(this->abilities[i].get_damage());
            temp[i].setname(this->abilities[i].get_name());
        }
        delete [] abilities;
        abilities = new Ability[num];
        for(int i = 0; i < this->num_abilities; i++)
        {
            abilities[i].setdmg(temp[i].get_damage());
            abilities[i].setname(temp[i].get_name());
        }
    }
    else
    {
        abilities = new Ability[num];
    }
}

int Player::get_hp() const
{
    return this->health;
}
int Player::get_defense() const
{
    return this->defense;
}
string Player::get_mume() const
{
    return this->name;
}
int Player::get_magic() const
{
    return this->magic;
}
int Player::get_strength() const
{
    return this->strength;
}
int Player::get_speed() const
{
    return this->speed;
}
int Player::get_intelligence() const
{
    return this->intelligence;
}

int Player::get_number_of_abilities() const
{
    return this->num_abilities;
}

Inventory Player::getInventory() const
{
    return this->inventory;
}

Ability Player::get_ability(int index) const
{
    if(this->abilities == nullptr)
    {
        return Ability();
    }
    if(index > num_abilities)
    {
        cout << "Index greater than number of abilities\n";
        return abilities[num_abilities];
    }
    return this->abilities[index];
}


class Warrior: public Player
{
public:
    Warrior(const string name = "John Doe"):Player(name,150,10, 0, 10, 5, 2,"Bronze Sword","Sword made out of bronze ",10,1)
    {
        add_ability(0, "Strong Attack", 300);
    }
    ~Warrior() = default;
};

class Mage: public Player
{
public:
    Mage(const string name = "John Doe"):Player(name, 100, 5,150,2, 5, 15,"Wooden Staff","Stuff made out of wood",8,1)
    {
        add_ability(0, "Fireball", 300);
    }
    ~Mage() = default;
};


class Rogue: public Player
{
public:
    Rogue(const string name = "John Doe"):Player(name, 125,7,50,8, 10, 10,"Iron Dagger","Dagger made out of iron",7,1)
    {
        add_ability(0, "The dagger cut", 250);
    }
    ~Rogue() = default;
};

class Cleric: public Player
{
public:
    Cleric(const string name = "John Doe"):Player(name, 125,8,125,5, 5,12,"Wooden Mace","Mace made out of wood",9,1)
    {
        add_ability(0, "The Spirit of Justice", 350);
    }
    ~Cleric() = default;
};

class Orc: public Player
{
public:
    Orc(const string name = "John Doe"):Player(name, 200,12,0,15,10,2,"Stone Axe","Axe made out of stone",11,1)
    {
        add_ability(0, "Strong Attack", 400);
    }
    ~Orc() = default;
};

class CreateMenu {
public:
    static bool display_load()
    {
        cout << "====== Yow want to load or create a new character? ======\n";
        cout << "1. Yes, I want to load a character.\n";
        cout << "2. No, I want to create a new character.\n";
        int option;
        cin >> option;
        if (option == 1)
        {
            return true;
        }
        return false;
    }
    void display_class();
    bool return_display();
    
};

void CreateMenu::display_class()
{
    cout << "====== Choose Your Class ======\n";
    cout << "1. Warrior\n";
    cout << "2. Mage\n";
    cout << "3. Rogue\n";
    cout << "4. Cleric\n";
    cout << "5. Orc\n";
    cout << "6. Independent Character\n";
    cout << "7. Exit\n";
}

bool CreateMenu::return_display()
{
    int option;
    cout << "You want to create other character?\n";
    cout << "0.No.\n";
    cout << "1.Yes.\n";
    cin >> option;
    if(option == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void save_game(Player &x,string filename)
{
    ofstream fout(filename,ios::trunc);
    if (fout.fail())
    {
        cout << "Error: could not open file " << "\n";
        return;
    }
    fout << x;
    cout << "Character saved successfully from " << "\n";
}

void load_game(Player &x, string filename)
{
    ifstream fin(filename,ios::app);
    cout << fin.getloc().name();
    if (fin.fail())
    {
        cout << "Error: could not open file " << "\n";
        return;
    }
    fin >> x;
    fin.close();
    cout << "Game loaded successfully from " << "\n";
}


class Shop: public Inventory
{
    static int Max_capacity;
public:
    Shop(int capacity = 30);
    bool add_item(Item* item);
    friend ostream & operator << (ostream &out, Shop& s);
    ~Shop();
};

int Shop::Max_capacity = 30;

Shop::Shop(int capacity)
{
    Max_capacity = capacity;
}

bool Shop::add_item(Item* item)
{
    if (this->items.size() < this->Max_capacity) {
        this->items.push_back(item);
        return true;
    } else {
        cout << "Shop inventory is full\n";
        return false;
    }
}


ostream & operator << (ostream &out, Shop& s)
{
    for (int i = 0; i < s.items.size(); i++)
    {
        cout << i+1 << ". " <<  s.items[i]->getName() << " - " << s.items[i]->getDescription() << " - " << s.items[i]->requiredClass() << "\n";
        if (dynamic_cast<Weapon*>(s.items[i]) != nullptr)
        {
            cout << "Attack: " << dynamic_cast<Weapon*>(s.items[i])->get_attack_value() << "\n";
        }
        else if (dynamic_cast<Armor*>(s.items[i])!= nullptr) {
            cout << "Defense: " << dynamic_cast<Armor*>(s.items[i])->get_armor_value() << "\n";
        }
    }
    return out;
}

Shop::~Shop()
{
    for(auto item : items)
    {
        if(item != nullptr)
        {
            delete item;
        }
    }
}


class Game
{
    Shop s;
    void initializate_shop();
    void generate_monsters();
public:
    void game_itself(Player &x);
};

void Game::initializate_shop()
{
    s.add_item(new Armor("Chainmail of the Knight", "A sturdy chainmail that increases the defense of knights by 10 points",10,"Warrior"));
    s.add_item(new Armor("Robe of the Enchanter","A mystical robe that increases the magic power of enchanters by 8 points.",8,"Mage"));
    s.add_item(new Armor("Leather Armor of the Scout","A light armor that increases the defense of scouts by 7 points.",7,"Rogue"));
    s.add_item(new Armor("Plate Armor of the Crusader","A heavy plate armor that increases the defense of orcs by 12 points",12,"Orc"));
    s.add_item(new Armor("Helm of the Guardian","A heavy helm that increases the defense of spiritual guardians by 11 points",11,"Cleric"));
    s.add_item(new Armor("Greaves of the God","Heavy greaves that increase the defense of Clerics by 12 points",12,"Cleric"));
    s.add_item(new Weapon("Sword of the Lost King", "A powerful sword that increases the attack of warriors by 10 points.", 10, "Warrior"));
    s.add_item(new Weapon("Shield of the Crusader", "A sturdy shield that increases the defense of paladins by 8 points.", 8, "Cleric"));
    s.add_item(new Weapon("Staff of the Archmage", "A mystical staff that increases the magic power of mages by 12 points.", 12, "Mage"));
    s.add_item(new Weapon("Bow of the Silent Hunter", "A silent bow that increases the attack of rangers by 9 points.", 9, "Rogue"));
    s.add_item(new Weapon("Dagger of the Shadow Assassin", "A sharp dagger that increases the attack of rogues by 8 points.", 8, "Rogue"));
    s.add_item(new Weapon("Spear of the Swift Lancer", "A long spear that increases the attack of dragoons by 11 points.", 11, "Warrior"));
    s.add_item(new Weapon("Axe of the Mighty Berserker", "A heavy axe that increases the attack of berserkers by 12 points.", 12, "Warrior"));
    s.add_item(new Weapon("Mace of the Divine Hammer", "A divine mace that increases the attack of clerics by 7 points.", 7, "Orc"));
    s.add_item(new Weapon("Wand of the Arcane Weaver", "A magical wand that increases the magic power of wizards by 10 points.", 10, "Mage"));

}

void loading_bar()
{
    int width = 50;
    cout << setw(width/2) << right << "Loading..." << endl;
    cout << "[" << setw(width) << left << "" << "]" << endl;
    cout << "[" << flush;

    for (int i = 0; i < width; i++)
    {
        cout << "#" << flush;
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    cout << "]" << endl;
    cout << setw(width/2) << right << "Done!" << endl;
}

int calculate_attack_damage(int character_damage,int mob_damage_protection) {
    float damage_multiplier = 0.8;
    if (rand() % 100 < 10)
    {
        damage_multiplier = 1.5;
    }
    else if (rand() % 100 < 5)
    {
        return 0;
    }
    int attack_damage = (int)(character_damage * damage_multiplier) - mob_damage_protection;
    return attack_damage > 0 ? attack_damage : 0;
}
int calculate_attack_damage_mob(int character_protection,int mob_damage) {
    float damage_multiplier = 0.1;
    if (rand() % 100 < 10)
    {
        damage_multiplier = 0.3;
    }
    else if (rand() % 100 < 5)
    {
        return 0;
    }
    int attack_damage = (int)(mob_damage * damage_multiplier) - character_protection;
    return attack_damage > 0 ? attack_damage : 0;
}


void Game::game_itself(Player &x)
{
    loading_bar();
    this->initializate_shop();
    cout << this->s;
    Mob Giant(100,100,70,50);
    cout << "You are face to face with a giant?\n";
    cout << "How you attack?\n";
    while(x.get_hp() > 0 && Giant.get_hp() > 0)
    {
        cout << "1.Normal Damage using your weapon\n";
        cout << "2.Use one of your abilities\n";
        cout << "3.Check your stats\n";
        cout << "4.Save your character\n";
        int option;
        cin >> option;
        if (option == 1)
        {
            int damage = calculate_attack_damage(x.get_strength(),0);
            if (damage == 0)
            {
                cout << "You missed the target." << "\n";
            }
            else {
                cout << "You deal " << damage << " damage to the enemy." << "\n";
                double new_hp = Giant.get_hp() - damage;
                Giant.modify_health(new_hp);
                cout << "Now Giant's health is : " << Giant.get_hp() << "\n";
            }
            damage = calculate_attack_damage_mob(x.get_defense(),Giant.get_dmg());
            if (damage == 0)
            {
                cout << "The enemy missed you." << "\n";
            }
            else {
                cout << "The enemy deal " << damage << " damage to the you." << "\n";
                double new_hp = x.get_hp() - damage;
                x.set_hp(new_hp);
                cout << "Your health now is " << x.get_hp() << "\n";
            }
        }
        else if(option == 2)
        {
            cout << "Which one of your abilities you want to use?\n";
            int num_abilities = x.get_number_of_abilities();
            for(int i = 0; i < num_abilities; i++)
            {
                cout << i+1 << "." << x.get_ability(i);
            }
            cout << num_abilities + 1 << "." << "Return to the damage menu\n";
            int option_ability;
            cin >> option_ability;
            if(option_ability != num_abilities + 1)
            {
                double damage = calculate_attack_ability(x.get_ability(option_ability-1).get_damage(), Giant.get_protection());
                if(damage == 0)
                {
                    cout << "You missed the target." << "\n";
                }
                else
                {
                    cout << "You deal " << damage << " damage to the enemy." << "\n";
                    double new_hp = Giant.get_hp() - damage;
                    Giant.modify_health(new_hp);
                    cout << "Now Giant's health is : " << Giant.get_hp() << "\n";
                }
                damage = calculate_attack_damage_mob(x.get_defense(),Giant.get_dmg());
                if (damage == 0)
                {
                    cout << "The enemy missed you." << "\n";
                }
                else {
                    cout << "The enemy deal " << damage << " damage to the you." << "\n";
                    double new_hp = x.get_hp() - damage;
                    x.set_hp(new_hp);
                    cout << "Your health now is " << x.get_hp() << "\n";
                }
            }
        }
        else if (option == 3)
        {
            cout << x;
        }
        else if(option == 4)
        {
            save_game(x, "/Users/rarestudur/Developer/C++/Proiect/savegame.txt");
        }
           
    }
    if(x.get_hp() <= 0)
    {
        cout << "You lost\n";
    }
    else if (Giant.get_hp() <= 0)
    {
        cout << "You won, the giant has been defeated!!!\n";
    }
    return ;
}



int main(int argc, const char * argv[]) {
    CreateMenu Menu;
    Game G;
    bool inmenu = true;
    while(inmenu)
    {
        system("clear");
        if(Menu.display_load() == true)
        {
            Player x;
            load_game(x, "savegame.txt");
            G.game_itself(x);
        }
        else
        {
            Menu.display_class();
            int option;
            cin >> option;
            system("clear");
            switch(option)
            {
                case 1:
                {
                    cout << "Warrior: The warrior is a master of close combat, wielding weapons such as swords, axes, and hammers with deadly precision. They are known for their high health and strength, making them excellent tanks for absorbing damage while their teammates deal damage from afar. Warriors can also specialize in specific types of combat, such as dual-wielding or shield-bashing, to suit their playstyle.\n";
                    if(Menu.return_display() == 0)
                    {
                        string name = enter_name();
                        Warrior x(name);
                        inmenu = false;
                        G.game_itself(x);
                    }
                }
                break;
                case 2:
                {
                    cout << "Mage:The mage is a powerful spellcaster, using their arcane knowledge to conjure spells that can deal massive damage to enemies or heal allies. They have low health and are often vulnerable in close combat, but their ability to manipulate the elements and cast powerful spells makes them a force to be reckoned with. Mages can specialize in specific types of magic, such as fire or ice, to tailor their abilities to specific situations.\n";
                    if(Menu.return_display() == 0)
                    {
                        string name = enter_name();
                        Mage x(name);
                        inmenu = false;
                        G.game_itself(x);
                    }
                }
                    break;
                case 3:
                {
                    cout << "The rogue is a master of stealth and subterfuge, using their agility and quick wit to maneuver through enemies undetected or deal massive damage with sneak attacks. They have low health and aren't suited for direct combat, but their ability to pick locks, disarm traps, and move silently makes them excellent for scouting and reconnaissance. Rogues can specialize in specific skills, such as pickpocketing or trap disarming, to better suit their playstyle.\n";
                    if(Menu.return_display() == 0)
                    {
                        string name = enter_name();
                        Rogue x(name);
                        inmenu = false;
                        G.game_itself(x);
                    }
                }
                    break;
                case 4:
                {
                    cout << "The cleric is a holy warrior, using their faith and divine powers to both heal allies and smite enemies. They have moderate health and combat abilities, but their ability to heal and buff allies makes them invaluable in any party. Clerics can specialize in specific domains, such as healing or combat, to better suit their role in a party.\n";
                    if(Menu.return_display() == 0)
                    {
                        string name = enter_name();
                        Cleric x(name);
                        inmenu = false;
                        G.game_itself(x);
                    }
                }
                    break;
                case 5:
                {
                    cout << "The orc is a fierce warrior, using their brute strength and primal instincts to overpower enemies. They have high health and strength, making them excellent tanks, but their lack of finesse can sometimes make them vulnerable to more agile enemies. Orcs can specialize in specific combat styles, such as berserker or shamanistic, to suit their playstyle and give them an edge in battle.\n";
                    if(Menu.return_display() == 0)
                    {
                        string name = enter_name();
                        Orc x(name);
                        inmenu = false;
                        G.game_itself(x);
                    }
                }
                case 6:
                {
                    if(Menu.return_display() == false)
                    {
                        Player x;
                        cin >> x;
                        inmenu = false;
                        G.game_itself(x);
                    }
                }
                    break;
                default:
                    inmenu = false;
                    break;
            }
        }
    }
    return 0;
}
