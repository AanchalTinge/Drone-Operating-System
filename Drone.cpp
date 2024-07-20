#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <thread>
#include <mutex>
#include <algorithm> // Add this line for std::reverse

using namespace std;

// Base class for drone operations
class DroneOperation {
public:
    virtual void execute() = 0;
};

class Takeoff : public DroneOperation {
public:
    void execute() override {
        cout << "Drone is taking off..." << endl;
    }
};

class Land : public DroneOperation {
public:
    void execute() override {
        cout << "Drone is landing..." << endl;
    }
};

class ReturnToHome : public DroneOperation {
public:
    void execute() override {
        cout << "Drone is returning to home..." << endl;
    }
};

class Failure : public DroneOperation {
public:
    void execute() override {
        cout << "Drone has encountered a failure..." << endl;
    }
};

// Survey class
class Survey : public DroneOperation {
public:
    void execute() override {
        cout << "Drone is surveying the area..." << endl;
    }
};

// MissionPlanning class
class MissionPlanning {
    struct Edge {
        int node;
        int cost;
    };

    vector<vector<Edge>> graph;
    int numNodes;

public:
    MissionPlanning(int nodes) : numNodes(nodes) {
        graph.resize(nodes);
    }

    void addEdge(int u, int v, int cost) {
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost});
    }

    vector<int> findShortestPath(int start, int end) {
        vector<int> dist(numNodes, INT_MAX);
        vector<int> prev(numNodes, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            for (const auto &edge : graph[current]) {
                int next = edge.node;
                int weight = edge.cost;
                if (dist[current] + weight < dist[next]) {
                    dist[next] = dist[current] + weight;
                    prev[next] = current;
                    pq.push({dist[next], next});
                }
            }
        }

        vector<int> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end()); // Fix: Add the std::reverse function call

        return path;
    }

    void executePath(int start, int end) {
        vector<int> path = findShortestPath(start, end);
        cout << "Path from " << start << " to " << end << ": ";
        for (int i : path) {
            cout << i << " ";
        }
        cout << endl;
    }
};

// Drone controller
class DroneController {
    DroneOperation *takeoff;
    DroneOperation *land;
    DroneOperation *returnToHome;
    DroneOperation *survey;
    MissionPlanning *missionPlanning;
    mutex mtx;

public:
    DroneController(MissionPlanning *mp) {
        takeoff = new Takeoff();
        land = new Land();
        returnToHome = new ReturnToHome();
        survey = new Survey();
        missionPlanning = mp;
    }

    ~DroneController() {
        delete takeoff;
        delete land;
        delete returnToHome;
        delete survey;
    }

    void executeTakeoff() {
        lock_guard<mutex> lock(mtx);
        takeoff->execute();
    }

    void executeLand() {
        lock_guard<mutex> lock(mtx);
        land->execute();
    }

    void executeReturnToHome() {
        lock_guard<mutex> lock(mtx);
        returnToHome->execute();
    }

    void executeSurvey() {
        lock_guard<mutex> lock(mtx);
        survey->execute();
    }

    void executeMission(int start, int end) {
        thread t1(&DroneController::executeTakeoff, this);

        // Plan the mission
        missionPlanning->executePath(start, end);

        // Survey the area
        thread t2(&DroneController::executeSurvey, this);

        t1.join();
        t2.join();

        // Return to home
        executeReturnToHome();

        // Land the drone
        executeLand();
    }
};

// Main function
int main() {
    int nodes = 100;
    MissionPlanning mp(nodes);

    // Add edges to the graph (for demonstration purposes)
    for (int i = 0; i < nodes; ++i) {
        for (int j = i + 1; j < nodes; ++j) {
            int cost = rand() % 10 + 1; // Random cost between 1 and 10
            mp.addEdge(i, j, cost);
        }
    }

    DroneController dc(&mp);
    dc.executeMission(0, 99);

    return 0;
}
