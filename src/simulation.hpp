#pragma once

#include "world.hpp"
#include "solver.hpp"

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
  explicit Simulation(double h)
      : solver(EulerSolver(h)), positionHistory(stack<vector<vec3>>()),
        velocityHistory(stack<vector<vec3>>()) {}

  void run(int stepsNb) {
    vector<vec3> pos{vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)};
    vector<vec3> vel{vec3(0, 0.7, 0), vec3(0, 0, 0.7), vec3(0.7, 0, 0)};
    World world(pos, vel);
    for (int i = 0; i < stepsNb; i++) {
      this->log(world);
      world = solver.step(world);
    }
    this->save();
  }
  
  void log(const World &world) {
    this->positionHistory.push(world.position);
    this->velocityHistory.push(world.velocity);
  }

  void save(string filename = "data.txt") {
    ofstream outFile(filename);

    outFile << "Positions:" << endl << "---" << endl;
    while (!this->positionHistory.empty()) {
      vector<vec3> pos = this->positionHistory.top();
      outFile << "[";
      for (int i = 0; i < N; i++) {
        outFile << pos[i];
        if (i != N - 1) {
          outFile << ", ";
        }
      }
      outFile << "]" << endl;
      this->positionHistory.pop();
    }

    outFile << "---" << endl << "Velocities:" << endl << "---" << endl;
    while (!this->velocityHistory.empty()) {
      vector<vec3> vel = this->velocityHistory.top();
      outFile << "[";
      for (int i = 0; i < N; i++) {
        outFile << vel[i];
        if (i != N - 1) {
          outFile << ", ";
        }
      }
      outFile << "]" << endl;
      this->velocityHistory.pop();
    }
  }
};
