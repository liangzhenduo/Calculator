#include <string.h>

int DeleteCharactor(char *str, int len){
    unsigned int i, j;
    for(i = 0; i < len; i ++){
        if(str[i] == ' '){
            for(j = i + 1; j < len; j ++){
                str[j-1] = str[j];
            }
            i --;
            str[--len] = '\0';
        }
    }
    return len;
}

int ChangeStringToInt(char *str, int len){
    int ret = 0;
	unsigned int i;
    for(i = 0; i < len; i ++){
        ret = ret * 10 + str[i] - '0';
    }
    return ret;
}

void InsertDataToString(int dat, char *str, int index){
    int arr[8];
    unsigned int neg = 0, i;
    if(dat < 0){
        str[index++] = '<';
        dat*=-1;
        neg = 1;
    }
    for(i = 0; dat > 0;){
        arr[i++] = dat % 10;
        dat /= 10;
    }
    for(i; i > 0;){
        str[index++] = arr[--i] + '0';
    }
    if(neg){
		str[index++] = '>';
	}
}

int StoreShortExp(char *str, int index, int len){
	int op1, op2, res, neg = 0;
	unsigned int i,j;
    char op = str[index];
    int start, end, tmp;
	
	str[index] = ' ';
	end = index-1;
	for(i = end; str[i] <= '9' && str[i] >= '0'; i --);
	start = i + 1;
    
    if(i != end){
        if(neg){
			op1 = (-1)*ChangeStringToInt(&str[start], end-start+1);
		}
        else{
			op1 = ChangeStringToInt(&str[start], end-start+1);
		}
        if(neg){
			start --;
			end ++;
		}
        for(j = start; j <= end; j ++){
            str[j] = ' ';
        }
    }

    tmp = start;
    start = index + 1;
    end = len - 1;
    neg = 0;

    if(str[start] == '<'){
        neg = 1;
        for(i = ++start; i < len; i ++){
            if(str[i] == '>'){
                end = i - 1;
            }
        }
    }
    else{
        for(i = start; str[i] <= '9' && str[i] >= '0'; i ++);
        end = i - 1;
    }

    if(i != start){
        if(neg){
			op2 = (-1)*ChangeStringToInt(&str[start], end-start+1);
		}
        else{
			op2 = ChangeStringToInt(&str[start], end-start+1);
		}
        if(neg){
			start --;
			end ++;
		}
        for(j = start; j <= end; j ++){
            str[j] = ' ';
        }
    }

    switch(op){
        case '+': res = op1 + op2; break;
        case '-': res = op1 - op2; break;
        case '*': res = op1 * op2; break;
        case '/': res = op1 / op2; break;
    }
    InsertDataToString(res, str, tmp);
    return res;
}

int *Calc(unsigned char *str){
    unsigned int len = strlen(str), neg = 0;
	int res = 0;
	unsigned int ret[8], i;
	
	for(i = 0; i < len; i ++){
        if(str[i] == '*'|| str[i] == '/'){
            res = StoreShortExp(str, i, len);
            len = DeleteCharactor(str, len);
            i = -1;
        }
    }   
    
	for(i = 0; i < len; i ++){
        if(str[i] == '+'|| str[i] == '-'){
            res = StoreShortExp(str, i, len);
            len = DeleteCharactor(str, len);
            i = -1;
        }
    }

	if(res < 0){
		neg = 1;
		res = -res;
	}
	for(i = 1; res; i ++){
		ret[i] = res % 10;
		res /= 10;
	}
	if(i == 1){
		ret[i++] = 0;
	}
	if(neg){
		ret[i++] = 13;
	}
	ret[0] = i - 1;
	return ret;
}
