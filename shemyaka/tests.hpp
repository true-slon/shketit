#ifndef TESTS_HPP
#define TESTS_HPP

#include <iostream>
#include <iomanip>

#include "graph.hpp"

void basicTest()
{
  std::cout << "--Basic test started--\n";
  Graph graph(3);
  graph.addNode();
  graph.addNode();
  graph.addNode();
  std::cout << std::boolalpha << graph.checkNode(1) << " " << graph.checkNode(3) << "\n";
  graph.addEdge(1, 2);
  graph.addEdge(0, 2);
  std::cout << "Edges before resizing\n";
  std::cout << graph.checkEdge(1, 2) << " " << graph.checkEdge(0, 1) << "\n";
  graph.addNode();
  std::cout << "Edges after resizing\n";
  std::cout << graph.checkEdge(1, 2) << " " << graph.checkEdge(0, 1) << "\n";
  //graph.deleteNode(2);
  std::cout << "Edges after removal\n";
  std::cout << graph.checkEdge(1, 2) << " " << graph.checkEdge(0, 2) << "\n";
  std::cout << "--Basic test ended--\n";
}

void exceptionTest()
{
  std::cout << "--Exception test started--\n";
  try
  {
    Graph graph1(0);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  Graph graph;
  try
  {
    graph.checkEdge(0, 1);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  try
  {
    graph.deleteEdge(1, 0);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  std::cout << "--Exception test ended--\n";
}

void bfsTest()
{
  std::cout << "--BFS test started--\n";
  Graph graph;
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addEdge(0, 3);
  graph.addEdge(2, 1);
  graph.addEdge(3, 1);
  graph.addEdge(0, 2);
  graph.bfs(3, std::cout);
  try
  {
    graph.bfs(4, std::cout);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  std::cout << "--BFS test ended--\n";
}

void distTest()
{
  std::cout << "--Shortest path test started--\n";
  Graph graph;
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addEdge(0, 3);
  graph.addEdge(2, 1);
  graph.addEdge(3, 1);
  graph.addEdge(0, 2);
  graph.getShortestPath(2, std::cout);
  std::cout << "--Shortest path test ended--\n";
}

void diameterTest()
{
  std::cout << "--Tree diameter test started--\n";
  Graph graph;
  try
  {
    graph.getDiameter();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addEdge(0, 3);
  graph.addEdge(2, 1);
  graph.addEdge(3, 1);
  graph.addEdge(0, 2);
  try
  {
    graph.getDiameter();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  graph.deleteEdge(1, 3);
  std::cout << graph.getDiameter() << "\n";
  graph.addNode();
  graph.addEdge(4,2);
  try
  {
    graph.getDiameter();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  std::cout << "--Tree diameter test ended--\n";
}

void newTest()
{
  std::cout << "--newtest--\n";
  Graph graph;
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addNode();
  graph.addEdge(0,1);
  graph.addEdge(0,2);
  graph.addEdge(1,2);
  graph.addEdge(2,3);
  graph.addEdge(2,4);
  graph.addEdge(1,3);
  graph.bfs(3, std::cout);
  graph.getShortestPath(4, std::cout);
  try
  {
    graph.getDiameter();
  }
  catch (const std::exception& e)
  {
    std::cout << "ERROR: " << e.what() <<"\n";
  }
}

#endif
