/**
 * @file lib.c
 * @author Rafael Candeias
 * @brief file with all functions to call
 * @version 0.1
 * @date 2019-04-3
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "lib.h"

Product *stock[STOCK_SIZE];
Delivery *deliveries[MAX_DELIVERIES];
int global_idp = 0;
int global_ide = 0;


/**
 * @brief Tells if a product exists by idp
 * @performance: O(1)
 * @param idp 
 * @return 1 = True
 */
int product_exists(int idp) {
    if (idp >= global_idp) {
        return 0;
    }
    return 1;
}


/**
 * @brief Tells if a delivery exists by ide
 * @performance: O(1)
 * @param ide 
 * @return 1 = True
 */
int delivery_exists(int ide) {
    if (ide >= global_ide || deliveries[ide] == NULL) {
        return 0;
    }
    return 1;
}


/**
 * @brief Tells if there is enough quantity of
 * product idp in stock
 * @performance: O(1)
 * @param idp 
 * @param quantity 
 * @return 1 = True
 */
int insuficient_stock(int idp, int quantity) {
    if (stock[idp]->quantity < quantity) {
        return 1;
    }
    return 0;
}


/**
 * @brief Calculates if a delivery can fit
 * more quantity of product idp
 * @performance: O(1)
 * @param ide 
 * @param idp 
 * @param quantity 
 * @return 1 = True
 */
int weight_limit_broken(int ide, int idp, int quantity) {
    if (deliveries[ide]->weight + stock[idp]->weight * quantity > MAX_WEIGHT) {
        return 1;
    }
    return 0;
}


void merge(int *arr, int l, int m, int r, char flag) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    int *L = (int *)malloc(sizeof(int) * n1);
    int *R = (int *)malloc(sizeof(int) * n2);
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if ((flag == 'l' && stock[L[i]]->price <= stock[R[j]]->price) || 
            (flag == 'L' && strcmp(stock[L[i]]->description, stock[R[j]]->description) <= 0)) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}


void mergeSort(int *arr, int l, int r, char flag) {
    if (l < r) {
        int m = l + (r - l) / 2;
  
        /* Sort first and second halves */
        mergeSort(arr, l, m, flag);
        mergeSort(arr, m + 1, r, flag);
  
        merge(arr, l, m, r, flag);
    }
}


/**
 * @brief Adds a new product to stock
 * @performance: O(1)
 * @param parameters description:price:weight:quantity
 */
void add_to_stock(char *parameters) {
    /* Get values */
    char description[DESCRIPTION];
    int price, weight, quantity;
    Product *p = (Product*)malloc(sizeof(Product));
    sscanf(parameters, "%[^:]:%d:%d:%d", description, &price, &weight, &quantity);

    strcpy(p->description, description);
    p->price = price;
    p->weight = weight;
    p->quantity = quantity;
    p->id = global_idp++;

    stock[p->id] = p;

    printf("Novo produto %d.\n", p->id);
}


/**
 * @brief Adds more quantity to product in stock
 * @performance: O(1)
 * @param parameters idp:qtd
 */
void add_qtd_to_stock(char *parameters) {
    int idp, quantity;
    sscanf(parameters, "%d:%d", &idp, &quantity);

    if (!product_exists(idp)) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    else {
        stock[idp]->quantity += quantity; 
    }
}


/**
 * @brief Creates new delivery
 * @performance: O(N)
 */
void new_delivery() {
    int idp;
    if (global_ide < 500) {
        deliveries[global_ide] = (Delivery*)malloc(sizeof(Delivery));
        deliveries[global_ide]->weight = 0;
        deliveries[global_ide]->cost = 0;
        for (idp = 0; idp < STOCK_SIZE; idp++) {
            deliveries[global_ide]->product_quantity[idp] = 0;
        }
        printf("Nova encomenda %d.\n", global_ide++);
    }
}


/**
 * @brief Adds a product to a delivery
 * If product already in delivery, adds quantity
 * @performance: O(1)
 * @param parameter ide:idp:quantity
 */
void add_product_to_delivery(char *parameters) {
    int ide, idp, quantity;
    sscanf(parameters, "%d:%d:%d", &ide, &idp, &quantity);

    if (!delivery_exists(ide)) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (!product_exists(idp)) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if (insuficient_stock(idp, quantity)) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if (weight_limit_broken(ide, idp, quantity)) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else {
        /* Remove quantity from stock */
        stock[idp]->quantity -= quantity;
        /* Updates delivery weight */
        deliveries[ide]->weight += quantity * stock[idp]->weight;
        /* Updates delivery cost */
        deliveries[ide]->cost += quantity * stock[idp]->price;
        /* Add product quantity to delivery */
        deliveries[ide]->product_quantity[idp] += quantity;
    }
}


/**
 * @brief removes quantity from a  product in stock
 * @performance: O(1)
 * @param parameters idp:qtd 
 */
void remove_qtd_from_stock(char *parameters) {
    int idp, qtd;
    sscanf(parameters, "%d:%d", &idp, &qtd);

    if (!product_exists(idp)) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if (insuficient_stock(idp, qtd)) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else {
        stock[idp]->quantity = qtd > stock[idp]->quantity ? 0 : stock[idp]->quantity-qtd;
    }
}


/**
 * @brief removes a product from a delivery
 * @performance: O(1)
 * @param parameters ide:idp
 */
void remove_product_from_delivery(char *parameters) {
    int ide, idp;
    sscanf(parameters, "%d:%d", &ide, &idp);

    if (!delivery_exists(ide)) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (!product_exists(idp)) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else {
        /* Restocks */
        stock[idp]->quantity += deliveries[ide]->product_quantity[idp];
        /* Reduces delivery weight */
        deliveries[ide]->weight -= deliveries[ide]->product_quantity[idp] * stock[idp]->weight;
        /* Reduces delivery cost */
        deliveries[ide]->cost -= deliveries[ide]->product_quantity[idp] * stock[idp]->price;
        /* Removes qtd */
        deliveries[ide]->product_quantity[idp] = 0;
    }
}


/**
 * @brief Calculates the cost of a delivery
 * @performance: O(1)
 * @param parameters ide
 */
void cost(char *parameters) {
    int ide;
    sscanf(parameters, "%d", &ide);

    if (!delivery_exists(ide)) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else {
        printf("Custo da encomenda %d %d.\n", ide, deliveries[ide]->cost);
    }
}


/**
 * @brief changes price of a product
 * Change cost of deliveries with that product
 * @performance: O(N)
 * @param parameters idp:price
 */
void change_price(char *parameters) {
    int idp, price, ide;
    sscanf(parameters, "%d:%d", &idp, &price);

    if (!product_exists(idp)) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else {
        /* Update all deliveries */
        for (ide = 0; ide < global_ide; ide++) {
            if (deliveries[ide]->product_quantity[idp] > 0) {
                deliveries[ide]->cost += deliveries[ide]->product_quantity[idp] * (price - stock[idp]->price);
            }
        }
        /* Update stock */
        stock[idp]->price = price;
    }
}


/**
 * @brief shows description and quantity of a product
 * in a delivery
 * @performance: O(1)
 * @param parameters ide:idp 
 */
void print_product_in_delivery(char *parameters) {
    int ide, idp;
    sscanf(parameters, "%d:%d", &ide, &idp);

    if (!delivery_exists(ide)) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if (!product_exists(idp)) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else {
        printf("%s %d.\n", stock[idp]->description, deliveries[ide]->product_quantity[idp]);
    }
}


/**
 * @brief Shows delivery with more of
 * a product idp
 * @performance: O(N)
 * @param parameters idp 
 */
void delivery_with_most_product(char *parameters) {
    int idp, ide, max_ide = 0;
    sscanf(parameters, "%d", &idp);

    if (!product_exists(idp)) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else {
        for (ide = 1; ide < global_ide; ide++) {
            max_ide = deliveries[ide]->product_quantity[idp] > deliveries[max_ide]->product_quantity[idp] ? ide : max_ide;
        }
        if (deliveries[max_ide]->product_quantity[idp] > 0) {
            printf("Maximo produto %d %d %d.\n", idp, max_ide, deliveries[max_ide]->product_quantity[idp]);
        }
    }
}


/**
 * @brief Prints all products in stock
 * ordered by their price. Uses
 * mergesort algorithm
 * @performance: O(NLog(N))
 */
void print_stock_ordered() {
    int *arr = (int*)malloc(sizeof(int) * global_idp);
    int i, idp;

    /* Populate */
    for (i = 0; i < global_idp; i++) {
        arr[i] = i;
    }

    mergeSort(arr, 0, global_idp-1, 'l');

    /* Print */
    printf("Produtos\n");
    for (i = 0; i < global_idp; i++) {
        idp = arr[i];
        printf("* %s %d %d\n", stock[idp]->description, stock[idp]->price, stock[idp]->quantity);
    }
    /* Free temp space */
    free(arr);
}


/**
 * @brief Prints all products in delivery
 * ordered by their description. Uses
 * mergesort algorithm.
 * @performance: O(NLog(N))
 * @param parameters ide
 */
void print_products_in_delivery(char *parameters) {
    int ide, idp, nP, i;
    int *arr;
    sscanf(parameters, "%d", &ide);

    if (!delivery_exists(ide)) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    else {
        arr = (int*)malloc(sizeof(int) * global_idp);
        /* Populate */
        nP = 0;
        for (idp = 0; idp < global_idp; idp++) {
            if (deliveries[ide]->product_quantity[idp] > 0) {
                arr[nP++] = idp;
            }
        }

        mergeSort(arr, 0, nP-1, 'L');

        /* Print */
        printf("Encomenda %d\n", ide);
        for (i = 0; i < nP; i++) {
            idp = arr[i];
            printf("* %s %d %d\n", stock[idp]->description, stock[idp]->price, deliveries[ide]->product_quantity[idp]);
        }
        /* Free temp space */
        free(arr);
    }
}


/**
 * @brief Frees allocated mem
 * @performance: O(N)
 */
void end() {
    int i;
    /* Clears stock */
    for (i = 0; i < global_idp; i++) {
        free(stock[i]);
    }
    /* Clears deliveries */
    for (i = 0; i < global_ide; i++) {
        free(deliveries[i]);
    }
}


/**
 * @brief Function used for debugging
 * Prints all that exists 
 * 
 */
#ifdef DEBUG
void print_all() {
    int i, j;
    printf("\n-------Print Stock-------\n");
    for (i = 0; i < global_idp; i++) {
        printf("%d : %s : p = %d : w = %d : qtd = %d\n", stock[i]->id, stock[i]->description, stock[i]->price, stock[i]->weight, stock[i]->quantity);
    }

    printf("\n-------Print Deliveries-------\n");
    for (i = 0; i < global_ide; i++) {
        printf("%d : w = %d : c = %d\n", i, deliveries[i]->weight, deliveries[i]->cost);
        for (j = 0; j < global_idp; j++) {
            if (deliveries[i]->product_quantity[j] > 0)
                printf("\t%du of %s\n", deliveries[i]->product_quantity[j], stock[j]->description);
        }
    }
    printf("\n");
}
#endif