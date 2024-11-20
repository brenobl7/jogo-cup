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
    al_install_mouse();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    al_set_window_position(display, 300, 100);

    //declarando menu e timer

    ALLEGRO_BITMAP* Menu = al_load_bitmap("./imagens/Menu.JPG");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_BITMAP * sprite = al_load_bitmap("./imagens/teste.png");

    //Registrando Eventos

    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_start_timer(timer);

    //frame da sprite

    float frame = 0.f;
    //Loop principal

    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue,&event);

        //clicar no x da janela

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }

        //posição do mouse

        int mouse_x = event.mouse.x;
        int mouse_y = event.mouse.y;

        //clica com o mouse no botão start

        if(266<=mouse_x && mouse_x <=532 && 225<=mouse_y && mouse_y<=300){

           if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1){

                //mudando fundo e sprite

                Menu = al_load_bitmap("./imagens/background.PNG");
                sprite = al_load_bitmap("./imagens/sprite.JPG");


           }
       }

        //Desenhando menu e sprite

        frame = frame + 0.09;
        if(frame >7){
            frame = 0.f;
        }


        al_draw_bitmap(Menu,0,0,0);
        al_draw_bitmap_region(sprite,180*(int)frame,250,180,180,0,380,0);
        al_flip_display();
    }

    //destruindo Display

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(Menu);
    al_destroy_bitmap(sprite);
    al_destroy_timer(timer);

    return 0;
}


