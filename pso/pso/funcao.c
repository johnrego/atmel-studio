#include "funcao.h"

particle *initializeParticle (particle *p, int swarmSize, int en, float min, float max){
	float ratio = (max - min) / (swarmSize - 1);
	p = malloc(sizeof(particle));
	p->position = min + (ratio * en);
	p->bestPosition = min + (ratio * en);
	p->fitness = 10;
	p->velocity = 0;
	if (en == (swarmSize - 1)){
		p->neighborA = en - 1;
		p->neighborB = 0;
	}
	else if (en == 0){
		p->neighborA = swarmSize -1;
		p->neighborB = en + 1;
	}
	else {
		p->neighborA = en - 1;
		p->neighborB = en + 1;
	}
	return p;
}

float fitnessCalculator (float position){
	float fit = pow(position, 3.0) -  1234.0;
	if (fit > 0){
		return fit;
	} 
	else {
		return -fit;
	}
}

particle *newVelocity (particle *p, particle *gBest, float pn){
	// float chi = 2.0 / abs(2 - 4.1 - sqrt(16.81 - 4 * 4.1));
	float chi = 0.7298;
	p->velocity += randomNumber() * 2.05 * (pn - p->position);
	p->velocity += randomNumber() * 2.05 * (gBest->bestPosition - p->position);
	p->velocity *= chi;
	float veloMax = 1.5, veloMin = -1.5;
	if (p->velocity > veloMax){
		p->velocity = veloMax;
	}
	if (p->velocity < veloMin){
		p->velocity = veloMin;
	}
	return p;	
}

float randomNumber(){
	return (float)rand() / RAND_MAX;
}

particle *newPosition (particle *p, float min, float max){
	p->position += p->velocity;
	if (p->position > max){
		p->position = max;
	}
	if (p->position < min){
		p->position = min;
	}
	return p;
}

float bestNeighbor (float pna, float pnb){
	if (fitnessCalculator(pna) < fitnessCalculator(pnb)){
		return pna;
	}
	else {
		return pnb;
	}
}

