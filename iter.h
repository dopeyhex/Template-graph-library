#pragma once

#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
#include <ranges>
#include <memory>
#include <queue>

#include "concepts.h"

template<typename GType> requires Graph<GType>
class Vertices {
private:
    GType &graph = nullptr;
    std::vector<size_t> inds{};
    Vertices(GType& graph, std::vector<size_t> ind) : graph(graph), inds(std::move(ind)) {}

public:
    class Iterator {
    private:
        Vertices* parent = nullptr;
        size_t pos = 0;

        Iterator(Vertices* par, size_t i) : parent(par), pos(i) {};

        friend Iterator Vertices::begin();

        friend Iterator Vertices::end();

    public:
        using reference_type = typename GType::VType&;
        using pointer_type = typename GType::VType*;

        Iterator() {};

        bool operator==(const Iterator& other) const {
            return (pos == other.pos) && (parent == other.parent);
        }

        reference_type operator*() {
            return parent->graph.Vertex(parent->inds[pos]);
        }

        pointer_type operator->() {
            return &parent->graph.Vertex(parent->inds[pos]);
        }

        Iterator& operator++() {
            ++pos;
            return *this;
        }

        Iterator operator++(int) {
            auto ret = *this;
            ++pos;
            return ret;
        }

        Iterator& operator--() {
            --pos;
            return *this;
        }

        Iterator operator--(int) {
            auto ret = *this;
            --pos;
            return ret;
        }

        Iterator& operator+=(size_t offset) {
            pos += offset;
            return *this;
        }

        Iterator& operator-=(size_t offset) {
            pos -= offset;
            return *this;
        }

        friend Iterator operator+(Iterator a, size_t n) {
            a += n;
            return a;
        }

        friend Iterator operator+(size_t n, Iterator a) {
            a += n;
            return a;
        }

        friend Iterator operator-(Iterator a, size_t n) {
            a -= n;
            return a;
        }

        friend Iterator operator-(size_t n, Iterator a) {
            a -= n;
            return a;
        }

        friend size_t operator-(Iterator a, Iterator b) {
            return a.pos - b.pos;
        }

        reference_type operator[](size_t n) {
            auto a = this + n;
            return *a;
        }


    };

    Vertices() {};

    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, inds.size());
    }

    friend Vertices BFS<>(GType& graph, size_t begin);

};

template<typename GType>
requires Graph<GType>
Vertices<GType> BFS(GType& graph, size_t begin) {
    std::vector<size_t> inds;
    std::vector<bool> visited(graph.VertexCount());
    std::queue<size_t> next;
    next.push(begin);

    while (!next.empty()) {
        auto v = next.front();
        next.pop();

        if (visited[v]) continue;
        visited[v] = true;
        inds.push_back(v);

        for (auto n : graph.Adj(v))
            next.push(n);
    }

    return {graph, inds};
}
