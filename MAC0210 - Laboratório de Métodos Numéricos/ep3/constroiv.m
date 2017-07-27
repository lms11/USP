function v = constroiv (type_interpolation, val_i, val_j, ax, ay, hx, hy, f, nx, ny)
    x_i = ax + (val_i - 1) * hx;
    y_j = ay + (val_j - 1) * hy;

    if (strcmp (type_interpolation, "bilinear"))
        % Bilinear interpolation
        A = [ 1, 0
             -1, 1 ];

        F = [ f(val_i, val_j),     f(val_i, val_j + 1)
              f(val_i + 1, val_j), f(val_i + 1, val_j + 1) ];

        B = [ 1, -1
              0,  1 ];

        alpha = A * F * B;
         %v = @(x, y) ([ 1, ((x - x_i)/hx) ] * alpha * [1 ; ((y - y_j)/hy) ]);
        v = @(x, y) (alpha(1, 1) + (alpha(2, 1) * (x - x_i) / hx) + (alpha(1, 2) * (y - y_j) / hy) + (alpha(2, 2) * (x - x_i) * (y - y_j) / (hx * hy)));

    else
        % Bicubic interpolation
        A = [  1,  0,  0, 0
               0,  0,  1, 0
              -3,  3, -2, -1
               2, -2,  1, 1 ];

        % func_dfx = dfx (f, nx, hx)
        % func_dfy = dfy (f, ny, hy)
        % func_dfxy = dfy (func_dxy, lim_y, hy)

        % printf ("Constroi V com (i, j) = (%f, %f) e limites (%d, %d)\n", val_i, val_j, nx, ny);

        % Otimizar
        F = [ f(val_i, val_j),                                  f(val_i, val_j + 1),                                    hy * dfy(f, val_j, ny, hy)(val_i, val_j),             hy * dfy(f, val_j + 1, ny, hy)(val_i, val_j + 1)
              f(val_i + 1, val_j),                              f(val_i + 1, val_j + 1),                                hy * dfy(f, val_j, ny, hy)(val_i + 1, val_j),         hy * dfy(f, val_j + 1, ny, hy)(val_i + 1, val_j + 1)
              hx * dfx(f, val_i, nx, hx)(val_i, val_j),         hx * dfx(f, val_i, nx, hx)(val_i, val_j + 1),           hx * hy * dfxy(f, val_i, val_j, nx, ny, hx, hy),      hx * hy * dfxy(f, val_i, val_j + 1, nx, ny, hx, hy)
              hx * dfx(f, val_i + 1, nx, hx)(val_i + 1, val_j), hx * dfx(f, val_i + 1, nx, hx)(val_i + 1, val_j + 1),   hx * hy * dfxy(f, val_i + 1, val_j, nx, ny, hx, hy),  hx * hy * dfxy(f, val_i + 1, val_j + 1, nx, ny, hx, hy) ];

        B = [ 1, 0, -3,  2
              0, 0,  3, -2
              0, 1, -2,  1
              0, 0, -1,  1 ];

        alpha = A * F * B;

        v = @(x, y) ([ 1, (x - x_i)/hx, ((x - x_i)/hx)^2, ((x - x_i)/hx)^3 ] * alpha * [ 1 ; (y - y_j)/hy ; ((y - y_j)/hy)^2 ; ((y - y_j)/hy)^3 ]);
    endif
endfunction
