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
 102;
 -2.17724;-0.16968;-43.96969;,
 -0.55425;86.80067;-44.43945;,
 3.12672;86.78920;-44.43440;,
 1.50376;-0.18105;-43.96465;,
 -0.58288;85.74590;-43.39404;,
 -2.16621;0.89677;-42.93574;,
 1.51479;0.88541;-42.93070;,
 3.09818;85.73452;-43.38902;,
 -1.27273;87.28209;40.81495;,
 2.40829;87.27070;40.81992;,
 -1.28376;86.21563;39.78096;,
 2.39726;86.20424;39.78598;,
 -2.89572;0.31178;41.28462;,
 0.78522;0.30038;41.28963;,
 -2.86719;1.36652;40.23920;,
 0.81386;1.35513;40.24420;,
 -2.17724;-0.16968;-43.96969;,
 1.50376;-0.18105;-43.96465;,
 -2.16621;0.89677;-42.93574;,
 1.51479;0.88541;-42.93070;,
 -0.58288;85.74590;-43.39404;,
 -0.55425;86.80067;-44.43945;,
 1.50376;-0.18105;-43.96465;,
 3.12672;86.78920;-44.43440;,
 3.09818;85.73452;-43.38902;,
 1.51479;0.88541;-42.93070;,
 -1.28376;86.21563;39.78096;,
 -1.27273;87.28209;40.81495;,
 2.40829;87.27070;40.81992;,
 2.39726;86.20424;39.78598;,
 -2.86719;1.36652;40.23920;,
 -2.89572;0.31178;41.28462;,
 0.78522;0.30038;41.28963;,
 0.81386;1.35513;40.24420;,
 -0.16313;0.69391;-43.33488;,
 0.56394;85.94636;-43.56628;,
 2.21296;85.93512;-43.56373;,
 1.48590;0.68276;-43.33241;,
 0.56485;83.09689;-42.14723;,
 -0.11332;3.57461;-41.93143;,
 1.46333;3.56396;-41.92904;,
 2.14153;83.08616;-42.14490;,
 0.24208;86.41828;-1.57720;,
 1.89112;86.40711;-1.57478;,
 0.26465;83.53709;-2.98055;,
 1.84131;83.52637;-2.97815;,
 -0.48500;1.16586;-1.34589;,
 1.16401;1.15468;-1.34340;,
 -0.41356;4.01487;-2.76477;,
 1.16311;4.00421;-2.76237;,
 -0.16313;0.69391;-43.33488;,
 1.48590;0.68276;-43.33241;,
 -0.11332;3.57461;-41.93143;,
 1.46333;3.56396;-41.92904;,
 0.56485;83.09689;-42.14723;,
 0.56394;85.94636;-43.56628;,
 1.48590;0.68276;-43.33241;,
 2.21296;85.93512;-43.56373;,
 2.14153;83.08616;-42.14490;,
 1.46333;3.56396;-41.92904;,
 0.26465;83.53709;-2.98055;,
 0.24208;86.41828;-1.57720;,
 1.89112;86.40711;-1.57478;,
 1.84131;83.52637;-2.97815;,
 -0.41356;4.01487;-2.76477;,
 -0.48500;1.16586;-1.34589;,
 1.16401;1.15468;-1.34340;,
 1.16311;4.00421;-2.76237;,
 -2.28470;0.69391;-1.77520;,
 -1.55763;85.94636;-2.00660;,
 0.09139;85.93512;-2.00406;,
 -0.63567;0.68276;-1.77274;,
 -1.55672;83.09689;-0.58755;,
 -2.23490;3.57461;-0.37176;,
 -0.65824;3.56396;-0.36936;,
 0.01996;83.08616;-0.58522;,
 -1.87950;86.41828;39.98248;,
 -0.23046;86.40711;39.98489;,
 -1.85692;83.53709;38.57913;,
 -0.28026;83.52637;38.58153;,
 -2.60657;1.16586;40.21378;,
 -0.95757;1.15468;40.21628;,
 -2.53513;4.01487;38.79491;,
 -0.95847;4.00421;38.79731;,
 -2.28470;0.69391;-1.77520;,
 -0.63567;0.68276;-1.77274;,
 -2.23490;3.57461;-0.37176;,
 -0.65824;3.56396;-0.36936;,
 -1.55672;83.09689;-0.58755;,
 -1.55763;85.94636;-2.00660;,
 -0.63567;0.68276;-1.77274;,
 0.09139;85.93512;-2.00406;,
 0.01996;83.08616;-0.58522;,
 -0.65824;3.56396;-0.36936;,
 -1.85692;83.53709;38.57913;,
 -1.87950;86.41828;39.98248;,
 -0.23046;86.40711;39.98489;,
 -0.28026;83.52637;38.58153;,
 -2.53513;4.01487;38.79491;,
 -2.60657;1.16586;40.21378;,
 -0.95757;1.15468;40.21628;,
 -0.95847;4.00421;38.79731;;
 
 48;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,4,7,11;,
 4;8,12,13,9;,
 4;14,10,11,15;,
 4;12,16,17,13;,
 4;18,14,15,19;,
 4;0,5,20,21;,
 4;22,23,24,25;,
 4;21,20,26,27;,
 4;23,28,29,24;,
 4;27,26,30,31;,
 4;28,32,33,29;,
 4;31,30,5,0;,
 4;32,22,25,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;35,42,43,36;,
 4;44,38,41,45;,
 4;42,46,47,43;,
 4;48,44,45,49;,
 4;46,50,51,47;,
 4;52,48,49,53;,
 4;34,39,54,55;,
 4;56,57,58,59;,
 4;55,54,60,61;,
 4;57,62,63,58;,
 4;61,60,64,65;,
 4;62,66,67,63;,
 4;65,64,39,34;,
 4;66,56,59,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;69,76,77,70;,
 4;78,72,75,79;,
 4;76,80,81,77;,
 4;82,78,79,83;,
 4;80,84,85,81;,
 4;86,82,83,87;,
 4;68,73,88,89;,
 4;90,91,92,93;,
 4;89,88,94,95;,
 4;91,96,97,92;,
 4;95,94,98,99;,
 4;96,100,101,97;,
 4;99,98,73,68;,
 4;100,90,93,101;;
 
 MeshMaterialList {
  2;
  48;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1;;
  Material {
   0.800000;0.781176;0.796863;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\3D表\現技術\\01_モデルビューワ\\Ver.2.1\\data\\TEXTURE\\mokume.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.001354;-0.005427;-0.999984;,
  0.003112;0.999979;-0.005621;,
  -0.001340;0.005425;0.999984;,
  -0.001350;0.005427;0.999984;,
  -0.003102;-0.999979;0.005621;,
  0.001344;-0.005426;-0.999984;,
  -0.003100;-0.999979;0.005621;,
  0.003098;0.999979;-0.005621;,
  -0.999790;0.018606;-0.008549;,
  -0.999790;0.018627;-0.008549;,
  0.999790;-0.018635;0.008525;,
  0.999791;-0.018605;0.008524;,
  -0.999790;0.018627;-0.008528;,
  0.999790;-0.018605;0.008555;,
  -0.999791;0.018607;-0.008528;,
  0.999790;-0.018635;0.008555;,
  0.001500;-0.002727;-0.999995;,
  0.006812;0.999914;-0.011187;,
  -0.001470;0.002726;0.999995;,
  -0.001477;0.002727;0.999995;,
  -0.006816;-0.999914;0.011186;,
  0.001504;-0.002726;-0.999995;,
  -0.006784;-0.999914;0.011187;,
  0.006775;0.999914;-0.011188;,
  -0.999877;0.014856;0.004985;,
  -0.999984;0.002228;0.005127;,
  0.999787;-0.002158;0.020505;,
  0.999678;-0.014785;0.020645;,
  -0.999787;0.002157;-0.020506;,
  0.999877;-0.014856;-0.004984;,
  -0.999678;0.014785;-0.020647;,
  0.999984;-0.002230;-0.005125;,
  0.001497;-0.002727;-0.999995;,
  0.006812;0.999914;-0.011187;,
  -0.001469;0.002726;0.999995;,
  -0.001480;0.002727;0.999995;,
  -0.006816;-0.999914;0.011186;,
  0.001503;-0.002726;-0.999995;,
  -0.006784;-0.999914;0.011187;,
  0.006775;0.999914;-0.011188;,
  -0.999877;0.014856;0.004985;,
  -0.999984;0.002228;0.005127;,
  0.999787;-0.002158;0.020505;,
  0.999678;-0.014785;0.020645;,
  -0.999787;0.002157;-0.020506;,
  0.999877;-0.014856;-0.004984;,
  -0.999677;0.014785;-0.020647;,
  0.999984;-0.002230;-0.005125;;
  48;
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,9,9;,
  4;10,11,11,10;,
  4;9,9,12,12;,
  4;11,13,13,11;,
  4;12,12,14,14;,
  4;13,15,15,13;,
  4;14,14,8,8;,
  4;15,10,10,15;,
  4;16,16,16,16;,
  4;19,19,19,19;,
  4;17,17,17,17;,
  4;20,20,20,20;,
  4;18,18,18,18;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,25,25;,
  4;26,27,27,26;,
  4;25,25,28,28;,
  4;27,29,29,27;,
  4;28,28,30,30;,
  4;29,31,31,29;,
  4;30,30,24,24;,
  4;31,26,26,31;,
  4;32,32,32,32;,
  4;35,35,35,35;,
  4;33,33,33,33;,
  4;36,36,36,36;,
  4;34,34,34,34;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,41,41;,
  4;42,43,43,42;,
  4;41,41,44,44;,
  4;43,45,45,43;,
  4;44,44,46,46;,
  4;45,47,47,45;,
  4;46,46,40,40;,
  4;47,42,42,47;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
