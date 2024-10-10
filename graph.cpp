#include "graph.hpp"

#include <utility>
#include <exception>
#include <iostream>
#include "queue.hpp"

Graph::Graph(size_t initialCapacity):
  capacity(initialCapacity),
  size(0)
{
  if (capacity == 0)
  {
    throw std::invalid_argument("ZERO CAPACITY");
  }
  try
  {
    adjMatrix = new bool*[capacity];
    for (int i = 0; i < capacity; ++i)
    {
      adjMatrix[i] = new bool[capacity];
      for (int j = 0; j < capacity; ++j)
      {
        adjMatrix[i][j] = false;
      }
    }
  }
  catch (...)
  {
    clean(adjMatrix, capacity);
    throw;
  }
}

bool Graph::checkNode(size_t node) const
{
  return node < size;
}

bool Graph::checkEdge(size_t node1, size_t node2) const
{
  if (node1 >= size || node2 >= size)
  {
    throw std::invalid_argument("INCORRECT NODE");
  }
  return adjMatrix[node1][node2];
}

void Graph::deleteNode(size_t node)
{
  if (node >= size)
  {
    throw std::invalid_argument("INCORRECT NODE");
  }

  for (size_t i = node; i < size-1; i++)
  {
    for (size_t j = 0; j < size; j++)
    {
      adjMatrix[i][j] = adjMatrix[i+1][j];
    }
    for (size_t j = 0; j < size; j++)
    {
      adjMatrix[j][i] = adjMatrix[j][i+1];
    }
  }
  size--;
}

void Graph::addNode()
{
  if (size == capacity)
  {
    resize(capacity*2);
  }
  //capacity*=2;
  size++;
}

void Graph::addEdge(size_t node1, size_t node2)
{
  if (node1 >= size || node2 >= size || node1 == node2)
  {
    throw std::invalid_argument("INCORRECT NODE");
  }
  adjMatrix[node1][node2] = true;
  adjMatrix[node2][node1] = true;
}

void Graph::deleteEdge(size_t node1, size_t node2)
{
  if (node1 >= size || node2 >= size)
  {
    throw std::invalid_argument("INCORRECT NODE");
  }
  adjMatrix[node1][node2] = false;
  adjMatrix[node2][node1] = false;
}

void Graph::bfs(size_t start, std::ostream& out) const
{
  if (start >= size)
  {
    throw std::invalid_argument("INCORRECT NODE");
  }
  bool* visited = new bool[size];
  for (size_t i = 0; i < size; ++i)
  {
    visited[i] = false;
  }

  QueueArray< size_t > queue(size);
  visited[start] = true;
  queue.enQueue(start);
  out << "BFS started: ";
  while (!queue.isEmpty())
  {
    size_t node = queue.deQueue();
    out << node << " ";
    for (size_t i = 0; i < size; ++i)
    {
      if (adjMatrix[node][i] && !visited[i])
      {
        visited[i] = true;
        queue.enQueue(i);
      }
    }
  }

  delete[] visited;
  out << "\n";
}

void Graph::getShortestPath(size_t start, std::ostream& out) const
{
  if (start >= size)
  {
    throw std::invalid_argument("INCORRECT NODE");
  }
  size_t* dist = new size_t[size];
  bfsPaths(start, dist);

  for (size_t i = 0; i < size; ++i)
  {
    if (dist[i] == size)
    {
      out << "Node " << i << " is not connected\n";
    }
    else
    {
      out << "Shortest path to node " << i << " is " << dist[i] << "\n";
    }
  }
  delete[] dist;
}

void Graph::bfsPaths(size_t start, size_t* dist) const
{
  bool* visited = new bool[size];
  for (size_t i = 0; i < size; ++i)
  {
    visited[i] = false;
    dist[i] = size;
  }
  QueueArray< size_t > queue(size);
  visited[start] = true;
  dist[start] = 0;
  queue.enQueue(start);

  while (!queue.isEmpty())
  {
    size_t node = queue.deQueue();
    for (size_t i = 0; i < size; ++i)
    {
      if (adjMatrix[node][i] && !visited[i])
      {
        dist[i] = dist[node] + 1;
        visited[i] = true;
        queue.enQueue(i);
      }
    }
  }

  delete[] visited;
}

size_t Graph::getDiameter() const
{
  if (size == 0)
  {
    throw std::invalid_argument("EMPTY GRAPH");
  }
  if (!isTree())
  {
    throw std::invalid_argument("NOT A TREE");
  }
  size_t res = 0;
  size_t* dist = new size_t[size];
  bfsPaths(0, dist);
  size_t maxDist = 0;
  for (size_t i = 0; i < size; ++i)
  {
    if (dist[i] > maxDist)
    {
      maxDist = dist[i];
      res = i;
    }
  }
  bfsPaths(res, dist);
  maxDist = 0;
  for (size_t i = 0; i < size; ++i)
  {
    if (dist[i] > maxDist)
    {
      maxDist = dist[i];
    }
  }
  delete[] dist;
  return maxDist;
}

bool Graph::hasCycle(size_t node, bool* visited, size_t parent) const
{
  visited[node] = true;
  for (int i = 0; i < size; ++i)
  {
    if (adjMatrix[node][i])
    {
      if (!visited[i])
      {
        if (hasCycle(i, visited, node))
        {
          return true;
        }
      }
      else if (i != parent)
      {
        return true;
      }
    }
  }
  return false;
}

bool Graph::isTree() const
{
  bool* visited = new bool[size];
  for (size_t i = 0; i < size; ++i)
  {
    visited[i] = false;
  }
  if (hasCycle(0, visited, size))
  {
    delete[] visited;
    return false;
  }
  for (size_t i = 0; i < size; ++i)
  {
    if (!visited[i])
    {
      delete[] visited;
      return false;
    }
  }
  delete[] visited;
  return true;
}

void Graph::clean(bool** adjMatrix, size_t capacity)
{
  if (!adjMatrix)
  {
    return;
  }
  for (size_t i = 0; i < capacity; i++)
  {
    delete[] adjMatrix[i];
  }
  delete[] adjMatrix;
  adjMatrix = nullptr;
}

void Graph::resize(size_t newCapacity)
{
  bool** newAdjMatrix = nullptr;
  try
  {
    newAdjMatrix = new bool*[newCapacity];
    for (size_t i = 0; i < newCapacity; ++i)
    {
      newAdjMatrix[i] = new bool[newCapacity];
      for (size_t j = 0; j < newCapacity; ++j)
      {
        if (i < size && j < size)
        {
          newAdjMatrix[i][j] = adjMatrix[i][j];
        }
        else
        {
          newAdjMatrix[i][j] = false;
        }
      }
    }
  }
  catch (const std::bad_alloc& e)
  {
    clean(newAdjMatrix, newCapacity);
    throw;
  }
  std::swap(adjMatrix, newAdjMatrix);
  clean(newAdjMatrix, capacity);
}

Graph::~Graph()
{
  clean(adjMatrix, capacity);
}
