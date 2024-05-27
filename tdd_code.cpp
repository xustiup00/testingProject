//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Polina Ustiuzhantseva <xustiup00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"

Graph::Graph()
{
    allNodes = {};
    allEdges = {};
    allEdgesCount = 0;
    allNodesCount = 0;
}

Graph::~Graph()
{
    while (!allNodes.empty())
    {
        Node *lastNode = allNodes.back();
        allNodes.pop_back();
        delete lastNode;
    }

    allEdges.clear();
}

std::vector<Node *> Graph::nodes()
{
    return allNodes;
}

std::vector<Edge> Graph::edges() const
{
    return allEdges;
}

Node *Graph::addNode(size_t nodeId)
{

    for (auto everyNode : allNodes)
    {
        // pokud uzel jiz existuje
        if (everyNode->id == nodeId)
        {
            return nullptr;
        }
    }
    struct Node *newNode = (struct Node *)malloc(sizeof(Node));
    if (newNode == nullptr)
    {
        return nullptr;
    }
    newNode->id = nodeId;
    newNode->color = 0;
    allNodes.push_back(newNode);
    allNodesCount++;
    return newNode;
}

bool Graph::addEdge(const Edge &edge)
{
    // Pokud je to smycka, vrati false
    if (edge.a == edge.b)
    {
        return false;
    }

    // pokud hrana jiz existuje, vrati false
    for (auto everyEdge : allEdges)
    {
        if (everyEdge.operator==(edge))
        {
            return false;
        }
    }

    addNode(edge.a);
    addNode(edge.b);

    allEdges.push_back(edge);
    allEdgesCount++;
    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge> &edges)
{
    for (auto &edge : edges)
    {
        this->addEdge(edge);
    }
}

Node *Graph::getNode(size_t nodeId)
{
    for (auto everyNode : allNodes)
    {
        if (everyNode->id == nodeId)
        {
            return everyNode;
        }
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge &edge) const
{
    for (auto everyEdge : allEdges)
    {
        if (everyEdge.operator==(edge))
        {
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId)
{
    bool exists = false;
    for (auto everyNode = allNodes.begin(); everyNode != allNodes.end(); everyNode++)
    {
        if ((*everyNode)->id == nodeId)
        {
            exists = true;
            for (auto everyEdge = allEdges.begin(); everyEdge != allEdges.end();)
            {
                if (everyEdge->a == nodeId || everyEdge->b == nodeId)
                {
                    allEdges.erase(everyEdge);
                    allEdgesCount--;
                }
                else
                {
                    everyEdge++;
                }
            }
            allNodesCount--;
            delete (*everyNode);
            allNodes.erase(everyNode);
        }
    }
    if (exists == false)
    {
        throw std::out_of_range("Out of range");
    }
}

void Graph::removeEdge(const Edge &edge)
{
    bool edgeExists = false;
    for (auto everyEdge = allEdges.begin(); everyEdge != allEdges.end(); everyEdge++)
    {
        if (edge.operator==(*everyEdge))
        {
            allEdges.erase(everyEdge);
            allNodesCount--;
            edgeExists = true;
        }
    }
    if (edgeExists == false)
    {
        throw std::out_of_range("Out of range");
    }
}

size_t Graph::nodeCount() const
{
    return allNodesCount;
}

size_t Graph::edgeCount() const
{
    return allEdgesCount;
}

size_t Graph::nodeDegree(size_t nodeId) const
{
    bool exists = false;
    int countOfDegree = 0;
    for (auto everyNode : allNodes)
    {
        if (everyNode->id == nodeId)
        {
            for (auto everyEdge : allEdges)
            {
                if (everyEdge.a == nodeId || everyEdge.b == nodeId)
                {
                    countOfDegree++;
                }
            }
            exists = true;
            return countOfDegree;
        }
    }
    if (exists == false)
    {
        throw std::out_of_range("Out of range");
    }
    return 0;
}

size_t Graph::graphDegree() const
{
    int max = 0, actualCount = 0;
    for (auto everyNode : allNodes)
    {
        for (auto everyEdge : allEdges)
        {
            if (everyNode->id == everyEdge.a || everyNode->id == everyEdge.b)
            {
                actualCount++;
            }
        }
        if (max < actualCount)
        {
            max = actualCount;
        }
        actualCount = 0;
    }
    return max;
}

void Graph::coloring()
{
    size_t maxColorNum = graphDegree() + 1;
    size_t actualColor = 1;
    for (auto everyNode : allNodes) {

        everyNode->color = actualColor;
        if (actualColor == maxColorNum) {
            actualColor = 1;
        }
        actualColor++;
    }
    
}

void Graph::clear()
{
    while (!allNodes.empty())
    {
        Node *lastNode = allNodes.back();
        allNodes.pop_back();
        delete lastNode;
    }

    allEdges.clear();
}

/*** Konec souboru tdd_code.cpp ***/
