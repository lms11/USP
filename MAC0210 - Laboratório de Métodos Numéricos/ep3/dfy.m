function func = dfy(f, val_j, lim_y, hy)
    % printf ("Construindo del y de f: j = %f, nx = %f, hx = %f\n", val_j, lim_y, hy);

    if val_j == 1
        % Dois pra frente
        % func = (-3 * f(val_i, val_j) + 4 * f(val_i, val_j + 1) - f(val_i, val_j + 2)) / (2 * hy);
        func = @(x, y) ((-3 * f(x, y) + 4 * f(x, y + 1) - f(x, y + 2)) / (2 * hy));

    elseif val_j == (lim_y + 1)
        % Dois pra trás
        % func = (3 * f(val_i, val_j) - 4 * f(val_i, val_j - 1) - f(val_i, val_j - 2)) / (2 * hy);
        func = @(x, y) ((3 * f(x, y) - 4 * f(x, y - 1) - f(x, y - 2)) / (2 * hy));

    else
        % Centrado
        % func = (f(val_i, val_j + 1) - f(val_i, val_j - 1)) / (2 * hy);
        func = @(x, y) ((f(x, y + 1) - f(x, y - 1)) / (2 * hy));

    endif
endfunction
