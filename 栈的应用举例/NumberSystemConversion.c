/*
 *1.数制转换：利用栈将数字转换进制后得到的数字压栈，之后在出栈。 n为要转换的数字，N为进制
 */
Stack s;//定义一个栈s
while(n)
{
    push(s,n%N);//将n%N压入栈中
    n = n/N;
}
while(!isEmpty(s))
{
    pop(s,e);//出栈，并将出栈的值赋给e
    printf("%d",e))
}
printf("\n");
如果为16进制转换，则在出栈时加上限制条件：
while(!isEmpty(s))
{
    pop(s,e);//出栈，并将出栈的值赋给e
    if(e <= 9)
    {
        printf("%d",e))
    }
    else
    {
        printf("%c",e+55));//以字符形式输出ABCDEF
    }
}