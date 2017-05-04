% Should correspond to the genGMM constants
data_range=[-1000,1000];
sigma_range=[100,300];
data_size=2000;

% Get the data from the files
% TODO -- fix sigmas
[orig_means, o_sigmas, orig_weights] = get_ms('orig_ms.txt');
[est_means, e_sigmas, est_weights] = get_ms('est_ms.txt');

orig_sigmas=zeros(1,1,size(o_sigmas, 1));
for i=1:size(o_sigmas, 1)
    orig_sigmas(1,1,i)=o_sigmas(i);
end
est_sigmas=zeros(1,1,size(e_sigmas, 1));
for i=1:size(e_sigmas, 1)
    est_sigmas(1,1,i)=e_sigmas(i);
end

% Plot original gmm
X=(data_range(1):1:data_range(2)).';
orig_gmm=gmdistribution(orig_means,orig_sigmas,orig_weights);
Y=pdf(orig_gmm,X);
figure(1),plot(X,Y);

% Plot new gmm
hold on
est_gmm=gmdistribution(est_means,est_sigmas,est_weights);
Y2=pdf(est_gmm,X);
plot(X,Y2);
hold off