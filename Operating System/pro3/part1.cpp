//random number guess
int isPrime()
{
   //osproj2b 
}

class Arg
{
public:
    void initialize(int a);//see textbook
private:
    int n;
    int l;
    int p;
    int c;
}
void initiallize(int arg1, int arg2, int arg3, int arg4)
{
    int n = arg1;
    int l = arg2;
    int p = arg3;
    int c = arg4;
}

void gatArg(char* argv, int argc)//decide have been end? argc?
{
   Arg myArg;
   if(argc <= 8)
   {
       myArg.initialize(atoi(argv[1]), atoi(argv[3], atoi(argv[5], 
                        atoi(argv[7])); 
    }
    else
        cout<<"There are some erros in your arguments."
}
    

void inBuffer()
{
     
}
void outBuffer()
{
     
}

public class PrimeTest1
{
public:
    static boolean IsPrimer(int q)  //
    {
    if (q < 2)
        return false;
    else if (q == 2)
        return true;
    for (int p = 2; p <= Math.sqrt(q); p++)
    {
        if (q % p == 0)
        return false;
    }
    return true;
    }
    static void main(String[] args)
    {
    int i = 0;
    int j;
    int q = 0;
    int a[] = new int[21];
    while (i <= 20)
    {
        q = (int) (Math.random() * 100);
        if (IsPrimer(q))
        {
        a[i] = q;
        for (j = i - 1; j >= 0; j--)
        {
            if (a[i] == a[j])
            i--;
        }
        i++;
        }
    }
    for (i = 0; i < 20; i++)
        System.out.print(a[i] + ",");
    }
}

