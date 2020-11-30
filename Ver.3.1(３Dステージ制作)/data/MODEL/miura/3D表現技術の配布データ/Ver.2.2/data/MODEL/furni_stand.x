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
 120;
 -62.75400;3.39954;-13.39575;,
 -59.75400;3.39954;-13.39575;,
 -59.75400;3.13775;16.21968;,
 -62.75400;3.13775;16.21968;,
 -59.75400;3.39954;-13.39575;,
 -59.75400;33.39840;-13.13394;,
 -59.75400;33.13661;16.48146;,
 -59.75400;3.13775;16.21968;,
 -59.75400;33.39840;-13.13394;,
 -62.75400;33.39840;-13.13394;,
 -62.75400;33.13661;16.48146;,
 -59.75400;33.13661;16.48146;,
 -62.75400;33.39840;-13.13394;,
 -62.75400;3.39954;-13.39575;,
 -62.75400;3.13775;16.21968;,
 -62.75400;33.13661;16.48146;,
 -59.75400;3.39954;-13.39575;,
 -62.75400;3.39954;-13.39575;,
 -62.75400;3.13775;16.21968;,
 -59.75400;3.13775;16.21968;,
 -1.34250;3.39954;-13.39575;,
 1.65750;3.39954;-13.39575;,
 1.65750;3.13775;16.21968;,
 -1.34250;3.13775;16.21968;,
 1.65750;3.39954;-13.39575;,
 1.65750;33.39840;-13.13394;,
 1.65750;33.13661;16.48146;,
 1.65750;3.13775;16.21968;,
 1.65750;33.39840;-13.13394;,
 -1.34250;33.39840;-13.13394;,
 -1.34250;33.13661;16.48146;,
 1.65750;33.13661;16.48146;,
 -1.34250;33.39840;-13.13394;,
 -1.34250;3.39954;-13.39575;,
 -1.34250;3.13775;16.21968;,
 -1.34250;33.13661;16.48146;,
 1.65750;3.39954;-13.39575;,
 -1.34250;3.39954;-13.39575;,
 -1.34250;3.13775;16.21968;,
 1.65750;3.13775;16.21968;,
 59.44817;3.39954;-13.39575;,
 62.44817;3.39954;-13.39575;,
 62.44817;3.13775;16.21968;,
 59.44817;3.13775;16.21968;,
 62.44817;3.39954;-13.39575;,
 62.44817;33.39840;-13.13394;,
 62.44817;33.13661;16.48146;,
 62.44817;3.13775;16.21968;,
 62.44817;33.39840;-13.13394;,
 59.44817;33.39840;-13.13394;,
 59.44817;33.13661;16.48146;,
 62.44817;33.13661;16.48146;,
 59.44817;33.39840;-13.13394;,
 59.44817;3.39954;-13.39575;,
 59.44817;3.13775;16.21968;,
 59.44817;33.13661;16.48146;,
 62.44817;3.39954;-13.39575;,
 59.44817;3.39954;-13.39575;,
 59.44817;3.13775;16.21968;,
 62.44817;3.13775;16.21968;,
 -62.77251;3.42582;-16.40693;,
 61.99797;3.42582;-16.40693;,
 61.99797;3.39963;-13.40703;,
 -62.77251;3.39963;-13.40703;,
 61.99797;3.42582;-16.40693;,
 61.99797;33.42467;-16.14513;,
 61.99797;33.39850;-13.14525;,
 61.99797;3.39963;-13.40703;,
 61.99797;33.42467;-16.14513;,
 -62.77251;33.42467;-16.14513;,
 -62.77251;33.39850;-13.14525;,
 61.99797;33.39850;-13.14525;,
 -62.77251;33.42467;-16.14513;,
 -62.77251;3.42582;-16.40693;,
 -62.77251;3.39963;-13.40703;,
 -62.77251;33.39850;-13.14525;,
 61.99797;3.42582;-16.40693;,
 -62.77251;3.42582;-16.40693;,
 -62.77251;3.39963;-13.40703;,
 61.99797;3.39963;-13.40703;,
 -62.76000;0.59319;-16.51935;,
 62.04000;0.59319;-16.51935;,
 62.04000;0.30783;16.17941;,
 -62.76000;0.30783;16.17941;,
 62.04000;0.59319;-16.51935;,
 62.04000;3.59307;-16.49318;,
 62.04000;3.30771;16.20557;,
 62.04000;0.30783;16.17941;,
 62.04000;3.59307;-16.49318;,
 -62.76000;3.59307;-16.49318;,
 -62.76000;3.30771;16.20557;,
 62.04000;3.30771;16.20557;,
 -62.76000;3.59307;-16.49318;,
 -62.76000;0.59319;-16.51935;,
 -62.76000;0.30783;16.17941;,
 -62.76000;3.30771;16.20557;,
 62.04000;0.59319;-16.51935;,
 -62.76000;0.59319;-16.51935;,
 -62.76000;0.30783;16.17941;,
 62.04000;0.30783;16.17941;,
 -62.76000;33.63242;-16.23102;,
 62.04000;33.63242;-16.23102;,
 62.04000;33.34708;16.46772;,
 -62.76000;33.34708;16.46772;,
 62.04000;33.63242;-16.23102;,
 62.04000;36.63231;-16.20483;,
 62.04000;36.34695;16.49390;,
 62.04000;33.34708;16.46772;,
 62.04000;36.63231;-16.20483;,
 -62.76000;36.63231;-16.20483;,
 -62.76000;36.34695;16.49390;,
 62.04000;36.34695;16.49390;,
 -62.76000;36.63231;-16.20483;,
 -62.76000;33.63242;-16.23102;,
 -62.76000;33.34708;16.46772;,
 -62.76000;36.34695;16.49390;,
 62.04000;33.63242;-16.23102;,
 -62.76000;33.63242;-16.23102;,
 -62.76000;33.34708;16.46772;,
 62.04000;33.34708;16.46772;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;;
 
 MeshMaterialList {
  1;
  36;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "C:\\Users\\student\\Documents\\3D表\現技術\\01_モデルビューワ\\Ver.2.1\\data\\TEXTURE\\mokume.jpg";
   }
  }
 }
 MeshNormals {
  17;
  0.000000;-0.999961;-0.008839;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.999961;0.008839;,
  0.000000;-0.999962;-0.008730;,
  0.000000;0.999962;0.008725;,
  0.000000;-0.999962;-0.008727;,
  0.000000;0.999962;0.008727;,
  0.000000;-0.999962;-0.008726;,
  0.000000;0.999962;0.008727;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.008727;-0.999962;,
  0.000000;-0.008726;0.999962;,
  0.000000;0.008727;-0.999962;,
  0.000000;0.008725;-0.999962;,
  0.000000;-0.008720;0.999962;,
  0.000000;0.008730;-0.999962;,
  0.000000;-0.008725;0.999962;;
  36;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;9,9,9,9;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;9,9,9,9;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;7,7,7,7;,
  4;1,1,1,1;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;15,15,15,15;,
  4;16,16,16,16;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
