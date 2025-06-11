#include <bits/stdc++.h>
using namespace std;
class Student
{
private:
    std::string name;
    int yearOfStudy;
    std::set<std::string> completed;
    std::set<std::string> enrolled;
    std::set<char> slots;

public:
    Student();
    Student(std::string name, int yearOfStudy)
    {
        this->name = name;
        this->yearOfStudy = yearOfStudy;
    }
    ~Student();
    void addCompletedCourses(std::vector<std::string> &completedCourses)
    {
        for (auto &i : completedCourses)
        {
            completed.insert(i);
        }
    }
    set<string> getCompleted()
    {
        return completed;
    }
    void addEnrolledCourse(string courseID, char courseSlot)
    {
        enrolled.insert(courseID);
        slots.insert(courseSlot);
    }

    bool getSlotAvailability(char slot)
    {
        return slots.find(slot) == slots.end();
    }
};

class Course
{
private:
    std::string name;
    int numberOfCredits;
    int capacity;
    std::set<string> prerequisites;
    char timeSlot;
    vector<string> studentsEnrolled;

public:
    Course();
    Course(string name, int numberOfCredits, int capacity, char timeSlot)
    {
        this->name = name;
        this->capacity = capacity;
        this->numberOfCredits = numberOfCredits;
        this->timeSlot = timeSlot;
    }
    ~Course();
    void addPrerequisites(vector<string> &allPrerequisites)
    {
        for (auto &i : allPrerequisites)
        {
            prerequisites.insert(i);
        }
    }
    void enrollStudent(string studentID)
    {
        studentsEnrolled.push_back(studentID);
    }
    void print(string ID)
    {
        cout << "Enrolled students in " << ID << endl;
        for (auto &i : studentsEnrolled)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    set<string> getPrereq()
    {
        return prerequisites;
    }
    bool getAvaliability()
    {
        return studentsEnrolled.size() == capacity;
    }
    char getSlot()
    {
        return timeSlot;
    }
};

class Institute
{
private:
    std::map<std::string, Student> allStudents;
    std::map<std::string, Course> allCourses;

public:
    Institute() {}
    ~Institute() {}
    void add_student()
    {
        std::string ID, name;
        int year, coursesCompleted;
        std::cin >> ID >> name >> year >> coursesCompleted;
        Student st(name, year);
        allStudents[ID] = st;
        std::vector<std::string> courses;
        for (int i = 0; i < coursesCompleted; i++)
        {
            std::string courseID;
            std::cin >> courseID;
            courses.push_back(courseID);
        }
        st.addCompletedCourses(courses);
    }
    void add_course()
    {
        std::string ID, name;
        int credits, capacity;
        char slot;
        std::cin >> ID >> name >> credits >> capacity >> slot;
        int prerequisites;
        std::cin >> prerequisites;
        vector<string> allPrerequisites;
        bool flag = 0;
        for (int i = 0; i < prerequisites; i++)
        {
            string courseID;
            cin >> courseID;
            if (allCourses.find(courseID) == allCourses.end())
            {
                flag = 1;
            }
            allPrerequisites.push_back(courseID);
        }
        if (flag)
        {
            return;
        }
        Course co(name, credits, capacity, slot);
        allCourses[ID] = co;
    }
    void enroll()
    {
        string studentID, courseID;
        cin >> studentID >> courseID;
        if (allStudents.find(studentID) == allStudents.end() || allCourses.find(courseID) == allCourses.end())
        {
            return;
        }
        Student &st = allStudents[studentID];
        Course &co = allCourses[courseID];
        set<string> completed = st.getCompleted();
        set<string> prerequisites = co.getPrereq();

        for (auto &i : prerequisites)
        {
            if (completed.find(i) == completed.end())
            {
                return;
            }
        }
        if (!co.getAvaliability() || !st.getSlotAvailability(co.getSlot()))
        {
            return;
        }
        co.enrollStudent(studentID);
        st.addEnrolledCourse(courseID, co.getSlot());
    }
    void print()
    {
        string courseID;
        cin >> courseID;
        if (allCourses.find(courseID) == allCourses.end())
        {
            cout << "Invalid Course " << courseID << endl;
        }
        else
        {
            allCourses[courseID].print(courseID);
        }
    }
};

int main()
{
    Institute IITMadras;
    int q;
    std::cin >> q;
    while (q--)
    {
        std::string str;
        std::cin >> str;
        if (str == "add_student")
        {
            IITMadras.add_student();
        }
        else if (str == "add_course")
        {
            IITMadras.add_course();
        }
        else if (str == "enroll")
        {
            IITMadras.enroll();
        }
        else
        {
            IITMadras.print();
        }
    }
}
