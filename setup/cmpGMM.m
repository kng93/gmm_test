% Should correspond to the genGMM constants
data_range=[-1000,1000];
sigma_range=[100,300];
data_size=2000;
n_gaussians=4;

for t_num = 1:20
    % Get the data from the files
    rel_path = ['results/c', num2str(n_gaussians), '_t', num2str(t_num), '/'];
    [orig_means, o_sigmas, orig_weights] = get_ms([rel_path, 'orig_ms.txt']);
    [est_means1, e_sigmas1, est_weights1] = get_ms([rel_path, 'cv_est_ms.txt']);
    [est_means2, e_sigmas2, est_weights2] = get_ms([rel_path, 'arma_est_ms.txt']);

    % Reorder sigmas to work with gmdistribution
    orig_sigmas=zeros(1,1,size(o_sigmas, 1));
    for i=1:size(o_sigmas, 1)
        orig_sigmas(1,1,i)=o_sigmas(i);
    end
    est_sigmas1=zeros(1,1,size(e_sigmas1, 1));
    for i=1:size(e_sigmas1, 1)
        est_sigmas1(1,1,i)=e_sigmas1(i);
    end
    est_sigmas2=zeros(1,1,size(e_sigmas2, 1));
    for i=1:size(e_sigmas2, 1)
        est_sigmas2(1,1,i)=e_sigmas2(i);
    end

    % Plot original gmm
    X=(data_range(1):1:data_range(2)).';
    orig_gmm=gmdistribution(orig_means,orig_sigmas,orig_weights);
    Y=pdf(orig_gmm,X);
    figure(1),plot(X,Y);

    % Plot new opencv gmm
    hold on
    est_gmm1=gmdistribution(est_means1,est_sigmas1,est_weights1);
    Y2=pdf(est_gmm1,X);
    plot(X,Y2);

    % Plot new arma gmm
    est_gmm2=gmdistribution(est_means2,est_sigmas2,est_weights2);
    Y3=pdf(est_gmm2,X);
    plot(X,Y3);
    hold off

    legend('orig', 'opencv', 'arma');
    saveas(gcf,[rel_path,'gmm_plot.png']);
end