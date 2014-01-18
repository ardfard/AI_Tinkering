#ifndef PSO_H
#define PSO_H

#include <armadillo>
#include <QHash>
#include <auto_ptr.h>
#include <armadillo>

class ObjectiveFunction;
typedef arma::vec Vector;

struct Bound
{
    Bound(Vector minVector = Vector(), Vector maxVector = Vector());
    Bound(const Bound& bound);

    Vector minVec;
    Vector maxVec;
};

struct Swarm;

struct Particle
{
    Particle(Swarm* swarm = 0);
    Vector position;
    double cost;
    Vector bestPosition;
    double bestCost;
    Vector velocity;
    Swarm* swarm;
    void updateVelocity();
    void updatePosition();
};

struct Swarm
{
    Swarm();
    ~Swarm();
    std::auto_ptr<ObjectiveFunction> objFun_;
    double c1;
    double c2;
    Bound positionBound;
    Bound velocityBound;
    double maxVelocity;
    void setup();
    void advance();
    std::auto_ptr<Particle> globalBest;
    std::vector<Particle*> population;
    int populationSize;
};

void findGlobalBest(std::vector<Particle*>& population, Particle* globalBest);
#endif // PSO_H
