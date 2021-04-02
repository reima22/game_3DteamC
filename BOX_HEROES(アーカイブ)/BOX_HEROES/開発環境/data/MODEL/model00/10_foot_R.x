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
 268;
 11.16152;-7.04456;-11.02453;,
 8.33003;-4.34405;-9.59289;,
 9.67135;-3.84577;-8.46590;,
 11.71382;-5.15739;-8.86746;,
 10.94773;-12.07598;-10.30207;,
 9.32911;-12.33548;-12.47979;,
 9.37822;-7.99494;-12.67441;,
 11.68829;-10.53073;-7.75190;,
 9.99533;-2.79540;-6.66866;,
 11.41585;-2.94682;-6.06401;,
 11.55007;-9.00249;-5.60434;,
 10.92530;-5.54851;-4.57870;,
 6.95650;-7.05931;-12.43912;,
 6.62700;-3.85633;-9.49009;,
 5.20085;-5.18039;-11.05836;,
 6.72190;-12.09084;-11.72352;,
 4.58092;-10.55574;-10.14261;,
 5.22623;-2.81219;-8.27290;,
 3.73003;-2.97389;-8.64937;,
 3.38362;-9.03118;-8.35141;,
 3.23962;-5.57545;-7.16402;,
 8.33003;-4.34405;-9.59289;,
 8.07918;-8.55716;-8.80316;,
 9.61322;-8.16056;-7.81860;,
 9.67135;-3.84577;-8.46590;,
 10.47757;-8.44604;-6.14509;,
 9.99533;-2.79540;-6.66866;,
 6.25941;-8.17234;-8.94677;,
 6.62700;-3.85633;-9.49009;,
 4.56134;-8.46681;-8.13520;,
 5.22623;-2.81219;-8.27290;,
 9.70863;-5.39630;-5.11475;,
 11.55007;-9.00249;-5.60434;,
 10.92530;-5.54851;-4.57870;,
 3.38362;-9.03118;-8.35141;,
 4.53181;-5.41457;-6.85614;,
 3.23962;-5.57545;-7.16402;,
 10.92530;-5.54851;-4.57870;,
 11.41585;-2.94682;-6.06401;,
 3.73003;-2.97389;-8.64937;,
 3.23962;-5.57545;-7.16402;,
 2.20779;-13.37456;-2.13077;,
 1.55645;-12.64590;0.01069;,
 0.80418;-12.64463;-0.21853;,
 1.45538;-13.37321;-2.36016;,
 0.40437;-10.73932;1.10495;,
 1.15677;-10.74080;1.33430;,
 0.40880;-8.38537;1.10495;,
 1.16120;-8.38686;1.33430;,
 2.86179;-12.64848;-4.27231;,
 2.10941;-12.64702;-4.50167;,
 3.26873;-10.74482;-5.59590;,
 2.51633;-10.74332;-5.82515;,
 3.27317;-8.39090;-5.59590;,
 2.52091;-8.38940;-5.82515;,
 2.87348;-6.48558;-4.27241;,
 2.12108;-6.48421;-4.50167;,
 2.22229;-5.75697;-2.13077;,
 1.46988;-5.75562;-2.36016;,
 1.56812;-6.48315;0.01069;,
 0.81585;-6.48169;-0.21853;,
 1.16120;-8.38686;1.33430;,
 0.40880;-8.38537;1.10495;,
 1.45538;-13.37321;-2.36016;,
 0.80418;-12.64463;-0.21853;,
 1.46263;-9.56441;-2.36016;,
 0.40437;-10.73932;1.10495;,
 0.40880;-8.38537;1.10495;,
 0.81585;-6.48169;-0.21853;,
 1.46988;-5.75562;-2.36016;,
 2.12108;-6.48421;-4.50167;,
 2.52091;-8.38940;-5.82515;,
 2.51633;-10.74332;-5.82515;,
 2.10941;-12.64702;-4.50167;,
 8.45927;-12.86737;0.06880;,
 9.20883;-12.81611;0.30142;,
 8.49992;-12.09499;2.42720;,
 7.75038;-12.14625;2.19462;,
 7.97033;-10.19776;3.71591;,
 7.22077;-10.24903;3.48333;,
 7.82230;-7.84878;3.67538;,
 7.07273;-7.90003;3.44266;,
 9.07678;-12.13659;-2.08206;,
 9.82638;-12.08534;-1.84948;,
 9.36682;-10.23319;-3.43642;,
 10.11640;-10.18192;-3.20382;,
 9.21878;-7.88418;-3.47696;,
 9.96834;-7.83293;-3.24434;,
 8.68904;-5.98687;-2.18824;,
 9.43863;-5.93556;-1.95564;,
 7.98014;-5.26588;-0.06243;,
 8.72971;-5.21458;0.17016;,
 7.36275;-5.99666;2.08832;,
 8.11233;-5.94538;2.32089;,
 7.07273;-7.90003;3.44266;,
 7.82230;-7.84878;3.67538;,
 9.20883;-12.81611;0.30142;,
 8.96928;-9.01535;0.23578;,
 8.49992;-12.09499;2.42720;,
 7.97033;-10.19776;3.71591;,
 7.82230;-7.84878;3.67538;,
 8.11233;-5.94538;2.32089;,
 8.72971;-5.21458;0.17016;,
 9.43863;-5.93556;-1.95564;,
 9.96834;-7.83293;-3.24434;,
 10.11640;-10.18192;-3.20382;,
 9.82638;-12.08534;-1.84948;,
 14.60943;-19.78053;-15.96287;,
 14.16533;-17.37303;-16.08234;,
 13.18127;-15.55206;-11.08332;,
 14.09258;-17.59332;-18.20250;,
 14.25256;-19.78026;-17.88226;,
 13.48110;-17.95191;-19.89718;,
 11.41451;-16.19678;-19.24828;,
 11.87740;-17.20488;-20.62838;,
 12.13333;-15.90974;-16.74949;,
 14.41535;-20.79262;-16.02487;,
 13.96897;-19.53477;-10.34703;,
 14.03635;-20.79262;-17.68964;,
 13.03324;-19.77810;-19.94587;,
 13.02840;-20.79262;-19.64807;,
 10.54682;-19.77209;-20.75721;,
 10.51191;-20.79262;-20.41593;,
 8.45110;-19.76914;-19.67346;,
 10.29797;-17.86894;-21.01894;,
 8.51041;-20.79262;-19.45146;,
 7.19124;-19.76914;-18.22341;,
 7.56986;-17.05443;-18.17029;,
 8.81965;-17.48993;-20.04723;,
 9.66960;-15.82868;-17.52903;,
 4.86466;-19.53466;-13.59374;,
 5.51747;-15.55876;-13.62719;,
 4.16500;-20.25448;-11.71426;,
 4.02275;-18.25440;-12.02253;,
 7.38302;-20.79262;-18.15943;,
 5.08209;-20.79307;-13.52221;,
 12.01645;-18.34087;-20.89367;,
 3.07841;-20.24048;-8.90112;,
 6.79638;-13.11043;-13.23314;,
 7.27417;-13.00493;-12.95182;,
 4.15964;-8.89508;-6.77024;,
 2.87817;-17.49831;-8.88612;,
 2.02458;-12.26306;-6.20857;,
 10.81296;-15.63556;-17.16732;,
 10.67230;-15.47918;-16.52939;,
 11.63515;-15.65899;-16.04877;,
 9.71107;-15.59578;-16.65756;,
 11.80226;-13.29662;-11.58743;,
 11.49449;-12.51909;-2.54135;,
 12.09056;-17.25561;-4.95837;,
 13.38071;-18.07405;-8.22848;,
 11.92975;-20.23941;-5.37268;,
 13.19455;-20.25487;-8.44201;,
 13.75168;-20.79307;-10.43279;,
 10.95092;-8.89790;-4.31644;,
 11.24917;-13.15913;-11.66094;,
 4.16500;-20.25448;-11.71426;,
 5.08209;-20.79307;-13.52221;,
 13.75168;-20.79307;-10.43279;,
 14.41535;-20.79262;-16.02487;,
 7.38302;-20.79262;-18.15943;,
 8.51041;-20.79262;-19.45146;,
 14.03635;-20.79262;-17.68964;,
 10.51191;-20.79262;-20.41593;,
 13.02840;-20.79262;-19.64807;,
 3.07841;-20.24048;-8.90112;,
 13.19455;-20.25487;-8.44201;,
 11.92975;-20.23941;-5.37268;,
 2.87817;-17.49831;-8.88612;,
 3.29397;-12.09310;-5.68245;,
 2.02458;-12.26306;-6.20857;,
 12.09056;-17.25561;-4.95837;,
 9.80946;-12.13017;-2.93418;,
 11.49449;-12.51909;-2.54135;,
 10.95092;-8.89790;-4.31644;,
 10.15545;-8.98407;-4.48166;,
 3.47769;-8.77859;-7.21882;,
 10.15545;-8.98407;-4.48166;,
 11.24917;-13.15913;-11.66094;,
 10.69044;-16.88863;-10.35748;,
 9.80946;-12.13017;-2.93418;,
 10.95428;-18.57920;-14.54772;,
 10.14483;-18.39749;-14.96569;,
 11.63515;-15.65899;-16.04877;,
 10.67230;-15.47918;-16.52939;,
 9.03034;-18.51598;-15.15640;,
 9.71107;-15.59578;-16.65756;,
 6.67492;-16.69246;-11.58810;,
 7.27417;-13.00493;-12.95182;,
 3.29397;-12.09310;-5.68245;,
 4.15964;-8.89508;-6.77024;,
 3.47769;-8.77859;-7.21882;,
 1.76555;-0.69106;0.58485;,
 1.43768;-9.14214;2.09502;,
 3.46321;-8.64639;5.48203;,
 3.58346;-17.79270;6.46554;,
 2.26684;-1.37234;-1.96289;,
 1.76986;-9.63810;-2.16623;,
 4.30418;-2.15470;-4.62794;,
 6.38327;-11.53276;-10.64484;,
 8.67334;-11.20948;-10.64391;,
 7.74889;-15.09543;-14.54131;,
 8.01905;-18.29468;-15.31278;,
 10.17142;-14.82729;-14.98140;,
 12.24515;-14.88537;-13.11062;,
 12.75582;-18.09685;-13.80876;,
 8.23823;-1.95184;-3.57464;,
 10.34416;-11.34054;-9.00544;,
 7.73480;-1.27744;-0.45327;,
 8.61631;-9.64735;0.11109;,
 7.11742;-17.93590;4.33209;,
 9.65147;-18.22567;0.07539;,
 6.07579;-0.57041;1.96417;,
 6.86444;-9.07201;3.96099;,
 3.41690;-0.18700;3.03357;,
 10.48507;-18.11902;-16.06181;,
 2.08351;-18.22597;-2.89634;,
 1.87696;-18.00935;2.03490;,
 6.14504;-18.47893;-1.66494;,
 1.49483;-14.94807;-3.01807;,
 1.55711;-18.21430;-2.82104;,
 0.81466;-17.63396;-0.04244;,
 1.04577;-13.19013;-0.41945;,
 0.90002;-20.80459;0.51522;,
 0.72715;-16.59784;5.86639;,
 1.06657;-20.71400;5.93968;,
 1.64085;-20.79893;-2.67623;,
 2.32992;-20.84944;-5.00858;,
 2.27784;-18.52363;-4.99770;,
 1.45350;-11.05002;4.60023;,
 2.92059;-16.13336;8.46811;,
 3.33235;-10.55840;6.97002;,
 3.08217;-20.79762;8.31821;,
 5.74349;-16.31320;7.80202;,
 6.45976;-11.02922;6.35802;,
 9.48814;-12.91528;3.02793;,
 9.72542;-17.39168;3.35569;,
 5.90426;-20.79827;7.72524;,
 9.52975;-20.78846;3.48614;,
 10.73404;-18.01848;0.85167;,
 10.58880;-20.80755;0.87611;,
 11.18877;-20.78420;-1.56442;,
 11.33974;-18.45708;-1.48657;,
 10.45770;-14.95026;0.68942;,
 11.02729;-16.63242;-0.55983;,
 2.32992;-20.84944;-5.00858;,
 2.27784;-18.52363;-4.99770;,
 11.33974;-18.45708;-1.48657;,
 11.18877;-20.78420;-1.56442;,
 1.97895;-16.62116;-4.28223;,
 11.02729;-16.63242;-0.55983;,
 1.49483;-14.94807;-3.01807;,
 10.45770;-14.95026;0.68942;,
 9.48814;-12.91528;3.02793;,
 1.04577;-13.19013;-0.41945;,
 1.45350;-11.05002;4.60023;,
 6.45976;-11.02922;6.35802;,
 3.33235;-10.55840;6.97002;,
 10.58880;-20.80755;0.87611;,
 9.52975;-20.78846;3.48614;,
 0.90002;-20.80459;0.51522;,
 1.64085;-20.79893;-2.67623;,
 5.90426;-20.79827;7.72524;,
 1.06657;-20.71400;5.93968;,
 3.08217;-20.79762;8.31821;,
 1.97895;-16.62116;-4.28223;,
 10.15545;-8.98407;-4.48166;,
 4.15964;-8.89508;-6.77024;;
 
 304;
 3;0,1,2;,
 3;2,3,0;,
 3;4,0,3;,
 3;0,4,5;,
 3;5,6,0;,
 3;1,0,6;,
 3;3,7,4;,
 3;3,2,8;,
 3;8,9,3;,
 3;3,9,10;,
 3;10,7,3;,
 3;9,11,10;,
 3;1,6,12;,
 3;12,6,5;,
 3;13,1,12;,
 3;12,14,13;,
 3;5,15,12;,
 3;14,12,15;,
 3;15,16,14;,
 3;17,13,14;,
 3;14,18,17;,
 3;14,16,19;,
 3;19,18,14;,
 3;18,19,20;,
 3;21,22,23;,
 3;23,24,21;,
 3;24,23,25;,
 3;25,26,24;,
 3;27,22,21;,
 3;21,28,27;,
 3;29,27,28;,
 3;28,30,29;,
 3;31,25,32;,
 3;32,33,31;,
 3;26,25,31;,
 3;34,29,35;,
 3;35,36,34;,
 3;30,35,29;,
 3;26,31,37;,
 3;37,38,26;,
 3;30,39,40;,
 3;40,35,30;,
 3;41,42,43;,
 3;43,44,41;,
 3;45,43,42;,
 3;42,46,45;,
 3;47,45,46;,
 3;46,48,47;,
 3;49,41,44;,
 3;44,50,49;,
 3;51,49,50;,
 3;50,52,51;,
 3;53,51,52;,
 3;52,54,53;,
 3;55,53,54;,
 3;54,56,55;,
 3;57,55,56;,
 3;56,58,57;,
 3;59,57,58;,
 3;58,60,59;,
 3;61,59,60;,
 3;60,62,61;,
 3;63,64,65;,
 3;64,66,65;,
 3;66,67,65;,
 3;67,68,65;,
 3;68,69,65;,
 3;69,70,65;,
 3;70,71,65;,
 3;71,72,65;,
 3;73,63,65;,
 3;72,73,65;,
 3;74,75,76;,
 3;76,77,74;,
 3;77,76,78;,
 3;78,79,77;,
 3;79,78,80;,
 3;80,81,79;,
 3;75,74,82;,
 3;82,83,75;,
 3;83,82,84;,
 3;84,85,83;,
 3;85,84,86;,
 3;86,87,85;,
 3;87,86,88;,
 3;88,89,87;,
 3;89,88,90;,
 3;90,91,89;,
 3;91,90,92;,
 3;92,93,91;,
 3;93,92,94;,
 3;94,95,93;,
 3;96,97,98;,
 3;98,97,99;,
 3;99,97,100;,
 3;100,97,101;,
 3;101,97,102;,
 3;102,97,103;,
 3;103,97,104;,
 3;104,97,105;,
 3;106,97,96;,
 3;105,97,106;,
 3;107,108,109;,
 3;110,108,107;,
 3;107,111,110;,
 3;110,111,112;,
 3;113,110,112;,
 3;112,114,113;,
 3;110,113,115;,
 3;115,108,110;,
 3;111,107,116;,
 3;116,107,117;,
 3;116,118,111;,
 3;119,111,118;,
 3;112,111,119;,
 3;118,120,119;,
 3;121,119,120;,
 3;120,122,121;,
 3;123,121,122;,
 3;124,121,123;,
 3;122,125,123;,
 3;126,123,125;,
 3;123,126,127;,
 3;128,113,114;,
 3;124,123,128;,
 3;127,128,123;,
 3;114,124,128;,
 3;128,127,129;,
 3;129,113,128;,
 3;126,130,131;,
 3;132,133,130;,
 3;125,134,126;,
 3;126,134,135;,
 3;124,136,121;,
 3;119,136,112;,
 3;136,114,112;,
 3;124,114,136;,
 3;121,136,119;,
 3;133,132,137;,
 3;127,131,138;,
 3;129,138,139;,
 3;140,139,138;,
 3;137,141,133;,
 3;133,141,142;,
 3;129,143,113;,
 3;113,143,115;,
 3;115,143,144;,
 3;144,145,115;,
 3;143,129,146;,
 3;146,144,143;,
 3;108,115,147;,
 3;148,109,147;,
 3;148,149,150;,
 3;151,152,150;,
 3;152,153,117;,
 3;150,149,151;,
 3;154,147,155;,
 3;145,155,147;,
 3;156,157,158;,
 3;159,158,157;,
 3;159,160,161;,
 3;161,162,159;,
 3;162,161,163;,
 3;163,164,162;,
 3;165,156,166;,
 3;166,167,165;,
 3;168,169,170;,
 3;168,165,167;,
 3;167,171,168;,
 3;168,171,172;,
 3;171,173,172;,
 3;172,169,168;,
 3;174,175,172;,
 3;172,173,174;,
 3;142,176,138;,
 3;177,178,179;,
 3;179,180,177;,
 3;181,179,178;,
 3;182,181,183;,
 3;183,184,182;,
 3;185,182,184;,
 3;184,186,185;,
 3;187,185,186;,
 3;186,188,187;,
 3;189,187,188;,
 3;169,190,191;,
 3;191,170,169;,
 3;192,193,194;,
 3;195,194,193;,
 3;196,197,193;,
 3;198,199,197;,
 3;198,200,199;,
 3;201,199,200;,
 3;202,199,201;,
 3;202,201,203;,
 3;204,203,200;,
 3;203,204,205;,
 3;206,207,200;,
 3;198,206,200;,
 3;206,208,209;,
 3;210,211,209;,
 3;211,205,207;,
 3;208,212,213;,
 3;212,214,194;,
 3;205,215,203;,
 3;203,215,202;,
 3;216,197,199;,
 3;195,210,213;,
 3;217,193,197;,
 3;217,216,218;,
 3;202,218,216;,
 3;205,218,202;,
 3;205,202,215;,
 3;211,218,205;,
 3;218,211,210;,
 3;210,195,218;,
 3;218,195,217;,
 3;219,220,221;,
 3;221,222,219;,
 3;223,221,220;,
 3;222,221,224;,
 3;223,225,224;,
 3;224,221,223;,
 3;220,226,223;,
 3;227,226,220;,
 3;220,228,227;,
 3;222,224,229;,
 3;229,224,230;,
 3;230,231,229;,
 3;230,224,225;,
 3;225,232,230;,
 3;231,230,233;,
 3;233,234,231;,
 3;233,235,234;,
 3;235,233,236;,
 3;236,233,237;,
 3;230,232,237;,
 3;237,233,230;,
 3;237,238,236;,
 3;235,236,239;,
 3;239,236,238;,
 3;238,240,239;,
 3;239,240,241;,
 3;241,242,239;,
 3;239,243,235;,
 3;243,239,244;,
 3;239,242,244;,
 3;245,246,247;,
 3;247,248,245;,
 3;247,246,249;,
 3;249,250,247;,
 3;250,249,251;,
 3;251,252,250;,
 3;253,252,251;,
 3;251,254,253;,
 3;253,254,255;,
 3;255,256,253;,
 3;256,255,257;,
 3;258,259,260;,
 3;260,261,258;,
 3;248,258,261;,
 3;261,245,248;,
 3;260,259,262;,
 3;262,263,260;,
 3;262,264,263;,
 3;220,219,265;,
 3;220,265,228;,
 3;109,117,107;,
 3;109,150,117;,
 3;117,153,116;,
 3;131,127,126;,
 3;135,130,126;,
 3;130,135,132;,
 3;131,130,133;,
 3;131,133,142;,
 3;138,129,127;,
 3;138,131,142;,
 3;147,109,108;,
 3;109,148,150;,
 3;117,150,152;,
 3;147,154,148;,
 3;155,266,154;,
 3;158,166,156;,
 3;157,160,159;,
 3;147,115,145;,
 3;139,146,129;,
 3;138,176,140;,
 3;178,183,181;,
 3;188,267,189;,
 3;194,214,192;,
 3;193,192,196;,
 3;197,196,198;,
 3;200,203,201;,
 3;200,207,204;,
 3;207,205,204;,
 3;209,207,206;,
 3;213,209,208;,
 3;209,213,210;,
 3;207,209,211;,
 3;194,213,212;,
 3;199,202,216;,
 3;213,194,195;,
 3;197,216,217;,
 3;193,217,195;;
 
 MeshMaterialList {
  2;
  304;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.320000;0.592800;0.336800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\model\\allegorica_d.tga";
   }
  }
  Material {
   0.460800;0.356000;0.363200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\model\\body_d.tga";
   }
  }
 }
 MeshNormals {
  297;
  0.530620;0.413218;-0.740063;,
  0.233270;0.672846;-0.702042;,
  0.335002;0.709061;-0.620489;,
  0.338990;0.736101;-0.585868;,
  0.934321;-0.082463;-0.346763;,
  0.317602;-0.093839;-0.943569;,
  0.297071;0.353106;-0.887167;,
  0.995151;-0.024503;-0.095253;,
  0.355387;0.762220;-0.541037;,
  0.321496;0.759875;-0.565005;,
  0.983224;0.029013;0.180079;,
  0.918948;0.050061;0.391188;,
  -0.109201;0.342660;-0.933091;,
  0.105802;0.708493;-0.697742;,
  0.082269;0.735229;-0.672808;,
  -0.534273;-0.087638;-0.840757;,
  -0.735118;-0.030596;-0.677248;,
  0.042799;0.760974;-0.647370;,
  0.080528;0.759028;-0.646059;,
  -0.892345;0.022411;-0.450798;,
  -0.968844;0.043413;-0.243838;,
  -0.313455;0.192949;0.929794;,
  -0.717335;0.131403;0.684225;,
  -0.945458;-0.136103;0.295947;,
  0.161222;0.129663;0.978364;,
  0.570128;-0.132319;0.810830;,
  -0.470259;-0.074366;0.879389;,
  -0.156352;-0.073265;0.984980;,
  -0.033145;-0.994125;0.103041;,
  -0.197066;-0.740646;0.642346;,
  -0.146466;-0.867326;0.475702;,
  0.029563;-0.994244;-0.102983;,
  -0.266714;-0.409120;0.872631;,
  -0.285796;-0.204286;0.936263;,
  -0.284991;0.205346;0.936276;,
  -0.265162;0.410124;0.872632;,
  0.143362;-0.867885;-0.475628;,
  0.194321;-0.741385;-0.642330;,
  0.265122;-0.410121;-0.872646;,
  0.284893;-0.205346;-0.936306;,
  0.285722;0.204251;-0.936293;,
  0.266706;0.409095;-0.872645;,
  0.197119;0.740640;-0.642337;,
  0.146527;0.867334;-0.475669;,
  0.033180;0.994127;-0.103010;,
  -0.029545;0.994245;0.102975;,
  -0.143312;0.867887;0.475640;,
  -0.194302;0.741401;0.642317;,
  -0.956563;0.001817;-0.291519;,
  0.030625;-0.992301;0.120002;,
  0.094413;-0.991838;-0.085700;,
  -0.092739;-0.866829;0.489905;,
  -0.152293;-0.740909;0.654111;,
  -0.244453;-0.410759;0.878362;,
  -0.277105;-0.206509;0.938385;,
  -0.302912;0.202261;0.931308;,
  -0.296080;0.406782;0.864213;,
  0.201853;-0.864675;-0.459992;,
  0.245502;-0.737978;-0.628583;,
  0.295990;-0.406757;-0.864256;,
  0.302843;-0.202230;-0.931337;,
  0.277088;0.206525;-0.938387;,
  0.244480;0.410752;-0.878358;,
  0.152283;0.740911;-0.654110;,
  0.092683;0.866840;-0.489896;,
  -0.030687;0.992302;-0.119976;,
  -0.094469;0.991830;0.085725;,
  -0.201890;0.864662;0.460001;,
  -0.245556;0.737978;0.628563;,
  0.953046;0.065182;0.295726;,
  0.999003;0.043034;-0.011878;,
  0.857871;0.507693;-0.079404;,
  0.946569;0.314250;0.072482;,
  0.843170;0.482889;-0.236397;,
  0.935655;-0.138941;-0.324414;,
  0.742818;0.280760;-0.607779;,
  0.200065;0.899818;-0.387688;,
  0.176249;0.628842;-0.757294;,
  0.346184;0.905463;-0.245547;,
  0.979024;-0.199682;-0.040484;,
  0.981226;-0.040982;0.188456;,
  0.894288;-0.219067;-0.390203;,
  0.656761;-0.242004;-0.714212;,
  0.520507;-0.257630;-0.814064;,
  0.000556;-0.273632;-0.961834;,
  -0.208698;-0.283130;-0.936100;,
  -0.617329;-0.108195;-0.779229;,
  -0.231407;0.151985;-0.960912;,
  -0.647159;-0.195975;-0.736736;,
  -0.839926;-0.049682;-0.540421;,
  -0.692366;0.424357;-0.583567;,
  -0.449718;0.605548;-0.656556;,
  -0.064101;0.906048;-0.418292;,
  -0.891721;-0.042163;-0.450618;,
  -0.828003;0.255509;-0.499125;,
  -0.913014;-0.141304;-0.382674;,
  -0.910336;0.004865;-0.413841;,
  -0.816702;-0.187151;-0.545869;,
  -0.886830;-0.182461;-0.424548;,
  0.324972;-0.028497;-0.945294;,
  -0.934758;-0.094018;-0.342619;,
  -0.316235;0.733455;-0.601698;,
  0.243994;0.871764;-0.424846;,
  0.256642;0.854103;-0.452374;,
  -0.940810;-0.020924;-0.338289;,
  -0.842839;0.213798;-0.493876;,
  0.054716;0.970991;-0.232770;,
  0.144539;0.969196;-0.199417;,
  0.113704;0.922226;-0.369554;,
  0.118546;0.957779;-0.261929;,
  0.607668;0.740842;-0.286170;,
  0.968996;0.209471;0.131032;,
  0.918307;-0.091401;0.385173;,
  0.956100;0.002142;0.293033;,
  0.917206;-0.109320;0.383121;,
  0.929469;-0.136978;0.342527;,
  0.959981;-0.180373;0.214247;,
  0.142082;0.858677;-0.492429;,
  0.185784;0.856268;-0.481964;,
  -0.412301;-0.036717;0.910307;,
  -0.296721;-0.116329;0.947852;,
  -0.228079;0.449818;0.863507;,
  -0.805255;0.171229;-0.567666;,
  -0.986048;0.076067;-0.148066;,
  -0.982504;0.126336;-0.136840;,
  -0.274168;0.491853;0.826385;,
  -0.185210;0.486237;0.853973;,
  0.859920;0.053208;0.507648;,
  -0.950119;0.097594;0.296226;,
  -0.983836;0.023303;0.177550;,
  -0.852209;0.105001;0.512556;,
  -0.899702;-0.002641;0.436497;,
  -0.950170;0.043941;-0.308620;,
  -0.950614;0.030843;-0.308841;,
  -0.451858;0.387233;-0.803664;,
  -0.723306;0.281156;-0.630697;,
  0.208360;0.697369;-0.685757;,
  -0.172981;0.571178;-0.802392;,
  -0.780765;0.128282;-0.611515;,
  0.208024;0.483253;-0.850407;,
  0.550351;0.616489;-0.563077;,
  0.942499;0.235415;-0.237224;,
  0.416582;0.564021;-0.712979;,
  0.942756;0.332672;-0.023257;,
  0.923780;0.146760;0.353684;,
  0.948640;0.105131;0.298379;,
  0.789675;0.067350;0.609817;,
  0.944429;0.137635;0.298514;,
  0.569785;0.242125;0.785315;,
  0.706177;0.134005;0.695239;,
  0.392302;0.257719;0.882995;,
  0.673130;0.287738;-0.681250;,
  -0.945931;0.018809;-0.323823;,
  -0.995425;-0.044390;0.084610;,
  -0.003610;-0.999301;0.037216;,
  -0.967305;-0.012030;-0.253332;,
  -0.959938;-0.040484;-0.277274;,
  -0.989339;-0.009393;-0.145328;,
  -0.995181;0.073556;-0.064843;,
  -0.992013;-0.056295;-0.112875;,
  -0.973323;0.046081;0.224763;,
  -0.883085;-0.063043;0.464958;,
  -0.966096;-0.045539;-0.254136;,
  -0.954304;-0.033338;-0.296972;,
  -0.950093;-0.026260;-0.310859;,
  -0.884732;0.204015;0.419079;,
  -0.775682;0.089061;0.624808;,
  -0.786593;0.213762;0.579290;,
  -0.762880;-0.047152;0.644818;,
  0.517311;0.111359;0.848522;,
  0.515960;0.160032;0.841532;,
  0.862345;0.086179;0.498932;,
  0.835273;0.024598;0.549284;,
  0.510859;-0.009528;0.859612;,
  0.879590;-0.034479;0.474482;,
  0.951094;0.014742;0.308550;,
  0.950313;-0.046790;0.307760;,
  0.966304;-0.059831;0.250354;,
  0.967290;-0.014385;0.253266;,
  0.948367;0.101310;0.300560;,
  0.960144;0.071915;0.270095;,
  0.323944;0.496267;-0.805468;,
  0.979280;-0.068952;-0.190410;,
  0.996956;-0.022498;-0.074648;,
  0.969864;0.039743;0.240385;,
  -0.749015;-0.028645;-0.661934;,
  -0.918210;0.033096;-0.394708;,
  -0.312668;0.161700;0.935998;,
  -0.870277;0.047766;0.490241;,
  -0.992851;-0.091801;-0.076289;,
  0.393423;0.047985;0.918104;,
  0.831459;-0.084394;0.549139;,
  -0.493868;-0.359666;0.791666;,
  -0.362069;0.255561;0.896434;,
  -0.926559;-0.112337;-0.358983;,
  -0.082752;-0.358217;0.929964;,
  -0.254925;0.255939;0.932474;,
  0.955811;-0.105708;0.274319;,
  -0.289877;0.514638;0.806920;,
  -0.288607;0.515159;0.807042;,
  -0.259961;0.514745;0.816981;,
  -0.261080;0.515273;0.816291;,
  -0.956569;0.001821;-0.291501;,
  -0.956567;0.001801;-0.291508;,
  -0.956560;0.001791;-0.291532;,
  -0.956558;0.001825;-0.291536;,
  -0.956561;0.001835;-0.291525;,
  -0.956569;0.001821;-0.291501;,
  -0.956563;0.001802;-0.291521;,
  -0.956559;0.001822;-0.291534;,
  -0.956565;0.001835;-0.291514;,
  -0.956565;0.001815;-0.291514;,
  0.953042;0.065175;0.295742;,
  0.953051;0.065172;0.295713;,
  0.953053;0.065167;0.295709;,
  0.953054;0.065183;0.295702;,
  0.953050;0.065191;0.295711;,
  0.953047;0.065179;0.295724;,
  0.953043;0.065189;0.295734;,
  0.953041;0.065186;0.295743;,
  0.953043;0.065188;0.295734;,
  0.953039;0.065189;0.295748;,
  -0.058609;-0.984882;0.163013;,
  -0.029152;-0.996222;0.081803;,
  -0.058072;-0.985151;0.161570;,
  0.000013;-1.000000;-0.000041;,
  0.000013;-1.000000;-0.000042;,
  0.000000;-1.000000;-0.000000;,
  -0.001620;-0.999989;0.004360;,
  -0.029991;-0.996128;0.082644;,
  -0.001621;-0.999989;0.004369;,
  -0.352204;-0.314899;0.881358;,
  -0.378220;-0.038326;0.924922;,
  -0.370102;-0.032105;0.928436;,
  -0.379137;-0.069232;0.922747;,
  -0.347015;-0.352669;0.869025;,
  -0.231824;-0.022117;0.972506;,
  -0.170228;0.437671;0.882874;,
  -0.983952;0.058670;-0.168514;,
  -0.981532;0.110444;-0.156194;,
  -0.989069;0.038803;-0.142254;,
  -0.310219;0.490825;0.814159;,
  -0.311898;0.491358;0.813196;,
  -0.228465;0.489114;0.841767;,
  -0.172993;0.481896;0.858982;,
  0.848831;0.071405;0.523820;,
  0.850136;0.062997;0.522782;,
  0.868511;0.005872;0.495635;,
  0.875998;-0.018525;0.481959;,
  -0.456891;0.394807;0.797106;,
  -0.426627;0.399712;0.811307;,
  -0.943695;0.000081;-0.330815;,
  -0.197480;0.214014;-0.956661;,
  0.981725;0.119260;0.148301;,
  0.411159;0.202046;0.888890;,
  -0.297358;0.272049;-0.915187;,
  0.468106;0.076714;0.880336;,
  -0.062463;-0.996562;0.054427;,
  -0.065108;-0.997830;0.009766;,
  0.015018;-0.999566;-0.025325;,
  0.056599;-0.998266;-0.016194;,
  0.056670;-0.997272;-0.047302;,
  0.049320;-0.997731;0.045824;,
  0.021192;-0.996005;0.086752;,
  -0.018855;-0.996760;0.078188;,
  0.228732;0.232503;0.945317;,
  0.225679;0.068144;0.971816;,
  0.205561;-0.024321;0.978342;,
  0.361742;0.010062;-0.932224;,
  0.352845;0.198336;-0.914420;,
  0.356326;0.222513;-0.907480;,
  0.362300;0.007675;-0.932030;,
  0.310857;0.579873;-0.753070;,
  0.257427;0.723283;-0.640776;,
  0.269464;0.709629;-0.651011;,
  0.174841;0.861256;-0.477146;,
  0.161240;0.870878;-0.464298;,
  0.119712;0.927251;-0.354788;,
  0.112997;0.936168;-0.332898;,
  0.091206;0.958221;-0.271096;,
  0.000592;-0.999999;-0.001226;,
  0.000745;-0.999994;0.003265;,
  -0.005648;-0.999969;0.005532;,
  0.000466;-0.999994;0.003538;,
  0.000818;-0.999980;0.006221;,
  -0.000946;-0.999771;0.021372;,
  -0.009418;-0.999947;-0.004265;,
  -0.015158;-0.999866;-0.006121;,
  -0.006463;-0.999539;-0.029662;,
  -0.949404;-0.034876;-0.312114;,
  0.987237;0.157999;0.020007;,
  0.010449;0.865095;-0.501499;,
  0.394854;0.834896;-0.383458;,
  -0.975760;0.141846;-0.166648;,
  0.871188;-0.070562;0.485853;,
  -0.833771;0.149285;0.531544;,
  0.926086;0.066522;0.371402;;
  304;
  3;0,1,2;,
  3;2,3,0;,
  3;4,182,183;,
  3;0,4,5;,
  3;5,6,0;,
  3;1,0,6;,
  3;183,7,4;,
  3;3,2,8;,
  3;8,9,3;,
  3;183,184,10;,
  3;10,7,183;,
  3;184,11,10;,
  3;1,6,12;,
  3;12,6,5;,
  3;13,1,12;,
  3;12,14,13;,
  3;5,15,12;,
  3;185,12,15;,
  3;15,16,185;,
  3;17,13,14;,
  3;14,18,17;,
  3;185,16,19;,
  3;19,186,185;,
  3;186,19,20;,
  3;187,21,22;,
  3;22,188,187;,
  3;188,22,23;,
  3;23,189,188;,
  3;24,21,187;,
  3;187,190,24;,
  3;25,24,190;,
  3;190,191,25;,
  3;26,23,192;,
  3;192,193,26;,
  3;189,23,194;,
  3;195,25,27;,
  3;27,196,195;,
  3;191,197,25;,
  3;198,26,193;,
  3;193,199,198;,
  3;200,201,196;,
  3;196,27,200;,
  3;28,29,30;,
  3;30,31,28;,
  3;32,30,29;,
  3;29,33,32;,
  3;34,32,33;,
  3;33,35,34;,
  3;36,28,31;,
  3;31,37,36;,
  3;38,36,37;,
  3;37,39,38;,
  3;40,38,39;,
  3;39,41,40;,
  3;42,40,41;,
  3;41,43,42;,
  3;44,42,43;,
  3;43,45,44;,
  3;46,44,45;,
  3;45,47,46;,
  3;35,46,47;,
  3;47,34,35;,
  3;202,203,48;,
  3;203,204,48;,
  3;204,205,48;,
  3;205,206,48;,
  3;206,207,48;,
  3;207,208,48;,
  3;208,209,48;,
  3;209,210,48;,
  3;211,202,48;,
  3;210,211,48;,
  3;49,50,51;,
  3;51,52,49;,
  3;52,51,53;,
  3;53,54,52;,
  3;54,53,55;,
  3;55,56,54;,
  3;50,49,57;,
  3;57,58,50;,
  3;58,57,59;,
  3;59,60,58;,
  3;60,59,61;,
  3;61,62,60;,
  3;62,61,63;,
  3;63,64,62;,
  3;64,63,65;,
  3;65,66,64;,
  3;66,65,67;,
  3;67,68,66;,
  3;68,67,56;,
  3;56,55,68;,
  3;212,69,213;,
  3;213,69,214;,
  3;214,69,215;,
  3;215,69,216;,
  3;216,69,217;,
  3;217,69,218;,
  3;218,69,219;,
  3;219,69,220;,
  3;221,69,212;,
  3;220,69,221;,
  3;70,71,72;,
  3;73,71,70;,
  3;70,74,73;,
  3;73,74,75;,
  3;76,73,75;,
  3;75,77,76;,
  3;73,76,78;,
  3;78,71,73;,
  3;74,70,79;,
  3;79,70,80;,
  3;79,81,74;,
  3;82,74,81;,
  3;75,74,82;,
  3;81,83,82;,
  3;84,82,83;,
  3;83,85,84;,
  3;86,84,85;,
  3;87,84,86;,
  3;85,88,86;,
  3;89,86,88;,
  3;86,89,90;,
  3;91,76,77;,
  3;87,86,91;,
  3;90,91,86;,
  3;77,87,91;,
  3;91,90,92;,
  3;92,76,91;,
  3;89,93,94;,
  3;95,96,93;,
  3;88,97,89;,
  3;89,97,98;,
  3;87,99,84;,
  3;82,99,75;,
  3;99,77,75;,
  3;87,77,99;,
  3;84,99,82;,
  3;96,95,100;,
  3;90,94,101;,
  3;92,101,102;,
  3;103,102,101;,
  3;100,104,96;,
  3;96,104,105;,
  3;92,106,76;,
  3;76,106,78;,
  3;78,106,107;,
  3;107,108,78;,
  3;106,92,109;,
  3;109,107,106;,
  3;71,78,110;,
  3;111,72,110;,
  3;111,112,113;,
  3;114,115,113;,
  3;115,116,80;,
  3;113,112,114;,
  3;117,110,118;,
  3;108,118,110;,
  3;222,223,224;,
  3;225,224,223;,
  3;225,226,227;,
  3;227,227,225;,
  3;227,227,227;,
  3;227,227,227;,
  3;228,222,229;,
  3;229,230,228;,
  3;231,119,232;,
  3;231,233,234;,
  3;234,235,231;,
  3;231,235,120;,
  3;235,236,120;,
  3;120,119,231;,
  3;237,121,120;,
  3;120,236,237;,
  3;105,122,101;,
  3;238,239,123;,
  3;123,240,238;,
  3;124,123,239;,
  3;125,241,242;,
  3;242,243,125;,
  3;126,125,243;,
  3;243,244,126;,
  3;127,245,246;,
  3;246,247,127;,
  3;248,127,247;,
  3;119,249,250;,
  3;250,232,119;,
  3;128,129,130;,
  3;131,130,129;,
  3;132,133,129;,
  3;134,135,133;,
  3;134,136,135;,
  3;137,135,136;,
  3;138,135,251;,
  3;252,137,139;,
  3;140,139,136;,
  3;139,140,141;,
  3;142,143,136;,
  3;134,142,136;,
  3;253,144,145;,
  3;146,147,145;,
  3;147,141,143;,
  3;144,148,149;,
  3;148,150,254;,
  3;141,151,139;,
  3;139,255,138;,
  3;152,133,135;,
  3;256,146,149;,
  3;153,129,133;,
  3;257,258,154;,
  3;259,154,258;,
  3;260,154,259;,
  3;260,259,261;,
  3;262,154,260;,
  3;154,262,263;,
  3;263,264,154;,
  3;154,264,257;,
  3;155,156,157;,
  3;157,158,155;,
  3;159,157,156;,
  3;158,157,160;,
  3;159,161,160;,
  3;160,157,159;,
  3;156,162,159;,
  3;163,162,156;,
  3;156,164,163;,
  3;158,160,165;,
  3;165,160,166;,
  3;166,167,165;,
  3;166,160,161;,
  3;161,168,166;,
  3;265,266,169;,
  3;169,170,265;,
  3;169,171,170;,
  3;171,169,172;,
  3;172,169,173;,
  3;266,267,173;,
  3;173,169,266;,
  3;173,174,172;,
  3;171,172,175;,
  3;175,172,174;,
  3;174,176,175;,
  3;175,176,177;,
  3;177,178,175;,
  3;175,179,171;,
  3;179,175,180;,
  3;175,178,180;,
  3;268,269,270;,
  3;270,271,268;,
  3;270,269,181;,
  3;181,272,270;,
  3;272,181,273;,
  3;273,274,272;,
  3;275,274,273;,
  3;273,276,275;,
  3;275,276,277;,
  3;277,278,275;,
  3;278,277,279;,
  3;280,281,282;,
  3;282,283,280;,
  3;284,280,283;,
  3;283,285,284;,
  3;282,281,286;,
  3;286,287,282;,
  3;286,288,287;,
  3;156,155,289;,
  3;156,289,164;,
  3;72,80,70;,
  3;72,113,80;,
  3;80,116,79;,
  3;94,90,89;,
  3;98,93,89;,
  3;93,98,95;,
  3;94,93,96;,
  3;94,96,105;,
  3;101,92,90;,
  3;101,94,105;,
  3;110,72,71;,
  3;72,111,113;,
  3;80,113,115;,
  3;110,290,111;,
  3;118,291,117;,
  3;224,229,222;,
  3;223,226,225;,
  3;110,78,108;,
  3;102,109,92;,
  3;101,292,103;,
  3;239,293,124;,
  3;247,294,248;,
  3;130,295,128;,
  3;129,128,132;,
  3;133,132,134;,
  3;136,139,137;,
  3;136,143,140;,
  3;143,141,296;,
  3;145,143,253;,
  3;149,145,144;,
  3;145,149,146;,
  3;143,145,147;,
  3;254,149,148;,
  3;135,138,152;,
  3;149,254,256;,
  3;133,152,153;,
  3;129,153,131;;
 }
 MeshTextureCoords {
  268;
  0.688020;0.714250;,
  0.660110;0.699890;,
  0.658700;0.714400;,
  0.673000;0.726120;,
  0.723740;0.720930;,
  0.720560;0.695990;,
  0.698120;0.694980;,
  0.709750;0.738470;,
  0.650320;0.728210;,
  0.654770;0.739350;,
  0.693320;0.750350;,
  0.669170;0.752980;,
  0.688020;0.714250;,
  0.658700;0.714400;,
  0.673000;0.726120;,
  0.723740;0.720930;,
  0.709750;0.738470;,
  0.650320;0.728210;,
  0.654770;0.739350;,
  0.693320;0.750350;,
  0.669170;0.752980;,
  0.319800;0.275440;,
  0.341430;0.268820;,
  0.336080;0.257310;,
  0.314770;0.265020;,
  0.334920;0.245580;,
  0.306560;0.255450;,
  0.336080;0.257310;,
  0.314770;0.265020;,
  0.334920;0.245580;,
  0.306560;0.255450;,
  0.317420;0.243660;,
  0.339440;0.238030;,
  0.320330;0.234860;,
  0.339440;0.238030;,
  0.317420;0.243660;,
  0.320330;0.234860;,
  0.311260;0.236650;,
  0.300510;0.248560;,
  0.300510;0.248560;,
  0.311260;0.236650;,
  0.221400;0.012700;,
  0.230580;0.012700;,
  0.230580;0.015770;,
  0.221400;0.015770;,
  0.239770;0.015770;,
  0.239770;0.012700;,
  0.248950;0.015770;,
  0.248950;0.012700;,
  0.212220;0.012700;,
  0.212220;0.015770;,
  0.203050;0.012700;,
  0.203040;0.015770;,
  0.193870;0.012700;,
  0.193860;0.015770;,
  0.184690;0.012700;,
  0.184680;0.015770;,
  0.175500;0.012700;,
  0.175500;0.015770;,
  0.166320;0.012700;,
  0.166320;0.015770;,
  0.157130;0.012700;,
  0.157130;0.015770;,
  0.475390;0.567910;,
  0.482180;0.570110;,
  0.475390;0.579470;,
  0.486380;0.575890;,
  0.486380;0.583040;,
  0.482180;0.588820;,
  0.475390;0.591020;,
  0.468600;0.588820;,
  0.464400;0.583040;,
  0.464400;0.575890;,
  0.468600;0.570110;,
  0.221400;0.012700;,
  0.221400;0.015770;,
  0.230580;0.015770;,
  0.230580;0.012700;,
  0.239770;0.015770;,
  0.239770;0.012700;,
  0.248950;0.015770;,
  0.248950;0.012700;,
  0.212220;0.012700;,
  0.212220;0.015770;,
  0.203050;0.012700;,
  0.203040;0.015770;,
  0.193870;0.012700;,
  0.193860;0.015770;,
  0.184690;0.012700;,
  0.184680;0.015770;,
  0.175500;0.012700;,
  0.175500;0.015770;,
  0.166320;0.012700;,
  0.166320;0.015770;,
  0.157130;0.012700;,
  0.157130;0.015770;,
  0.475390;0.567910;,
  0.475390;0.579470;,
  0.482180;0.570110;,
  0.486380;0.575890;,
  0.486380;0.583040;,
  0.482180;0.588820;,
  0.475390;0.591020;,
  0.468600;0.588820;,
  0.464400;0.583040;,
  0.464400;0.575890;,
  0.468600;0.570110;,
  0.606710;0.261710;,
  0.607430;0.276170;,
  0.636160;0.288620;,
  0.596730;0.274400;,
  0.595440;0.262240;,
  0.587620;0.275050;,
  0.587090;0.288190;,
  0.582130;0.282260;,
  0.601670;0.290770;,
  0.605540;0.256020;,
  0.640080;0.263540;,
  0.594490;0.257380;,
  0.581210;0.267230;,
  0.580350;0.262580;,
  0.567900;0.276910;,
  0.565050;0.272260;,
  0.558680;0.288430;,
  0.574280;0.285170;,
  0.554480;0.283780;,
  0.555500;0.299050;,
  0.571740;0.304040;,
  0.571480;0.292990;,
  0.587390;0.301670;,
  0.549330;0.329400;,
  0.574370;0.334020;,
  0.542200;0.340150;,
  0.554870;0.341970;,
  0.550080;0.295360;,
  0.541170;0.326450;,
  0.578970;0.277690;,
  0.538940;0.358390;,
  0.592810;0.335910;,
  0.596860;0.335130;,
  0.610500;0.380770;,
  0.554980;0.362560;,
  0.581930;0.386380;,
  0.594980;0.297630;,
  0.597460;0.300230;,
  0.604080;0.295550;,
  0.591760;0.304620;,
  0.632750;0.306000;,
  0.688160;0.306990;,
  0.673660;0.278130;,
  0.652800;0.272910;,
  0.671950;0.259990;,
  0.652060;0.259650;,
  0.639670;0.256280;,
  0.678010;0.330260;,
  0.630930;0.309960;,
  0.008410;0.838910;,
  0.008860;0.834400;,
  0.028750;0.833940;,
  0.025770;0.822140;,
  0.009920;0.823260;,
  0.011200;0.819780;,
  0.023720;0.819070;,
  0.014500;0.816290;,
  0.020170;0.815900;,
  0.008380;0.845420;,
  0.029160;0.838540;,
  0.028980;0.845720;,
  0.007900;0.851340;,
  0.011200;0.864540;,
  0.008230;0.864180;,
  0.029540;0.852220;,
  0.026480;0.864740;,
  0.030180;0.863770;,
  0.028650;0.872440;,
  0.026880;0.872370;,
  0.605780;0.382150;,
  0.010110;0.242530;,
  0.010110;0.214190;,
  0.021890;0.214190;,
  0.021890;0.242530;,
  0.021890;0.198380;,
  0.021890;0.195090;,
  0.010110;0.198380;,
  0.010110;0.195090;,
  0.021890;0.191730;,
  0.010110;0.191730;,
  0.021890;0.175650;,
  0.010110;0.175650;,
  0.021890;0.148990;,
  0.011820;0.872160;,
  0.010100;0.872490;,
  0.037140;0.440150;,
  0.023460;0.441910;,
  0.024300;0.446790;,
  0.009500;0.448490;,
  0.036030;0.434170;,
  0.022640;0.434100;,
  0.034770;0.428220;,
  0.019580;0.416270;,
  0.020130;0.414930;,
  0.013810;0.408510;,
  0.008630;0.406980;,
  0.014270;0.406310;,
  0.014210;0.408450;,
  0.009010;0.406910;,
  0.035150;0.427810;,
  0.019950;0.416890;,
  0.036250;0.433680;,
  0.022710;0.434190;,
  0.009300;0.442620;,
  0.008830;0.433530;,
  0.037390;0.440110;,
  0.023640;0.442090;,
  0.037990;0.443570;,
  0.008940;0.404200;,
  0.008740;0.432630;,
  0.009110;0.441560;,
  0.008380;0.432460;,
  0.360590;0.025630;,
  0.360260;0.015280;,
  0.368930;0.016730;,
  0.369470;0.030880;,
  0.369960;0.005720;,
  0.386720;0.018230;,
  0.386210;0.005720;,
  0.360170;0.005720;,
  0.352870;0.005720;,
  0.352910;0.014270;,
  0.386620;0.035560;,
  0.396000;0.018870;,
  0.397110;0.036020;,
  0.395400;0.005720;,
  0.403750;0.018310;,
  0.407630;0.034480;,
  0.421800;0.028860;,
  0.421610;0.015170;,
  0.404050;0.005720;,
  0.421030;0.005720;,
  0.429690;0.013450;,
  0.429620;0.005720;,
  0.437290;0.005720;,
  0.437090;0.012450;,
  0.429580;0.022870;,
  0.433880;0.017880;,
  0.500950;0.932720;,
  0.496260;0.932680;,
  0.496660;0.913090;,
  0.501340;0.913560;,
  0.492120;0.932610;,
  0.492500;0.912890;,
  0.487780;0.932460;,
  0.488120;0.912910;,
  0.481580;0.912800;,
  0.481520;0.931190;,
  0.471560;0.926440;,
  0.472200;0.915760;,
  0.468480;0.921090;,
  0.506370;0.913000;,
  0.512050;0.913200;,
  0.512400;0.931590;,
  0.505850;0.932400;,
  0.522580;0.917120;,
  0.522560;0.927520;,
  0.525660;0.922060;,
  0.356030;0.020500;,
  0.674670;0.334770;,
  0.010110;0.148990;;
 }
}
