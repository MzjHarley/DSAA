/*
 *�б༭����
 *˼·����Ҫд���ļ����ַ�ѹ��ջ��,֮����д���ļ���
 *��������˸��'#'���ͳ�ջɾȥһ���ַ�����������з�'@',�����ջɾȥһ�У������ַ�ѹ��ջ�С�
 *�ȵ��ַ�ȫ��ѹ��ջ֮�󣬾�д�뵽�ļ��С�
 */
FILE* fp;//�����ļ�ָ�룬ָ��һ���ļ�������һ��ȫ�ֱ���
void LineEdit()
{
    Stack s;
    char ch;
    InitStack(s);//��ʼ��ջ
    ch = getchar();//�ӿ���̨�����ַ���
    //ctrl+Z����
    while(ch != EOF)//EOFΪctrl+Z����ȫ��δ����ʱ
    {
        while(ch!=EOF && ch!='\n') //δ����ĩʱ
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
        //ѹջ��ɺ�ջ�е��ַ�д���ļ���д�뻻�з�
        char * p = s.base;
        while(s.top > p)
        {
            fputc(*p,fp);//��ջ���ַ����뵽�ļ�fp��
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
    fp = fopen("test.txt","w");//�ԡ�д�롱��ʽ���ļ�������ļ������ڣ���ô����һ�����ļ�������ļ����ڣ���ô����ļ����ݣ��൱��ɾ��ԭ�ļ����ٴ���һ�����ļ�����
    if(fp)  //fp��ΪNULL
    {
        LineEdit();//�༭�ļ�
        fclose(fp);//������ر��ļ�
    }
    else
    {
        printf("���ļ�ʧ��.\n");
    }
}