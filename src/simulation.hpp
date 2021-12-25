#pragma once
#include "solver.hpp"
#include "world.hpp"
#include <algorithm>
#include <deque>
#include <fstream>
#include <random>

using namespace std;

class Simulation {
protected:
  int N;
  deque<vector<vec3>> positionHistory;
  deque<vector<vec3>> velocityHistory;
  deque<World> worldHistory;
  EulerSolver solver;

public:
  explicit Simulation()
      : N(), solver(EulerSolver()), positionHistory(deque<vector<vec3>>()),
        velocityHistory(deque<vector<vec3>>()), worldHistory(deque<World>()) {}

  explicit Simulation(const int &N, const double &h)
      : N(N), solver(EulerSolver(N, h)), positionHistory(deque<vector<vec3>>()),
        velocityHistory(deque<vector<vec3>>()), worldHistory(deque<World>()) {}

  void run_example(const int &stepsNb);

  void run(const int &stepsNb, World &world);

  void randomSearch(const int &searchNb);
  void randomSearch();

  double stability() const;

  void log(const World &world);
  void savePositions(const string &filename = "positions.txt");
  void save(const string &filename = "data.txt");
  void clear();
};
