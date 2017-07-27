function test (f, f_x, f_y, f_xy, ax, bx, ay, by, nx, ny, width, height, identifier)
    hx = (bx - ax) / nx;
    hy = (by - ay) / ny;

    printf ("===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====\n");
    printf ("Iniciando testes...");
    printf ("Valores de entrada:\nax = %f\nbx = %f\nay = %f\nby = %f\nnx = %f\nny = %f\nImage width = %f\nImage height = %f\nhx = %f\nhy = %f\n", ax, bx, ay, by, nx, ny, width, height, hx, hy);
    printf ("Função (e suas derivadas):\n");
    f
    f_x
    f_y
    f_xy


    ##
    #  O primeiro teste a ser feito é quanto
    #  a qualidade das aproximações de funções.
    #  Vamos comparar as derivadas aproximadas
    #  com seus valores reais.
    ##

    printf ("\nVerificando qualidade das aproximações das derivadas...\n");

    vals      = matrify(f, ax, ay, nx, ny, hx, hy);
    vals_f_x  = matrify(f_x, ax, ay, nx, ny, hx, hy);
    vals_f_y  = matrify(f_y, ax, ay, nx, ny, hx, hy);
    vals_f_xy = matrify(f_xy, ax, ay, nx, ny, hx, hy);
    [ aprox_f_x, aprox_f_y, aprox_f_xy ] = aproxdf(vals, nx, ny, hx, hy);

    printf ("Imprimindo imagens da dfx, dfy e dfxy (tanto aproximadas quanto reais)...\n");

    # Print real values
    [ red, green, blue ] = rgb(vals_f_x);
    save_image (red, green, blue, strcat("output/", identifier, "_dfx.ppm"));

    [ red, green, blue ] = rgb(vals_f_y);
    save_image (red, green, blue, strcat("output/", identifier, "_dfy.ppm"));

    [ red, green, blue ] = rgb(vals_f_xy);
    save_image (red, green, blue, strcat("output/", identifier, "_dfxy.ppm"));

    # Print approximate values
    [ red, green, blue ] = rgb(aprox_f_x);
    save_image (red, green, blue, strcat("output/", identifier, "_aprox_dfx.ppm"));

    [ red, green, blue ] = rgb(aprox_f_y);
    save_image (red, green, blue, strcat("output/", identifier, "_aprox_dfy.ppm"));

    [ red, green, blue ] = rgb(aprox_f_xy);
    save_image (red, green, blue, strcat("output/", identifier, "_aprox_dfxy.ppm"));

    % # Print difference
    [ red, green, blue ] = rgb(abs(vals_f_x - aprox_f_x));
    save_image (red, green, blue, strcat("output/", identifier, "_diff_dfx.ppm"));

    [ red, green, blue ] = rgb(abs(vals_f_y - aprox_f_y));
    save_image (red, green, blue, strcat("output/", identifier, "_diff_dfy.ppm"));

    [ red, green, blue ] = rgb(abs(vals_f_xy - aprox_f_xy));
    save_image (red, green, blue, strcat("output/", identifier, "_diff_dfxy.ppm"));



    ##
    #  Fim
    ##

    printf ("===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====\n\n");
endfunction
