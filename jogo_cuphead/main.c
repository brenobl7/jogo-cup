#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
int main()
{
    //configurações básicas janela

    al_init();
    al_set_app_name("Dark Punch");
    al_init_image_addon();
    al_install_mouse();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    al_set_window_position(display, 300, 100);
    al_install_keyboard();
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
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    //frame da sprite
  int pos_x = 0, pos_y = 400;
    int current_frame_y = 0;
    float frame = 0.f;
    //Loop principal

    while(true){
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
      break;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT ){
      current_frame_y = 200;
      pos_x += 2;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_LEFT ){
      current_frame_y = 25;
      pos_x -= 2;

    }else if( event.keyboard.keycode == ALLEGRO_KEY_UP+ALLEGRO_KEY_SPACE ){
      current_frame_y = 230* 3;
      pos_y -= 20;
      al_rest(4.0);

    }

        //posição do mouse

        int mouse_x = event.mouse.x;
        int mouse_y = event.mouse.y;

        //clica com o mouse no botão start

        if(266<=mouse_x && mouse_x <=532 && 225<=mouse_y && mouse_y<=300){

           if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1){

                //mudando fundo e sprite

                Menu = al_load_bitmap("./imagens/background.PNG");
                sprite = al_load_bitmap("./imagens/sprite2trans.PNG");


           }
       }

        //Desenhando menu e sprite


        frame = frame + 0.09;
        if(frame >7){
            frame = 3.f;
        }


        al_draw_bitmap(Menu,0,0,0);                                      //altura


        al_draw_bitmap_region(sprite, 180 * (int)frame, current_frame_y, 110, 160, pos_x, pos_y, 0);
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


