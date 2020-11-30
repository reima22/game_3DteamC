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
 286;
 0.00000;50.00000;-9.00000;,
 3.44412;50.00000;-8.31492;,
 2.94664;37.50000;-7.11388;,
 0.00000;37.50000;-7.70000;,
 6.36399;50.00000;-6.36399;,
 5.44475;37.50000;-5.44475;,
 8.31492;50.00000;-3.44412;,
 7.11388;37.50000;-2.94664;,
 9.00000;50.00000;0.00000;,
 7.70000;37.50000;0.00000;,
 8.31492;50.00000;3.44412;,
 7.11388;37.50000;2.94664;,
 6.36399;50.00000;6.36399;,
 5.44475;37.50000;5.44475;,
 3.44412;50.00000;8.31492;,
 2.94664;37.50000;7.11388;,
 0.00000;50.00000;9.00000;,
 0.00000;37.50000;7.70000;,
 -3.44412;50.00000;8.31492;,
 -2.94664;37.50000;7.11388;,
 -6.36399;50.00000;6.36399;,
 -5.44475;37.50000;5.44475;,
 -8.31492;50.00000;3.44412;,
 -7.11388;37.50000;2.94664;,
 -9.00000;50.00000;0.00000;,
 -7.70000;37.50000;0.00000;,
 -8.31492;50.00000;-3.44412;,
 -7.11388;37.50000;-2.94664;,
 -6.36399;50.00000;-6.36399;,
 -5.44475;37.50000;-5.44475;,
 -3.44412;50.00000;-8.31492;,
 -2.94664;37.50000;-7.11388;,
 0.00000;50.00000;-9.00000;,
 0.00000;37.50000;-7.70000;,
 2.87010;25.00000;-6.92910;,
 0.00000;25.00000;-7.50000;,
 5.30333;25.00000;-5.30333;,
 6.92910;25.00000;-2.87010;,
 7.50000;25.00000;0.00000;,
 6.92910;25.00000;2.87010;,
 5.30333;25.00000;5.30333;,
 2.87010;25.00000;6.92910;,
 0.00000;25.00000;7.50000;,
 -2.87010;25.00000;6.92910;,
 -5.30333;25.00000;5.30333;,
 -6.92910;25.00000;2.87010;,
 -7.50000;25.00000;0.00000;,
 -6.92910;25.00000;-2.87010;,
 -5.30333;25.00000;-5.30333;,
 -2.87010;25.00000;-6.92910;,
 0.00000;25.00000;-7.50000;,
 3.44412;12.50000;-8.31492;,
 0.00000;12.50000;-9.00000;,
 6.36399;12.50000;-6.36399;,
 8.31492;12.50000;-3.44412;,
 9.00000;12.50000;0.00000;,
 8.31492;12.50000;3.44412;,
 6.36399;12.50000;6.36399;,
 3.44412;12.50000;8.31492;,
 0.00000;12.50000;9.00000;,
 -3.44412;12.50000;8.31492;,
 -6.36399;12.50000;6.36399;,
 -8.31492;12.50000;3.44412;,
 -9.00000;12.50000;0.00000;,
 -8.31492;12.50000;-3.44412;,
 -6.36399;12.50000;-6.36399;,
 -3.44412;12.50000;-8.31492;,
 0.00000;12.50000;-9.00000;,
 4.30515;0.00000;-10.39365;,
 0.00000;0.00000;-11.25000;,
 7.95499;0.00000;-7.95499;,
 10.39365;0.00000;-4.30515;,
 11.25000;0.00000;0.00000;,
 10.39365;0.00000;4.30515;,
 7.95499;0.00000;7.95499;,
 4.30515;0.00000;10.39365;,
 0.00000;0.00000;11.25000;,
 -4.30515;0.00000;10.39365;,
 -7.95499;0.00000;7.95499;,
 -10.39365;0.00000;4.30515;,
 -11.25000;0.00000;0.00000;,
 -10.39365;0.00000;-4.30515;,
 -7.95499;0.00000;-7.95499;,
 -4.30515;0.00000;-10.39365;,
 0.00000;0.00000;-11.25000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;30.00000;-22.50000;,
 0.00000;42.50000;-30.62500;,
 11.71968;42.50000;-28.29379;,
 8.61039;30.00000;-20.78730;,
 21.65513;42.50000;-21.65513;,
 15.90989;30.00000;-15.90989;,
 28.29379;42.50000;-11.71968;,
 20.78730;30.00000;-8.61039;,
 30.62500;42.50000;0.00000;,
 22.50000;30.00000;0.00000;,
 28.29379;42.50000;11.71968;,
 20.78730;30.00000;8.61039;,
 21.65513;42.50000;21.65513;,
 15.90989;30.00000;15.90989;,
 11.71968;42.50000;28.29379;,
 8.61039;30.00000;20.78730;,
 0.00000;42.50000;30.62500;,
 0.00000;30.00000;22.50000;,
 -11.71968;42.50000;28.29379;,
 -8.61039;30.00000;20.78730;,
 -21.65513;42.50000;21.65513;,
 -15.90989;30.00000;15.90993;,
 -28.29379;42.50000;11.71968;,
 -20.78730;30.00000;8.61039;,
 -30.62500;42.50000;0.00000;,
 -22.50000;30.00000;0.00000;,
 -28.29379;42.50000;-11.71968;,
 -20.78730;30.00000;-8.61039;,
 -21.65513;42.50000;-21.65513;,
 -15.90989;30.00000;-15.90993;,
 -11.71968;42.50000;-28.29379;,
 -8.61034;30.00000;-20.78730;,
 0.00000;42.50000;-30.62500;,
 0.00000;30.00000;-22.50000;,
 0.00000;55.00000;-33.75000;,
 12.91554;55.00000;-31.18095;,
 23.86485;55.00000;-23.86485;,
 31.18095;55.00000;-12.91554;,
 33.75000;55.00000;0.00000;,
 31.18095;55.00000;12.91554;,
 23.86485;55.00000;23.86485;,
 12.91554;55.00000;31.18095;,
 0.00000;55.00000;33.75000;,
 -12.91554;55.00000;31.18095;,
 -23.86485;55.00000;23.86485;,
 -31.18095;55.00000;12.91554;,
 -33.75000;55.00000;0.00000;,
 -31.18095;55.00000;-12.91554;,
 -23.86485;55.00000;-23.86485;,
 -12.91554;55.00000;-31.18095;,
 0.00000;55.00000;-33.75000;,
 0.00000;67.50000;-31.25000;,
 11.95890;67.50000;-28.87120;,
 22.09710;67.50000;-22.09710;,
 28.87120;67.50000;-11.95890;,
 31.25000;67.50000;0.00000;,
 28.87120;67.50000;11.95890;,
 22.09710;67.50000;22.09710;,
 11.95890;67.50000;28.87120;,
 0.00000;67.50000;31.25000;,
 -11.95890;67.50000;28.87120;,
 -22.09710;67.50000;22.09710;,
 -28.87120;67.50000;11.95890;,
 -31.25000;67.50000;0.00000;,
 -28.87120;67.50000;-11.95890;,
 -22.09710;67.50000;-22.09710;,
 -11.95880;67.50000;-28.87120;,
 0.00000;67.50000;-31.25000;,
 0.00000;80.00000;-27.50000;,
 10.52381;80.00000;-25.40670;,
 19.44547;80.00000;-19.44547;,
 25.40670;80.00000;-10.52381;,
 27.50000;80.00000;0.00000;,
 25.40670;80.00000;10.52381;,
 19.44547;80.00000;19.44547;,
 10.52381;80.00000;25.40670;,
 0.00000;80.00000;27.50000;,
 -10.52381;80.00000;25.40670;,
 -19.44547;80.00000;19.44547;,
 -25.40670;80.00000;10.52381;,
 -27.50000;80.00000;0.00000;,
 -25.40670;80.00000;-10.52381;,
 -19.44547;80.00000;-19.44547;,
 -10.52381;80.00000;-25.40670;,
 0.00000;80.00000;-27.50000;,
 0.00000;92.50000;-22.50000;,
 8.61036;92.50000;-20.78724;,
 15.90996;92.50000;-15.90996;,
 20.78724;92.50000;-8.61036;,
 22.50000;92.50000;0.00000;,
 20.78724;92.50000;8.61036;,
 15.90996;92.50000;15.90996;,
 8.61036;92.50000;20.78724;,
 0.00000;92.50000;22.50000;,
 -8.61036;92.50000;20.78724;,
 -15.90984;92.50000;15.90996;,
 -20.78724;92.50000;8.61036;,
 -22.50000;92.50000;0.00000;,
 -20.78724;92.50000;-8.61036;,
 -15.90984;92.50000;-15.90996;,
 -8.61036;92.50000;-20.78724;,
 0.00000;92.50000;-22.50000;,
 0.00000;105.00000;-16.25000;,
 6.21855;105.00000;-15.01305;,
 11.49044;105.00000;-11.49044;,
 15.01305;105.00000;-6.21855;,
 16.25000;105.00000;0.00000;,
 15.01305;105.00000;6.21855;,
 11.49044;105.00000;11.49044;,
 6.21855;105.00000;15.01305;,
 0.00000;105.00000;16.25000;,
 -6.21855;105.00000;15.01305;,
 -11.49044;105.00000;11.49044;,
 -15.01305;105.00000;6.21855;,
 -16.25000;105.00000;0.00000;,
 -15.01305;105.00000;-6.21855;,
 -11.49044;105.00000;-11.49044;,
 -6.21855;105.00000;-15.01305;,
 0.00000;105.00000;-16.25000;,
 0.00000;117.50000;-9.37500;,
 3.58770;117.50000;-8.66130;,
 6.62910;117.50000;-6.62910;,
 8.66130;117.50000;-3.58770;,
 9.37500;117.50000;0.00000;,
 8.66130;117.50000;3.58770;,
 6.62910;117.50000;6.62910;,
 3.58770;117.50000;8.66130;,
 0.00000;117.50000;9.37500;,
 -3.58770;117.50000;8.66130;,
 -6.62910;117.50000;6.62910;,
 -8.66130;117.50000;3.58770;,
 -9.37500;117.50000;0.00000;,
 -8.66130;117.50000;-3.58770;,
 -6.62910;117.50000;-6.62910;,
 -3.58770;117.50000;-8.66130;,
 0.00000;117.50000;-9.37500;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;128.43988;0.00000;,
 0.00000;23.77610;0.00000;,
 0.00000;30.00000;-22.50000;,
 8.61039;30.00000;-20.78730;,
 15.90989;30.00000;-15.90989;,
 20.78730;30.00000;-8.61039;,
 22.50000;30.00000;0.00000;,
 20.78730;30.00000;8.61039;,
 15.90989;30.00000;15.90989;,
 8.61039;30.00000;20.78730;,
 0.00000;30.00000;22.50000;,
 -8.61039;30.00000;20.78730;,
 -15.90989;30.00000;15.90993;,
 -20.78730;30.00000;8.61039;,
 -22.50000;30.00000;0.00000;,
 -20.78730;30.00000;-8.61039;,
 -15.90989;30.00000;-15.90993;,
 -8.61034;30.00000;-20.78730;;
 
 240;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
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
 4;3,2,34,35;,
 4;2,5,36,34;,
 4;5,7,37,36;,
 4;7,9,38,37;,
 4;9,11,39,38;,
 4;11,13,40,39;,
 4;13,15,41,40;,
 4;15,17,42,41;,
 4;17,19,43,42;,
 4;19,21,44,43;,
 4;21,23,45,44;,
 4;23,25,46,45;,
 4;25,27,47,46;,
 4;27,29,48,47;,
 4;29,31,49,48;,
 4;31,33,50,49;,
 4;35,34,51,52;,
 4;34,36,53,51;,
 4;36,37,54,53;,
 4;37,38,55,54;,
 4;38,39,56,55;,
 4;39,40,57,56;,
 4;40,41,58,57;,
 4;41,42,59,58;,
 4;42,43,60,59;,
 4;43,44,61,60;,
 4;44,45,62,61;,
 4;45,46,63,62;,
 4;46,47,64,63;,
 4;47,48,65,64;,
 4;48,49,66,65;,
 4;49,50,67,66;,
 4;52,51,68,69;,
 4;51,53,70,68;,
 4;53,54,71,70;,
 4;54,55,72,71;,
 4;55,56,73,72;,
 4;56,57,74,73;,
 4;57,58,75,74;,
 4;58,59,76,75;,
 4;59,60,77,76;,
 4;60,61,78,77;,
 4;61,62,79,78;,
 4;62,63,80,79;,
 4;63,64,81,80;,
 4;64,65,82,81;,
 4;65,66,83,82;,
 4;66,67,84,83;,
 3;85,1,0;,
 3;86,4,1;,
 3;87,6,4;,
 3;88,8,6;,
 3;89,10,8;,
 3;90,12,10;,
 3;91,14,12;,
 3;92,16,14;,
 3;93,18,16;,
 3;94,20,18;,
 3;95,22,20;,
 3;96,24,22;,
 3;97,26,24;,
 3;98,28,26;,
 3;99,30,28;,
 3;100,32,30;,
 3;101,69,68;,
 3;102,68,70;,
 3;103,70,71;,
 3;104,71,72;,
 3;105,72,73;,
 3;106,73,74;,
 3;107,74,75;,
 3;108,75,76;,
 3;109,76,77;,
 3;110,77,78;,
 3;111,78,79;,
 3;112,79,80;,
 3;113,80,81;,
 3;114,81,82;,
 3;115,82,83;,
 3;116,83,84;,
 4;117,118,119,120;,
 4;120,119,121,122;,
 4;122,121,123,124;,
 4;124,123,125,126;,
 4;126,125,127,128;,
 4;128,127,129,130;,
 4;130,129,131,132;,
 4;132,131,133,134;,
 4;134,133,135,136;,
 4;136,135,137,138;,
 4;138,137,139,140;,
 4;140,139,141,142;,
 4;142,141,143,144;,
 4;144,143,145,146;,
 4;146,145,147,148;,
 4;148,147,149,150;,
 4;118,151,152,119;,
 4;119,152,153,121;,
 4;121,153,154,123;,
 4;123,154,155,125;,
 4;125,155,156,127;,
 4;127,156,157,129;,
 4;129,157,158,131;,
 4;131,158,159,133;,
 4;133,159,160,135;,
 4;135,160,161,137;,
 4;137,161,162,139;,
 4;139,162,163,141;,
 4;141,163,164,143;,
 4;143,164,165,145;,
 4;145,165,166,147;,
 4;147,166,167,149;,
 4;151,168,169,152;,
 4;152,169,170,153;,
 4;153,170,171,154;,
 4;154,171,172,155;,
 4;155,172,173,156;,
 4;156,173,174,157;,
 4;157,174,175,158;,
 4;158,175,176,159;,
 4;159,176,177,160;,
 4;160,177,178,161;,
 4;161,178,179,162;,
 4;162,179,180,163;,
 4;163,180,181,164;,
 4;164,181,182,165;,
 4;165,182,183,166;,
 4;166,183,184,167;,
 4;168,185,186,169;,
 4;169,186,187,170;,
 4;170,187,188,171;,
 4;171,188,189,172;,
 4;172,189,190,173;,
 4;173,190,191,174;,
 4;174,191,192,175;,
 4;175,192,193,176;,
 4;176,193,194,177;,
 4;177,194,195,178;,
 4;178,195,196,179;,
 4;179,196,197,180;,
 4;180,197,198,181;,
 4;181,198,199,182;,
 4;182,199,200,183;,
 4;183,200,201,184;,
 4;185,202,203,186;,
 4;186,203,204,187;,
 4;187,204,205,188;,
 4;188,205,206,189;,
 4;189,206,207,190;,
 4;190,207,208,191;,
 4;191,208,209,192;,
 4;192,209,210,193;,
 4;193,210,211,194;,
 4;194,211,212,195;,
 4;195,212,213,196;,
 4;196,213,214,197;,
 4;197,214,215,198;,
 4;198,215,216,199;,
 4;199,216,217,200;,
 4;200,217,218,201;,
 4;202,219,220,203;,
 4;203,220,221,204;,
 4;204,221,222,205;,
 4;205,222,223,206;,
 4;206,223,224,207;,
 4;207,224,225,208;,
 4;208,225,226,209;,
 4;209,226,227,210;,
 4;210,227,228,211;,
 4;211,228,229,212;,
 4;212,229,230,213;,
 4;213,230,231,214;,
 4;214,231,232,215;,
 4;215,232,233,216;,
 4;216,233,234,217;,
 4;217,234,235,218;,
 4;219,236,237,220;,
 4;220,237,238,221;,
 4;221,238,239,222;,
 4;222,239,240,223;,
 4;223,240,241,224;,
 4;224,241,242,225;,
 4;225,242,243,226;,
 4;226,243,244,227;,
 4;227,244,245,228;,
 4;228,245,246,229;,
 4;229,246,247,230;,
 4;230,247,248,231;,
 4;231,248,249,232;,
 4;232,249,250,233;,
 4;233,250,251,234;,
 4;234,251,252,235;,
 3;236,253,237;,
 3;237,254,238;,
 3;238,255,239;,
 3;239,256,240;,
 3;240,257,241;,
 3;241,258,242;,
 3;242,259,243;,
 3;243,260,244;,
 3;244,261,245;,
 3;245,262,246;,
 3;246,263,247;,
 3;247,264,248;,
 3;248,265,249;,
 3;249,266,250;,
 3;250,267,251;,
 3;251,268,252;,
 3;269,270,271;,
 3;269,271,272;,
 3;269,272,273;,
 3;269,273,274;,
 3;269,274,275;,
 3;269,275,276;,
 3;269,276,277;,
 3;269,277,278;,
 3;269,278,279;,
 3;269,279,280;,
 3;269,280,281;,
 3;269,281,282;,
 3;269,282,283;,
 3;269,283,284;,
 3;269,284,285;,
 3;269,285,270;;
 
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.313600;0.100000;0.050400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\wood000.jpg";
   }
  }
  Material {
   0.100000;0.376800;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\leaf000.jpg";
   }
  }
 }
 MeshNormals {
  214;
  0.000000;1.000000;0.000000;,
  0.000000;-0.103442;-0.994636;,
  0.380624;-0.103442;-0.918926;,
  0.703313;-0.103443;-0.703313;,
  0.918926;-0.103442;-0.380624;,
  0.994636;-0.103442;-0.000000;,
  0.918926;-0.103442;0.380624;,
  0.703313;-0.103443;0.703313;,
  0.380624;-0.103442;0.918926;,
  0.000000;-0.103442;0.994636;,
  -0.380624;-0.103442;0.918926;,
  -0.703313;-0.103443;0.703313;,
  -0.918926;-0.103442;0.380624;,
  -0.994636;-0.103442;0.000000;,
  -0.918926;-0.103442;-0.380624;,
  -0.703313;-0.103443;-0.703313;,
  -0.380624;-0.103442;-0.918926;,
  0.000000;-0.059782;-0.998212;,
  0.381992;-0.059782;-0.922230;,
  0.705842;-0.059782;-0.705842;,
  0.922230;-0.059782;-0.381992;,
  0.998212;-0.059782;-0.000000;,
  0.922230;-0.059782;0.381992;,
  0.705842;-0.059782;0.705842;,
  0.381992;-0.059782;0.922230;,
  0.000000;-0.059782;0.998212;,
  -0.381992;-0.059782;0.922230;,
  -0.705842;-0.059782;0.705842;,
  -0.922230;-0.059782;0.381992;,
  -0.998212;-0.059782;0.000000;,
  -0.922230;-0.059782;-0.381992;,
  -0.705842;-0.059782;-0.705842;,
  -0.381992;-0.059782;-0.922230;,
  0.000000;0.051701;-0.998663;,
  0.382165;0.051701;-0.922647;,
  0.706161;0.051701;-0.706161;,
  0.922647;0.051701;-0.382165;,
  0.998663;0.051701;0.000000;,
  0.922647;0.051701;0.382165;,
  0.706161;0.051701;0.706161;,
  0.382165;0.051701;0.922647;,
  0.000000;0.051701;0.998663;,
  -0.382165;0.051701;0.922647;,
  -0.706161;0.051701;0.706161;,
  -0.922647;0.051701;0.382165;,
  -0.998663;0.051701;0.000000;,
  -0.922647;0.051701;-0.382165;,
  -0.706161;0.051701;-0.706161;,
  -0.382165;0.051701;-0.922647;,
  0.000000;0.148218;-0.988955;,
  0.378450;0.148217;-0.913678;,
  0.699297;0.148218;-0.699297;,
  0.913678;0.148217;-0.378450;,
  0.988955;0.148218;0.000000;,
  0.913678;0.148217;0.378450;,
  0.699297;0.148218;0.699297;,
  0.378450;0.148217;0.913678;,
  0.000000;0.148218;0.988955;,
  -0.378450;0.148217;0.913678;,
  -0.699297;0.148218;0.699297;,
  -0.913678;0.148217;0.378450;,
  -0.988955;0.148218;0.000000;,
  -0.913678;0.148217;-0.378450;,
  -0.699297;0.148218;-0.699297;,
  -0.378450;0.148217;-0.913678;,
  0.000000;0.177153;-0.984183;,
  0.376624;0.177153;-0.909270;,
  0.695923;0.177154;-0.695923;,
  0.909270;0.177153;-0.376624;,
  0.984183;0.177153;0.000000;,
  0.909270;0.177153;0.376624;,
  0.695923;0.177154;0.695923;,
  0.376624;0.177153;0.909270;,
  0.000000;0.177153;0.984183;,
  -0.376624;0.177153;0.909270;,
  -0.695923;0.177154;0.695923;,
  -0.909270;0.177153;0.376624;,
  -0.984183;0.177153;0.000000;,
  -0.909270;0.177153;-0.376624;,
  -0.695923;0.177154;-0.695923;,
  -0.376624;0.177153;-0.909270;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-0.808138;-0.588993;,
  0.225399;-0.808138;-0.544158;,
  0.416481;-0.808138;-0.416481;,
  0.544158;-0.808138;-0.225399;,
  0.588993;-0.808138;-0.000000;,
  0.544158;-0.808138;0.225399;,
  0.416481;-0.808138;0.416481;,
  0.225399;-0.808138;0.544158;,
  0.000000;-0.808138;0.588993;,
  -0.225398;-0.808138;0.544159;,
  -0.416481;-0.808138;0.416481;,
  -0.544159;-0.808138;0.225398;,
  -0.588993;-0.808138;0.000000;,
  -0.544159;-0.808138;-0.225398;,
  -0.416481;-0.808138;-0.416482;,
  -0.225398;-0.808138;-0.544159;,
  -0.000000;-0.399580;-0.916698;,
  0.350806;-0.399580;-0.846918;,
  0.648204;-0.399580;-0.648204;,
  0.846918;-0.399580;-0.350806;,
  0.916698;-0.399580;-0.000000;,
  0.846918;-0.399580;0.350806;,
  0.648204;-0.399580;0.648204;,
  0.350806;-0.399580;0.846918;,
  0.000000;-0.399580;0.916698;,
  -0.350806;-0.399580;0.846919;,
  -0.648204;-0.399580;0.648204;,
  -0.846919;-0.399580;0.350806;,
  -0.916698;-0.399580;0.000000;,
  -0.846919;-0.399580;-0.350806;,
  -0.648203;-0.399580;-0.648204;,
  -0.350805;-0.399580;-0.846919;,
  -0.000000;-0.023833;-0.999716;,
  0.382575;-0.023833;-0.923617;,
  0.706906;-0.023834;-0.706906;,
  0.923617;-0.023833;-0.382575;,
  0.999716;-0.023833;-0.000000;,
  0.923617;-0.023833;0.382575;,
  0.706906;-0.023834;0.706906;,
  0.382575;-0.023833;0.923617;,
  0.000000;-0.023833;0.999716;,
  -0.382575;-0.023833;0.923617;,
  -0.706906;-0.023834;0.706906;,
  -0.923617;-0.023833;0.382575;,
  -0.999716;-0.023833;0.000000;,
  -0.923617;-0.023833;-0.382575;,
  -0.706906;-0.023833;-0.706906;,
  -0.382575;-0.023833;-0.923617;,
  -0.000000;0.242019;-0.970272;,
  0.371307;0.242018;-0.896414;,
  0.686086;0.242017;-0.686086;,
  0.896414;0.242018;-0.371307;,
  0.970272;0.242019;0.000000;,
  0.896414;0.242018;0.371307;,
  0.686086;0.242017;0.686086;,
  0.371307;0.242018;0.896414;,
  0.000000;0.242019;0.970272;,
  -0.371307;0.242018;0.896414;,
  -0.686086;0.242017;0.686086;,
  -0.896414;0.242018;0.371307;,
  -0.970272;0.242019;0.000000;,
  -0.896414;0.242018;-0.371307;,
  -0.686085;0.242018;-0.686087;,
  -0.371306;0.242018;-0.896415;,
  -0.000000;0.329718;-0.944079;,
  0.361282;0.329718;-0.872216;,
  0.667565;0.329718;-0.667565;,
  0.872216;0.329718;-0.361282;,
  0.944079;0.329719;0.000000;,
  0.872216;0.329718;0.361282;,
  0.667565;0.329718;0.667565;,
  0.361282;0.329718;0.872216;,
  0.000000;0.329719;0.944079;,
  -0.361282;0.329719;0.872216;,
  -0.667564;0.329720;0.667565;,
  -0.872216;0.329719;0.361283;,
  -0.944079;0.329719;0.000000;,
  -0.872216;0.329719;-0.361283;,
  -0.667564;0.329719;-0.667565;,
  -0.361282;0.329718;-0.872216;,
  0.000000;0.409679;-0.912230;,
  0.349093;0.409679;-0.842791;,
  0.645043;0.409681;-0.645043;,
  0.842791;0.409679;-0.349093;,
  0.912230;0.409679;0.000000;,
  0.842791;0.409679;0.349093;,
  0.645043;0.409681;0.645043;,
  0.349093;0.409679;0.842791;,
  0.000000;0.409679;0.912230;,
  -0.349095;0.409680;0.842790;,
  -0.645043;0.409681;0.645044;,
  -0.842790;0.409680;0.349096;,
  -0.912230;0.409679;0.000000;,
  -0.842790;0.409680;-0.349096;,
  -0.645043;0.409681;-0.645044;,
  -0.349095;0.409680;-0.842790;,
  0.000000;0.464661;-0.885489;,
  0.338864;0.464661;-0.818084;,
  0.626135;0.464662;-0.626135;,
  0.818084;0.464661;-0.338864;,
  0.885489;0.464661;0.000000;,
  0.818084;0.464661;0.338864;,
  0.626135;0.464662;0.626135;,
  0.338864;0.464661;0.818084;,
  0.000000;0.464661;0.885489;,
  -0.338865;0.464661;0.818084;,
  -0.626135;0.464661;0.626135;,
  -0.818084;0.464660;0.338865;,
  -0.885489;0.464661;0.000000;,
  -0.818084;0.464660;-0.338865;,
  -0.626135;0.464661;-0.626135;,
  -0.338865;0.464661;-0.818084;,
  0.000000;0.569479;-0.822006;,
  0.314574;0.569477;-0.759433;,
  0.581247;0.569477;-0.581247;,
  0.759433;0.569477;-0.314574;,
  0.822006;0.569479;0.000000;,
  0.759433;0.569477;0.314574;,
  0.581247;0.569477;0.581247;,
  0.314574;0.569477;0.759433;,
  0.000000;0.569479;0.822006;,
  -0.314574;0.569477;0.759433;,
  -0.581247;0.569477;0.581247;,
  -0.759433;0.569477;0.314574;,
  -0.822006;0.569479;0.000000;,
  -0.759433;0.569477;-0.314574;,
  -0.581247;0.569477;-0.581247;,
  -0.314574;0.569477;-0.759433;,
  0.637148;0.760250;-0.126736;,
  0.000000;-1.000000;-0.000000;,
  -0.540147;0.760251;0.360914;,
  -0.290588;0.650708;-0.701525;;
  240;
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,16,32,31;,
  4;16,1,17,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,32,48,47;,
  4;32,17,33,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,48,64,63;,
  4;48,33,49,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,64,80,79;,
  4;64,49,65,80;,
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
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  3;81,81,81;,
  4;82,98,99,83;,
  4;83,99,100,84;,
  4;84,100,101,85;,
  4;85,101,102,86;,
  4;86,102,103,87;,
  4;87,103,104,88;,
  4;88,104,105,89;,
  4;89,105,106,90;,
  4;90,106,107,91;,
  4;91,107,108,92;,
  4;92,108,109,93;,
  4;93,109,110,94;,
  4;94,110,111,95;,
  4;95,111,112,96;,
  4;96,112,113,97;,
  4;97,113,98,82;,
  4;98,114,115,99;,
  4;99,115,116,100;,
  4;100,116,117,101;,
  4;101,117,118,102;,
  4;102,118,119,103;,
  4;103,119,120,104;,
  4;104,120,121,105;,
  4;105,121,122,106;,
  4;106,122,123,107;,
  4;107,123,124,108;,
  4;108,124,125,109;,
  4;109,125,126,110;,
  4;110,126,127,111;,
  4;111,127,128,112;,
  4;112,128,129,113;,
  4;113,129,114,98;,
  4;114,130,131,115;,
  4;115,131,132,116;,
  4;116,132,133,117;,
  4;117,133,134,118;,
  4;118,134,135,119;,
  4;119,135,136,120;,
  4;120,136,137,121;,
  4;121,137,138,122;,
  4;122,138,139,123;,
  4;123,139,140,124;,
  4;124,140,141,125;,
  4;125,141,142,126;,
  4;126,142,143,127;,
  4;127,143,144,128;,
  4;128,144,145,129;,
  4;129,145,130,114;,
  4;130,146,147,131;,
  4;131,147,148,132;,
  4;132,148,149,133;,
  4;133,149,150,134;,
  4;134,150,151,135;,
  4;135,151,152,136;,
  4;136,152,153,137;,
  4;137,153,154,138;,
  4;138,154,155,139;,
  4;139,155,156,140;,
  4;140,156,157,141;,
  4;141,157,158,142;,
  4;142,158,159,143;,
  4;143,159,160,144;,
  4;144,160,161,145;,
  4;145,161,146,130;,
  4;146,162,163,147;,
  4;147,163,164,148;,
  4;148,164,165,149;,
  4;149,165,166,150;,
  4;150,166,167,151;,
  4;151,167,168,152;,
  4;152,168,169,153;,
  4;153,169,170,154;,
  4;154,170,171,155;,
  4;155,171,172,156;,
  4;156,172,173,157;,
  4;157,173,174,158;,
  4;158,174,175,159;,
  4;159,175,176,160;,
  4;160,176,177,161;,
  4;161,177,162,146;,
  4;162,178,179,163;,
  4;163,179,180,164;,
  4;164,180,181,165;,
  4;165,181,182,166;,
  4;166,182,183,167;,
  4;167,183,184,168;,
  4;168,184,185,169;,
  4;169,185,186,170;,
  4;170,186,187,171;,
  4;171,187,188,172;,
  4;172,188,189,173;,
  4;173,189,190,174;,
  4;174,190,191,175;,
  4;175,191,192,176;,
  4;176,192,193,177;,
  4;177,193,178,162;,
  4;178,194,195,179;,
  4;179,195,196,180;,
  4;180,196,197,181;,
  4;181,197,198,182;,
  4;182,198,199,183;,
  4;183,199,200,184;,
  4;184,200,201,185;,
  4;185,201,202,186;,
  4;186,202,203,187;,
  4;187,203,204,188;,
  4;188,204,205,189;,
  4;189,205,206,190;,
  4;190,206,207,191;,
  4;191,207,208,192;,
  4;192,208,209,193;,
  4;193,209,194,178;,
  3;194,210,195;,
  3;195,210,196;,
  3;196,210,197;,
  3;197,210,198;,
  3;198,210,199;,
  3;199,210,200;,
  3;200,210,201;,
  3;201,212,202;,
  3;202,212,203;,
  3;203,212,204;,
  3;204,212,205;,
  3;205,212,206;,
  3;206,212,207;,
  3;207,212,208;,
  3;208,213,209;,
  3;209,213,194;,
  3;211,82,83;,
  3;211,83,84;,
  3;211,84,85;,
  3;211,85,86;,
  3;211,86,87;,
  3;211,87,88;,
  3;211,88,89;,
  3;211,89,90;,
  3;211,90,91;,
  3;211,91,92;,
  3;211,92,93;,
  3;211,93,94;,
  3;211,94,95;,
  3;211,95,96;,
  3;211,96,97;,
  3;211,97,82;;
 }
 MeshTextureCoords {
  286;
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;0.250000;,
  0.000000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.187500;0.000000;,
  0.187500;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.312500;0.000000;,
  0.312500;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.437500;0.000000;,
  0.437500;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.562500;0.000000;,
  0.562500;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.687500;0.000000;,
  0.687500;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.812500;0.000000;,
  0.812500;0.250000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.937500;0.000000;,
  0.937500;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.062500;0.500000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.187500;0.500000;,
  0.250000;0.500000;,
  0.312500;0.500000;,
  0.375000;0.500000;,
  0.437500;0.500000;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.687500;0.500000;,
  0.750000;0.500000;,
  0.812500;0.500000;,
  0.875000;0.500000;,
  0.937500;0.500000;,
  1.000000;0.500000;,
  0.062500;0.750000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.187500;0.750000;,
  0.250000;0.750000;,
  0.312500;0.750000;,
  0.375000;0.750000;,
  0.437500;0.750000;,
  0.500000;0.750000;,
  0.562500;0.750000;,
  0.625000;0.750000;,
  0.687500;0.750000;,
  0.750000;0.750000;,
  0.812500;0.750000;,
  0.875000;0.750000;,
  0.937500;0.750000;,
  1.000000;0.750000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.031250;0.000000;,
  0.093750;0.000000;,
  0.156250;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.906250;0.000000;,
  0.968750;0.000000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;,
  0.000000;1.000000;,
  0.000000;0.875000;,
  0.062500;0.875000;,
  0.062500;1.000000;,
  0.125000;0.875000;,
  0.125000;1.000000;,
  0.187500;0.875000;,
  0.187500;1.000000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.312500;0.875000;,
  0.312500;1.000000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.437500;0.875000;,
  0.437500;1.000000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.562500;0.875000;,
  0.562500;1.000000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.687500;0.875000;,
  0.687500;1.000000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.812500;0.875000;,
  0.812500;1.000000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  0.937500;0.875000;,
  0.937500;1.000000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.062500;0.750000;,
  0.125000;0.750000;,
  0.187500;0.750000;,
  0.250000;0.750000;,
  0.312500;0.750000;,
  0.375000;0.750000;,
  0.437500;0.750000;,
  0.500000;0.750000;,
  0.562500;0.750000;,
  0.625000;0.750000;,
  0.687500;0.750000;,
  0.750000;0.750000;,
  0.812500;0.750000;,
  0.875000;0.750000;,
  0.937500;0.750000;,
  1.000000;0.750000;,
  0.000000;0.625000;,
  0.062500;0.625000;,
  0.125000;0.625000;,
  0.187500;0.625000;,
  0.250000;0.625000;,
  0.312500;0.625000;,
  0.375000;0.625000;,
  0.437500;0.625000;,
  0.500000;0.625000;,
  0.562500;0.625000;,
  0.625000;0.625000;,
  0.687500;0.625000;,
  0.750000;0.625000;,
  0.812500;0.625000;,
  0.875000;0.625000;,
  0.937500;0.625000;,
  1.000000;0.625000;,
  0.000000;0.500000;,
  0.062500;0.500000;,
  0.125000;0.500000;,
  0.187500;0.500000;,
  0.250000;0.500000;,
  0.312500;0.500000;,
  0.375000;0.500000;,
  0.437500;0.500000;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.687500;0.500000;,
  0.750000;0.500000;,
  0.812500;0.500000;,
  0.875000;0.500000;,
  0.937500;0.500000;,
  1.000000;0.500000;,
  0.000000;0.375000;,
  0.062500;0.375000;,
  0.125000;0.375000;,
  0.187500;0.375000;,
  0.250000;0.375000;,
  0.312500;0.375000;,
  0.375000;0.375000;,
  0.437500;0.375000;,
  0.500000;0.375000;,
  0.562500;0.375000;,
  0.625000;0.375000;,
  0.687500;0.375000;,
  0.750000;0.375000;,
  0.812500;0.375000;,
  0.875000;0.375000;,
  0.937500;0.375000;,
  1.000000;0.375000;,
  0.000000;0.250000;,
  0.062500;0.250000;,
  0.125000;0.250000;,
  0.187500;0.250000;,
  0.250000;0.250000;,
  0.312500;0.250000;,
  0.375000;0.250000;,
  0.437500;0.250000;,
  0.500000;0.250000;,
  0.562500;0.250000;,
  0.625000;0.250000;,
  0.687500;0.250000;,
  0.750000;0.250000;,
  0.812500;0.250000;,
  0.875000;0.250000;,
  0.937500;0.250000;,
  1.000000;0.250000;,
  0.000000;0.125000;,
  0.062500;0.125000;,
  0.125000;0.125000;,
  0.187500;0.125000;,
  0.250000;0.125000;,
  0.312500;0.125000;,
  0.375000;0.125000;,
  0.437500;0.125000;,
  0.500000;0.125000;,
  0.562500;0.125000;,
  0.625000;0.125000;,
  0.687500;0.125000;,
  0.750000;0.125000;,
  0.812500;0.125000;,
  0.875000;0.125000;,
  0.937500;0.125000;,
  1.000000;0.125000;,
  0.031250;0.000000;,
  0.062500;0.000000;,
  0.093750;0.000000;,
  0.125000;0.000000;,
  0.156250;0.000000;,
  0.187500;0.000000;,
  0.218750;0.000000;,
  0.250000;0.000000;,
  0.281250;0.000000;,
  0.312500;0.000000;,
  0.343750;0.000000;,
  0.375000;0.000000;,
  0.406250;0.000000;,
  0.437500;0.000000;,
  0.468750;0.000000;,
  0.500000;0.000000;,
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
  0.000000;0.000000;;
 }
}
