#include "serialConfig.h"
#include "funcao.h"

static FILE mysdtout = FDEV_SETUP_STREAM(USART0_Transmit_IO, NULL, _FDEV_SETUP_WRITE);

size_t swarmSize = 5, generations = 50000, min = 0, max = 20;

int main(void){	
	USART0_Init(MYUBRR);
	sei();
	stdout = &mysdtout;
	particle **swarm = malloc(swarmSize * sizeof(particle));
	// particle *dev = malloc(sizeof(particle));
	for (size_t a = 0; a < swarmSize; a++){
		swarm[a] = initializeParticle(swarm[a], swarmSize, a, min, max);
		// dev = swarm[a];
	}
	particle *gBest = swarm[0];
	while (1){
		for (size_t a = 0; a < generations; a++){
			// Percorre todo o enxame
			for (size_t b = 0; b < swarmSize; b++){
				// Calcula a aptidão
				swarm[b]->fitness = fitnessCalculator(swarm[b]->position);
				// Verifica se a posição atual é melhor que a melhor posição até o momento
				if (fitnessCalculator(swarm[b]->position) < fitnessCalculator(swarm[b]->bestPosition)){
					swarm[b]->bestPosition = swarm[b]->position;
					if (fitnessCalculator(swarm[b]->position) == 0.0){
						printf("Solucao encontrada!\r\n");
						printf("Particula: %d Posicao: %f Fitness: %f\r\n", b, swarm[b]->position, swarm[b]->fitness);
						_delay_ms(10000);
						return 0;
					}
				}
				/*
				Verifica se a posição atual da partícula, é melhor que
				a melhor posição da melhor partícula até o momento
				*/
				if (fitnessCalculator(swarm[b]->position) < fitnessCalculator(gBest->bestPosition)){
					gBest = swarm[b];
					printf("Geracao %d\r\n", a+1);
					printf("Melhor Posicao %f com Fitness: %f\r\n", gBest->position, gBest->fitness);
				}
			}
			// Atualiza as posições
			for (size_t b = 0; b < swarmSize; b++){
				// dev = swarm[b]; 
				float bNeigh = bestNeighbor(swarm[swarm[b]->neighborA]->position, swarm[swarm[b]->neighborB]->position);
				swarm[b] = newVelocity(swarm[b], gBest, bNeigh);
				swarm[b] = newPosition(swarm[b], min, max);	
			}
		}
		printf("Solucao nao encontrada!\r\n");
		printf("Melhor posicao %f com Fitness: %f\r\n", gBest->position, gBest->fitness);
		_delay_ms(10000);
		return 1;
	}
}

