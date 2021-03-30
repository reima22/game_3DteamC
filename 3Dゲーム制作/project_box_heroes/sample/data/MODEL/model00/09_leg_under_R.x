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
 153;
 5.02438;2.57472;-12.67078;,
 7.86217;2.09948;-14.20443;,
 8.79213;-5.84443;-12.59843;,
 6.44742;-6.44787;-10.66068;,
 6.60808;-9.53328;-9.21925;,
 2.57164;3.04783;-9.83003;,
 4.47610;-7.12189;-7.63524;,
 4.58699;6.68270;-12.49778;,
 4.62389;-6.60892;-6.87441;,
 2.96689;3.00675;-8.93096;,
 6.82041;-9.10782;-8.36512;,
 8.58141;-11.66657;-7.41460;,
 8.78582;-12.21899;-8.01563;,
 6.83464;8.11300;-13.49457;,
 4.62482;6.29575;-11.58553;,
 6.69598;7.70393;-12.55375;,
 9.55686;3.36052;-11.68983;,
 10.56763;-5.72069;-9.76602;,
 8.79213;-5.84443;-12.59843;,
 7.86217;2.09948;-14.20443;,
 10.54586;-8.85589;-8.39597;,
 10.46146;4.39881;-8.13197;,
 11.13264;-5.95246;-6.20052;,
 8.74514;7.41040;-11.59601;,
 10.40079;-5.59372;-5.62702;,
 10.02849;4.18244;-7.41030;,
 9.90555;-8.55419;-7.72208;,
 8.58141;-11.66657;-7.41460;,
 8.78582;-12.21899;-8.01563;,
 6.83464;8.11300;-13.49457;,
 8.38051;6.94562;-10.84588;,
 6.69598;7.70393;-12.55375;,
 4.62482;6.29575;-11.58553;,
 7.55897;-0.78905;-10.24852;,
 6.69598;7.70393;-12.55375;,
 8.38051;6.94562;-10.84588;,
 8.58141;-11.66657;-7.41460;,
 9.90555;-8.55419;-7.72208;,
 6.82041;-9.10782;-8.36512;,
 10.02849;4.18244;-7.41030;,
 10.40079;-5.59372;-5.62702;,
 2.96689;3.00675;-8.93096;,
 4.62389;-6.60892;-6.87441;,
 0.93208;-5.19498;-2.92426;,
 1.33325;-2.08340;-3.47747;,
 3.35034;-6.25178;-5.93520;,
 3.95564;-12.68689;-4.89572;,
 8.56168;-13.01905;-6.34024;,
 7.95706;-6.87853;-7.42362;,
 1.66731;-12.43416;-1.41275;,
 1.09047;-4.15646;0.71183;,
 2.01963;-11.20044;2.34022;,
 3.50845;-16.37531;2.10268;,
 6.60930;-23.65045;-3.53238;,
 5.45171;-23.65391;-1.35412;,
 9.66599;-23.24390;-4.99382;,
 12.21615;-22.60641;-2.83570;,
 12.55330;-28.38532;-2.78173;,
 12.98479;-28.07463;-0.51432;,
 12.66564;-22.28804;-0.32376;,
 13.21401;-10.60777;0.01848;,
 12.26193;-11.50996;-3.33254;,
 12.13025;-3.23656;-0.80103;,
 11.46215;-4.84779;-4.52233;,
 8.97654;-3.02101;1.88445;,
 9.75242;-9.72077;3.36255;,
 10.26647;-15.61177;3.06955;,
 10.74425;-22.53846;1.93181;,
 10.20188;-28.86766;-4.61359;,
 5.04786;-9.61702;5.61045;,
 4.47532;-3.48539;3.44587;,
 6.22571;-16.40403;4.90410;,
 7.93491;-0.93935;0.86646;,
 4.62898;-1.67312;1.58259;,
 7.44248;-23.19561;2.86756;,
 7.95706;-6.87853;-7.42362;,
 7.69910;0.02938;-9.15479;,
 10.56655;0.00052;-1.96099;,
 8.86943;0.59079;-1.58748;,
 9.36481;1.74582;-4.30637;,
 11.10502;-28.18104;1.46313;,
 11.46564;-33.82374;1.41700;,
 13.30381;-33.86133;-0.55863;,
 8.22815;-33.06960;2.08550;,
 9.96945;-36.60933;4.33248;,
 7.85144;-36.13369;4.59810;,
 10.74760;-40.99970;5.23265;,
 12.89635;-40.65195;2.57080;,
 12.63557;-37.76678;2.17972;,
 8.10428;-41.45483;5.65287;,
 14.17594;-39.97645;-0.46467;,
 13.67330;-43.47257;2.72475;,
 14.99127;-42.54786;-0.64386;,
 15.16724;-43.38574;-4.66446;,
 14.12426;-40.39155;-4.12235;,
 11.74602;-40.77288;-6.85387;,
 12.89044;-34.16409;-3.05994;,
 10.73782;-34.49132;-4.89236;,
 7.84526;-34.78148;-4.19269;,
 7.22733;-29.21599;-3.52619;,
 6.84336;-35.03207;-2.04986;,
 6.14760;-29.34304;-1.49354;,
 6.77920;-41.16126;-2.65181;,
 8.12079;-41.02817;-5.55874;,
 7.95853;-44.25897;-6.29904;,
 6.55454;-43.34987;-2.88186;,
 6.33739;-41.88311;0.81489;,
 6.34865;-38.28337;0.73570;,
 6.66499;-34.36074;0.44529;,
 6.12894;-28.88554;0.61788;,
 8.22815;-33.06960;2.08550;,
 7.83533;-28.13259;2.30803;,
 6.55735;-37.11091;3.31838;,
 7.85144;-36.13369;4.59810;,
 8.10428;-41.45483;5.65287;,
 6.29630;-41.77666;4.18458;,
 6.36034;-44.91603;1.08724;,
 6.76498;-43.05745;3.06699;,
 5.59276;-23.41046;0.82684;,
 7.44248;-23.19561;2.86756;,
 6.22571;-16.40403;4.90410;,
 5.04786;-9.61702;5.61045;,
 4.47532;-3.48539;3.44587;,
 2.39596;-1.74624;0.36970;,
 4.62898;-1.67312;1.58259;,
 1.55283;-1.87564;-1.03776;,
 1.82395;-0.40090;-2.57276;,
 2.34052;0.51832;-4.99489;,
 3.65553;0.67951;-7.50386;,
 7.69910;0.02938;-9.15479;,
 6.29630;-41.77666;4.18458;,
 6.76498;-43.05745;3.06699;,
 8.80017;-42.23887;3.09611;,
 6.36034;-44.91603;1.08724;,
 8.10428;-41.45483;5.65287;,
 10.74760;-40.99970;5.23265;,
 11.63582;-41.65691;3.77374;,
 13.67330;-43.47257;2.72475;,
 9.85697;1.43003;-7.05385;,
 7.83533;-28.13259;2.30803;,
 11.63582;-41.65691;3.77374;,
 7.69910;0.02938;-9.15479;,
 7.12736;0.15609;-6.91966;,
 9.85697;1.43003;-7.05385;,
 7.93491;-0.93935;0.86646;,
 4.62898;-1.67312;1.58259;,
 3.65553;0.67951;-7.50386;,
 2.39596;-1.74624;0.36970;,
 2.34052;0.51832;-4.99489;,
 1.82395;-0.40090;-2.57276;,
 8.86943;0.59079;-1.58748;,
 9.36481;1.74582;-4.30637;,
 11.75662;-42.49268;-6.51162;;
 
 204;
 3;0,1,2;,
 3;2,3,0;,
 3;2,4,3;,
 3;5,0,3;,
 3;3,6,5;,
 3;4,6,3;,
 3;0,5,7;,
 3;5,6,8;,
 3;8,9,5;,
 3;6,4,10;,
 3;11,10,4;,
 3;4,12,11;,
 3;10,8,6;,
 3;1,0,7;,
 3;1,7,13;,
 3;2,12,4;,
 3;9,14,7;,
 3;14,15,13;,
 3;13,7,14;,
 3;7,5,9;,
 3;16,17,18;,
 3;18,19,16;,
 3;18,17,20;,
 3;17,16,21;,
 3;20,17,22;,
 3;21,22,17;,
 3;16,23,21;,
 3;24,22,21;,
 3;21,25,24;,
 3;25,21,23;,
 3;26,20,22;,
 3;20,26,27;,
 3;27,28,20;,
 3;19,23,16;,
 3;19,29,23;,
 3;18,20,28;,
 3;22,24,26;,
 3;30,23,29;,
 3;29,31,30;,
 3;23,30,25;,
 3;32,33,34;,
 3;35,34,33;,
 3;36,37,33;,
 3;38,36,33;,
 3;39,35,33;,
 3;37,40,33;,
 3;40,39,33;,
 3;41,42,33;,
 3;32,41,33;,
 3;42,38,33;,
 3;43,44,45;,
 3;43,45,46;,
 3;47,46,45;,
 3;45,48,47;,
 3;46,49,43;,
 3;50,44,43;,
 3;50,43,49;,
 3;49,51,50;,
 3;49,52,51;,
 3;49,46,53;,
 3;49,54,52;,
 3;53,54,49;,
 3;55,53,46;,
 3;46,47,55;,
 3;56,55,47;,
 3;55,56,57;,
 3;58,57,56;,
 3;56,59,58;,
 3;60,59,56;,
 3;47,61,56;,
 3;56,61,60;,
 3;62,60,61;,
 3;61,63,62;,
 3;60,62,64;,
 3;64,65,60;,
 3;60,65,66;,
 3;59,60,66;,
 3;58,59,67;,
 3;66,67,59;,
 3;57,68,55;,
 3;53,55,68;,
 3;66,65,69;,
 3;69,65,64;,
 3;64,70,69;,
 3;67,66,71;,
 3;69,71,66;,
 3;70,64,72;,
 3;64,62,72;,
 3;73,70,72;,
 3;71,74,67;,
 3;75,63,61;,
 3;61,47,75;,
 3;75,76,63;,
 3;62,63,77;,
 3;72,77,78;,
 3;77,79,78;,
 3;80,67,74;,
 3;67,80,58;,
 3;58,80,81;,
 3;57,58,82;,
 3;81,82,58;,
 3;83,81,80;,
 3;81,83,84;,
 3;84,83,85;,
 3;86,84,85;,
 3;84,86,87;,
 3;87,88,84;,
 3;84,88,81;,
 3;82,81,88;,
 3;85,89,86;,
 3;88,90,82;,
 3;87,90,88;,
 3;90,87,91;,
 3;92,90,91;,
 3;93,90,92;,
 3;93,94,90;,
 3;95,94,93;,
 3;90,94,96;,
 3;68,57,96;,
 3;82,96,57;,
 3;96,82,90;,
 3;96,94,95;,
 3;95,97,96;,
 3;96,97,68;,
 3;98,97,95;,
 3;68,99,53;,
 3;99,68,97;,
 3;97,98,99;,
 3;99,98,100;,
 3;53,99,101;,
 3;101,54,53;,
 3;100,101,99;,
 3;102,100,98;,
 3;95,103,98;,
 3;98,103,102;,
 3;95,104,103;,
 3;104,102,103;,
 3;102,104,105;,
 3;102,105,106;,
 3;102,107,100;,
 3;102,106,107;,
 3;101,100,108;,
 3;108,100,107;,
 3;108,109,101;,
 3;54,101,109;,
 3;109,108,110;,
 3;110,111,109;,
 3;108,107,112;,
 3;112,107,106;,
 3;110,108,112;,
 3;110,112,113;,
 3;114,113,112;,
 3;106,115,112;,
 3;105,116,106;,
 3;117,106,116;,
 3;106,117,115;,
 3;118,109,111;,
 3;54,118,52;,
 3;109,118,54;,
 3;52,118,119;,
 3;111,119,118;,
 3;119,120,52;,
 3;51,52,120;,
 3;120,121,51;,
 3;51,121,122;,
 3;122,50,51;,
 3;123,50,122;,
 3;124,123,122;,
 3;123,125,50;,
 3;125,44,50;,
 3;126,44,125;,
 3;126,125,123;,
 3;127,44,126;,
 3;45,44,128;,
 3;128,129,45;,
 3;128,44,127;,
 3;129,48,45;,
 3;130,131,132;,
 3;131,133,132;,
 3;132,134,130;,
 3;135,134,132;,
 3;132,136,135;,
 3;136,132,137;,
 3;112,115,114;,
 3;72,62,77;,
 3;77,138,79;,
 3;76,138,63;,
 3;63,138,77;,
 3;74,139,80;,
 3;80,139,83;,
 3;87,86,140;,
 3;87,140,91;,
 3;141,142,143;,
 3;144,143,142;,
 3;142,145,144;,
 3;145,142,146;,
 3;141,146,142;,
 3;147,146,148;,
 3;146,147,145;,
 3;148,149,147;,
 3;144,150,151;,
 3;151,143,144;,
 3;104,95,152;,
 3;95,93,152;;
 
 MeshMaterialList {
  2;
  204;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  163;
  -0.622989;-0.165612;-0.764498;,
  -0.467684;-0.069433;-0.881164;,
  -0.471614;-0.364948;-0.802741;,
  -0.687396;-0.297700;-0.662466;,
  -0.671971;-0.512131;-0.534955;,
  -0.948582;-0.175399;-0.263490;,
  -0.913953;-0.253740;-0.316710;,
  -0.564012;-0.011196;-0.825691;,
  -0.833269;-0.327673;0.445302;,
  -0.834938;0.413992;0.362614;,
  -0.588415;-0.636719;0.498354;,
  -0.815031;-0.482390;0.320974;,
  -0.803785;-0.548382;0.230668;,
  -0.423430;0.034511;-0.905271;,
  -0.527063;0.783417;0.329336;,
  -0.258637;0.654057;0.710856;,
  0.885990;0.078016;-0.457094;,
  0.942660;-0.048308;-0.330241;,
  0.931356;-0.304299;-0.199945;,
  0.992899;0.109892;-0.045559;,
  0.986495;0.051391;0.155520;,
  0.826830;0.191813;-0.528735;,
  0.660851;-0.101101;0.743676;,
  0.511632;0.630178;0.584045;,
  0.478031;-0.477191;0.737411;,
  0.005281;0.873896;0.486084;,
  -0.560103;0.148405;0.815022;,
  -0.933117;-0.070354;-0.352623;,
  -0.961694;0.138813;-0.236381;,
  -0.563932;-0.159531;-0.810266;,
  -0.604484;-0.204825;-0.769835;,
  0.191009;-0.128006;-0.973206;,
  -0.326799;-0.218275;-0.919542;,
  -0.961449;-0.231181;-0.148898;,
  -0.926615;0.184318;0.327736;,
  -0.831125;-0.098927;0.547215;,
  -0.854169;-0.308244;0.418784;,
  -0.692218;-0.165053;-0.702561;,
  -0.971891;-0.211820;-0.102765;,
  -0.375328;-0.155458;-0.913762;,
  0.882509;0.003278;-0.470284;,
  0.854182;0.050743;-0.517492;,
  0.939066;0.040941;0.341289;,
  0.936819;-0.015071;0.349490;,
  0.967770;0.047664;0.247286;,
  0.844792;0.001167;-0.535093;,
  0.946947;0.171565;-0.271765;,
  0.871791;0.057456;-0.486497;,
  0.488842;0.359037;0.795064;,
  0.576584;0.124952;0.807427;,
  0.595802;-0.039064;0.802181;,
  0.564263;-0.076823;0.822013;,
  0.266577;0.034660;-0.963190;,
  0.392433;0.140799;0.908940;,
  -0.208018;0.516287;0.830768;,
  0.386259;-0.121349;0.914373;,
  0.060066;0.820074;0.569096;,
  -0.131292;0.899207;0.417359;,
  0.280135;-0.124879;0.951803;,
  0.703443;-0.122273;-0.700155;,
  0.909530;0.401896;-0.105992;,
  0.380571;0.773410;0.506955;,
  0.602988;0.756292;0.253826;,
  0.420495;-0.024200;0.906972;,
  0.586604;0.238316;0.774017;,
  0.965924;0.138900;0.218397;,
  0.258924;0.315641;0.912868;,
  0.485458;0.383095;0.785856;,
  -0.060096;0.315821;0.946914;,
  0.492274;0.115869;0.862694;,
  0.778342;0.130798;0.614065;,
  0.781897;0.222119;0.582495;,
  -0.457789;0.171849;0.872294;,
  0.957359;0.227931;0.177515;,
  0.796136;0.244507;0.553519;,
  0.937918;0.283461;0.199899;,
  0.858341;0.234172;-0.456525;,
  0.879066;0.303433;-0.367658;,
  0.217252;0.176645;-0.959999;,
  0.839926;0.176942;-0.513046;,
  0.085997;0.175572;-0.980703;,
  -0.652644;0.106390;-0.750158;,
  -0.647663;-0.026126;-0.761479;,
  -0.962521;-0.013481;-0.270874;,
  -0.964469;-0.101785;-0.243803;,
  -0.953138;0.074301;-0.293269;,
  -0.674775;0.163123;-0.719771;,
  -0.612183;0.088747;-0.785720;,
  -0.978397;0.079682;-0.190762;,
  -0.999670;-0.025386;-0.003967;,
  -0.998103;0.037529;-0.048811;,
  -0.980492;0.054551;0.188839;,
  -0.905262;-0.106429;0.411307;,
  -0.362905;-0.097860;0.926673;,
  -0.909763;0.202291;0.362504;,
  -0.960826;-0.042910;0.273810;,
  -0.997590;-0.001319;0.069377;,
  -0.980580;-0.170214;0.097419;,
  -0.857544;-0.201694;0.473220;,
  -0.458168;0.731822;0.504499;,
  -0.887838;0.390634;0.243205;,
  -0.914452;0.383025;0.130650;,
  -0.939364;0.202095;-0.277043;,
  -0.742830;-0.068964;-0.665919;,
  0.115501;-0.811321;0.573078;,
  0.405315;-0.454887;0.792968;,
  0.900626;0.434581;-0.003501;,
  -0.158402;0.984069;0.080729;,
  0.239736;-0.188065;-0.952449;,
  -0.450075;-0.723613;0.523275;,
  -0.663767;-0.590443;0.459119;,
  0.242858;-0.566410;-0.787528;,
  -0.616605;0.710175;0.339779;,
  -0.240730;0.886921;0.394235;,
  -0.697570;0.633067;0.335591;,
  0.812712;-0.174673;-0.555867;,
  0.783323;0.119680;-0.609985;,
  0.568499;0.511706;0.644178;,
  0.141806;0.841788;0.520850;,
  0.559659;-0.414769;0.717460;,
  0.367901;-0.592591;0.716578;,
  0.712923;-0.272709;0.646043;,
  0.756762;-0.332388;0.562876;,
  0.726723;0.201689;-0.656654;,
  0.388537;0.323716;0.862697;,
  -0.770470;0.130033;0.624073;,
  -0.234799;0.224340;0.945802;,
  -0.663421;0.042570;0.747034;,
  0.257152;0.191615;0.947183;,
  -0.832122;0.102145;0.545105;,
  -0.866207;-0.032733;0.498612;,
  0.491205;0.311957;0.813265;,
  0.555843;0.189000;0.809517;,
  0.546067;0.247744;0.800271;,
  0.635392;0.001867;-0.772188;,
  0.645036;0.177471;0.743258;,
  0.590980;0.425283;0.685476;,
  -0.418193;-0.100885;-0.902739;,
  0.661938;-0.093469;-0.743708;,
  0.441098;0.692862;0.570417;,
  -0.773956;0.192159;0.603380;,
  -0.775903;0.454310;0.437695;,
  -0.700717;-0.259436;0.664596;,
  -0.685736;-0.248052;0.684277;,
  -0.728733;-0.020027;0.684505;,
  -0.760783;0.151724;0.631022;,
  -0.362768;-0.213763;-0.907031;,
  0.090984;-0.824020;0.559207;,
  0.256702;-0.663233;0.703012;,
  0.283618;-0.727375;0.624889;,
  0.078724;-0.946884;0.311792;,
  0.144360;-0.907399;0.394698;,
  -0.080378;-0.564730;0.821352;,
  0.724256;-0.090464;-0.683572;,
  -0.142621;0.985460;-0.092348;,
  -0.680022;0.730002;-0.068321;,
  0.159132;0.964164;0.212285;,
  0.525973;0.785484;0.326141;,
  0.355929;0.862260;0.360308;,
  0.173079;0.908015;0.381512;,
  -0.697112;0.696763;0.168985;,
  -0.891791;0.452296;-0.011730;,
  -0.970250;0.148885;-0.190916;;
  204;
  3;0,1,2;,
  3;2,3,0;,
  3;2,4,3;,
  3;5,0,3;,
  3;3,6,5;,
  3;4,6,3;,
  3;0,5,7;,
  3;5,6,8;,
  3;8,9,5;,
  3;109,110,10;,
  3;11,10,110;,
  3;4,12,11;,
  3;10,8,109;,
  3;1,0,7;,
  3;1,7,13;,
  3;2,111,4;,
  3;9,14,112;,
  3;14,15,113;,
  3;113,112,14;,
  3;112,114,9;,
  3;16,17,115;,
  3;115,116,16;,
  3;115,17,18;,
  3;17,16,19;,
  3;18,17,20;,
  3;19,20,17;,
  3;16,21,19;,
  3;22,20,117;,
  3;19,23,22;,
  3;23,117,118;,
  3;24,119,120;,
  3;119,24,121;,
  3;121,122,18;,
  3;116,21,16;,
  3;116,123,21;,
  3;115,18,111;,
  3;120,22,24;,
  3;25,118,113;,
  3;113,15,25;,
  3;118,25,23;,
  3;124,26,15;,
  3;125,15,26;,
  3;126,127,26;,
  3;128,126,26;,
  3;129,125,26;,
  3;127,130,26;,
  3;130,129,26;,
  3;131,132,133;,
  3;124,131,133;,
  3;132,128,133;,
  3;27,28,29;,
  3;27,29,30;,
  3;31,30,29;,
  3;29,32,31;,
  3;30,33,27;,
  3;34,28,27;,
  3;34,27,33;,
  3;33,35,34;,
  3;33,36,35;,
  3;33,30,37;,
  3;33,38,36;,
  3;37,38,33;,
  3;39,37,30;,
  3;30,31,39;,
  3;40,134,31;,
  3;134,40,41;,
  3;42,41,40;,
  3;40,43,42;,
  3;44,43,40;,
  3;31,45,40;,
  3;40,45,44;,
  3;46,44,45;,
  3;45,47,46;,
  3;135,136,48;,
  3;48,49,44;,
  3;44,49,50;,
  3;43,44,50;,
  3;42,43,51;,
  3;50,51,43;,
  3;41,52,134;,
  3;37,39,137;,
  3;50,49,53;,
  3;53,49,48;,
  3;48,54,53;,
  3;51,50,55;,
  3;53,55,50;,
  3;54,48,56;,
  3;48,136,56;,
  3;57,54,56;,
  3;55,58,51;,
  3;138,47,45;,
  3;45,31,138;,
  3;138,59,47;,
  3;46,47,60;,
  3;56,139,61;,
  3;139,62,61;,
  3;63,51,58;,
  3;51,63,42;,
  3;42,63,64;,
  3;41,42,65;,
  3;64,65,42;,
  3;66,64,63;,
  3;64,66,67;,
  3;67,66,68;,
  3;69,67,68;,
  3;67,69,70;,
  3;70,71,67;,
  3;67,71,64;,
  3;65,64,71;,
  3;68,72,69;,
  3;71,73,65;,
  3;70,73,71;,
  3;73,70,74;,
  3;75,73,74;,
  3;76,73,75;,
  3;76,77,73;,
  3;78,77,76;,
  3;73,77,79;,
  3;52,41,79;,
  3;65,79,41;,
  3;79,65,73;,
  3;79,77,78;,
  3;78,80,79;,
  3;79,80,52;,
  3;81,80,78;,
  3;52,82,37;,
  3;82,52,80;,
  3;80,81,82;,
  3;82,81,83;,
  3;37,82,84;,
  3;84,38,37;,
  3;83,84,82;,
  3;85,83,81;,
  3;78,86,81;,
  3;81,86,85;,
  3;78,87,86;,
  3;87,85,86;,
  3;85,87,88;,
  3;85,88,89;,
  3;85,90,83;,
  3;85,89,90;,
  3;84,83,91;,
  3;91,83,90;,
  3;91,92,84;,
  3;38,84,92;,
  3;92,91,140;,
  3;140,93,92;,
  3;91,90,94;,
  3;94,90,89;,
  3;140,91,94;,
  3;140,94,141;,
  3;72,68,94;,
  3;89,95,94;,
  3;88,96,89;,
  3;97,89,96;,
  3;89,97,95;,
  3;98,92,93;,
  3;38,98,36;,
  3;92,98,38;,
  3;36,98,142;,
  3;93,142,98;,
  3;142,143,36;,
  3;35,36,143;,
  3;143,144,35;,
  3;35,144,145;,
  3;54,34,35;,
  3;99,34,54;,
  3;57,99,54;,
  3;99,100,34;,
  3;100,28,34;,
  3;101,28,100;,
  3;101,100,99;,
  3;102,28,101;,
  3;29,28,103;,
  3;103,146,29;,
  3;103,28,102;,
  3;146,32,29;,
  3;147,148,104;,
  3;148,149,104;,
  3;104,150,147;,
  3;151,150,104;,
  3;104,105,151;,
  3;105,104,152;,
  3;94,95,72;,
  3;56,136,139;,
  3;60,106,62;,
  3;59,153,47;,
  3;47,106,60;,
  3;58,93,63;,
  3;63,93,66;,
  3;70,69,105;,
  3;70,105,74;,
  3;154,107,155;,
  3;56,155,107;,
  3;107,57,56;,
  3;57,107,156;,
  3;154,156,107;,
  3;157,156,158;,
  3;156,99,57;,
  3;158,159,99;,
  3;56,160,161;,
  3;161,155,162;,
  3;87,78,108;,
  3;78,76,108;;
 }
 MeshTextureCoords {
  153;
  0.498460;0.643230;,
  0.499520;0.660650;,
  0.546490;0.660110;,
  0.550050;0.643540;,
  0.568090;0.637900;,
  0.498530;0.623140;,
  0.555020;0.625300;,
  0.476800;0.637850;,
  0.557460;0.621790;,
  0.496910;0.618470;,
  0.569360;0.632820;,
  0.586690;0.636800;,
  0.587430;0.642060;,
  0.466470;0.648110;,
  0.474270;0.633200;,
  0.462840;0.643580;,
  0.354210;0.677380;,
  0.405270;0.676770;,
  0.401930;0.694230;,
  0.356360;0.694500;,
  0.423590;0.672700;,
  0.353320;0.658290;,
  0.409590;0.657400;,
  0.333050;0.672720;,
  0.412260;0.651750;,
  0.352170;0.653680;,
  0.425180;0.666680;,
  0.443650;0.674560;,
  0.443040;0.680080;,
  0.323430;0.683730;,
  0.330590;0.669540;,
  0.320320;0.681050;,
  0.260380;0.917600;,
  0.244170;0.912210;,
  0.263520;0.912710;,
  0.260750;0.908140;,
  0.219520;0.912460;,
  0.225900;0.908630;,
  0.225720;0.915260;,
  0.252950;0.901660;,
  0.231320;0.902760;,
  0.252200;0.923060;,
  0.230690;0.921060;,
  0.347470;0.425830;,
  0.332530;0.428200;,
  0.348280;0.406050;,
  0.379630;0.397440;,
  0.378700;0.370160;,
  0.349840;0.381380;,
  0.381280;0.418590;,
  0.349360;0.444750;,
  0.381430;0.438060;,
  0.404510;0.428810;,
  0.431560;0.385960;,
  0.434350;0.403860;,
  0.428140;0.362840;,
  0.427250;0.343220;,
  0.454530;0.344300;,
  0.454890;0.327760;,
  0.427730;0.326090;,
  0.373550;0.322240;,
  0.374420;0.342130;,
  0.340950;0.319830;,
  0.343850;0.341440;,
  0.338790;0.299780;,
  0.370270;0.298150;,
  0.397610;0.302500;,
  0.429670;0.309290;,
  0.454970;0.362360;,
  0.368020;0.274140;,
  0.336340;0.278150;,
  0.401170;0.281370;,
  0.327070;0.300040;,
  0.324780;0.283830;,
  0.433040;0.291850;,
  0.348270;0.368590;,
  0.313840;0.362270;,
  0.325000;0.321010;,
  0.318960;0.314440;,
  0.312270;0.330890;,
  0.456100;0.311410;,
  0.482530;0.313520;,
  0.482060;0.329420;,
  0.477950;0.297660;,
  0.497370;0.300220;,
  0.494270;0.291470;,
  0.517890;0.299550;,
  0.515800;0.314990;,
  0.502200;0.315370;,
  0.518620;0.287680;,
  0.511970;0.330480;,
  0.529220;0.315640;,
  0.524890;0.331340;,
  0.527930;0.347770;,
  0.512490;0.346960;,
  0.512790;0.360560;,
  0.481810;0.345370;,
  0.481790;0.361870;,
  0.483510;0.378520;,
  0.457530;0.382240;,
  0.486550;0.393410;,
  0.460450;0.398630;,
  0.515120;0.388590;,
  0.513680;0.374600;,
  0.528970;0.372980;,
  0.525660;0.387390;,
  0.519990;0.404880;,
  0.503480;0.406410;,
  0.485920;0.409160;,
  0.461100;0.413150;,
  0.481840;0.422540;,
  0.460370;0.426230;,
  0.501150;0.419920;,
  0.497700;0.429370;,
  0.521880;0.430050;,
  0.521810;0.420260;,
  0.533990;0.404800;,
  0.526860;0.415240;,
  0.436270;0.417130;,
  0.438890;0.429930;,
  0.411140;0.443930;,
  0.383240;0.458840;,
  0.353240;0.464260;,
  0.338500;0.450770;,
  0.340810;0.463130;,
  0.335970;0.442290;,
  0.326130;0.436970;,
  0.317550;0.422520;,
  0.314410;0.406200;,
  0.316860;0.383830;,
  0.978160;0.487290;,
  0.977260;0.479190;,
  0.989860;0.480690;,
  0.969360;0.456790;,
  0.988360;0.492290;,
  0.978160;0.487290;,
  0.977260;0.479190;,
  0.969360;0.456790;,
  0.311450;0.345870;,
  0.455500;0.294750;,
  0.520540;0.306470;,
  0.409910;0.829120;,
  0.409550;0.839360;,
  0.396810;0.835310;,
  0.396580;0.877630;,
  0.409920;0.884290;,
  0.425270;0.840430;,
  0.420580;0.881670;,
  0.428570;0.853000;,
  0.427210;0.866970;,
  0.392910;0.863580;,
  0.392150;0.847630;,
  0.519990;0.360270;;
 }
}
