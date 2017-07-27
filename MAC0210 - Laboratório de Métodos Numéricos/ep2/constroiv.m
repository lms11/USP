% Função constroiv
%
% Parâmetros:
%   type_interpolation: (string) valores possiveis: bilinear, bicubic
%   val_i: (int) a posição de x_i na matriz
%   val_j: (int) a posição de x_j na matriz
%   ax: (float) o início do intervalo [ax, bx]
%   ay: (float) o início do intervalo [ay, by]
%   hx: (float) valor de ((bx - ax) / nx)
%   hy: (float) valor de ((by - ay) / ny)
%   f: uma matriz com os valores de f
%   dxf: uma matriz com os valores da derivada parcial de f em x
%   dyf: uma matriz com os valores da derivada parcial de f em y
%   dxyf: uma matriz com os valores da derivada segunda de f
%
% Retorno: v_ij = s_ij (bilinear ou bicúbica)

function v = constroiv (type_interpolation, val_i, val_j, ax, ay, hx, hy, f, dxf, dyf, dxyf)
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

        v = @(x, y) (alpha(1, 1) + (alpha(2, 1) * (x - x_i) / hx) + (alpha(1, 2) * (y - y_j) / hy) + (alpha(2, 2) * (x - x_i) * (y - y_j) / (hx * hy)));

    else
        % Bicubic interpolation
        A = [  1,  0,  0, 0
               0,  0,  1, 0
              -3,  3, -2, -1
               2, -2,  1, 1 ];

        F = [ f(val_i, val_j),            f(val_i, val_j + 1),            hy * dyf(val_i, val_j),           hy * dyf(val_i, val_j + 1)
              f(val_i + 1, val_j),        f(val_i + 1, val_j + 1),        hy * dyf(val_i + 1, val_j),       hy * dyf(val_i + 1, val_j + 1)
              hx * dxf(val_i, val_j),     hx * dxf(val_i, val_j + 1),     hx * hy * dxyf(val_i, val_j),     hx * hy * dxyf(val_i, val_j + 1)
              hx * dxf(val_i + 1, val_j), hx * dxf(val_i + 1, val_j + 1), hx * hy * dxyf(val_i + 1, val_j), hx * hy * dxyf(val_i + 1, val_j + 1) ];

        B = [ 1, 0, -3,  2
              0, 0,  3, -2
              0, 1, -2,  1
              0, 0, -1,  1 ];

        alpha = A * F * B;

        v = @(x, y) ([ 1, (x - x_i)/hx, ((x - x_i)/hx)^2, ((x - x_i)/hx)^3 ] * alpha * [ 1 ; (y - y_j)/hy ; ((y - y_j)/hy)^2 ; ((y - y_j)/hy)^3 ]);
    endif
endfunction
