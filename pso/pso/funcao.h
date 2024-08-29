#ifndef FUNCAO_H_
#define FUNCAO_H_

#include <math.h>
#include <stdlib.h>

typedef struct particle_ {
	float position, bestPosition, velocity, fitness;
	size_t neighborA, neighborB; 
} particle;

particle *initializeParticle (particle *p, int swarmSize, int en, float min, float max);
float fitnessCalculator (float position);
particle *newVelocity (particle *p, particle *gBest, float pn);
float randomNumber();
particle *newPosition (particle *p, float min, float max);
float bestNeighbor (float pna, float pnb);

#endif /* FUNCAO_H_ */