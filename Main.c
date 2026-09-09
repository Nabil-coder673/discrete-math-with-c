#include <stdio.h>
#include <string.h>


#define V 10
#define INF 99999

char places[V][50] = {
    "Cox's Bazar",
    "Himchari",
    "Inani Beach",
    "Saint Martin",
    "Bandarban",
    "Rangamati",
    "Sajek",
    "Sylhet",
    "Srimangal",
    "Dhaka"
};

int graph[V][V] = {0};

/* Function to find vertex with minimum distance */
int minDistance(int dist[], int visited[])
{
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/* Dijkstra Algorithm */
void dijkstra(int source)
{
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\n============================================\n");
    printf("Shortest Distances from %s\n", places[source]);
    printf("============================================\n");

    printf("%-20s %-15s\n", "Place", "Distance");

    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INF)
            printf("%-20s Not Reachable\n", places[i]);
        else
            printf("%-20s %d km\n", places[i], dist[i]);
    }
}

/* Find shortest distance between two places */
void shortestPath(int source, int destination)
{
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\n============================================\n");
    printf("Minimum Shortest Distance\n");
    printf("============================================\n");

    printf("Source      : %s\n", places[source]);
    printf("Destination : %s\n", places[destination]);

    if (dist[destination] == INF)
        printf("Destination is not reachable.\n");
    else
        printf("Minimum Distance = %d km\n", dist[destination]);
}

/* Display all tourist places */
void displayPlaces()
{
    printf("\n============================================\n");
    printf("Tourist Places\n");
    printf("============================================\n");

    for (int i = 0; i < V; i++)
    {
        printf("%d. %s\n", i + 1, places[i]);
    }
}

/* Display edges and weights */
void displayEdges()
{
    printf("\n============================================\n");
    printf("Edges and Weights\n");
    printf("============================================\n");

    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (graph[i][j] != 0)
            {
                printf("%-15s <--> %-15s = %d km\n",
                       places[i], places[j], graph[i][j]);
            }
        }
    }
}

/* Search tourist place */
int searchPlace()
{
    char search[30];

    printf("\nEnter tourist place name: ");
    getchar();
    fgets(search, sizeof(search), stdin);

    search[strcspn(search, "\n")] = '\0';

    for (int i = 0; i < V; i++)
    {
        if (strcasecmp(search, places[i]) == 0)
        {
            printf("\nPlace Found!\n");
            printf("Place  : %s\n", places[i]);
            printf("Vertex : %d\n", i);
            return i;
        }
    }

    printf("\nTourist place not found.\n");

    return -1;
}

/* Select place by vertex number */
int selectPlace(char message[])
{
    int choice;

    printf("\n%s\n", message);

    for (int i = 0; i < V; i++)
    {
        printf("%d. %s\n", i, places[i]);
    }

    printf("Enter vertex number: ");
    scanf("%d", &choice);

    if (choice < 0 || choice >= V)
    {
        printf("Invalid vertex number!\n");
        return -1;
    }

    return choice;
}

int main()
{
    /* -----------------------------------------
       Create Graph
       ----------------------------------------- */

    graph[0][1] = graph[1][0] = 15;
    graph[0][4] = graph[4][0] = 100;
    graph[0][9] = graph[9][0] = 390;

    graph[1][2] = graph[2][1] = 25;

    graph[2][3] = graph[3][2] = 60;
    graph[2][4] = graph[4][2] = 110;

    graph[3][9] = graph[9][3] = 450;

    graph[4][5] = graph[5][4] = 75;
    graph[4][6] = graph[6][4] = 160;

    graph[5][6] = graph[6][5] = 95;
    graph[5][9] = graph[9][5] = 310;

    graph[6][7] = graph[7][6] = 250;

    graph[7][8] = graph[8][7] = 80;
    graph[7][9] = graph[9][7] = 240;

    graph[8][9] = graph[9][8] = 190;

    int choice;

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("     TOURIST PLACE NAVIGATION SYSTEM\n");
        printf("============================================\n");

        printf("Number of Vertices : %d\n", V);

        int edgeCount = 0;

        for (int i = 0; i < V; i++)
        {
            for (int j = i + 1; j < V; j++)
            {
                if (graph[i][j] != 0)
                    edgeCount++;
            }
        }

        printf("Number of Edges    : %d\n", edgeCount);

        printf("\n--------------- MAIN MENU ----------------\n");

        printf("1. Display Tourist Places\n");
        printf("2. Search Tourist Place\n");
        printf("3. Display Edges and Weights\n");
        printf("4. Dijkstra - Shortest Distance from Source\n");
        printf("5. Find Shortest Path between Two Places\n");
        printf("6. Exit\n");

        printf("-------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displayPlaces();
                break;

            case 2:
                searchPlace();
                break;

            case 3:
                displayEdges();
                break;

            case 4:
            {
                int source;

                source = selectPlace(
                    "Select Source Tourist Place"
                );

                if (source != -1)
                {
                    dijkstra(source);
                }

                break;
            }

            case 5:
            {
                int source, destination;

                source = selectPlace(
                    "Select Source Tourist Place"
                );

                if (source == -1)
                    break;

                destination = selectPlace(
                    "Select Destination Tourist Place"
                );

                if (destination == -1)
                    break;

                shortestPath(source, destination);

                break;
            }

            case 6:
                printf("\nThank you for using Tourist Navigation System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        if (choice != 6)
        {
            printf("\nPress Enter to return to Main Menu...");
            getchar();
            getchar();
        }

    } while (choice != 6);

    return 0;
}