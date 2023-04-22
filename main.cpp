#include <iostream>
#include <cstring>
#include <climits>
using namespace std;


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

class String
{
    char *point;
public:
    String()
    {
        point = nullptr;
    }
    String(const char* x)
    {
        this -> point = new char [strlen(x)];
        strcpy(point,x);
    }
    String(const String &sir)
    {
        this->point = new char[strlen(sir.point)];
        strcpy(this->point,sir.point);
    }
    ~String()
    {
        if(this->point != nullptr)
        {
            delete [] this->point;
        }
    }
    char get_String() const;
    String & operator=(const String &sir)
    {
        if(this->point != nullptr)
        {
            delete [] this->point;
        }
        this->point = new char[strlen(sir.point)];
        strcpy(this->point,sir.point);
        return *this;
    }
    String & operator=(const char sir[])
    {
        if(this->point != nullptr)
        {
            delete [] this->point;
        }
        this->point = new char[strlen(sir)];
        strcpy(this->point,sir);
        return *this;
    }
    String & operator =(String && sir)
    {
        this->point = sir.point; // muta nu copie
        sir.point = nullptr;
        return *this;
    }
    friend ostream & operator << (ostream &out, const String &x);
    friend istream & operator >> (istream &in,  String &x);
};

String enter_name()
{
    cout << "Enter your character's name\n";
    String nume;
    cin >> ws >> nume;
    return nume;
}


char String::get_String() const
{
    return *this->point;
}

ostream & operator <<(ostream &out,const String &x)
{
    cout << x.point;
    return out;
}

istream & operator >> (istream &in, String &x)
{
    char *temp = new char[100];
    in.getline(temp,100);
    x.point = new char[strlen(temp)];
    strcpy(x.point,temp);
    delete [] temp;
    return in;
}

class Ability
{
    String ability_name;
    int damage;
public:
    Ability();
    Ability(const String name,int dmg);
    String get_name() const
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
    void setname(const String &name)
    {
        this->ability_name = name;
    }
    friend ostream & operator << (ostream &out, const Ability &x);
    friend istream & operator >> (istream &in, Ability &x);
    ~Ability() = default;
};

ostream & operator <<(ostream &out,const Ability &x)
{
    cout << x.ability_name << " " << x.damage << "\n";
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

Ability::Ability()
{
    this->ability_name = "Simple";
    this->damage = 0;
}

Ability::Ability(const String name,int dmg)
{
    this->ability_name = name;
    this->damage = dmg;
}

class Weapon
{
    String name_weapon;
    int attack;
public:
    Weapon();
    Weapon(String name,int atk): name_weapon(name),attack(atk){}
    Weapon(const char* name,int atk):name_weapon(name),attack(atk){}
    String get_name() const;
    int get_attack_value() const;
    friend ostream & operator << (ostream &out, const Weapon &x);
    friend istream & operator >> (istream &in, Weapon &x);
};

ostream & operator << (ostream &out, const Weapon &x)
{
    cout << "The name and the attack of your weapon is\n";
    cout << x.name_weapon << " " << x.attack << "\n";
    return out;
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

Weapon::Weapon()
{
    this->name_weapon = "Basic Weapon";
    this->attack = 0;
}

String Weapon::get_name() const
{
    return this->name_weapon;
}

int Weapon::get_attack_value() const
{
    return this->attack;
}

class Player
{
    int health,defense,magic,strength,speed,intelligence;
    String name;
    Weapon weapon;
    int num_abilities;
    Ability *abilities;
public:
    Player():name(""),health(0),defense(0),magic(0),strength(0),speed(0),intelligence(0),weapon(),num_abilities(1)
    {
        this->abilities = new Ability[num_abilities];
        add_ability(0, "Basic",0);
    }
    Player(const char* nume,const int& hp,const int & df,const int& Mp,const int& St,const int& Sp,const int& It, const char* name_weapon,int atk,int num_ab):name(nume),health(hp),magic(Mp),strength(St),speed(Sp),intelligence(It),weapon(name_weapon,atk),num_abilities(num_ab)
    {
        if (num_abilities <= 0)
        {
            cout << "Invalid number of abilities.\n";
            return;
        }
        this->abilities = new Ability[num_abilities];
    }
    Player(const String nume,const int& hp,const int & df,const int& Mp,const int& St,const int& Sp,const int& It, const char* name_weapon,int atk,int num_ab):name(nume),health(hp),magic(Mp),strength(St),speed(Sp),intelligence(It),weapon(name_weapon,atk),num_abilities(num_ab)
    {
        if (num_abilities <= 0)
        {
            cout << "Invalid number of abilities.\n";
            return;
        }
        this->abilities = new Ability[num_abilities];
    }
    char get_mume() const;
    int get_hp() const;
    int get_defense() const;
    int get_magic() const;
    int get_strength() const;
    int get_speed() const;
    int get_intelligence() const;
    int get_number_of_abilities() const;
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
    friend istream & operator >> (istream &in,  Player &x);
    ~Player()
    {
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

ostream & operator << (ostream &out, const Player &x)
{
    cout << "Name: " << x.name << "\n";
    cout << "Health: " << x.health << "\n";
    cout << "Defense: " << x.defense << "\n";
    cout << "Strength: " << x.strength << "\n";
    cout << "Magic Damage: " << x.magic << "\n";
    cout << "Speed: " << x.speed << "\n";
    cout << "Intelligence: " << x.intelligence << "\n";
    cout << x.weapon;
    cout << "Number of abilities: " << x.num_abilities << "\n";
    cout << "The name and damage of each ability : \n";
    for(int i = 0; i < x.num_abilities; i++)
    {
        cout << x.abilities[i];
    }
    return out;
}
istream & operator >> (istream &in,  Player &x)
{
    cout << "Enter this values for your character\n";
    cout << "Enter the name of your character\n";
    cin >> ws >> x.name;
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
    return in;
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
char Player::get_mume() const
{
    return this->name.get_String();
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
    Warrior():Player("John Doe",150,10,0,10,5,2,"Bronze Sword",10,1)
    {
        add_ability(0, "Strong Attack", 300);
    }
    Warrior(const char name[]):Player(name,150,10, 0, 10, 5, 2,"Bronze Sword",10,1)
    {
        add_ability(0, "Strong Attack", 300);
    }
    Warrior(const String name):Player(name,150,10, 0, 10, 5, 2,"Bronze Sword",10,1)
    {
        add_ability(0, "Strong Attack", 300);
    }
    ~Warrior() = default;
};

class Mage: public Player
{
public:
    Mage():Player("John Doe",100,5,150,2,5,15,"Wooden Staff",8,1)
    {
        add_ability(0, "Fireball", 300);
    }
    Mage(const char name[]):Player(name, 100, 5,150,2, 5, 15,"Wooden Staff",8,1)
    {
        add_ability(0, "Fireball", 300);
    }
    Mage(String name):Player(name, 100, 5,150,2, 5, 15,"Wooden Staff",8,1)
    {
        add_ability(0, "Fireball", 300);
    }
    ~Mage() = default;
};


class Rogue: public Player
{
public:
    Rogue():Player("John Doe",125,7,50,8,10,10,"Iron Dagger",7,1)
    {
        add_ability(0, "The dagger cut", 250);
    }
    Rogue(const char name[]):Player(name, 125,7,50,8, 10, 10,"Iron Dagger",7,1)
    {
        add_ability(0, "The dagger cut", 250);
    }
    Rogue(String name):Player(name, 125,7,50,8, 10, 10,"Iron Dagger",7,1)
    {
        add_ability(0, "The dagger cut", 250);
    }
    ~Rogue() = default;
};

class Cleric: public Player
{
public:
    Cleric():Player("John Doe",125,8,125,5,5,12,"Wooden Mace",9,1)
    {
        add_ability(0, "The Spirit of Justice", 350);
    }
    Cleric(const char name[]):Player(name, 125,8,125,5, 5,12,"Wooden Mace",9,1)
    {
        add_ability(0, "The Spirit of Justice", 350);
    }
    Cleric(String name):Player(name, 125,8,125,5, 5,12,"Wooden Mace",9,1)
    {
        add_ability(0, "The Spirit of Justice", 350);
    }
    ~Cleric() = default;
};

class Orc: public Player
{
public:
    Orc():Player("John Doe",200,12,0,15,10,2,"Stone Axe",11,1)
    {
        add_ability(0, "Strong Attack", 400);
    }
    Orc(const char name[]):Player(name, 200,12,0,15,10,2,"Stone Axe",11,1)
    {
        add_ability(0, "Strong Attack", 400);
    }
    Orc(String name):Player(name, 200,12,0,15,10,2,"Stone Axe",11,1)
    {
        add_ability(0, "Strong Attack", 400);
    }
    ~Orc() = default;
};

class CreateMenu {
public:
    void display();
    bool return_display();
    
};

void CreateMenu::display() {
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

void game_itself(Player &x)
{
    Mob Giant(100,100,70,50);
    cout << "You are face to face with a giant?\n";
    cout << "How you attack?\n";
    while(x.get_hp() > 0 && Giant.get_hp() > 0)
    {
        cout << "1.Normal Damage using your weapon\n";
        cout << "2.Use one of your abilities\n";
        cout << "3.Check your stats\n";
        int option;
        cin >> option;
        if (option == 1)
        {
            int damage = calculate_attack_damage(x.get_strength(),0);
            if (damage == 0)
            {
                cout << "You missed the target." << "\n";
            } else {
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
           
    }
    if(x.get_hp() <= 0)
    {
        cout << "You lost\n";
    }
    else if (Giant.get_hp() <= 0)
    {
        cout << "You won, the giant has been defeated!!!\n";
    }
    return;
}

int main(int argc, const char * argv[]) {
    CreateMenu Menu;
    bool inmenu = true;
    while(inmenu)
    {
        system("clear");
        Menu.display();
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
                    String name = enter_name();
                    Warrior x(name);
                    inmenu = false;
                    game_itself(x);
                }
            }
            break;
            case 2:
            {
                cout << "Mage:The mage is a powerful spellcaster, using their arcane knowledge to conjure spells that can deal massive damage to enemies or heal allies. They have low health and are often vulnerable in close combat, but their ability to manipulate the elements and cast powerful spells makes them a force to be reckoned with. Mages can specialize in specific types of magic, such as fire or ice, to tailor their abilities to specific situations.\n";
                if(Menu.return_display() == 0)
                {
                    String name = enter_name();
                    Mage x(name);
                    inmenu = false;
                    game_itself(x);
                }
            }
                break;
            case 3:
            {
                cout << "The rogue is a master of stealth and subterfuge, using their agility and quick wit to maneuver through enemies undetected or deal massive damage with sneak attacks. They have low health and aren't suited for direct combat, but their ability to pick locks, disarm traps, and move silently makes them excellent for scouting and reconnaissance. Rogues can specialize in specific skills, such as pickpocketing or trap disarming, to better suit their playstyle.\n";
                if(Menu.return_display() == 0)
                {
                    String name = enter_name();
                    Rogue x(name);
                    inmenu = false;
                    game_itself(x);
                }
            }
                break;
            case 4:
            {
                cout << "The cleric is a holy warrior, using their faith and divine powers to both heal allies and smite enemies. They have moderate health and combat abilities, but their ability to heal and buff allies makes them invaluable in any party. Clerics can specialize in specific domains, such as healing or combat, to better suit their role in a party.\n";
                if(Menu.return_display() == 0)
                {
                    String name = enter_name();
                    Cleric x(name);
                    inmenu = false;
                    game_itself(x);
                }
            }
                break;
            case 5:
            {
                cout << "The orc is a fierce warrior, using their brute strength and primal instincts to overpower enemies. They have high health and strength, making them excellent tanks, but their lack of finesse can sometimes make them vulnerable to more agile enemies. Orcs can specialize in specific combat styles, such as berserker or shamanistic, to suit their playstyle and give them an edge in battle.\n";
                if(Menu.return_display() == 0)
                {
                    String name = enter_name();
                    Orc x(name);
                    inmenu = false;
                    game_itself(x);
                }
            }
            case 6:
            {
                if(Menu.return_display() == false)
                {
                    Player x;
                    cin >> x;
                    inmenu = false;
                    game_itself(x);
                }
            }
                break;
            default:
                inmenu = false;
                break;
        }
    }
    return 0;
}
