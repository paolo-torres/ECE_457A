clc;
clear;

generations = 1 : 1 : 1000;

bestFitnesses = zeros(1000, 1);

% 1-5: 0.5
% 6-10: 0.546875
% 11-26: 0.609375
% 27-175: 0.65625
% 176-177: 0.71875
% 178-377: 0.765625
% 378-537: 0.828125
% 538-881: 0.875
% 882-892: 0.9375
% 893-1000: 1

ranges = [1 5 10 26 175 177 377 537 881 892 1000];

values = [0.5 0.546875 0.609375 0.65625 0.71875 0.765625 0.828125 0.875 ... 
    0.9375 1];

for i = 1 : 1000
    if i >= ranges(1) && i <= ranges(2)
        bestFitnesses(i) = values(1);
    elseif i >= ranges(2) + 1 && i <= ranges(3)
        bestFitnesses(i) = values(2);
    elseif i >= ranges(3) + 1 && i <= ranges(4)
        bestFitnesses(i) = values(3);
    elseif i >= ranges(4) + 1 && i <= ranges(5)
        bestFitnesses(i) = values(4);
    elseif i >= ranges(5) + 1 && i <= ranges(6)
        bestFitnesses(i) = values(5);
    elseif i >= ranges(6) + 1 && i <= ranges(7)
        bestFitnesses(i) = values(6);
    elseif i >= ranges(7) + 1 && i <= ranges(8)
        bestFitnesses(i) = values(7);
    elseif i >= ranges(8) + 1 && i <= ranges(9)
        bestFitnesses(i) = values(8);
    elseif i >= ranges(9) + 1 && i <= ranges(10)
        bestFitnesses(i) = values(9);
    elseif i >= ranges(10) + 1 && i <= ranges(11)
        bestFitnesses(i) = values(10);
    end
end

plot(generations, bestFitnesses, 'LineWidth', 3);
title('Progress of Best Program Fitness in Each Iteration');
xlabel('Generation');
ylabel('Best Program Fitness');
grid on;
ax = gca;
ax.FontSize = 24;
