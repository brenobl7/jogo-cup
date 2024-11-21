#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main() {

    // Configurações básicas da janela

    al_init();
    al_set_app_name("Dark Punch");
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    al_set_window_position(display, 300, 100);

    // Declarando menu e timer

    ALLEGRO_BITMAP* Menu = al_load_bitmap("./imagens/Menu.JPG");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_BITMAP* sprite = al_load_bitmap("./imagens/teste.png");

    // Variáveis de controle

    int pos_x = 100, pos_y = 400;  // Posição do personagem
    int current_frame_y = 0;       // Linha da sprite
    float frame = 0.0;             // Controle de animação
    float vel_y = 0;               // Velocidade vertical
    float gravity = 0.5;           // Gravidade
    bool is_jumping = false;       // Verifica se está pulando

    const int ground_y = 400;      // Altura do chão
    bool in_menu = true;           // Controle do menu
    bool moving_left = false;      // Movimento para esquerda
    bool moving_right = false;     // Movimento para direita

    // Registrando Eventos

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    // Loop principal

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        // Posição do mouse

        int mouse_x = event.mouse.x;
        int mouse_y = event.mouse.y;

        // Controle do menu

        if (in_menu) {
            if (266 <= mouse_x && mouse_x <= 532 && 225 <= mouse_y && mouse_y <= 300) {
                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
                    in_menu = false;  // Sai do menu
                    Menu = al_load_bitmap("./imagens/background.PNG");  // Troca para o fundo do jogo
                    sprite = al_load_bitmap("./imagens/sprite_final.PNG");  // Troca o sprite
                }
            }
        } else {

            // Controle do teclado

            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_UP && !is_jumping ) {
                    vel_y = -10;        // Velocidade inicial do pulo
                    is_jumping = true;  // Está no ar


                }

                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    moving_right = true;
                    current_frame_y = 200;  // Define o frame para movimento à direita
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    moving_left = true;
                    current_frame_y = 25;  // Define o frame para movimento à esquerda
                }
            }

            if (event.type == ALLEGRO_EVENT_KEY_UP) {
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    moving_right = false;  // Para de mover à direita
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    moving_left = false;  // Para de mover à esquerda
                }
            }

            // Atualiza a posição horizontal

            if (moving_right) {
                pos_x += 2;  // Move para a direita
            }
            if (moving_left) {
                pos_x -= 2;  // Move para a esquerda
            }

            // Atualizando a posição vertical com física

            if (is_jumping) {
                pos_y += vel_y;       // Atualiza a posição
                vel_y += gravity;     // Aplica gravidade
                 //1190 o priemiro

                // Verifica se atingiu o chão

                if (pos_y >= ground_y) {
                    pos_y = ground_y; // Reseta para o chão
                    vel_y = 0;        // Para o movimento vertical
                    is_jumping = false;
                }
            }

        }

        // Animação do sprite

        frame += 0.07;
        if (frame > 7) {
            frame = 3.0;
        }

        // Renderização

        al_clear_to_color(al_map_rgb(0, 0, 0));  // Limpa a tela

        if (in_menu) {
            al_draw_bitmap(Menu, 0, 0, 0);  // Mostra o menu
        } else {
            al_draw_bitmap(Menu, 0, 0, 0);  // Mostra o fundo do jogo
            al_draw_bitmap_region(sprite, 180 * (int)frame, current_frame_y, 160, 160, pos_x, pos_y, 0);  // Mostra o personagem
        }

        al_flip_display();
    }

    // Destruindo recursos


    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(Menu);
    al_destroy_bitmap(sprite);
    al_destroy_timer(timer);

    return 0;
}




