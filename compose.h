#pragma once

#include "concepts.h"
#include "iter.h"

template<typename GType> requires Graph<GType>
class Compose {
private:
    GType &graph;
    size_t root;
public:
    Compose(GType &g, size_t r) :
        graph(g), root(r) {};

    template<typename T>
    requires Functor<typename GType::VType, T>
    void Call(T value) {
        auto NewRoot = BFS(graph, root);
        for (auto it = NewRoot.end() - 1; it != NewRoot.begin() - 1; --it) {
            (*it)(value);
        }
    }
};