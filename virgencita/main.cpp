/*****
 Computacion Grafica: CCOMP 7-1
 * Gonzales Navarrete Mateo
 * Nieto Rosas Miguel
 * Palma Ugarte Joaquin
 *****/


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buildShaders.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

const int N = 20+4; // number of figures
const int MV = 189; // maximum number of vertexs in one figure 75(previus)

unsigned int VBO, VAO, EBO[N];

const float vertices[] = {

  ////// Fondo

  -0.7, 1.0, 0.0,//0
    -0.6, 0.7, 0.0,//1
    -0.7, 0.75, 0.0,//2
    -0.7, 0.55, 0.0,//3
    -0.5, 0.3, 0.0,//4
    -0.7, 0.15, 0.0,//5
    -0.7, 0.0, 0.0,//6
    -0.45, -0.05, 0.0,//7
    -0.7, -0.1, 0.0,//8
    -0.7, -0.4, 0.0,//9
    -0.4, -0.5, 0.0,//10
    -0.7, -0.7, 0.0,//11
    -0.7, -0.9, 0.0,//12
    -0.45, -0.95, 0.0,//13
    -0.7, -1.0, 0.0,//14
    -0.48, -1.0, 0.0,//15
    -0.45, 1.0, 0.0,//16
    -0.15, 0.95, 0.0,//17
    -0.25, 0.9, 0.0,//18
    -0.35, 0.8, 0.0,//19
    -0.4, 0.75, 0.0,//20
    -0.43, 0.65, 0.0,//21
    -0.45, 0.5, 0.0,//22
    -0.2, 0.6, 0.0,//23
    -0.4, 0.35, 0.0,//24
    0.0, 1.0, 0.0,//25
    -0.35, 0.25, 0.0,//26
    -0.3, 0.2, 0.0,//27
    -0.2, 0.15, 0.0,//28
    0.0, 0.1, 0.0,//29
    0.3, -0.7, 0.0,//30
    0.8, -0.3, 0.0,//31
    0.40, 0.1, 0.0,//32
    -0.05, -0.7, 0.0,//33
    -0.15, -1.0, 0.0,//34
    -0.3, -1.0, 0.0,//35
    0.6, -1.0, 0.0,//36
    0.8, -1.0, 0.0,//37
    0.7, -0.8, 0.0,//38
    0.55, -0.65, 0.0,//39
    0.8, 0.0, 0.0,//40
    0.8, 0.45, 0.0,//41
    0.75, 0.5, 0.0,//42
    0.8, 0.6, 0.0,//43
    0.6, 0.6, 0.0,//44
    0.8, 0.95, 0.0,//45
    0.7, 1.0, 0.0,//46
    0.6, 1.0, 0.0,//47
    0.35, 1.0, 0.0,//48
    0.15, 0.98, 0.0,//49
    0.25, 0.96, 0.0,//50
    0.34, 0.92, 0.0,//51
    0.45, 0.85, 0.0,//52
    0.55, 0.75, 0.0,//53
    0.0, 0.5, 0.0,//54
    0.58, 0.5, 0.0,//55
    0.52, 0.38, 0.0,//56
    0.45, 0.3, 0.0,//57
    0.3, 0.2, 0.0,//58
    0.8, 1.0, 0.0,//59

    ////// Virgencita

    -.1f, 0.72f, 0.0f,//60
    0.0f, 0.78f, 0.0f,
    0.01f, 0.7f, 0.0f,
    0.1f, 0.78f, 0.0f,
    0.12f, 0.65f, 0.0f,
    0.2f, 0.76f, 0.0f,
    0.2f, 0.6f, 0.0f,
    0.28f, 0.7f, 0.0f,
    0.28f, 0.5f, 0.0f,
    0.32f, 0.62f, 0.0f,
    0.33f, 0.43f, 0.0f,//70
    0.38f, 0.53f, 0.0f,
    0.36f, 0.37f, 0.0f,
    0.41f, 0.48f, 0.0f,
    0.40f, 0.31f, 0.0f,
    0.44f, 0.38f, 0.0f,
    0.41f, 0.28f, 0.0f,
    0.45f, 0.3f, 0.0f,
    0.47f, 0.12f, 0.0f,

    -0.16f, 0.67f, 0.0f,
    -.1f, 0.65f, 0.0f,
    0.0f, 0.6f, 0.0f,//80
    0.1f, 0.51f, 0.0f,
    0.15f, 0.45f, 0.0f,
    0.19f, 0.36f, 0.0f,
    0.26f, 0.2f, 0.0f,
    0.3f, 0.05f, 0.0f,
    0.32f, -0.14f, 0.0f,
    0.5f, -0.05f, 0.0f,
    0.33f, -0.24f, 0.0f,
    0.54f, -0.2f, 0.0f,
    0.31f, -0.32f, 0.0f,//90
    0.56f, -0.32f, 0.0f,
    0.3f, -0.52f, 0.0f,
    0.55f, -0.55f, 0.0f,
    0.24f, -1.f, 0.0f,
    0.42f, -0.9f, 0.0f,

    0.07f, 0.48f, 0.0f,
    0.1f, 0.36f, 0.0f,
    0.14f, 0.22f, 0.0f,
    0.17f, 0.15f, 0.0f,
    0.18f, -0.06f, 0.0f,//100
    0.22f, -0.12f, 0.0f,
    0.23f, -0.21f, 0.0f,
    0.22f, -0.29f, 0.0f,
    0.135f, -0.4f, 0.0f,
    0.16f, -0.59f, 0.0f,
    0.29f, -0.6f, 0.0f,
    0.27f, -0.79f, 0.0f,
    0.16f, -0.72f, 0.0f,
    0.25f, -0.9f, 0.0f,
    0.1f, -0.9f, 0.0f,//110
    0.16f, -1.f, 0.0f,
    0.01f, -0.99f, 0.0f,

    -0.19f, 0.64f, 0.0f,
    -0.21f, 0.58f, 0.0f,
    -0.14f, 0.53f, 0.0f,
    -0.04f, 0.48f, 0.0f,
    0.05f, 0.42f, 0.0f,

    -0.21f, 0.46f, 0.0f,
    -0.15f, 0.34f, 0.0f,
    -0.14f, 0.25f, 0.0f,//120
    -0.12f, 0.245f, 0.0f,
    -0.07f, 0.19f, 0.0f,
    -0.02f, 0.16f, 0.0f,
    0.04f, 0.16f, 0.0f,
    0.04f, 0.11f, 0.0f,

    0.0f, 0.03f, 0.0f,//127


    //circulo perfecto
    -0.03f, -0.2f, 0.0f,//7 + x = 128
    0.17f, -0.2f, 0.0f, // 8
    0.169001f, -0.180033f, 0.0f, // 9
    0.166013f, -0.160266f, 0.0f, // 10
    0.161067f, -0.140896f, 0.0f, // 11
    0.154212f, -0.122116f, 0.0f, // 12
    0.145517f, -0.104115f, 0.0f, // 13
    0.135067f, -0.0870715f, 0.0f, // 14
    0.122968f, -0.0711565f, 0.0f, // 15
    0.109341f, -0.0565288f, 0.0f, // 16
    0.094322f, -0.0433346f, 0.0f, // 17
    0.0780605f, -0.0317058f, 0.0f, // 18
    0.0607192f, -0.0217585f, 0.0f, // 19
    0.044716f, -0.0135922f, 0.0f, // 20
    0.0234998f, -0.00728836f, 0.0f, // 21
    0.00399343f, -0.00291005f, 0.0f, // 22
    -0.0158526f, -0.000501003f, 0.0f, // 23
    -0.0358399f, -8.52794e-05f, 0.0f, // 24
    -0.0557689f, -0.00166704f, 0.0f, // 25
    -0.0754404f, -0.00523047f, 0.0f, // 26
    -0.0946579f, -0.01074f, 0.0f, // 27
    -0.113229f, -0.0181405f, 0.0f, // 28
    -0.130969f, -0.0273581f, 0.0f, // 29
    -0.1477f, -0.0383007f, 0.0f, // 30
    -0.163255f, -0.050859f, 0.0f, // 31
    -0.177479f, -0.0649074f, 0.0f, // 32
    -0.190229f, -0.0803056f, 0.0f, // 33
    -0.201378f, -0.0968997f, 0.0f, // 34
    -0.210814f, -0.114524f, 0.0f, // 35
    -0.218444f, -0.133002f, 0.0f, // 36
    -0.224192f, -0.15215f, 0.0f, // 37
    -0.227998f, -0.171776f, 0.0f, // 38
    -0.229827f, -0.191684f, 0.0f, // 39
    -0.229659f, -0.211675f, 0.0f, // 40
    -0.227496f, -0.231549f, 0.0f, // 41
    -0.22336f, -0.251108f, 0.0f, // 42
    -0.217291f, -0.270157f, 0.0f, // 43
    -0.209352f, -0.288504f, 0.0f, // 44
    -0.19962f, -0.305967f, 0.0f, // 45
    -0.188194f, -0.322372f, 0.0f, // 46
    -0.175186f, -0.337553f, 0.0f, // 47
    -0.160729f, -0.35136f, 0.0f, // 48
    -0.144965f, -0.363655f, 0.0f, // 49
    -0.128052f, -0.374315f, 0.0f, // 50
    -0.11016f, -0.383233f, 0.0f, // 51
    -0.0914666f, -0.39032f, 0.0f, // 52
    -0.0721592f, -0.395506f, 0.0f, // 53
    -0.0524305f, -0.398738f, 0.0f, // 54
    -0.0324777f, -0.399985f, 0.0f, // 55
    -0.0125002f, -0.399233f, 0.0f, // 56
    0.00730247f, -0.396491f, 0.0f, // 57
    0.0267324f, -0.391785f, 0.0f, // 58
    0.0455955f, -0.385163f, 0.0f, // 59
    0.0637033f, -0.376691f, 0.0f, // 60
    0.0808749f, -0.366453f, 0.0f, // 61
    0.0969386f, -0.354553f, 0.0f, // 62
    0.111734f, -0.341108f, 0.0f, // 63
    0.125113f, -0.326253f, 0.0f, // 64
    0.136943f, -0.310137f, 0.0f, // 65
    0.147104f, -0.29292f, 0.0f, // 66
    0.155496f, -0.274775f, 0.0f, // 67
    0.162034f, -0.255883f, 0.0f, // 68
    0.166654f, -0.236433f, 0.0f, // 69
    0.169308f, -0.216618f, 0.0f, // 70



    //mano
    -0.3f, -0.7f, 0.0f, // 71
    -0.32f, -0.6f, 0.0f, // 72
    -0.35f, -0.5f, 0.0f, // 73
    -0.33f, -0.4f, 0.0f, // 74
    -0.3f, -0.3f, 0.0f, // 75
    -0.24f, -0.2f, 0.0f, // 76
    -0.17f, -0.1f, 0.0f, // 77
    -0.1f, -0.05f, 0.0f, // 78
    -0.08f, -0.08f, 0.0f, // 79
    -0.1f, -0.12f, 0.0f, // 80
    -0.24f, -0.3f, 0.0f, // 81
    -0.1f, -0.3f, 0.0f, // 82
    -0.05f, -0.27f, 0.0f, // 83
    -0.01f, -0.25f, 0.0f, // 84
    0.03f, -0.26f, 0.0f, // 85
    0.08f, -0.26f, 0.0f, // 86
    0.15f, -0.2f, 0.0f, // 87
    0.15f, -0.28f, 0.0f, // 88
    0.12f, -0.33f, 0.0f, // 89
    0.07f, -0.35f, 0.0f, // 90
    0.02f, -0.4f, 0.0f, // 91
    0.04f, -0.49f, 0.0f, // 92
    0.05f, -0.55f, 0.0f, // 93
    -0.05f, -0.63f, 0.0f, // 94
    -0.18f, -0.68f, 0.0f, // 95

    //cabello
    0.15f, -0.14f, 0.0f, // 96
    0.11f, -0.1f, 0.0f, // 97
    0.06f, -0.08f, 0.0f, // 98
    0.02f, -0.06f, 0.0f, // 99
    -0.04f, -0.06f, 0.0f, // 100
    -0.1f, -0.08f, 0.0f, // 101
    -0.28f, -0.31f, 0.0f, // 102


    //ropa
    -0.22f, -0.85f, 0.0f, // 103
    -0.15f, -0.92f, 0.0f, // 104
    -0.05f, -0.97f, 0.0f, // 105
    0.02f, -0.97f, 0.0f, // 106
    0.1f, -0.9f, 0.0f, // 107
    0.15f, -0.8f, 0.0f, // 108
    0.16f, -0.7f, 0.0f, // 109
    0.19f, -0.6f, 0.0f, // 110
    0.18f, -0.5f, 0.0f, // 111
    0.15f, -0.4f, 0.0f, // 112



  };

unsigned int figures[N][MV] = {

  ////// Fondo

  {
    // 1
    0, 1, 2,
    0, 1, 16,//
    42, 44, 55,
    55, 42, 56,
    42, 56, 32,
    32, 56, 57,//
    32, 31, 39,//
    32, 40, 31,//
  },
  {
    // 2
    2, 1, 3,
    1, 3, 4,
    3, 4, 5,//
    1, 21, 4,
    21, 22, 4,
    22, 24, 4,//
  },
  {
    // 3
    4, 5, 8,
    4, 8, 7,//
    30, 39, 38,
    30, 38, 36,
    30, 36, 34,//
  },
  {
    // 4
    7, 8, 9,
    10, 9, 7,//
    39, 31, 38,//
  },
  {
    // 5
    9, 10, 12,
    10, 12, 13,
    13, 33, 34,
    13, 35, 34,
    13, 33, 10,//
    16, 17, 25,
    25, 48, 49,
    49, 48, 50,
    50, 48, 51,
    51, 48, 47,
    51, 52, 47,
    52, 53, 47,
    53, 44, 41,
    47, 53, 41,
    47, 41, 59,//
  },
  {
    // 6
    4, 24, 26,
    4, 26, 7,
    7, 26, 27,
    7, 27, 28,
    7, 28, 29,//
    7, 29, 10,
    20, 20, 33,//
    31, 32, 30,
    30, 39, 31,//
  },
  {
    // 7
    54, 17, 18,
    54, 18, 19,
    54, 19, 20,
    54, 20, 21,
    54, 21, 22,
    54, 22, 24,
    54, 24, 26,
    54, 26, 27,
    54, 27, 28,
    54, 28, 29,
    54, 29, 58,
    54, 58, 57,
    54, 57, 56,
    54, 56, 55,
    54, 55, 44,
    54, 44, 53,
    54, 53, 52,
    54, 52, 51,
    54, 51, 50,
    54, 50, 49,
    54, 49, 25,
    54, 25, 17,
  },
  {
    // 8
    16, 1, 21,
    16, 21, 20,
    16, 20, 19,
    16, 19, 18,
    16, 18, 17,//
    42, 40, 32,//
    12, 13, 14,
    14, 13, 15,
    13, 15, 35,//
    40, 41, 42,//
  },
  {
    // 9
    38, 36, 37,
    37, 38, 31,//
  },

  ////// Virgencita

  {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    18
  }, // Veil Outter
  {
    19, 0, 20,
    2, 21, 4,
    22, 6, 23,
    8, 24, 12,
    25, 16, 26,
    18, 27,
    28, 29, 30,
    31, 32, 33,
    34, 35, 36
  }, // Veil Middle
  {
    21, 37, 22,
    38, 23, 39,
    24, 40, 25,
    41, 26, 42,
    27, 43, 29,
    44, 31, 45,
    33, 46, 47,
    49, 48, 51,
    50, 53, 52
  }, // Veil Inner
  {
    54, 19, 55,
    20, 56, 21,
    57, 37, 58,
    38
  }, // Hair
  {
    55, 59, 56,
    60, 57, 61,
    58, 62, 38,
    63, 39, 64,
    39, 65, 40,
    66
  }, // Face
  {
    66, 40, 67,
    41
  }, // Chest


  //circulo perfecto 16
  {
    128, 129, 130, // 1
    128, 130, 131, // 2
    128, 131, 132, // 3
    128, 132, 133, // 4
    128, 133, 134, // 5
    128, 134, 135, // 6
    128, 135, 136, // 7
    128, 136, 137, // 8
    128, 137, 138, // 9
    128, 138, 139, // 10
    128, 139, 140, // 11
    128, 140, 141, // 12
    128, 141, 142, // 13
    128, 142, 143, // 14
    128, 143, 144, // 15
    128, 144, 145, // 16
    128, 145, 146, // 17
    128, 146, 147, // 18
    128, 147, 148, // 19
    128, 148, 149, // 20
    128, 149, 150, // 21
    128, 150, 151, // 22
    128, 151, 152, // 23
    128, 152, 153, // 24
    128, 153, 154, // 25
    128, 154, 155, // 26
    128, 155, 156, // 27
    128, 156, 157, // 28
    128, 157, 158, // 29
    128, 158, 159, // 30
    128, 159, 160, // 31
    128, 160, 161, // 32
    128, 161, 162, // 33
    128, 162, 163, // 34
    128, 163, 164, // 35
    128, 164, 165, // 36
    128, 165, 166, // 37
    128, 166, 167, // 38
    128, 167, 168, // 39
    128, 168, 169, // 40
    128, 169, 170, // 41
    128, 170, 171, // 42
    128, 171, 172, // 43
    128, 172, 173, // 44
    128, 173, 174, // 45
    128, 174, 175, // 46
    128, 175, 176, // 47
    128, 176, 177, // 48
    128, 177, 178, // 49
    128, 178, 179, // 50
    128, 179, 180, // 51
    128, 180, 181, // 52
    128, 181, 182, // 53
    128, 182, 183, // 54
    128, 183, 184, // 55
    128, 184, 185, // 56
    128, 185, 186, // 57
    128, 186, 187, // 58
    128, 187, 188, // 59
    128, 188, 189, // 60
    128, 189, 190, // 61
    128, 190, 191, // 62

    128, 191, 129, // 1
  },

  //mano  17
  {
    199, 200, 201,
    198, 199, 201,
    202, 198, 201,
    202, 197, 201,
    196, 197, 202,
    195, 196, 202,
    195, 194, 202,
    193, 194, 202,
    192, 193, 202,
    214, 192, 202,
    192, 214, 216,
    215, 214, 216,
    212, 214, 202,
    203, 212, 202,
    204, 212, 203,
    205, 212, 204,
    206, 212, 205,
    207, 212, 206,
    211, 207, 212,
    210, 207, 211,
    209, 210, 207,
    208, 209, 207, //22
  },
  //cabello 18

  {
    223, 222, 221,
    223, 221, 220,
    223, 220, 219,
    223, 219, 218,
    223, 218, 217,
    223, 217, 208,
    223, 208, 210,
  },
  //ropa 19

  {
    202, 192, 224, //10
    202, 224, 225,
    202, 225, 226,
    202, 226, 227,
    202, 227, 228,
    202, 228, 229,
    202, 229, 230,
    202, 230, 231,
    202, 231, 232,
    202, 232, 207,
  },
  {
    //20
    0, 1, 1, 2, 1, 3, 1, 16, 1, 4, 4, 5, 4, 7, 6, 7, 8, 7, 7, 10, 9, 10, 10, 11, 10, 13, 12, 13,
    13, 15, 13, 35, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 24, 24, 23, 23, 21,
    24, 26, 26, 27, 27, 28, 28, 29, 29, 7, 17, 25, 23, 25, 36, 38, 38, 37, 38, 39, 38, 31,
    39, 31, 40, 42, 41, 42, 42, 43, 42, 47, 46, 45, 42, 44, 57, 56, 56, 55, 55, 44, 44, 53,
    53, 52, 52, 51, 51, 48, 50, 51, 50, 49, 25, 49, 51, 54, 31, 32, 40, 32, 42, 32, 0, 59,
    0, 14, 14, 37, 37, 59, 1, 21, 4, 24,
  },//Lines

};

void drawWithEBO(int EBOindex, int vertexNumber,
                 GLenum primitive_type=GL_TRIANGLES) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[EBOindex]);
  glDrawElements(primitive_type, vertexNumber, GL_UNSIGNED_INT, 0);
}

void startVertexInput() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(N, EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  for (int i = 0; i < N; ++i) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(figures[i]), figures[i],
                 GL_STATIC_DRAW);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",
                                        NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // 1rojo, 2blue, 3lightblue, 4[blueish], 5gree, 6greenDarker, 7yellow, 8pink, 9purple

  unsigned int P01 = glCreateProgram();
  BuildShaders(P01, "shaders/default.vs", "shaders/red.fs");

  unsigned int P02 = glCreateProgram();
  BuildShaders(P02, "shaders/default.vs", "shaders/blue.fs");

  unsigned int P03 = glCreateProgram();
  BuildShaders(P03, "shaders/default.vs", "shaders/olive.fs");

  unsigned int P04 = glCreateProgram();
  BuildShaders(P04, "shaders/default.vs", "shaders/lilac.fs");

  unsigned int P05 = glCreateProgram();
  BuildShaders(P05, "shaders/default.vs", "shaders/orange.fs");

  unsigned int P06 = glCreateProgram();
  BuildShaders(P06, "shaders/default.vs", "shaders/lightblue.fs");

  unsigned int P07 = glCreateProgram();
  BuildShaders(P07, "shaders/default.vs", "shaders/yellow.fs");

  unsigned int P08 = glCreateProgram();
  BuildShaders(P08, "shaders/default.vs", "shaders/pink.fs");

  unsigned int P09 = glCreateProgram();
  BuildShaders(P09, "shaders/default.vs", "shaders/purple.fs");

  unsigned int defaultProgram = glCreateProgram();
  BuildShaders(defaultProgram, "shaders/default.vs", "shaders/beige.fs");

  unsigned int blueishProgram = glCreateProgram();
  BuildShaders(blueishProgram, "shaders/default.vs", "shaders/blueish.fs");

  unsigned int brownProgram = glCreateProgram();
  BuildShaders(brownProgram, "shaders/default.vs", "shaders/brown.fs");

  unsigned int skinProgram = glCreateProgram();
  BuildShaders(skinProgram, "shaders/default.vs", "shaders/skin.fs");

  unsigned int blackProgram = glCreateProgram();
  BuildShaders(blackProgram, "shaders/default.vs", "shaders/black.fs");

  for (int i = 9; i < 15; ++i) {
    for (int j = 0; j < MV; j++) figures[i][j] += 60;
  }

  startVertexInput();

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);

    // Fondo

    glUseProgram(P01);
    drawWithEBO(0, 24);

    glUseProgram(P02);
    drawWithEBO(1, MV);

    glUseProgram(P03);
    drawWithEBO(2, MV);

    glUseProgram(P04);
    drawWithEBO(3, MV);

    glUseProgram(P05);
    drawWithEBO(4, MV);

    glUseProgram(P06);
    drawWithEBO(5, MV);

    glUseProgram(P07);
    drawWithEBO(6, MV);

    glUseProgram(P08);
    drawWithEBO(7, MV);

    glUseProgram(P09);
    drawWithEBO(8, MV);

    // Lines
    glUseProgram(blackProgram);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(100);
    drawWithEBO(19, MV, GL_LINES);

    // Virgencita

    glUseProgram(defaultProgram);
    drawWithEBO(9, 19, GL_TRIANGLE_STRIP);
    drawWithEBO(11, 27, GL_TRIANGLE_STRIP);
    drawWithEBO(14, 4, GL_TRIANGLE_STRIP);

    glUseProgram(blueishProgram);
    drawWithEBO(10, 26, GL_TRIANGLE_STRIP);

    glUseProgram(brownProgram);
    drawWithEBO(12, 10, GL_TRIANGLE_STRIP);

    glUseProgram(skinProgram);
    drawWithEBO(13, 16, GL_TRIANGLE_STRIP);


    // BEBE
    //ropa
    glUseProgram(blueishProgram);
    drawWithEBO(18, 30);

    //redondo
    glUseProgram(P07);
    drawWithEBO(15, 3 * 63);


    //cabello
    glUseProgram(brownProgram);
    drawWithEBO(17, 21);

    //mano
    glUseProgram(skinProgram);
    drawWithEBO(16, 22 * 3);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(N, EBO);
  glDeleteProgram(P01);
  glDeleteProgram(P02);
  glDeleteProgram(P03);
  glDeleteProgram(P04);
  glDeleteProgram(P05);
  glDeleteProgram(P06);
  glDeleteProgram(P07);
  glDeleteProgram(P08);
  glDeleteProgram(P09);
  glDeleteProgram(defaultProgram);
  glDeleteProgram(blueishProgram);
  glDeleteProgram(brownProgram);
  glDeleteProgram(skinProgram);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
