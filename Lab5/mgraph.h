#ifndef MGRAPH_H
#define MGRAPH_H

#include <cassert>
#include <QDebug>

#include "Graph.h"
#include "random.h"

class LGraph;

class MGraph : Graph
{
private:
    std::vector<std::vector<int*>> _matrix;
    int _nodes;
    int _edges;
    bool _directed;
    bool _weighed;

    void _addEdge(const int& fnode, const int& tnode, const int& weight, const bool& increment = true);
    void _removeOneWays();
    void _equateWeights();
    void _fill();
    int _firstNeighbour(int row, int max = -1) const;
    int _furthestNeighbour(int row, int max = -1) const;
    [[nodiscard]] std::vector<int> _neighboursWithWeight(int row, int weight) const;
    [[nodiscard]] std::vector<int> _descendingNeighbours(int row) const;

public:
    MGraph();
    explicit MGraph(int nodes, int edges = 0, bool directed = false, bool weighted = false);
    explicit MGraph(const LGraph& lGraph);
    ~MGraph();

//    void build(const LGraph& lgraph);
    void addNode() override;
    void addEdge(const int& fnode, const int& tnode) override;
    void addEdge(const int& fnode, const int& tnode, const int& weight) override;
    void eraseEdge(const int& fnode, const int& tnode) override;
    void eraseEdges() override;

    void print() const override;

    void directed(const bool& directed) override;
    void weighted(const bool &weighted) override;

    void dfs(const int& snode) const;
    void dfs(const int& snode, bool* visited, bool byWeight = false) const;

    void bfs(const int& snode) const;
    void bfs(const int& snode, bool* visited, bool byWeight = false) const;

    int nodes() const override;
    int edges() const override;
    bool directed() const override;
    bool weighted() const override;
    bool empty() const override;

};

#endif // MGRAPH_H