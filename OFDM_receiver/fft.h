#ifndef FFT_H_
#define FFT_H_

typedef float DTYPE;
#include <stdint.h>

typedef int INTTYPE;

#define M 10 			/*Number of Stages = Log2N */
const int SIZE = 1024 ;		/* SIZE OF FFT */
#define SIZE2 SIZE>>1
#define FFT_BITS 10 // Number of bits of FFT, i.e., log(1024)

//W_real and W_image are twiddle factors for 1024 size FFT.
//WW_R[i]=cos(e*i/SIZE);
//WW_I[i]=sin(e*i/SIZE);
//where i=[0,512) and DTYPE	e = -6.283185307178;
const DTYPE W_real[]={1.000000, 0.999981,0.999925,0.999831,0.999699,0.999529,0.999322,0.999078,0.998795,0.998476,0.998118,0.997723,0.997290,0.996820,0.996313,0.995767,0.995185,

0.994565,0.993907,0.993212,0.992480,0.991710,0.990903,0.990058,0.989177,0.988258,0.987301,0.986308,0.985278,0.984210,0.983105,0.981964,0.980785,

0.979570,0.978317,0.977028,0.975702,0.974339,0.972940,0.971504,0.970031,0.968522,0.966976,0.965394,0.963776,0.962121,0.960431,0.958703,0.956940,

0.955141,0.953306,0.951435,0.949528,0.947586,0.945607,0.943593,0.941544,0.939459,0.937339,0.935184,0.932993,0.930767,0.928506,0.926210,0.923880,

0.921514,0.919114,0.916679,0.914210,0.911706,0.909168,0.906596,0.903989,0.901349,0.898674,0.895966,0.893224,0.890449,0.887640,0.884797,0.881921,

0.879012,0.876070,0.873095,0.870087,0.867046,0.863973,0.860867,0.857729,0.854558,0.851355,0.848120,0.844854,0.841555,0.838225,0.834863,0.831470,

0.828045,0.824589,0.821102,0.817585,0.814036,0.810457,0.806848,0.803208,0.799537,0.795837,0.792107,0.788346,0.784557,0.780737,0.776888,0.773010,

0.769103,0.765167,0.761202,0.757209,0.753187,0.749136,0.745058,0.740951,0.736817,0.732654,0.728464,0.724247,0.720002,0.715731,0.711432,0.707107,

0.702755,0.698376,0.693971,0.689541,0.685084,0.680601,0.676093,0.671559,0.667000,0.662416,0.657807,0.653173,0.648514,0.643832,0.639124,0.634393,

0.629638,0.624859,0.620057,0.615232,0.610383,0.605511,0.600616,0.595699,0.590760,0.585798,0.580814,0.575808,0.570781,0.565732,0.560662,0.555570,

0.550458,0.545325,0.540171,0.534998,0.529804,0.524590,0.519356,0.514103,0.508830,0.503538,0.498228,0.492898,0.487550,0.482184,0.476799,0.471397,

0.465976,0.460539,0.455084,0.449611,0.444122,0.438616,0.433094,0.427555,0.422000,0.416430,0.410843,0.405241,0.399624,0.393992,0.388345,0.382683,

0.377007,0.371317,0.365613,0.359895,0.354163,0.348419,0.342661,0.336890,0.331106,0.325310,0.319502,0.313682,0.307850,0.302006,0.296151,0.290285,

0.284407,0.278520,0.272621,0.266713,0.260794,0.254866,0.248928,0.242980,0.237024,0.231058,0.225084,0.219101,0.213110,0.207111,0.201105,0.195090,

0.189069,0.183040,0.177004,0.170962,0.164913,0.158858,0.152797,0.146730,0.140658,0.134581,0.128498,0.122411,0.116319,0.110222,0.104122,0.098017,

0.091909,0.085797,0.079682,0.073565,0.067444,0.061321,0.055195,0.049068,0.042938,0.036807,0.030675,0.024541,0.018407,0.012271,0.006136,-0.000000,

-0.006136,-0.012272,-0.018407,-0.024541,-0.030675,-0.036807,-0.042938,-0.049068,-0.055195,-0.061321,-0.067444,-0.073565,-0.079682,-0.085797,-0.091909,-0.098017,

-0.104122,-0.110222,-0.116319,-0.122411,-0.128498,-0.134581,-0.140658,-0.146731,-0.152797,-0.158858,-0.164913,-0.170962,-0.177004,-0.183040,-0.189069,-0.195090,

-0.201105,-0.207111,-0.213110,-0.219101,-0.225084,-0.231058,-0.237024,-0.242980,-0.248928,-0.254866,-0.260794,-0.266713,-0.272621,-0.278520,-0.284408,-0.290285,

-0.296151,-0.302006,-0.307850,-0.313682,-0.319502,-0.325310,-0.331106,-0.336890,-0.342661,-0.348419,-0.354164,-0.359895,-0.365613,-0.371317,-0.377007,-0.382683,

-0.388345,-0.393992,-0.399624,-0.405241,-0.410843,-0.416430,-0.422000,-0.427555,-0.433094,-0.438616,-0.444122,-0.449611,-0.455084,-0.460539,-0.465977,-0.471397,

-0.476799,-0.482184,-0.487550,-0.492898,-0.498228,-0.503538,-0.508830,-0.514103,-0.519356,-0.524590,-0.529804,-0.534998,-0.540172,-0.545325,-0.550458,-0.555570,

-0.560662,-0.565732,-0.570781,-0.575808,-0.580814,-0.585798,-0.590760,-0.595699,-0.600617,-0.605511,-0.610383,-0.615232,-0.620057,-0.624860,-0.629638,-0.634393,

-0.639125,-0.643832,-0.648514,-0.653173,-0.657807,-0.662416,-0.667000,-0.671559,-0.676093,-0.680601,-0.685084,-0.689541,-0.693972,-0.698376,-0.702755,-0.707107,

-0.711432,-0.715731,-0.720003,-0.724247,-0.728464,-0.732654,-0.736817,-0.740951,-0.745058,-0.749136,-0.753187,-0.757209,-0.761202,-0.765167,-0.769103,-0.773010,

-0.776888,-0.780737,-0.784557,-0.788346,-0.792107,-0.795837,-0.799537,-0.803208,-0.806848,-0.810457,-0.814036,-0.817585,-0.821103,-0.824589,-0.828045,-0.831470,

-0.834863,-0.838225,-0.841555,-0.844854,-0.848120,-0.851355,-0.854558,-0.857729,-0.860867,-0.863973,-0.867046,-0.870087,-0.873095,-0.876070,-0.879012,-0.881921,

-0.884797,-0.887640,-0.890449,-0.893224,-0.895966,-0.898674,-0.901349,-0.903989,-0.906596,-0.909168,-0.911706,-0.914210,-0.916679,-0.919114,-0.921514,-0.923880,

-0.926210,-0.928506,-0.930767,-0.932993,-0.935184,-0.937339,-0.939459,-0.941544,-0.943594,-0.945607,-0.947586,-0.949528,-0.951435,-0.953306,-0.955141,-0.956940,

-0.958704,-0.960431,-0.962121,-0.963776,-0.965394,-0.966976,-0.968522,-0.970031,-0.971504,-0.972940,-0.974339,-0.975702,-0.977028,-0.978317,-0.979570,-0.980785,

-0.981964,-0.983105,-0.984210,-0.985278,-0.986308,-0.987301,-0.988258,-0.989177,-0.990058,-0.990903,-0.991710,-0.992480,-0.993212,-0.993907,-0.994565,-0.995185,

-0.995767,-0.996313,-0.996820,-0.997290,-0.997723,-0.998118,-0.998476,-0.998795,-0.999078,-0.999322,-0.999529,-0.999699,-0.999831,-0.999925,-0.999981};
const DTYPE W_imag[]={-0.000000,-0.006136,-0.012272,-0.018407,-0.024541,-0.030675,-0.036807,-0.042938,-0.049068,-0.055195,-0.061321,-0.067444,-0.073565,-0.079682,-0.085797,-0.091909,-0.098017,-0.104122,-0.110222,-0.116319,-0.122411,-0.128498,-0.134581,-0.140658,-0.146730,-0.152797,-0.158858,-0.164913,-0.170962,-0.177004,-0.183040,-0.189069,-0.195090,-0.201105,-0.207111,-0.213110,-0.219101,-0.225084,-0.231058,-0.237024,-0.242980,-0.248928,-0.254866,-0.260794,-0.266713,-0.272621,-0.278520,-0.284408,-0.290285,-0.296151,-0.302006,-0.307850,-0.313682,-0.319502,-0.325310,-0.331106,-0.336890,-0.342661,-0.348419,-0.354164,-0.359895,-0.365613,-0.371317,-0.377007,-0.382683,-0.388345,-0.393992,-0.399624,-0.405241,-0.410843,-0.416430,-0.422000,-0.427555,-0.433094,-0.438616,-0.444122,-0.449611,-0.455084,-0.460539,-0.465977,-0.471397,-0.476799,-0.482184,-0.487550,-0.492898,-0.498228,-0.503538,-0.508830,-0.514103,-0.519356,-0.524590,-0.529804,-0.534998,-0.540172,-0.545325,-0.550458,-0.555570,-0.560662,-0.565732,-0.570781,-0.575808,-0.580814,-0.585798,-0.590760,-0.595699,-0.600617,-0.605511,-0.610383,-0.615232,-0.620057,-0.624860,-0.629638,-0.634393,-0.639124,-0.643832,-0.648514,-0.653173,-0.657807,-0.662416,-0.667000,-0.671559,-0.676093,-0.680601,-0.685084,-0.689541,-0.693971,-0.698376,-0.702755,-0.707107,-0.711432,-0.715731,-0.720003,-0.724247,-0.728464,-0.732654,-0.736817,-0.740951,-0.745058,-0.749136,-0.753187,-0.757209,-0.761202,-0.765167,-0.769103,-0.773010,-0.776888,-0.780737,-0.784557,-0.788346,-0.792107,-0.795837,-0.799537,-0.803208,-0.806848,-0.810457,-0.814036,-0.817585,-0.821103,-0.824589,-0.828045,-0.831470,-0.834863,-0.838225,-0.841555,-0.844854,-0.848120,-0.851355,-0.854558,-0.857729,-0.860867,-0.863973,-0.867046,-0.870087,-0.873095,-0.876070,-0.879012,-0.881921,-0.884797,-0.887640,-0.890449,-0.893224,-0.895966,-0.898674,-0.901349,-0.903989,-0.906596,-0.909168,-0.911706,-0.914210,-0.916679,-0.919114,-0.921514,-0.923880,-0.926210,-0.928506,-0.930767,-0.932993,-0.935184,-0.937339,-0.939459,-0.941544,-0.943593,-0.945607,-0.947586,-0.949528,-0.951435,-0.953306,-0.955141,-0.956940,-0.958703,-0.960431,-0.962121,-0.963776,-0.965394,-0.966976,-0.968522,-0.970031,-0.971504,-0.972940,-0.974339,-0.975702,-0.977028,-0.978317,-0.979570,-0.980785,-0.981964,-0.983105,-0.984210,-0.985278,-0.986308,-0.987301,-0.988258,-0.989177,-0.990058,-0.990903,-0.991710,-0.992480,-0.993212,-0.993907,-0.994565,-0.995185,-0.995767,-0.996313,-0.996820,-0.997290,-0.997723,-0.998118,-0.998476,-0.998795,-0.999078,-0.999322,-0.999529,-0.999699,-0.999831,-0.999925,-0.999981,-1.000000,-0.999981,-0.999925,-0.999831,-0.999699,-0.999529,-0.999322,-0.999078,-0.998795,-0.998476,-0.998118,-0.997723,-0.997290,-0.996820,-0.996313,-0.995767,-0.995185,-0.994565,-0.993907,-0.993212,-0.992480,-0.991710,-0.990903,-0.990058,-0.989177,-0.988258,-0.987301,-0.986308,-0.985278,-0.984210,-0.983105,-0.981964,-0.980785,-0.979570,-0.978317,-0.977028,-0.975702,-0.974339,-0.972940,-0.971504,-0.970031,-0.968522,-0.966976,-0.965394,-0.963776,-0.962121,-0.960431,-0.958703,-0.956940,-0.955141,-0.953306,-0.951435,-0.949528,-0.947586,-0.945607,-0.943593,-0.941544,-0.939459,-0.937339,-0.935183,-0.932993,-0.930767,-0.928506,-0.926210,-0.923880,-0.921514,-0.919114,-0.916679,-0.914210,-0.911706,-0.909168,-0.906596,-0.903989,-0.901349,-0.898674,-0.895966,-0.893224,-0.890449,-0.887640,-0.884797,-0.881921,-0.879012,-0.876070,-0.873095,-0.870087,-0.867046,-0.863973,-0.860867,-0.857729,-0.854558,-0.851355,-0.848120,-0.844854,-0.841555,-0.838225,-0.834863,-0.831470,-0.828045,-0.824589,-0.821102,-0.817585,-0.814036,-0.810457,-0.806848,-0.803208,-0.799537,-0.795837,-0.792107,-0.788346,-0.784557,-0.780737,-0.776888,-0.773010,-0.769103,-0.765167,-0.761202,-0.757209,-0.753187,-0.749136,-0.745058,-0.740951,-0.736817,-0.732654,-0.728464,-0.724247,-0.720002,-0.715731,-0.711432,-0.707107,-0.702755,-0.698376,-0.693971,-0.689541,-0.685084,-0.680601,-0.676093,-0.671559,-0.667000,-0.662416,-0.657807,-0.653173,-0.648514,-0.643831,-0.639124,-0.634393,-0.629638,-0.624859,-0.620057,-0.615232,-0.610383,-0.605511,-0.600616,-0.595699,-0.590760,-0.585798,-0.580814,-0.575808,-0.570781,-0.565732,-0.560661,-0.555570,-0.550458,-0.545325,-0.540171,-0.534998,-0.529804,-0.524590,-0.519356,-0.514103,-0.508830,-0.503538,-0.498228,-0.492898,-0.487550,-0.482184,-0.476799,-0.471397,-0.465976,-0.460539,-0.455084,-0.449611,-0.444122,-0.438616,-0.433094,-0.427555,-0.422000,-0.416429,-0.410843,-0.405241,-0.399624,-0.393992,-0.388345,-0.382683,-0.377007,-0.371317,-0.365613,-0.359895,-0.354163,-0.348419,-0.342661,-0.336890,-0.331106,-0.325310,-0.319502,-0.313682,-0.307850,-0.302006,-0.296151,-0.290285,-0.284407,-0.278520,-0.272621,-0.266713,-0.260794,-0.254866,-0.248928,-0.242980,-0.237024,-0.231058,-0.225084,-0.219101,-0.213110,-0.207111,-0.201105,-0.195090,-0.189069,-0.183040,-0.177004,-0.170962,-0.164913,-0.158858,-0.152797,-0.146730,-0.140658,-0.134581,-0.128498,-0.122411,-0.116319,-0.110222,-0.104122,-0.098017,-0.091909,-0.085797,-0.079682,-0.073564,-0.067444,-0.061321,-0.055195,-0.049068,-0.042938,-0.036807,-0.030675,-0.024541,-0.018407,-0.012271,-0.006136};


//LUT MAP for bit reversal
const int LUT_MAP[] = {0, 512, 256, 768, 128, 640, 384, 896, 64, 576, 320, 832, 192, 704, 448, 960, 32, 544, 288, 800, 160, 672, 416, 928, 96, 608, 352, 864, 224, 736, 480, 992, 16, 528, 272, 784, 144, 656, 400, 912, 80, 592, 336, 848, 208, 720, 464, 976, 48, 560, 304, 816, 176, 688, 432, 944, 112, 624, 368, 880, 240, 752, 496, 1008, 8, 520, 264, 776, 136, 648, 392, 904, 72, 584, 328, 840, 200, 712, 456, 968, 40, 552, 296, 808, 168, 680, 424, 936, 104, 616, 360, 872, 232, 744, 488, 1000, 24, 536, 280, 792, 152, 664, 408, 920, 88, 600, 344, 856, 216, 728, 472, 984, 56, 568, 312, 824, 184, 696, 440, 952, 120, 632, 376, 888, 248, 760, 504, 1016, 4, 516, 260, 772, 132, 644, 388, 900, 68, 580, 324, 836, 196, 708, 452, 964, 36, 548, 292, 804, 164, 676, 420, 932, 100, 612, 356, 868, 228, 740, 484, 996, 20, 532, 276, 788, 148, 660, 404, 916, 84, 596, 340, 852, 212, 724, 468, 980, 52, 564, 308, 820, 180, 692, 436, 948, 116, 628, 372, 884, 244, 756, 500, 1012, 12, 524, 268, 780, 140, 652, 396, 908, 76, 588, 332, 844, 204, 716, 460, 972, 44, 556, 300, 812, 172, 684, 428, 940, 108, 620, 364, 876, 236, 748, 492, 1004, 28, 540, 284, 796, 156, 668, 412, 924, 92, 604, 348, 860, 220, 732, 476, 988, 60, 572, 316, 828, 188, 700, 444, 956, 124, 636, 380, 892, 252, 764, 508, 1020, 2, 514, 258, 770, 130, 642, 386, 898, 66, 578, 322, 834, 194, 706, 450, 962, 34, 546, 290, 802, 162, 674, 418, 930, 98, 610, 354, 866, 226, 738, 482, 994, 18, 530, 274, 786, 146, 658, 402, 914, 82, 594, 338, 850, 210, 722, 466, 978, 50, 562, 306, 818, 178, 690, 434, 946, 114, 626, 370, 882, 242, 754, 498, 1010, 10, 522, 266, 778, 138, 650, 394, 906, 74, 586, 330, 842, 202, 714, 458, 970, 42, 554, 298, 810, 170, 682, 426, 938, 106, 618, 362, 874, 234, 746, 490, 1002, 26, 538, 282, 794, 154, 666, 410, 922, 90, 602, 346, 858, 218, 730, 474, 986, 58, 570, 314, 826, 186, 698, 442, 954, 122, 634, 378, 890, 250, 762, 506, 1018, 6, 518, 262, 774, 134, 646, 390, 902, 70, 582, 326, 838, 198, 710, 454, 966, 38, 550, 294, 806, 166, 678, 422, 934, 102, 614, 358, 870, 230, 742, 486, 998, 22, 534, 278, 790, 150, 662, 406, 918, 86, 598, 342, 854, 214, 726, 470, 982, 54, 566, 310, 822, 182, 694, 438, 950, 118, 630, 374, 886, 246, 758, 502, 1014, 14, 526, 270, 782, 142, 654, 398, 910, 78, 590, 334, 846, 206, 718, 462, 974, 46, 558, 302, 814, 174, 686, 430, 942, 110, 622, 366, 878, 238, 750, 494, 1006, 30, 542, 286, 798, 158, 670, 414, 926, 94, 606, 350, 862, 222, 734, 478, 990, 62, 574, 318, 830, 190, 702, 446, 958, 126, 638, 382, 894, 254, 766, 510, 1022, 1, 513, 257, 769, 129, 641, 385, 897, 65, 577, 321, 833, 193, 705, 449, 961, 33, 545, 289, 801, 161, 673, 417, 929, 97, 609, 353, 865, 225, 737, 481, 993, 17, 529, 273, 785, 145, 657, 401, 913, 81, 593, 337, 849, 209, 721, 465, 977, 49, 561, 305, 817, 177, 689, 433, 945, 113, 625, 369, 881, 241, 753, 497, 1009, 9, 521, 265, 777, 137, 649, 393, 905, 73, 585, 329, 841, 201, 713, 457, 969, 41, 553, 297, 809, 169, 681, 425, 937, 105, 617, 361, 873, 233, 745, 489, 1001, 25, 537, 281, 793, 153, 665, 409, 921, 89, 601, 345, 857, 217, 729, 473, 985, 57, 569, 313, 825, 185, 697, 441, 953, 121, 633, 377, 889, 249, 761, 505, 1017, 5, 517, 261, 773, 133, 645, 389, 901, 69, 581, 325, 837, 197, 709, 453, 965, 37, 549, 293, 805, 165, 677, 421, 933, 101, 613, 357, 869, 229, 741, 485, 997, 21, 533, 277, 789, 149, 661, 405, 917, 85, 597, 341, 853, 213, 725, 469, 981, 53, 565, 309, 821, 181, 693, 437, 949, 117, 629, 373, 885, 245, 757, 501, 1013, 13, 525, 269, 781, 141, 653, 397, 909, 77, 589, 333, 845, 205, 717, 461, 973, 45, 557, 301, 813, 173, 685, 429, 941, 109, 621, 365, 877, 237, 749, 493, 1005, 29, 541, 285, 797, 157, 669, 413, 925, 93, 605, 349, 861, 221, 733, 477, 989, 61, 573, 317, 829, 189, 701, 445, 957, 125, 637, 381, 893, 253, 765, 509, 1021, 3, 515, 259, 771, 131, 643, 387, 899, 67, 579, 323, 835, 195, 707, 451, 963, 35, 547, 291, 803, 163, 675, 419, 931, 99, 611, 355, 867, 227, 739, 483, 995, 19, 531, 275, 787, 147, 659, 403, 915, 83, 595, 339, 851, 211, 723, 467, 979, 51, 563, 307, 819, 179, 691, 435, 947, 115, 627, 371, 883, 243, 755, 499, 1011, 11, 523, 267, 779, 139, 651, 395, 907, 75, 587, 331, 843, 203, 715, 459, 971, 43, 555, 299, 811, 171, 683, 427, 939, 107, 619, 363, 875, 235, 747, 491, 1003, 27, 539, 283, 795, 155, 667, 411, 923, 91, 603, 347, 859, 219, 731, 475, 987, 59, 571, 315, 827, 187, 699, 443, 955, 123, 635, 379, 891, 251, 763, 507, 1019, 7, 519, 263, 775, 135, 647, 391, 903, 71, 583, 327, 839, 199, 711, 455, 967, 39, 551, 295, 807, 167, 679, 423, 935, 103, 615, 359, 871, 231, 743, 487, 999, 23, 535, 279, 791, 151, 663, 407, 919, 87, 599, 343, 855, 215, 727, 471, 983, 55, 567, 311, 823, 183, 695, 439, 951, 119, 631, 375, 887, 247, 759, 503, 1015, 15, 527, 271, 783, 143, 655, 399, 911, 79, 591, 335, 847, 207, 719, 463, 975, 47, 559, 303, 815, 175, 687, 431, 943, 111, 623, 367, 879, 239, 751, 495, 1007, 31, 543, 287, 799, 159, 671, 415, 927, 95, 607, 351, 863, 223, 735, 479, 991, 63, 575, 319, 831, 191, 703, 447, 959, 127, 639, 383, 895, 255, 767, 511, 1023};


void fft(DTYPE XX_R[SIZE], DTYPE XX_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);

void demod(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int D[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);

void ofdm_receiver( volatile DTYPE *inptr, volatile uint32_t *outptr );

#endif
