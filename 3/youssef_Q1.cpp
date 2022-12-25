#include <iostream>


/////////////////////////////////////////////////////////// WEIGHTED_GRAPH CLASS ///////////////////////////////////////////////////////////
class WeightedGraph
{
    int m_numVertices;
    int** m_graph;
    const int INFINITY = 999999999;
    
public:
    WeightedGraph(int** graph, int vertices) {
        this->m_graph = graph;
        this->m_numVertices = vertices;
    }

    void primMST();
    friend std::ostream& operator << (std::ostream &out, WeightedGraph &graph);

private:
    int minimumKey(const int key[], const bool visited[]) const;
    void displayMinSpanningTree(int parent[]);
    void display();

};



void WeightedGraph::primMST() {
    int parent[m_numVertices]; // stores parent of node
    bool visited[m_numVertices]; // stores the visited vertices so far
    int key[m_numVertices]; // stores the minimum weights found so far

    for (int i = 0; i < m_numVertices; ++i) { // set visited all to false and keys to infinity
        visited[i] = false;
        key[i] = INFINITY;
    }

    // choosing the first vertex
    parent[0] = -1;
    key[0] = 0;

    for (int i = 0; i < m_numVertices; ++i)
    {
        int minKeyIndex = minimumKey(key, visited); // get the smallest key which vertex has not been visited
        visited[minKeyIndex] = true; // mark as vertex as visited

        for (int j = 0; j < m_numVertices; ++j) {
            if (m_graph[minKeyIndex][j] > 0 && m_graph[minKeyIndex][j] < key[j] && !visited[j]) // if the weight less than the key value present and is greater than 0
            {
                key[j] = m_graph[minKeyIndex][j];
                parent[j] = minKeyIndex;
            }
        }
    }

//    for (int i = 0; i < m_numVertices; ++i) {
//        std::cout << parent[i] << " ";
//    }
    displayMinSpanningTree(parent);
}



int WeightedGraph::minimumKey(const int key[], const bool visited[]) const {
    int min = INFINITY;
    int index;
    for (int i = 0; i < m_numVertices ; ++i) {
        if (key[i] < min && !visited[i])
        {
            min = key[i];
            index = i;
        }
    }
    return index;
}



void WeightedGraph::displayMinSpanningTree(int *parent) {
    int minSpanningTreeSum = 0;
    for (int i = 1; i < m_numVertices; ++i) {
        minSpanningTreeSum += m_graph[i][parent[i]];
        std::cout << "Edge:\t(" << parent[i] << " --- " << i << ")" << "\tWeight: " << m_graph[i][parent[i]] << '\n';
    }
    std::cout << "Sum of minimum spanning tree is: " << minSpanningTreeSum;
}





void WeightedGraph::display() {
    std::cout << "   ";
    for (int i = 0; i < m_numVertices; ++i) {
        std::cout  << i +1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < m_numVertices; ++i) {
        std::cout  << i +1 << "  ";
        for (int j = 0; j < m_numVertices; ++j) {
            std::cout << m_graph[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


std::ostream &operator<<(std::ostream &out, WeightedGraph &graph) {
    graph.display();
    return out;
}

/////////////////////////////////////////////////////////// WEIGHTED_GRAPH CLASS ///////////////////////////////////////////////////////////












//utility functions and variables.



const int VERTICES = 7;

int** initMatrix(int** matrix, int size){
    matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i] = new int[size];
        }
    }
    return matrix;
}

int** setMatrix(int** matrix, int size)
{
    for (int i = 0; i < size ; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}



int main() {
    int **graph;
    graph = initMatrix(graph, VERTICES);
    graph = setMatrix(graph, VERTICES);



    // assignment test case
    graph[0][1] = 2;
    graph[0][2] = 4;
    graph[0][3] = 1;

    graph[1][0] = 2;
    graph[1][3] = 3;
    graph[1][4] = 10;

    graph[2][0] = 4;
    graph[2][3] = 2;
    graph[2][5] = 5;

    graph[3][0] = 1;
    graph[3][1] = 3;
    graph[3][2] = 2;
    graph[3][3] = 0;
    graph[3][4] = 7;
    graph[3][5] = 8;
    graph[3][6] = 4;

    graph[4][1] = 10;
    graph[4][3] = 7;
    graph[4][6] = 6;

    graph[5][2] = 5;
    graph[5][3] = 8;
    graph[5][6] = 1;

    graph[6][3] = 4;
    graph[6][4] = 6;
    graph[6][5] = 1;



    WeightedGraph weightedGraph(graph, VERTICES);
    weightedGraph.primMST();

}
