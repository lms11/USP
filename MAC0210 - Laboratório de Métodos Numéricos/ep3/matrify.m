function [ vals ] = matrify(f, ax, ay, nx, ny, hx, hy)
    % Reset values
    vals = zeros (nx + 1, ny + 1);

    % Compute all the values
    for ii = 1:rows(f)
         for jj = 1:columns(f)
            this_x = ax + (ii - 1) * hx;
            this_y = ay + (jj - 1) * hy;

            vals(ii, jj) = f(this_x, this_y);
         endfor
     endfor
endfunction
