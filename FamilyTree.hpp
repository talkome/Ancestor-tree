//
// Created by ko tal on 09/07/2020.
//
using namespace std;
#include <string>

namespace family{

    class Person {
    public:
        string name;
        bool isMale;
        string relation;
        Person* mother;
        Person* father;

        explicit Person(const string& person_name);
        Person(const string& name, bool isMale);
    };

    class Tree{
    public:
        static Person* root;

        explicit Tree(const string& name);

        Tree& addFather(const string& name1,const string& name2);
        Tree& addMother(const string& name1,const string& name2);
        string relation(const string& name);
        string find(const string& name);
        void display();
        void remove(const string& name);
        Person* findPerson(Person* root, const string& childName);
        void deleteTree(Person* person);
        static string countRelation(int height, bool gender);
        int treeHeight(Person* root, const string& name);
        static bool checkLegalInput(const string& relation);
        Person* relationsNames(Person* root, const string& relation);
        string printTree(Person* root, string family);
    };

};



