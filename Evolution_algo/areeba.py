import random
import time

LOWER_X = -15
UPPER_X = 15
LOWER_Y = -25
UPPER_Y = 20

class Individual:
    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y
        self.f = 0.0

    def evaluate_fitness(self):
        self.f = 100 - (self.x - 7*self.y)**2 + 8*(self.y**2) - 6*self.x

def get_adjusted_fitness(population):
    smallest = float('inf')
    for person in population:
        if person.f < smallest:
            smallest = person.f
    smallest = abs(smallest)

    new_fitness = [person.f + smallest + 1 for person in population]
    return new_fitness

def calculate_cumulative_proportions(adjusted_fitness, population):
    fitness_sum = sum(adjusted_fitness)
    proportion = [f / fitness_sum for f in adjusted_fitness]

    print("\nProportions\n")
    for val in proportion:
        print(val)

    cumulative = {}
    cumulative[population[0]] = proportion[0]
    for i in range(1, len(population)):
        cumulative[population[i]] = proportion[i] + cumulative[population[i-1]]
    
    print("\nCumulative\n")
    for key, value in cumulative.items():
        print("\n", value)
    return cumulative

def seed_calculation():
    # This mimics the C++ seed calculation using current time and a hash of thread ID
    seed = int((time.time() + hash(time.time())) % 2**32)
    random.seed(seed)

def get_parent(population, cumulative):
    num = random.uniform(0, 1)
    num2 = 0
    print("\n")
    for person, value in cumulative.items():
        if num > num2 and num <= value:
            print(person.x, person.y, person.f, num)
            return person
        num2 = value
    return population[0]

def evolution(population, new_population, cumulative_probabilities):
    parent1 = get_parent(population, cumulative_probabilities)
    parent2 = get_parent(population, cumulative_probabilities)
    while parent1.f == parent2.f:
        print("same\n")
        parent2 = get_parent(population, cumulative_probabilities)

def main():
    population = []  # initial population

    # Read from input file
    with open('v4_input.txt', 'r') as file:
        for line in file:
            x, y = map(float, line.split())  # Convert strings to floats
            person = Individual(x, y)
            person.evaluate_fitness()
            population.append(person)

    # Print population
    for person in population:
        print(f"X: {person.x} Y: {person.y} Fitness: {person.f}")

    new_fitness = get_adjusted_fitness(population)
    print("\nAfter Adjusting fitness: \n")
    for fitness in new_fitness:
        print(fitness)

    cumulative = calculate_cumulative_proportions(new_fitness, population)

    # Testing of parent selection
    new_population = []
    evolution(population, new_population, cumulative)

if __name__ == "__main__":
    main()

