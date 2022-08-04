/*
*********************
servidor_chat.c
*********************
*/
 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#define VERDE "\x1b[32m"
//#define AZUL   "\x1b[34m"
struct sockaddr;//Declaración de la estructura sockaddr contenidas en #include<netinet/in.h>
//Declaración de funciones
void SaberComoEs() //Saber como es el sistema.
{
   int16_t i = 1;
   int8_t *p = (int8_t *) &i;
   printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
     if (p[0] == 1) printf("Tu sistema es Little Endian\n");
 
   else           printf("Tu sistema es Big Endian\n");
printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
 
   return ;
}
 
 
/*Declaramos una función destinada para el chat cliente servidor.
donde se establece el buffer para el intercambio*/
void lafunc(int chatServClient)
{
    char buferIntercambio[90]; //Reserva de buffer para el intercambio de 90bytes write y read
    int h;
    // Este es un bucle  repetitivo read >-> write para el  chat interactivo
    for (;;) {
        bzero(buferIntercambio, 90);//borra los datos en los n bytes de la memoria
       //comenzando en la ubicación señalada , escribiendo ceros (bytes que contiene '\0') en esa área.
 
        // Leemos el mensaje del cliente y lo copiamos en buferIntermedio.
        read(chatServClient, buferIntercambio, sizeof(buferIntercambio));
 
        // Imprimimos el contenido del buffer del cliente.
        printf("Mensaje del cliente: %s\t : ", buferIntercambio);
        bzero( buferIntercambio,90);//volvemos a borrar datos
        h = 0;
        // Copiamos el mensaje del Servidor en el buffer.
        while ((buferIntercambio[h++] = getchar()) != '\n');
        //repetir bucle mientras no sea igual.
        //chatServClient es el nuevo descriptor de socket creado por aceppt.
        //Para cada cliente aceptado se crear'un nuevo Descriptor Socket
 
        //  Mandamos el contenido del bufer al client utilizando la función write().
        write(chatServClient, buferIntercambio, sizeof(buferIntercambio));
 
        // Si el mensaje contiene  "Exit" entonces el seridor sale y el chat termina.
        if (strncmp("hasta luego lucas", buferIntercambio, 16) == 0)
           // la llamada strncmp compara caracteres,
            //en este caso le decimos que compare 16.
            // si el servidor manda el mensaje "hasta luego lucas" 16 bytes --16) == 0)
            //el servidor saldrá de la conexión
         {
            printf("Salida del Servidor\n");
            break;
 
        }
        }
        }
//***************** 
// Inicio de main
  
int main()
{
    char Codigo_ascii[17];
    size_t i, j;
    int  salida;    /* Salida del comando */
    char comando[60];   /* Comando a ejecutar */
 //**********************************
printf ( "LLAMADA (ifconfig) con system.\n");
sprintf (comando, "ifconfig ");
salida = system (comando);

  //********************************   

/*Llamamos a esta función
para saber el tipo de alojamiento en tu sistema*/
SaberComoEs();
/*Hacemos la entrada de la ip con la función scanf*/
char IP[24];
printf("Introduce una IP\n");
scanf("%s",IP);
printf("++++++++++++++++\n");
    //char *ip = "127.0.0.1"; Esta sería otra forma de introducir ip estática.
    //declaracion de variables a estructuras.
    int sockDescriptor, chatServClient, Larg,lon_MiServ;
    struct sockaddr_in strucServidor, struCliente;
 
    // Creación del Socket y comprobación de su ejecución, si devuelve -1 el descriptor habrá error
    sockDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockDescriptor == -1) {
        printf("La creación del socket no ha tenido exito\n");
        exit(0);
    }
    else
        //printf("Socket creado con éxito\n");
    bzero(&strucServidor, sizeof(strucServidor));
 
 /*En vez de pasar el puerto por argumento de main,
  lo hacemos por medio de la entrada standard scanf.*/
printf("*******************\n" );
printf("Introduce un Puerto(Mejor,superior a 1000):\n");
printf("+++++++++++++++++++\n");
char puerto [20];
scanf("%s",puerto);
printf("-------------------\n" );
int valor =atoi(puerto); //Esta función convierte el argumento de una cadena  en un número entero (tipo int).
printf("Valor de entrada: %i\n",valor );
 
    // assignaciones ip, puerto
    strucServidor.sin_family = AF_INET;
    strucServidor.sin_addr.s_addr = inet_addr(IP);
    strucServidor.sin_port = htons(valor);
    /*La función htons convierte un u_short de host
     a orden de bytes de red TCP/IP ( big-endian).*/
   printf("Socket creado con éxito\n");
    // Llamamos a la función bind() para crear socket.
    if ((bind(sockDescriptor, (struct sockaddr *)&strucServidor, sizeof(strucServidor))) != 0) {
        printf("No se ha podido asignar dirección. Bind ha fayado\n");
                exit(0);
    }
    else
 
 printf("Tamaño de la strucServidor = %li\n", sizeof(strucServidor));
 
lon_MiServ=sizeof(strucServidor);
getsockname (sockDescriptor,(struct sockaddr *)&strucServidor,&lon_MiServ);//hacemos un cast a (struct sockaddr *)
printf("La IP local es: %s\n", inet_ntoa(strucServidor.sin_addr));
printf("El Puerto local de conexión es: %d\n", (int) ntohs(strucServidor.sin_port));
printf("----------------------------------------------\n");
printf("Disposición en memoria del Puerto y la IP\n");


//Rutina de volcado para ver posición en memoria del puerto e IP

for (i = 0; i < 123; ++i) {
        printf("%02X ", ((unsigned char*)&strucServidor)[i]);
        if (((unsigned char*)&strucServidor)[i] >= ' ' && ((unsigned char*)&strucServidor)[i] <= '~')
         {
            Codigo_ascii[i % 16] = ((unsigned char*)&strucServidor)[i];
        } else {
            Codigo_ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1==123) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf(" |  %s \n", Codigo_ascii);
            }
            }
            }


// Ahora el Servidor está preparado para escuchar
printf("\n");
printf("***********************************************\n");
printf("Socket enlazado con éxito.\n");
    if ((listen(sockDescriptor, 5)) != 0) { //Ponemos el socket a escuchar, y  una cola máxima de 5 clientes.
        printf("La escucha de Clientes ha fallado...\n");
        exit(0);
    }
    else
        printf("El Servidor está preparado\n");
    Larg = sizeof(struCliente);
 
    // Aceptamos datos del cliente.
chatServClient = accept(sockDescriptor, (struct sockaddr *)&struCliente, &Larg);//Nuevo socket abierto por aceppt()
        if (chatServClient < 0) {
        printf("El servidor no ha aceptado\n");
        exit(0);
    }
    else
    printf("El servidor acepta CLIENTE con nuevo SOCKET-Descriptor %d: \n",chatServClient);
   //dump(&strucServidor, 120);
    // Llamada a la función lafunc que trabajará con los buffer de mensajes


lafunc(chatServClient);  //Llamada a lafun
 
    // El socket descriptor es cerrado
    close(sockDescriptor);
 }

