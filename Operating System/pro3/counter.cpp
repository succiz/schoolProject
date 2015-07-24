//counter
while(true)
{
    while(counter == BUFFERSIZE)
    
    ;//do nothing
    
    buffer[in] = nextProcuced;
    
    in = (in + 1) % BUFFERSIZE;
    
    counter++;
}

while(true)
{
   while(counter == 0)
   
   ;
   
   nextConsumered = buffer[Out];
   
   out = (out + 1) % BUFERSIZE;
   
   counter--;
}
