function ep3
    ##
    #  Definindo algumas constantes.
    ##

    IMAGE_HEIGHT = 512;
    IMAGE_WIDTH = 512;
    type_interpolation = "bicubic"; % bilinear or bicubic
    nx = 512;
    ny = 512;
    ax = -10;
    bx = 10;
    ay = -10;
    by = 10;

    ##
    #  Definindo funções para
    #  serem usadas nos testes.
    ##

    printf ("Rodando teste 1...\n");
    func_ex1    = @(x,y) x^3 + 1000 * sin(x * y);
    func_ex1_x  = @(x,y) 3 * x^2 + 1000 * y * cos(x * y);
    func_ex1_y  = @(x,y) 1000 * x * cos(x * y);
    func_ex1_xy = @(x,y) 1000 * (cos(x * y) - x * y * sin(x * y));
    test (func_ex1, func_ex1_x, func_ex1_y, func_ex1_xy, ax, bx, ay, by, nx, ny, IMAGE_WIDTH, IMAGE_HEIGHT, "test1");

    printf ("Rodando teste 2...\n");
    func_ex2    = @(x,y) x^3 + y^3;
    func_ex2_x  = @(x,y) 3*x^2;
    func_ex2_y  = @(x,y) 3*y^2;
    func_ex2_xy = @(x,y) 0;
    test (func_ex2, func_ex2_x, func_ex2_y, func_ex2_xy, ax, bx, ay, by, nx, ny, IMAGE_WIDTH, IMAGE_HEIGHT, "test2");


endfunction
