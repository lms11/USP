function ep2
    IMAGE_HEIGHT = 128;
    IMAGE_WIDTH = 128;
    eps_error = 1e-3;

    % General problem definitions
    type_interpolation = "bicubic"; % bilinear or bicubic
    nx = 128; % It should be a divisor of IMAGE_WIDTH
    ny = 128; % It should be a divisor of IMAGE_HEIGHT
    ax = -10;
    bx = 10;
    ay = -10;
    by = 10;
    hx = (bx - ax) / nx;
    hy = (by - ay) / ny;
    f = zeros (nx + 1, ny + 1);
    dxf = zeros (nx + 1, ny + 1);
    dyf = zeros (nx + 1, ny + 1);
    dxyf = zeros (nx + 1, ny + 1);

    % Example 4
    l_f    = @(x,y) x^3 + 1000 * sin(x * y);
    l_dxf  = @(x,y) 3*x^2 + 1000 * y * cos(x * y);
    l_dyf  = @(x,y) 1000 * x * cos(x * y);
    l_dxyf = @(x,y) 1000 * (cos (x * y) - x * y * sin(x * y));


    % Compute all values
    for ii = 1:rows(f)
         for jj = 1:columns(f)
            this_x = ax + (ii - 1) * hx;
            this_y = ay + (jj - 1) * hy;

            f(ii, jj)    = l_f    (this_x, this_y);
            dxf(ii, jj)  = l_dxf  (this_x, this_y);
            dyf(ii, jj)  = l_dyf  (this_x, this_y);
            dxyf(ii, jj) = l_dxyf (this_x, this_y);
         endfor
     endfor

    % Useful variables to use when drawing
    pixels_x = floor (IMAGE_WIDTH  / nx);
    pixels_y = floor (IMAGE_HEIGHT / ny);
    hxx      = (bx - ax) / (IMAGE_WIDTH - 1);
    hyy      = (by - ay) / (IMAGE_HEIGHT - 1);

    % Values for f
    f_m_values = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    f_m_red    = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    f_m_blue   = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    f_m_green  = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    f_maxval   = intmin;
    f_minval   = intmax;

    % Values for v
    v_m_values = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    v_m_red    = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    v_m_blue   = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    v_m_green  = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    v_maxval   = intmin;
    v_minval   = intmax;

    % Values for |f - v|
    fv_m_values = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    fv_m_red    = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    fv_m_blue   = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    fv_m_green  = zeros (IMAGE_HEIGHT, IMAGE_WIDTH);
    fv_maxval   = intmin;
    fv_minval   = intmax;

    % Compute all the values
    for ii = 0:(nx - 1)
        for jj = 0:(ny - 1)
            v = constroiv (type_interpolation, ii + 1, jj + 1, ax, ay, hx, hy, f, dxf, dyf, dxyf);

            for iii = 0:(pixels_x - 1)
                for jjj = 0:(pixels_y - 1)

                    % Compute the value of (x, y) in the image and its position on the matrix
                    this_x = ax + (ii * pixels_x + iii) * hxx;
                    this_y = ay + (jj * pixels_y + jjj) * hyy;
                    posx = ii * pixels_x + iii + 1;
                    posy = jj * pixels_y + jjj + 1;

                    % Compute f, v and |f - v|
                    f_value = l_f (this_x, this_y);
                    v_value = v (this_x, this_y);
                    fv_value = abs(f_value - v_value);

                    % Store the values
                    f_m_values (posx, posy)  = f_value;
                    v_m_values (posx, posy)  = v_value;
                    fv_m_values (posx, posy) = fv_value;

                    % Compute the min/max of each of them
                    if (f_value > f_maxval)
                        f_maxval = f_value;
                    elseif (f_value < f_minval)
                        f_minval = f_value;
                    endif

                    if (v_value > v_maxval)
                        v_maxval = v_value;
                    elseif (v_value < v_minval)
                        v_minval = v_value;
                    endif

                    if (fv_value > fv_maxval)
                        fv_maxval = fv_value;
                    elseif (fv_value < fv_minval)
                        fv_minval = fv_value;
                    endif

                endfor
            endfor
        endfor
    endfor

    % Compute all colors using some color progression
    % See reference: https://stackoverflow.com/questions/20792445/calculate-rgb-value-for-a-range-of-values-to-create-heat-map
    for ii = 1:IMAGE_WIDTH
        for jj = 1:IMAGE_HEIGHT
            % Compute the values in the image of f
            if (f_maxval - f_minval < eps_error)
                f_m_red(ii, jj) = 0;
                f_m_blue(ii, jj) = 255;
                f_m_green(ii, jj) = 0;

            else
                value = f_m_values (ii, jj);
                if (f_maxval != f_minval)
                  ratio = 2 * (value - f_minval) / (f_maxval - f_minval);
                else
                  ratio = 0;
                endif
                blue  = floor (max (0, 255 * (1 - ratio)));
                red   = floor (max (0, 255 * (ratio - 1)));
                green = 255 - blue - red;

                f_m_red(ii, jj) = red;
                f_m_blue(ii, jj) = blue;
                f_m_green(ii, jj) = green;
            endif


            % Compute the values in the image of v
            if (v_maxval - v_minval < eps_error)
                v_m_red(ii, jj) = 0;
                v_m_blue(ii, jj) = 255;
                v_m_green(ii, jj) = 0;

            else
                value = v_m_values (ii, jj);
                if (v_maxval != v_minval)
                  ratio = 2 * (value - v_minval) / (v_maxval - v_minval);
                else
                  ratio = 0;
                endif
                blue  = floor (max (0, 255 * (1 - ratio)));
                red   = floor (max (0, 255 * (ratio - 1)));
                green = 255 - blue - red;

                v_m_red(ii, jj) = red;
                v_m_blue(ii, jj) = blue;
                v_m_green(ii, jj) = green;
            endif


            % Compute the values in the image of f
            if (fv_maxval - fv_minval < eps_error)
                fv_m_red(ii, jj) = 0;
                fv_m_blue(ii, jj) = 255;
                fv_m_green(ii, jj) = 0;

            else
                value = fv_m_values (ii, jj);
                if (fv_maxval != fv_minval)
                  ratio = 2 * (value - fv_minval) / (fv_maxval - fv_minval);
                else
                  ratio = 0;
                endif
                blue  = floor (max (0, 255 * (1 - ratio)));
                red   = floor (max (0, 255 * (ratio - 1)));
                green = 255 - blue - red;

                fv_m_red(ii, jj) = red;
                fv_m_blue(ii, jj) = blue;
                fv_m_green(ii, jj) = green;
            endif

        endfor
    endfor

    % For debug purposes
    printf ("f -- min: %f, max = %f\n", f_minval, f_maxval);
    printf ("v -- min: %f, max = %f\n", v_minval, v_maxval);
    printf ("|f - v| -- min: %f, max = %f\n", fv_minval, fv_maxval);

    % Open files
    f_fid = fopen ("output/image-f.ppm", "w");
    v_fid = fopen ("output/image-v.ppm", "w");
    fv_fid = fopen ("output/image-fv.ppm", "w");

    % Print all values of PPM
    % See reference: https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html
    fprintf (f_fid, "P3\n");
    fprintf (f_fid, "%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    for ii = 1:IMAGE_WIDTH
        for jj = 1:IMAGE_HEIGHT
            fprintf (f_fid, "%d %d %d ", f_m_red(ii, jj), f_m_green(ii, jj), f_m_blue(ii, jj)); % RGB
        endfor
        fprintf (f_fid, "\n");
    endfor

    fprintf (v_fid, "P3\n");
    fprintf (v_fid, "%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    for ii = 1:IMAGE_WIDTH
        for jj = 1:IMAGE_HEIGHT
            fprintf (v_fid, "%d %d %d ", v_m_red(ii, jj), v_m_green(ii, jj), v_m_blue(ii, jj)); % RGB
        endfor
        fprintf (v_fid, "\n");
    endfor

    fprintf (fv_fid, "P3\n");
    fprintf (fv_fid, "%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    for ii = 1:IMAGE_WIDTH
        for jj = 1:IMAGE_HEIGHT
            fprintf (fv_fid, "%d %d %d ", fv_m_red(ii, jj), fv_m_green(ii, jj), fv_m_blue(ii, jj)); % RGB
        endfor
        fprintf (fv_fid, "\n");
    endfor

    % Close files
    fclose (f_fid);
    fclose (v_fid);
    fclose (fv_fid);
endfunction
