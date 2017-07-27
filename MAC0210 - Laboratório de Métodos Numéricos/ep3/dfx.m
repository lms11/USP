function func = dfx(f, val_i, lim_x, hx)
    if val_i == 1
        % Dois pra frente
        % func = (-3 * f(val_i, val_j) + 4 * f(val_i + 1, val_j) - f(val_i + 2, val_j)) / (2 * hx)
        func = @(x, y) ((-3 * f(x, y) + 4 * f(x + 1, y) - f(x + 2, y)) / (2 * hx));

    elseif val_i == (lim_x + 1)
        % Dois pra trás
        % func = (3 * f(val_i, val_j) - 4 * f(val_i - 1, val_j) - f(val_i - 2, val_j)) / (2 * hx);
        func = @(x, y) ((3 * f(x, y) - 4 * f(x - 1, y) - f(x - 2, y)) / (2 * hx));

    else
        % Centrado
        % func = (f(val_i + 1, val_j) - f(val_i - 1, val_j)) / (2 * hx);
        func = @(x, y) ((f(x + 1, y) - f(x - 1, y)) / (2 * hx));

    endif
endfunction
