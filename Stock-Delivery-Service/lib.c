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
    if (idp >= global_idp || stock[idp]->dead) {
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


/**
 * @brief Merges two subarrays of arr[].
 * First subarray is arr[l..m].
 * Second subarray is arr[m+1..r].
 */
void merge(Product *arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    /* create temp arrays */
    Product **L = (Product**)malloc(sizeof(Product*) * n1);
    Product **R = (Product**)malloc(sizeof(Product*) * n2);
    
    for (i = 0; i < n1; i++) {
        L[i] = (Product*)malloc(sizeof(Product));
    }
    for (i = 0; i < n2; i++) {
        R[i] = (Product*)malloc(sizeof(Product));
    }

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        strcpy(L[i]->description, arr[l + i]->description);
        L[i]->price = arr[l + i]->price;
        L[i]->weight = arr[l + i]->weight;
        L[i]->quantity = arr[l + i]->quantity;
    }
    for (j = 0; j < n2; j++) {
        strcpy(R[j]->description, arr[m + 1 + j]->description);
        R[j]->price = arr[m + 1 + j]->price;
        R[j]->weight = arr[m + 1 + j]->weight;
        R[j]->quantity = arr[m + 1 + j]->quantity;
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; /* Initial index of first subarray */
    j = 0; /* Initial index of second subarray */
    k = l; /* Initial index of merged subarray */
    while (i < n1 && j < n2) {
        if (L[i]->price <= R [j]->price) {
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

    for (i = 0; i < n1; i++) {
        free(L[i]);
    }
    free(L);
    for (i = 0; i < n2; i++) {
        free(R[i]);
    }
    free(R);
}


/**
 * @brief applies mergesort
 *
 * @param arr
 * @param l is for left index
 * @param r is right index of the
 * sub-array of arr to be sorted
 */
void mergeSort(Product *arr[], int l, int r) {
    int m;

    if (l < r) {
        /* Same as (l+r)/2, but avoids overflow for
        large l and h */
        m = l + (r - l) / 2;

        /* Sort first and second halves */
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
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
    p->dead = 0;
    p->id = global_idp++;

    stock[p->id] = p;

    printf("Novo produto criado %d.\n", p->id);
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
        global_ide++;
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
        stock[idp]->quantity -= qtd;
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
        printf("%s %d\n", stock[idp]->description, deliveries[ide]->product_quantity[idp]);
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
        printf("Maximo produto %d %d %d.\n", idp, max_ide, deliveries[max_ide]->product_quantity[idp]);
    }
}


/**
 * @brief Prints all products in stock
 * ordered by their description. Uses
 * mergesort algorithm
 * @performance: O(NLog(N))
 */
void print_stock_ordered() {
    Product *arr[STOCK_SIZE];
    int i;

    memcpy(arr, stock, sizeof(stock));
    mergeSort(arr, 0, global_idp - 1);

    for (i = 0; i < global_idp; i++) {
        printf("%s %d %d\n", arr[i]->description, arr[i]->price, arr[i]->quantity);
    }
}


/*
void print_products(int ide) {

}
*/

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
        if (!stock[i]->dead)
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