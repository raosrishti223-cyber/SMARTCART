// ecommerce.h
#ifndef ECOMMERCE_H
#define ECOMMERCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NAME_LEN 50
#define BRAND_LEN 40
#define CAT_LEN 20
#define USERNAME_LEN 40
#define PASS_LEN 7
#define MAX_QUEUE 500 //for category history


// ====================== STRUCTURES ======================
//BST NODES
typedef struct Product {
    int id;
    char category[CAT_LEN];
    char item[NAME_LEN];
    char brand[BRAND_LEN];
    float price;
    float rating;
    struct Product *left, *right; //pointers for BST
} Product;
//LL node 
typedef struct CartNode {
    Product *product;//pointer to product in catalog
    struct CartNode *next;
} CartNode;



//History Queue(Circular Queues)
typedef struct {
    char data[MAX_QUEUE][CAT_LEN];
    int front, rear, size;
} HistoryQueue;

// ====================== FUNCTION DECLARATIONS ======================

// BST & Catalog
Product* createProductNode(int id, const char* cat, const char* item, const char* brand, float price, float rating);
Product* insertBST(Product *root, Product *newNode);
Product* searchBST(Product *root, int id); //searches tree for product by id
void buildCatalog();

// Cart (Linked List)
CartNode* createCartNode(Product *p);
void addToCart(Product *p);
int removeFromCart(int index);
int cartSize();
void freeCart();
// void freeUndoStack();

// Queue (History)
void initQueue(HistoryQueue *q);
int isQueueFull(HistoryQueue *q);
int isQueueEmpty(HistoryQueue *q);
void enqueueHistory(HistoryQueue *q, const char *cat);
char* dequeueHistory(HistoryQueue *q);
char* getLastCategory();

// User Management
int user_exists(const char *username);
int register_user(const char *username, const char *password);
int verify_user(const char *username, const char *password);

// Cart Persistence
void save_cart_to_file(const char *username);
void load_cart_from_file(const char *username);

// Display & Interaction
void showCategories();
void listProductsByCategory(const char *cat);
void viewCart();
void addItemInteractive();
void deleteItemInteractive();
void buyAndEmptyCart();
void sortMenu();
void main_menu_display(); // Main Menu
void auth_menu();// Authentication
void register_flow();
int login_flow();

// Recommendations
int inCart(Product *p);
void getTop3NotInCart(const char *cat, Product *result[3]);

// External globals (declared in main.c)
extern Product *catalog_root; //BST root
extern CartNode *cart_head; //Cart Linked List head
// extern UndoNode *undo_stack; //Undo Stack top
extern HistoryQueue history; //Category history queue
extern char current_user[USERNAME_LEN]; //Logged in user

#endif