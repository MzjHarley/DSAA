/*
 *行编辑程序
 *思路：将要写入文件的字符压入栈中,之后再写入文件中
 *如果碰到退格符'#'，就出栈删去一个字符；如果是退行符'@',就清空栈删去一行，其余字符压入栈中。
 *等到字符全部压入栈之后，就写入到文件中。
 */
FILE* fp;//定义文件指针，指向一个文件，它是一个全局变量
void LineEdit()
{
    Stack s;
    char ch;
    InitStack(s);//初始化栈
    ch = getchar();//从控制台接收字符；
    //ctrl+Z结束
    while(ch != EOF)//EOF为ctrl+Z键，全文未结束时
    {
        while(ch!=EOF && ch!='\n') //未到行末时
        {
            switch(ch)
            {
                case '#':
                    if(!isEmpty(s))
                    {
                        pop(s,ch);
                    }
                    break;
                case '@':
                    clearStack(s);
                    break;
                default:
                    push(s,ch);
            }
            ch = getchar();
        }
        //压栈完成后将栈中的字符写入文件并写入换行符
        char * p = s.base;
        while(s.top > p)
        {
            fputc(*p,fp);//将栈中字符送入到文件fp中
            p++;
        }
        fputc('\n',fp);
        clearStack(s);
        if(ch != EOF)
        {
            ch = getchar();
        }
    }
    destroyStack(s);
}
int main()
{
    fp = fopen("test.txt","w");//以“写入”方式打开文件。如果文件不存在，那么创建一个新文件；如果文件存在，那么清空文件内容（相当于删除原文件，再创建一个新文件）。
    if(fp)  //fp不为NULL
    {
        LineEdit();//编辑文件
        fclose(fp);//结束后关闭文件
    }
    else
    {
        printf("打开文件失败.\n");
    }
}