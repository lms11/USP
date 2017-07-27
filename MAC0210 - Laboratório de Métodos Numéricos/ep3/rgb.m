function [ red, blue, green ] = rgb(vals)
    eps_error = 1e-9;
    width  = columns(vals);
    height = rows(vals);
    red    = zeros (height, width);
    blue   = zeros (height, width);
    green  = zeros (height, width);
    minval = intmax;
    maxval = intmin;

    for ii = 1:width
        for jj = 1:height
            % Compute the min/max
            if (vals(ii, jj) > maxval)
                maxval = vals(ii, jj);
            endif
            if (vals(ii, jj) < minval)
                minval = vals(ii, jj);
            endif
        endfor
    endfor

    % Compute all colors using some color progression
    % See reference: https://stackoverflow.com/questions/20792445/calculate-rgb-value-for-a-range-of-values-to-create-heat-map
    for ii = 1:height
        for jj = 1:width
            % Compute the values in the image of f
            if (maxval - minval < eps_error)
                red(ii, jj) = 0;
                blue(ii, jj) = 255;
                green(ii, jj) = 0;

            else
                value = vals (ii, jj);
                if (maxval != minval)
                  ratio = 2 * (value - minval) / (maxval - minval);
                else
                  ratio = 0;
                endif
                b = floor (max (0, 255 * (1 - ratio)));
                r = floor (max (0, 255 * (ratio - 1)));
                g = 255 - b - r;

                red(ii, jj)   = r;
                green(ii, jj) = g;
                blue(ii, jj)  = b;
            endif
        endfor
    endfor
endfunction
