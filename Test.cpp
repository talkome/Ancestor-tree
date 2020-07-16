/**
 * A demonstration test program for Gimatriya calculation.
 * 
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * Date: 2020-02
 */

#include "doctest.h"
#include "FamilyTree.hpp"
#include <iostream>
#include <string>
using namespace std;

family::Tree T("a");

TEST_CASE("Test case 1") {  
	family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov");   // Tells the tree that the father of Yosef is Yaakov.
	T.addMother("Yosef", "Rachel");
	T.addFather("Yaakov", "Isaac");
	T.addMother("Yaakov", "Rivka");
	T.addFather("Isaac", "Avraham");
	T.addFather("Avraham", "Terah");

    CHECK(T.relation("Rivka") == string("mother"));
    CHECK(T.relation("Terah") == string("great-great-grandfather"));
    CHECK(T.relation("xyz") == string("unrelated"));

    CHECK(T.find("mother") == string("Rivka"));
    CHECK(T.find("great-great-grandfather") == string("Terah"));

    TEST_CASE("addFather")
    {
        T.addFather("a","b");
                CHECK(T.relation("b") == string("father"));

        T.addFather("b", "c");
                CHECK(T.relation("c") == string("grandfather"));

        T.addFather("c", "d");
                CHECK(T.relation("d") == string("great-grandfather"));

        T.addFather("d", "e");
                CHECK(T.relation("e") == string("great-great-grandfather"));

        T.addFather("e", "f");
                CHECK(T.relation("f") == string("great-great-great-grandfather"));

                CHECK(T.find("father") == string("b"));
                CHECK(T.find("grandfather") == string("c"));
                CHECK(T.find("great-grandfather") == string("d"));
                CHECK(T.find("great-great-grandfather") == string("e"));
                CHECK(T.find("great-great-great-grandfather") == string("f"));

        std::cout<<"----------------------"<<std::endl;

    }  //10


    TEST_CASE("g*gf"){
                CHECK(T.relation("c") == string("grandfather"));
                CHECK(T.relation("d") == string("great-grandfather"));
                CHECK(T.relation("e") == string("great-great-grandfather"));
                CHECK(T.relation("f") == string("great-great-great-grandfather"));

        // remove


                CHECK_NOTHROW(T.remove("b") );
                CHECK_THROWS_AS(T.remove("c"), const std::exception& );
                CHECK_THROWS_AS(T.remove("d"), const std::exception& );
                CHECK_THROWS_AS(T.remove("f"), const std::exception& );
                CHECK_THROWS_AS(T.remove("k"), const std::exception&);
                CHECK_THROWS_AS(T.remove("z"), const std::exception&);
                CHECK_THROWS_AS(T.remove("b"), const std::exception&);
                CHECK_THROWS_AS(T.remove("c"), const std::exception&);
                CHECK_THROWS_AS(T.remove("d"), const std::exception&);
                CHECK_THROWS_AS(T.remove("e"), const std::exception&);
                CHECK_THROWS_AS(T.remove("f"), const std::exception&);

    } //15


    family::Tree TT("a");

    TEST_CASE("m-mm-m-..."){
        TT.addMother("a","b");
                CHECK(TT.relation("b") == string("mother"));

        TT.addFather("b", "c");
                CHECK(TT.relation("c") == string("grandfather"));

        TT.addFather("c", "d");
                CHECK(TT.relation("d") == string("great-grandfather"));

        TT.addFather("d", "e");
                CHECK(TT.relation("e") == string("great-great-grandfather"));

        TT.addFather("e", "f");
                CHECK(TT.relation("f") == string("great-great-great-grandfather"));

                CHECK(TT.find("mother") == string("b"));
                CHECK(TT.find("grandfather") == string("c"));
                CHECK(TT.find("great-grandfather") == string("d"));
                CHECK(TT.find("great-great-grandfather") == string("e"));
                CHECK(TT.find("great-great-great-grandfather") == string("f"));

    }// 10

    TEST_CASE("g*gm"){
        family::Tree TT("a");
        TT.addMother("a","b");
        TT.addFather("b", "c");
        TT.addFather("c", "d");
        TT.addFather("d", "e");
        TT.addFather("e", "f");

                CHECK(TT.relation("c") == string("grandfather"));
                CHECK(TT.relation("d") == string("great-grandfather"));
                CHECK(TT.relation("e") == string("great-great-grandfather"));
                CHECK(TT.relation("f") == string("great-great-great-grandfather"));


        // remove

                CHECK_NOTHROW(TT.remove("b") );
                CHECK_THROWS_AS(TT.remove("c"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("d"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("e"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("f"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("k"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("z"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("b"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("c"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("d"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("e"), const std::exception&);
                CHECK_THROWS_AS(TT.remove("f"), const std::exception&);
    } //16



    family::Tree TTT("a");

    TEST_CASE("MIX"){
        TTT.addFather("a","b");
                CHECK(TTT.relation("b") == string("father"));

        TTT.addMother("a", "c");
                CHECK(TTT.relation("c") == string("mother"));

        TTT.addFather("c", "d");
                CHECK(TTT.relation("d") == string("grandfather"));

        TTT.addMother("c", "e");
                CHECK(TTT.relation("e") == string("grandmother"));

        TTT.addFather("e", "f");
                CHECK(TTT.relation("f") == string("great-grandfather"));

        TTT.addMother("e", "g");
                CHECK(TTT.relation("g") == string("great-grandmother"));




//     b

// a
//         d

//     c
//             f
//         e
//             g


        // find
                CHECK(TTT.find("mother") == string("c"));
                CHECK(TTT.find("father") == string("b"));
                CHECK(TTT.find("father") == string("b"));
                CHECK(TTT.find("mother") == string("c"));
                CHECK(TTT.find("father") == string("b"));
                CHECK(TTT.find("mother") == string("c"));
                CHECK(TTT.find("grandfather") == string("d"));
                CHECK(TTT.find("grandmother") == string("e"));


                CHECK_NOTHROW(TTT.remove("b") );
                CHECK_NOTHROW(TTT.remove("c") );
                CHECK_THROWS_AS(TTT.remove("d"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("e"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("f"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("g"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("k"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("z"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("b"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("c"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("d"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("e"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("f"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("g"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("cc"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("db"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("eg"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove("fhfghf"), const std::exception&);
                CHECK_THROWS_AS(TTT.remove(""), const std::exception&);

    }// 28



    /// 88

    family::Tree TTTT("a");
    TEST_CASE("MIX"){
        TTTT.addFather("a","b");
        TTTT.addMother("a", "c");
        TTTT.addFather("c", "d");
        TTTT.addMother("c", "e");
        TTTT.addFather("e", "f");
        TTTT.addMother("e", "g");

                CHECK_NOTHROW(TTTT.remove("c"));
                CHECK_THROWS_AS(TTTT.remove("d"), const std::exception&);
                CHECK_NOTHROW(TTTT.remove("b"));




                CHECK_THROWS_AS(TTTT.remove("f"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("d"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("e"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("f"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("c"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("g"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("e"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("p"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("fd"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("csgdfg"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove("gsdfs"), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove(" "), const std::exception&);
                CHECK_THROWS_AS(TTTT.remove(""), const std::exception&);

    } //11


// ----------
// HILA TESTS
// ----------

    TEST_CASE("Test 1 addFather & addMother & relation") {

        family::Tree T ("Shalom");
        T.addFather("Shalom", "Aharon")
                .addMother("Shalom", "Yafa");

                CHECK(T.relation("Shalom") == string("me"));
                CHECK(T.relation("Aharon") == string("father"));
                CHECK(T.relation("Yafa") == string("mother"));

                CHECK_THROWS(T.addFather("Shalom", "Yosef")); //Shalom already has a father
                CHECK_THROWS(T.addMother("Shalom", "Meri"));

        T.addMother("Yafa", "Ahuva").addMother("Ahuva", "Miriam");

                CHECK(T.relation("Ahuva") == string("grandmother"));
                CHECK(T.relation("Miriam") == string("great-grandmother"));
                CHECK_THROWS(T.addMother("Yafa", "Michal"));
                CHECK_THROWS(T.addMother("Ahuva", "Michal"));
                CHECK_THROWS(T.addFather("Sason", "Yaakov")); //Sason is not on the tree

        T.addFather("Yafa", "Avi").addFather("Aharon", "Yigal").addMother("Aharon", "Nira");

                CHECK(T.relation("Avi") == string("grandfather"));
                CHECK(T.relation("Yigal") == string("grandfather"));
                CHECK(T.relation("Nira") == string("grandmother"));
                CHECK_THROWS(T.addFather("Yafa", "Yishai"));
                CHECK_THROWS(T.addMother("Aharon", "Tzila"));

        //check case of searching name that doesn't exist on the tree
                CHECK(T.relation("Hila") == string("unrelated"));
                CHECK(T.relation("Ben") == string("unrelated"));
                CHECK(T.relation("Eva") == string("unrelated"));
                CHECK(T.relation("Shimon") == string("unrelated"));
                CHECK(T.relation("Yossi") == string("unrelated"));
    }

    TEST_CASE("Test 1 find") {

        family::Tree T ("Yonit");
        T.addFather("Yonit", "Arel").addMother("Yonit", "Ronit")
                .addFather("Ronit", "Yonatan").addMother("Ronit", "Simha")
                .addFather("Arel", "Yosef").addMother("Arel", "Dikla");

                CHECK(T.find("mother") == string("Ronit"));
                CHECK(T.find("father") == string("Arel"));
                CHECK((T.find("grandfather") == string("Yosef") || T.find("grandfather") == string("Yonatan")));
                CHECK((T.find("grandmother") == string("Simha") || T.find("grandmother") == string("Dikla")));
                CHECK_THROWS(T.find("uncle")); //there is no option of "uncle" on this tree
                CHECK_THROWS(T.find("sister"));
                CHECK_THROWS(T.find("great-grandfather")); //there is no great-grandfather here
                CHECK_THROWS(T.find("great-grandmother"));

        T.addMother("Yosef", "Efrat").addFather("Yosef", "Shmuel").addFather("Shmuel", "Israel");

                CHECK(T.find("great-grandmother") == string("Efrat"));
                CHECK(T.find("great-grandfather") == string("Shmuel"));
                CHECK(T.find("great-great-grandfather") == string("Israel"));
                CHECK_THROWS(T.find("great-great-grandmother"));

        T.addFather("Yonatan", "Ofer").addMother("Yonatan", "Sima").addMother("Simha", "Ester");

                CHECK((T.find("great-grandfather") == string("Shmuel") || T.find("great-grandfather") == string("Ofer")));
                CHECK((T.find("great-grandmother") == string("Efrat")
                       || T.find("great-grandmother") == string("Sima")
                       || T.find("great-grandmother") == string("Ester")));
                CHECK_THROWS(T.find("great-great-great-grandfather"));
                CHECK_THROWS(T.find("great-great-great-great-grandfather"));
    }

    TEST_CASE("Test 1 remove") {

        family::Tree T ("Maya");
        T.addMother("Maya", "Anat").addFather("Maya", "Rami")
                .addMother("Anat", "Rivka").addFather("Anat", "Yoni")
                .addMother("Yoni", "Vered").addFather("Yoni", "Shlomi")
                .addFather("Rami", "David");

                CHECK_THROWS(T.remove("Maya")); //try to remove the root --> exception

                CHECK((T.find("grandfather") == string("David") || T.find("grandfather") == string("Yoni")));

                CHECK(T.find("father") == string("Rami"));
        T.remove("Rami");
                CHECK_THROWS(T.find("father"));
                CHECK(T.find("grandfather") == string("Yoni")); //because David has removed from the tree while removing Rami

                CHECK(T.find("great-grandmother") == string("Vered"));
                CHECK(T.find("great-grandfather") == string("Shlomi"));
        T.remove("Vered");
                CHECK_THROWS(T.find("great-grandmother"));
        T.remove("Yoni");
                CHECK_THROWS(T.find("great-grandfather"));
                CHECK_THROWS(T.find(T.find("grandfather")));

        T.addFather("Anat", "Nir"); //we've removed Yoni, sowe can add new father to Anat now
                CHECK(T.find("grandfather") == string("Nir"));
                CHECK(T.find("grandmother") == string("Rivka"));
        T.remove("Rivka");
                CHECK_THROWS(T.find("grandmother"));
        T.remove("Anat");
                CHECK_THROWS(T.find("grandfather"));
                CHECK_THROWS(T.find("mother"));
    }

    TEST_CASE("Test 2 addFather & addMother & relation"){

        family::Tree T ("Ronny");
        T.addFather("Ronny", "Dan").addMother("Ronny", "Rivka");

                CHECK(T.relation("Ronny") == string("me"));
                CHECK(T.relation("Dan") == string("father"));
                CHECK(T.relation("Rivka") == string("mother"));
                CHECK(T.relation("Rina") == string("unrelated"));
                CHECK(T.relation("Noa") == string("unrelated"));
                CHECK_THROWS(T.addFather("Ronny", "Liad")); // already has a father
                CHECK_THROWS(T.addMother("Ronny", "Lital"));

        T.addMother("Rivka", "Arbel").addMother("Arbel", "Rita").addFather("Dan", "Ronen").addFather("Ronen", "Almog");

                CHECK(T.relation("Arbel") == string("grandmother"));
                CHECK(T.relation("Rita") == string("great-grandmother"));
                CHECK(T.relation("Ronen") == string("grandfather"));
                CHECK(T.relation("Almog") == string("great-grandfather"));

                CHECK_THROWS(T.addMother("Ronny", "Michal")); // already has a mother
                CHECK_THROWS(T.addMother("Arbel", "Dana"));

                CHECK_THROWS(T.addFather("Gonen", "a")); // not on the tree
                CHECK_THROWS(T.addFather("Gina", "b"));

        T.addFather("Arbel", "Avi").addFather("Almog", "Yigal").addMother("Dan", "Hadar");

                CHECK(T.relation("Avi") == string("great-grandfather"));
                CHECK(T.relation("Yigal") == string("great-great-grandfather"));
                CHECK(T.relation("Hadar") == string("grandmother"));

                CHECK_THROWS(T.addFather("Arbel", "Yishai")); // already has father
                CHECK_THROWS(T.addMother("Dan", "Gal"));

                CHECK_THROWS(T.addMother("Teva", "a")); // not in tree
                CHECK_THROWS(T.addMother("Toly", "b"));
                CHECK_THROWS(T.addMother("Yonatan", "c"));
                CHECK_THROWS(T.addMother("Aaron", "d"));
                CHECK_THROWS(T.addMother("Norit", "e"));

    }

    TEST_CASE("Test 2 find"){

        family::Tree T ("Shimrit");
        T.addFather("Shimrit", "Shlomi").addMother("Shimrit", "Shani")
                .addFather("Shlomi", "Yona").addMother("Shlomi", "Shira")
                .addFather("Shani", "Snir").addMother("Shani", "Shayli");

                CHECK(T.find("mother") == string("Shani"));
                CHECK(T.find("father") == string("Shlomi"));
                CHECK((T.find("grandfather") == string("Yona") || T.find("grandfather") == string("Snir")));
                CHECK((T.find("grandmother") == string("Shira") || T.find("grandmother") == string("Shayli")));
                CHECK_THROWS(T.find("brother")); //there is no option of "uncle" on this tree
                CHECK_THROWS(T.find("friend"));
                CHECK_THROWS(T.find("great-grandfather")); //there is no great-grandfather here
                CHECK_THROWS(T.find("great-grandmother"));

        T.addMother("Snir", "ShemTov").addFather("Snir", "Hanoh").addFather("Hanoh", "Alex");

                CHECK(T.find("great-grandfather") == string("Hanoh"));
                CHECK(T.find("great-grandmother") == string("ShemTov"));
                CHECK(T.find("great-great-grandfather") == string("Alex"));

                CHECK_THROWS(T.find("great-great-great-grandmother")); //there is no great-great-great-grandmother
    }

    TEST_CASE("Test 2 remove"){
        family::Tree T ("Omri");
        T.addMother("Omri", "Hanna").addFather("Omri", "Omer")
                .addMother("Hanna", "Rachel").addFather("Hanna", "Loren")
                .addMother("Loren", "Calanit").addFather("Loren", "Moky")
                .addFather("Omer", "Nadav");

                CHECK_THROWS(T.remove("Omri")); //try to remove the root --> exception

                CHECK((T.find("grandfather") == string("Nadav") || T.find("grandfather") == string("Loren")));

                CHECK(T.find("father") == string("Omer"));
        T.remove("Omer");
                CHECK_THROWS(T.find("father"));
                CHECK(T.find("grandfather") == string("Loren")); // Nadav has removed from the tree while removing Omer

                CHECK(T.find("great-grandmother") == string("Calanit"));
                CHECK(T.find("great-grandfather") == string("Moky"));
        T.remove("Calanit");
                CHECK_THROWS(T.find("great-grandmother"));
        T.remove("Loren");
                CHECK_THROWS(T.find("great-grandfather"));
                CHECK_THROWS(T.find(T.find("grandfather")));

        T.addFather("Hanna", "Nissan"); //removed Loren, sowe can add new father to Hanna now
                CHECK(T.find("grandfather") == string("Nissan"));
                CHECK(T.find("grandmother") == string("Rachel"));
    }






// -------------
// NETANEL TESTS
// -------------

    family::Tree *test_tree(){ // helper function for other tests
        family::Tree *T  = new family::Tree("Yosef"); // Yosef is the "root" of the tree (the youngest person).
                CHECK_NOTHROW(T->addFather("Yosef", "Yaakov"));   // Tells the tree that the father of Yosef is Yaakov.
                CHECK_NOTHROW(T->addMother("Yosef", "Rachel"));   // Tells the tree that the mother of Yosef is Rachel.
                CHECK_NOTHROW(T->addFather("Yaakov", "Isaac"));
                CHECK_NOTHROW(T->addMother("Yaakov", "Rivka"));
                CHECK_NOTHROW(T->addFather("Isaac", "Avraham"));
                CHECK_NOTHROW(T->addMother("Isaac", "Sara"));
                CHECK_NOTHROW(T->addFather("Avraham", "Terah"));

                CHECK_NOTHROW(T->addFather("Rivka", "Betuel"));
                CHECK_NOTHROW(T->addFather("Rachel", "Lavan"));
                CHECK_NOTHROW(T->addFather("Sara", "Haran"));
                CHECK_NOTHROW(T->addFather("Betuel", "Nahor"));
                CHECK_NOTHROW(T->addMother("Betuel", "Milca"));

        return T;
    }


    TEST_CASE("add father") {
        family::Tree t("Nati");
                CHECK_NOTHROW(t.addFather("Nati", "Nadav"));
                CHECK_NOTHROW(t.addFather("Nadav", "Haim"));
                CHECK_NOTHROW(t.addFather("Haim", "Dori"));

                CHECK(t.find("father") == "Nadav");
                CHECK(t.find("grandfather") == "Haim");
                CHECK(t.find("great-grandfather") == "Dori");

                CHECK_THROWS(t.addFather("Nati", "Nadav")); // Nati alredy have a father
                CHECK_THROWS(t.addFather("Nadav", "Avi")); // Nadav alredy have a father
                CHECK_THROWS(t.addFather("Dani", "Avi")); // Dani not exist
    }

    TEST_CASE("add mother") {
        family::Tree t("Nati");
                CHECK_NOTHROW(t.addMother("Nati", "Orit"));
                CHECK_NOTHROW(t.addMother("Orit", "Aliza"));
                CHECK_NOTHROW(t.addMother("Aliza", "Chyia"));

                CHECK(t.find("mother") == "Orit");
                CHECK(t.find("grandmother") == "Aliza");
                CHECK(t.find("great-grandmother") == "Chyia");

                CHECK_THROWS(t.addMother("Nati", "Orit")); // Nati alredy have a mother
                CHECK_THROWS(t.addMother("Orit", "Ruti")); // Orit alredy have a mother
                CHECK_THROWS(t.addMother("Dani", "Ruti")); // Dani not exist

    }

    TEST_CASE("add father & mother chaining") {
        family::Tree t("Nati");
                CHECK_NOTHROW(t.addMother("Nati", "bla").addFather("Nati", "plip").addMother("bla","qwerty"));
    }

    TEST_CASE("display") {
        family::Tree *T;
                CHECK_NOTHROW(T = test_tree());
                CHECK_NOTHROW(T->display());
        /*
        Need to print:
        Display Yosef tree. Father = up, mother = down.
                                /``Terah
                        /``Avraham
                /``Isaac
                                /``Haran
                        \_Sara
        /``Yaakov
                                /``Nahor
                        /``Betuel
                                \_Milca
                \_Rivka
    Yosef
                /``Lavan
        \_Rachel
        */

        delete T;
    }

    TEST_CASE("relation") {
        family::Tree *T;
                CHECK_NOTHROW(T = test_tree());

                CHECK(T->relation("Yosef") == "me");
                CHECK(T->relation("Yaakov") == "father");
                CHECK(T->relation("Isaac") == "grandfather");
                CHECK(T->relation("Avraham") == "great-grandfather");
                CHECK(T->relation("Terah") == "great-great-grandfather");
                CHECK(T->relation("Sara") == "great-grandmother");
                CHECK(T->relation("Rivka") == "grandmother");
                CHECK(T->relation("Betuel") == "great-grandfather");
                CHECK(T->relation("Rachel") == "mother");

                CHECK(T->relation("Lavan") == "grandfather");
                CHECK(T->relation("Haran") == "great-great-grandfather");
                CHECK(T->relation("Nahor") == "great-great-grandfather");
                CHECK(T->relation("Milca") == "great-great-grandmother");

        delete T;
    }

    TEST_CASE("find") {
        family::Tree *T;
                CHECK_NOTHROW(T = test_tree());

                CHECK(T->find("me") == "Yosef");
                CHECK(T->find("father") == "Yaakov");
                CHECK(T->find("mother") == "Rachel");

        string grandfather;
                CHECK_NOTHROW(grandfather = T->find("grandfather"));
                CHECK((grandfather == "Isaac" ||
                       grandfather == "Lavan"));

                CHECK(T->find("grandmother") == "Rivka");

        string great_grandfather;
                CHECK_NOTHROW(great_grandfather = T->find("great-grandfather"));
                CHECK((great_grandfather == "Avraham" ||
                       great_grandfather == "Betuel"));

                CHECK(T->find("great-grandmother") == "Sara");

        string great_great_grandfather;
                CHECK_NOTHROW(great_great_grandfather = T->find("great-great-grandfather"));
                CHECK((great_great_grandfather == "Terah" ||
                       great_great_grandfather == "Haran" ||
                       great_great_grandfather == "Nahor"));

                CHECK(T->find("great-great-grandmother") == "Milca");

                CHECK_THROWS(T->find("brother")); // not define
                CHECK_THROWS(T->find("great-great-great-grandfather")); // not exist
                CHECK_THROWS(T->find("Sara")); // not a rilation
        delete T;
    }



    TEST_CASE("remove function") {
        family::Tree *T;
                CHECK_NOTHROW(T = test_tree());

                CHECK_THROWS(T->remove("Yosef")); // cant remove root

                CHECK_THROWS(T->remove("Dani")); // cant remove unexist

                CHECK_NOTHROW(T->remove("Betuel"));

                CHECK(T->relation("Betuel") == "unrelated");
                CHECK(T->relation("Nahor") == "unrelated");
                CHECK(T->relation("Milca") == "unrelated");

                CHECK_THROWS(T->remove("Betuel")); // already removed
                CHECK_THROWS(T->remove("Nahor")); // already removed
                CHECK_THROWS(T->remove("Milca")); // already removed


                CHECK_NOTHROW(T->remove("Haran"));
                CHECK(T->relation("Haran") == "unrelated");
                CHECK_THROWS(T->remove("Haran")); // already removed


                CHECK_NOTHROW(T->remove("Lavan"));
                CHECK(T->relation("Lavan") == "unrelated");
                CHECK_THROWS(T->remove("Lavan")); // already removed

                CHECK_NOTHROW(T->remove("Terah"));
                CHECK(T->relation("Terah") == "unrelated");
                CHECK_THROWS(T->remove("Terah")); // already removed

                CHECK_NOTHROW(T->remove("Sara"));
                CHECK(T->relation("Sara") == "unrelated");
                CHECK_THROWS(T->remove("Sara")); // already removed

                CHECK_NOTHROW(T->remove("Avraham"));
                CHECK(T->relation("Avraham") == "unrelated");
                CHECK_THROWS(T->remove("Avraham")); // already removed

                CHECK_NOTHROW(T->remove("Rivka"));
                CHECK(T->relation("Rivka") == "unrelated");
                CHECK_THROWS(T->remove("Rivka")); // already removed

                CHECK_NOTHROW(T->remove("Isaac"));
                CHECK(T->relation("Isaac") == "unrelated");
                CHECK_THROWS(T->remove("Isaac")); // already removed

                CHECK_NOTHROW(T->remove("Rachel"));
                CHECK(T->relation("Rachel") == "unrelated");
                CHECK_THROWS(T->remove("Rachel")); // already removed

                CHECK_NOTHROW(T->remove("Yaakov"));
                CHECK(T->relation("Yaakov") == "unrelated");
                CHECK_THROWS(T->remove("Yaakov")); // already removed

        delete T;
}
