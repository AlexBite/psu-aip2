#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstdlib>

using namespace std;

struct Vertex {
    int value;
    vector<Vertex*> neighbors;
};

Vertex* breadthFirstSearch(Vertex* start, int target, int numVertices) {
    queue<Vertex*> queue;
    vector<bool> visited(numVertices, false);

    queue.push(start);
    visited[start->value] = true;

    while (!queue.empty()) {
        Vertex* current = queue.front();
        queue.pop();

        if (current->value == target) {
            return current;
        }

        for (Vertex* neighbor : current->neighbors) {
            if (!visited[neighbor->value]) {
                queue.push(neighbor);
                visited[neighbor->value] = true;
            }
        }
    }

    return nullptr;
}

int main() {
    system("chcp 65001");  // Set console code page to UTF-8

    ifstream inputFile("graph.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл с графом." << endl;
        return 1;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    vector<Vertex> vertices(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int sourceIndex, targetIndex;
        inputFile >> sourceIndex >> targetIndex;

        vertices[sourceIndex].value = sourceIndex;
        vertices[targetIndex].value = targetIndex;

        vertices[sourceIndex].neighbors.push_back(&vertices[targetIndex]);
        vertices[targetIndex].neighbors.push_back(&vertices[sourceIndex]);
    }

    inputFile.close();

    int targetValue;
    cout << "Введите значение вершины для поиска: ";
    cin >> targetValue;

    Vertex* startVertex = &vertices[0];
    Vertex* foundVertex = breadthFirstSearch(startVertex, targetValue, numVertices);

    if (foundVertex != nullptr) {
        cout << "Адрес вершины: " << foundVertex << endl;
    } else {
        cerr << "Вершина не найдена в графе." << endl;
    }

    return 0;
}
