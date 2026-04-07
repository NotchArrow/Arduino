/*************************************************

 * Public Constants

 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

const int PITCHES[] = {
  // 0          1         2        3         4        5          6          7        8        9          10         11       12
  NOTE_B0,  NOTE_C1,  NOTE_CS1, NOTE_D1,  NOTE_DS1, NOTE_E1,  NOTE_F1,  NOTE_FS1, NOTE_G1,  NOTE_GS1, NOTE_A1,  NOTE_AS1, NOTE_B1,
  // 13         14        15       16        17       18         19         20       21       22         23         24
  NOTE_C2,  NOTE_CS2, NOTE_D2,  NOTE_DS2, NOTE_E2,  NOTE_F2,  NOTE_FS2, NOTE_G2,  NOTE_GS2, NOTE_A2,  NOTE_AS2, NOTE_B2,
  // 25         26        27       28        29       30         31         32       33       34         35         36
  NOTE_C3,  NOTE_CS3, NOTE_D3,  NOTE_DS3, NOTE_E3,  NOTE_F3,  NOTE_FS3, NOTE_G3,  NOTE_GS3, NOTE_A3,  NOTE_AS3, NOTE_B3,
  // 37         38        39       40        41       42         43         44       45       46         47         48
  NOTE_C4,  NOTE_CS4, NOTE_D4,  NOTE_DS4, NOTE_E4,  NOTE_F4,  NOTE_FS4, NOTE_G4,  NOTE_GS4, NOTE_A4,  NOTE_AS4, NOTE_B4,
  // 49         50        51       52        53       54         55         56       57       58         59         60
  NOTE_C5,  NOTE_CS5, NOTE_D5,  NOTE_DS5, NOTE_E5,  NOTE_F5,  NOTE_FS5, NOTE_G5,  NOTE_GS5, NOTE_A5,  NOTE_AS5, NOTE_B5,
  // 61         62        63       64        65       66         67         68       69       70         71         72
  NOTE_C6,  NOTE_CS6, NOTE_D6,  NOTE_DS6, NOTE_E6,  NOTE_F6,  NOTE_FS6, NOTE_G6,  NOTE_GS6, NOTE_A6,  NOTE_AS6, NOTE_B6,
  // 73         74        75       76        77       78         79         80       81       82         83         84
  NOTE_C7,  NOTE_CS7, NOTE_D7,  NOTE_DS7, NOTE_E7,  NOTE_F7,  NOTE_FS7, NOTE_G7,  NOTE_GS7, NOTE_A7,  NOTE_AS7, NOTE_B7,
  // 85         86        87       88
  NOTE_C8,  NOTE_CS8, NOTE_D8,  NOTE_DS8
};

const String PITCH_NAMES[] = {
  "B0",  "C1",  "C#1", "D1",  "D#1", "E1",  "F1",  "F#1", "G1",  "G#1", "A1",  "A#1", "B1",
  "C2",  "C#2", "D2",  "D#2", "E2",  "F2",  "F#2", "G2",  "G#2", "A2",  "A#2", "B2",
  "C3",  "C#3", "D3",  "D#3", "E3",  "F3",  "F#3", "G3",  "G#3", "A3",  "A#3", "B3",
  "C4",  "C#4", "D4",  "D#4", "E4",  "F4",  "F#4", "G4",  "G#4", "A4",  "A#4", "B4",
  "C5",  "C#5", "D5",  "D#5", "E5",  "F5",  "F#5", "G5",  "G#5", "A5",  "A#5", "B5",
  "C6",  "C#6", "D6",  "D#6", "E6",  "F6",  "F#6", "G6",  "G#6", "A6",  "A#6", "B6",
  "C7",  "C#7", "D7",  "D#7", "E7",  "F7",  "F#7", "G7",  "G#7", "A7",  "A#7", "B7",
  "C8",  "C#8", "D8",  "D#8"
};