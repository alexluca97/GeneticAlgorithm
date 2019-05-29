import random, sys, math, bitstring
from bitstring import BitArray


def Rastrigin(param):  # -5.12 5.12
    sum = 0
    for i in range(len(param)):
        sum += (pow(param[i], 2) - 10 * math.cos(2 * math.pi * param[i]))
    return 10 * len(param) + sum


def Schwefel(param):  # -500 500
    sum = 0
    for i in range(len(param)):
        sum += (-param[i] * math.sin(math.sqrt(abs(param[i]))))
    return sum

def Six_Hump(param):
    sum = 0

def De_Jong(param): # -5.12 5.12
    sum = 0
    for i in range(len(param)):
        sum +=(param[i] * param[i])
    return sum


def random_bitstring(length):
    _bitt = random.randint(0, 1)
    bits = BitArray(bin=str(_bitt))
    length -= 1
    while length > 0:
        _bitt = BitArray(bin=str(random.randint(0, 1)))
        bits.append(_bitt)
        length -= 1
    return bits


def generate(size, length):
    population = []
    for i in range(0, size):
        population.append(random_bitstring(length))

    return population


def calculate_parameters(a, b, candidate, n, n_param):
    parameters = []
    i = 0
    j = i + n
    while j <= n * n_param:
        X = a + candidate[i:j].int * (b - a) / (pow(2, n) - 1)
        parameters.append(X)
        i = j
        j = j + n
    return parameters


def evaluate(a, b, n, n_param, population, func):
    pop_fitness = []
    val = []
    for pop in population:
        pop_fitness.append(1.0 / (func(calculate_parameters(a, b, pop, n, n_param))))
        val.append(func(calculate_parameters(a, b, pop, n, n_param)))

    # print(pop_fitness)
    # print(val)
    # print()
    return pop_fitness


def select(population_fitness, population):
    selection = []
    S = 0
    for i in range(0, len(population_fitness)):
        S += population_fitness[i]
    p = []
    for i in range(0, len(population_fitness)):
        p.append(population_fitness[i] / S)

    q = []
    q.append(0)
    for i in range(1, len(population_fitness)):
        q.append(q[i - 1] + p[i - 1])

    for i in range(0, len(population)):
        ok = 1
        while ok:
            r = random.uniform(0, 1)
            j = 0
            while j < len(population) - 1:
                new_string = BitArray(bin=population[j].bin)
                if q[j] < r <= q[j + 1]:
                    selection.append(new_string)
                    ok = 0
                    break
                j += 1

    return selection


def mutation(population, percent):
    bit_1 = BitArray(bin='1')
    bit_0 = BitArray(bin='0')

    for pop in population:
        if random.uniform(0, 1) < percent:
            r = random.randint(0, len(population[0].bin) - 1)

            if (pop.bin[r]) == '1':

                pop.overwrite(bit_0, r)
            else:
                pop.overwrite(bit_1, r)

    return population


def cross(population, percent):
    # print(population)
    for pop in population:

        if random.uniform(0, 1) < percent:
            ok = 1
            while ok:
                for pop1 in population:
                    if random.uniform(0, 1) < percent:
                        ok = 0
                        ok1 = 0
                        p1 = BitArray()
                        p2 = BitArray()
                        for i in range(0, len(pop.bin)):
                            if i % 50 == 0:
                                ok1 = 1
                            if ok1 == 0:
                                p1.append(BitArray(bin=pop.bin[i]))
                                p2.append(BitArray(bin=pop1.bin[i]))
                            else:
                                p1.append(BitArray(bin=pop1.bin[i]))
                                p2.append(BitArray(bin=pop.bin[i]))
                        pop = p1

                        break
    # print(population)
    return population


# def cross1(population,percent):


def minimum(a, b, n, n_param, population, func):
    m = []
    for i in population:
        m.append(func(calculate_parameters(a, b, i, n, n_param)))

    return min(m)


def genetic_alg(a, b, n_param, population_dim, func):
    d = 2
    N = (b - a) * pow(10, d)
    n = math.ceil(math.log(N, 2))

    population = generate(population_dim, n * n_param)

    i = 0
    while i < 500:
        population_fitness = evaluate(a, b, n, n_param, population, func)

        population = select(population_fitness, population)

        population = mutation(population, 0.01)

        population = cross(population, 0.70)
        print((minimum(a, b, n, n_param, population, func)))
        i = i + 1
    #print((minimum(a, b, n, n_param, population, func)))


#genetic_alg(-5.12, 5.12, 5, 100, Rastrigin)
genetic_alg(-500, 500, 30, 100, Schwefel)
#genetic_alg(-5.12,5.12,5,100,De_Jong)
