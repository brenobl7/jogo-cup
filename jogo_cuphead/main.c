#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int main()
{
    //configurações básicas janela

    al_init();
    al_set_app_name("Dark Punch");
    al_init_image_addon();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    al_set_window_position(display, 300, 100);

    //declarando menu e timer

    ALLEGRO_BITMAP* Menu = al_load_bitmap("./imagens/Menu.JPG");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    //Registrando Eventos

    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    //Loop principal

    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue,&event);

        //clicar no x da janela

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }

        //Desenhando menu

        al_draw_bitmap(Menu,0,0,0);
        al_flip_display();
    }

    //destruindo Display

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}


