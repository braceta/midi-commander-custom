/*
 * switch_router.h
 *
 *  Created on: 8 Jul 2021
 *      Author: D Harvie
 */

#ifndef INC_SWITCH_ROUTER_H_
#define INC_SWITCH_ROUTER_H_

void handle_switches(void);
void handle_exp_pedals(uint16_t adcValue1, uint16_t adcValue2);
void sw_led_init(void);

#endif /* INC_SWITCH_ROUTER_H_ */
