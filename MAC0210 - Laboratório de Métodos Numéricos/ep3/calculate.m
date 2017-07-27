function [ new_vals ] = calculate(vals, width, height, nx, ny, ax, bx, ay, by, type_interpolation = "bicubic")
    % Define some constants
    pixels_x = floor (width  / nx);
    pixels_y = floor (height / ny);
    hxx      = (bx - ax) / (width);
    hyy      = (by - ay) / (height);

    % Reset values
    new_vals = zeros (height, width);
    minval   = intmin;
    maxval   = intmax;

    for ii = 1:ny
        for jj = 1:nx
            v = constroiv (type_interpolation, ii, jj, ax, ay, hx, hy, vals, nx, ny);

            for iii = 0:(pixels_x - 1)
                for jjj = 0:(pixels_y - 1)
                    % Compute the value of (x, y) in the image and its position on the matrix
                    this_x = ax + ((ii - 1) * pixels_x + iii) * hxx;
                    this_y = ay + ((jj - 1) * pixels_y + jjj) * hyy;
                    posx = (ii - 1) * pixels_x + iii + 1;
                    posy = (jj - 1) * pixels_y + jjj + 1;

                    % Compute f
                    value = v(this_x, this_y);

                    % Store the values
                    new_vals(posx, posy) = value;
                endfor
            endfor
        endfor
    endfor
endfunction
