#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 4; // Number of queens
const int POP_SIZE = 100; // Population size
const int MAX_GEN = 1000; // Maximum generations
const double MUTATION_RATE = 0.05; // Mutation rate

// Chromosome structure representing a solution (queen positions in each row)
struct Chromosome {
    vector<int> genes;
    int fitness;

    Chromosome() : genes(N), fitness(0) {
        // Initialize chromosome with random queen positions
        for (int i = 0; i < N; ++i) {
            genes[i] = rand() % N;
        }
    }

    // Calculate the fitness of the chromosome (number of non-attacking pairs)
    void calculateFitness() {
        fitness = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                // Check for non-attacking pairs
                if (genes[i] != genes[j] && abs(genes[i] - genes[j]) != abs(i - j)) {
                    fitness++;
                }
            }
        }
    }
};

// Genetic Algorithm functions
Chromosome crossover(const Chromosome &parent1, const Chromosome &parent2) {
    Chromosome child;
    int crossoverPoint = rand() % N;
    for (int i = 0; i < N; ++i) {
        child.genes[i] = (i < crossoverPoint) ? parent1.genes[i] : parent2.genes[i];
    }
    return child;
}

void mutate(Chromosome &chromosome) {
    if ((double) rand() / RAND_MAX < MUTATION_RATE) {
        int pos = rand() % N;
        chromosome.genes[pos] = rand() % N;
    }
}

// Function to select a parent using tournament selection
Chromosome selectParent(const vector<Chromosome> &population) {
    int tournamentSize = 5;
    Chromosome best = population[rand() % POP_SIZE];
    for (int i = 1; i < tournamentSize; ++i) {
        Chromosome contender = population[rand() % POP_SIZE];
        if (contender.fitness > best.fitness) {
            best = contender;
        }
    }
    return best;
}

int main() {
    srand(time(0));
    vector<Chromosome> population(POP_SIZE);

    // Initialize population and calculate fitness
    for (auto &chromosome : population) {
        chromosome.calculateFitness();
    }

    int generation = 0;
    Chromosome bestSolution;

    // Genetic algorithm loop
    while (generation < MAX_GEN) {
        sort(population.begin(), population.end(), [](const Chromosome &a, const Chromosome &b) {
            return a.fitness > b.fitness;
        });

        if (population[0].fitness == (N * (N - 1)) / 2) { // Max fitness for non-attacking pairs
            bestSolution = population[0];
            break;
        }

        vector<Chromosome> newPopulation;

        // Selection and crossover to create a new population
        for (int i = 0; i < POP_SIZE; ++i) {
            Chromosome parent1 = selectParent(population);
            Chromosome parent2 = selectParent(population);
            Chromosome child = crossover(parent1, parent2);
            mutate(child);
            child.calculateFitness();
            newPopulation.push_back(child);
        }

        population = newPopulation;
        generation++;
    }

    // Print the solution
    if (bestSolution.fitness == (N * (N - 1)) / 2) {
        cout << "Solution found in generation " << generation << ":\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (j == bestSolution.genes[i]) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
