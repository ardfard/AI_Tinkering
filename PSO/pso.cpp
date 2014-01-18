#include "pso.h"
#include <float.h>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <boost/foreach.hpp>
#include <iostream>
#include <QMapIterator>
#include "objectivefunction.h"

Bound::Bound(Vector minVector, Vector maxVector)
{
    minVec = minVector;
    maxVec = maxVector;
}

Bound::Bound(const Bound& bound)
{
        minVec = bound.minVec;
        maxVec = bound.maxVec;
}


Particle::Particle(Swarm* swarm_)
{
    swarm = swarm_;
    int vecSize = swarm->positionBound.minVec.size();
    position = swarm->positionBound.minVec + arma::randu(vecSize) % (swarm->positionBound.maxVec - swarm->positionBound.minVec);
    cost = swarm->objFun_->call(position);
    bestPosition = position;
    bestCost = this->cost;
    velocity = swarm->velocityBound.minVec + arma::randu(vecSize) % (swarm->velocityBound.maxVec - swarm->velocityBound.minVec);
}

void Particle::updateVelocity()
{
    int vecSize = velocity.size();
    velocity = 0.4 * velocity + swarm->c1*arma::randu(vecSize)%(bestPosition - position)
                                                        + swarm->c2*arma::randu(vecSize)%(swarm->globalBest->bestPosition - position);
    for (int i = 0; i < velocity.size(); i++) {

        velocity[i] = (velocity[i] > swarm->maxVelocity) ? swarm->maxVelocity : velocity[i];
        velocity[i] = (velocity[i] < -swarm->maxVelocity) ? -swarm->maxVelocity : velocity[i];
    }
}

void Particle::updatePosition()
{
    position += velocity;

    for ( unsigned int i = 0; i < position.size(); i++) {
        if (position[i] > swarm->positionBound.maxVec[i]) {
            position[i] = swarm->positionBound.maxVec[i] -
                    fabs(position[i] - swarm->positionBound.maxVec[i]);
            velocity[i] *= -1;
        } else if (position[i] < swarm->positionBound.minVec[i]) {
            position[i] = swarm->positionBound.minVec[i] +
                    fabs(position[i] - swarm->positionBound.minVec[i]);
            velocity[i] *= -1;
        }
    }
}

void findGlobalBest(std::vector<Particle*>& population, Particle* globalBest)
{
    BOOST_FOREACH(Particle* particle, population) {
        if (particle->cost < globalBest->cost) {
            globalBest->cost = particle->cost;
            globalBest->position = particle->position;
        }
    }
}

Swarm::Swarm()
{

}

Swarm::~Swarm()
{
    BOOST_FOREACH(Particle* &particle, population) {
        delete particle;
    }
}

void Swarm::setup()
{
    population.resize(populationSize);
    BOOST_FOREACH(Particle* &particle, population) {
        particle = new Particle(this);
    }
    globalBest = std::auto_ptr<Particle>(new Particle(this));
    population[0]->position;

    globalBest->position = population[0]->position;
    globalBest->cost = population[0]->cost;
    findGlobalBest(population, globalBest.get());

}

void Swarm::advance()
{
    BOOST_FOREACH (Particle* particle, population) {
        particle->updateVelocity();
        particle->updatePosition();
        particle->cost = objFun_->call(particle->position);

        if (particle->bestCost < particle->cost){
            particle->bestCost = particle->cost;
            particle->bestPosition = particle->position;
        }
    }
}
