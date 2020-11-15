clc;
clear;

populationSize = 50;

Kp = 2 + (18 - 2) * rand(50, 1);
Ti = 1.05 + (9.42 - 1.05) * rand(50, 1);
Td = 0.26 + (2.37 - 0.26) * rand(50, 1);
parameters = zeros(populationSize, 3);

population = zeros(populationSize, 4);

fitnesses = zeros(populationSize, 1);
fitnessSum = 0;

for i = 1 : populationSize
    parameters(i, 1) = Kp(i);
    parameters(i, 2) = Ti(i);
    parameters(i, 3) = Td(i);
    
    [population(i, 1), population(i, 2), population(i, 3), ...
        population(i, 4)] = perfFCN(parameters(i, :));
    
    if population(i, 1) > 1000
        population(i, 1) = 0;
        population(i, 2) = 0;
        population(i, 3) = 0;
        population(i, 4) = 0;
    end
    
    fitnesses(i) = population(i, 1) + population(i, 2) ...
        + population(i, 3) + population(i, 4);
    
    fitnesses(i) = 1 / fitnesses(i);
    if isinf(fitnesses(i))
        fitnesses(i) = 0;
    end
    
    fitnessSum = fitnessSum + fitnesses(i);
end

fitnessAverage = fitnessSum / populationSize;

probabilities = zeros(populationSize, 1);
expectedCounts = zeros(populationSize, 1);

for i = 1 : populationSize
    probabilities(i) = fitnesses(i) / fitnessSum;
    expectedCounts(i) = fitnesses(i) / fitnessAverage;
end

actualCounts = round(expectedCounts);

generations = 150;
crossoverProbability = 0.6;
mutationProbability = 0.25;

n = 0;
while n < generations
    n = n + 1;
end
