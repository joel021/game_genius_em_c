#define DATA "data\\data.txt"
#define USER "data\\user.txt"
#define BUFFERSIZE 128

bool exitGame = false;
char name[128];
char *text;
int timer = 0, item = 5;

void inputData(int *level, bool starting, int *clear_h);
void createData(bool starting);
bool userExist();
void getUser();
List *createList();
void closeGame();
void initInterface();
void initHome(List *list_user, int *menu);
void getButton(int *menu, int *p_horizontal, int *p_vertical, bool gamer, bool *clicked);
void showView(bool img);
void saveUser(int level);
int levelCompleted();

void delay(){
    timer+=100;
}

// salva no arquivo o numero de sequencias acertadas
void saveData(int sequences){
    char s[33];
    itoa (sequences,s,10);
    strcat(s, "\n");
    FILE* f = fopen(DATA, "a");
    fprintf(f, s);

    fclose(f);
}

// mostra as interfaces de help e about
void showView(bool img){
    // redefine o tamnho da tela
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 700, 0,0);
    FONT* f_title       = load_font("fonts/aharoni_16.pcx", NULL, NULL);
    FONT* f_text        = load_font("fonts/arial_12.pcx", NULL, NULL);
    BITMAP* d_buffer    = create_bitmap(800, 700);
    BITMAP* back        = load_bitmap("images/d_back.bmp", NULL);
    BITMAP* pysical     = load_bitmap("images/physical game.bmp", NULL);

    draw_sprite(d_buffer, back, 0, 0);
    rectfill(d_buffer, 0, 0, 800, 70, makecol(0,162,232));

    //void textprintf_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *fmt, ...);
    textprintf_ex(d_buffer, f_title, 20, 673, 0, -1, "Pressione ESC para voltar");

    char text[100];

    if(img){

        FILE *file = fopen("data/about.txt", "r");

        textprintf_ex(d_buffer, f_title, 20, 30, 0xFFFFFF, -1, "Sobre");
        textprintf_ex(d_buffer, f_text, 389, 640, 0, -1, "Imagem do Jogo fisico.");
        draw_sprite(d_buffer, pysical, 182, 252);

        int y = 100;
        while(fgets(text, 100, file) != NULL){
            text[(int)strlen(text)-1] = '\0';
            textout_justify_ex(d_buffer, f_text, text, 20, 200, y, 80, makecol(49, 49, 49), -1);
            y += text_height(f_text);
        }
        fclose(file);
    } else {
        textprintf_ex(d_buffer, f_title, 20, 30, 0xFFFFFF, -1, "Ajuda");

        FILE *file = fopen("data/help.txt", "r");
        int y = 100;
        while(fgets(text, 100, file) != NULL){
            text[(int)strlen(text)-1] = '\0';
            textout_justify_ex(d_buffer, f_text, text, 20, 200, y, 80, makecol(49, 49, 49), -1);
            y += text_height(f_text);
        }
        fclose(file);
    }
    draw_sprite(screen, d_buffer, 0, 0);
    while(!key[KEY_ESC] && !exitGame){}

    destroy_font(f_title);
    destroy_bitmap(d_buffer);
    destroy_bitmap(back);
    destroy_font(f_text);
    clear(screen);
    destroy_bitmap(pysical);
}

void getButton(int *item, int *p_horizontal, int *p_vertical, bool gamer, bool *clicked){

    if(key[KEY_DOWN]){
        if(*p_vertical >= 1 || gamer){
            // botao de baixo
            *item           = 3;
            *p_horizontal   = 1;
            *p_vertical     = 2;
        } else {
            //botao do meio
            *item           = 4;
            *p_horizontal   = *p_vertical = 1;
        }

    } else if(key[KEY_UP]){
        if(*p_vertical <= 1 || gamer){
            // botao e cima
            *item = 1;
            *p_horizontal  = 1;
            *p_vertical    = 0;
        } else{
            //botao do meio
            *item = 4;
            *p_horizontal  = *p_vertical = 1;
        }
    } else if(key[KEY_RIGHT]){
        if(*p_horizontal >= 1 || gamer){
            //botão direita
            *item           = 2;
            *p_horizontal   = 2;
            *p_vertical     = 1;
        }else{
            //botão do meio
            *item           = 4;
            *p_horizontal   = *p_vertical = 1;
        }
    } else if(key[KEY_LEFT]){
        if(*p_horizontal <= 1 || gamer){
            //botão esquerda
            *item = 0;
            *p_horizontal   = 0;
            *p_vertical     = 1;
        } else {
            // botão do meio
            *item           = 4;
            *p_horizontal   = *p_vertical = 1;
        }
    }
	//DETECTANDO CLICK DO MOUSE
	if((mouse_b & 1) && gamer){

		if(((mouse_x>160) && (mouse_x<280)) && ((mouse_y>160) && (mouse_y<380))){

			//botão esquerda
            *item = 0;
            *p_horizontal   = 0;
            *p_vertical     = 1;
		}
		if(((mouse_x>280) && (mouse_x<550)) && ((mouse_y>76) && (mouse_y<160))){

			// botao e cima
            *item = 1;
            *p_horizontal  = 1;
            *p_vertical    = 0;
		}
		if(((mouse_x>520) && (mouse_x<630)) && ((mouse_y>160) && (mouse_y<370))){
			//botão direita
            *item           = 2;
            *p_horizontal   = 2;
            *p_vertical     = 1;
		}
		if(((mouse_x>250) && (mouse_x<520)) && ((mouse_y>360) && (mouse_y<450))){
			// botao de baixo
            *item           = 3;
            *p_horizontal   = 1;
            *p_vertical     = 2;
		}
	}else if((mouse_b & 1) && !gamer){

        if(((mouse_x>280) && (mouse_x<350)) && ((mouse_y>135) && (mouse_y<210))){

            //ajuda
            *item = 0;
            *p_horizontal   = 0;
            *p_vertical     = 1;
            *clicked        = true;

        }
        if(((mouse_x>360) && (mouse_x<475)) && ((mouse_y>101) && (mouse_y<137))){

            //sair
            *item = 1;
            *p_horizontal  = 1;
            *p_vertical    = 0;
            *clicked        = true;

        }
        if(((mouse_x>312) && (mouse_x<445)) && ((mouse_y>204) && (mouse_y<258))){

            //perfil
            *item           = 3;
            *p_horizontal   = 1;
            *p_vertical     = 2;
            *clicked        = true;

        }
        if(((mouse_x>355) && (mouse_x<448)) && ((mouse_y>131) && (mouse_y<202))){

            //iniciar
            *item           = 4;
            *p_horizontal   = *p_vertical = 1;
            *clicked        = true;

        }
        if(((mouse_x>447) && (mouse_x<514)) && ((mouse_y>138) && (mouse_y<236))){

            //sobre
            *item           = 2;
            *p_horizontal   = 2;
            *p_vertical     = 1;
            *clicked        = true;

        }
	}
     //FINAL DO IF DO MOUSE
}

void initInterface(){
// inicialização
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(32);
    // modo de video, resolção:800x600, inicia:(0,0)
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0,0);
    set_window_title("Genius");
    // botão fechar
    set_close_button_callback(closeGame);
    install_int_ex(delay, MSEC_TO_TIMER(100));
}

void closeGame(){
     exitGame = true;
}

int levelCompleted(){
    // recebe o nível que ele já alcançou
    char text[100];
    FILE *a = fopen("data/a.txt", "r");
    fgets(text, 100, a);
    int b = (int)atoi(text);
    fclose(a);

    return b;
}
// recebe os dados do usuário e salva no arquivo
void createData(bool starting){

    // recebe o nível que ele já alcançou
    int b = levelCompleted();

    // agora, level pode assumir valores de 1 até b
    int level = b;
    int clear_h;

    // recebe dados do usuário
    inputData(&level, starting, &clear_h);

    // salva os dados
    saveUser(level);
    // cria arquivo de lista caso não exista
    FILE *file = fopen(DATA, "r");
    if(file == NULL || clear_h == 1){
        fclose(file);
        file = fopen(DATA, "w");
    }
    fclose(file);

}

void saveUser(int level){
    FILE *file = fopen(USER, "w");
    // escreve os dados no arquivo
    fprintf(file, "%s\n%i", name, level);
    fclose(file);

    if(level > levelCompleted()){
        FILE *file = fopen("data/a.txt", "w");
        // escreve os dados no arquivo
        fprintf(file, "%i", level);
        fclose(file);
    }
}
bool userExist(){
    FILE *file = fopen(USER, "r");

    if(file == NULL){
        fclose(file);
        return false;
    }else{
        fclose(file);
        return true;
    }

}

// pega os valores para name e level no arquivo
void getUser(int *level){
    FILE *file = fopen(USER, "r");
    char text[100];

    fgets(text, 100, file);
    strcpy(name, text);
    name[(int)strlen(name)-1] = '\0'; // retira o \n da linha
    fgets(text, 100, file);
    *level = (int)atoi(text);

    fclose(file);
}

// cria a lista de histórico e ordena em ordem decrescente
List *createList(){
    char text[100];
    List *list_user = newList();
    DataNode data;

    FILE *file = fopen(DATA, "r");

    //adicionar dados de histótico a lista
    while(fgets(text, 100, file) != NULL){
        data.value = (int)atoi(text);
        push(list_user, data);
    }

    fclose(file);
    decSort(list_user);

    // limita a lista a um tamnho de 90 pontuações
    while (list_user -> size > 90){
        // apaga o primeiro elemento da lista, que é o primeiro dado adicionado
        pop(list_user);
    }

    return list_user;
}

void inputData(int *level, bool starting, int *clear_h){

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0,0);

    // posição do texto
    *clear_h         = 0;
    bool input_level = false;
    int input_clear  = 0;
    int color        = 0xFFFFFF;

    char    edittext[128];
    BITMAP *back    = load_bitmap("images/back.bmp", NULL);

    // cria um buffer para escrever os textos e a imagem de fundo.
    BITMAP *buffer  = create_bitmap(360, 100);

    int     caret   = 0;
    int l           = 0;
    int b           = *level;// guardaremos o valor de level inicialmente.

    char asscii;

    memset(edittext, 0, sizeof(edittext));

    int j = 2;

    if(!starting)
        j = 3;

    while (l != j)
    {
       clear(buffer);

       //escreve a imagem de fundo no buffer em (0, 60) do buffer.
       draw_sprite(buffer, back, 0, 60);

       if(l == 0)
            textprintf_ex(buffer, font, 10, 10, color, -1, "Digite seu nome:");
       else if(l == 1){
            int a = b;
            if(a < 2)
                a = 2;
            textprintf_ex(buffer, font, 10, 10, color, -1, "Digite um nivel entre 1 e %i.", a);
       }
        else if(l == 2)
            textprintf_ex(buffer, font, 10, 10, color, -1, "1 para limpar e 0 para deixar o historico.");
       // desenha cursor no buffer criado
       vline(buffer, ( caret * 8 ) + 10, 68, 78, 0xFFFFFF);

       if(keypressed())
       {
                color         = 0xFFFFFF;
                // newkey = numero correspondente a alguma tecla clicada. Retorna no formato ASCII
                // leia https://liballeg.org/stabledocs/en/alleg006.html#readkey
                int  newkey   = readkey();


                char ASCII    = newkey & 0xff;
                char scancode = newkey >> 8;

                /* Acrescentar somente numeros e letras */
                if((ASCII >= 48 && ASCII <= 57) || (ASCII >= 65 && ASCII <= 90) || (ASCII >= 97 && ASCII <= 122)){
                    asscii = ASCII;

                    if(caret < 128 - 1)
                    {
                        // só escreve caso já não exista nivel ou
                        if((l == 1 && input_level) || (l == 2 && input_clear == 1)){
                            edittext[0] = ASCII;
                            caret = 1;
                        } else {
                            edittext[caret] = ASCII;
                            caret++;
                            edittext[caret] = '\0';
                        }
                    }
                } else if(scancode == KEY_BACKSPACE){
                     if (caret > 0)
                        caret--;

                     edittext[caret] = '\0';

                     // caso o texto a ser digitado não seja o nome e o nível já tenha sido digitado, então, o nível vai ser corrigido pelo usuário ainda.
                     if(l == 1 && input_level)
                        input_level = false;
                    if(l == 2 && input_clear == 1)
                        input_clear = 0;
                } else if(scancode == KEY_ENTER){

                    if(l == 0){
                        strcpy(name, edittext);

                        if(strlen(edittext) > 0)
                            l = 1;
                        else
                            color = 0xff0000;
                    } else if(l == 1){
                        // o usuário digitou o nível
                        *level = (int)atoi(edittext);

                        if((b < 3 && asscii >= 49 && asscii <= 50) || (b == 3 && asscii >= 49 && asscii <= 51) || (b == 4 && asscii >= 49 && asscii <= 52)){
                            input_level = true;
                            l = 2;
                        } else
                            color = 0xff0000;

                    } else {
                        // digitou se limpa ou não o histórico
                        // o usuário digitou o nível
                        *clear_h = (int)atoi(edittext);

                        if(asscii >= 48 && asscii <= 49){
                            input_clear = 1;
                            l = 3;
                        } else
                            color = 0xff0000;
                    }
                    // retorna o cursor para a posição inicial, apaga todo valor da string
                    caret = 0;
                    memset(edittext, 0, sizeof(edittext));
                }

         }
        // l = 0 -> digitando nome; l = 1 -> digitando nível;
         // escreve texto em (xt, yt) do buffer
         textprintf_ex(buffer, font, 10, 70, 0xFFFFFF, -1, "%s", edittext);

         // escreve o buffer na screen em (0, 0)
        ///blit(struct BITMAP* source, struct BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
         blit(buffer, screen, 0, 0, 240, 240, 800, 600);
         show_mouse(screen);
    }

    destroy_bitmap(buffer);
    destroy_bitmap(back);
    clear(screen);
}

/// IMPRIMRIR EM BLOCOS NA TELA
BITMAP* printList(List *list_user){
    // largura e altura dos blocos
    int w_b = 250, h_b = 230;

    // a partir de 300 que é desenhado os blocos
    int y   = 315;

    /// divisão de blocos, cada bloco vai ter até 10 potuações, c é colunas colunas, b é blocos, l é linhas de blocos
    /// p é posição ou rank da pontuação
    float s1    = (list_user -> size)/10.0;
    int b       = s1;
    int l       = s1/3;

    // se a divisão por 10 não for exata, tem mais um bloco a ser adicionado porque b só recebe a parte inteira
    if(s1-b > 0)
        b++;

    // se a divisão pela quantidade de blocos suportados em uma linha der um número quebrado, temos que adicionar mais uma linha
    if((s1/3)-l > 0)
        l++;

    /// largura e altura do buffer eajusta a janela.
    int w = 800, h = l*230+345;

    // não desenha caso seja muita coisa.

    /*
    if(l > 3){
        BITMAP *buffer_home  = create_bitmap(800, 600);
        textprintf_ex(buffer_home, font, 390, 315, 0xFFFFFF, -1, "Nao eh possivel informar o seu rank de partidas.");
        return buffer_home;
    }*/
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, w, h, 0,0);

    //contadores
    int i = 0, j;

    //cria o buffer "janela que vai gruadar todo o conteudo e escrever na screen"
    BITMAP *buffer_home  = create_bitmap(800, h);
    BITMAP *back_rank    = load_bitmap("images/background_rank.bmp", NULL);

    // aloca memória dinamicamente para o conteudo text
    text = (char*) malloc((list_user -> size)*sizeof(char));
    char s[33];

    //decSort(list_user);
    Node *pointer = list_user -> head;

    clear(buffer_home);

    // cor de fundo
    rectfill(buffer_home, 0, 0, 800, 300, makecol(32,32,32));

    // contador posição rank e contador de blocos de 10.
    int p1 = 10, p = 1;

    // fonte a ser usada
    FONT* f_blocks      = load_font("fonts/calibri_11.pcx", NULL, NULL);
    FONT* f_t_blocks    = load_font("fonts/calibri_bold_11.pcx", NULL, NULL);
    // cria os blocos
    for(i = 0; i < l; i++){
        // colunas
        int c;

        if(b >= 3){
            c = 3;
            b -= 3;
        } else
            c = b;

        // posição inicial do bloco, iniciando a partir de 300 em y
        int x = 10;

        //posição inicial do texto
        int x_t1 = x+10, x_t2 = x+70, x_t3 = x+170;

        for(j = 0; j < c; j++){
            int y_t = y+10;
            strcpy(text, "");

            // desenha bloco
            draw_sprite(buffer_home, back_rank, x, y);

            //rectfill(buffer_home, x, y, w_b, h_b, makecol(32,32,32));

            if(i == 0 || j == 0){
                textprintf_ex(buffer_home, f_t_blocks, x_t1, y_t, 0xFFFFFF, -1, "Rank");
                textprintf_ex(buffer_home, f_t_blocks, x_t2, y_t, 0xFFFFFF, -1, "Pontuacao");
                textprintf_ex(buffer_home, f_t_blocks, x_t3, y_t, 0xFFFFFF, -1, "Nivel");
            }

            y_t += 20;

            // imprimir em 10 e 10
            while(pointer != NULL && p <= p1){

                // escreve rank
                itoa (p,s,10);
                strcpy(text, s);
                strcat(text, "#");
                textprintf_ex(buffer_home, f_blocks, x_t1, y_t, 0xFFFFFF, -1, text);

                // escreve pontuacao
                itoa (pointer -> data.value,s,10);
                strcpy(text, s);
                textprintf_ex(buffer_home, f_blocks, x_t2, y_t, 0xFFFFFF, -1, text);

                if(pointer -> data.value < 8)
                    itoa (1,s,10);
                else if(pointer -> data.value < 14)
                    itoa (2,s,10);
                else if(pointer -> data.value < 20)
                    itoa (3,s,10);
                else if(pointer -> data.value <= 31)
                    itoa (4,s,10);

                // escreve nivel
                strcpy(text, s);
                textprintf_ex(buffer_home, f_blocks, x_t3, y_t, 0xFFFFFF, -1, text);

                pointer = pointer -> next;
                p++;

                // adiciona espaço de 20px para o novo rexto, 10 de espaço e 10 de tamanho que o texto deve ocupar.
                y_t += 20;
            }

            p1   += 10;
            x    += 265;

            x_t1 += 265;
            x_t2 += 265;
            x_t3 += 265;
        }
        y   += 245;
    }

    if(i == 0)
        textprintf_ex(buffer_home, f_blocks, 390, 315, 0xFFFFFF, -1, "Sem rank.");

    // retorna todos os blocos para serem desenhados

    destroy_font(f_blocks);
    destroy_font(f_t_blocks);
    return buffer_home;
}

void initHome(List *list_user, int* menu) {
    int p_vertical    = 1;//posição menu vertical,
    int p_horizontal  = 1; // posição menu horizontal

    //menu botão selecionado: 0 = ajuda, 1 = sair, 2 = iniciar, 3 = sobre, 4 = perfil

    BITMAP *buffer_home = printList(list_user);

    rectfill(buffer_home, 0, 0, 800, 70, makecol(0,162,232));

    FONT* f_title = load_font("fonts/aharoni_16.pcx", NULL, NULL);
    textprintf_ex(buffer_home, f_title, 270, 30, 0xFFFFFF, -1, "Ola, %s! Eu sou o Genius!.", name);

    BITMAP* genius_home = load_bitmap("images/button_start.bmp", NULL);
    SAMPLE* s_click     = load_sample("sounds/click.wav");

    // desenha a partir de 0
    ///blit(struct BITMAP* source, struct BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
    draw_sprite(buffer_home, genius_home, 250, 100);

    float delay     = 0;
    bool clicked    = false;
    int h_menu;
    while(!key[KEY_ENTER] && !exitGame && !clicked){
        delay       = timer;
        h_menu      = *menu;
        getButton(menu, &p_horizontal, &p_vertical, false, &clicked);

        switch(*menu){
            case 0:
                // ajuda
                destroy_bitmap(genius_home);
                genius_home = load_bitmap("images/button_help.bmp", NULL);
                break;
            case 1:
                // sair
                destroy_bitmap(genius_home);
                genius_home = load_bitmap("images/button_exit.bmp", NULL);
                break;
            case 2:
                // sobre
                destroy_bitmap(genius_home);
                genius_home = load_bitmap("images/button_about.bmp", NULL);
                break;
            case 3:
                // perfil
                destroy_bitmap(genius_home);
                genius_home = load_bitmap("images/button_profile.bmp", NULL);
                break;
            case 4:
                // iniciar
                destroy_bitmap(genius_home);
                genius_home = load_bitmap("images/button_start.bmp", NULL);
                break;
        }

        if(h_menu != *menu){
            play_sample(s_click, 255, 128, 1000, 0);
        }

        draw_sprite(buffer_home, genius_home, 250, 100);
        draw_sprite(screen, buffer_home, 0, 0);
        show_mouse(screen);

        while(timer == delay){}
    }
    destroy_bitmap(genius_home);
    destroy_bitmap(buffer_home);
    destroy_font(f_title);
    destroy_sample(s_click);
    clear(screen);
}
