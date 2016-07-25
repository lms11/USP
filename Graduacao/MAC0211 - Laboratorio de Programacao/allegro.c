#include "allegro.h"

int allegroInit () {
    if (!al_init ()) {
        fprintf (stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    /* Inclui bibliotecas da Allegro que permite criar as imagens  */
    if (!al_init_image_addon ()) {
        fprintf (stderr, "Falha ao inicializar add-on allegro_image.\n");
        return -1;
    }

    // al_init_primitives_addon ();
    al_init_font_addon ();

    if (!al_init_ttf_addon ()) {
        fprintf (stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return -1;
    }

    if (!al_install_audio ()) {
        fprintf(stderr, "Falha ao inicializar audio.\n");
        return -1;
    }

    if (!al_init_acodec_addon ()) {
        fprintf(stderr, "Falha ao inicializar audio codecs.\n");
        return -1;
    }

    if (!al_reserve_samples (51)) {
        fprintf(stderr, "Falha ao reservar samples.\n");
        return -1;
    }

    /* Verifica se o teclado foi inicializado */
    if (!al_install_keyboard ()) {
        fprintf (stderr, "Falha ao iniciar o teclado.\n");
        return -1;
    }

    /* Cria o display que será a imagem mostrada do jogo e que possui duas dimensões
       DISPLAY_W (largura) DISPLAY_H (altura).*/
    ALLEGRO_DISPLAY_MODE disp_data;
    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_MONITOR_INFO info;
    int i = 0;
    do {
      al_get_monitor_info(i++, &info);
    } while (!(info.x1 == 0 && info.y1 == 0));
    DISPLAY_W = info.x2 - info.x1;
    DISPLAY_H = info.y2 - info.y1;

    UNIVERSE_RATIO = 1.0 * DISPLAY_W / DISPLAY_H;
    UNIVERSE_H = 8e7;
    UNIVERSE_W = UNIVERSE_H * UNIVERSE_RATIO;
    SCALE_X = (DISPLAY_W / UNIVERSE_W);
    SCALE_Y = (DISPLAY_H / UNIVERSE_H);

    display = al_create_display (DISPLAY_W, DISPLAY_H);
    if (!display) {
        fprintf (stderr, "Falha ao criar janela.\n");
        return -1;
    }

    /* Bitmap do fundo */
    background_image = al_load_bitmap ("./images/space.jpg");
    if (!background_image) {
        fprintf (stderr, "Falha ao carregar 'images/space.jpg'.\n");
        al_destroy_display (display);
        return -1;
    }

    mainFont = al_load_ttf_font ("fonts/Starjedi.ttf", 48, 0);
    if (!mainFont) {
        fprintf(stderr, "Falha ao carregar 'fonts/Starjedi.ttf'.\n");
        al_destroy_display (display);
        al_destroy_bitmap (background_image);
        return -1;
    }

    background_sound = al_load_sample ("audios/lukhash.wav");
    if (!background_sound) {
        fprintf(stderr, "Falha ao carregar 'audios/lukhash.wav'.\n");
        al_destroy_display (display);
        al_destroy_bitmap (background_image);
        al_destroy_font (mainFont);
        return -1;
    }

    return 0;
}

void allegroDestroy () {
    al_destroy_display (display);
    al_destroy_bitmap (background_image);
    al_destroy_font (mainFont);
    al_destroy_sample (background_sound);
    al_shutdown_font_addon ();
    al_shutdown_ttf_addon ();
}
