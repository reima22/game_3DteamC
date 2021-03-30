xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 211;
 -3.84790;4.25217;5.68148;,
 -7.21407;0.81537;6.89804;,
 -4.02271;-2.52095;5.89052;,
 -0.33343;1.17417;4.94964;,
 -7.94182;-0.36215;-2.13060;,
 -5.39126;-3.22223;-1.01988;,
 -9.00567;-4.13783;-1.11756;,
 -10.27383;-2.05087;-1.31756;,
 -10.33662;-1.15503;5.90276;,
 -7.85398;-4.53279;5.59268;,
 -3.96062;-3.22687;-3.67172;,
 -6.12406;-1.14071;-4.72156;,
 -2.91350;3.41825;-3.25700;,
 -0.16687;0.54233;-1.60300;,
 -11.31831;-0.93047;4.08308;,
 -8.10351;-4.90735;3.90988;,
 -11.83310;-0.38943;2.58964;,
 -8.77119;-4.45631;2.29100;,
 -9.19030;1.73945;3.68012;,
 -9.75686;1.73945;1.80748;,
 -4.72838;-2.79447;3.81788;,
 -5.02190;-2.86503;2.17204;,
 -0.23015;0.67129;1.69372;,
 -2.79903;3.14385;1.37716;,
 -11.23463;-1.33943;0.58668;,
 -9.10191;-4.25255;0.56372;,
 -9.00686;1.32073;-1.07012;,
 -5.23214;-3.04047;0.52620;,
 -5.01326;5.32369;3.44780;,
 -5.19143;5.59105;1.10284;,
 -4.81679;5.28121;-1.89916;,
 -7.17246;-2.46615;-4.25764;,
 -4.81831;-4.25487;-4.72204;,
 -8.14478;-7.04543;-6.49796;,
 -9.97998;-5.51239;-6.19124;,
 -9.97998;-5.51239;-6.19124;,
 -8.14478;-7.04543;-6.49796;,
 -8.44198;-7.54727;-4.74820;,
 -10.25310;-6.07358;-4.45084;,
 -10.25310;-6.07358;-4.45084;,
 -8.44198;-7.54727;-4.74820;,
 -4.93239;-4.64479;-2.46596;,
 -7.29254;-3.21095;-2.13812;,
 -7.29254;-3.21095;-2.13812;,
 -4.93239;-4.64479;-2.46596;,
 -4.81831;-4.25487;-4.72204;,
 -7.17246;-2.46615;-4.25764;,
 -7.17246;-2.46615;-4.25764;,
 -9.97998;-5.51239;-6.19124;,
 -4.81831;-4.25487;-4.72204;,
 -8.14478;-7.04543;-6.49796;,
 -9.83103;-0.95167;-1.62148;,
 -8.18695;-3.64479;-1.56332;,
 -11.14007;-5.52919;-1.20060;,
 -12.23807;-3.78063;-1.39196;,
 -12.23807;-3.78063;-1.39196;,
 -11.14007;-5.52919;-1.20060;,
 -11.02423;-5.61487;0.45548;,
 -12.21415;-3.83679;0.63572;,
 -12.21415;-3.83679;0.63572;,
 -11.02423;-5.61487;0.45548;,
 -8.02854;-3.81431;0.54964;,
 -9.90863;-1.26135;0.55788;,
 -9.90863;-1.26135;0.55788;,
 -8.02854;-3.81431;0.54964;,
 -8.18695;-3.64479;-1.56332;,
 -9.83103;-0.95167;-1.62148;,
 -9.83103;-0.95167;-1.62148;,
 -12.23807;-3.78063;-1.39196;,
 -8.18695;-3.64479;-1.56332;,
 -11.14007;-5.52919;-1.20060;,
 -10.45004;-8.92582;-1.20988;,
 -10.12248;-6.90007;-1.01428;,
 -6.50238;-7.45136;-0.85972;,
 -6.45955;-8.96917;-0.95012;,
 -6.45955;-8.96917;-0.95012;,
 -6.50238;-7.45136;-0.85972;,
 -6.74574;-7.37543;0.56276;,
 -6.87391;-8.87275;0.49676;,
 -6.87391;-8.87275;0.49676;,
 -6.74574;-7.37543;0.56276;,
 -10.15199;-6.81499;0.59548;,
 -10.49780;-8.96205;0.47132;,
 -10.49780;-8.96205;0.47132;,
 -10.15199;-6.81499;0.59548;,
 -10.12248;-6.90007;-1.01428;,
 -10.45004;-8.92582;-1.20988;,
 -10.45004;-8.92582;-1.20988;,
 -6.45955;-8.96917;-0.95012;,
 -10.12248;-6.90007;-1.01428;,
 -6.50238;-7.45136;-0.85972;,
 -9.75094;-1.72655;0.72828;,
 -8.22238;-3.98279;0.40420;,
 -11.26111;-5.99927;0.54308;,
 -12.54559;-4.01199;0.75436;,
 -12.54559;-4.01199;0.75436;,
 -11.26111;-5.99927;0.54308;,
 -11.26814;-5.96727;2.26020;,
 -12.37807;-4.19431;2.54300;,
 -12.37807;-4.19431;2.54300;,
 -11.26814;-5.96727;2.26020;,
 -8.08086;-4.01151;2.18684;,
 -9.77511;-1.68671;2.47612;,
 -9.77511;-1.68671;2.47612;,
 -8.08086;-4.01151;2.18684;,
 -8.22238;-3.98279;0.40420;,
 -9.75094;-1.72655;0.72828;,
 -9.75094;-1.72655;0.72828;,
 -12.54559;-4.01199;0.75436;,
 -8.22238;-3.98279;0.40420;,
 -11.26111;-5.99927;0.54308;,
 -9.88941;-8.81226;0.80380;,
 -9.64983;-6.86460;0.76356;,
 -6.19633;-7.71669;0.80132;,
 -6.50231;-9.23387;0.93380;,
 -6.50231;-9.23387;0.93380;,
 -6.19633;-7.71669;0.80132;,
 -6.18949;-7.55037;2.55796;,
 -6.52160;-9.17856;2.75716;,
 -6.52160;-9.17856;2.75716;,
 -6.18949;-7.55037;2.55796;,
 -9.64097;-6.61841;2.41340;,
 -9.97692;-8.92805;2.59468;,
 -9.97692;-8.92805;2.59468;,
 -9.64097;-6.61841;2.41340;,
 -9.64983;-6.86460;0.76356;,
 -9.88941;-8.81226;0.80380;,
 -9.88941;-8.81226;0.80380;,
 -6.50231;-9.23387;0.93380;,
 -9.64983;-6.86460;0.76356;,
 -6.19633;-7.71669;0.80132;,
 -9.71151;-2.08279;2.55076;,
 -8.12686;-4.12743;2.27268;,
 -10.91399;-5.84799;2.54308;,
 -11.90863;-4.08830;2.65396;,
 -11.90863;-4.08830;2.65396;,
 -10.91399;-5.84799;2.54308;,
 -10.71438;-5.99150;4.10940;,
 -11.66335;-4.32119;4.24484;,
 -11.66335;-4.32119;4.24484;,
 -10.71438;-5.99150;4.10940;,
 -7.81582;-4.40847;4.07916;,
 -9.40655;-2.20327;4.29828;,
 -9.40655;-2.20327;4.29828;,
 -7.81582;-4.40847;4.07916;,
 -8.12686;-4.12743;2.27268;,
 -9.71151;-2.08279;2.55076;,
 -9.71151;-2.08279;2.55076;,
 -11.90863;-4.08830;2.65396;,
 -8.12686;-4.12743;2.27268;,
 -10.91399;-5.84799;2.54308;,
 -10.70285;-8.75810;2.70812;,
 -10.32680;-6.30087;2.46180;,
 -6.70651;-6.88765;2.63332;,
 -7.23060;-8.87025;2.83748;,
 -7.23060;-8.87025;2.83748;,
 -6.70651;-6.88765;2.63332;,
 -6.95216;-6.94642;4.12540;,
 -7.45927;-8.75735;4.40524;,
 -7.45927;-8.75735;4.40524;,
 -6.95216;-6.94642;4.12540;,
 -10.35700;-5.96786;4.13884;,
 -10.67000;-8.40511;4.38764;,
 -10.67000;-8.40511;4.38764;,
 -10.35700;-5.96786;4.13884;,
 -10.32680;-6.30087;2.46180;,
 -10.70285;-8.75810;2.70812;,
 -10.70285;-8.75810;2.70812;,
 -7.23060;-8.87025;2.83748;,
 -10.32680;-6.30087;2.46180;,
 -6.70651;-6.88765;2.63332;,
 -8.83103;-2.76631;4.38220;,
 -7.58055;-4.00239;4.13692;,
 -9.34287;-5.35399;4.32252;,
 -10.08199;-4.08743;4.42340;,
 -10.08199;-4.08743;4.42340;,
 -9.34287;-5.35399;4.32252;,
 -9.18830;-5.70622;5.66196;,
 -9.92638;-4.40895;5.78900;,
 -9.92638;-4.40895;5.78900;,
 -9.18830;-5.70622;5.66196;,
 -7.22638;-4.09407;5.80796;,
 -8.26079;-2.95839;5.91100;,
 -8.26079;-2.95839;5.91100;,
 -7.22638;-4.09407;5.80796;,
 -7.58055;-4.00239;4.13692;,
 -8.83103;-2.76631;4.38220;,
 -8.83103;-2.76631;4.38220;,
 -10.08199;-4.08743;4.42340;,
 -7.58055;-4.00239;4.13692;,
 -9.34287;-5.35399;4.32252;,
 -12.08251;-7.36561;4.54148;,
 -11.91779;-5.79368;4.33340;,
 -9.34981;-6.23340;4.53644;,
 -9.42372;-7.60594;4.51052;,
 -9.42372;-7.60594;4.51052;,
 -9.34981;-6.23340;4.53644;,
 -9.46953;-5.91847;5.93652;,
 -9.38266;-7.11483;5.99268;,
 -9.38266;-7.11483;5.99268;,
 -9.46953;-5.91847;5.93652;,
 -11.89431;-5.47090;5.67924;,
 -12.02132;-7.04869;5.86268;,
 -12.02132;-7.04869;5.86268;,
 -11.89431;-5.47090;5.67924;,
 -11.91779;-5.79368;4.33340;,
 -12.08251;-7.36561;4.54148;,
 -12.08251;-7.36561;4.54148;,
 -9.42372;-7.60594;4.51052;,
 -11.91779;-5.79368;4.33340;,
 -9.34981;-6.23340;4.53644;;
 
 87;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,5,4,11;,
 4;12,13,10,11;,
 3;12,11,4;,
 3;13,5,10;,
 4;14,15,9,8;,
 4;14,16,17,15;,
 4;14,18,19,16;,
 4;14,8,1,18;,
 4;15,20,2,9;,
 4;15,17,21,20;,
 4;20,22,3,2;,
 4;22,23,0,3;,
 4;24,25,17,16;,
 4;24,7,6,25;,
 4;24,26,4,7;,
 4;24,16,19,26;,
 4;25,27,21,17;,
 4;25,6,5,27;,
 4;27,5,13,22;,
 4;22,13,12,23;,
 3;22,20,21;,
 3;22,21,27;,
 3;28,23,29;,
 3;28,0,23;,
 3;30,23,12;,
 3;30,29,23;,
 4;12,4,26,30;,
 4;30,26,19,29;,
 4;29,19,18,28;,
 4;0,28,18,1;,
 4;31,32,33,34;,
 4;35,36,37,38;,
 4;39,40,41,42;,
 4;43,44,45,46;,
 4;43,47,48,38;,
 4;49,44,37,50;,
 4;51,52,53,54;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 4;63,64,65,66;,
 4;63,67,68,58;,
 4;69,64,57,70;,
 4;71,72,73,74;,
 4;75,76,77,78;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;83,87,88,78;,
 4;89,84,77,90;,
 4;91,92,93,94;,
 4;95,96,97,98;,
 4;99,100,101,102;,
 4;103,104,105,106;,
 4;103,107,108,98;,
 4;109,104,97,110;,
 4;111,112,113,114;,
 4;115,116,117,118;,
 4;119,120,121,122;,
 4;123,124,125,126;,
 4;123,127,128,118;,
 4;129,124,117,130;,
 4;131,132,133,134;,
 4;135,136,137,138;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;143,147,148,138;,
 4;149,144,137,150;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;159,160,161,162;,
 4;163,164,165,166;,
 4;163,167,168,158;,
 4;169,164,157,170;,
 4;171,172,173,174;,
 4;175,176,177,178;,
 4;179,180,181,182;,
 4;183,184,185,186;,
 4;183,187,188,178;,
 4;189,184,177,190;,
 4;191,192,193,194;,
 4;195,196,197,198;,
 4;199,200,201,202;,
 4;203,204,205,206;,
 4;203,207,208,198;,
 4;209,204,197,210;;
 
 MeshMaterialList {
  1;
  87;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.781176;0.800000;0.787451;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  -0.044853;-0.247072;-0.967959;,
  -0.059989;-0.229909;0.971362;,
  -0.381213;0.026044;-0.924120;,
  0.272834;0.022643;0.961795;,
  -0.791284;-0.605844;0.082600;,
  -0.393312;0.110634;-0.912724;,
  -0.717968;0.695533;-0.027490;,
  0.108824;-0.105972;0.988396;,
  0.498873;-0.862286;-0.087116;,
  0.030962;0.137206;-0.990058;,
  0.462834;-0.017620;-0.886270;,
  -0.624135;-0.727316;-0.285426;,
  -0.769868;-0.608773;0.191568;,
  -0.617668;0.686158;0.384282;,
  0.556877;-0.827958;-0.066131;,
  -0.815688;-0.577478;-0.034236;,
  -0.663515;0.474737;-0.578250;,
  0.456318;-0.889816;0.000795;,
  0.713714;0.700114;0.021255;,
  0.611179;-0.791472;-0.005596;,
  0.702189;0.711990;-0.001126;,
  0.703732;0.710450;0.004616;,
  0.711065;0.702825;0.020582;,
  0.094088;-0.991294;-0.092106;,
  -0.569769;0.586257;-0.575904;,
  0.588703;-0.788574;0.177709;,
  0.577969;-0.753593;0.313127;,
  -0.750887;-0.596938;0.282547;,
  -0.648086;0.643869;0.406714;,
  -0.772090;0.634954;-0.026652;,
  -0.620373;0.617253;0.483876;,
  -0.569008;0.641025;0.515089;,
  0.477880;-0.873127;-0.096332;,
  0.588546;-0.808298;0.016390;,
  0.500125;-0.865315;0.033242;,
  0.398202;-0.906098;-0.142903;,
  0.670285;-0.742103;-0.000648;,
  0.691184;0.722113;-0.028595;,
  0.684973;0.727525;-0.038992;,
  0.675887;0.734431;-0.061547;,
  -0.822527;-0.552627;-0.134364;,
  -0.722595;0.415158;-0.552721;,
  0.309495;-0.950629;-0.022753;,
  0.273299;-0.961818;0.014607;,
  0.705463;0.708733;0.004400;,
  0.706812;0.707256;0.014348;,
  -0.594145;0.534843;-0.600778;,
  -0.662190;0.748809;-0.028119;,
  -0.584659;0.726945;0.360173;,
  -0.515266;0.662118;0.544151;,
  0.159820;0.406221;-0.899690;,
  -0.633888;-0.704866;-0.318356;,
  -0.199538;-0.465962;0.862012;,
  -0.039106;-0.089240;-0.995242;,
  -0.838212;-0.545208;0.012198;,
  0.020749;-0.037583;0.999078;,
  0.060614;0.074106;-0.995407;,
  0.973690;-0.040498;0.224248;,
  -0.001645;-0.050533;0.998721;,
  -0.081003;0.070613;-0.994209;,
  -0.842578;-0.538344;0.015757;,
  0.085814;-0.082832;0.992862;,
  0.016199;-0.056867;-0.998250;,
  0.980245;-0.197173;0.015575;,
  -0.024530;0.103621;0.994314;,
  -0.099933;0.031998;-0.994480;,
  -0.866320;-0.495491;0.063069;,
  0.041504;-0.063216;0.997136;,
  0.031440;-0.107409;-0.993718;,
  0.958394;-0.241058;0.152879;,
  0.024949;0.120690;0.992377;,
  -0.115199;0.045786;-0.992287;,
  -0.867143;-0.497459;-0.024460;,
  0.003655;-0.091306;0.995816;,
  0.022538;-0.058841;-0.998013;,
  0.999514;0.010958;0.029175;,
  -0.065348;0.082574;0.994440;,
  0.573112;0.784383;0.237248;,
  -0.757099;0.639346;0.134305;,
  0.669775;-0.736408;-0.095424;,
  0.828668;0.557867;0.045757;,
  -0.751056;0.658612;0.046319;,
  0.520456;-0.848736;-0.093660;,
  -0.986596;0.161171;-0.025552;,
  0.004947;-0.999773;0.020723;,
  0.156667;0.986921;-0.037969;,
  0.815798;0.577597;-0.029248;,
  -0.661927;0.747505;0.055580;,
  0.537796;-0.842868;-0.018677;,
  -0.990996;0.131334;-0.026043;,
  -0.097266;-0.995052;-0.020257;,
  0.251635;0.960584;-0.118147;,
  0.794655;0.602929;-0.070707;,
  -0.665652;0.722327;0.187486;,
  0.488614;-0.854060;-0.178434;,
  -0.990256;0.136570;-0.027250;,
  -0.071484;-0.987980;0.137059;,
  0.215845;0.974604;-0.059654;,
  0.703677;0.696570;-0.140102;,
  -0.669122;0.687612;0.281896;,
  0.601373;-0.767179;-0.223130;,
  -0.995579;0.093464;0.009300;,
  -0.062093;-0.959150;0.276000;,
  0.190151;0.957774;-0.215667;;
  87;
  4;3,7,7,3;,
  4;5,0,0,2;,
  4;7,1,1,7;,
  4;11,23,11,11;,
  4;9,10,10,10;,
  3;24,24,24;,
  3;25,26,26;,
  4;12,12,27,27;,
  4;12,4,4,12;,
  4;28,13,6,29;,
  4;28,30,31,13;,
  4;32,14,33,34;,
  4;32,35,8,14;,
  4;14,19,36,33;,
  4;37,20,38,39;,
  4;15,15,4,4;,
  4;15,40,40,15;,
  4;41,16,5,2;,
  4;41,29,6,16;,
  4;42,17,8,35;,
  4;42,43,23,17;,
  4;17,23,25,19;,
  4;37,44,45,20;,
  3;19,14,8;,
  3;19,8,17;,
  3;21,20,18;,
  3;21,38,20;,
  3;22,20,45;,
  3;22,18,20;,
  4;9,5,16,46;,
  4;46,16,6,47;,
  4;47,6,13,48;,
  4;49,48,13,31;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;94,94,94,94;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;;
 }
 MeshTextureCoords {
  211;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
