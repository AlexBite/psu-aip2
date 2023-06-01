#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>

using namespace std;

// Вершина
struct Vertex
{
    int index;
    // дистанция от начальной вершины
    int distance;
};

// Компаратор для очереди с приоритетами
struct VertexComparator
{
    bool operator()(Vertex const& v1, Vertex const& v2) const
    {
        return v1.distance > v2.distance;
    }
};

// Ребро между вершинами
struct Edge
{
    // вершина, к которой ведёт ребро
    int destination;
    // вес (расстояние)
    int weight;
};

// Считать граф из файла.
// Требования к файлу:
// Первая строка - номера вершин, остальные строки - рёбра в формате (начальная вершина, конечная вершина, вес)
vector<vector<Edge>> readGraphFromFile(const string& filename, int& numVertices)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cerr << "Не удалось открыть файл: " << filename << endl;
        exit(1);
    }

    inputFile >> numVertices;

    vector<vector<Edge>> graph(numVertices);

    int source, destination, weight;
    while (inputFile >> source >> destination >> weight)
    {
        Edge edge;
        edge.destination = destination;
        edge.weight = weight;
        graph[source].push_back(edge);
    }

    inputFile.close();

    return graph;
}


pair<vector<int>, vector<int>> dijkstra(const vector<vector<Edge>>& graph, int startVertex)
{
    int numVertices = graph.size();
    // Расстояния от начальной вершины
    vector<int> distances(numVertices, numeric_limits<int>::max());
    // Индекс - вершина, значение - из какой вершины идти в вершину по индексу
    vector<int> previous(numVertices, -1);
    // Пройденные вершины
    vector<bool> visited(numVertices, false);

    distances[startVertex] = 0;

    // Используем priority queue с компаратором,
    // чтобы удобно получать вершину с минимальным расстоянием от начальной вершины
    priority_queue<Vertex, vector<Vertex>, VertexComparator> pq;

    // Инициализируем вершину
    Vertex initialVertex{startVertex, 0};
    pq.push(initialVertex);

    while (!pq.empty())
    {
        // Получить вершину с минимальной дистанцией
        // Благодаря VertexComparator pq.top() всегда вернёт такую вершину
        Vertex current = pq.top();
        pq.pop();

        int currentIndex = current.index;
        if (visited[currentIndex])
            continue;

        visited[currentIndex] = true;

        // Идём по всем дочерним вершинам (куда можем попасть из текущей вершины)
        for (const Edge& edge : graph[currentIndex])
        {
            int neighborIndex = edge.destination;
            int newDistance = distances[currentIndex] + edge.weight;

            // Обновляем данные о расстоянии и предыдущей вершине, если был найден более короткий путь
            if (newDistance < distances[neighborIndex])
            {
                distances[neighborIndex] = newDistance;
                previous[neighborIndex] = currentIndex;

                // Добавляем родителя в очередь приоритетов
                pq.push({neighborIndex, newDistance});
            }
        }
    }

    return {distances, previous};
}


vector<int> getShortestPath(const vector<int>& previous, int endVertex)
{
    vector<int> path;

    // Идём от конечной вершины к начальной,
    // чтобы восстановить маршрут
    int currentVertex = endVertex;
    while (currentVertex != -1)
    {
        path.push_back(currentVertex);
        currentVertex = previous[currentVertex];
    }

    // Реверс, чтобы путь шёл от начальной к конечной
    reverse(path.begin(), path.end());

    return path;
}

int main()
{
    system("chcp 65001");
    string filename;
    cout << "Введите название файла: ";
    cin >> filename;

    int numVertices;
    vector<vector<Edge>> graph = readGraphFromFile(filename, numVertices);

    int startVertex, endVertex;
    cout << "Задайте вершину начала пути: ";
    cin >> startVertex;
    cout << "Задайте вершину конца пути: ";
    cin >> endVertex;

    pair<vector<int>, vector<int>> result = dijkstra(graph, startVertex);
    vector<int> distances = result.first;
    vector<int> previous = result.second;

    int shortestDistance = distances[endVertex];
    vector<int> shortestPath = getShortestPath(previous, endVertex);

    cout << "Минимальное расстояние: " << shortestDistance << endl;
    cout << "Кратчайший путь: ";
    for (int vertex : shortestPath)
        cout << vertex << " ";
    
    cout << endl;

    return 0;
}
