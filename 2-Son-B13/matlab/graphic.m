fileId = fopen("results.txt", "r");
formatSpec = '%d %f %f';
sizeA = [3 inf];
A = fscanf(fileId,formatSpec, sizeA);
A = A';
A(:,1)

figure
hold on
plot(A(:, 1), A(:, 2))
plot(A(:, 1), A(:, 3))
xlabel('iterations')
ylabel('runtime')
legend('malloc', 'lab')
