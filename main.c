#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Queue structure for BFS
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// Create a new queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important to handle the circular queue
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Check if the queue is full
int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Enqueue an item to the queue
void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Dequeue an item from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// DFS function
void DFS(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int vertex, int visited[MAX_VERTICES]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < vertices; ++i) {
        if (graph[vertex][i] && !visited[i]) {
            DFS(graph, vertices, i, visited);
        }
    }
}

// BFS function
void BFS(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int source) {
    struct Queue* queue = createQueue(MAX_VERTICES);

    int visited[MAX_VERTICES] = {0};
    enqueue(queue, source);
    visited[source] = 1;

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                enqueue(queue, i);
                visited[i] = 1;
            }
        }
    }

    free(queue->array);
    free(queue);
}

int main() {
    int choice;
    int vertices, edges, source;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    do {
        printf("\nChoose an option:\n");
        printf("1: Depth-First Search (DFS)\n");
        printf("2: Breadth-First Search (BFS)\n");
        printf("3: Restart with a New Graph\n");
        printf("4: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &vertices);

                printf("Enter the number of edges: ");
                scanf("%d", &edges);

                printf("Enter the edges (vertex pairs):\n");
                for (int i = 0; i < edges; ++i) {
                    int u, v;
                    scanf("%d %d", &u, &v);
                    graph[u][v] = 1;
                    graph[v][u] = 1; // Assuming an undirected graph
                }

                printf("Enter the source vertex: ");
                scanf("%d", &source);

                printf("DFS starting from vertex %d: ", source);
                // Array to keep track of visited vertices
                int visitedDFS[MAX_VERTICES] = {0};
                DFS(graph, vertices, source, visitedDFS);
                break;

            case 2:
                printf("Enter the source vertex: ");
                scanf("%d", &source);

                printf("BFS starting from vertex %d: ", source);
                // Array to keep track of visited vertices
                int visitedBFS[MAX_VERTICES] = {0};
                BFS(graph, vertices, source);
                break;

            case 3:
                // Reset the graph for a new session
                for (int i = 0; i < MAX_VERTICES; ++i) {
                    for (int j = 0; j < MAX_VERTICES; ++j) {
                        graph[i][j] = 0;
                    }
                }
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}
