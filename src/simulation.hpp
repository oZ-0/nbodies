#pragma once
#include "solver.hpp"
#include "world.hpp"
#include <fstream>
#include <stack>

using namespace std;
class Simulation {
protected:
  int N;
  stack<vector<vec3>> positionHistory;
  stack<vector<vec3>> velocityHistory;
  EulerSolver solver;

public:
  explicit Simulation()
      : N(), solver(EulerSolver()), positionHistory(stack<vector<vec3>>()),
        velocityHistory(stack<vector<vec3>>()) {}

  explicit Simulation(int N, double h)
      : N(N), solver(EulerSolver(N, h)), positionHistory(stack<vector<vec3>>()),
        velocityHistory(stack<vector<vec3>>()) {}

  void run(const int stepsNb);

  void log(const World &world);

  void savePositions(const string filename = "positions.txt");

  void save(const string filename = "data.txt");
};
