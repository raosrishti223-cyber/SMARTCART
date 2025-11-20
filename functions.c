// functions.c
#include "ecommerce.h"

// ====================== GLOBAL DECLARATIONS (for extern) ======================
Product *catalog_root = NULL; //catalog BST root
CartNode *cart_head = NULL; //cart linked list head
HistoryQueue history = { .front = 0, .rear = 0, .size = 0 }; 
char current_user[USERNAME_LEN] = {0};

// ====================== CATALOG DATA ======================
Product electronics[] = {
    {1,"Electronics","Laptop","Lenovo",55000,4.4,NULL,NULL},
    {2,"Electronics","Laptop","HP",60000,4.3,NULL,NULL},
    {3,"Electronics","Laptop","Dell",58000,4.2,NULL,NULL},
    {4,"Electronics","Laptop","Asus",62000,4.1,NULL,NULL},
    {5,"Electronics","Charger","Lenovo",1500,4.0,NULL,NULL},
    {6,"Electronics","Charger","Boat",1200,3.8,NULL,NULL},
    {7,"Electronics","Charger","Apple",2500,4.6,NULL,NULL},
    {8,"Electronics","Headphones","Sony",3500,4.7,NULL,NULL},
    {9,"Electronics","Headphones","Boat",2000,3.9,NULL,NULL},
    {10,"Electronics","Mouse","Logitech",1000,4.5,NULL,NULL},
    {11,"Electronics","Keyboard","Logitech",1800,4.2,NULL,NULL},
    {12,"Electronics","Smartphone","Samsung",45000,4.6,NULL,NULL},
    {13,"Electronics","Smartphone","OnePlus",48000,4.4,NULL,NULL},
    {14,"Electronics","Powerbank","Mi",1500,4.0,NULL,NULL},
    {15,"Electronics","Speaker","JBL",4000,4.5,NULL,NULL}
};

Product stationery[] = {
    {16,"Stationery","Pen","Parker",300,4.6,NULL,NULL},
    {17,"Stationery","Pen","Cello",20,3.7,NULL,NULL},
    {18,"Stationery","Pen","Reynolds",15,3.9,NULL,NULL},
    {19,"Stationery","Notebook","Classmate",50,4.0,NULL,NULL},
    {20,"Stationery","Notebook","Camlin",60,3.8,NULL,NULL},
    {21,"Stationery","Notebook","Oxford",120,4.3,NULL,NULL},
    {22,"Stationery","Marker","Faber-Castell",100,4.5,NULL,NULL},
    {23,"Stationery","Marker","Camlin",25,3.6,NULL,NULL},
    {24,"Stationery","Eraser","Apsara",10,3.5,NULL,NULL},
    {25,"Stationery","Pencil","Nataraj",5,3.8,NULL,NULL},
    {26,"Stationery","Highlighter","Faber-Castell",90,4.4,NULL,NULL},
    {27,"Stationery","Ruler","Classmate",20,3.9,NULL,NULL},
    {28,"Stationery","Stapler","Kangaro",200,4.1,NULL,NULL},
    {29,"Stationery","Glue","Fevicol",30,4.2,NULL,NULL},
    {30,"Stationery","Scissors","Maped",80,4.0,NULL,NULL}
};

Product clothing[] = {
    {31,"Clothing","T-shirt","Nike",1200,4.4,NULL,NULL},
    {32,"Clothing","T-shirt","Adidas",1500,4.3,NULL,NULL},
    {33,"Clothing","T-shirt","Puma",1100,4.0,NULL,NULL},
    {34,"Clothing","Jeans","Levis",2500,4.5,NULL,NULL},
    {35,"Clothing","Jeans","Wrangler",2200,4.1,NULL,NULL},
    {36,"Clothing","Shirt","Peter England",1800,4.0,NULL,NULL},
    {37,"Clothing","Shirt","Van Heusen",2000,3.9,NULL,NULL},
    {38,"Clothing","Jacket","Puma",3500,4.2,NULL,NULL},
    {39,"Clothing","Jacket","Adidas",4000,4.3,NULL,NULL},
    {40,"Clothing","Saree","Biba",3000,4.1,NULL,NULL},
    {41,"Clothing","Kurta","Fabindia",1800,4.0,NULL,NULL},
    {42,"Clothing","Shoes","Nike",4500,4.6,NULL,NULL},
    {43,"Clothing","Shoes","Bata",2000,3.8,NULL,NULL},
    {44,"Clothing","Sweater","Monte Carlo",2500,4.0,NULL,NULL},
    {45,"Clothing","Cap","Puma",800,3.9,NULL,NULL}
};

Product food[] = {
    {46,"Food","Chips","Lays",20,4.0,NULL,NULL},
    {47,"Food","Chips","Bingo",25,3.7,NULL,NULL},
    {48,"Food","Chips","Pringles",80,4.2,NULL,NULL},
    {49,"Food","Chocolate","Cadbury",50,4.5,NULL,NULL},
    {50,"Food","Chocolate","Nestle",45,4.1,NULL,NULL},
    {51,"Food","Chocolate","Ferrero",300,4.8,NULL,NULL},
    {52,"Food","Biscuit","Parle",30,4.0,NULL,NULL},
    {53,"Food","Biscuit","Britannia",35,4.0,NULL,NULL},
    {54,"Food","Juice","Tropicana",120,4.2,NULL,NULL},
    {55,"Food","Juice","Real",110,4.0,NULL,NULL},
    {56,"Food","Juice","Paper Boat",90,3.9,NULL,NULL},
    {57,"Food","Noodles","Maggi",12,4.1,NULL,NULL},
    {58,"Food","Nuts","Haldiram",200,4.3,NULL,NULL},
    {59,"Food","Cookies","Sunfeast",40,3.8,NULL,NULL},
    {60,"Food","Bread","Britannia",35,4.0,NULL,NULL}
};

// ====================== BST FUNCTIONS ======================
Product* createProductNode(int id, const char* cat, const char* item, const char* brand, float price, float rating) {
    Product *node = (Product*)malloc(sizeof(Product));
    node->id = id;
    strcpy(node->category, cat);
    strcpy(node->item, item);
    strcpy(node->brand, brand);
    node->price = price;
    node->rating = rating;
    node->left = node->right = NULL;
    return node;
}

Product* insertBST(Product *root, Product *newNode) {
    if (!root) return newNode;
    if (newNode->id < root->id)
        root->left = insertBST(root->left, newNode);
    else
        root->right = insertBST(root->right, newNode);
    return root;
}

Product* searchBST(Product *root, int id) {
    if (!root || root->id == id) return root;
    if (id < root->id) return searchBST(root->left, id);
    return searchBST(root->right, id);
}

void buildCatalog() {
    int i;
    for (i = 0; i < 15; i++) {
        catalog_root = insertBST(catalog_root, createProductNode(electronics[i].id, electronics[i].category,
                                                                 electronics[i].item, electronics[i].brand,
                                                                 electronics[i].price, electronics[i].rating));
        catalog_root = insertBST(catalog_root, createProductNode(stationery[i].id, stationery[i].category,
                                                                 stationery[i].item, stationery[i].brand,
                                                                 stationery[i].price, stationery[i].rating));
        catalog_root = insertBST(catalog_root, createProductNode(clothing[i].id, clothing[i].category,
                                                                 clothing[i].item, clothing[i].brand,
                                                                 clothing[i].price, clothing[i].rating));
        catalog_root = insertBST(catalog_root, createProductNode(food[i].id, food[i].category,
                                                                 food[i].item, food[i].brand,
                                                                 food[i].price, food[i].rating));
    }
}

// ====================== CART FUNCTIONS ======================
CartNode* createCartNode(Product *p) {
    CartNode *node = (CartNode*)malloc(sizeof(CartNode));
    node->product = p;
    node->next = NULL;
    return node;
}

void addToCart(Product *p) {
    CartNode *newNode = createCartNode(p);
    newNode->next = cart_head;
    cart_head = newNode;
    enqueueHistory(&history, p->category);
}

int removeFromCart(int index) {
    if (index < 1 || !cart_head) return 0;
    CartNode *temp = cart_head, *prev = NULL;
    int pos = 1;
    while (temp && pos < index) { prev = temp; temp = temp->next; pos++; }
    if (!temp) return 0;

    if (prev) prev->next = temp->next;
    else cart_head = temp->next;



    free(temp);
    return 1;
}

int cartSize() {
    int count = 0;
    CartNode *t = cart_head;
    while (t) { count++; t = t->next; }
    return count;
}

void freeCart() {
    while (cart_head) {
        CartNode *temp = cart_head;
        cart_head = cart_head->next;
        free(temp);
    }
}



// ====================== QUEUE (HISTORY) ======================
void initQueue(HistoryQueue *q) {
    q->front = q->rear = q->size = 0;
}

int isQueueFull(HistoryQueue *q) { return q->size == MAX_QUEUE; }
int isQueueEmpty(HistoryQueue *q) { return q->size == 0; }

void enqueueHistory(HistoryQueue *q, const char *cat) {
    if (isQueueFull(q)) return;
    strcpy(q->data[q->rear], cat);
    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->size++;
}

char* dequeueHistory(HistoryQueue *q) {
    if (isQueueEmpty(q)) return NULL;
    char *cat = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    q->size--;
    return cat;
}

char* getLastCategory() {
    if (isQueueEmpty(&history)) return NULL;
    int idx = (history.rear - 1 + MAX_QUEUE) % MAX_QUEUE;
    return history.data[idx];
}

// ====================== QUEUE (HISTORY) ======================
// queue functions here...


/* ====================== PASSWORD VALIDATION ====================== */
int isValidPassword(const char *pass) {
    if (strlen(pass) != 6) return 0;

    // First 2 should NOT be digits
    if (isdigit(pass[0]) || isdigit(pass[1]))
        return 0;

    // Last 4 must be digits
    for (int i = 2; i < 6; i++) {
        if (!isdigit(pass[i]))
            return 0;
    }

    return 1;
}



// ====================== USER PERSISTENCE ======================
int user_exists(const char *username) {
    FILE *f = fopen("users.txt", "r");
    if (!f) return 0;
    char u[USERNAME_LEN], p[PASS_LEN];
    while (fscanf(f, "%39s %39s", u, p) == 2)
        if (strcmp(u, username) == 0) { fclose(f); return 1; }
    fclose(f);
    return 0;
}

int register_user(const char *username, const char *password) {
    if (user_exists(username)) return 0;
    FILE *f = fopen("users.txt", "a");
    if (!f) return -1;
    fprintf(f, "%s %s\n", username, password);
    fclose(f);
    return 1;
}

int verify_user(const char *username, const char *password) {
    FILE *f = fopen("users.txt", "r");
    if (!f) return 0;
    char u[USERNAME_LEN], p[PASS_LEN];
    while (fscanf(f, "%39s %39s", u, p) == 2)
        if (strcmp(u, username) == 0 && strcmp(p, password) == 0) { fclose(f); return 1; }
    fclose(f);
    return 0;
}

// ====================== CART PERSISTENCE ======================
void save_cart_to_file(const char *username) {
    char fname[128];
    snprintf(fname, sizeof(fname), "cart_%s.txt", username);
    FILE *f = fopen(fname, "w");
    if (!f) return;
    fprintf(f, "%d\n", cartSize());
    CartNode *t = cart_head;
    while (t) {
        fprintf(f, "%d|%s|%s|%s|%.2f|%.1f\n",
                t->product->id, t->product->category, t->product->item,
                t->product->brand, t->product->price, t->product->rating);
        t = t->next;
    }
    fclose(f);
}

void load_cart_from_file(const char *username) {
    freeCart();
    char fname[128];
    snprintf(fname, sizeof(fname), "cart_%s.txt", username);
    FILE *f = fopen(fname, "r");
    if (!f) return;
    int n; if (fscanf(f, "%d\n", &n) != 1) { fclose(f); return; }
    char line[512];
    while (fgets(line, sizeof(line), f) && n--) {
        int id; char cat[CAT_LEN], item[NAME_LEN], brand[BRAND_LEN]; float price, rating;
        if (sscanf(line, "%d|%19[^|]|%49[^|]|%39[^|]|%f|%f", &id, cat, item, brand, &price, &rating) == 6) {
            Product *p = searchBST(catalog_root, id);
            if (p) addToCart(p);
        }
    }
    fclose(f);
}

// ====================== DISPLAY HELPERS ======================
void showCategories() {
    printf("\nChoose Category:\n");
    printf("1) Electronics\n2) Stationery\n3) Clothing\n4) Food\n0) Back to menu\n");
    printf("Enter choice: ");
}

void listProductsByCategory(const char *cat) {
    printf("\nProducts in category (Item | Brand | (Rs)Price | Rating):\n");
    int count = 0;
    for (int i = 1; i <= 60; i++) {
        Product *p = searchBST(catalog_root, i);
        if (p && strcmp(p->category, cat) == 0) {
            printf("%2d) %-12s | %-12s | %7.2f | %.1f\n",
                   ++count, p->item, p->brand, p->price, p->rating);
        }
    }
    printf("Enter product number to add (0 = cancel): ");
}

// ====================== RECOMMENDATIONS ======================
int inCart(Product *p) {
    CartNode *t = cart_head;
    while (t) {
        if (t->product == p) return 1;
        t = t->next;
    }
    return 0;
}

void getTop3NotInCart(const char *cat, Product *result[3]) {
    Product *candidates[15]; int n = 0;
    for (int i = 1; i <= 60; i++) {
        Product *p = searchBST(catalog_root, i);
        if (p && strcmp(p->category, cat) == 0 && !inCart(p))
            candidates[n++] = p;
    }
    for (int i = 0; i < 3 && i < n; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++)
            if (candidates[j]->rating > candidates[maxIdx]->rating)
                maxIdx = j;
        if (maxIdx != i) {
            Product *temp = candidates[i];
            candidates[i] = candidates[maxIdx];
            candidates[maxIdx] = temp;
        }
        result[i] = candidates[i];
    }
    for (int i = n; i < 3; i++) result[i] = NULL;
}

// ====================== VIEW CART + RECOMMENDATIONS ======================
void viewCart() {
    if (!cart_head) {
        printf("\nCart is empty.\n");
        return;
    }
    printf("\n====== Your Cart (%d items) ======\n", cartSize());
    CartNode *t = cart_head;
    int idx = 1;
    while (t) {
        printf("%2d) %-12s | %-12s | %-12s | %7.2f | %.1f\n",
               idx++, t->product->category, t->product->item,
               t->product->brand, t->product->price, t->product->rating);
        t = t->next;
    }

    printf("\n-- Category-based recommendations (top-rated & not in cart) --\n");
    t = cart_head;
    int suggested = 0;
    while (t) {
        Product *cur = t->product;
        Product *top3[3];
        getTop3NotInCart(cur->category, top3);
        if (top3[0]) {
            printf("\nFor %s (%s):\n", cur->item, cur->brand);
            for (int i = 0; i < 3 && top3[i]; i++) {
                printf(" - %s (%s) %.2f %.1f\n",
                       top3[i]->item, top3[i]->brand, top3[i]->price, top3[i]->rating);
            }
            suggested = 1;
        }
        t = t->next;
    }
    if (!suggested) printf("No recommendations available.\n");

    printf("\n-- Predicted next purchase --\n");
    char *predCat = getLastCategory();
    if (!predCat || cartSize() == 0) {
        printf("Not enough data.\n");
    } else {
        printf("Likely category: %s\n", predCat);
        Product *top[3]; getTop3NotInCart(predCat, top);
        if (top[0]) {
            printf("Suggested: %s (%s) %.2f %.1f\n",
                   top[0]->item, top[0]->brand, top[0]->price, top[0]->rating);
        } else {
            printf("No suggestion (all in cart).\n");
        }
    }
}

// ====================== INTERACTIVE FUNCTIONS ======================
void addItemInteractive() {
    int catChoice;
    while (1) {
        showCategories();
        if (scanf("%d", &catChoice) != 1) { while(getchar()!='\n'); printf("Invalid.\n"); continue; }
        if (catChoice == 0) return;
        if (catChoice < 1 || catChoice > 4) { printf("Invalid category.\n"); continue; }

        const char *cat = (catChoice==1) ? "Electronics" :
                          (catChoice==2) ? "Stationery" :
                          (catChoice==3) ? "Clothing" : "Food";

        listProductsByCategory(cat);
        int prodChoice;
        if (scanf("%d", &prodChoice) != 1) { while(getchar()!='\n'); printf("Invalid.\n"); continue; }
        if (prodChoice == 0) return;

        int count = 0;
        Product *selected = NULL;
        for (int i = 1; i <= 60; i++) {
            Product *p = searchBST(catalog_root, i);
            if (p && strcmp(p->category, cat) == 0) {
                count++;
                if (count == prodChoice) { selected = p; break; }
            }
        }
        if (!selected) { printf("Invalid product.\n"); continue; }

        addToCart(selected);
        printf("\nAdded to cart: %s - %s (%s) %.2f %.1f\n",
               selected->category, selected->item, selected->brand,
               selected->price, selected->rating);
        return;
    }
}

void deleteItemInteractive() {
    if (!cart_head) { printf("\nCart empty.\n"); return; }
    viewCart();
    printf("\nEnter item number to remove (0 = cancel): ");
    int idx;
    if (scanf("%d", &idx) != 1) { while(getchar()!='\n'); printf("Invalid.\n"); return; }
    if (idx == 0) return;
    if (!removeFromCart(idx)) { printf("Invalid index.\n"); return; }
    printf("Item removed.\n");
}

void buyAndEmptyCart() {
    if (!cart_head) {
        printf("\nCart is empty. Nothing to buy.\n");
        return;
    }

    float total = 0.0;
    CartNode *t = cart_head;
    while (t) {
        total += t->product->price;
        t = t->next;
    }

    printf("\nPurchase completed. Total amount: ₹%.2f\n", total);
    freeCart();
    printf("Cart emptied.\n");
}

// ====================== SORT CART (VIEW ONLY) ======================
int comparePriceAsc(const void *a, const void *b) {
    Product *pa = *(Product**)a; Product *pb = *(Product**)b;
    return (pa->price > pb->price) - (pa->price < pb->price);
}

int comparePriceDesc(const void *a, const void *b) { return comparePriceAsc(b, a); }

int compareBrand(const void *a, const void *b) {
    Product *pa = *(Product**)a; Product *pb = *(Product**)b;
    return strcmp(pa->brand, pb->brand);
}

void sortMenu() {
    if (!cart_head) { printf("\nCart empty.\n"); return; }
    printf("\nSort options:\n1) Price (Low to High)\n2) Price (High to Low)\n3) Brand (A to Z)\n0) Cancel\nChoose: ");
    int s; if (scanf("%d",&s)!=1) { while(getchar()!='\n'); printf("Invalid.\n"); return; }
    if (s == 0) return;

    int n = cartSize();
    Product **arr = (Product**)malloc(n * sizeof(Product*));
    CartNode *t = cart_head; int i = 0;
    while (t) { arr[i++] = t->product; t = t->next; }

    if (s == 1) qsort(arr, n, sizeof(Product*), comparePriceAsc);
    else if (s == 2) qsort(arr, n, sizeof(Product*), comparePriceDesc);
    else if (s == 3) qsort(arr, n, sizeof(Product*), compareBrand);
    else { free(arr); printf("Invalid.\n"); return; }

    printf("\n-- Sorted view --\n");
    for (i = 0; i < n; i++) {
        printf("%2d) %-12s | %-12s | %-12s | %7.2f | %.1f\n",
               i+1, arr[i]->category, arr[i]->item, arr[i]->brand,
               arr[i]->price, arr[i]->rating);
    }
    free(arr);
}

// ====================== MENUS ======================
void main_menu_display() {
    printf("\n========= E-COMMERCE SIM =========\n");
    printf("1) Add Item to Cart\n");
    printf("2) Delete Item from Cart\n");
    printf("3) View Cart + Recommendations\n");
    printf("4) Sort Cart (view only)\n");
    printf("5) Buy and Empty Cart\n");
    printf("6) Logout and Save Cart\n");
    printf("7) Exit (save & quit)\n");
    printf("Enter choice: ");
}

void auth_menu() {
    printf("\nWelcome! Choose:\n1) New user? Register\n2) Already registered? Login\n3) Exit\nEnter choice: ");
}

void register_flow() {
    char username[USERNAME_LEN], password[PASS_LEN];
    printf("\n--- Register ---\nUsername: ");
    scanf("%39s", username);

    if (user_exists(username)) {
        printf("User exists.\n");
        return;
    }

    printf("Password (6 chars; first 2 non-digit, last 4 digits): ");
    scanf("%6s", password);

    // Validate password format
    if (!isValidPassword(password)) {
        printf("Invalid password! Must be 6 characters:\n");
        printf(" - First 2: non-digit characters\n");
        printf(" - Last 4: digits\n");
        return;
    }

    if (register_user(username, password) == 1) {
        printf("Registered.\n");
    } else {
        printf("Failed.\n");
    }
}


int login_flow() {
    char username[USERNAME_LEN], password[PASS_LEN];
    printf("\n--- Login ---\nUsername: "); scanf("%39s", username);
    printf("Password: "); scanf("%6s", password);
    if (verify_user(username, password)) {
        strcpy(current_user, username);
        printf("Welcome, %s!\n", username);
        load_cart_from_file(username);
        return 1;
    }
    printf(user_exists(username) ? "Wrong password.\n" : "No such user.\n");
    return 0;
}