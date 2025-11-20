// main.c
#include "ecommerce.h"

int main() {
    buildCatalog();
    initQueue(&history);
    printf("Interactive E-Commerce Cart Simulation (Advanced DS)\n");

    int authed = 0;
    while (!authed) {
        auth_menu();
        int a; 
        if (scanf("%d",&a)!=1) { while(getchar()!='\n'); printf("Invalid.\n"); continue; }
        if (a == 1) register_flow();
        else if (a == 2) { if (login_flow()) authed = 1; }
        else if (a == 3) { printf("Goodbye!\n"); return 0; }
        else printf("Invalid.\n");
    }

    while (1) {
        main_menu_display();
        int choice; 
        if (scanf("%d",&choice)!=1) { while(getchar()!='\n'); printf("Invalid.\n"); continue; }
        if (choice == 1) addItemInteractive();
        else if (choice == 2) deleteItemInteractive();
        else if (choice == 3) viewCart();
        else if (choice == 4) sortMenu();
        else if (choice == 5) buyAndEmptyCart();
        else if (choice == 6) {
            save_cart_to_file(current_user);
            printf("Logged out. Bye %s!\n", current_user);
            freeCart(); 
            // freeUndoStack(); 
            initQueue(&history);
            current_user[0] = '\0'; authed = 0;
            while (!authed) {
                auth_menu();
                int a; if (scanf("%d",&a)!=1) { while(getchar()!='\n'); continue; }
                if (a == 1) register_flow();
                else if (a == 2) { if (login_flow()) authed = 1; }
                else if (a == 3) return 0;
            }
        }
        else if (choice == 7) {
            save_cart_to_file(current_user);
            printf("Saved. Goodbye!\n");
            break;
        }
        else printf("Invalid.\n");
    }

    freeCart();
    // freeUndoStack();
    return 0;
}