#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <algorithm>
#include <sstream>

struct Creature 
{
    float fitness, x, y, z;
    void test() 
    {
        float ans = 3*x*x + 49*std::pow(y, 5) - 12*z + 16;
        fitness = (ans == 0) ? -1 : std::abs(1/ans);
    };
    void print() const
    {
        std::cout << "Fitness " << fitness << " (" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};

inline float randInRangef(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
}

inline int randInRangei(int min, int max)
{
    return min + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX/(max-min)));
}

int main(int argc, char *argv[]) 
{
    //percent chance of a mutation
    float MUTATION_RATE = 1;
    //number selected to reproduce
    int SELECTION_SIZE = 100;
    int POPULATION = 100000;

    std::cout << "Set mutation rate (default is 1%) lower numbers reduce randomness:\n";
    std::string input;
    std::getline( std::cin, input );
    if ( !input.empty() ) {
        std::istringstream stream( input );
        stream >> MUTATION_RATE;
    }
    std::cout << "Set population size (default is 100000) higher numbers increase the change of progression:\n";
    std::getline( std::cin, input );
    if ( !input.empty() ) {
        std::istringstream stream( input );
        stream >> POPULATION;
    }
    std::cout << "Set reproduction limit (default is 100) higher numbers mean more diversity:\n";
    std::getline( std::cin, input );
    if ( !input.empty() ) {
        std::istringstream stream( input );
        stream >> SELECTION_SIZE;
    }

    // set a unique seed for the program.
    srand(time(0));
    
    //inital random solutions
    std::vector<Creature> creatures;

    for (int i = 0; i < POPULATION; i++)
        creatures.push_back(Creature{
            0,
            randInRangef(-10000, 10000),
            randInRangef(-10000, 10000),
            randInRangef(-10000, 10000)
        });

    bool running = true;
    long unsigned int gen = 1;
    Creature best;
    int bestGen = 0;
    while (running) {

        // determine creatures fitness. The & references the address of the creature so that it is modified not copied  
        for (auto& c: creatures) c.test();

        // determine the fittest
        sort(creatures.begin(), creatures.end(), 
            //This is a lambda function. This function is a comparator for the sorting algorithm.
            [](const auto& a, const auto& b) {
                return a.fitness > b.fitness;
            }
        );

        if (creatures[0].fitness == -1) {
            running == false;
            creatures[0].print();
            break;
        }

        /*print top*/
        system("clear");
        if (creatures[0].fitness > best.fitness) {
            best = creatures[0];
            bestGen = gen;
        }
        std::cout << "Generation: " << gen << " (Mutation rate: " << MUTATION_RATE 
        << ", Selection size: " << SELECTION_SIZE << ", Population: " << POPULATION << ")" << std::endl 
        << "Fittest creature is from gen " << bestGen << ": " ;
        best.print();
        std::cout << "Fittest creature in current gen: " ;
        creatures[0].print();
        /*print top 10
        std::for_each(creatures.begin(), creatures.begin() + 10, 
            [](const auto& c){ c.print(); }
        );*/

        std::vector<Creature> fittest;
        //coppies the best from the population into a new list
        std::copy(
            creatures.begin(), 
            creatures.begin() + SELECTION_SIZE, 
            //inserts into the back of the new vector
            std::back_inserter(fittest)
        );
        creatures.clear();

        //mutate the fittest
        std::for_each(fittest.begin(), fittest.end(), [&](auto& c){
            c.x *= randInRangef(1 - (MUTATION_RATE/100), 1 + (MUTATION_RATE/100));
            c.y *= randInRangef(1 - (MUTATION_RATE/100), 1 + (MUTATION_RATE/100));
            c.z *= randInRangef(1 - (MUTATION_RATE/100), 1 + (MUTATION_RATE/100));
        });

        // cross over genes
        for (int i = 0; i < POPULATION; i++) {
            creatures.push_back(Creature{
                0,
                fittest[randInRangei(0, SELECTION_SIZE - 1)].x,
                fittest[randInRangei(0, SELECTION_SIZE - 1)].y,
                fittest[randInRangei(0, SELECTION_SIZE - 1)].z
            });
        }
        gen++;
    }

    return 0;
}