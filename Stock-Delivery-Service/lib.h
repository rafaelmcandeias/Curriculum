/**
 * @file lib.h
 * @author Rafael Candeias
 * @brief Auxiliarity functions
 * @version 0.1
 * @date 2020-04-3
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INPUT 500
#define DESCRIPTION 64
#define STOCK_SIZE 10000
#define MAX_DELIVERIES 500
#define MAX_WEIGHT 200

#define ADD_TO_STOCK 'a'
#define ADD_QTD_TO_STOCK 'q'
#define NEW_DEL 'N'
#define ADD_PRO_TO_DEL 'A'
#define RMV_QTD_F_STOCK 'r'
#define RMV_PRO_F_DEL 'R'
#define COST 'C'
#define CHANGE_PRICE 'p'
#define PRINT_PRO_IN_DEL 'E'
#define DEL_W_MOST_P 'm'
#define P_STOCK_ORD 'l'
#define P_PRO_IN_DEL 'L'
#define STOP 'x'

#ifdef DEBUG
#define PRINT 'P'
#endif

/* Structures */
typedef struct Products {
    int id;
    char description[DESCRIPTION];
    int price;
    int weight;
    int quantity;
    int dead;
} Product;

typedef struct Deliveries {
    int weight;
    int product_quantity[STOCK_SIZE];
    int cost;
} Delivery;

/* Functions implemented */
int product_exists(int idp);
int delivery_exists(int ide);
int insuficient_stock(int idp, int quantity);
/* command: a */
void add_to_stock(char *parameters);
/* command: q */
void add_qtd_to_stock(char *parameters);
/* command: N */
void new_delivery();
/* command: A */
void add_product_to_delivery(char *parameters);
/* command: r */
void remove_qtd_from_stock(char *parameters);
/* command: R */
void remove_product_from_delivery(char *parameters);
/* command: C */
void cost(char *parameters);
/* command: p */
void change_price(char *parameters);
/* command: E */
void print_product_in_delivery(char *parameters);
/* command: m */
void delivery_with_most_product(char *parameters);
/* command: l */
void print_stock_ordered();
/* command: L */
void print_products_in_delivery(char *parameters);
void end();

#ifdef DEBUG
/* command: P */
void print_all();
#endif

#endif