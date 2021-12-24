#include "simulation.hpp"

using namespace std;

void Simulation::run(const int stepsNb) {
  vector<vec3> pos{vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)};
  vector<vec3> vel{vec3(0, 0.7, 0), vec3(0, 0, 0.7), vec3(0.7, 0, 0)};
  World world(pos, vel);
  for (int i = 0; i < stepsNb; i++) {
    this->log(world);
    world = solver.step(world);
  }
  this->savePositions();
}

void Simulation::log(const World &world) {
  this->positionHistory.push(world.position);
  this->velocityHistory.push(world.velocity);
}

void Simulation::savePositions(const string filename /*= "positions.txt"*/) {
  ofstream outFile(filename);
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
}

void Simulation::save(const string filename /*= "data.txt"*/) {
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