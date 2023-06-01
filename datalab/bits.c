/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 德摩根定律
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*
  Tmax : 0111,1111,1111,1111... |  2^31 - 1 | 0x7FFFFFFFF
  Tmin : 1000,0000,0000,0000... |  -2^31    | Ox800000000
  可得：Tmax + 1 = Tmin, 进一步可得 ~(Tmax + 1) = Tmax，～是把每一位都取反
  利用这个性质可以来判断x是否=Tmax, 但题目中不能用=
  转而利用xor的性质(两者不同时为True), 将上述条件转换为 ~(x + 1)^x , x != Tmax时为True
  需要注意的是当x=-1时(补码：1111,1111,1111,1111), 也满足 x的补码 + 1 = Tmin(溢出)
  所以需要添加x=-1的情况: !(x+1), 当x=-1是为True(在c中，非0即为1) 
  上述两种情况满足任意一种，x的补码都 != Tmax, 综合两者取或门，~(x + 1)^x | !(x+1)
  题目要求x=Tmax时返回True, 最后需要对整个结果取非门
  */

  return !(~(x + 1)^x | !(x+1));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 构造一个32位的奇数位全为1的数 y = 0xAAAAAAAA，将其与 x 进行与运算，如果结果仍为 y, 则 x 的奇数位均为 1
  // 注意实验要求不能使用big constants such as 0xffffffff. 所以先构造0xAA再移位
  int mask = 0xAA << 8 | 0xAA; // OxAAAA
  mask = mask << 16 | mask;    // 0xAAAAAAAA
  return !(x & mask)^mask;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int cond1 = !(x >> 8);        // 先检查最高24位是否都为0
  int cond2 = !(0b11 ^ (x >> 4));  // 比较中间4位是否为0011
  int y = x & (0xF);  // 获取后四位
  int cond3 = ((y + ~0xA + 1) >> 31) & 0x1; // 判断后四位是否在[0,9]之间，即 y-10 < 0, 注意由于不能用-，只能用补码代替，然后通过位移获取符号位
  return cond1 * cond2 & cond3;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 本题的关键是把x转化为全0或者全1，则可以把x ? y : z 转化为 x & y + ~x & z
  x = !x;     // 先把x转为布尔 
  x = ~x + 1; // 再把x转为全0(x==1)，或者全1(x!=0)
  return (x & y) | (~x & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // xy异号: 看谁为正数谁大, xy同号：看x-y的符号
  int signx = (x >> 31) & 0x1; // 获得x的符号  
  int signy = (y >> 31) & 0x1;
  int cond1 = !(signx ^ signy); // 同号
  int cond2 = signx | !signy ;  // 异号
  // cond1 = cond1 & (x + ~y + 1) >> 31; 忽略了x=y的情况下x-y也为False。所以把x <= y转换为 x < y+1，即x-y-1 < 0
  cond1 = cond1 & (x + ~y) >> 31 & 0x1;  // 查看x-y-1的符号;
  return cond1 | cond2 ;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // 本题的关键在于利用当x=0时, x与-x符号相等的特点
  // 先求取x与-x的做或/异或运算的符号位，因为x != 0时，由于符号位为1 ，右移后的结果便为0x11111111, 令其加1 ，刚好为0， 满足返回要求
  return ((~x + 1) | x >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /*
  x 为正数，以八位为例：0011 1010，需找到最高位 1，除此以外，还需一位 0 作为符号位；
  x 为负数，以八位为例：1100 1001，需找到最高位 0，除此以外，还需更高一位 1 作为符号位
  所以为了统一，不妨当 x 为负数时，将其取反， 那么也只需要找到最高位 1 后再加一位即可
  */
  int sign = x >> 31 & 0x1; 
  x = (~sign & x) | (sign & ~x);

  // 接下来使用二分法，先考虑高16位是否存在1
  int y = !!(x >> 16); // 把高16位规格化
  /*
  若高16位有1，处理后的y=0x00000001。说明x需要的位数至少为16，引入变量 bit16 记录该权重,将处理后的x左移4位即可得到16;
  如果高16位没有1, x左移4位得到0 
  */
  int bit16 = y << 4; 
  
  /*
  如果高16位有1 ，则将x右移16位，对右移后的x的低16位中的高8位进行同样的操作，从而二分地在x的高16位中找到最大位的1;
  如果高16位没有1 ，则x无需右移， 在x的低16位中的高8位进行同样的操作
  */
  x = x >> bit16;

  // 同理，分别对高 8 位，4位，2位，1位进行检查，检查后进行同样的操作
  int bit8 = !!(x >> 8) << 3;
  x = x >> bit8;
  int bit4 = !!(x >> 4) << 2;
  x = x >> bit4;
  int bit2 = !!(x >> 2) << 1;
  x = x >> bit2;
  int bit1 = !!(x >> 1);  // 剩下最后一位，x不需要移动
  x = x >> bit1;
  int bit0 = x;

  // 最后将所有权重求和
  return bit16 + bit8 + bit4 + bit2 + bit1 + bit0;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned sign = (uf >> 31) & 0x1 ;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if(exp == 0) {                 // Denormailized
    frac = frac << 1;
    return (sign << 31) | (exp << 23) | frac; 
  }
  if(exp != 0 && exp !=255) {    // Normalized
    exp++;
    return (sign << 31) | (exp << 23) | frac;  
  }
  return uf ;                     // Nan
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned sign = (uf >> 31) & 0x1 ;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  int E = exp - 127;
  frac = frac | (1 << 23);              // 规格化的数据，f开头为“1.”

  if(E < 0) return 0;                   // 非规格化的数据, value < 1.0, f=0
  else if(E >= 31) return 0x80000000u;  // 超过int的表示范围2^31-1，infinity或者Nan
  else{
    if(E > 23){                         // frac有23位，若 E > 23,
      frac = frac << (23 - E);          // 需要在frac的末尾添加 (E - 23) 个 0
    }else{
      frac = frac >> (E - 23);          // E < 23, 则frac末尾的 (23 - E)个数无法保留
    }
  }
  if(sign) return ~frac + 1;            // 负数的情况
  return frac;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
/*
结果是浮点数,浮点数各格式下的范围：
 格式	    |   最小值	  |   最大值
 规格化	  | 2^-126    |  2^{-127} X (2 - 2^-23) 
 非规格化	| 2^-149     | 2^{-126} X (1 - 2^-23) 
*/

if(x < -149)
		return 0;                   // too small
	else if(x < -126)             // 非规格化
		return 1 << (x + 149);      // 阶码值为E = 1 - bias = -126, 是固定的，这时候只能通过控制尾码来计算。由M×2^126=2^x可得M是由1左移n位, 则x+126 = -(23 - n)，得 n = x + 149 
	else if(x <= 127)             // 规格化
		return (x + 127) << 23;     // 让尾码为全0，控制阶码即可。X = e - bias --> e = x + 127, return 2^(x + 127) 
	else
		return (0xFF) << 23;        // too big


}
