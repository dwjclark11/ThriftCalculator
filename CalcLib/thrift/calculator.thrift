namespace cpp calculator

const i32 WINDOW_WIDTH = 320
const i32 WINDOW_HEIGHT = 416

const i32 BUTTON_SIZE_X = 48
const i32 BUTTON_SIZE_Y = 48

enum Operation 
{
  ADD = 1,
  SUBTRACT = 2,
  MULTIPLY = 3,
  DIVIDE = 4
}

struct Work 
{
  1: i32 num1 = 0,
  2: i32 num2,
  3: Operation op,
  4: bool bNumFirstNumSet = false,
  5: bool bNumSecondNumSet = false,
}


exception InvalidOperation 
{
  1: i32 op,
  2: string why
}

service Calculator
{
   i32 calculate(1:Work w) throws (1:InvalidOperation io),
}
