// MRB3971.h
//
#ifndef MRB3971_LIBRARY
#define MRB3971_LIBRARY
#include <Arduino.h>
#include <driver/gpio.h>

typedef struct{                        
  uint16_t w, h, id;
  uint8_t  dir; 
  uint16_t  wramcmd, rramcmd, setxcmd, setycmd;  
} _lcd_dev; 

#define LCD_W 480
#define LCD_H 800

#if defined(LCD_USE_16BIT)
#define LCD_16BIT   // 16-bit parallel mode
#else
#define LCD_8BIT    // 8-bit parallel mode (default)
#endif

// color define
#define WHITE      0xFFFF
#define BLACK      0x0000   
#define BLUE       0x001F  
#define RED        0xF800
#define GREEN      0x07E0
#define CYAN       0x07FF
#define YELLOW     0xFFE0
#define MAGENTA    0xF81F

class MRB3971 {
public:
  MRB3971(uint8_t cs, uint8_t rs, uint8_t rd, uint8_t wr, int8_t rst,
          const uint8_t *data_pins, uint8_t bus_width, uint8_t pin=2);
  void parallel_setup(void);
  void set_inputs(void);
  void set_outputs(void);
  uint16_t parallel_read(void);
  void parallel_write(uint16_t value);
  void writex2(uint8_t HVAL,uint8_t LVAL);
  void WR_REG(uint16_t Reg);
  void WR_DATA(uint16_t Data);
  void WriteReg(uint16_t Reg, uint16_t RegValue);
  uint16_t RD_DATA(void);
  void ReadReg(uint16_t Reg,uint16_t *Rval,int n);
  void WriteRAM_Prepare(void);
  void FillWindow(uint16_t Color);
  void Clear(uint8_t dir, uint16_t color);
  void Reset(void);
  void WriteRegM( uint16_t adr, uint16_t len, uint8_t dat[]);
  void Init(void);
  void SetWindow(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);
  void direction(uint8_t direction);
  uint16_t Read_ID(void);

  void DrawPoint(uint16_t x,uint16_t y);
  uint16_t ReadPoint(uint16_t x,uint16_t y);
  void ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);
  void ShowString(uint16_t x,uint16_t y,uint8_t *p);
  void DrawCircle(uint16_t x0,uint16_t y0,uint8_t r);
  void Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  void DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  void DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);  

  void pset( uint16_t x, uint16_t y, uint16_t col );
  uint16_t point( uint16_t x, uint16_t y );
  void scanLine( uint16_t lx, uint16_t rx, uint16_t y, uint16_t col );
  void paint( uint16_t x, uint16_t y, uint16_t paintCol );
  
  void ledon();     // LED ON
  void ledoff();    // LED OFF
  void FlushBuffer(const uint16_t *buf, uint32_t len);  // Bulk RGB565 write for LVGL flush
  void FillPixels(uint16_t color, uint32_t count);      // Fill exactly `count` pixels (efficient fillRect)
  
private:
  uint8_t _cs;
  uint8_t _rs;
  uint8_t _rd;
  uint8_t _wr;
  int8_t _rst;
  uint32_t _csbit0;
  uint32_t _csbit1;
  uint32_t _rsbit0;
  uint32_t _rsbit1;
  uint32_t _rdbit0;
  uint32_t _rdbit1;
  uint32_t _wrbit0;
  uint32_t _wrbit1;
  uint32_t _rstbit0;
  uint32_t _rstbit1;
  uint8_t _data_pins[16];
  uint8_t _bus_width;
  uint32_t _data_mask0;
  uint32_t _data_mask1;
  bool _is_contiguous;
  uint8_t _contiguous_bank;
  uint8_t _parallel0;
  uint32_t _contiguous_mask;
  uint8_t _pin;
};

#endif
