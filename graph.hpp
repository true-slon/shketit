#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstddef>
#include <ostream>

class Graph
{
public:
  explicit Graph(size_t initialCapacity = 5);
  bool checkNode(size_t numNode) const;
  bool checkEdge(size_t node1, size_t node2) const;
  void addNode();
  void deleteNode(size_t numNode);
  void bfs(size_t start, std::ostream& out) const;
  void getShortestPath(size_t start, std::ostream& out) const;
  size_t getDiameter() const;
  void addEdge(size_t node1, size_t node2);
  void deleteEdge(size_t node1, size_t node2);
  ~Graph();
  Graph(const Graph& other) = delete;
  Graph& operator=(const Graph& other) = delete;
  Graph(Graph&& other) = delete;

private:
  size_t size;
  size_t capacity;
  bool** adjMatrix;
  void clean(bool** adjMatrix, size_t capacity);
  void resize(size_t capacity);
  void bfsPaths(size_t start, size_t* dist) const;
  bool hasCycle(size_t node, bool* visited, size_t parent) const;
  bool isTree() const;
};

#endif
