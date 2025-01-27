/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Alvarez, Giselé
    DNI: 34579954
    Entrega: Sí
    -----------------
    Apellido: Sarabia, Patricio
    DNI: 32335091
    Entrega: Sí
    -----------------
    Apellido: Varrenti, Pablo Martin
    DNI: 38056239
    Entrega: Sí
    -----------------
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funciones_grupo.h"
#include "funciones_alvarez.h"
#include "funciones_sarabia.h"
#include "funciones_varrenti.h"



int solucion(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Uso: bmpmanipuleitor <opcion1> <opcion2> ... <archivo> <archivo2>...\n");
        return 1;
    }

    char* archivo_entrada = NULL;
    char* opciones_validas[16]; // Máximo de opciones válidas
    int num_opciones_validas = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strstr(argv[i], ".bmp") != NULL)
        {
            archivo_entrada = argv[i];
        }
        else if (es_opcion_valida(argv[i]))
        {
            int es_duplicado = 0;
            for (int j = 0; j < num_opciones_validas; j++)
            {
                if (strcmp(opciones_validas[j], argv[i]) == 0)
                {
                    es_duplicado = 1;
                    break;
                }
            }
            if (!es_duplicado)
            {
                opciones_validas[num_opciones_validas++] = argv[i];
            }
        }
    }

    if (archivo_entrada == NULL)
    {
        printf("No se especificó un archivo BMP válido.\n");
        return 1;
    }

    FILE* archivo = fopen(archivo_entrada, "rb");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo %s\n", archivo_entrada);
        return 1;
    }
/////////////////////////ASIGNAMOS MEMORIA PARA LA MATRIZ
    t_metadata metadata = obtener_metadata(archivo);
    int ancho = metadata.ancho;
    int alto = metadata.alto;

    t_pixel** imagen = (t_pixel**)malloc(sizeof(t_pixel*) * alto);
    if (imagen == NULL)
    {
        perror("Error asignando memoria alto");
        fclose(archivo);
        return 1;
    }

    for (int j = 0; j < alto; j++)
    {
        imagen[j] = (t_pixel*)malloc(sizeof(t_pixel) * ancho);
        if (imagen[j] == NULL)
        {
            perror("Error asignando memoria ancho");
            for (int k = 0; k < j; k++)
            {
                free(imagen[k]);
            }
            free(imagen);
            fclose(archivo);
            return 1;
        }
    }
////////////////////////////////////////////////////
    fseek(archivo, metadata.offset, SEEK_SET); ///Que comience desde el parametro "comienzo de imagen" u offset, como se le quiera llamar

    for (int j = 0; j < alto; j++)
    {
        if (fread(imagen[j], sizeof(t_pixel), ancho, archivo) != ancho)
        {
            perror("Error leyendo la imagen");
            for (int k = 0; k < alto; k++)
            {
                free(imagen[k]);
            }
            free(imagen);
            fclose(archivo);
            return 1;
        }
        fseek(archivo, calcRelleno(ancho),SEEK_CUR); ///Mueve el cursor para ignorar los bits de relleno/padding
        //printf("%x|%x|%x\n", imagen[j]->pixel[0],imagen[j]->pixel[1],imagen[j]->pixel[2]);
    }

    fclose(archivo);

    for (int i = 0; i < num_opciones_validas; i++)
    {
        t_pixel** imagen_copia = (t_pixel**)malloc(sizeof(t_pixel*) * alto);
        if (imagen_copia == NULL)
        {
            perror("Error asignando memoria alto para copia");
            continue;
        }

        for (int j = 0; j < alto; j++)
        {
            imagen_copia[j] = (t_pixel*)malloc(sizeof(t_pixel) * ancho);
            if (imagen_copia[j] == NULL)
            {
                perror("Error asignando memoria ancho para copia");
                for (int k = 0; k < j; k++)
                {
                    free(imagen_copia[k]);
                }
                free(imagen_copia);
                continue;
            }

            // Copiamos la imagen
            memcpy(imagen_copia[j], imagen[j], sizeof(t_pixel) * ancho);
        }

        if (strcmp(opciones_validas[i], "--negativo") == 0)
        {
            negativo(imagen_copia, ancho, alto);
        }
        else if (strcmp(opciones_validas[i], "--escala-de-grises") == 0)
        {
            escala_de_grises(imagen_copia, ancho, alto);
        }
        else if (strncmp(opciones_validas[i], "--aumentar-contraste=", 20) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 21);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel aumentar contraste: Valor %d\n", nivel); //Mensaje depurador
                aumentar_contraste(imagen_copia, ancho, alto, nivel);
            }
            else
            {
                printf("El nivel de aumento de contraste %d no está entre 0 y 100.\n", nivel);
            }

        }
        else if (strncmp(opciones_validas[i], "--reducir-contraste=", 19) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 20);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel reducir contrastte: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 20 como nivel
                reducir_contraste(imagen_copia, ancho, alto, nivel);
            }
            else
            {
                printf("El nivel de reducción de contrate %d no está entre 0 y 100.\n", nivel);
            }

        }
        else if (strncmp(opciones_validas[i], "--tonalidad-azul=", 16) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 17);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel azul: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 50 como nivel
                aumentar_azul(imagen_copia, ancho, alto, nivel);
            }
            else
            {
                printf("El nivel de la tonalidad azul %d no está entre 0 y 100.\n", nivel);
            }

        }
        else if (strncmp(opciones_validas[i], "--tonalidad-roja=", 16) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 17);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel rojo: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 15 como nivel
                aumentar_rojo(imagen_copia, ancho, alto, nivel);
            }
            else
            {
                printf("El nivel de tonalidad roja %d no está entre 0 y 100.\n", nivel);
            }

        }
        else if (strncmp(opciones_validas[i], "--tonalidad-verde=", 17) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 18);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel verde: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 5 como nivel
                aumentar_verde(imagen_copia, ancho, alto, nivel);
            }
            else
            {
                printf("El nivel de tonalidad Verde %d no está entre 0 y 100.\n", nivel);
            }


        }
        else if (strcmp(opciones_validas[i], "--espejar-horizontal") == 0)
        {
            espejar_horizontal(imagen_copia, ancho, alto);
        }
        else if (strcmp(opciones_validas[i], "--espejar-vertical") == 0)
        {
            espejar_vertical(imagen_copia, ancho, alto);
        }
        else if (strncmp(opciones_validas[i], "--recortar=",10) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 11);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel recorte: Valor %d\n", nivel); //Mensaje depurador
                recortar_30(&imagen_copia, &ancho, &alto,&metadata,nivel);
            }
            else
            {
                printf("El porcentaje de Recorte %d no está entre 0 y 100.\n", nivel);
            }

        }
        else if (strcmp(opciones_validas[i], "--rotar-derecha") == 0)
        {
            rotar_derecha(&imagen_copia, &ancho, &alto,&metadata);

        }
        else if (strcmp(opciones_validas[i], "--rotar-izquierda") == 0)
        {
            rotar_izquierda(&imagen_copia, &ancho, &alto,&metadata);
        }
        else if (strncmp(opciones_validas[i], "--achicar=",9) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 10);

            if (validar_nivel(nivel))
            {
                //printf("El número %d está entre 0 y 100.\n", nivel);
                //printf("nivel % achicar: Valor %d\n", nivel); //Mensaje depurador
                achicar_10(&imagen_copia, &ancho, &alto,&metadata,nivel);
            }
            else
            {
                printf("El número %d no está entre 0 y 100.\n", nivel);
            }
        }
        else if (strcmp(opciones_validas[i], "--comodin") == 0)
        {
            comodin_aplicar_desenfoque(&imagen_copia, ancho, alto);
        }


        //Queremos obtener solo el nombre del archivo sin la ruta
        char* nombre_archivo = strrchr(archivo_entrada, '/');
        if (nombre_archivo == NULL)
        {
            nombre_archivo = strrchr(archivo_entrada, '\\');
        }
        if (nombre_archivo != NULL)
        {
            nombre_archivo++; // Avanzamos el puntero para omitir la barra
        }
        else
        {
            nombre_archivo = archivo_entrada; // No se encontró ninguna barra, usar el nombre completo
        }

        char archivo_salida[512];
        // Almaceno la cadena formateada en el búfer archivo_salida
        snprintf(archivo_salida, sizeof(archivo_salida), "%.*sIMAGEN_%s_%s", (int)(nombre_archivo - archivo_entrada), archivo_entrada, reemplazar_caracteres(opciones_validas[0] + 2), nombre_archivo);

        //printf("obtener_nombre_opcion(opciones_validas[i] + 2): %s\n", reemplazar_caracteres(opciones_validas[i] + 2));

        archivo = fopen(archivo_salida, "wb");
        if (archivo == NULL)
        {
            printf("No es posible crear el archivo %s\n", archivo_salida);
            for (int j = 0; j < alto; j++)
            {
                free(imagen_copia[j]);
            }
            free(imagen_copia);
            continue;
        }

        // Guardo la imagen con los cambios especificados
        guardar_imagen(archivo, imagen_copia, ancho, alto, metadata);

        //printf("Mensaje depurador test\n");

        fclose(archivo);

        for (int j = 0; j < alto; j++)
        {
            free(imagen_copia[j]);
        }
        free(imagen_copia);
    }

    // Liberación de memoria de la matriz imagen

    for (int j = 0; j < alto; j++)
    {
        free(imagen[j]);
    }
    free(imagen);

    //printf("Mensaje depurador test5\n");

    return 0;
}
void mover_cursor(FILE* archivo, int cant_posicion)
{
    unsigned char aux;
    for(int i = 0; i <cant_posicion; i++)
    {
        fread(&aux, sizeof(unsigned char), 1, archivo);
    }
}


bool es_opcion_valida(const char* opcion)
{
    //printf("opcion: %s\n", opcion);
    // Verificamos si la opción contiene '='
    const char *pos = strchr(opcion, '=');
    if (pos != NULL)
    {
        // Creamos una copia de la opción hasta el '='
        size_t length = pos - opcion;
        char resultado[length + 1];
        strncpy(resultado, opcion, length);
        resultado[length] = '\0';  // Queremos que el carácter nulo al final

        // Mensaje depurador para ver que hay en la variable resultado xd
        //printf("Resultado: %s\n", resultado);
        return  strcmp(resultado, "--aumentar-contraste") == 0 || strcmp(resultado, "--reducir-contraste") == 0 || strcmp(resultado, "--tonalidad-azul") == 0
                || strcmp(resultado, "--tonalidad-verde") == 0 || strcmp(resultado, "--tonalidad-roja") == 0 ||  strcmp(resultado, "--recortar") == 0
                || strcmp(resultado, "--achicar") == 0;
    }
    else
    {
        return strcmp(opcion, "--negativo") == 0 || strcmp(opcion, "--escala-de-grises") == 0 || strcmp(opcion, "--espejar-horizontal") == 0 || strcmp(opcion, "--espejar-vertical") == 0 || strcmp(opcion, "--rotar-derecha") == 0 || strcmp(opcion, "--rotar-izquierda") == 0
               || strcmp(opcion, "--concatenar-horizontal") == 0 || strcmp(opcion, "--concatenar-vertical") == 0
               || strcmp(opcion, "--comodin") == 0;
    }
}

bool es_duplicado(char* archivo, char** archivos_procesados, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(archivo, archivos_procesados[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool validar_nivel(int nivel)
{
    return (nivel >= 0 && nivel <= 100);
}

char *reemplazar_caracteres(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (cadena[i] == '-' || cadena[i] == '=')
        {
            cadena[i] = '_';
        }
    }
    return cadena;
}

t_metadata obtener_metadata(FILE* archivo)
{
    t_metadata metadata;
    mover_cursor(archivo, 0);

    // Leer tipo de archivo
    if (fread(&metadata.tipo, sizeof(unsigned short), 1, archivo) != 1)
    {
        perror("Error leyendo tipo de archivo en obtener_metadata");
        return metadata;
    }
    printf("tipo: %u\n", metadata.tipo);

    // Leer tamaño del archivo
    if (fread(&metadata.tamArchivo, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo tamArchivo en obtener_metadata");
        return metadata;
    }
    printf("tamArchivo: %u\n", metadata.tamArchivo);

    // Leer campos reservados
    if (fread(&metadata.reservado1, sizeof(unsigned short), 1, archivo) != 1 ||
            fread(&metadata.reservado2, sizeof(unsigned short), 1, archivo) != 1)
    {
        perror("Error leyendo campos reservados en obtener_metadata");
        return metadata;
    }
    printf("reservado1: %u\n", metadata.reservado1);

    // Leer offset
    if (fread(&metadata.offset, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo offset en obtener_metadata");
        return metadata;
    }
    printf("offset: %u\n", metadata.offset);

    // Leer tamaño del encabezado
    if (fread(&metadata.tamEncabezado, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo tamEncabezado en obtener_metadata");
        return metadata;
    }
    printf("tamEncabezado: %u\n", metadata.tamEncabezado);

    // Leer ancho y alto de la imagen
    if (fread(&metadata.ancho, sizeof(int), 1, archivo) != 1 ||
            fread(&metadata.alto, sizeof(int), 1, archivo) != 1)
    {
        perror("Error leyendo dimensiones en obtener_metadata");
        return metadata;
    }
    printf("ancho: %u\n", metadata.ancho);
    printf("alto: %u\n", metadata.alto);

    // Leer planos y profundidad
    if (fread(&metadata.planos, sizeof(unsigned short), 1, archivo) != 1 ||
            fread(&metadata.profundidad, sizeof(unsigned short), 1, archivo) != 1)
    {
        perror("Error leyendo planos o profundidad en obtener_metadata");
        return metadata;
    }
    printf("planos: %u\n", metadata.planos);
    printf("profundidad: %u\n", metadata.profundidad);

    // Leer compresión y tamaño de la imagen
    if (fread(&metadata.compresion, sizeof(unsigned int), 1, archivo) != 1 ||
            fread(&metadata.tamImagen, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo compresión o tamaño de la imagen en obtener_metadata");
        return metadata;
    }
    printf("compresion: %u\n", metadata.compresion);
    printf("tamImagen: %u\n", metadata.tamImagen);

    // Leer resolución y colores
    if (fread(&metadata.resolucionX, sizeof(int), 1, archivo) != 1 ||
            fread(&metadata.resolucionY, sizeof(int), 1, archivo) != 1 ||
            fread(&metadata.coloresUsados, sizeof(unsigned int), 1, archivo) != 1 ||
            fread(&metadata.coloresImportantes, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo resolución o colores en obtener_metadata");
        return metadata;
    }
    printf("resolucionX: %u\n", metadata.resolucionX);
    printf("resolucionY: %u\n", metadata.resolucionY);
    printf("coloresUsados: %u\n", metadata.coloresUsados);
    printf("coloresImportantes: %u\n", metadata.coloresImportantes);

    return metadata;
}


void guardar_imagen(FILE* archivo, t_pixel** imagen, int ancho, int alto, t_metadata metadata)
{
    // Escribir encabezado BMP
    fwrite(&metadata.tipo, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.tamArchivo, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.reservado1, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.reservado2, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.offset, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.tamEncabezado, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.ancho, sizeof(int), 1, archivo);
    fwrite(&metadata.alto, sizeof(int), 1, archivo);
    fwrite(&metadata.planos, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.profundidad, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.compresion, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.tamImagen, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.resolucionX, sizeof(int), 1, archivo);
    fwrite(&metadata.resolucionY, sizeof(int), 1, archivo);
    fwrite(&metadata.coloresUsados, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.coloresImportantes, sizeof(unsigned int), 1, archivo);


    // Escribir datos adicionales (84 bytes para BMPv5)
    unsigned char datos_adicionales = 0; // Inicializar con ceros o con los datos correspondientes
    ///Con este for si la imagen tenía relleno antes del comienzo de la imagen la misma será rellenada(?.
    for(int i = 0; i < (metadata.offset - 54); i++)
    {
        fwrite(&datos_adicionales, 1, 1, archivo);
    }


    // Calcular el tamaño de una fila y el relleno necesario
    ///No me funciona esta formula
    //int rowSize = ancho * 3; // 3 bytes por píxel (RGB)
    //int padding = (4 - (rowSize % 4)%4);
    int padding = calcRelleno(ancho);


    // Escribir datos de la imagen
    unsigned char paddingBytes[3] = {0, 0, 0}; // Máximo 3 bytes de relleno

    for (int i = 0; i <alto; i++)   // Almacena los píxeles
    {
        for (int j = 0; j < ancho; j++)
        {
            fwrite(&imagen[i][j], sizeof(t_pixel), 1, archivo);
        }

        // Escribir los bytes de relleno
        fwrite(paddingBytes, sizeof(unsigned char), padding, archivo);
    }

    //printf("Mensaje depurador test2\n");
}

int calcRelleno(unsigned int ancho)
{
    unsigned short bit_relleno =0;
    while((ancho*3+bit_relleno)%4!=0)
    {
        bit_relleno++;
    }
    return bit_relleno;
}
