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
 36;
 3.33193;1.67001;3.23436;,
 3.38505;1.66753;0.60844;,
 5.25441;4.59721;0.59408;,
 4.81156;3.56577;2.31380;,
 2.31469;0.16729;2.81928;,
 1.66737;-0.98867;0.50068;,
 3.47933;1.22733;-2.67388;,
 4.53412;3.03405;-1.52192;,
 2.26305;-0.39007;-1.18860;,
 2.16957;2.37181;3.55752;,
 12.42697;-5.63207;2.46900;,
 14.22721;-4.04215;2.27568;,
 3.38673;4.28977;2.67584;,
 0.91553;0.71205;2.61476;,
 10.92425;-7.11227;2.58168;,
 2.55453;2.29249;-2.47640;,
 12.43536;-5.53015;-2.40708;,
 10.84433;-7.24115;-2.45808;,
 1.14893;0.36849;-1.48500;,
 3.61917;3.86073;-1.34748;,
 14.06601;-4.21391;-2.37028;,
 12.40104;-5.67383;0.32792;,
 14.22173;-4.02071;-0.04764;,
 3.91236;4.91881;1.05880;,
 2.30077;2.29829;0.74084;,
 0.44269;-0.04831;0.94736;,
 10.83085;-7.15519;0.08208;,
 11.09997;-6.65675;0.22436;,
 11.15161;-6.40531;1.85232;,
 12.90884;-4.86631;2.21824;,
 12.38441;-5.42047;0.06608;,
 12.44164;-5.28327;-2.25100;,
 11.06833;-6.72123;-1.42400;,
 13.49153;-4.33055;1.10140;,
 13.58061;-4.19687;-0.07108;,
 13.39329;-4.35179;-1.57208;;
 
 28;
 4;0,1,2,3;,
 4;0,4,5,1;,
 4;1,6,7,2;,
 4;1,5,8,6;,
 4;9,10,11,12;,
 4;9,13,14,10;,
 4;15,16,17,18;,
 4;15,19,20,16;,
 3;21,17,20;,
 4;22,23,12,11;,
 4;22,20,19,23;,
 3;22,11,21;,
 3;22,21,20;,
 4;23,24,9,12;,
 4;23,19,15,24;,
 4;24,25,13,9;,
 4;24,15,18,25;,
 4;25,26,14,13;,
 4;25,18,17,26;,
 4;26,21,10,14;,
 4;27,28,29,30;,
 4;27,30,31,32;,
 3;21,11,10;,
 3;21,26,17;,
 3;33,34,30;,
 3;33,30,29;,
 3;35,31,30;,
 3;35,30,34;;
 
 MeshMaterialList {
  1;
  28;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.780800;0.800000;0.787200;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  46;
  -0.082524;-0.177087;0.980729;,
  0.834758;-0.540833;0.103335;,
  0.817404;-0.574348;-0.044441;,
  0.832212;-0.553794;0.027114;,
  0.834776;-0.541624;0.098956;,
  0.180830;0.144482;0.972844;,
  -0.141941;-0.125309;-0.981912;,
  0.427497;0.579470;-0.693873;,
  0.828494;-0.559219;0.029533;,
  0.834049;-0.548073;0.063077;,
  0.825403;-0.564478;-0.008670;,
  0.831407;-0.553729;0.046331;,
  0.834769;-0.541230;0.101146;,
  0.050251;-0.016666;0.998598;,
  0.002273;0.061844;-0.998083;,
  0.678461;-0.734553;0.011102;,
  0.628112;0.778091;-0.007043;,
  -0.815422;0.573664;-0.077438;,
  -0.793650;0.603727;-0.075057;,
  -0.592381;-0.803229;0.062506;,
  -0.684973;0.727525;-0.038992;,
  -0.675887;0.734431;-0.061547;,
  -0.706811;0.707257;0.014349;,
  -0.705463;0.708734;0.004401;,
  -0.713714;0.700115;0.021254;,
  -0.691183;0.722113;-0.028594;,
  -0.702189;0.711990;-0.001126;,
  -0.703732;0.710450;0.004615;,
  -0.711064;0.702826;0.020583;,
  0.683857;-0.729077;0.028043;,
  0.679063;-0.733750;0.022015;,
  0.621496;0.747318;0.235073;,
  0.672653;-0.739948;0.003914;,
  0.666824;-0.745214;-0.000916;,
  -0.836068;0.542804;-0.079712;,
  -0.818245;0.571881;-0.058542;,
  -0.850055;0.523113;-0.061314;,
  -0.821310;0.561996;-0.098036;,
  -0.812303;0.575234;-0.096276;,
  -0.783655;0.618706;-0.055570;,
  -0.803086;0.588324;-0.094490;,
  -0.567203;-0.781478;0.259948;,
  -0.593811;-0.792779;-0.137442;,
  0.689248;-0.724423;0.012201;,
  0.678683;-0.734430;0.001341;,
  0.694671;-0.719317;-0.003910;;
  28;
  4;10,11,8,2;,
  4;10,3,9,11;,
  4;11,12,1,8;,
  4;11,9,4,12;,
  4;13,13,5,5;,
  4;13,0,0,13;,
  4;14,14,6,6;,
  4;14,7,7,14;,
  3;15,29,30;,
  4;16,16,31,31;,
  4;16,7,7,16;,
  3;32,33,15;,
  3;32,15,30;,
  4;34,17,35,36;,
  4;34,37,38,17;,
  4;17,18,39,35;,
  4;17,38,40,18;,
  4;19,19,41,41;,
  4;19,42,42,19;,
  4;43,15,44,45;,
  4;25,21,20,26;,
  4;25,26,22,23;,
  3;15,33,44;,
  3;15,43,29;,
  3;27,24,26;,
  3;27,26,20;,
  3;28,22,26;,
  3;28,26,24;;
 }
 MeshTextureCoords {
  36;
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
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
