#include "simulation.hpp"

using namespace std;

void Simulation::run_example(const int &stepsNb) {
  vector<vec3> pos{vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)};
  vector<vec3> vel{vec3(0, 0.7, 0), vec3(0, 0, 0.7), vec3(0.7, 0, 0)};
  World world(pos, vel);
  for (int i = 0; i < stepsNb; i++) {
    this->log(world);
    solver.step(world);
  }
  this->savePositions();
}

void Simulation::run(const int &stepsNb, World &world) {
  World cWorld(world);
  for (int i = 0; i < stepsNb; i++) {
    this->log(cWorld);
    solver.step(cWorld);
  }
}

void Simulation::randomSearch(const int &searchNb) {
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<double> dis(0.0, 1.0);
  for (int i = 0; i < searchNb; i++) {
    vector<vec3> pos({vec3(dis, gen), vec3(dis, gen), vec3(dis, gen)});
    vector<vec3> vel({vec3(dis, gen), vec3(dis, gen), vec3(dis, gen)});
    World cWorld = World(pos, vel);

    this->run(5000, cWorld);
    double stability = this->stability();
    if (stability < 0.1) {
      cout << cWorld << endl << "Stability: " << stability << endl;
    }
  }
}

void Simulation::optimize(World &world, int stepNb /*= 100*/,
                          const bool verbose /*= true*/) {
  int NObjects = world.getNumObjects();
  World newWorld(world);
  double h = 0.1;
  this->run(25000, newWorld);
  double preQ = 1e10;
  double Q = this->stability(true);
  if (verbose) {
    cout << "Starting stability: " << Q << endl;
  }
  int step = 0;
  vector<double> grad(NObjects * 3 * 2 , 0);
  while (h > 1e-5 && step < stepNb) {
    while (Q <= preQ && h > 1e-5 && step < stepNb) {
      preQ = Q;
      for (int i = 0; i < NObjects * 3 * 2; i++) {
        World newWorld = world.tilt(i, h);
        this->run(25000, newWorld);
        double newQ = this->stability(true);
        cout << newQ << " ";
        grad[i] = newQ - Q;
      }
      cout << "Grad: ";
      for (int i = 0; i < NObjects * 3 * 2; i++) {
        cout << grad[i] << ", ";
      }
      cout << endl;
      world -= grad;
      this->run(25000, world);
      Q = this->stability(true);
      if (verbose) {
        cout << "Stability: " << Q << "; h: " << h << "; step: " << step
             << endl;
        // cout << world;
      }
      step++;
    }
    if (verbose) {
      cout << "Temporary failure..." << endl;
    }
    Q = preQ;
    world += grad;
    h /= 1.1;
    step++;
  }
}

void Simulation::randomSearch() {
  double minStability = 1e10;
  bool found = false;

  int i = 0;
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<double> dis(0.0, 1.0);
  while (!found) {
    vector<vec3> pos({vec3(dis, gen), vec3(dis, gen), vec3(dis, gen)});
    vector<vec3> vel({vec3(dis, gen), vec3(dis, gen), vec3(dis, gen)});
    World cWorld = World(pos, vel);

    this->run(25000, cWorld);
    double stability = this->stability();
    if (stability < minStability) {
      minStability = stability;
      cout << " Min stability: " << minStability << endl << cWorld << endl;
    }
    if (i % 1000 == 0)
      cout << i << " Min stability: " << minStability << endl;
    ;
    i++;
    if (stability < 0.1) {
      cout << cWorld << endl << "Stability: " << stability << endl;
      found = true;
    }
    this->clear();
  }
}

// double Simulation::stability() const {
//   World init = this->worldHistory.front();
//   World minWorld = *min(this->worldHistory.begin(), this->worldHistory.end(),
//                         [init](const World w1, const World w2) {
//                           return (init.distance(w1) < init.distance(w2));
//                         });
//   return init.distance(minWorld);
// }

double Simulation::stability(const bool &clear /*= false*/) {
  World init(this->worldHistory.front());
  double dist = init.distance(this->worldHistory.back());
  for (int i = 1000; i < this->worldHistory.size(); i++) {
    double newDist = init.distance(this->worldHistory[i]);
    if (newDist < dist) {
      dist = newDist;
    }
  }
  if (clear) {
    this->clear();
  }
  return dist;
}

void Simulation::log(const World &world) {
  this->positionHistory.push_back(world.position);
  this->velocityHistory.push_back(world.velocity);
  this->worldHistory.push_back(world);
}

void Simulation::savePositions(const string &filename /*= "positions.txt"*/) {
  ofstream outFile(filename);
  while (!this->positionHistory.empty()) {
    vector<vec3> pos = this->positionHistory.front();
    outFile << "[";
    for (int i = 0; i < this->N; i++) {
      outFile << pos[i];
      if (i != N - 1) {
        outFile << ", ";
      }
    }
    outFile << "]" << endl;
    this->positionHistory.pop_front();
  }
}

void Simulation::save(const string &filename /*= "data.txt"*/) {
  ofstream outFile(filename);

  outFile << "Positions:" << endl << "---" << endl;
  while (!this->positionHistory.empty()) {
    vector<vec3> pos = this->positionHistory.front();
    outFile << "[";
    for (int i = 0; i < this->N; i++) {
      outFile << pos[i];
      if (i != N - 1) {
        outFile << ", ";
      }
    }
    outFile << "]" << endl;
    this->positionHistory.pop_front();
  }

  outFile << "---" << endl << "Velocities:" << endl << "---" << endl;
  while (!this->velocityHistory.empty()) {
    vector<vec3> vel = this->velocityHistory.front();
    outFile << "[";
    for (int i = 0; i < this->N; i++) {
      outFile << vel[i];
      if (i != this->N - 1) {
        outFile << ", ";
      }
    }
    outFile << "]" << endl;
    this->velocityHistory.pop_front();
  }
}

void Simulation::clear() {
  this->positionHistory.clear();
  this->velocityHistory.clear();
  this->worldHistory.clear();
}