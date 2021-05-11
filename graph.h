#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
//#include <list> -- "list" on vectors is just easier:(
#include <optional>
#include <utility>
#include <vector>

template<class VType, class EType>
class AMGraph {
private:
    using ETypeInit = std::optional<EType>; //check whether it's initialized or not
    std::vector<VType> verts{};
    std::vector<std::vector<ETypeInit>> edges{};
public:
    VType &Vertex(size_t i) { return verts[i]; }

    EType& Edge(size_t first, size_t second) { return *(edges[x][y]); }

    size_t VertexCount() { return verts.size(); }

    void AddVertex(VType v, size_t i) {
        verts.insert(verts.begin() + i, std::move(v));
        //seems like insert is the fastest way to do this. At least the fastest to write :p

        //changing edges{}: for all already inserted vertices initialize i-th edge and add new vector to the i-th place of edges{}
        for (auto& edge : edges)
            edge.insert(edge.begin() + i, std::nullopt);

        std::vector<ETypeInit> edge(verts.size(), std::nullopt);
        edges.insert(edges.begin + i, edge);
        //return vertices[i];
        //std::cout << "Vertex inserted!\n";
    }

    void DeleteVertex(size_t i) {
        //doing mostly the same thing in a reversed order

        edges.erase(edges.begin() + i);
        for (auto& edge : edges)
            edge.erase(edge.begin() + i);

        verts.erase(verts.begin() + i);
        //std::cout << "Vertex deleted!\n";
    }

    bool IsEdge(size_t first, size_t second) { return bool(edges[x][y]); }

    void AddEdge(EType edge, size_t first, size_t second) {
        edges[first][second] = std::make_optional(std::move(edge)); //kinda magic :O
        //return *(edges[first][second]);
        //std::cout << "Edge inserted!\n";
    }

    void DeleteEdge(size_t first, size_t second) { 
        edges[first][second] = std::nullopt;
        //std::cout << "Edge deleted!\n";
    }

    auto Adj(size_t i) {
        if (i < verts.size()) {
            std::vector<VType> vec;
            for (auto &edge : edges[i]) {
                for (int j = 0; j < i; ++j) {
                    if (edge[j])
                        vec.push_back(edge[j]);
                }
            }
            return vec;
        }
        else
            return;
    }
};

template<class VType, class EType>
class ALGraph {
private:
    using ETypeInit = std::pair<size_t, EType>;
    std::vector<VType> verts{};
    std::vector<std::vector<ETypeInit>> edges{};
public:
    VType& Vertex(size_t i) { return verts[i]; }

    size_t VertexCount() { return verts.size(); }

    void AddVertex(VType v, size_t i) {
        verts.insert(verts.begin() + i, std::move(v));
        std::vector<ETypeInit> edge{};
        edges.insert(edges.begin() + i, edge);
        //std::cout << "Vertex inserted!\n";
    }

    void DeleteVertex(size_t i) {
        edges.erase(edges.begin() + i);
        for (auto &edge : edges) {
            for (auto &pair : edge) {
                if (pair.first == i) {
                    edge.erase(pair);
                }
            }
        }
        verts.erase(edges.begin() + i);
        //std::cout << "Vertex deleted!\n";
    }

    bool IsEdge(size_t first, size_t second) {
        for (auto& pair : edges[first]) {
            if (pair.first == second) {
                return true;
            }
        }
        return false;
    }

    void AddEdge(EType edge, size_t first, size_t second) {
        edges[first].push_back({second, std::move(edge});
        //std::cout << "Edge inserted!\n";
    }

    void DeleteEdge(size_t first, size_t second) {
        for (auto& pair : edges[first]) {
            if (pair.first == second) {
                edges[first].erase(pair);
            }
        }
        //std::cout << "Edge deleted!\n";
    }

    auto Adj(size_t i) {
        return edges[i] | std::views::transform([](auto i) { return i.first; }); //Спасибо @OperatorGK за подсказку!
    }
};

//Compile-time graph was not implemented as I was stuck with contexpr versions of the functions:(