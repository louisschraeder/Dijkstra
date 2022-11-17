#include <iostream>

#include "Dijkstra_pq.h"

using namespace std;

int main() {
    string file = "../USA-road-d.NY.gr";

    /*
    Dijkstra_pq dijkstra(file);
    dijkstra.load_graph();
    cout << "loaded" << endl;
    dijkstra.init(1);
    cout << "init" << endl;
    cout << "sequential" << endl;
    auto sbeging = chrono::system_clock::now();
    dijkstra.sequential();
    dijkstra.print(264346);
    auto stime = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - sbeging).count();
    cout << "\nDijkstra Sequential: " << stime << " ms" << endl;
     */

    Dijkstra_pq dijkstra(file);
    dijkstra.load_graph();
    cout << "loaded" << endl;
    dijkstra.init(1);
    cout << "init" << endl;
    cout << "parallel" << endl;
    auto pbeging = chrono::system_clock::now();
    dijkstra.parallel();
    dijkstra.print(264346);
    auto ptime = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - pbeging).count();
    cout << "\nDijkstra Sequential: " << ptime << " ms" << endl;

    /*
    Dijkstra dijkstra(file);
    dijkstra.load_graph();
    cout << "loaded" << endl;
    dijkstra.init(1);
    cout << "init" << endl;
    cout << "sequential" << endl;
    auto sbeging = chrono::system_clock::now();
    dijkstra.sequential();
    dijkstra.print(264346);
    auto stime = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - sbeging).count();
    cout << "\nDijkstra Sequential: " << stime << " ms" << endl;

    dijkstra.load_graph();
    cout << "loaded" << endl;
    dijkstra.init(1);
    cout << "init" << endl;
    cout << "parallel" << endl;
    auto pbeging = chrono::system_clock::now();
    dijkstra.parallel();
    dijkstra.print(264346);
    auto ptime = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - pbeging).count();
    cout << "\nDijkstra Parallel: " << ptime << " ms" << endl;

    auto speed_up = (double) stime / (double) ptime;
    auto cores = thread::hardware_concurrency();
    auto efficiency = speed_up / cores;
    cout << "\n\ncores: " << cores;
    cout << "\nSpeed-up: " << speed_up;
    cout << "\nEfficiency: " << efficiency;
     */
}
