//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Polina Ustiuzhantseva <xustiup00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Polina Ustiuzhantseva
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.

// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public testing::Test
{
protected:
    BinaryTree TestTree;
};

class NonEmptyTree : public testing::Test
{

    virtual void SetUp()
    {
        int nodeValues[] = {40, 28, 36, 44, 52, 100, 39, 12, 6, 70};
        for (auto value : nodeValues)
        {
            TestTree.InsertNode(value);
        }
    }

protected:
    BinaryTree TestTree;
};

class TreeAxioms : public testing::Test
{

    virtual void SetUp()
    {
        int nodeValues[] = {40, 28, 36, 44, 52, 100, 39, 12, 6, 70, 33, 44, 55, 111, 99, 88};
        for (auto value : nodeValues)
        {
            TestTree.InsertNode(value);
        }
    }

protected:
    BinaryTree TestTree;
};

// InsertNodeTest nad EmptyTree
TEST_F(EmptyTree, InsertNode)
{
    auto node = TestTree.InsertNode(5);
    Node_t *ptrNode = TestTree.FindNode(5);
    EXPECT_TRUE(node.first);
    EXPECT_EQ(node.second, ptrNode);
}

// DeleteNode test nad EmptyTree
TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(TestTree.DeleteNode(5));
}

// FindNode test nad EmptyTree
TEST_F(EmptyTree, FindNode)
{
    EXPECT_EQ(TestTree.FindNode(1), nullptr);
}

// InsertNode nad NonEmptyTree
TEST_F(NonEmptyTree, InsertNode)
{

    // testovani vlozeni uzlu, ktery neexistuje
    auto node1 = TestTree.InsertNode(1);
    Node_t *ptrNode1 = TestTree.FindNode(1);
    EXPECT_EQ(node1.first, true);
    EXPECT_EQ(node1.second, ptrNode1);

    // testovani vlozeni uzlu, ktery existuje
    Node_t *ptrNode2 = TestTree.FindNode(44);
    auto node2 = TestTree.InsertNode(44);
    EXPECT_EQ(node2.first, false);
    EXPECT_EQ(node2.second, ptrNode2);
}

// DeleteNode nad NonEmptyTree
TEST_F(NonEmptyTree, DeleteNode)
{
    EXPECT_TRUE(TestTree.DeleteNode(40));
    EXPECT_TRUE(TestTree.DeleteNode(70));

    EXPECT_FALSE(TestTree.DeleteNode(22));
}

// FindNode nad NonEmptyTree
TEST_F(NonEmptyTree, FindNode)
{
    EXPECT_EQ(TestTree.FindNode(20), nullptr);

    EXPECT_NE(TestTree.FindNode(52), nullptr);
}

// testovani prvni axiomy(vsechny listove uzly jsou cerne)
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t *> arrayOfLeafs{};
    TestTree.GetLeafNodes(arrayOfLeafs);
    for (auto leaf : arrayOfLeafs)
    {
        EXPECT_EQ(leaf->color, Color_t::BLACK);
    }
}

// testovani druhe axiomy(pokud je uzel cerveny, pak jsou jeho oba potomci cerne)
TEST_F(TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t *> arrayOfNodes{};
    TestTree.GetAllNodes(arrayOfNodes);
    for (auto node : arrayOfNodes)
    {
        if (node->color == RED)
        {
            EXPECT_EQ(node->pLeft->color, Color_t::BLACK);
            EXPECT_EQ(node->pRight->color, Color_t::BLACK);
        }
    }
}

// testovani treti axiomy(kazda cesta od kazdeho listoveho uzlu ke koreni obsahuje stejny pocet cernych uzlu)
TEST_F(TreeAxioms, Axiom3)
{
    std::vector<BinaryTree::Node_t *> arrayOfLeafs{};
    TestTree.GetLeafNodes(arrayOfLeafs);
    int Count = -1;
    for (auto node : arrayOfLeafs)
    {
        int blackNodesCount = 0;   //pocet cernych uzlu na aktualni ceste
        while (true)
        {
            if (node != nullptr)
            {
                if (node->color == BLACK)
                    blackNodesCount++;
                node = node->pParent;
            }
            else
            {
                if (Count = -1)
                {
                    Count = blackNodesCount;
                }
                else
                {
                    EXPECT_EQ(blackNodesCount, Count);
                }
                break;
            }
        }
    }
}

/*** Konec souboru black_box_tests.cpp ***/
