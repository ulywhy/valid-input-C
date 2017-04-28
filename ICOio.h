/*
 *
 *funciones para validar valores de entrada del usuario
 *para incluir en Code::Blocks ver 
  http://wiki.codeblocks.org/index.php/FAQ-Compiling_(general)#Q:_I_would_like_to_compile_a_project_using_some_non-standard_libraries._How_can_I_indicate_to_CodeBlocks_that_these_libraries_and_include_files_exist.3F
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//definicion de variable booleana, donde 1:verdadero y 0:falso
#ifndef bool
#define bool short
#define true 1
#define false 0
#endif

#ifndef ICO_IO_HEADER
#define ICO_IO_HEADER

/*CLEAR INPUT STREAM*/

/*consume() elimina los caracteres que quedan en el stream
 *de entrada (teclado).
 *puede ser usada en lugar de fflush() en <stdio.h>, que
 *tiene un resultado impredecible,
 *ver http://man7.org/linux/man-pages/man3/fflush.3.html y
 * http://stackoverflow.com/a/16781818
 */
 
 /*consume() clears data left in the input stream*/
int consume(void){
	int count = 0;
	char c;
	do{
		c = getchar();
		if(isgraph(c)) ++count;
	}while(c != EOF && c != '\n');
	return count;
}


/*clear() imprime un conjunto de caracteres que simulan la
 *llamada a funciones del sistema operativo "cls" o "clear"
 *para windows y Lunix respectivamente.
 */
void clear(void){
	printf("\033[H\033[J");
	return;
}

/*****NUMBERS INPUT*****/

/*getInt() devuelve un entero.
*/
int getInt(void){
	int number;
	int check = scanf("%d", &number);
	int con = consume();
	while(con != 0 || check == 0){
		fprintf(stderr, "inválido, ingresa un entero\n");
		check = scanf("%d", &number);
		con = consume();
	}
	return number;
}

/*getFloat() devuelve un número decimal.
*/
float getFloat(void){
	float number;
	int check = scanf("%f", &number);
	int con = consume();
	while(con != 0 || check == 0){
		fprintf(stderr, "inválido, ingresa un decimal\n");
		check = scanf("%f", &number);
		con = consume();
	}
	return number;
}

/*****CHARACTERS INPUT*****/

/*getString() guarda una cadena de caracteres de longitud
 *menor o igual a 'size'-1 en el arreglo al que apunta la
 *variable ptr.
 */
int getString(char* ptr, int size){
	char * check = NULL;
	int len = 0;
	do{
		check = fgets(ptr, size, stdin);
		len = strlen(check);
		check[len-1] = '\0';
	}while(check == NULL || *check == EOF || strlen(check) == 0);
	return strlen(ptr);
}

/*getChar() devuelve un caracter.
 */
char getChar(void){
	char letter;
	int check = scanf("%c", &letter);
	int con = consume();
	while(check == 0 || con != 0){
		printf("inválido, ingresa un caracter ");
		scanf("%c", &letter);
		con = consume();
	}
	return letter;
}

/*****SIMPLE INTERFACE HELPERS*****/

/*binaryCharDecision() valida entradas de valores binarios 
 *(1/0) (verdad/faso) (si/no). imrime una instrucción o
 *pregunta mientras no se ingrese los caracteres
 *corrspondientes a 'yes' o 'no'
 *'yes' or 'no' charcter;
 *binaryCharDecision() considera cada letra como minúscula, 
 *es lo mismo 'S' y 's'.
 *VALOR DE RETORNO
 *binaryCharDecision() devuelve true o false si la respuesta
 *del usuario es 'yes' y 'no' respectivamente según la
 *opción seleccionada por el usuario.
 */
bool binaryCharDecision(const char* statement, const char yes, const char no){
	char option;
	int len = strlen(statement);
	int j;
	
	for(;;){
		printf("%s (%c/%c)  ", statement, yes, no);
		option = getChar();
		//allways compare lower cases 
		option = tolower(option);
		if( option == tolower(yes) )
			return true;
		else if( option == tolower(no) )
			return false;
	}
}
#endif
