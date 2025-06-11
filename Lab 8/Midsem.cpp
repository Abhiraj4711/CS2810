#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Comparator;

class Employee
{
private:
    int ID;
    int age;
    int experience;
    int bossID;
    vector<int> children;
    int depth;
    int mom(int a, int b, vector<int> &vec)
    {
        return a;
    }
    bool comp(int a, int b, map<int, Employee *> &IDtoEmployee)
    {
        if (IDtoEmployee[a]->getAge() == IDtoEmployee[b]->getAge())
        {
            return IDtoEmployee[a]->getID() > IDtoEmployee[a]->getID();
        }
        return IDtoEmployee[a]->getAge() > IDtoEmployee[a]->getAge();
    }
    int quickSelectFunction(int a, int b, vector<int> &vec, map<int, Employee *> &IDtoEmployee, int k)
    {
        if (a == b)
        {
            return vec[a];
        }
        int median = mom(a, b, vec);
        swap(vec[a], vec[median]);
        median = a;
        int bb = b;
        while (median < bb)
        {
            Employee e(0, 0, 0, 0);
            if (comp(vec[median + 1], vec[median], IDtoEmployee))
            {
                swap(vec[bb], vec[median + 1]);
                bb--;
            }
            else
            {
                swap(vec[median + 1], vec[median]);
                median++;
            }
        }

        if (k == median - a + 1)
        {
            return vec[k];
        }
        else if (k < median - a + 1)
        {
            return quickSelectFunction(a, median, vec, IDtoEmployee, k);
        }
        else
        {
            return quickSelectFunction(median + 1, b, vec, IDtoEmployee, k - (median - a + 1));
        }
    }

public:
    int average(map<int, Employee *> &IDtoEmployee)
    {
        vector<Employee *> vecForSubordinates;
        queue<int> queueForSubordinates;
        vecForSubordinates.push_back(IDtoEmployee[ID]);
        queueForSubordinates.push(ID);
        while (!queueForSubordinates.empty())
        {
            int curr = queueForSubordinates.front();
            queueForSubordinates.pop();
            for (auto i : IDtoEmployee[curr]->getChildren())
            {
                vecForSubordinates.push_back(IDtoEmployee[i]);
                queueForSubordinates.push(i);
            }
        }
        ll total = 0;
        for (auto i : vecForSubordinates)
        {
            total += i->getExperience();
        }
        return total / vecForSubordinates.size();
    }
    Employee(int id, int Age, int Experience, int bossid)
    {
        ID = id;
        age = Age;
        experience = Experience;
        bossID = bossid;
        children.resize(0);
        depth = 0;
    }
    int getAge()
    {
        return age;
    }
    int getID()
    {
        return ID;
    }
    int getExperience()
    {
        return experience;
    }
    int getDepth()
    {
        return depth;
    }
    int getBoss()
    {
        return bossID;
    }
    vector<int> &getChildren()
    {
        return children;
    }
    void setDepth(int d)
    {
        depth = d;
    }
    void addChild(int childID)
    {
        children.push_back(childID);
    }

    int quickSelect(int k, map<int, Employee *> &IDtoEmployee)
    {
        vector<int> vecForSubordinates;
        queue<int> queueForSubordinates;
        vecForSubordinates.push_back(ID);
        queueForSubordinates.push(ID);
        while (!queueForSubordinates.empty())
        {
            int curr = queueForSubordinates.front();
            queueForSubordinates.pop();
            for (auto i : IDtoEmployee[curr]->getChildren())
            {
                vecForSubordinates.push_back(i);
                queueForSubordinates.push(i);
            }
        }

        return quickSelectFunction(0, vecForSubordinates.size(), vecForSubordinates, IDtoEmployee, k);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<Employee *> allEmployees;
    int boss;
    map<int, Employee *> IDtoEmployee;
    vector<int> depthMaxExperience;
    vector<int> depthMaxAge;
    int minAge = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int id, age, experience, bossID;
        cin >> id >> age >> experience >> bossID;
        Employee *e = new Employee(id, age, experience, bossID);
        allEmployees.push_back(e);
        IDtoEmployee[id] = e;
        if (age < minAge)
        {
            minAge = age;
        }
        if (id == bossID)
        {
            boss = id;
        }
    }

    for (auto e : allEmployees)
    {
        int bossID = e->getBoss();
        if (bossID == e->getID())
        {
            continue;
        }
        Employee *bossOfEmp = IDtoEmployee[bossID];
        bossOfEmp->addChild(e->getID());
    }

    queue<int> queueOfEmp;
    queueOfEmp.push(boss);
    queueOfEmp.push(0);
    int depth = 0;
    depthMaxExperience.push_back(0);
    depthMaxAge.push_back(0);

    while (!queueOfEmp.empty())
    {
        int currEmp = queueOfEmp.front();
        queueOfEmp.pop();
        if (currEmp == 0)
        {
            depth++;
            if (queueOfEmp.empty())
            {
                break;
            }
            queueOfEmp.push(0);
            depthMaxExperience.push_back(depthMaxExperience[depth - 1]);
            depthMaxAge.push_back(depthMaxAge[depth - 1]);
            continue;
        }
        Employee *emp = IDtoEmployee[currEmp];
        emp->setDepth(depth);
        depthMaxExperience[depth] = max(depthMaxExperience[depth], emp->getExperience());
        depthMaxAge[depth] = max(depthMaxAge[depth], emp->getAge());
        vector<int> &children = emp->getChildren();
        for (auto i : children)
        {
            queueOfEmp.push(i);
        }
    }
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int compType;
            cin >> compType;
            if (compType == 1)
            {
                int ans = 0;
                for (auto e : allEmployees)
                {
                    if (e == IDtoEmployee[boss])
                    {
                        ans++;
                    }
                    else if (e->getExperience() >= depthMaxExperience[e->getDepth() - 1])
                    {
                        ans++;
                    }
                }
                cout << ans << "\n";
            }
            else if (compType == 2)
            {
                int ans = 0;
                for (auto e : allEmployees)
                {
                    if (e == IDtoEmployee[boss])
                    {
                        ans++;
                    }
                    else if (e->getAge() >= depthMaxAge[e->getDepth() - 1])
                    {
                        ans++;
                    }
                }
                cout << ans << "\n";
            }
            else
            {
                int ans = 0;
                for (auto e : allEmployees)
                {
                    if (e->getAge() == minAge || e->getExperience() == depthMaxExperience.back())
                    {
                        ans++;
                    }
                }
                cout << ans << "\n";
            }
        }
        else if (type == 2)
        {
            int id;
            cin >> id;
            cout << IDtoEmployee[id]->average(IDtoEmployee) << "\n";
        }
        else
        {
            int idofEmployeeHere, kHere;
            cin >> idofEmployeeHere >> kHere;
            cout << "HI";
            Employee *emp = IDtoEmployee[idofEmployeeHere];
            cout << emp->quickSelect(kHere, IDtoEmployee) << "\n";
        }
    }
}