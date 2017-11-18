clc;
clear;

%VICTIMS COORD
victims_y = randi(120, 5, 1);
victims_x = randi(90, 5, 1);
victims_coord = [victims_x victims_y];
evac = randi(2);


%SORT VICTIMS BY Y (SMALLEST TO LARGEST)
for startIndex=1:5
    
    smallestIndex = startIndex;
    
    for currentIndex=startIndex+1:5  
        if victims_coord(currentIndex, 2) < victims_coord(smallestIndex, 2)
            smallestIndex = currentIndex;
        end
    end 
    holder = victims_coord(startIndex, 1:2);
    victims_coord(startIndex, 1:2) = victims_coord(smallestIndex, 1:2);
    victims_coord(smallestIndex, 1:2) = holder;
    

end



d = [0 0 0 0 0];

theta = [0 0 0 0 0];
thetaMoved = [0 0 0 0 0];
robot_coord = [90 0];
des_coord_x = [0 0 0 0 0];
des_coord_y = [0 0 0 0 0];

for i=1:5
    switch(i)
        case 1
           a = robot_coord(1) - victims_coord(1, 1);
           b = victims_coord(1, 2) - robot_coord(2);
           theta(1) = atan(a/b);
           thetaMoved(1) = theta(1);
        
           d(1) = sqrt((a^2 + b^2));
           des_coord_x(1) = robot_coord(1) - d(1) * sin(theta(1));
           des_coord_y(1) = robot_coord(2) + d(1) * cos(theta(1));
           robot_coord = victims_coord(1, 1:2);
        case 2
           a = robot_coord(1) - victims_coord(2, 1);
           b = victims_coord(2, 2) - robot_coord(2);
           theta(2) = atan(a/b);
           thetaMoved(2) = theta(2) - theta(1);
        
           d(2) = sqrt((a^2 + b^2));
           des_coord_x(2) = robot_coord(1) - d(2) * sin(theta(2));
           des_coord_y(2) = robot_coord(2) + d(2) * cos(theta(2));
           robot_coord = victims_coord(2, 1:2);
           
        case 3
           a = robot_coord(1) - victims_coord(3, 1);
           b = victims_coord(3, 2) - robot_coord(2);
           theta(3) = atan(a/b);
           thetaMoved(3) = theta(3) - theta(2);
        
           d(3) = sqrt((a^2 + b^2));
           des_coord_x(3) = robot_coord(1) - d(3) * sin(theta(3));
           des_coord_y(3) = robot_coord(2) + d(3) * cos(theta(3));
           robot_coord = victims_coord(3, 1:2);

        case 4
           a = robot_coord(1) - victims_coord(4, 1);
           b = victims_coord(4, 2) - robot_coord(2);
           theta(4) = atan(a/b);
           thetaMoved(4) = theta(4) - theta(3);
        
           d(4) = sqrt((a^2 + b^2));
           des_coord_x(4) = robot_coord(1) - d(4) * sin(theta(4));
           des_coord_y(4) = robot_coord(2) + d(4) * cos(theta(4));
           robot_coord = victims_coord(4, 1:2);

        case 5
           a = robot_coord(1) - victims_coord(5, 1);
           b = victims_coord(5, 2) - robot_coord(2);
           theta(5) = atan(a/b);
           thetaMoved(5) = theta(5) - theta(4);
        
           d(5) = sqrt((a^2 + b^2));
           des_coord_x(5) = robot_coord(1) - d(5) * sin(theta(5));
           des_coord_y(5) = robot_coord(2) + d(5) * cos(theta(5));
           robot_coord = victims_coord(5, 1:2);

    end
    
end

for i=1:5
theta(i) = (theta(i)*180)/pi;
end

for i=1:5
thetaMoved(i) = (thetaMoved(i)*180)/pi;
end

des_coord= [des_coord_x' des_coord_y'];

plot(victims_coord(1, 1), victims_coord(1, 2), 'b*');
hold on;
grid on;
plot(90, 0, 'o');
plot(victims_coord(2, 1), victims_coord(2, 2), 'r*');
plot(victims_coord(3, 1), victims_coord(3, 2), 'g*');
plot(victims_coord(4, 1), victims_coord(4, 2), 'c*');
plot(victims_coord(5, 1), victims_coord(5, 2), 'k*');

plot(des_coord(1, 1), des_coord(1, 2), 'bo');
plot(des_coord(2, 1), des_coord(2, 2), 'ro');
plot(des_coord(3, 1), des_coord(3, 2), 'go');
plot(des_coord(4, 1), des_coord(4, 2), 'co');
plot(des_coord(5, 1), des_coord(5, 2), 'ko');
% plot(victims_coord(1:5,1), victims_coord(1:5, 2));
hold off;
xlim([0 90]);
ylim([0 120]);