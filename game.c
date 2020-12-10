void startGame(int *level, List* list, int *init);
void salveData(int sequences);
BITMAP* getImg(char *text, int item);
int returnQofLevel(int level);
void showWaiting(BITMAP* buffer_game, BITMAP* img_genius, int s);
void turnLevel(int *level, int i);
void addColor(List* list, int plus);
void initialSettings(List *list, int level, int *wait_time, int *i);
void showMessage(BITMAP* buffer_game, int level, bool error);

// função que inicia o jogo
void startGame(int *level, List* list, int *init){
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0,0);
    bool error = false;
    destroyList(list);

    list = newList();
    int wait_time, i, j;

    int t = 2000;
    // define a lista e o tempo de espera de acordo com o nível
    initialSettings(list, *level, &wait_time, &i);

    BITMAP* buffer_game     = create_bitmap(800, 600);
    BITMAP* img_genius      = load_bitmap("images/img_genius.bmp", NULL);
    BITMAP* input_0         = load_bitmap("images/input_0.bmp", NULL);
    BITMAP* input_1         = load_bitmap("images/input_1.bmp", NULL);
    BITMAP* input_2         = load_bitmap("images/input_2.bmp", NULL);
    BITMAP* input_3         = load_bitmap("images/input_3.bmp", NULL);
    BITMAP* output_0        = load_bitmap("images/output_0.bmp", NULL);
    BITMAP* output_1        = load_bitmap("images/output_1.bmp", NULL);
    BITMAP* output_2        = load_bitmap("images/output_2.bmp", NULL);
    BITMAP* output_3        = load_bitmap("images/output_3.bmp", NULL);

    // carregando audios
    SAMPLE *red     = load_sample("sounds/red.wav");
    SAMPLE *blue    = load_sample("sounds/blue.wav");
    SAMPLE *yellow  = load_sample("sounds/yellow.wav");
    SAMPLE *green   = load_sample("sounds/green.wav");
    SAMPLE *s_init  = load_sample("sounds/init.wav");

    int q = returnQofLevel(*level); // define a quatidade de sequencias de acordo com o nível

    int count = 0;
    for( ; i < q && !error && !exitGame; i++){

        //mostra a imagem img_genius por 2 segundo
        play_sample(s_init, 255, 128, 1000, 0);
        showWaiting(buffer_game, img_genius, 2000);

        Node *pointer = list -> head;

        timer = 0;
        bool pause;
        for(j = 0; j < list -> size && !exitGame; j++){
            switch(pointer -> data.value){
                case 0:
                    play_sample(green, 255, 128, 1000, 0);
                    showWaiting(buffer_game, output_0, t);
                    stop_sample(green);
                    break;
                case 1:
                    play_sample(red, 255, 128, 1000, 0);
                    showWaiting(buffer_game, output_1, t);
                    stop_sample(red);
                    break;
                case 2:
                    play_sample(blue, 255, 128, 1000, 0);
                    showWaiting(buffer_game, output_2, t);
                    stop_sample(blue);
                    break;
                case 3:
                    play_sample(yellow, 255, 128, 1000, 0);
                    showWaiting(buffer_game, output_3, t);
                    stop_sample(yellow);
                    break;
            }

			// mostra a imagem padrao por t milissegundos
            showWaiting(buffer_game, img_genius, 600);

            pointer = pointer -> next;
        }

        pointer = list -> head;
        for(j = 0; j < list -> size && !exitGame; j++){

            item                = 4;
            timer               = 1;
            int p_horizontal    = 1;
            int p_vertical      = 1;

            FONT *f             = load_font("fonts/calibri_12.pcx", NULL, NULL);

            while(timer <= wait_time && item == 4 && !exitGame){
                draw_sprite(buffer_game, img_genius, 0, 0);
                textprintf_ex(buffer_game, f, 76, 20, 0xFFFFFF, -1, "Voce esta demorando %.2f ssegundos, maximo de %.2f segundos.", timer/1000.0, wait_time/1000.0);
                draw_sprite(screen, buffer_game, 0, 0);
                show_mouse(screen);
                getButton(&item, &p_horizontal, &p_vertical, true, NULL);
                clear(buffer_game);
            }
            destroy_font(f);

            switch(item){
                case 0:
                    play_sample(green, 255, 128, 1000, 0);
                    showWaiting(buffer_game, input_0, 500);
                    //stop_sample(green);
                    break;
                case 1:
                    play_sample(red, 255, 128, 1000, 0);
                    showWaiting(buffer_game, input_1, 500);
                    ///stop_sample(red);
                    break;
                case 2:
                    play_sample(blue, 255, 128, 1000, 0);
                    showWaiting(buffer_game, input_2, 500);
                    ///stop_sample(blue);
                    break;
                case 3:
                    play_sample(yellow, 255, 128, 1000, 0);
                    showWaiting(buffer_game, input_3, 500);
                    ///stop_sample(yellow);
                    break;
            }

            // verficar a resposta
            if(item != pointer -> data.value && !exitGame){
                showMessage(buffer_game, *level, true);
                *init = 5;
                error = true;
                count--;
                break;
            }
            pointer = pointer -> next;
        }

        // redefine os nível de acordo com o tamanho da lista
        turnLevel(level, list -> size);

        // adiciona numero de uma cor aleatória na lista,
        addColor(list, timer);
        count++;
        clear(screen);

        // aumenta velocidade das cores piscando
        t = t-i;

        if(i == q-1 && !error){
            // passou de nivel
            showMessage(buffer_game, *level, false);

            // nosso novo q
            q = returnQofLevel(*level);
        }
    }

    // salva o histórico
    saveData(count);
    // salva os dados de usuários
    saveUser(*level);

    // a variável error ser falsa pode ser que o usuário ganhou ou ele tenha clicado em sair. Caso tenha errado
    if(i == q && !error){
        *init = 5;
        showMessage(buffer_game, *level, false);
    } else if(!error){
        // se clicou em fechar
        *init = 1;
    }

    destroy_bitmap(buffer_game);
    destroy_bitmap(img_genius);
    destroy_bitmap(input_0);
    destroy_bitmap(input_1);
    destroy_bitmap(input_2);
    destroy_bitmap(input_3);
    destroy_bitmap(output_0);
    destroy_bitmap(output_1);
    destroy_bitmap(output_2);
    destroy_bitmap(output_3);
    destroy_sample(red);
    destroy_sample(blue);
    destroy_sample(green);
    destroy_sample(yellow);
    destroy_sample(s_init);

    clear(screen);
}

void showMessage(BITMAP* buffer_game, int level, bool error){
    SAMPLE *sound1      = load_sample("sounds/six_short.wav");
    SAMPLE *sound2      = load_sample("sounds/final.wav");
    SAMPLE *sound3      = load_sample("sounds/error.wav");
    BITMAP *back_cong;

    if(error)
        back_cong = load_bitmap("images/back_error.bmp", NULL);
    else
        back_cong   = load_bitmap("images/back_cong.bmp", NULL);

    FONT* f_title       = load_font("fonts/aharoni_16.pcx", NULL, NULL);

    if(level != 4 && !error)
        play_sample(sound1, 255, 128, 1000, 0);
    else if(!error)
        play_sample(sound2, 255, 128, 1000, 0);
    else
        play_sample(sound3, 255, 128, 1000, 0);

    float mseconds    = 0;
    timer           = 0;
    float delay1    = 0;
    delay1          = timer;

    for(mseconds = 0; mseconds < 20000.0 && !key[KEY_ESC] && !key[KEY_ENTER]; mseconds += 10.0){
        clear(buffer_game);

        draw_sprite(buffer_game, back_cong, 0, 0);

        if(level != 4 && !error)
            textprintf_ex(buffer_game, f_title, 200, 10, 0xFFFFFF, -1, "Voce passou para o nivel %i", level);
        else if(!error)
            textprintf_ex(buffer_game, f_title, 200, 10, 0xFFFFFF, -1, "Voce ganhou e eu perdi.");
        else
            textprintf_ex(buffer_game, f_title, 200, 10, 0xFFFFFF, -1, "Nivel = %i", level);

        textprintf_ex(buffer_game, f_title, 200, 36, 0xFFFFFF, -1, "Isso fecharah em %.2f", mseconds/1000.0);

        draw_sprite(screen, buffer_game, 0, 0);

        // espera 100 milisegundos
        while(timer == delay1){}
    }

    clear(buffer_game);
    destroy_bitmap(back_cong);
    destroy_font(f_title);
    destroy_sample(sound1);
    destroy_sample(sound2);
    destroy_sample(sound3);
}

void addColor(List* list, int plus){
    DataNode node;
    srand((unsigned)time(NULL)+plus);
    node.value = rand() % 4;
    push(list, node);
}

// configurações iniciais para iniciar a partida
void initialSettings(List *list, int level, int *wait_time, int *i){
    *i      = returnQofLevel(level-1);
    int i2  = *i;

    do {
        addColor(list, i2);
        i2--;
    } while(i2 > 0);

    *wait_time = 5000;
}

void turnLevel(int *level, int i){
    if(i >= 8 && i < 14 && *level < 2)
        *level = 2;
    else if(i >= 14 && i < 20 && *level < 3)
        *level = 3;
    else if(i >= 20 && i <= 31 && *level < 4)
        *level = 4;
}

//mostra a imagem por ms milissegundos e depois destroi ela
void showWaiting(BITMAP* buffer_game, BITMAP* img_genius, int ms){
    int mseconds    = 0;
    timer           = 0;
    float delay1    = 0;
    delay1          = timer;

    for(mseconds = 0; mseconds < ms; mseconds += 10){
        clear(buffer_game);

        draw_sprite(buffer_game, img_genius, 0, 0);
        draw_sprite(screen, buffer_game, 0, 0);

        // espera 100 milisegundos
        while(timer == delay1){}
    }
    clear(buffer_game);
}

BITMAP* getImg(char *text, int item0){
    // preparando a variável com o endereço da imagem
    char str_img[33];

    strcpy(str_img, "images/");

    strcat(str_img, text);
    strcat(str_img, "_");

    char s[33];
    itoa(item0, s, 10);

    strcat(str_img, s);

    strcat(str_img, ".bmp");

    BITMAP* img_genius = load_bitmap(str_img, NULL);

    return img_genius;
}

int returnQofLevel(int level){
    switch(level){
        case 1:
            return 8;
            break;
        case 2:
            return 14;
            break;
        case 3:
            return 20;
            break;
        case 4:
            return 31;
            break;
    }
    return 0;
}
