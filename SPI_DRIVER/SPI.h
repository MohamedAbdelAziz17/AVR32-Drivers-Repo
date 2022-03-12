#ifndef SPI_H_
#define SPI_H_

#include "SPI_CONFIG.h"


extern void		MCAL_SPI_Init ( void (*local_ptr) (uint8_t ) );

extern void		MCAL_SPI_SS_ENABLE(uint8_t u8SlaveNumber);

extern void		MCAL_SPI_SS_DISABLE(uint8_t u8SlaveNumber);

extern void		MCAL_SPI_Transmit ( uint8_t u8Data);

extern uint8_t  MCAL_SPI_Receive ( void );


#endif /* SPI_H_ */
