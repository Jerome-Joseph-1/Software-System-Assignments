gcc -o main main.c 

if [ -f main ]; then 
    ./main
    rm main 
fi 