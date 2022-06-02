#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char *byte_pointer;//指向无符号数的指针

void show_bytes(byte_pointer start_p,size_t len)
{
    size_t i;
    for(i=0;i<len;i++)
    {
        printf("%.2x  ",start_p[i]);
    }
    printf("\n");
}
void show_int(int x)
{
    show_bytes((byte_pointer)&x,sizeof(int));
}
void show_float(float x)
{
    show_bytes((byte_pointer)&x,sizeof(float));
}
void show_long(long x)
{
    show_bytes((byte_pointer)&x,sizeof(long));
}
void show_pointer(void *x)
{
    show_bytes((byte_pointer)&x,sizeof(void *));
}
void show_unsigned(unsigned x)
{
    show_bytes((byte_pointer)&x,sizeof(unsigned));
}
/*************************/
//大端返回0 小端返回1
unsigned char is_little_endian()
{
    int x=0x01;
    return *((byte_pointer)&x);
}
//2.59
int A_2_59(int x,int y)
{
    return (x&0xff)|(y&~0xff);
}
//2.60
unsigned replace_byte(unsigned x,int i,unsigned char b)
{
    //先把需要位置置0
    x&=~(0xff<<(i<<3));
    //替换成b
    x|=b<<(i<<3);
    return x;

}

//2.61
int A_2_61(int x)
{
    //返回最高位为0或者最低位为1
    char low_bit=x&0xff;
    char high_bit=x>>((sizeof(int)-1)<<3);
    return !(~low_bit)||!high_bit;
}
//2.62
unsigned srl(unsigned x,int k)
{
    int mask=-2;
    //算术右移实现逻辑右移
    unsigned xsra=(int)x>>k;
    //高位置零
    if(k<31)
    {
        mask=1<<(k+1);
        mask-=1;
        //掩膜置到高位
        mask=mask<<(8*sizeof(int)-k);
    }
    return xsra&=~mask;

}
int any_odd_check(unsigned x)
{
    int rec=1;
    //奇偶校验 奇数个1返回0
    while(x)
    {
        if(x&0x01)
            rec=!rec;
        x=x>>1;
    }
    return rec;
}


int leftmost_one(unsigned x)
{
    //只保留位编码最左边的那个1
    //从高位向低位寻找
  /* unsigned mask=1<<31;
    while(!(mask&x)&&mask)
    {
        mask>>=1;
    }
    return (int)mask;*/
    //(A+B)^A   A==1  0   A==0  B
    x|=(x>>1);
    x|=(x>>2);
    x|=(x>>4);
    x|=(x>>16);
    return x^(x>>1);
}

//2.67 32位机返回1
int int_size_is()
{
    int set_msb=1<<31;//>=32
    return set_msb&&(set_msb<0);//最高位符号位
}
int int_size_is1()
{
    int z=1<<15;
    z=z<<15;
    int set_msb=z<<1;//>=32
    return set_msb&&(set_msb<0);//最高位符号位
}
//2.68
int lower_one_mask(int n)
{
    int x=0;
    //把<n的位设置为1
    x=1<<n;
    x-=1;
    if(n>>5)
        x-=1;
    return x;
}
//2.69 循环左移
unsigned rotate_left(unsigned x,int n)
{
    //0<=n<w
    return x<<n|x>>(31-n)>>1;
}
//2.70 1<=n<=w
int fit_bits(int x,int n)
{
    //数值是否可以使用n位补码表示
    //判断高位有效性 绝对值
    x=x>>(n-1);//一个符号位
    return !~x||!x;
}
//2.71
int xbyte(unsigned word,int bytenum)
{
    //数据移位
    char res=(word>>(bytenum<<3))&0xff;
    return (int)res;
}
//2.73 饱和溢出
int saturates_add(int x,int y)
{
    int res=x+y;
    if(x>0&&y>0&&res<0)
    {
        res=0x7fffffff;
    }
    else if(x<0&&y<0&&res>0)
    {
        res=0x80000000;
    }
    return res;
}
//2.74 检验溢出
int tsub_ok(int x,int y)
{
    //x-y 不溢出返回1
    int z=x-y;
    return !((y>0&&z>x)||(y<0&&z<x));
}
//2.75
int signed_high_prod(int x,int y)
{
    long long  temp=(long long)x*(long long)y;
    int rec;
    rec=temp>>32;
    return rec;
}
unsigned unsigned_high_prod(unsigned x,unsigned y)
{
    int sx=(int)x;
    int sy=(int)y;
    unsigned res=signed_high_prod(sx,sy);
    return res+(sx>>31&1)*y+(sy>>31&1)*x;
}

//2.76 分配内存
void *my_calloc(size_t nmemb,size_t size)
{
    //分配nmemb*size大小内存 初始化为0
    size_t num=size*nmemb;
    if(num==0)
        return NULL;
    void *p=malloc(num);
    memset(p,0,num);
    return p;
}

//2.78
int divide_power2(int x,int k)
{
    //K的取值 0<=k<w-1
    //大于0下舍入 小于0上舍入
    int bias=((x>>31)&1)*((1<<k)-1);//偏置
    return (x+bias)>>k;
}
//2.79

int main()
{
    int a=-5;
    a=divide_power2(21,2);
    printf("%d ",a/2);

    return 0;
}
