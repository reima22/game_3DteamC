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
 400;
 -0.91865;1.02941;-7.03513;,
 0.59102;0.87987;-8.19654;,
 -0.15819;-0.97450;-8.19654;,
 -1.66786;-0.36456;-7.03513;,
 0.59102;0.87987;-8.19654;,
 1.66786;0.44479;-6.56831;,
 0.91865;-1.40957;-6.56831;,
 -0.15819;-0.97450;-8.19654;,
 1.66786;0.44479;-6.56831;,
 0.15819;1.05474;-5.40690;,
 -0.59102;-0.79963;-5.40690;,
 0.91865;-1.40957;-6.56831;,
 0.15819;1.05474;-5.40690;,
 -0.91865;1.02941;-7.03513;,
 -1.66786;-0.36456;-7.03513;,
 -0.59102;-0.79963;-5.40690;,
 0.59102;0.87987;-8.19654;,
 -0.91865;1.02941;-7.03513;,
 -1.66786;-0.36456;-7.03513;,
 -0.15819;-0.97450;-8.19654;,
 -0.42809;0.41466;-1.18233;,
 1.43114;0.41297;-0.84790;,
 0.78783;-0.80962;-1.23077;,
 -1.07140;-0.36109;-1.56520;,
 1.43114;0.41297;-0.84790;,
 1.07140;0.28115;1.56520;,
 0.42809;-0.94144;1.18233;,
 0.78783;-0.80962;-1.23077;,
 1.07140;0.28115;1.56520;,
 -0.78783;0.72969;1.23077;,
 -1.43114;-0.49290;0.84790;,
 0.42809;-0.94144;1.18233;,
 -0.78783;0.72969;1.23077;,
 -0.42809;0.41466;-1.18233;,
 -1.07140;-0.36109;-1.56520;,
 -1.43114;-0.49290;0.84790;,
 1.43114;0.41297;-0.84790;,
 -0.42809;0.41466;-1.18233;,
 -1.07140;-0.36109;-1.56520;,
 0.78783;-0.80962;-1.23077;,
 5.62100;0.77887;2.33205;,
 7.55758;1.24268;2.51786;,
 8.01532;-0.70240;2.60240;,
 6.07873;-1.16621;2.41658;,
 7.55758;1.24268;2.51786;,
 7.35727;0.65299;4.50742;,
 7.81500;-0.66308;4.59195;,
 8.01532;-0.70240;2.60240;,
 7.35727;0.65299;4.50742;,
 5.42068;0.81819;4.32160;,
 5.87842;-1.12689;4.40614;,
 7.81500;-0.66308;4.59195;,
 5.42068;0.81819;4.32160;,
 5.62100;0.77887;2.33205;,
 6.07873;-1.16621;2.41658;,
 5.87842;-1.12689;4.40614;,
 7.55758;1.24268;2.51786;,
 5.62100;0.77887;2.33205;,
 6.07873;-1.16621;2.41658;,
 8.01532;-0.70240;2.60240;,
 -8.34988;0.65073;1.53667;,
 -5.58953;0.84723;0.99206;,
 -5.20608;-0.65682;1.20172;,
 -7.96643;-0.85332;1.74633;,
 -5.58953;0.84723;0.99206;,
 -5.24957;0.94814;5.17767;,
 -4.86612;-0.55591;5.38733;,
 -5.20608;-0.65682;1.20172;,
 -5.24957;0.94814;5.17767;,
 -8.00992;0.31295;5.72228;,
 -7.62648;-0.75241;5.93194;,
 -4.86612;-0.55591;5.38733;,
 -8.00992;0.31295;5.72228;,
 -8.34988;0.65073;1.53667;,
 -7.96643;-0.85332;1.74633;,
 -7.62648;-0.75241;5.93194;,
 -5.58953;0.84723;0.99206;,
 -8.34988;0.65073;1.53667;,
 -7.96643;-0.85332;1.74633;,
 -5.20608;-0.65682;1.20172;,
 2.09276;0.91210;10.68160;,
 1.16926;-0.37872;11.64622;,
 1.16926;-1.86030;10.17655;,
 2.09276;-0.08430;9.21193;,
 1.16926;-0.37872;11.64622;,
 -0.60476;0.54581;11.14407;,
 -0.60476;-0.93577;9.67440;,
 1.16926;-1.86030;10.17655;,
 -0.60476;0.54581;11.14407;,
 0.31874;1.12809;10.17945;,
 0.31874;0.84024;8.70978;,
 -0.60476;-0.93577;9.67440;,
 0.31874;1.12809;10.17945;,
 2.09276;0.91210;10.68160;,
 2.09276;-0.08430;9.21193;,
 0.31874;0.84024;8.70978;,
 1.16926;-0.37872;11.64622;,
 2.09276;0.91210;10.68160;,
 2.09276;-0.08430;9.21193;,
 1.16926;-1.86030;10.17655;,
 -8.98614;0.59241;-4.53156;,
 -7.51416;0.93626;-4.39653;,
 -7.16624;-0.50577;-4.33509;,
 -8.63822;-0.84962;-4.47013;,
 -7.51416;0.93626;-4.39653;,
 -7.66642;0.59212;-2.95066;,
 -7.31850;-0.47661;-2.88923;,
 -7.16624;-0.50577;-4.33509;,
 -7.66642;0.59212;-2.95066;,
 -9.13840;0.80765;-3.08570;,
 -8.79048;-0.82047;-3.02427;,
 -7.31850;-0.47661;-2.88923;,
 -9.13840;0.80765;-3.08570;,
 -8.98614;0.59241;-4.53156;,
 -8.63822;-0.84962;-4.47013;,
 -8.79048;-0.82047;-3.02427;,
 -7.51416;0.93626;-4.39653;,
 -8.98614;0.59241;-4.53156;,
 -8.63822;-0.84962;-4.47013;,
 -7.16624;-0.50577;-4.33509;,
 -5.50584;0.59051;8.78390;,
 -4.73156;0.41297;7.06081;,
 -5.25869;-0.80962;7.59238;,
 -6.03297;-0.36109;9.31548;,
 -4.73156;0.41297;7.06081;,
 -2.47717;0.28115;7.99364;,
 -3.00429;-0.94144;8.52522;,
 -5.25869;-0.80962;7.59238;,
 -2.47717;0.28115;7.99364;,
 -3.25145;0.72969;9.71674;,
 -3.77858;-0.49290;10.24832;,
 -3.00429;-0.94144;8.52522;,
 -3.25145;0.72969;9.71674;,
 -5.50584;0.59051;8.78390;,
 -6.03297;-0.36109;9.31548;,
 -3.77858;-0.49290;10.24832;,
 -4.73156;0.41297;7.06081;,
 -5.50584;0.59051;8.78390;,
 -6.03297;-0.36109;9.31548;,
 -5.25869;-0.80962;7.59238;,
 -13.30169;0.77887;2.33205;,
 -11.36511;0.92808;2.51786;,
 -10.90737;-0.70240;2.60240;,
 -12.84396;-1.16621;2.41658;,
 -11.36511;0.92808;2.51786;,
 -11.56542;0.60571;4.50742;,
 -11.10769;-0.66308;4.59195;,
 -10.90737;-0.70240;2.60240;,
 -11.56542;0.60571;4.50742;,
 -13.50201;0.81819;4.32160;,
 -13.04428;-1.12689;4.40614;,
 -11.10769;-0.66308;4.59195;,
 -13.50201;0.81819;4.32160;,
 -13.30169;0.77887;2.33205;,
 -12.84396;-1.16621;2.41658;,
 -13.04428;-1.12689;4.40614;,
 -11.36511;0.92808;2.51786;,
 -13.30169;0.77887;2.33205;,
 -12.84396;-1.16621;2.41658;,
 -10.90737;-0.70240;2.60240;,
 8.69857;0.39902;-6.83055;,
 10.56881;0.84723;-4.72856;,
 10.58277;-0.65682;-4.29176;,
 8.71253;-0.85332;-6.39375;,
 10.56881;0.84723;-4.72856;,
 7.13490;0.94814;-2.31129;,
 7.14887;-0.55591;-1.87449;,
 10.58277;-0.65682;-4.29176;,
 7.13490;0.94814;-2.31129;,
 5.26467;1.00187;-4.41328;,
 5.27863;-0.75241;-3.97647;,
 7.14887;-0.55591;-1.87449;,
 5.26467;1.00187;-4.41328;,
 8.69857;0.39902;-6.83055;,
 8.71253;-0.85332;-6.39375;,
 5.27863;-0.75241;-3.97647;,
 10.56881;0.84723;-4.72856;,
 8.69857;0.39902;-6.83055;,
 8.71253;-0.85332;-6.39375;,
 10.58277;-0.65682;-4.29176;,
 -5.35880;0.86150;-10.07323;,
 -3.99300;0.41297;-8.76817;,
 -4.31813;-0.80962;-9.44251;,
 -5.68393;-0.36109;-10.74757;,
 -3.99300;0.41297;-8.76817;,
 -5.62486;0.28115;-6.95448;,
 -5.94999;-0.94144;-7.62881;,
 -4.31813;-0.80962;-9.44251;,
 -5.62486;0.28115;-6.95448;,
 -6.99066;0.28334;-8.25953;,
 -7.31579;-0.49290;-8.93387;,
 -5.94999;-0.94144;-7.62881;,
 -6.99066;0.28334;-8.25953;,
 -5.35880;0.86150;-10.07323;,
 -5.68393;-0.36109;-10.74757;,
 -7.31579;-0.49290;-8.93387;,
 -3.99300;0.41297;-8.76817;,
 -5.35880;0.86150;-10.07323;,
 -5.68393;-0.36109;-10.74757;,
 -4.31813;-0.80962;-9.44251;,
 -2.78097;1.00099;-3.54809;,
 -2.28617;-0.37872;-2.30772;,
 -3.62351;-1.86030;-2.91718;,
 -4.11831;-0.08430;-4.15755;,
 -2.28617;-0.37872;-2.30772;,
 -3.47878;0.54581;-0.90166;,
 -4.81613;-0.93577;-1.51112;,
 -3.62351;-1.86030;-2.91718;,
 -3.47878;0.54581;-0.90166;,
 -3.97358;1.23741;-2.14203;,
 -5.31093;0.84024;-2.75150;,
 -4.81613;-0.93577;-1.51112;,
 -3.97358;1.23741;-2.14203;,
 -2.78097;1.00099;-3.54809;,
 -4.11831;-0.08430;-4.15755;,
 -5.31093;0.84024;-2.75150;,
 -2.28617;-0.37872;-2.30772;,
 -2.78097;1.00099;-3.54809;,
 -4.11831;-0.08430;-4.15755;,
 -3.62351;-1.86030;-2.91718;,
 3.43819;0.86150;-10.81284;,
 5.29742;0.41297;-10.47841;,
 4.65411;-0.80962;-10.86128;,
 2.79487;-0.36109;-11.19571;,
 5.29742;0.41297;-10.47841;,
 4.93768;0.28115;-8.06531;,
 4.29437;-0.94144;-8.44818;,
 4.65411;-0.80962;-10.86128;,
 4.93768;0.28115;-8.06531;,
 3.07845;0.27718;-8.39974;,
 2.43514;-0.49290;-8.78261;,
 4.29437;-0.94144;-8.44818;,
 3.07845;0.27718;-8.39974;,
 3.43819;0.86150;-10.81284;,
 2.79487;-0.36109;-11.19571;,
 2.43514;-0.49290;-8.78261;,
 5.29742;0.41297;-10.47841;,
 3.43819;0.86150;-10.81284;,
 2.79487;-0.36109;-11.19571;,
 4.65411;-0.80962;-10.86128;,
 2.74545;0.36373;3.34312;,
 3.72822;0.56438;3.41130;,
 3.96051;-0.27709;3.44232;,
 2.97774;-0.47774;3.37414;,
 3.72822;0.56438;3.41130;,
 3.62657;0.36356;4.14140;,
 3.85885;-0.26008;4.17242;,
 3.96051;-0.27709;3.44232;,
 3.62657;0.36356;4.14140;,
 2.64380;0.48933;4.07321;,
 2.87609;-0.46073;4.10423;,
 3.85885;-0.26008;4.17242;,
 2.64380;0.48933;4.07321;,
 2.74545;0.36373;3.34312;,
 2.97774;-0.47774;3.37414;,
 2.87609;-0.46073;4.10423;,
 3.72822;0.56438;3.41130;,
 2.74545;0.36373;3.34312;,
 2.97774;-0.47774;3.37414;,
 3.96051;-0.27709;3.44232;,
 -1.49150;0.36373;6.45312;,
 -0.67509;0.56438;5.90180;,
 -0.47295;-0.27709;5.78324;,
 -1.28936;-0.47774;6.33456;,
 -0.67509;0.56438;5.90180;,
 -0.30571;0.36356;6.53971;,
 -0.10356;-0.26008;6.42114;,
 -0.47295;-0.27709;5.78324;,
 -0.30571;0.36356;6.53971;,
 -1.12212;0.48933;7.09103;,
 -0.91998;-0.46073;6.97246;,
 -0.10356;-0.26008;6.42114;,
 -1.12212;0.48933;7.09103;,
 -1.49150;0.36373;6.45312;,
 -1.28936;-0.47774;6.33456;,
 -0.91998;-0.46073;6.97246;,
 -0.67509;0.56438;5.90180;,
 -1.49150;0.36373;6.45312;,
 -1.28936;-0.47774;6.33456;,
 -0.47295;-0.27709;5.78324;,
 2.61423;0.36373;-5.45625;,
 3.50683;0.56438;-5.87307;,
 3.72504;-0.27709;-5.95856;,
 2.83243;-0.47774;-5.54174;,
 3.50683;0.56438;-5.87307;,
 3.77188;0.36356;-5.18524;,
 3.99008;-0.26008;-5.27072;,
 3.72504;-0.27709;-5.95856;,
 3.77188;0.36356;-5.18524;,
 2.87927;0.48933;-4.76842;,
 3.09747;-0.46073;-4.85390;,
 3.99008;-0.26008;-5.27072;,
 2.87927;0.48933;-4.76842;,
 2.61423;0.36373;-5.45625;,
 2.83243;-0.47774;-5.54174;,
 3.09747;-0.46073;-4.85390;,
 3.50683;0.56438;-5.87307;,
 2.61423;0.36373;-5.45625;,
 2.83243;-0.47774;-5.54174;,
 3.72504;-0.27709;-5.95856;,
 -10.95238;0.36373;-1.69872;,
 -10.06719;0.56438;-2.13106;,
 -9.85051;-0.27709;-2.22034;,
 -10.73571;-0.47774;-1.78800;,
 -10.06719;0.56438;-2.13106;,
 -9.79018;0.36356;-1.44795;,
 -9.57350;-0.26008;-1.53723;,
 -9.85051;-0.27709;-2.22034;,
 -9.79018;0.36356;-1.44795;,
 -10.67537;0.48933;-1.01562;,
 -10.45869;-0.46073;-1.10490;,
 -9.57350;-0.26008;-1.53723;,
 -10.67537;0.48933;-1.01562;,
 -10.95238;0.36373;-1.69872;,
 -10.73571;-0.47774;-1.78800;,
 -10.45869;-0.46073;-1.10490;,
 -10.06719;0.56438;-2.13106;,
 -10.95238;0.36373;-1.69872;,
 -10.73571;-0.47774;-1.78800;,
 -9.85051;-0.27709;-2.22034;,
 2.72491;0.36373;-6.97203;,
 3.61010;0.56438;-7.40436;,
 3.82678;-0.27709;-7.49364;,
 2.94158;-0.47774;-7.06131;,
 3.61010;0.56438;-7.40436;,
 3.88712;0.36356;-6.72125;,
 4.10379;-0.26008;-6.81053;,
 3.82678;-0.27709;-7.49364;,
 3.88712;0.36356;-6.72125;,
 3.00192;0.48933;-6.28892;,
 3.21860;-0.46073;-6.37820;,
 4.10379;-0.26008;-6.81053;,
 3.00192;0.48933;-6.28892;,
 2.72491;0.36373;-6.97203;,
 2.94158;-0.47774;-7.06131;,
 3.21860;-0.46073;-6.37820;,
 3.61010;0.56438;-7.40436;,
 2.72491;0.36373;-6.97203;,
 2.94158;-0.47774;-7.06131;,
 3.82678;-0.27709;-7.49364;,
 -4.73014;0.36373;2.78107;,
 -3.91373;0.56438;2.22975;,
 -3.71158;-0.27709;2.11118;,
 -4.52799;-0.47774;2.66251;,
 -3.91373;0.56438;2.22975;,
 -3.54434;0.36356;2.86766;,
 -3.34220;-0.26008;2.74909;,
 -3.71158;-0.27709;2.11118;,
 -3.54434;0.36356;2.86766;,
 -4.36075;0.48933;3.41898;,
 -4.15861;-0.46073;3.30041;,
 -3.34220;-0.26008;2.74909;,
 -4.36075;0.48933;3.41898;,
 -4.73014;0.36373;2.78107;,
 -4.52799;-0.47774;2.66251;,
 -4.15861;-0.46073;3.30041;,
 -3.91373;0.56438;2.22975;,
 -4.73014;0.36373;2.78107;,
 -4.52799;-0.47774;2.66251;,
 -3.71158;-0.27709;2.11118;,
 8.12290;0.36373;-1.29049;,
 8.93931;0.56438;-1.84181;,
 9.14145;-0.27709;-1.96038;,
 8.32504;-0.47774;-1.40906;,
 8.93931;0.56438;-1.84181;,
 9.30869;0.36356;-1.20391;,
 9.51084;-0.26008;-1.32247;,
 9.14145;-0.27709;-1.96038;,
 9.30869;0.36356;-1.20391;,
 8.49228;0.48933;-0.65258;,
 8.69442;-0.46073;-0.77115;,
 9.51084;-0.26008;-1.32247;,
 8.49228;0.48933;-0.65258;,
 8.12290;0.36373;-1.29049;,
 8.32504;-0.47774;-1.40906;,
 8.69442;-0.46073;-0.77115;,
 8.93931;0.56438;-1.84181;,
 8.12290;0.36373;-1.29049;,
 8.32504;-0.47774;-1.40906;,
 9.14145;-0.27709;-1.96038;,
 -11.24931;0.36373;6.20317;,
 -10.98656;0.56438;5.25373;,
 -10.90985;-0.27709;5.03228;,
 -11.17260;-0.47774;5.98173;,
 -10.98656;0.56438;5.25373;,
 -10.29139;0.36356;5.49890;,
 -10.21468;-0.26008;5.27745;,
 -10.90985;-0.27709;5.03228;,
 -10.29139;0.36356;5.49890;,
 -10.55414;0.48933;6.44835;,
 -10.47743;-0.46073;6.22690;,
 -10.21468;-0.26008;5.27745;,
 -10.55414;0.48933;6.44835;,
 -11.24931;0.36373;6.20317;,
 -11.17260;-0.47774;5.98173;,
 -10.47743;-0.46073;6.22690;,
 -10.98656;0.56438;5.25373;,
 -11.24931;0.36373;6.20317;,
 -11.17260;-0.47774;5.98173;,
 -10.90985;-0.27709;5.03228;;
 
 120;
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
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,225,236,237;,
 4;238,239,226,235;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;252,245,256,257;,
 4;258,259,246,255;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;272,265,276,277;,
 4;278,279,266,275;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;292,285,296,297;,
 4;298,299,286,295;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;312,305,316,317;,
 4;318,319,306,315;,
 4;320,321,322,323;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;332,325,336,337;,
 4;338,339,326,335;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;352,345,356,357;,
 4;358,359,346,355;,
 4;360,361,362,363;,
 4;364,365,366,367;,
 4;368,369,370,371;,
 4;372,373,374,375;,
 4;372,365,376,377;,
 4;378,379,366,375;,
 4;380,381,382,383;,
 4;384,385,386,387;,
 4;388,389,390,391;,
 4;392,393,394,395;,
 4;392,385,396,397;,
 4;398,399,386,395;;
 
 MeshMaterialList {
  1;
  120;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.401569;0.401569;0.401569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\stone000.jpg";
   }
  }
 }
 MeshNormals {
  120;
  -0.546355;0.255035;-0.797780;,
  0.754835;-0.304973;-0.580703;,
  0.538418;-0.217535;0.814116;,
  0.203258;0.239436;-0.949398;,
  0.866709;-0.488162;0.102540;,
  -0.217197;-0.185812;0.958279;,
  0.100158;-0.019661;-0.994777;,
  0.950656;0.283071;0.126984;,
  -0.097946;0.024767;0.994884;,
  -0.178030;-0.180238;-0.967378;,
  0.968304;0.235112;-0.084314;,
  0.156632;0.209204;0.965246;,
  0.886488;-0.358188;0.292985;,
  -0.493875;-0.612367;0.617329;,
  -0.850359;0.448034;-0.275962;,
  -0.756767;0.353776;0.549679;,
  0.224616;0.974137;-0.024579;,
  -0.374607;-0.927184;0.000000;,
  -0.800403;0.584229;-0.134280;,
  0.122590;0.992249;-0.020318;,
  -0.219052;-0.971938;-0.085749;,
  -0.968292;-0.231905;-0.092907;,
  -0.083021;0.988868;0.123483;,
  0.228867;-0.972540;0.042265;,
  -0.956989;-0.281056;0.071974;,
  -0.140469;0.989325;0.038797;,
  0.074527;-0.997057;0.017984;,
  0.381651;0.849377;-0.364556;,
  0.036567;0.707578;0.705689;,
  0.000000;-0.477285;-0.878749;,
  0.095803;-0.019283;-0.995214;,
  0.952968;0.275843;0.125546;,
  -0.092937;0.022085;0.995427;,
  -0.970900;-0.224217;-0.084138;,
  -0.043988;0.998350;0.036901;,
  0.223507;-0.973746;0.043170;,
  -0.875347;0.214311;-0.433404;,
  0.309169;-0.488161;-0.816157;,
  0.877270;-0.185812;0.442574;,
  -0.320183;0.540854;0.777792;,
  0.060323;0.986650;-0.151273;,
  -0.136195;-0.971938;0.191801;,
  0.099021;-0.021809;-0.994846;,
  0.944189;0.309080;0.113917;,
  -0.097796;0.025315;0.994884;,
  -0.968292;-0.231904;-0.092907;,
  0.009877;0.997391;0.071511;,
  0.228867;-0.972540;0.042265;,
  0.747842;-0.194896;-0.634625;,
  0.564099;0.235111;0.791527;,
  -0.739491;0.169204;0.651555;,
  -0.576937;-0.238187;-0.781288;,
  0.022397;0.993348;-0.112950;,
  0.022330;-0.997057;0.073342;,
  0.710028;0.185813;-0.679216;,
  0.666141;-0.488161;0.563875;,
  -0.693524;-0.239353;0.679510;,
  -0.670734;0.561124;-0.485032;,
  -0.012260;0.983865;0.178489;,
  -0.135337;-0.971938;-0.192408;,
  0.638678;-0.345476;-0.687558;,
  0.356939;-0.612367;0.705409;,
  -0.610375;0.429809;0.665362;,
  -0.209465;0.824513;-0.525645;,
  0.677577;0.678329;0.284182;,
  -0.799627;-0.477284;-0.364411;,
  0.217197;0.185813;-0.958279;,
  0.866709;-0.488162;0.102540;,
  -0.203083;-0.240366;0.949200;,
  -0.826233;0.562359;-0.033045;,
  0.086423;0.983884;0.156532;,
  -0.219052;-0.971938;-0.085749;,
  0.072602;-0.016720;-0.997221;,
  0.936577;0.310169;0.163151;,
  -0.070423;0.019148;0.997333;,
  -0.960951;-0.253882;-0.110079;,
  -0.038448;0.998350;0.042646;,
  0.196448;-0.979230;0.050170;,
  -0.556739;-0.016722;-0.830519;,
  0.838479;0.310170;-0.448050;,
  0.558524;0.019146;0.829267;,
  -0.825011;-0.253883;0.504877;,
  -0.004042;0.998350;0.057277;,
  0.185691;-0.979230;-0.081411;,
  -0.419963;-0.016721;-0.907387;,
  0.898246;0.310169;-0.311368;,
  0.421923;0.019149;0.906429;,
  -0.893834;-0.253882;0.369601;,
  -0.012952;0.998350;0.055939;,
  0.196140;-0.979230;-0.051360;,
  -0.435735;-0.016720;-0.899920;,
  0.892674;0.310169;-0.326998;,
  0.437679;0.019148;0.898927;,
  -0.887247;-0.253882;0.385145;,
  -0.011974;0.998350;0.056156;,
  0.195213;-0.979230;-0.054776;,
  -0.435735;-0.016720;-0.899920;,
  0.892675;0.310168;-0.326998;,
  0.437679;0.019149;0.898928;,
  -0.887247;-0.253882;0.385145;,
  -0.011974;0.998350;0.056156;,
  0.195214;-0.979230;-0.054776;,
  -0.556739;-0.016722;-0.830519;,
  0.838479;0.310169;-0.448050;,
  0.558524;0.019145;0.829267;,
  -0.825010;-0.253883;0.504878;,
  -0.004042;0.998350;0.057276;,
  0.185691;-0.979230;-0.081411;,
  -0.556739;-0.016722;-0.830519;,
  0.838479;0.310169;-0.448049;,
  0.558525;0.019146;0.829267;,
  -0.825011;-0.253883;0.504876;,
  -0.004042;0.998350;0.057277;,
  0.185691;-0.979230;-0.081411;,
  -0.962726;-0.016722;-0.269960;,
  0.346598;0.310171;-0.885248;,
  0.963271;0.019148;0.267847;,
  -0.299449;-0.253884;0.919714;,
  0.034125;0.998350;0.046179;,
  0.088327;-0.979230;-0.182502;;
  120;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;107,107,107,107;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;111,111,111,111;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;114,114,114,114;,
  4;115,115,115,115;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;118,118,118,118;,
  4;119,119,119,119;;
 }
 MeshTextureCoords {
  400;
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
