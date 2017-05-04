data_range=[-1000,1000];
sigma_range=[100,300];
data_size=2000;
n_gaussians=5;

weights=rand(n_gaussians,1);
weights = weights./sum(weights);
means=zeros(n_gaussians,1);
sigmas=zeros(1,1,n_gaussians);
for i=1:n_gaussians
    means(i)=data_range(1)+(data_range(2)-data_range(1))*rand(1);
    sigmas(1,1,i)=sigma_range(1)+(sigma_range(2)-sigma_range(1))*rand(1);
end
gmm=gmdistribution(means,sigmas,weights);
X=(data_range(1):1:data_range(2)).';
Y=pdf(gmm,X);
figure(10),plot(X,Y); title('True probability density function of the GMM');

fileID = fopen('gmm.txt','w');
sampled_data = random(gmm,data_size);
for i=1:data_size
    fprintf(fileID,'%f\n',sampled_data(i));
end
fclose(fileID);
figure(20), hist(sampled_data,1000); title('Histogram of data sampled from the GMM');

% Print out the means/sigmas/weights for comparison
resFile = fopen('orig_ms.txt','w');
fprintf(resFile, 'MEANS\n');
for i=1:n_gaussians
    fprintf(resFile, '%f\n', means(i));
end
fprintf(resFile, '\nSIGMAS\n');
for i=1:n_gaussians
    fprintf(resFile, '%f\n', sigmas(1,1,i));
end
fprintf(resFile, '\nWEIGHTS\n');
for i=1:n_gaussians
    fprintf(resFile, '%f\n', weights(i));
end

