#include <stdio.h>
#include <stdbool.h>
#include <allegro.h>
#include "list_operations.c"
#include "main_operations.c"
#include "game.c"
#include "resource.h"

int main(int argc, char *argv[]){

    int level   = 1;
    strcpy(name, "USER");

    initInterface();

    if(!userExist()){
        createData(true);
    }
    getUser(&level);

    List *list_user = createList();

    int init = 4;
    initHome(list_user, &init);

    while(!exitGame && init != 1){

        switch(init){
            case 0:
                // ajuda
                showView(false);
                init = 5;
                break;
            case 2:
                //sobre
                showView(true);
                init = 5;
                break;
            case 3:
                // perfil
                createData(false);
                getUser(&level);
                init = 5;
                break;
            case 4:
                //iniciar
                startGame(&level, list_user, &init);
                break;
            case 5:
                // home
                destroyList(list_user);
                list_user   = createList();
                init        = 4;
                initHome(list_user, &init);

                break;
        }
    }
    return 0;
}
END_OF_MAIN()
