% Parameters
k = 4; % k = number of gaussians
mr = [-20, 20]; % mu range
sr = [0.1, 3]; % sigma range
cr = [0.2 1]; % constant range

% Pick mus + sigmas
mu = mr(1) + (mr(2)-mr(1))*rand(1,k) % Random in the mu range (mr)
sigmas = sr(1) + (sr(2)-sr(1))*rand(1,k) % Random in sigma range (sr)
xr = [min(mu)-max(sigmas)-3, max(mu)+max(sigmas)+3]; % x range

% Pick the constants for the GMM
%(GM = c1* G1+ c2* G2 + .... + c4* G4, c1+c2+...+c4=1
cts = cr(1) + (cr(2)-cr(1))*rand(1, k);
sum_c = sum(cts);
cts = cts / sum_c % normalize to sum up to 1
% mu = [-5:0.1:5];
% Y = 0.3*normpdf(mu, 0, 1) + 0.7*normpdf(mu, 2, 0.5);
% plot(mu, Y);

% Get the points
num_points = 500; %500000;
pts = zeros(num_points, 2);
% x points
for i = 1:num_points
   pts(i, 1) = xr(1) + (xr(2)-xr(1))*rand(1); % Pick x values in x range (xr)
end
% y points
for j = 1:k
   pts(:,2) = pts(:,2) + cts(j)*normpdf(pts(:,1), mu(j), sigmas(j));
end

% Plot the graph
scatter(pts(:,1), pts(:,2));