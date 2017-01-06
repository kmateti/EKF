%% EKF Simulation
%
% Copyright (C) 2017 by Kiron Mateti
%
% This m-file will simulate a vehicle and a sensing system using nonlinear
% equations of motion and an extended Kalman filter.
%
%
%
clc
clear
close all

LINEAR_TEST = 1;

if LINEAR_TEST
    %% Sample Integration of Linear State Space Equations of motion
    Ts = 1e-3;
    t0 = 0;
    tf = 10;
    t = t0:Ts:tf - Ts;
    N = length(t);
    x0 = [0; 0.1];
 
    A = [0, 1; -2 -3];
    f_lin = @(x, t)(A * x);
 
    % Use built-in Octave function lsode
    X = lsode(f_lin, x0, t);
    X = X';
 
    % Use closed form solution
    Xp = zeros(2, N);
    Xp(:, 1) = x0;
 
    for ii = 2:N
        Xp(:, ii) = expm(A * t(ii - 1)) * Xp(:, 1);
    end
 
    % Yet another method
    phi = expm(A * Ts);
    Xpp(:, 1) = x0;
    for ii = 2:N
        Xpp(:, ii) = phi * Xpp(:, ii - 1);
    end
 
    hf = figure;
    subplot(2, 1, 1)
    plot(t, X(1, :), t, Xp(1, :), t, Xpp(1, :));
    ylabel('Position');
    title('Linear Time Invariant Solution');
    subplot(2, 1, 2)
    plot(t, X(2, :), t, Xp(2, :), t, Xpp(2, :));
    ylabel('Velocity');
    xlabel('Time (s)');
    set(findall(hf,'-property','XGrid'), 'XGrid', 'on')
    set(findall(hf,'-property','YGrid'), 'YGrid', 'on')
    set(findall(hf,'-property','XMinorTick'), 'XMinorTick', 'on')
    set(findall(hf,'-property','YMinorTick'), 'YMinorTick', 'on')
    set(findall(hf,'-property','LineWidth'), 'LineWidth', 1.5)
    set(findall(hf,'-property','FontSize'), 'FontSize', 14)
    set(findall(hf,'-property','FontName'), 'FontName', 'Arial')
end
%end

