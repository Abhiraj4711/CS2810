#include <bits/stdc++.h>

class QNS
{
private:
    // attributes
    int powerLevel;
    int durability;
    int energyStorage;
    int heatLevel;
    static std::queue<QNS *> suits;

public:
    // Constructors
    QNS(int p, int d, int e, int h)
    {
        powerLevel = p;
        durability = d;
        energyStorage = e;
        heatLevel = h;
    }
    QNS()
    {
        powerLevel = 1000;
        durability = 500;
        energyStorage = 300;
        heatLevel = 0;
    }
    QNS(QNS *q)
    {
        powerLevel = q->powerLevel;
        durability = q->durability;
        energyStorage = q->energyStorage;
        heatLevel = q->heatLevel;
    }

    // operator overloading
    QNS *operator+(QNS *q)
    {
        powerLevel = std::min(5000, powerLevel + q->energyStorage);
        durability = durability + q->durability;
        energyStorage += q->powerLevel;
        heatLevel = heatLevel;
        return this;
    }
    QNS *operator-(int x)
    {
        durability -= x;
        durability = durability;
        energyStorage += x;
        heatLevel += x;
        heatLevel = std::max(0, heatLevel);
        return this;
    }
    QNS *operator*(int x)
    {
        powerLevel = std::min(5000, powerLevel + ((powerLevel * x) / 100));
        energyStorage += 5 * x;
        heatLevel += x;
        heatLevel = std::max(0, heatLevel);
        return this;
    }
    QNS *operator/(int x)
    {
        durability += x;
        heatLevel -= x;
        heatLevel = std::max(heatLevel, 0);
        return this;
    }

    // function overloading
    void boostPower(int factor)
    {
        *this *factor;
    }
    void boostPower(QNS *otherSuit)
    {
        *this + otherSuit;
    }

    // comparision overloading
    bool operator==(QNS *q)
    {
        return ((durability == q->durability) && (powerLevel == q->powerLevel));
    }
    bool operator<(QNS *q)
    {
        return ((powerLevel + durability) < (q->powerLevel + q->durability));
    }

    // getters
    int getPowerLevel()
    {
        return powerLevel;
    }
    int getDurability()
    {
        return durability;
    }
    int getEnergyStorage()
    {
        return energyStorage;
    }
    int getHeatLevel()
    {
        return heatLevel;
    }

    // setters
    void setPowerLevel(int p)
    {
        powerLevel = p;
    }
    void setDurability(int d)
    {
        durability = d;
    }
    void setEnergyStorage(int e)
    {
        energyStorage = e;
    }
    void setHeatLevel(int h)
    {
        heatLevel = h;
    }

    // other functions
    static void addSuit(int p, int d, int e, int h)
    {
        QNS *q = new QNS(p, d, e, h);
        QNS::suits.push(q);
    }
    static QNS *getExtraSuit()
    {
        if (QNS::suits.empty())
        {
            return NULL;
        }
        auto ans = QNS::suits.front();
        QNS::suits.pop();
        return ans;
    }
};

std::queue<QNS *> QNS::suits;

class Avenger
{
private:
    // attributes
    std::string name;
    QNS suit;
    int attackStrength;

public:
    // constructor
    Avenger(std::string avName, QNS *avSuit, int strength)
    {
        name = avName;
        suit = *avSuit;
        attackStrength = strength;
    }

    // methods
    void attack(Avenger &enemy)
    {
        enemy.suit - attackStrength;
    }
    void upgradeSuit()
    {
        QNS *q = QNS::getExtraSuit();
        if (q == NULL)
        {
            return;
        }
        suit + q;
    }
    void repair(int x)
    {
        suit / x;
    }
    void printStatus()
    {
        std::cout << name << " " << suit.getPowerLevel() << " " << suit.getDurability() << " " << suit.getEnergyStorage() << " " << suit.getHeatLevel() << "\n";
    }

    // getters
    std::string getName()
    {
        return name;
    }
    int getAttackStrength()
    {
        return attackStrength;
    }
    QNS *getSuit()
    {
        return &suit;
    }
};

class Battle
{
private:
    // attributes
    std::vector<Avenger *> heroes;
    std::vector<Avenger *> enemies;
    std::vector<std::string> battleLog;

public:
    // methods
    void addAvenger(std::string name, int attack)
    {
        QNS *q = QNS::getExtraSuit();
        if (q == NULL)
        {
            std::cout << name + " is out of fight\n";
            return;
        }
        Avenger *av = new Avenger(name, q, attack);
        heroes.push_back(av);
    }
    void addEnemy(std::string name, int attack)
    {
        QNS *q = QNS::getExtraSuit();
        if (q == NULL)
        {
            std::cout << name + " is out of fight\n";
            return;
        }
        Avenger *en = new Avenger(name, q, attack);
        enemies.push_back(en);
    }
    void startBattle()
    {
        std::string str;
        while (std::cin >> str)
        {
            if (str == "Attack")
            {
                std::string av1, av2;
                std::cin >> av1 >> av2;
                Avenger *a1 = NULL, *a2 = NULL;
                for (auto it : heroes)
                {
                    if (it->getName() == av1)
                    {
                        a1 = it;
                    }
                    else if (it->getName() == av2)
                    {
                        a2 = it;
                    }
                }
                for (auto it : enemies)
                {
                    if (it->getName() == av1)
                    {
                        a1 = it;
                    }
                    else if (it->getName() == av2)
                    {
                        a2 = it;
                    }
                }
                if (a1->getSuit()->getHeatLevel() <= 500 && a1->getSuit()->getDurability() > 0 && a2->getSuit()->getDurability() > 0)
                {
                    *a2->getSuit() - a1->getAttackStrength();
                    battleLog.push_back(a1->getName() + " attacks " + a2->getName());
                    if (a2->getSuit()->getDurability() <= 0)
                    {
                        battleLog.push_back(a2->getName() + " suit destroyed");
                    }
                    else if (a2->getSuit()->getHeatLevel() > 500)
                    {
                        battleLog.push_back(a2->getName() + " suit overheated");
                    }
                }
            }
            else if (str == "Repair")
            {
                std::string av;
                int x;
                std::cin >> av >> x;
                Avenger *a = NULL;
                for (auto it : heroes)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                for (auto it : enemies)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                *a->getSuit() / x;
                battleLog.push_back(a->getName() + " repaired");
            }
            else if (str == "BoostPowerByFactor")
            {
                std::string av;
                int x;
                std::cin >> av >> x;
                Avenger *a = NULL;
                for (auto it : heroes)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                for (auto it : enemies)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                *a->getSuit() * x;
                battleLog.push_back(a->getName() + " boosted");
                if (a->getSuit()->getHeatLevel() > 500 && a->getSuit()->getDurability() > 0)
                {
                    battleLog.push_back(a->getName() + " suit overheated");
                }
            }
            else if (str == "BoostPower")
            {
                std::string av;
                int p, d, e, h;
                std::cin >> av >> p >> d >> e >> h;
                Avenger *a = NULL;
                for (auto it : heroes)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                for (auto it : enemies)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                battleLog.push_back(a->getName() + " boosted");
                QNS *q = new QNS(p, d, e, h);
                *a->getSuit() + q;
            }
            else if (str == "AvengerStatus")
            {
                std::string av;
                std::cin >> av;
                Avenger *a = NULL;
                for (auto it : heroes)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                for (auto it : enemies)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                a->printStatus();
            }
            else if (str == "Upgrade")
            {
                std::string av;
                std::cin >> av;
                Avenger *a = NULL;
                for (auto it : heroes)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                for (auto it : enemies)
                {
                    if (it->getName() == av)
                    {
                        a = it;
                        break;
                    }
                }
                QNS *q = QNS::getExtraSuit();
                if (q != NULL)
                {
                    *a->getSuit() + q;
                    battleLog.push_back(a->getName() + " upgraded");
                }
                else
                {
                    battleLog.push_back(a->getName() + " upgrade Fail");
                }
            }
            else if (str == "PrintBattleLog")
            {
                printBattleLog();
            }
            else if (str == "BattleStatus")
            {
                int ans = Result();
                if (ans == 1)
                {
                    std::cout << "heroes are winning\n";
                }
                else if (ans == -1)
                {
                    std::cout << "enemies are winning\n";
                }
                else
                {
                    std::cout << "tie\n";
                }
            }
            else
            {
                return;
            }
        }
    }
    void printBattleLog()
    {
        for (auto it : battleLog)
        {
            std::cout << it << "\n";
        }
    }
    int Result()
    {
        int heroesSum = 0;
        for (auto hero : heroes)
        {
            if (hero->getSuit()->getDurability() > 0)
                heroesSum += hero->getSuit()->getDurability() + hero->getSuit()->getPowerLevel();
        }
        int enemiesSum = 0;
        for (auto enemy : enemies)
        {
            if (enemy->getSuit()->getDurability() > 0)
                enemiesSum += enemy->getSuit()->getDurability() + enemy->getSuit()->getPowerLevel();
        }
        if (enemiesSum == heroesSum)
        {
            return 0;
        }
        else if (enemiesSum > heroesSum)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
};

int main()
{
    int k, n, m;
    std::cin >> k >> n >> m;
    Battle b;
    while (k--)
    {
        int p, d, e, h;
        std::cin >> p >> d >> e >> h;
        QNS::addSuit(std::min(5000, p), std::max(0, d), e, std::max(std::min(500, h), 0));
    }
    while (n--)
    {
        std::string name;
        int attack;
        std::cin >> name >> attack;
        b.addAvenger(name, attack);
    }
    while (m--)
    {
        std::string name;
        int attack;
        std::cin >> name >> attack;
        b.addEnemy(name, attack);
    }
    std::string str;
    std::cin >> str;
    b.startBattle();
}