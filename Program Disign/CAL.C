#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DeleteCharactor(char *str,int len,char ch)
{
    int i,j;
    for(i=0;i<len;i++)
    {
        if(str[i] == ch)
        {
            for(j=i+1;j<len;j++)
            {
                str[j-1] = str[j];
            }
            i--;
            str[--len] = '\0';
        }
    }
    return len;
}
int ChangeStringToInt(char *str,int len)
{
    int temp = 0,i=0;
    while(i<len)
    {
        temp = temp * 10 + str[i] - '0';
        i++;
    }
    return temp;
}
void InsertDataToString(int dat,char *str,int index)
{
    int arr[10] = {0},i=0;
    int neg = 0;
    if(dat<0)
    {
        str[index++] = '<';
        dat*=-1;
        neg = 1;
    }
    while(dat>0)
    {
        arr[i++] = dat%10;
        dat/=10;
    }
    while(i>0)
    {
        str[index++]=arr[--i] + '0';
    }
    if(neg) str[index++] = '>';
}
int StoreShortExp(char *str,int index,int len)
{
    int i,j,data1=0,data2=0,result;
    char op = str[index];
    int StartIndex = 0,EndIndex = 0,StartStartIndex;
    int neg = 0;
    EndIndex = index-1;
    str[index] = ' ';
    StartIndex = 0;
    
        i = EndIndex;
        while(str[i]<='9'&&str[i]>='0') i--;
        StartIndex = i+1;
    
    if(i != EndIndex)
    {
        if(neg) data1 = (-1)*ChangeStringToInt(&str[StartIndex],EndIndex-StartIndex+1);
        else data1 = ChangeStringToInt(&str[StartIndex],EndIndex-StartIndex+1);
        if(neg) {StartIndex--;EndIndex++;}
        for(j=StartIndex;j<=EndIndex;j++)
        {
            str[j] = ' ';
        }
    }
    StartStartIndex = StartIndex;
    StartIndex = index+1;
    EndIndex = len-1;
    neg = 0;
    if(str[StartIndex] == '<')
    {
        StartIndex++;
        neg = 1;
        for(i = StartIndex;i<len;i++)
        {
            if(str[i] == '>')
            {
                EndIndex = i-1;
            }
        }
    }
    else
    {
        i = StartIndex;
        while(str[i] <='9'&&str[i]>='0') i++;
        EndIndex = i-1;
    }
    if(i != StartIndex)
    {
        if(neg) data2 = (-1)*ChangeStringToInt(&str[StartIndex],EndIndex-StartIndex+1);
        else data2 = ChangeStringToInt(&str[StartIndex],EndIndex-StartIndex+1);
        if(neg) {StartIndex--;EndIndex++;}
        for(j=StartIndex;j<=EndIndex;j++)
        {
            str[j] = ' ';
        }
    }
    switch(op)
    {
        case '+':result = data1+data2;break;
        case '-':result = data1-data2;break;
        case '*':result = data1*data2;break;
        case '/':result = data1/data2;break;
    }
    InsertDataToString(result,str,StartStartIndex);
    return result;
}
int *Calc(unsigned char *str)
{
    int len = strlen(str);
    int i,neg = 0;
    int StartIndex = 0, EndIndex = 0;
	int res[8];
    int result = 0;
    for(i=0;i<len;i++)
    {
        if(str[i] == '*'|| str[i] == '/')
        {
            result = StoreShortExp(str,i,len);
            len = DeleteCharactor(str,len,' ');
            i = -1;
        }
    }   
    for(i=0;i<len;i++)
    {
        if(str[i] == '+'|| str[i] == '-')
        {
            result = StoreShortExp(str,i,len);
            len = DeleteCharactor(str,len,' ');
            i=-1;
        }
    }
	if(result<0) neg = 1, result = -result;
	for(i=1;result;i++){
		res[i] = result%10;
		result/=10;
	}
	if(neg) res[i++]=13;
	res[0] = i-1;
	return res;
}
