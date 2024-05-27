//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Polina Ustiuzhantseva <xustiup00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Polina Ustiuzhantseva
 *
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v
//       indexu
//============================================================================//

class EmptyHashMap : public testing::Test
{

    void SetUp()
    {
        TestHashMap = hash_map_ctor();
    }

    void TearDown()
    {

        if (TestHashMap != nullptr)
        {
            hash_map_dtor(TestHashMap);
        }
    }

protected:
    hash_map_t *TestHashMap;
};



class NonEmptyHashMap : public testing::Test
{

    void SetUp()
    {
        TestHashMap = hash_map_ctor();
        hash_map_put(TestHashMap, "Aoaoa", 1);
        hash_map_put(TestHashMap, "Brrrr", 2);
        hash_map_put(TestHashMap, "Ceda", 3);
        hash_map_put(TestHashMap, "Do", 4);
        hash_map_put(TestHashMap, "Eee", 5);
        hash_map_put(TestHashMap, "Feee", 6);
        hash_map_put(TestHashMap, "Ind", 7);
        hash_map_put(TestHashMap, "Xxx", 1);
    }

    void TearDown()
    {

        if (TestHashMap != nullptr)
        {
            hash_map_dtor(TestHashMap);
        }
    }

protected:
    hash_map_t *TestHashMap;
};

// --------------------------------------------------------vsechny funkce z white_box_cod.h---------------------------------------------------------------//

// Testovani konstruktoru
TEST(Constructor, ctorFunction)
{
    hash_map_t *TestHashMap = hash_map_ctor();
    EXPECT_TRUE(TestHashMap);
    EXPECT_EQ(TestHashMap->allocated, 8);
}


// // testovani destruktoru
TEST(Destructor, dctorFunction)
{
    hash_map_t *TestHashMap = hash_map_ctor();
    hash_map_dtor(TestHashMap);
    EXPECT_NE(TestHashMap->allocated, 8);
    //TODO pridat mazani pointeru
}


// testovani Clear funkce
TEST_F(NonEmptyHashMap, ClearFunction)
{
    hash_map_clear(TestHashMap);
    EXPECT_EQ(TestHashMap->used, 0);
    EXPECT_EQ(TestHashMap->first, nullptr);
    EXPECT_EQ(TestHashMap->last, nullptr);
}


//testovani, jestli misto nebylo rezervovano pri pridani polozky do prazdne hash tabulky
TEST_F(EmptyHashMap, reserveAndCapacityFunction) {
    hash_map_put(TestHashMap, "To", 45);
    EXPECT_EQ(hash_map_capacity(TestHashMap), 8);
}

//testovani, jestli se rezervovali dalsich 8 mist po pridani 9 polozky
TEST_F(NonEmptyHashMap, reserveAndCapacityFunction) {
    hash_map_put(TestHashMap, "To", 45);
    EXPECT_EQ(hash_map_capacity(TestHashMap), 16);
}


//testivani funkce Size pro prazdnou hash tabulku
TEST_F(EmptyHashMap, SizeFunction) {
    EXPECT_EQ(hash_map_size(TestHashMap), 0);
    hash_map_put(TestHashMap, "Retezec", 44);
    EXPECT_EQ(hash_map_size(TestHashMap), 1);
    hash_map_put(TestHashMap, "Retezec2", 34);
    hash_map_put(TestHashMap, "Eeeee", 34);
    EXPECT_EQ(hash_map_size(TestHashMap), 3);
}

//testovani funkce Size pro neprazdnou tabulku
TEST_F(NonEmptyHashMap, SizeFunction) {
    EXPECT_EQ(hash_map_size(TestHashMap), 8);
    hash_map_put(TestHashMap, "Retezec", 44);
    EXPECT_EQ(hash_map_size(TestHashMap), 9);
    hash_map_put(TestHashMap, "Read", 34);
    hash_map_put(TestHashMap, "Eeeee", 34);
    EXPECT_EQ(hash_map_size(TestHashMap), 11);
}


//testovani Contains funkce nad prazdnou tabulkou
TEST_F(EmptyHashMap, ContainsFunction) {
    EXPECT_EQ(hash_map_contains(TestHashMap, "Cer"), 0);
    EXPECT_EQ(hash_map_contains(TestHashMap, "Brrrr"), 0);
    EXPECT_EQ(hash_map_contains(TestHashMap, "Ragetbuklgios"), 0);
}

//testovani Contains funkce nad neprazdnou tabulkou
TEST_F(NonEmptyHashMap, ContainsFunction) {
    EXPECT_TRUE(hash_map_contains(TestHashMap, "Feee") != false);
    EXPECT_TRUE(hash_map_contains(TestHashMap, "Aoaoa") != false);
    EXPECT_EQ(hash_map_contains(TestHashMap, "NotFound"), false);
}


//Testovani Put funkce nad prazdnou tabulkou
TEST_F(EmptyHashMap, PutFunction) {
    EXPECT_NO_THROW(hash_map_put(TestHashMap, "Vvvvm", 28));
    EXPECT_EQ(hash_map_put(TestHashMap, "Index", 28), 0); //O = OK, tj. uspesne vlozeni
    EXPECT_EQ(hash_map_put(TestHashMap, "Index", 28), 4);
}

// Testovani Put funkce nad neprazdnou tabulkou
TEST_F(NonEmptyHashMap, PutFunction) {
    EXPECT_EQ(hash_map_put(TestHashMap, "Ind", 71), 4); 
    EXPECT_EQ(hash_map_put(TestHashMap, "Vvvv", 28), 0);
    EXPECT_EQ(hash_map_put(TestHashMap,"Bluhbluh", 111), 0);
}


//Testovani Get funkce nad prazdnou tabulkou
TEST_F(EmptyHashMap, GetFunction) {
    int value;
    EXPECT_EQ(hash_map_get(TestHashMap, "Ind", &value), 3);
}

//Testovani Get funkce nad neprazdnou tabulkou
TEST_F(NonEmptyHashMap, GetFunction) {
    int value;
    EXPECT_EQ(hash_map_get(TestHashMap, "Aoaoa", &value), 0);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(hash_map_get(TestHashMap, "BluhBluh", &value), 3);
}


//Testovani funkce Pop nad prazdnou tabulkou
TEST_F(EmptyHashMap, PopFunction) {
    int value;
    EXPECT_EQ(hash_map_pop(TestHashMap, "AAAA", &value), 3);
    EXPECT_EQ(hash_map_pop(TestHashMap, "FEEEE", &value), 3);
}

//Testovani funkce Pop nad neprazdnou tabulkou
TEST_F(NonEmptyHashMap, PopFunction) {
    int value;
    EXPECT_EQ(hash_map_pop(TestHashMap, "Aoaoa", &value), 0);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(hash_map_contains(TestHashMap, "Aoaoa"), 0);
    EXPECT_EQ(hash_map_pop(TestHashMap, "Feee", &value), 0);
    EXPECT_EQ(value, 6);
    EXPECT_EQ(hash_map_contains(TestHashMap, "Feee"), 0);
}


//Testovani funkce 
TEST_F(EmptyHashMap, RemoveFunction) {
    EXPECT_EQ(hash_map_remove(TestHashMap, "Eee"), 3);
    EXPECT_EQ(hash_map_remove(TestHashMap, "Vv"), 3);
}

TEST_F(NonEmptyHashMap, RemoveFunction) {
    EXPECT_EQ(hash_map_remove(TestHashMap, "Feee"), 0);
    EXPECT_EQ(hash_map_contains(TestHashMap, "Feee"), 0);
    EXPECT_EQ(hash_map_remove(TestHashMap, "Vv"), 3);
}






/*** Konec souboru white_box_tests.cpp ***/

