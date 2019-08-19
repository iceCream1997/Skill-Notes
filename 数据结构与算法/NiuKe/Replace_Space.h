/*请实现一个函数，将一个字符串中的每个空格替换成“%20”。
例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。 */
#include "head.h"

using namespace std;
//思路：将空格转换为%20，该字符串长度会发生改变。
//先求出改变后的字符串的长度，判断是否会越界。
//在替换时，如果从前往后，为了避免空格替换后覆盖原本的字符
//每一次替换都需要移动该空格之后所有的字符
//因此应该采用从后往前替换的方法。
class solution{
public:
    void replaceSpace(char* str,int length)
    {
        int spacenum =  0;
        int len = 0;
        char* p = str;
        while(*p != '\0')
        {
            if(*p == ' ')
            {
                spacenum++;
                p++;
                len++;
            }
            else
            {
                p++;
                len++;
            }    
        }
        int nlen = len + spacenum * 2;
        if(nlen > length)
            return;
        while(len >= 0){
            if(str[len] != ' ')
            {
                str[nlen] = str[len];
                --len,--nlen;
            }else
            {
                str[nlen] = '0';
                str[nlen-1] = '2';
                str[nlen-2] = '%';
                --len;
                nlen-=3;
            }
            
        }
    }
};