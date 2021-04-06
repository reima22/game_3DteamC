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
 63;
 1.52946;-4.99164;5.32297;,
 1.52946;-8.53953;5.32297;,
 1.52946;-9.69455;-4.38100;,
 1.52946;-4.99164;-4.38100;,
 1.52946;-2.87095;-4.38100;,
 1.52946;-2.09720;5.32297;,
 -8.17451;-4.94752;-4.38100;,
 -8.17451;-9.69455;-4.38100;,
 -8.17451;-8.53953;5.32297;,
 -8.17451;-4.94752;5.32297;,
 -8.17451;-2.09720;5.32297;,
 -8.17451;-2.87095;-4.38100;,
 -3.11732;-9.69455;5.32297;,
 1.52946;-8.53953;5.32297;,
 1.52946;-4.99164;5.32297;,
 -3.16504;-4.97029;7.45902;,
 -8.17451;-4.94752;5.32297;,
 -8.17451;-8.53953;5.32297;,
 -3.21535;0.00948;5.32297;,
 -8.17451;-2.09720;5.32297;,
 1.52946;-2.09720;5.32297;,
 -6.03494;-9.69455;-10.30313;,
 -8.17451;-9.69455;-4.38100;,
 -8.17451;-4.94752;-4.38100;,
 -6.05509;-4.95719;-10.30328;,
 -0.44589;-4.98268;-10.27101;,
 1.52946;-4.99164;-4.38100;,
 1.52946;-9.69455;-4.38100;,
 -0.42577;-9.69455;-10.27090;,
 -0.46710;-2.39918;-10.27115;,
 1.52946;-2.87095;-4.38100;,
 -8.17451;-2.87095;-4.38100;,
 -6.07633;-2.39918;-10.30337;,
 -1.83919;-2.39918;-14.31899;,
 -3.21535;-0.54147;-20.90573;,
 -3.21535;-2.39918;-14.31899;,
 -3.21535;-2.39918;-10.28694;,
 -0.46710;-2.39918;-10.27115;,
 -4.65367;-2.39918;-14.31898;,
 -6.07633;-2.39918;-10.30337;,
 -3.11732;-9.69455;-14.35000;,
 -3.11732;-7.72824;-17.15176;,
 -1.77989;-9.69455;-14.35000;,
 -0.42577;-9.69455;-10.27090;,
 -3.11732;-9.69455;-10.28639;,
 -4.57288;-9.69455;-14.35000;,
 -6.03494;-9.69455;-10.30313;,
 -4.61227;-4.96373;-14.33489;,
 -3.16504;-4.97029;-19.33324;,
 -3.11732;-7.72824;-17.15176;,
 -4.57288;-9.69455;-14.35000;,
 -1.77989;-9.69455;-14.35000;,
 -1.80882;-4.97648;-14.33494;,
 -3.21535;-0.54147;-20.90573;,
 -1.83919;-2.39918;-14.31899;,
 -4.65367;-2.39918;-14.31898;,
 -3.11732;-9.69455;5.32297;,
 1.52946;-9.69455;-4.38100;,
 -8.17451;-9.69455;-4.38100;,
 1.52946;-2.87095;-4.38100;,
 -3.21535;0.00948;5.32297;,
 -3.21535;-0.18944;-3.80721;,
 -8.17451;-2.87095;-4.38100;;
 
 42;
 4;0,1,2,3;,
 4;3,4,5,0;,
 4;6,7,8,9;,
 4;9,10,11,6;,
 4;12,13,14,15;,
 4;15,16,17,12;,
 4;18,19,16,15;,
 4;15,14,20,18;,
 4;21,22,23,24;,
 4;25,26,27,28;,
 4;29,30,26,25;,
 4;24,23,31,32;,
 3;33,34,35;,
 4;35,36,37,33;,
 3;35,34,38;,
 4;38,39,36,35;,
 3;40,41,42;,
 4;42,43,44,40;,
 3;45,41,40;,
 4;40,44,46,45;,
 4;47,48,49,50;,
 4;50,21,24,47;,
 4;51,49,48,52;,
 4;52,25,28,51;,
 4;52,48,53,54;,
 4;54,29,25,52;,
 4;55,53,48,47;,
 4;47,24,32,55;,
 3;1,56,57;,
 3;56,44,57;,
 3;44,43,57;,
 3;8,58,56;,
 3;56,58,44;,
 3;58,46,44;,
 3;5,59,60;,
 3;60,59,61;,
 3;61,59,36;,
 3;59,37,36;,
 3;10,60,62;,
 3;60,61,62;,
 3;61,36,62;,
 3;36,39,62;;
 
 MeshMaterialList {
  5;
  42;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
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
  58;
  -0.985382;-0.001988;-0.170350;,
  -0.985143;-0.001018;-0.171735;,
  0.986832;0.001965;-0.161738;,
  0.987063;0.001024;-0.160329;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.985263;-0.001503;-0.171043;,
  0.986948;0.001494;-0.161034;,
  0.000001;0.962453;0.271449;,
  0.000000;-0.818534;-0.574458;,
  0.008320;0.208702;0.977944;,
  0.008081;-0.219535;0.975571;,
  -0.944854;-0.087211;-0.315667;,
  0.008395;-0.006680;0.999942;,
  -0.941988;-0.007195;-0.335571;,
  -0.941008;-0.003693;-0.338364;,
  0.947611;0.007167;-0.319347;,
  0.948582;0.003727;-0.316508;,
  -0.941500;-0.005444;-0.336969;,
  0.948099;0.005447;-0.317929;,
  0.002573;0.997270;-0.073797;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.990569;0.137017;,
  0.000001;0.990569;0.137017;,
  0.000001;0.990569;0.137017;,
  0.000000;-0.953555;-0.301219;,
  0.000000;-0.953555;-0.301219;,
  0.000000;-0.953555;-0.301219;,
  -0.943977;-0.047562;-0.326567;,
  0.951571;-0.025676;-0.306355;,
  0.009105;0.984287;-0.176338;,
  0.266898;-0.211629;0.940201;,
  0.290534;-0.005843;0.956847;,
  -0.274409;-0.006973;0.961588;,
  -0.251287;-0.212446;0.944310;,
  -0.285717;0.198801;0.937467;,
  0.301624;0.200196;0.932172;,
  -0.000230;0.999198;0.040028;,
  -0.000228;0.999213;0.039654;,
  -0.920719;-0.119322;-0.371536;,
  -0.932551;-0.062464;-0.355593;,
  0.942579;-0.042811;-0.331229;,
  0.934150;-0.090944;-0.345098;,
  0.953869;-0.059331;-0.294303;,
  0.969802;-0.027482;-0.242340;,
  0.959616;-0.008522;-0.281185;,
  -0.954266;-0.032614;-0.297173;,
  -0.964515;-0.054687;-0.258303;,
  0.239629;-0.964060;0.114747;,
  0.004685;-0.998283;0.058390;,
  0.080522;-0.996007;0.038558;,
  -0.221174;-0.968399;0.115264;,
  -0.074248;-0.996489;0.038694;,
  0.404723;0.911546;-0.072682;,
  0.345156;0.935335;-0.077568;,
  0.008681;0.998645;-0.051319;,
  -0.389940;0.917927;-0.073191;,
  -0.332829;0.939718;-0.078452;;
  42;
  4;4,4,3,7;,
  4;7,2,4,4;,
  4;6,1,5,5;,
  4;5,5,0,6;,
  4;11,31,32,13;,
  4;13,33,34,11;,
  4;10,35,33,13;,
  4;13,32,36,10;,
  4;15,1,6,18;,
  4;19,7,3,17;,
  4;16,2,7,19;,
  4;18,6,0,14;,
  3;22,8,23;,
  4;23,20,37,22;,
  3;23,8,24;,
  4;24,38,20,23;,
  3;25,9,26;,
  4;26,21,21,25;,
  3;27,9,25;,
  4;25,21,21,27;,
  4;28,12,39,40;,
  4;40,15,18,28;,
  4;41,42,43,29;,
  4;29,19,17,41;,
  4;29,43,44,45;,
  4;45,16,19,29;,
  4;46,47,12,28;,
  4;28,18,14,46;,
  3;48,49,50;,
  3;49,21,50;,
  3;21,21,50;,
  3;51,52,49;,
  3;49,52,21;,
  3;52,21,21;,
  3;53,54,55;,
  3;55,54,30;,
  3;30,54,20;,
  3;54,37,20;,
  3;56,55,57;,
  3;55,30,57;,
  3;30,20,57;,
  3;20,38,57;;
 }
 MeshTextureCoords {
  63;
  1.000000;0.515364;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.515364;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.510818;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.510818;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.478854;1.000000;,
  0.000000;1.000000;,
  0.000000;0.515364;,
  0.483771;0.513165;,
  1.000000;0.510818;,
  1.000000;1.000000;,
  0.488955;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.220484;1.000000;,
  0.000000;1.000000;,
  0.000000;0.510818;,
  0.218408;0.511811;,
  0.796439;0.514439;,
  1.000000;0.515364;,
  1.000000;1.000000;,
  0.798512;1.000000;,
  0.794253;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.216219;0.000000;,
  0.652858;1.000000;,
  0.511046;1.000000;,
  0.511046;0.828712;,
  0.511045;0.658596;,
  0.794253;1.000000;,
  0.362825;1.000000;,
  0.216219;1.000000;,
  0.521146;0.169980;,
  0.521146;0.000000;,
  0.658969;0.000000;,
  0.798512;0.000000;,
  0.521146;0.341428;,
  0.371151;0.000000;,
  0.220484;0.000000;,
  0.367091;0.512487;,
  0.516229;0.513165;,
  0.521146;1.000000;,
  0.371151;1.000000;,
  0.658969;1.000000;,
  0.655988;0.513800;,
  0.511046;0.000000;,
  0.652858;0.000000;,
  0.362825;0.000000;,
  0.521146;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.511045;0.000000;,
  0.511045;0.352614;,
  0.000000;1.000000;;
 }
}
