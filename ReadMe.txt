Простая библиотека для работы с графами
Спасибо @OperatorGK за помощь!
Для использования нужно заинклюдить файл lib.h
Требования: компилятор должен поддерживать c++20

Что умеет:
concepts.h описывает концепты, которые использует библиотека, то есть выражения типа f(x) (Functor), f(x, y) (BiFunctor), bool f(x) (Predicate).
Graph<GType> описывает доступные графы и их интерфейсы.
У графов есть типы VType для вершин и EType для рёбер и методы VertexCount(), Vertex(index), Edge(first vertex, second vertex), 
IsEdge(first vertex, second vertex).

graph.h
Есть два типа графов -- ALGraph на листе смежности и AMGraph на матрице смежности. Графы ориентированные, поддерживают методы:
AddEdge(first vertex, second vertex), DeleteEdge(first vertex, second vertex), AddVertex(index), DeleteVertex(index).
Графы должны быть CopyConstructible для копирования, вершины и рёбра должны поддерживать move-семантику.

iter.h
Vertices<GType> BFS позволяет делать обход в глубину.

compose.h
Реализует компоновщик. Вершины -- функторы, в конструктор передаются граф и корневой объект. Имеет метод Call<T><T value>, который вызывает каждый функтор в иерархии.