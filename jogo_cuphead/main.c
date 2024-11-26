#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main() {
    // Inicializações básicas
    al_init();
    al_set_app_name("Dark Punch");
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    al_set_window_position(display, 300, 100);

    // Recursos do jogo
    ALLEGRO_BITMAP* Menu = al_load_bitmap("./imagens/Menu.JPG");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_BITMAP* sprite = al_load_bitmap("./imagens/sprite_final.PNG");

    // Variáveis de controle
    int pos_x = 100, pos_y = 400; // Posição inicial do personagem
    int current_frame_y = 240;    // Coordenada inicial do estado parado
    float frame = 0.0;            // Controle de animação
    float vel_y = 0;              // Velocidade vertical
    float gravity = 0.5;          // Gravidade
    bool is_jumping = false;      // Estado de pulo
    bool is_attacking = false;    // Estado de ataque
    bool facing_left = false;     // Direção do personagem
    bool moving_left = false;     // Movimento para esquerda
    bool moving_right = false;    // Movimento para direita
    const int ground_y = 400;     // Altura do chão
    bool in_menu = true;          // Estado do menu

    // Configurando eventos
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

        // Controle do menu
        if (in_menu) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            if (266 <= mouse_x && mouse_x <= 532 && 225 <= mouse_y && mouse_y <= 300) {
                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
                    in_menu = false;
                    Menu = al_load_bitmap("./imagens/background.PNG");
                    sprite = al_load_bitmap("./imagens/sprite_final.PNG");
                }
            }
        } else {
            // Controle do teclado
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                // Controle do pulo
                if (event.keyboard.keycode == ALLEGRO_KEY_UP && !is_jumping && !is_attacking) {
                    vel_y = -10;
                    is_jumping = true;
                }

                // Controle do movimento para a direita
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && !is_attacking) {
                    moving_right = true;
                    facing_left = false;
                    current_frame_y = 200; // Andando para a direita
                }

                // Controle do movimento para a esquerda
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && !is_attacking) {
                    moving_left = true;
                    facing_left = true;
                    current_frame_y = 25; // Andando para a esquerda
                }

                // Controle do ataque
                if (event.keyboard.keycode == ALLEGRO_KEY_X && !is_attacking) {
                    is_attacking = true;
                    frame = 0; // Início da animação de ataque
                    current_frame_y = facing_left ? 1340 : 1500; // Ataque para a direção correta
                }
            }

            if (event.type == ALLEGRO_EVENT_KEY_UP) {
                // Libera o movimento após soltar as teclas de direção
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    moving_right = false;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    moving_left = false;
                }
            }

            // Atualização da posição apenas se não estiver atacando
            if (!is_attacking) {
                if (moving_right) pos_x += 2;
                if (moving_left) pos_x -= 2;
            }

            // Controle de física
            if (is_jumping) {
                pos_y += vel_y;
                vel_y += gravity;
                if (pos_y >= ground_y) {
                    pos_y = ground_y;
                    vel_y = 0;
                    is_jumping = false;
                }
            }

            // Animação de ataque
            if (is_attacking) {
                frame += 0.2; // Avança mais rápido para ciclos mais curtos
                if (frame >= 6) { // Finaliza o ataque após 5 frames
                    is_attacking = false; // Termina o ataque
                    frame = 0; // Reseta a animação

                    // Retorna ao estado parado ou andando
                    if (moving_right) {
                        current_frame_y = 200; // Andando para a direita
                    } else if (moving_left) {
                        current_frame_y = 25; // Andando para a esquerda
                    } else {
                        current_frame_y = 380; // Estado parado
                    }
                }
            }

            // Estado parado
            if (!moving_left && !moving_right && !is_jumping && !is_attacking) {
                current_frame_y = 380;
                frame = 4; // Reseta a animação
            } else if (!is_attacking) {
                // Animação de movimento
                frame += 0.07;
                if (frame > 7) frame = 3.0;
            }
        }

        // Renderização
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (in_menu) {
            al_draw_bitmap(Menu, 0, 0, 0);
        } else {
            al_draw_bitmap(Menu, 0, 0, 0);
            al_draw_bitmap_region(sprite, 180 * (int)frame, current_frame_y, 150, 160, pos_x, pos_y, 0);
        }

        al_flip_display();
    }

    // Finalização
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(Menu);
    al_destroy_bitmap(sprite);
    al_destroy_timer(timer);

    return 0;
}
