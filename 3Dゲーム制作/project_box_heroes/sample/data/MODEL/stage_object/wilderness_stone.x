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
 23;
 5.38938;37.00084;-2.54807;,
 30.23114;27.53391;-9.22610;,
 -2.14090;27.53391;-10.06813;,
 5.38938;37.00084;-2.54807;,
 20.74243;27.53391;14.93522;,
 5.38938;37.00084;-2.54807;,
 -36.73802;27.53391;-0.98636;,
 5.38938;37.00084;-2.54807;,
 -19.45238;27.53391;-9.22610;,
 5.38938;37.00084;-2.54807;,
 -2.14090;27.53391;-10.06813;,
 45.58419;9.15089;-13.35334;,
 -2.14090;9.15089;-23.42415;,
 30.23114;9.15089;25.74047;,
 -46.22672;9.15089;9.81891;,
 -34.80545;9.15089;-13.35334;,
 -2.14090;9.15089;-23.42415;,
 52.20153;0.82193;-14.84274;,
 -2.40321;0.82193;-36.90417;,
 34.63528;0.82193;39.22048;,
 -52.84406;0.82193;17.20239;,
 -39.77639;0.82193;-14.84274;,
 -2.40321;0.82193;-36.90417;;
 
 18;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 4;2,1,11,12;,
 4;1,4,13,11;,
 4;4,6,14,13;,
 4;6,8,15,14;,
 4;8,10,16,15;,
 4;12,11,17,18;,
 4;11,13,19,17;,
 4;13,14,20,19;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 3;19,20,17;,
 3;20,21,17;,
 3;21,22,17;;
 
 MeshMaterialList {
  1;
  18;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.520800;0.228800;0.068800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  -0.078175;0.724842;-0.684466;,
  -0.016133;0.564670;-0.825159;,
  0.064452;0.548884;-0.833410;,
  0.229366;0.808523;0.541925;,
  -0.184461;0.666515;0.722310;,
  -0.284619;0.633428;-0.719556;,
  -0.035382;0.595644;-0.802469;,
  0.173117;0.576449;-0.798585;,
  0.504831;0.741210;0.442440;,
  -0.174401;0.647624;0.741733;,
  -0.520116;0.525279;-0.673470;,
  -0.046799;0.686627;-0.725502;,
  0.235229;0.660601;-0.712933;,
  0.331596;0.799747;0.500449;,
  -0.141093;0.772092;0.619650;,
  -0.599506;0.582084;-0.549337;,
  0.121820;0.913674;0.387763;,
  0.596963;0.767250;0.234441;,
  -0.469965;0.661186;-0.584778;,
  0.745406;0.604357;0.281289;,
  -0.202214;0.502751;0.840447;,
  -0.751395;0.413723;-0.514042;,
  0.725230;0.636735;0.261937;,
  -0.815188;0.449653;-0.365076;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;;
  18;
  3;0,2,1;,
  3;16,3,17;,
  3;16,4,3;,
  3;0,5,18;,
  3;0,1,5;,
  4;1,2,7,6;,
  4;17,3,8,19;,
  4;3,4,9,20;,
  4;18,5,10,21;,
  4;5,1,6,10;,
  4;6,7,12,11;,
  4;19,8,13,22;,
  4;8,9,14,13;,
  4;21,10,15,23;,
  4;10,6,11,15;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,25,24;;
 }
 MeshTextureCoords {
  23;
  0.100000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.300000;0.000000;,
  0.400000;0.200000;,
  0.500000;0.000000;,
  0.600000;0.200000;,
  0.700000;0.000000;,
  0.800000;0.200000;,
  0.900000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.400000;0.400000;,
  0.600000;0.400000;,
  0.800000;0.400000;,
  1.000000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;;
 }
}
