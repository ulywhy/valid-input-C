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

#define ANSI_COLOR_UN     "\x1b[90m"
#define ANSI_COLOR_RED     "\x1b[91m"
#define ANSI_COLOR_GREEN   "\x1b[92m"
#define ANSI_COLOR_YELLOW  "\x1b[93m"
#define ANSI_COLOR_BLUE    "\x1b[94m"
#define ANSI_COLOR_MAGENTA "\x1b[95m"
#define ANSI_COLOR_CYAN    "\x1b[96m"
#define ANSI_COLOR_RESET   "\x1b[92m"

#define ANSI_BACK_COLOR_UN     "\x1b[40m"
#define ANSI_BACK_COLOR_RED     "\x1b[41m"
#define ANSI_BACK_COLOR_GREEN   "\x1b[42m"
#define ANSI_BACK_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BACK_COLOR_BLUE    "\x1b[44m"
#define ANSI_BACK_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BACK_COLOR_CYAN    "\x1b[46m"
#define ANSI_BACK_COLOR_RESET    "\x1b[49m"

/*CLEAR INPUT STREAM*/

/*consume() elimina los caracteres que quedan en el stream
 *de entrada (teclado).
 *puede ser usada en lugar de fflush() en <stdio.h>, que
 *tiene un resultado impredecible,
 *ver http://man7.org/linux/man-pages/man3/fflush.3.html y
 * http://stackoverflow.com/a/16781818
 */
 
 /*consume()*/
 
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
	printf(ANSI_COLOR_YELLOW);
	int number;
	int check = scanf("%d", &number);
	int con = consume();
	while(con != 0 || check == 0){
		fprintf(stderr, "%sinválido, ingresa un entero\n%s", ANSI_COLOR_RESET, ANSI_COLOR_YELLOW);
		check = scanf("%d", &number);
		con = consume();
	
	}
	printf(ANSI_COLOR_RESET);
	return number;
}

/*getFloat() devuelve un número decimal.
*/
float getFloat(void){
	printf(ANSI_COLOR_YELLOW);
	float number;
	int check = scanf("%f", &number);
	int con = consume();
	while(con != 0 || check == 0){
		fprintf(stderr, "%sinválido, ingresa un decimal\n%s", ANSI_COLOR_RESET, ANSI_COLOR_YELLOW);
		check = scanf("%f", &number);
		con = consume();
	}
	fprintf(stdout, "%s", ANSI_COLOR_RESET);
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
	printf(ANSI_COLOR_YELLOW);
	do{
		check = fgets(ptr, size, stdin);
		len = strlen(check);
		check[len-1] = '\0';
	}while(check == NULL || *check == EOF || strlen(check) == 0);
	printf(ANSI_COLOR_RESET);
	return strlen(ptr);
}

/*getChar() devuelve un caracter.
 */
char getChar(void){
	printf(ANSI_COLOR_YELLOW);
	char letter;
	int check = scanf("%c", &letter);
	int con = consume();
	while(check == 0 || con != 0){
		printf(ANSI_COLOR_RESET);
		printf("inválido, ingresa un caracter ");
		printf(ANSI_COLOR_YELLOW);
		scanf("%c", &letter);
		con = consume();
	}
	printf(ANSI_COLOR_RESET);
	return letter;
}

/*****SIMPLE INTERFACE HELPERS*****/

/*menu() imprime un menù personalizado;
 *'header' es el titulo y debe ser de tipo string, y
 *'options' puede tener varias cadenas.
 *ejemplo para declarar 'options':
 	char *options[OPTLEN] = { 
			"1) Crear nueva base de datos\n",
			"2) Agragar elementos a base de datos actual\n",
			"3) Ver todos los registros\n",
			"4) Buscsar un registro\n",
			"0) Salir\n\n",
			"ingresa una opcion   "
			};
 *
 *donde OPTLEN define la longitud maxima de cada opción.
 */
void menu(char **options, char** header, int optc){
	int j;
	int len = strlen(header[0]);
	printf(ANSI_COLOR_RED);//RED TITLE
	if(header != NULL){
		for(j = 0; j < 7; ++j) puts(header[j]);//print title
	}
	printf(ANSI_COLOR_RESET);
	for(j = 0; j < optc; ++j){
		printf("%s", options[j]);
	}
	return;
}

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
	
	do{
		printf(ANSI_COLOR_RESET);
		printf("%s (%c/%c)  ", statement, yes, no);
		option = getChar();
		//allways compare lower cases 
		option = tolower(option);
		if( option == tolower(yes) )
			return true;
		else if( option == tolower(no) )
			return false;
	}while(true);
}
 
#endif
