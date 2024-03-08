#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#define BIT(x)		(1 << x)

#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave Select

void spi_masterInit(void)
{
	// Set MOSI, SCK, SS and SS_display to be output
	DDR_SPI = 0xff;

	// Set MISO to be input
	DDR_SPI &= ~BIT(SPI_MISO);

	// Deselect slave
	PORT_SPI |= BIT(SPI_SS);

	// Disable SPI interrupts (bit 7),
	// enable SPI (bit 6),
	// disable data order (bit 5),
	// set mode to master (bit 4),
	// CPOL and CPHA low (bit 3, 2),
	// set SCK frequency prescaler to 64 (bitrate = 125 kHz)
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}


// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data;							// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete
}

// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{

	PORTB |= BIT(chipNumber);
}


// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_slaveSelect(0);				// Select display chip (MAX7219)
	spi_write(0x09);      			// Register 09: Decode Mode
	spi_write(0xFF);				// 	-> 1's = BCD mode for all digits
	spi_slaveDeSelect(0);			// Deselect display chip

	spi_slaveSelect(0);				// Select dispaly chip
	spi_write(0x0A);      			// Register 0A: Intensity

	// Excercise b2
	spi_write(0x0F);    			//  -> Level 4 (in range [1..F])

	spi_slaveDeSelect(0);			// Deselect display chip

	spi_slaveSelect(0);				// Select display chip
	spi_write(0x0B);  				// Register 0B: Scan-limit

	// Excercise b1
	spi_write(0x03);   				// 	-> 1 = Display digits 0..1

	spi_slaveDeSelect(0);			// Deselect display chip

	spi_slaveSelect(0);				// Select display chip
	spi_write(0x0C); 				// Register 0B: Shutdown register
	spi_write(0x01); 				// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);			// Deselect display chip
}

// Excercise C
void spi_writeWord (unsigned char address, unsigned char data) {
	spi_slaveSelect(0);

	// Send the seven segment's address. Choice between 1, 2, 3 and 4.
	spi_write(address);

	// Send the character to show on the display.
	spi_write(data);

	spi_slaveDeSelect(0);
	wait(1000);
}

int main(void)
{
	// inilialize
	DDRB=0x01;					  	// Set PB0 pin as output for display select
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip

	// clear display (all zero's)
	for (char i =1; i<=2; i++)
	{
		spi_slaveSelect(0); 		// Select display chip
		spi_write(i);  				// 	digit adress: (digit place)
		spi_write(0);				// 	digit value: 0
		spi_slaveDeSelect(0);		// Deselect display chip
	}
	wait(1000);

	// Excercise b1
	spi_writeWord(4, 1);
	spi_writeWord(3, 2);
	spi_writeWord(2, 3);
	spi_writeWord(1, 4);

	return 0;
}