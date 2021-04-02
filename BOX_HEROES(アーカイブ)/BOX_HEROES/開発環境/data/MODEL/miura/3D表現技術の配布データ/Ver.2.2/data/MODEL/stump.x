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
 259;
 0.00000;15.88508;-8.00000;,
 2.47214;15.88508;-7.60846;,
 2.47214;14.71386;-7.60846;,
 0.00000;14.71386;-8.00000;,
 2.47214;15.88508;-7.60846;,
 4.70228;15.88508;-6.47214;,
 4.70228;14.71386;-6.47214;,
 2.47214;14.71386;-7.60846;,
 6.47214;15.88508;-4.70228;,
 6.47214;14.71386;-4.70228;,
 7.60846;15.88508;-2.47214;,
 7.60846;14.71386;-2.47214;,
 8.00000;15.88508;0.00000;,
 8.00000;14.71386;0.00000;,
 7.60846;15.88508;2.47214;,
 7.60846;14.71386;2.47214;,
 6.47214;15.88508;4.70228;,
 6.47214;14.71386;4.70228;,
 4.70228;15.88508;6.47214;,
 4.70228;14.71386;6.47214;,
 2.47214;15.88508;7.60846;,
 2.47214;14.71386;7.60846;,
 -0.00000;15.88508;8.00000;,
 -0.00000;14.71386;8.00000;,
 -2.47214;15.88508;7.60845;,
 -2.47214;14.71386;7.60845;,
 -4.70229;15.88508;6.47214;,
 -4.70229;14.71386;6.47214;,
 -6.47214;15.88508;4.70228;,
 -6.47214;14.71386;4.70228;,
 -7.60846;15.88508;2.47213;,
 -7.60846;14.71386;2.47213;,
 -8.00000;15.88508;-0.00001;,
 -8.00000;14.71386;-0.00001;,
 -7.60845;15.88508;-2.47215;,
 -7.60845;14.71386;-2.47215;,
 -6.47213;15.88508;-4.70229;,
 -6.47213;14.71386;-4.70229;,
 -4.70228;15.88508;-6.47215;,
 -4.70228;14.71386;-6.47215;,
 -2.47213;15.88508;-7.60846;,
 -2.47213;14.71386;-7.60846;,
 2.47214;13.54263;-7.60846;,
 0.00000;13.54263;-8.00000;,
 4.70228;13.54263;-6.47214;,
 2.47214;13.54263;-7.60846;,
 6.47214;13.54263;-4.70228;,
 7.60846;13.54263;-2.47214;,
 8.00000;13.54263;0.00000;,
 7.60846;13.54263;2.47214;,
 6.47214;13.54263;4.70228;,
 4.70228;13.54263;6.47214;,
 2.47214;13.54263;7.60846;,
 -0.00000;13.54263;8.00000;,
 -2.47214;13.54263;7.60845;,
 -4.70229;13.54263;6.47214;,
 -6.47214;13.54263;4.70228;,
 -7.60846;13.54263;2.47213;,
 -8.00000;13.54263;-0.00001;,
 -7.60845;13.54263;-2.47215;,
 -6.47213;13.54263;-4.70229;,
 -4.70228;13.54263;-6.47215;,
 -2.47213;13.54263;-7.60846;,
 2.47214;12.37138;-7.60846;,
 0.00000;12.37138;-8.00000;,
 4.70228;12.37138;-6.47214;,
 2.47214;12.37138;-7.60846;,
 6.47214;12.37138;-4.70228;,
 7.60846;12.37138;-2.47214;,
 8.00000;12.37138;0.00000;,
 7.60846;12.37138;2.47214;,
 6.47214;12.37138;4.70228;,
 4.70228;12.37138;6.47214;,
 2.47214;12.37138;7.60846;,
 -0.00000;12.37138;8.00000;,
 -2.47214;12.37138;7.60845;,
 -4.70229;12.37138;6.47214;,
 -6.47214;12.37138;4.70228;,
 -7.60846;12.37138;2.47213;,
 -8.00000;12.37138;-0.00001;,
 -7.60845;12.37138;-2.47215;,
 -6.47213;12.37138;-4.70229;,
 -4.70228;12.37138;-6.47215;,
 -2.47213;12.37138;-7.60846;,
 2.47214;11.20014;-7.60846;,
 0.00000;11.20014;-8.00000;,
 4.70228;11.20014;-6.47214;,
 2.47214;11.20014;-7.60846;,
 6.47214;11.20014;-4.70228;,
 7.60846;11.20014;-2.47214;,
 8.00000;11.20014;0.00000;,
 7.60846;11.20014;2.47214;,
 6.47214;11.20014;4.70228;,
 4.70228;11.20014;6.47214;,
 2.47214;11.20014;7.60846;,
 -0.00000;11.20014;8.00000;,
 -2.47214;11.20014;7.60845;,
 -4.70229;11.20014;6.47214;,
 -6.47214;11.20014;4.70228;,
 -7.60846;11.20014;2.47213;,
 -8.00000;11.20014;-0.00001;,
 -7.60845;11.20014;-2.47215;,
 -6.47213;11.20014;-4.70229;,
 -4.70228;11.20014;-6.47215;,
 -2.47213;11.20014;-7.60846;,
 2.47214;10.02829;-7.60846;,
 0.00000;10.02829;-8.00000;,
 4.70228;10.02829;-6.47214;,
 2.47214;10.02829;-7.60846;,
 6.47214;10.02829;-4.70228;,
 7.60846;10.02829;-2.47214;,
 8.00000;10.02829;0.00000;,
 7.60846;10.02829;2.47214;,
 6.47214;10.02829;4.70228;,
 4.70228;10.02829;6.47214;,
 2.47214;10.02829;7.60846;,
 -0.00000;10.02829;8.00000;,
 -2.47214;10.02829;7.60845;,
 -4.70229;10.02829;6.47214;,
 -6.47214;10.02829;4.70228;,
 -7.60846;10.02829;2.47213;,
 -8.00000;10.02829;-0.00001;,
 -7.60845;10.02829;-2.47215;,
 -6.47213;10.02829;-4.70229;,
 -4.70228;10.02829;-6.47215;,
 -2.47213;10.02829;-7.60846;,
 2.19266;7.89735;-8.67974;,
 0.02984;7.89735;-8.88583;,
 5.38546;7.89735;-7.29296;,
 2.19266;7.89735;-8.67974;,
 7.35267;7.05221;-5.25590;,
 8.55230;6.36076;-2.93781;,
 8.86042;7.89735;0.12273;,
 7.83745;7.89735;4.15929;,
 7.07297;7.89735;5.42616;,
 5.88327;7.89735;6.64560;,
 2.78345;7.89735;8.62669;,
 -0.00000;7.89735;9.23821;,
 -3.60046;7.89735;8.91750;,
 -6.22354;7.89735;7.41486;,
 -8.90953;7.36444;5.90528;,
 -8.38253;7.89735;2.80908;,
 -8.44083;7.89735;0.20594;,
 -8.41072;7.89735;-2.78296;,
 -6.59382;7.89735;-4.72398;,
 -4.83733;7.89735;-7.07265;,
 -2.71172;7.89735;-8.44155;,
 2.01271;5.70192;-9.83655;,
 0.10407;5.22298;-11.18605;,
 5.90729;5.67138;-7.86081;,
 2.01271;5.70192;-9.83655;,
 8.04297;4.35958;-5.48428;,
 9.66005;3.05838;-3.47468;,
 10.01724;4.20242;0.37980;,
 8.97591;5.57829;4.38881;,
 7.79987;5.73691;6.44747;,
 6.58523;5.72452;7.77915;,
 2.70912;5.73499;9.85075;,
 -0.24292;5.75789;10.51161;,
 -4.57489;5.76639;9.99234;,
 -8.46321;5.76639;8.64568;,
 -10.84191;5.03717;7.39265;,
 -9.57989;5.76639;3.36247;,
 -9.32784;5.76639;0.83070;,
 -8.96615;5.76639;-3.06043;,
 -7.14649;5.76639;-5.57973;,
 -4.95387;5.76639;-7.93424;,
 -1.86903;5.70191;-9.83655;,
 2.21837;3.56116;-11.84169;,
 -0.03185;2.59462;-13.02881;,
 6.16566;3.49407;-8.63586;,
 2.21837;3.56116;-11.84169;,
 8.58941;2.08860;-5.87376;,
 13.04384;1.10736;-4.86706;,
 11.12264;2.76421;-0.41712;,
 9.50743;3.51417;4.62307;,
 8.80637;3.57763;6.70153;,
 7.23238;3.56082;8.20566;,
 2.83366;3.57807;10.70529;,
 -0.50508;3.61359;12.11973;,
 -5.23434;3.63518;10.99983;,
 -11.82271;3.63545;10.49193;,
 -14.72151;2.48389;9.94627;,
 -11.01386;3.63224;4.35614;,
 -10.76607;3.63471;0.89843;,
 -9.56816;3.63545;-2.99425;,
 -7.57441;3.63545;-5.77305;,
 -5.23665;3.63545;-8.88540;,
 -2.22893;3.55308;-11.19902;,
 3.16953;1.42236;-12.25301;,
 -0.29488;0.71831;-18.80488;,
 6.41583;1.49799;-9.17404;,
 3.16953;1.42236;-12.25301;,
 10.40118;0.72013;-6.71711;,
 14.50690;0.36151;-5.63129;,
 12.97740;0.60009;-1.49064;,
 10.84809;0.93336;3.60654;,
 11.16534;0.53027;7.89047;,
 6.63142;0.39053;10.00959;,
 3.40111;0.03154;12.12115;,
 0.38041;0.41813;15.94535;,
 -5.87024;0.28926;11.98425;,
 -15.46679;1.25808;13.01667;,
 -19.34189;0.80282;13.65728;,
 -14.80958;1.49217;6.95170;,
 -14.81564;1.43768;3.86877;,
 -12.74225;1.50207;-3.10314;,
 -10.54348;1.04654;-7.49880;,
 -7.36620;1.50449;-10.19862;,
 -3.19457;1.50270;-14.62356;,
 3.62864;-0.62646;-12.51782;,
 0.00000;-0.64734;-24.98982;,
 6.60309;-0.62646;-9.90971;,
 3.62864;-0.62646;-12.51782;,
 13.05869;-0.63260;-7.96223;,
 19.97382;-0.62646;-7.95388;,
 16.22614;-0.64608;-2.32110;,
 12.37116;-0.63053;3.32041;,
 16.61760;-0.62646;9.14273;,
 6.87741;-0.63851;11.18100;,
 3.70971;-0.65474;14.36196;,
 0.92607;-0.62646;21.10006;,
 -6.43205;-0.75552;12.85837;,
 -16.40617;-0.62646;15.65635;,
 -28.47385;-0.62646;20.84368;,
 -23.31250;-0.62646;13.62546;,
 -18.41725;-0.62646;7.71638;,
 -14.65540;-0.62646;-3.49243;,
 -16.77884;-0.62646;-10.47191;,
 -10.33258;-0.67263;-13.43579;,
 -5.33539;-0.62646;-16.77059;,
 0.00000;15.88508;0.00000;,
 2.47214;15.88508;-7.60846;,
 0.00000;15.88508;-8.00000;,
 4.70228;15.88508;-6.47214;,
 6.47214;15.88508;-4.70228;,
 7.60846;15.88508;-2.47214;,
 8.00000;15.88508;0.00000;,
 7.60846;15.88508;2.47214;,
 6.47214;15.88508;4.70228;,
 4.70228;15.88508;6.47214;,
 2.47214;15.88508;7.60846;,
 -0.00000;15.88508;8.00000;,
 -2.47214;15.88508;7.60845;,
 -4.70229;15.88508;6.47214;,
 -6.47214;15.88508;4.70228;,
 -7.60846;15.88508;2.47213;,
 -8.00000;15.88508;-0.00001;,
 -7.60845;15.88508;-2.47215;,
 -6.47213;15.88508;-4.70229;,
 -4.70228;15.88508;-6.47215;,
 -2.47213;15.88508;-7.60846;,
 0.00000;-0.62646;-0.00000;,
 6.60309;-0.62646;-9.90971;,
 13.05869;-0.63260;-7.96223;,
 19.97382;-0.62646;-7.95388;,
 16.22614;-0.64608;-2.32110;,
 12.37116;-0.63053;3.32041;,
 16.61760;-0.62646;9.14273;;
 
 240;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,0,3,41;,
 4;3,2,42,43;,
 4;7,6,44,45;,
 4;6,9,46,44;,
 4;9,11,47,46;,
 4;11,13,48,47;,
 4;13,15,49,48;,
 4;15,17,50,49;,
 4;17,19,51,50;,
 4;19,21,52,51;,
 4;21,23,53,52;,
 4;23,25,54,53;,
 4;25,27,55,54;,
 4;27,29,56,55;,
 4;29,31,57,56;,
 4;31,33,58,57;,
 4;33,35,59,58;,
 4;35,37,60,59;,
 4;37,39,61,60;,
 4;39,41,62,61;,
 4;41,3,43,62;,
 4;43,42,63,64;,
 4;45,44,65,66;,
 4;44,46,67,65;,
 4;46,47,68,67;,
 4;47,48,69,68;,
 4;48,49,70,69;,
 4;49,50,71,70;,
 4;50,51,72,71;,
 4;51,52,73,72;,
 4;52,53,74,73;,
 4;53,54,75,74;,
 4;54,55,76,75;,
 4;55,56,77,76;,
 4;56,57,78,77;,
 4;57,58,79,78;,
 4;58,59,80,79;,
 4;59,60,81,80;,
 4;60,61,82,81;,
 4;61,62,83,82;,
 4;62,43,64,83;,
 4;64,63,84,85;,
 4;66,65,86,87;,
 4;65,67,88,86;,
 4;67,68,89,88;,
 4;68,69,90,89;,
 4;69,70,91,90;,
 4;70,71,92,91;,
 4;71,72,93,92;,
 4;72,73,94,93;,
 4;73,74,95,94;,
 4;74,75,96,95;,
 4;75,76,97,96;,
 4;76,77,98,97;,
 4;77,78,99,98;,
 4;78,79,100,99;,
 4;79,80,101,100;,
 4;80,81,102,101;,
 4;81,82,103,102;,
 4;82,83,104,103;,
 4;83,64,85,104;,
 4;85,84,105,106;,
 4;87,86,107,108;,
 4;86,88,109,107;,
 4;88,89,110,109;,
 4;89,90,111,110;,
 4;90,91,112,111;,
 4;91,92,113,112;,
 4;92,93,114,113;,
 4;93,94,115,114;,
 4;94,95,116,115;,
 4;95,96,117,116;,
 4;96,97,118,117;,
 4;97,98,119,118;,
 4;98,99,120,119;,
 4;99,100,121,120;,
 4;100,101,122,121;,
 4;101,102,123,122;,
 4;102,103,124,123;,
 4;103,104,125,124;,
 4;104,85,106,125;,
 4;106,105,126,127;,
 4;108,107,128,129;,
 4;107,109,130,128;,
 4;109,110,131,130;,
 4;110,111,132,131;,
 4;111,112,133,132;,
 4;112,113,134,133;,
 4;113,114,135,134;,
 4;114,115,136,135;,
 4;115,116,137,136;,
 4;116,117,138,137;,
 4;117,118,139,138;,
 4;118,119,140,139;,
 4;119,120,141,140;,
 4;120,121,142,141;,
 4;121,122,143,142;,
 4;122,123,144,143;,
 4;123,124,145,144;,
 4;124,125,146,145;,
 4;125,106,127,146;,
 4;127,126,147,148;,
 4;129,128,149,150;,
 4;128,130,151,149;,
 4;130,131,152,151;,
 4;131,132,153,152;,
 4;132,133,154,153;,
 4;133,134,155,154;,
 4;134,135,156,155;,
 4;135,136,157,156;,
 4;136,137,158,157;,
 4;137,138,159,158;,
 4;138,139,160,159;,
 4;139,140,161,160;,
 4;140,141,162,161;,
 4;141,142,163,162;,
 4;142,143,164,163;,
 4;143,144,165,164;,
 4;144,145,166,165;,
 4;145,146,167,166;,
 4;146,127,148,167;,
 4;148,147,168,169;,
 4;150,149,170,171;,
 4;149,151,172,170;,
 4;151,152,173,172;,
 4;152,153,174,173;,
 4;153,154,175,174;,
 4;154,155,176,175;,
 4;155,156,177,176;,
 4;156,157,178,177;,
 4;157,158,179,178;,
 4;158,159,180,179;,
 4;159,160,181,180;,
 4;160,161,182,181;,
 4;161,162,183,182;,
 4;162,163,184,183;,
 4;163,164,185,184;,
 4;164,165,186,185;,
 4;165,166,187,186;,
 4;166,167,188,187;,
 4;167,148,169,188;,
 4;169,168,189,190;,
 4;171,170,191,192;,
 4;170,172,193,191;,
 4;172,173,194,193;,
 4;173,174,195,194;,
 4;174,175,196,195;,
 4;175,176,197,196;,
 4;176,177,198,197;,
 4;177,178,199,198;,
 4;178,179,200,199;,
 4;179,180,201,200;,
 4;180,181,202,201;,
 4;181,182,203,202;,
 4;182,183,204,203;,
 4;183,184,205,204;,
 4;184,185,206,205;,
 4;185,186,207,206;,
 4;186,187,208,207;,
 4;187,188,209,208;,
 4;188,169,190,209;,
 4;190,189,210,211;,
 4;192,191,212,213;,
 4;191,193,214,212;,
 4;193,194,215,214;,
 4;194,195,216,215;,
 4;195,196,217,216;,
 4;196,197,218,217;,
 4;197,198,219,218;,
 4;198,199,220,219;,
 4;199,200,221,220;,
 4;200,201,222,221;,
 4;201,202,223,222;,
 4;202,203,224,223;,
 4;203,204,225,224;,
 4;204,205,226,225;,
 4;205,206,227,226;,
 4;206,207,228,227;,
 4;207,208,229,228;,
 4;208,209,230,229;,
 4;209,190,211,230;,
 3;231,232,233;,
 3;231,234,232;,
 3;231,235,234;,
 3;231,236,235;,
 3;231,237,236;,
 3;231,238,237;,
 3;231,239,238;,
 3;231,240,239;,
 3;231,241,240;,
 3;231,242,241;,
 3;231,243,242;,
 3;231,244,243;,
 3;231,245,244;,
 3;231,246,245;,
 3;231,247,246;,
 3;231,248,247;,
 3;231,249,248;,
 3;231,250,249;,
 3;231,251,250;,
 3;231,233,251;,
 3;252,211,210;,
 3;252,210,253;,
 3;252,253,254;,
 3;252,254,255;,
 3;252,255,256;,
 3;252,256,257;,
 3;252,257,258;,
 3;252,258,219;,
 3;252,219,220;,
 3;252,220,221;,
 3;252,221,222;,
 3;252,222,223;,
 3;252,223,224;,
 3;252,224,225;,
 3;252,225,226;,
 3;252,226,227;,
 3;252,227,228;,
 3;252,228,229;,
 3;252,229,230;,
 3;252,230,211;;
 
 MeshMaterialList {
  2;
  240;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\bark1col.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\TreeEnd002_2K_Color.png";
   }
  }
 }
 MeshNormals {
  185;
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.309017;0.000000;-0.951056;,
  0.587786;0.000000;-0.809017;,
  0.809017;0.000000;-0.587786;,
  0.951056;0.000000;-0.309017;,
  1.000000;0.000000;0.000000;,
  0.951056;0.000000;0.309017;,
  0.809017;0.000000;0.587786;,
  0.587786;0.000000;0.809017;,
  0.309017;0.000000;0.951056;,
  -0.000001;0.000000;1.000000;,
  -0.309017;0.000000;0.951056;,
  -0.587785;0.000000;0.809017;,
  -0.809017;0.000000;0.587785;,
  -0.951057;0.000000;0.309016;,
  -1.000000;0.000000;-0.000001;,
  -0.951056;0.000000;-0.309018;,
  -0.809017;0.000000;-0.587786;,
  -0.587784;0.000000;-0.809018;,
  -0.309015;0.000000;-0.951057;,
  0.309017;0.000000;-0.951056;,
  0.587786;0.000000;-0.809017;,
  0.809017;0.000000;-0.587786;,
  0.951056;0.000000;0.309017;,
  0.809017;0.000000;0.587786;,
  0.587786;0.000000;0.809017;,
  0.309017;0.000000;0.951056;,
  -0.000001;0.000000;1.000000;,
  -0.951057;0.000000;0.309016;,
  -0.951056;0.000000;-0.309018;,
  -0.000000;0.000000;-1.000000;,
  0.587786;0.000000;-0.809017;,
  0.951056;0.000000;-0.309017;,
  0.809017;0.000000;0.587786;,
  -0.000001;0.000000;1.000000;,
  -0.809017;0.000000;0.587785;,
  -0.951057;0.000000;0.309016;,
  -1.000000;0.000000;-0.000001;,
  -0.000000;0.000000;-1.000000;,
  0.309017;0.000000;-0.951056;,
  0.951056;0.000000;0.309017;,
  -1.000000;0.000000;-0.000001;,
  -0.587784;0.000000;-0.809018;,
  -0.000001;0.000000;1.000000;,
  -0.951057;0.000000;0.309016;,
  -0.008274;0.201987;-0.979353;,
  0.288096;0.211121;-0.934039;,
  0.581276;0.207037;-0.786927;,
  0.810246;0.177637;-0.558522;,
  0.938464;0.158316;-0.306955;,
  0.985904;0.167313;0.000634;,
  0.928105;0.188641;0.320992;,
  0.787238;0.208024;0.580503;,
  0.585542;0.206456;0.783911;,
  0.319898;0.224140;0.920558;,
  0.015328;0.260018;0.965482;,
  -0.290339;0.300261;0.908596;,
  -0.547039;0.338302;0.765702;,
  -0.788175;0.323451;0.523602;,
  -0.947889;0.213142;0.236806;,
  -0.989532;0.144296;0.002321;,
  -0.938259;0.127322;-0.321649;,
  -0.796300;0.085731;-0.598796;,
  -0.608898;0.114724;-0.784909;,
  -0.316600;0.178554;-0.931602;,
  -0.014700;0.482097;-0.875994;,
  0.282943;0.433854;-0.855403;,
  0.574119;0.368277;-0.731272;,
  0.800939;0.323250;-0.503990;,
  0.900575;0.309984;-0.304755;,
  0.940295;0.340294;-0.006716;,
  0.862994;0.392716;0.317829;,
  0.720515;0.441322;0.534877;,
  0.549566;0.449555;0.704186;,
  0.317409;0.461277;0.828538;,
  0.040514;0.498959;0.865678;,
  -0.228782;0.568116;0.790508;,
  -0.420854;0.657331;0.625139;,
  -0.693547;0.650401;0.309793;,
  -0.891663;0.450890;0.040438;,
  -0.944571;0.327801;-0.018200;,
  -0.894350;0.297198;-0.334381;,
  -0.752518;0.260069;-0.605047;,
  -0.619381;0.289882;-0.729614;,
  -0.346296;0.402795;-0.847252;,
  -0.041022;0.588303;-0.807600;,
  0.338883;0.507147;-0.792440;,
  0.621914;0.363629;-0.693539;,
  0.766126;0.376688;-0.520728;,
  0.776349;0.524639;-0.349337;,
  0.870042;0.492752;-0.014898;,
  0.870307;0.396331;0.292381;,
  0.744483;0.417920;0.520661;,
  0.555285;0.421448;0.716966;,
  0.343906;0.441234;0.828880;,
  0.057281;0.503516;0.862085;,
  -0.186743;0.566759;0.802441;,
  -0.352967;0.729000;0.586492;,
  -0.664916;0.738036;0.114846;,
  -0.840443;0.530006;-0.112914;,
  -0.901023;0.426050;-0.081483;,
  -0.873093;0.328151;-0.360590;,
  -0.744403;0.296414;-0.598333;,
  -0.619025;0.363702;-0.696081;,
  -0.408962;0.479276;-0.776559;,
  0.041140;0.728212;-0.684116;,
  0.443116;0.531483;-0.721924;,
  0.641415;0.425663;-0.638277;,
  0.593066;0.589319;-0.548612;,
  0.551586;0.780144;-0.295175;,
  0.776371;0.623173;0.094356;,
  0.864655;0.447294;0.228690;,
  0.738073;0.472207;0.481943;,
  0.518201;0.401795;0.755002;,
  0.430486;0.435492;0.790587;,
  0.081173;0.544747;0.834662;,
  -0.154628;0.529340;0.834200;,
  -0.206635;0.768934;0.605015;,
  -0.519458;0.854101;0.025956;,
  -0.677323;0.720565;-0.148391;,
  -0.720672;0.684250;-0.111505;,
  -0.732165;0.593753;-0.333753;,
  -0.666413;0.543379;-0.510522;,
  -0.552814;0.601301;-0.576917;,
  -0.361957;0.703113;-0.612061;,
  0.187962;0.853402;-0.486185;,
  0.622330;0.473784;-0.623085;,
  0.583080;0.452164;-0.674956;,
  0.353703;0.743370;-0.567710;,
  0.354873;0.914592;-0.193873;,
  0.619246;0.758182;0.204191;,
  0.709964;0.689511;0.143272;,
  0.539463;0.767779;0.345681;,
  0.361293;0.676234;0.642008;,
  0.433380;0.715277;0.548234;,
  0.065082;0.803664;0.591513;,
  -0.121456;0.656488;0.744494;,
  0.015765;0.773424;0.633693;,
  -0.278845;0.954891;0.102121;,
  -0.481546;0.859267;-0.172553;,
  -0.568831;0.807065;-0.158359;,
  -0.563290;0.795982;-0.221624;,
  -0.439285;0.847249;-0.298660;,
  -0.371362;0.845231;-0.384284;,
  -0.306591;0.864786;-0.397677;,
  0.741296;0.579466;-0.338672;,
  0.716619;0.437609;-0.543097;,
  0.523571;0.447688;-0.724879;,
  0.245567;0.769830;-0.589116;,
  0.216479;0.961951;-0.166698;,
  0.447022;0.871669;0.200910;,
  0.545537;0.832848;0.093563;,
  0.361444;0.902487;0.234255;,
  0.229826;0.846971;0.479395;,
  0.333674;0.890303;0.309875;,
  0.024395;0.945785;0.323875;,
  -0.088842;0.801852;0.590881;,
  0.126840;0.783479;0.608336;,
  -0.133912;0.976464;0.169071;,
  -0.433000;0.877233;-0.207299;,
  -0.607176;0.763082;-0.221456;,
  -0.595051;0.781652;-0.186908;,
  -0.376058;0.899832;-0.221095;,
  -0.290899;0.897496;-0.331480;,
  -0.350729;0.867276;-0.353301;,
  -0.000263;-1.000000;-0.000886;,
  -0.363513;0.873763;-0.323104;,
  0.000128;-1.000000;0.000836;,
  0.001441;-0.999999;0.000418;,
  -0.000396;-1.000000;-0.000264;,
  0.000047;-1.000000;0.000848;,
  -0.000501;-0.999999;-0.001257;,
  -0.001395;-0.999998;-0.001300;,
  -0.000773;-0.999998;0.001653;,
  0.000127;-1.000000;-0.000231;,
  0.001697;-0.999996;-0.002122;,
  -0.003343;-0.999994;-0.001106;,
  0.004631;-0.999989;-0.000203;,
  0.000062;-0.999950;-0.010006;,
  -0.009161;-0.999912;-0.009600;,
  0.000000;-1.000000;-0.000000;,
  -0.002062;-0.999992;0.003304;,
  0.001749;-0.999996;0.002092;,
  0.002498;-0.999997;-0.000795;;
  240;
  4;1,2,21,1;,
  4;2,3,22,21;,
  4;3,4,23,22;,
  4;4,5,5,23;,
  4;5,6,6,5;,
  4;6,7,24,6;,
  4;7,8,25,24;,
  4;8,9,26,25;,
  4;9,10,27,26;,
  4;10,11,28,27;,
  4;11,12,12,28;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,29,14;,
  4;15,16,16,29;,
  4;16,17,30,16;,
  4;17,18,18,30;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,1,1,20;,
  4;1,21,21,31;,
  4;21,22,32,21;,
  4;22,23,23,32;,
  4;23,5,33,23;,
  4;5,6,6,33;,
  4;6,24,24,6;,
  4;24,25,34,24;,
  4;25,26,26,34;,
  4;26,27,10,26;,
  4;27,28,35,10;,
  4;28,12,12,35;,
  4;12,13,13,12;,
  4;13,14,36,13;,
  4;14,29,37,36;,
  4;29,16,38,37;,
  4;16,30,30,38;,
  4;30,18,18,30;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,1,31,20;,
  4;31,21,40,39;,
  4;21,32,32,40;,
  4;32,23,4,32;,
  4;23,33,33,4;,
  4;33,6,6,33;,
  4;6,24,41,6;,
  4;24,34,34,41;,
  4;34,26,9,34;,
  4;26,10,10,9;,
  4;10,35,35,10;,
  4;35,12,12,35;,
  4;12,13,13,12;,
  4;13,36,36,13;,
  4;36,37,37,36;,
  4;37,38,42,37;,
  4;38,30,30,42;,
  4;30,18,18,30;,
  4;18,19,43,18;,
  4;19,20,20,43;,
  4;20,31,39,20;,
  4;39,40,21,39;,
  4;40,32,22,21;,
  4;32,4,23,22;,
  4;4,33,33,23;,
  4;33,6,6,33;,
  4;6,41,24,6;,
  4;41,34,25,24;,
  4;34,9,26,25;,
  4;9,10,10,26;,
  4;10,35,44,10;,
  4;35,12,12,44;,
  4;12,13,13,12;,
  4;13,36,36,13;,
  4;36,37,45,36;,
  4;37,42,42,45;,
  4;42,30,30,42;,
  4;30,18,18,30;,
  4;18,43,19,18;,
  4;43,20,20,19;,
  4;20,39,39,20;,
  4;39,21,47,46;,
  4;21,22,48,47;,
  4;22,23,49,48;,
  4;23,33,50,49;,
  4;33,6,51,50;,
  4;6,24,52,51;,
  4;24,25,53,52;,
  4;25,26,54,53;,
  4;26,10,55,54;,
  4;10,44,56,55;,
  4;44,12,57,56;,
  4;12,13,58,57;,
  4;13,36,59,58;,
  4;36,45,60,59;,
  4;45,42,61,60;,
  4;42,30,62,61;,
  4;30,18,63,62;,
  4;18,19,64,63;,
  4;19,20,65,64;,
  4;20,39,46,65;,
  4;46,47,67,66;,
  4;47,48,68,67;,
  4;48,49,69,68;,
  4;49,50,70,69;,
  4;50,51,71,70;,
  4;51,52,72,71;,
  4;52,53,73,72;,
  4;53,54,74,73;,
  4;54,55,75,74;,
  4;55,56,76,75;,
  4;56,57,77,76;,
  4;57,58,78,77;,
  4;58,59,79,78;,
  4;59,60,80,79;,
  4;60,61,81,80;,
  4;61,62,82,81;,
  4;62,63,83,82;,
  4;63,64,84,83;,
  4;64,65,85,84;,
  4;65,46,66,85;,
  4;66,67,87,86;,
  4;67,68,88,87;,
  4;68,69,89,88;,
  4;69,70,90,89;,
  4;70,71,91,90;,
  4;71,72,92,91;,
  4;72,73,93,92;,
  4;73,74,94,93;,
  4;74,75,95,94;,
  4;75,76,96,95;,
  4;76,77,97,96;,
  4;77,78,98,97;,
  4;78,79,99,98;,
  4;79,80,100,99;,
  4;80,81,101,100;,
  4;81,82,102,101;,
  4;82,83,103,102;,
  4;83,84,104,103;,
  4;84,85,105,104;,
  4;85,66,86,105;,
  4;86,87,107,106;,
  4;87,88,108,107;,
  4;88,89,109,108;,
  4;89,90,110,109;,
  4;90,91,111,110;,
  4;91,92,112,111;,
  4;92,93,113,112;,
  4;93,94,114,113;,
  4;94,95,115,114;,
  4;95,96,116,115;,
  4;96,97,117,116;,
  4;97,98,118,117;,
  4;98,99,119,118;,
  4;99,100,120,119;,
  4;100,101,121,120;,
  4;101,102,122,121;,
  4;102,103,123,122;,
  4;103,104,124,123;,
  4;104,105,125,124;,
  4;105,86,106,125;,
  4;106,107,127,126;,
  4;107,108,128,127;,
  4;108,109,129,128;,
  4;109,110,130,129;,
  4;110,111,131,130;,
  4;111,112,132,131;,
  4;112,113,133,132;,
  4;113,114,134,133;,
  4;114,115,135,134;,
  4;115,116,136,135;,
  4;116,117,137,136;,
  4;117,118,138,137;,
  4;118,119,139,138;,
  4;119,120,140,139;,
  4;120,121,141,140;,
  4;121,122,142,141;,
  4;122,123,143,142;,
  4;123,124,144,143;,
  4;124,125,145,144;,
  4;125,106,126,145;,
  4;126,127,147,146;,
  4;127,128,148,147;,
  4;128,129,149,148;,
  4;129,130,150,149;,
  4;130,131,151,150;,
  4;131,132,152,151;,
  4;132,133,153,152;,
  4;133,134,154,153;,
  4;134,135,155,154;,
  4;135,136,156,155;,
  4;136,137,157,156;,
  4;137,138,158,157;,
  4;138,139,159,158;,
  4;139,140,160,159;,
  4;140,141,161,160;,
  4;141,142,162,161;,
  4;142,143,163,162;,
  4;143,144,164,163;,
  4;144,145,165,164;,
  4;145,126,167,165;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;166,168,169;,
  3;166,169,170;,
  3;166,170,171;,
  3;166,171,172;,
  3;166,172,173;,
  3;166,173,174;,
  3;166,174,175;,
  3;166,175,176;,
  3;166,176,177;,
  3;166,177,178;,
  3;166,178,179;,
  3;166,179,180;,
  3;166,180,181;,
  3;166,181,181;,
  3;166,181,181;,
  3;166,181,181;,
  3;166,181,182;,
  3;166,182,183;,
  3;166,183,184;,
  3;166,184,168;;
 }
 MeshTextureCoords {
  259;
  0.994889;0.327892;,
  1.040161;0.327892;,
  1.040161;0.347524;,
  0.994889;0.347524;,
  0.040161;0.327892;,
  0.086735;0.327892;,
  0.086735;0.347524;,
  0.040161;0.347524;,
  0.135419;0.327892;,
  0.135419;0.347524;,
  0.186615;0.327892;,
  0.186615;0.347524;,
  0.240060;0.327892;,
  0.240060;0.347524;,
  0.294773;0.327892;,
  0.294773;0.347524;,
  0.349420;0.327892;,
  0.349420;0.347524;,
  0.402934;0.327892;,
  0.402934;0.347524;,
  0.454939;0.327892;,
  0.454939;0.347524;,
  0.505733;0.327892;,
  0.505733;0.347524;,
  0.555975;0.327892;,
  0.555975;0.347524;,
  0.606328;0.327892;,
  0.606328;0.347524;,
  0.657149;0.327892;,
  0.657149;0.347524;,
  0.708315;0.327892;,
  0.708315;0.347524;,
  0.759256;0.327892;,
  0.759256;0.347524;,
  0.809224;0.327892;,
  0.809224;0.347524;,
  0.857662;0.327892;,
  0.857662;0.347524;,
  0.904455;0.327892;,
  0.904455;0.347524;,
  0.949959;0.327892;,
  0.949959;0.347524;,
  1.040161;0.367156;,
  0.994889;0.367156;,
  0.086735;0.367156;,
  0.040161;0.367156;,
  0.135419;0.367156;,
  0.186615;0.367156;,
  0.240060;0.367156;,
  0.294773;0.367156;,
  0.349420;0.367156;,
  0.402934;0.367156;,
  0.454939;0.367156;,
  0.505733;0.367156;,
  0.555975;0.367156;,
  0.606328;0.367156;,
  0.657149;0.367156;,
  0.708315;0.367156;,
  0.759256;0.367156;,
  0.809224;0.367156;,
  0.857662;0.367156;,
  0.904455;0.367156;,
  0.949959;0.367156;,
  1.040161;0.386788;,
  0.994889;0.386788;,
  0.086735;0.386788;,
  0.040161;0.386788;,
  0.135419;0.386788;,
  0.186615;0.386788;,
  0.240060;0.386788;,
  0.294773;0.386788;,
  0.349420;0.386788;,
  0.402934;0.386788;,
  0.454939;0.386788;,
  0.505733;0.386788;,
  0.555975;0.386788;,
  0.606328;0.386788;,
  0.657149;0.386788;,
  0.708315;0.386788;,
  0.759256;0.386788;,
  0.809224;0.386788;,
  0.857662;0.386788;,
  0.904455;0.386788;,
  0.949959;0.386788;,
  1.040161;0.406420;,
  0.994889;0.406420;,
  0.086735;0.406420;,
  0.040161;0.406420;,
  0.135419;0.406420;,
  0.186615;0.406420;,
  0.240060;0.406420;,
  0.294773;0.406420;,
  0.349420;0.406420;,
  0.402934;0.406420;,
  0.454939;0.406420;,
  0.505733;0.406420;,
  0.555975;0.406420;,
  0.606328;0.406420;,
  0.657149;0.406420;,
  0.708315;0.406420;,
  0.759256;0.406420;,
  0.809224;0.406420;,
  0.857662;0.406420;,
  0.904455;0.406420;,
  0.949959;0.406420;,
  1.040161;0.426062;,
  0.994889;0.426062;,
  0.086735;0.426062;,
  0.040161;0.426062;,
  0.135419;0.426062;,
  0.186615;0.426062;,
  0.240060;0.426062;,
  0.294773;0.426062;,
  0.349420;0.426062;,
  0.402934;0.426062;,
  0.454939;0.426062;,
  0.505733;0.426062;,
  0.555975;0.426062;,
  0.606328;0.426062;,
  0.657149;0.426062;,
  0.708315;0.426062;,
  0.759256;0.426062;,
  0.809224;0.426062;,
  0.857662;0.426062;,
  0.904455;0.426062;,
  0.949959;0.426062;,
  1.031190;0.461781;,
  0.995856;0.461781;,
  0.089002;0.461781;,
  0.031190;0.461781;,
  0.137873;0.475947;,
  0.185110;0.487537;,
  0.243444;0.461781;,
  0.325698;0.461781;,
  0.354362;0.461781;,
  0.386888;0.461781;,
  0.454941;0.461781;,
  0.504925;0.461781;,
  0.565580;0.461781;,
  0.615768;0.461781;,
  0.661371;0.470713;,
  0.705814;0.461781;,
  0.754849;0.461781;,
  0.809440;0.461781;,
  0.856602;0.461781;,
  0.908593;0.461781;,
  0.950655;0.461781;,
  1.025186;0.498580;,
  0.997639;0.506608;,
  0.090926;0.499092;,
  0.025186;0.498580;,
  0.142095;0.521080;,
  0.183885;0.542890;,
  0.248639;0.523714;,
  0.320622;0.500652;,
  0.360983;0.497993;,
  0.390814;0.498201;,
  0.461688;0.498026;,
  0.507954;0.497642;,
  0.571874;0.497499;,
  0.626314;0.497499;,
  0.657710;0.509722;,
  0.702249;0.497499;,
  0.743534;0.497499;,
  0.810540;0.497499;,
  0.862500;0.497499;,
  0.914708;0.497499;,
  0.968721;0.498580;,
  1.023615;0.534463;,
  0.996436;0.550664;,
  0.087761;0.535587;,
  0.023615;0.534463;,
  0.142452;0.559145;,
  0.184187;0.575593;,
  0.236508;0.547821;,
  0.320532;0.535251;,
  0.354446;0.534187;,
  0.387591;0.534469;,
  0.463028;0.534179;,
  0.510253;0.533584;,
  0.573561;0.533222;,
  0.635957;0.533218;,
  0.656652;0.552520;,
  0.694645;0.533271;,
  0.743351;0.533230;,
  0.806173;0.533218;,
  0.860580;0.533218;,
  0.918485;0.533218;,
  0.967789;0.534598;,
  1.033830;0.570313;,
  0.995438;0.582114;,
  0.086641;0.569045;,
  0.033830;0.570313;,
  0.148022;0.582083;,
  0.182680;0.588095;,
  0.224521;0.584095;,
  0.298313;0.578509;,
  0.349107;0.585266;,
  0.410286;0.587608;,
  0.460391;0.593625;,
  0.499074;0.587146;,
  0.574823;0.589305;,
  0.638994;0.573066;,
  0.652072;0.580697;,
  0.682420;0.569143;,
  0.712911;0.570056;,
  0.794542;0.568977;,
  0.854678;0.576612;,
  0.904627;0.568936;,
  0.965608;0.568966;,
  1.038251;0.604654;,
  0.998301;0.605004;,
  0.083605;0.604654;,
  0.038251;0.604654;,
  0.153548;0.604757;,
  0.182811;0.604654;,
  0.221144;0.604983;,
  0.288822;0.604723;,
  0.331114;0.604654;,
  0.415772;0.604857;,
  0.463371;0.605129;,
  0.495304;0.604654;,
  0.575742;0.606818;,
  0.628493;0.604654;,
  0.648088;0.604654;,
  0.665580;0.604654;,
  0.688361;0.604654;,
  0.793154;0.604654;,
  0.844316;0.604654;,
  0.899952;0.605428;,
  0.952104;0.604654;,
  0.490375;0.522512;,
  0.631972;0.934320;,
  0.496666;0.957542;,
  0.753417;0.870787;,
  0.849113;0.773162;,
  0.909694;0.651002;,
  0.929229;0.516264;,
  0.905806;0.382138;,
  0.841718;0.261753;,
  0.743237;0.166893;,
  0.620005;0.106843;,
  0.484084;0.087481;,
  0.348779;0.110704;,
  0.227334;0.174237;,
  0.131637;0.271861;,
  0.071056;0.394021;,
  0.051522;0.528759;,
  0.074945;0.662885;,
  0.139033;0.783270;,
  0.237513;0.878131;,
  0.360746;0.938181;,
  0.914916;0.604654;,
  1.083605;0.604654;,
  1.153548;0.604757;,
  1.182811;0.604654;,
  1.221143;0.604983;,
  1.288822;0.604723;,
  1.331114;0.604654;;
 }
}
