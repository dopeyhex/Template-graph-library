������� ���������� ��� ������ � �������
������� @OperatorGK �� ������!
��� ������������� ����� ����������� ���� lib.h
����������: ���������� ������ ������������ c++20

��� �����:
concepts.h ��������� ��������, ������� ���������� ����������, �� ���� ��������� ���� f(x) (Functor), f(x, y) (BiFunctor), bool f(x) (Predicate).
Graph<GType> ��������� ��������� ����� � �� ����������.
� ������ ���� ���� VType ��� ������ � EType ��� ���� � ������ VertexCount(), Vertex(index), Edge(first vertex, second vertex), 
IsEdge(first vertex, second vertex).

graph.h
���� ��� ���� ������ -- ALGraph �� ����� ��������� � AMGraph �� ������� ���������. ����� ���������������, ������������ ������:
AddEdge(first vertex, second vertex), DeleteEdge(first vertex, second vertex), AddVertex(index), DeleteVertex(index).
����� ������ ���� CopyConstructible ��� �����������, ������� � ���� ������ ������������ move-���������.

iter.h
Vertices<GType> BFS ��������� ������ ����� � �������.

compose.h
��������� �����������. ������� -- ��������, � ����������� ���������� ���� � �������� ������. ����� ����� Call<T><T value>, ������� �������� ������ ������� � ��������.