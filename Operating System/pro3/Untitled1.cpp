class Prime  
{
public: 
    Prime(){}    //constructor
    boolean isPrime(int number)  //determine if it is a prime
    {
        if (number <= 1)
            return false;
    }
    int checkPrime = number;
    checkPrime--;
    while (checkPrime > 1)
    {
        if (number % checkPrime == 0)
        {
        return false;
        }
        checkPrime--;
    }
    return true;
    }
    
    /**
     * @param amount
     * ������ɵ���������
     */
    void addPrime(int amount)   //����ָ���������������
    {
    for(int i = 0;i < amount;i++)
        while(true)
        {
        int temp = (int) (Math.random() * 100);
        if (isPrime(temp))
        {
            prime[i] = temp;
            break;
        }
        }
    }

    void add20Prime()   //����20���������
    {
    for (int i = 0; i < 20; i++)
        while (true)
        {
        int temp = (int) (Math.random() * 100);
        if (isPrime(temp))
        {
            prime[i] = temp;
            break;
        }
        }
    }

    void printPrime()  //��ӡ����
    {
    for(int i = 0;i <= 19;i++)
    {
        System.out.print(prime[i]+" ");
    }
    }
private:
        int[] prime = new int[1000];//store the prime numbers   
}  
