/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0-BETA   1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± CABECERA > TECLAS.H                                                    ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0/beta                                                    ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

#if !defined(TECLAS_H)
#define TECLAS_H

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± teclas especiales ASCII                                                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define KEY_ESC	    0x1B
#define KEY_ENTER   0x0D
#define KEY_BS	    0x08
#define KEY_TAB     0x09

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± teclas especiales de exploraci¢n del teclado                           ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define KEY_SHIFT_TAB	0x0F

#define KEY_F1	    0x3b
#define KEY_F2      0x3c
#define KEY_F3      0x3d
#define KEY_F4      0x3e
#define KEY_F5      0x3f
#define KEY_F6      0x40
#define KEY_F7      0x41
#define KEY_F8      0x42
#define KEY_F9      0x43
#define KEY_F10     0x44
#define KEY_F11
#define KEY_F12

#define KEY_SHIFT_F1	    0x54
#define KEY_SHIFT_F2        0x55
#define KEY_SHIFT_F3        0x56
#define KEY_SHIFT_F4        0x57
#define KEY_SHIFT_F5        0x58
#define KEY_SHIFT_F6        0x59
#define KEY_SHIFT_F7        0x5A
#define KEY_SHIFT_F8        0x5B
#define KEY_SHIFT_F9        0x5C
#define KEY_SHIFT_F10       0x5D
#define KEY_SHIFT_F11
#define KEY_SHIFT_F12

#define KEY_CTRL_F1	0x5E
#define KEY_CTRL_F2     0x5F
#define KEY_CTRL_F3     0x60
#define KEY_CTRL_F4     0x61
#define KEY_CTRL_F5     0x62
#define KEY_CTRL_F6     0x63
#define KEY_CTRL_F7     0x64
#define KEY_CTRL_F8     0x65
#define KEY_CTRL_F9     0x66
#define KEY_CTRL_F10    0x67
#define KEY_CTRL_F11
#define KEY_CTRL_F12

#define KEY_ALT_F1	0x68
#define KEY_ALT_F2      0x69
#define KEY_ALT_F3      0x6A
#define KEY_ALT_F4      0x6B
#define KEY_ALT_F5      0x6C
#define KEY_ALT_F6      0x6D
#define KEY_ALT_F7      0x6E
#define KEY_ALT_F8      0x6F
#define KEY_ALT_F9      0x70
#define KEY_ALT_F10     0x71
#define KEY_ALT_F11
#define KEY_ALT_F12

#define KEY_INS	    0x52
#define KEY_DEL     0x53
#define KEY_ORG     0x47
#define KEY_END     0x4F
#define KEY_PUP     0x49
#define KEY_PDN     0x51

#define KEY_CTRL_INS	0x92
#define KEY_CTRL_DEL    0x93
#define KEY_CTRL_ORG    0x77
#define KEY_CTRL_END    0x75
#define KEY_CTRL_PUP    0x84
#define KEY_CTRL_PDN    0x76

#define KEY_UP	        0x48
#define KEY_DOWN        0x50
#define KEY_RIGHT       0x4D
#define KEY_LEFT        0x4B

#define KEY_CTRL_UP	0x8D
#define KEY_CTRL_DOWN   0x91
#define KEY_CTRL_RIGHT  0x74
#define KEY_CTRL_LEFT   0x73

#endif
