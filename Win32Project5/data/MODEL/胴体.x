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
 52;
 -3.58660;-0.07387;-0.16595;,
 6.40203;-0.07387;-7.17589;,
 -3.58660;-0.07387;-10.07953;,
 10.53946;-0.07387;-0.16595;,
 6.40203;-0.07387;6.84400;,
 -3.58660;-0.07387;9.74763;,
 -13.57521;-0.07387;6.84400;,
 -17.71264;-0.07387;-0.16595;,
 -13.57521;-0.07387;-7.17589;,
 8.16779;-1.10823;-8.41510;,
 -3.58660;-1.10823;-11.83201;,
 13.03661;-1.10823;-0.16595;,
 8.16779;-1.10823;8.08320;,
 -3.58660;-1.10823;11.50011;,
 -15.34098;-1.10823;8.08320;,
 -20.20979;-1.10823;-0.16595;,
 -15.34098;-1.10823;-8.41510;,
 8.89917;-3.60539;-8.92838;,
 -3.58660;-3.60539;-12.55792;,
 14.07096;-3.60539;-0.16595;,
 8.89917;-3.60539;8.59649;,
 -3.58660;-3.60539;15.71134;,
 -16.07236;-3.60539;8.59649;,
 -21.24412;-3.60539;-0.16595;,
 -16.07236;-3.60539;-8.92838;,
 9.30980;-31.85747;-0.16595;,
 5.53253;-31.85747;-8.92838;,
 5.53253;-31.85747;8.59649;,
 -16.48297;-31.85747;-0.16595;,
 -12.70572;-31.85747;8.59649;,
 -12.70572;-31.85747;-8.92838;,
 -3.58660;-31.85747;-12.55792;,
 4.99835;-34.35463;-8.41510;,
 -3.58660;-34.35463;-11.83201;,
 8.55435;-34.35463;-0.16595;,
 4.99835;-34.35463;8.08320;,
 -3.58660;-31.85747;12.22601;,
 -3.58660;-34.35463;11.50011;,
 -12.17155;-34.35463;8.08320;,
 -15.72754;-34.35463;-0.16595;,
 -12.17155;-34.35463;-8.41510;,
 3.70871;-35.38898;-7.17589;,
 -3.58660;-35.38898;-10.07953;,
 6.73053;-35.38898;-0.16595;,
 3.70871;-35.38898;6.84400;,
 -3.58660;-35.38898;9.74763;,
 -10.88190;-35.38898;6.84400;,
 -13.90372;-35.38898;-0.16595;,
 -10.88190;-35.38898;-7.17589;,
 -3.58660;-35.38898;-0.16595;,
 -3.58660;-17.72175;-17.42228;,
 -3.58660;-9.21108;17.65664;;
 
 64;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;17,19,25,26;,
 4;19,20,27,25;,
 4;22,23,28,29;,
 4;23,24,30,28;,
 4;31,26,32,33;,
 4;26,25,34,32;,
 4;25,27,35,34;,
 4;27,36,37,35;,
 4;36,29,38,37;,
 4;29,28,39,38;,
 4;28,30,40,39;,
 4;30,31,33,40;,
 4;33,32,41,42;,
 4;32,34,43,41;,
 4;34,35,44,43;,
 4;35,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,33,42,48;,
 3;42,41,49;,
 3;41,43,49;,
 3;43,44,49;,
 3;44,45,49;,
 3;45,46,49;,
 3;46,47,49;,
 3;47,48,49;,
 3;48,42,49;,
 3;31,50,26;,
 3;26,50,17;,
 3;50,18,17;,
 3;36,27,51;,
 3;27,20,51;,
 3;20,21,51;,
 3;36,51,29;,
 3;29,51,22;,
 3;51,21,22;,
 3;31,30,50;,
 3;30,24,50;,
 3;24,18,50;;
 
 MeshMaterialList {
  5;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.382400;0.661600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.075200;0.140800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.746400;0.800000;0.166400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.084800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  52;
  0.000000;1.000000;0.000000;,
  0.000000;0.965060;-0.262028;,
  0.134666;0.972994;-0.187475;,
  0.192662;0.981265;-0.000000;,
  0.134666;0.972994;0.187475;,
  -0.000000;0.965060;0.262028;,
  -0.134666;0.972994;0.187475;,
  -0.192662;0.981265;-0.000000;,
  -0.134666;0.972994;-0.187475;,
  0.000000;0.617485;-0.786583;,
  0.449853;0.663190;-0.598174;,
  0.691540;0.722338;-0.000000;,
  0.439877;0.724598;0.530533;,
  -0.000000;0.752189;0.658948;,
  -0.439878;0.724598;0.530533;,
  -0.691541;0.722337;-0.000000;,
  -0.449853;0.663190;-0.598174;,
  0.000000;0.302566;-0.953129;,
  0.617962;0.156140;-0.770548;,
  0.992453;0.122628;-0.000000;,
  0.663760;0.218648;0.715273;,
  0.000000;0.482113;0.876109;,
  -0.663760;0.218648;0.715273;,
  -0.992453;0.122626;-0.000000;,
  -0.617962;0.156139;-0.770547;,
  -0.000000;-0.302374;-0.953189;,
  0.657117;-0.219305;-0.721181;,
  0.976072;-0.217446;-0.000000;,
  0.656626;-0.200481;0.727084;,
  -0.000000;-0.256253;0.966610;,
  -0.656626;-0.200480;0.727083;,
  -0.976073;-0.217444;-0.000000;,
  -0.657118;-0.219304;-0.721181;,
  -0.000000;-0.620815;-0.783957;,
  0.542106;-0.626893;-0.559578;,
  0.774020;-0.633161;-0.000000;,
  0.542105;-0.626893;0.559578;,
  -0.000000;-0.620814;0.783958;,
  -0.542106;-0.626892;0.559578;,
  -0.774022;-0.633159;-0.000000;,
  -0.542107;-0.626892;-0.559578;,
  0.000000;-0.965391;-0.260807;,
  0.178088;-0.966520;-0.184728;,
  0.252276;-0.967655;-0.000000;,
  0.178088;-0.966520;0.184728;,
  -0.000000;-0.965391;0.260807;,
  -0.178088;-0.966520;0.184728;,
  -0.252276;-0.967655;-0.000000;,
  -0.178088;-0.966520;-0.184728;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-0.024734;-0.999694;,
  -0.000000;-0.000440;1.000000;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  3;41,42,49;,
  3;42,43,49;,
  3;43,44,49;,
  3;44,45,49;,
  3;45,46,49;,
  3;46,47,49;,
  3;47,48,49;,
  3;48,41,49;,
  3;25,50,26;,
  3;26,50,18;,
  3;50,17,18;,
  3;29,28,51;,
  3;28,20,51;,
  3;20,21,51;,
  3;29,51,30;,
  3;30,51,22;,
  3;51,21,22;,
  3;25,32,50;,
  3;32,24,50;,
  3;24,17,50;;
 }
 MeshTextureCoords {
  52;
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
