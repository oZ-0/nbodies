#pragma once
#include "solver.hpp"
#include "world.hpp"
#include <stack>
#include <fstream>

using namespace std;
class Simulation {
protected:
  stack<vector<vec3>> positionHistory;
  stack<vector<vec3>> velocityHistory;
  EulerSolver solver;

public:
  explicit Simulation()
      : solver(EulerSolver()), positionHistory(stack<vector<vec3>>()),
        velocityHistory(stack<vector<vec3>>()) {}

  explicit Simulation(int N, double h)
      : solver(EulerSolver(N, h)), positionHistory(stack<vector<vec3>>()),
        velocityHistory(stack<vector<vec3>>()) {}

  void run(const int stepsNb);

  void log(const World &world);
  
  void savePositions(const string filename = "positions.txt");

  void save(const string filename = "data.txt");
};
