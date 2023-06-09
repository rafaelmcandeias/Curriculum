/**
 * @file main.c
 * @author Rafael Candeias
 * @brief File with main loop.
 * @version 0.1
 * @date 2020-04-4
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "lib.h"

int main() {
    char parameters[INPUT];
    char command = getchar();

    while (command != STOP) {
        getchar();
        switch (command) {
            /* command: a */
            case ADD_TO_STOCK:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                add_to_stock(parameters);
                break;
            
            /* command: q */
            case ADD_QTD_TO_STOCK:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                add_qtd_to_stock(parameters);
                break;
            
            /* command: N */
            case NEW_DEL:
                #ifdef DEBUG
                printf("INPUT: %c\n", command);
                #endif
                new_delivery();
                break;

            /* command: A */
            case ADD_PRO_TO_DEL:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                add_product_to_delivery(parameters);
                break;

            /* command: r */
            case RMV_QTD_F_STOCK:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                remove_qtd_from_stock(parameters);
                break;

            /* command: R */
            case RMV_PRO_F_DEL:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                remove_product_from_delivery(parameters);
                break;
            
            /* command: C */
            case COST:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                cost(parameters);
                break;
            
            /* command: p */
            case CHANGE_PRICE:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                change_price(parameters);
                break;
            
            /* command: E */
            case PRINT_PRO_IN_DEL:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                print_product_in_delivery(parameters);
                break;
            
            /* command: m */
            case DEL_W_MOST_P:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                delivery_with_most_product(parameters);
                break;
            
            /* command: l */
            case P_STOCK_ORD:
                #ifdef DEBUG
                printf("INPUT: %c\n", command);
                #endif
                print_stock_ordered();
                break;

            /* command: L */
            case P_PRO_IN_DEL:
                scanf("%s%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                print_products_in_delivery(parameters);
                break;

            /* command: P */
            #ifdef DEBUG
            case PRINT:
                print_all();
                break;
            #endif
        }
        command = getchar();
    }
    end();
    return 0;
}
