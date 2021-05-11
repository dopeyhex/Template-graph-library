#pragma once

#include <concepts>
#include <ranges>

template<class F, class T>
concept Functor = requires(F f, T x) {
    f(x);
};

template<class F, class T1, class T2>
concept BiFunctor = requires(F f, T1 x, T2 y) {
    f(x, y);
};

template<class F, class T>
concept Predicate = requires(F f, T x) {
    { f(x) } -> std::same_as<bool>;
};

template<class GType>
concept Graph = requires(GType graph, size_t first, size_t second) {
    typename GType::VType;
    typename GType::EType;
    { graph.VertexCount() } -> std::same_as<size_t>;
    { graph.Vertex(first) } -> std::same_as<typename GType::VType&>;
    { graph.IsEdge(first, second) } -> std::same_as<bool>;
    { graph.Edge(first, second) } -> std::same_as<typename GType::EType&>;
};