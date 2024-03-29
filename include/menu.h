#ifndef _MENU_H
#define _MENU_H

// selección de objeto
#define OBJ_ALL 0b11111

#define OBJ_CUB 0b1
#define OBJ_TET 0b10
#define OBJ_PLY 0b100
#define OBJ_REV 0b1000
#define OBJ_TAP 0b10000


// selección de modo de visualización
#define VIS_ALL 0b01111

#define VIS_PUN 0b00001
#define VIS_LIN 0b00010
#define VIS_SOL 0b00100
#define VIS_AJE 0b01000

// P3
#define VIS_ILU 0b10000


// constantes

/// Ángulo de giro de la luz direccional
#define ANG_ILU 10

// colores terminal

#define RST   "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif