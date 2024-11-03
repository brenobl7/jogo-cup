#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
int main()
{
    //iniciando o allegro

    al_init();
    al_set_app_name("jogo");

    //display da janela

    int h = 600;
    int w = 800;

    ALLEGRO_DISPLAY* display = al_create_display(w,h);

    //adicionando eventos

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue,al_get_display_event_source(display));

    //loop principal do jogo

    while(true){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue,&event);
        //clica no x da janela fecha;
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
    }
    return 0;
}

