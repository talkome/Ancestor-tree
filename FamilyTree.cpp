//
// Created by ko tal on 09/07/2020.
//

#include <iostream>
#include <regex>
#include "FamilyTree.hpp"
using namespace family;

Person::Person(const string& person_name) {
    name = person_name;
    father = nullptr;
    mother = nullptr;
}

Person::Person(const string& person_name, bool isMale) {
    name = person_name;
    father = nullptr;
    mother = nullptr;
    isMale = isMale;

}

Tree &family::Tree::addFather(const string& child, const string& father) {
    Person* chosenChild = findPerson(root,child);
    if(chosenChild == nullptr)
        throw exception();
    else {
        if (chosenChild->father != nullptr)
            throw exception();

        Person* newFather = new Person(father);
        chosenChild->father = newFather;
        chosenChild->father->relation = relation(father);
        return *this;
    }
}

Tree &family::Tree::addMother(const string& child, const string& mother) {
    Person* chosenChild = findPerson(root, child);
    if(chosenChild == nullptr)
        throw exception();
    else{
        if (chosenChild->father != nullptr)
            throw exception();

        Person* newMother = new Person(mother);
        chosenChild->father = newMother;
        chosenChild->father->relation = relation(mother);
        return *this;
    }
}

Person* Tree::findPerson(Person* root, const string& childName) {
    if (root == nullptr)
        return nullptr;
    if (root->name == childName)
        return root;
    Person* found = findPerson(root->father,childName);
    if (found != nullptr)
        return found;
    return findPerson(root->mother,childName);
}

Tree::Tree(const string& name) {
    root = new Person(name);
}

string family::Tree::relation(const string& name) {
    if (name == root->name)
        return "me";
    else{
        Person* found = findPerson(root, name);
        if (found != nullptr){
            int height = treeHeight(root,name);
            return countRelation(height,found->isMale);
        } else return "unrelated";
    }
}

string Tree::countRelation(int height, bool gender) {
    if (height == 1) {
        if (gender)
            return "Father";
        else return "Mother";
    } else {
        string great = "";
        for (size_t i = 0; i < height-2; ++i) {
            great += "great-";
        }
        if(gender)
            return great+"grandfather";
        else return great+"grandmother";
    }
}

int Tree::treeHeight(Person* root, const string& name) {
    if(root == nullptr)
        return -1;
    else if (root->name == name)
        return 0;
    int leftSide = treeHeight(root->father, name);
    if (leftSide < 0){
        int rightSide = treeHeight(root->mother,name);
        if (rightSide < 0)
            return rightSide;
        else
            return rightSide+1;
    }
    return leftSide+1;

}

string family::Tree::find(const string& relation) {
    if (relation == "me")
        return root->name;
    if (checkLegalInput(relation)){
        Person* found = relationsNames(root,relation);
        if (found == nullptr)
            throw exception();
        else
            return found->name;
    }
    else throw runtime_error("the tree cannot handle the "+relation+" relation");
}

bool Tree::checkLegalInput(const string& relation) {
    regex pat{ "^(?:(?:great-)*grand)?(?:mother|father)$" };
    bool match = regex_search(relation, pat);
    return match;
}

Person *Tree::relationsNames(Person *root, const string& relation) {
    if (root == nullptr)
        return nullptr;
    if (root->relation == relation)
        return root;
    Person* found = relationsNames(root->father, relation);
    if (found != nullptr) return found;
    return relationsNames(root->mother,relation);
}

void Tree::remove(const string& name) {
    if (name == root->name)
        throw exception();
    else{
        bool gender;
        Person* found = findPerson(root,name);
        std::cout << "remove: "+name << endl;
        if (found != nullptr)
        {
            Person* child;
            if ((root->father && root->father->name == found->name) ||
            (root->mother && root->mother->name == found->name)){
                child = root;
            } else {
                child = findPerson(root, name);
            }
            gender = child->father != nullptr && (child->father->name == name);
            deleteTree(found);
            if (gender)
                child->father = nullptr;
            else child->mother = nullptr;
        }
    }
}

void Tree::deleteTree(Person *person) {
    if (person == nullptr) return;
    deleteTree(person->mother);
    deleteTree(person->father);
    free(person);
    delete person;
}

void Tree::display() {
    std::cout << printTree(root,"") << std::endl;
}

string Tree::printTree(Person *root, string family) {
    if (root->father == nullptr && root->mother == nullptr)
        return family;
    if (root->father == nullptr){
        family.append("[Son: "+root->name+" Mother: "+root->mother->name+"]");
        return printTree(root->mother,family);
    }
    if (root->mother == nullptr){
        family.append("[Son: "+root->name+" Father: "+root->mother->name+"]") ;
        return printTree(root->father,family);
    }
    family.append("[Son: "+root->name+", Father: "+root->father->name+", Mother: "+root->mother->name+"]") ;
    return printTree(root->father,family);
    return printTree(root->mother,family);
}












