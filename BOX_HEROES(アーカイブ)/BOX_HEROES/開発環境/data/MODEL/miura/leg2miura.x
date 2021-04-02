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
 35;
 -4.65046;0.05389;-0.65534;,
 -3.65438;0.05541;4.62146;,
 -0.53470;0.05589;3.04762;,
 -0.33442;0.05401;-1.62070;,
 -2.28810;0.05689;-4.96334;,
 -5.18122;0.05613;-4.49138;,
 -8.18662;0.05445;-0.18902;,
 -6.26046;0.05489;3.59754;,
 -6.85958;0.05621;-3.12734;,
 -5.79138;-23.65434;-0.69310;,
 -4.98962;-22.91630;-4.21466;,
 -2.06806;-23.36242;-3.80898;,
 -0.98838;-23.61366;-2.05210;,
 -1.15266;-23.63630;3.24230;,
 -3.31018;-23.44486;4.65330;,
 -7.53242;-23.60570;0.22514;,
 -7.05022;-23.02542;-2.57270;,
 -6.44230;-23.82166;2.26146;,
 -7.03942;-8.80743;-2.46214;,
 -4.93710;-8.78111;-3.75606;,
 -2.02618;-8.77875;-3.95414;,
 -7.66010;-8.84451;0.57882;,
 -0.13122;-8.78231;-2.10162;,
 -6.36630;-8.86323;3.00418;,
 0.16654;-8.80599;3.58986;,
 -3.09694;-8.88095;5.69410;,
 -1.63250;-0.88939;2.87010;,
 -4.34970;-0.79367;3.40458;,
 -3.91854;-1.50119;-0.51010;,
 -0.91570;-1.55627;-1.07218;,
 -6.23770;-0.96027;2.47446;,
 -7.04658;-1.39735;0.03502;,
 -4.67518;-2.15079;-4.17082;,
 -1.73078;-1.94543;-3.02470;,
 -6.82882;-1.84871;-2.48462;;
 
 28;
 4;0,1,2,3;,
 4;4,5,0,3;,
 4;6,7,1,0;,
 4;5,8,6,0;,
 4;9,10,11,12;,
 4;13,14,9,12;,
 4;15,16,10,9;,
 4;14,17,15,9;,
 4;18,8,5,19;,
 4;5,4,20,19;,
 4;21,6,8,18;,
 4;4,3,22,20;,
 4;23,7,6,21;,
 4;3,2,24,22;,
 4;25,1,7,23;,
 4;2,1,25,24;,
 4;10,16,18,19;,
 4;20,11,10,19;,
 4;16,15,21,18;,
 4;22,12,11,20;,
 4;15,17,23,21;,
 4;24,13,12,22;,
 4;17,14,25,23;,
 4;25,14,13,24;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;28,32,33,29;,
 4;31,34,32,28;;
 
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  54;
  -0.000009;1.000000;0.000692;,
  0.000361;1.000000;0.000616;,
  -0.139873;-0.963401;-0.228678;,
  -0.071588;-0.981514;-0.177499;,
  -0.000196;1.000000;-0.000322;,
  0.000020;1.000000;-0.000227;,
  0.036949;-0.998145;-0.048385;,
  -0.020489;-0.999377;0.028733;,
  0.003723;-0.983923;0.178555;,
  -0.001552;-0.984468;0.175555;,
  0.008997;-0.983341;0.181548;,
  -0.001290;-0.984145;0.177364;,
  0.006958;-0.984802;0.173539;,
  0.002834;-0.984484;0.175453;,
  -0.000088;1.000000;-0.000275;,
  0.000176;1.000000;0.000654;,
  0.008239;-0.999918;-0.009838;,
  -0.105831;-0.973384;-0.203282;,
  -0.000102;1.000000;0.000185;,
  0.000044;1.000000;0.000190;,
  -0.046302;-0.996122;-0.074809;,
  0.000190;1.000000;0.000194;,
  -0.049117;-0.993017;-0.107258;,
  -0.051885;-0.988838;-0.139671;,
  -0.321926;-0.036367;-0.946066;,
  -0.823235;-0.025254;-0.567139;,
  0.418213;-0.030422;-0.907839;,
  -0.992808;-0.021778;0.117722;,
  0.943005;-0.011349;-0.332584;,
  -0.746610;-0.020513;0.664945;,
  0.950732;-0.034499;0.308089;,
  -0.564482;-0.021770;0.825158;,
  0.007978;-0.984080;0.177545;,
  0.003278;-0.984205;0.177004;,
  -0.001421;-0.984307;0.176460;,
  -0.804565;-0.058816;-0.590945;,
  -0.356666;-0.086950;-0.930177;,
  0.387094;-0.051259;-0.920614;,
  -0.995958;-0.033207;0.083456;,
  0.944335;0.031578;-0.327466;,
  -0.724884;-0.010141;0.688796;,
  0.998827;0.048206;-0.004475;,
  -0.506672;-0.002272;0.862136;,
  0.492916;0.114110;0.862561;,
  0.519711;0.023253;0.854026;,
  -0.285096;0.015466;-0.958374;,
  -0.840621;0.009188;-0.541546;,
  0.447419;-0.010410;-0.894264;,
  -0.988466;-0.010577;0.151074;,
  0.939906;-0.054312;-0.337086;,
  -0.767110;-0.030674;0.640782;,
  0.878085;-0.080043;0.471762;,
  -0.619419;-0.041157;0.783981;,
  0.541805;-0.067813;0.837764;;
  28;
  4;19,14,4,18;,
  4;0,15,19,18;,
  4;21,5,14,19;,
  4;15,1,21,19;,
  4;22,17,3,20;,
  4;7,16,22,20;,
  4;23,2,17,22;,
  4;16,6,23,22;,
  4;25,35,36,24;,
  4;36,37,26,24;,
  4;27,38,35,25;,
  4;37,39,28,26;,
  4;29,40,38,27;,
  4;39,41,30,28;,
  4;31,42,40,29;,
  4;43,43,44,43;,
  4;45,46,25,24;,
  4;26,47,45,24;,
  4;46,48,27,25;,
  4;28,49,47,26;,
  4;48,50,29,27;,
  4;30,51,49,28;,
  4;50,52,31,29;,
  4;44,53,51,30;,
  4;12,13,33,32;,
  4;13,11,34,33;,
  4;33,8,10,32;,
  4;34,9,8,33;;
 }
 MeshTextureCoords {
  35;
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
