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
 450;
 -5.00000;70.00000;-2.00000;,
 0.00000;70.00000;-2.00000;,
 0.00000;60.00000;-2.00000;,
 -5.00000;60.00000;-2.00000;,
 5.00000;70.00000;-2.00000;,
 5.00000;60.00000;-2.00000;,
 0.00000;50.00000;-2.00000;,
 -5.00000;50.00000;-2.00000;,
 5.00000;50.00000;-2.00000;,
 0.00000;40.00000;-2.00000;,
 -5.00000;40.00000;-2.00000;,
 5.00000;40.00000;-2.00000;,
 0.00000;30.00000;-2.00000;,
 -5.00000;30.00000;-2.00000;,
 5.00000;30.00000;-2.00000;,
 0.00000;20.00000;-2.00000;,
 -5.00000;20.00000;-2.00000;,
 5.00000;20.00000;-2.00000;,
 0.00000;10.00000;-2.00000;,
 -5.00000;10.00000;-2.00000;,
 5.00000;10.00000;-2.00000;,
 0.00000;0.00000;-2.00000;,
 -5.00000;0.00000;-2.00000;,
 5.00000;0.00000;-2.00000;,
 5.00000;70.00000;-2.00000;,
 5.00000;70.00000;2.00000;,
 5.00000;60.00000;2.00000;,
 5.00000;60.00000;-2.00000;,
 5.00000;50.00000;2.00000;,
 5.00000;50.00000;-2.00000;,
 5.00000;40.00000;2.00000;,
 5.00000;40.00000;-2.00000;,
 5.00000;30.00000;2.00000;,
 5.00000;30.00000;-2.00000;,
 5.00000;20.00000;2.00000;,
 5.00000;20.00000;-2.00000;,
 5.00000;10.00000;2.00000;,
 5.00000;10.00000;-2.00000;,
 5.00000;0.00000;2.00000;,
 5.00000;0.00000;-2.00000;,
 5.00000;70.00000;2.00000;,
 0.00000;70.00000;2.00000;,
 0.00000;60.00000;2.00000;,
 5.00000;60.00000;2.00000;,
 -5.00000;70.00000;2.00000;,
 -5.00000;60.00000;2.00000;,
 0.00000;50.00000;2.00000;,
 5.00000;50.00000;2.00000;,
 -5.00000;50.00000;2.00000;,
 0.00000;40.00000;2.00000;,
 5.00000;40.00000;2.00000;,
 -5.00000;40.00000;2.00000;,
 0.00000;30.00000;2.00000;,
 5.00000;30.00000;2.00000;,
 -5.00000;30.00000;2.00000;,
 0.00000;20.00000;2.00000;,
 5.00000;20.00000;2.00000;,
 -5.00000;20.00000;2.00000;,
 0.00000;10.00000;2.00000;,
 5.00000;10.00000;2.00000;,
 -5.00000;10.00000;2.00000;,
 0.00000;0.00000;2.00000;,
 5.00000;0.00000;2.00000;,
 -5.00000;0.00000;2.00000;,
 -5.00000;70.00000;2.00000;,
 -5.00000;70.00000;-2.00000;,
 -5.00000;60.00000;-2.00000;,
 -5.00000;60.00000;2.00000;,
 -5.00000;50.00000;-2.00000;,
 -5.00000;50.00000;2.00000;,
 -5.00000;40.00000;-2.00000;,
 -5.00000;40.00000;2.00000;,
 -5.00000;30.00000;-2.00000;,
 -5.00000;30.00000;2.00000;,
 -5.00000;20.00000;-2.00000;,
 -5.00000;20.00000;2.00000;,
 -5.00000;10.00000;-2.00000;,
 -5.00000;10.00000;2.00000;,
 -5.00000;0.00000;-2.00000;,
 -5.00000;0.00000;2.00000;,
 -5.00000;0.00000;-2.00000;,
 0.00000;0.00000;-2.00000;,
 5.00000;0.00000;-2.00000;,
 0.00000;80.00000;2.00000;,
 0.00000;80.00000;-2.00000;,
 0.00000;80.00000;-2.00000;,
 60.00000;60.00000;-2.00000;,
 60.00000;52.00000;-2.00000;,
 45.00000;52.00000;-2.00000;,
 45.00000;60.00000;-2.00000;,
 60.00000;44.00000;-2.00000;,
 45.00000;44.00000;-2.00000;,
 30.00000;52.00000;-2.00000;,
 30.00000;60.00000;-2.00000;,
 30.00000;44.00000;-2.00000;,
 15.00000;52.00000;-2.00000;,
 15.00000;60.00000;-2.00000;,
 15.00000;44.00000;-2.00000;,
 0.00000;52.00000;-2.00000;,
 0.00000;60.00000;-2.00000;,
 0.00000;44.00000;-2.00000;,
 -15.00000;52.00000;-2.00000;,
 -15.00000;60.00000;-2.00000;,
 -15.00000;44.00000;-2.00000;,
 -30.00000;52.00000;-2.00000;,
 -30.00000;60.00000;-2.00000;,
 -30.00000;44.00000;-2.00000;,
 -45.00000;52.00000;-2.00000;,
 -45.00000;60.00000;-2.00000;,
 -45.00000;44.00000;-2.00000;,
 -60.00000;52.00000;-2.00000;,
 -60.00000;60.00000;-2.00000;,
 -60.00000;44.00000;-2.00000;,
 60.00000;44.00000;-2.00000;,
 60.00000;44.00000;2.00000;,
 45.00000;44.00000;2.00000;,
 45.00000;44.00000;-2.00000;,
 30.00000;44.00000;2.00000;,
 30.00000;44.00000;-2.00000;,
 15.00000;44.00000;2.00000;,
 15.00000;44.00000;-2.00000;,
 0.00000;44.00000;2.00000;,
 0.00000;44.00000;-2.00000;,
 -15.00000;44.00000;2.00000;,
 -15.00000;44.00000;-2.00000;,
 -30.00000;44.00000;2.00000;,
 -30.00000;44.00000;-2.00000;,
 -45.00000;44.00000;2.00000;,
 -45.00000;44.00000;-2.00000;,
 -60.00000;44.00000;2.00000;,
 -60.00000;44.00000;-2.00000;,
 60.00000;44.00000;2.00000;,
 60.00000;52.00000;2.00000;,
 45.00000;52.00000;2.00000;,
 45.00000;44.00000;2.00000;,
 60.00000;60.00000;2.00000;,
 45.00000;60.00000;2.00000;,
 30.00000;52.00000;2.00000;,
 30.00000;44.00000;2.00000;,
 30.00000;60.00000;2.00000;,
 15.00000;52.00000;2.00000;,
 15.00000;44.00000;2.00000;,
 15.00000;60.00000;2.00000;,
 0.00000;52.00000;2.00000;,
 0.00000;44.00000;2.00000;,
 0.00000;60.00000;2.00000;,
 -15.00000;52.00000;2.00000;,
 -15.00000;44.00000;2.00000;,
 -15.00000;60.00000;2.00000;,
 -30.00000;52.00000;2.00000;,
 -30.00000;44.00000;2.00000;,
 -30.00000;60.00000;2.00000;,
 -45.00000;52.00000;2.00000;,
 -45.00000;44.00000;2.00000;,
 -45.00000;60.00000;2.00000;,
 -60.00000;52.00000;2.00000;,
 -60.00000;44.00000;2.00000;,
 -60.00000;60.00000;2.00000;,
 60.00000;60.00000;2.00000;,
 60.00000;60.00000;-2.00000;,
 45.00000;60.00000;-2.00000;,
 45.00000;60.00000;2.00000;,
 30.00000;60.00000;-2.00000;,
 30.00000;60.00000;2.00000;,
 15.00000;60.00000;-2.00000;,
 15.00000;60.00000;2.00000;,
 0.00000;60.00000;-2.00000;,
 0.00000;60.00000;2.00000;,
 -15.00000;60.00000;-2.00000;,
 -15.00000;60.00000;2.00000;,
 -30.00000;60.00000;-2.00000;,
 -30.00000;60.00000;2.00000;,
 -45.00000;60.00000;-2.00000;,
 -45.00000;60.00000;2.00000;,
 -60.00000;60.00000;-2.00000;,
 -60.00000;60.00000;2.00000;,
 60.00000;52.00000;-2.00000;,
 60.00000;60.00000;-2.00000;,
 60.00000;44.00000;-2.00000;,
 -60.00000;60.00000;-2.00000;,
 -60.00000;52.00000;-2.00000;,
 -60.00000;44.00000;-2.00000;,
 35.00000;70.00000;-2.00000;,
 40.00000;70.00000;-2.00000;,
 40.00000;60.00000;-2.00000;,
 35.00000;60.00000;-2.00000;,
 45.00000;70.00000;-2.00000;,
 45.00000;60.00000;-2.00000;,
 40.00000;50.00000;-2.00000;,
 35.00000;50.00000;-2.00000;,
 45.00000;50.00000;-2.00000;,
 40.00000;40.00000;-2.00000;,
 35.00000;40.00000;-2.00000;,
 45.00000;40.00000;-2.00000;,
 40.00000;30.00000;-2.00000;,
 35.00000;30.00000;-2.00000;,
 45.00000;30.00000;-2.00000;,
 40.00000;20.00000;-2.00000;,
 35.00000;20.00000;-2.00000;,
 45.00000;20.00000;-2.00000;,
 40.00000;10.00000;-2.00000;,
 35.00000;10.00000;-2.00000;,
 45.00000;10.00000;-2.00000;,
 40.00000;0.00000;-2.00000;,
 35.00000;0.00000;-2.00000;,
 45.00000;0.00000;-2.00000;,
 45.00000;70.00000;-2.00000;,
 45.00000;70.00000;2.00000;,
 45.00000;60.00000;2.00000;,
 45.00000;60.00000;-2.00000;,
 45.00000;50.00000;2.00000;,
 45.00000;50.00000;-2.00000;,
 45.00000;40.00000;2.00000;,
 45.00000;40.00000;-2.00000;,
 45.00000;30.00000;2.00000;,
 45.00000;30.00000;-2.00000;,
 45.00000;20.00000;2.00000;,
 45.00000;20.00000;-2.00000;,
 45.00000;10.00000;2.00000;,
 45.00000;10.00000;-2.00000;,
 45.00000;0.00000;2.00000;,
 45.00000;0.00000;-2.00000;,
 45.00000;70.00000;2.00000;,
 40.00000;70.00000;2.00000;,
 40.00000;60.00000;2.00000;,
 45.00000;60.00000;2.00000;,
 35.00000;70.00000;2.00000;,
 35.00000;60.00000;2.00000;,
 40.00000;50.00000;2.00000;,
 45.00000;50.00000;2.00000;,
 35.00000;50.00000;2.00000;,
 40.00000;40.00000;2.00000;,
 45.00000;40.00000;2.00000;,
 35.00000;40.00000;2.00000;,
 40.00000;30.00000;2.00000;,
 45.00000;30.00000;2.00000;,
 35.00000;30.00000;2.00000;,
 40.00000;20.00000;2.00000;,
 45.00000;20.00000;2.00000;,
 35.00000;20.00000;2.00000;,
 40.00000;10.00000;2.00000;,
 45.00000;10.00000;2.00000;,
 35.00000;10.00000;2.00000;,
 40.00000;0.00000;2.00000;,
 45.00000;0.00000;2.00000;,
 35.00000;0.00000;2.00000;,
 35.00000;70.00000;2.00000;,
 35.00000;70.00000;-2.00000;,
 35.00000;60.00000;-2.00000;,
 35.00000;60.00000;2.00000;,
 35.00000;50.00000;-2.00000;,
 35.00000;50.00000;2.00000;,
 35.00000;40.00000;-2.00000;,
 35.00000;40.00000;2.00000;,
 35.00000;30.00000;-2.00000;,
 35.00000;30.00000;2.00000;,
 35.00000;20.00000;-2.00000;,
 35.00000;20.00000;2.00000;,
 35.00000;10.00000;-2.00000;,
 35.00000;10.00000;2.00000;,
 35.00000;0.00000;-2.00000;,
 35.00000;0.00000;2.00000;,
 35.00000;0.00000;-2.00000;,
 40.00000;0.00000;-2.00000;,
 45.00000;0.00000;-2.00000;,
 40.00000;80.00000;2.00000;,
 40.00000;80.00000;-2.00000;,
 40.00000;80.00000;-2.00000;,
 -45.00000;70.00000;-2.00000;,
 -40.00000;70.00000;-2.00000;,
 -40.00000;60.00000;-2.00000;,
 -45.00000;60.00000;-2.00000;,
 -35.00000;70.00000;-2.00000;,
 -35.00000;60.00000;-2.00000;,
 -40.00000;50.00000;-2.00000;,
 -45.00000;50.00000;-2.00000;,
 -35.00000;50.00000;-2.00000;,
 -40.00000;40.00000;-2.00000;,
 -45.00000;40.00000;-2.00000;,
 -35.00000;40.00000;-2.00000;,
 -40.00000;30.00000;-2.00000;,
 -45.00000;30.00000;-2.00000;,
 -35.00000;30.00000;-2.00000;,
 -40.00000;20.00000;-2.00000;,
 -45.00000;20.00000;-2.00000;,
 -35.00000;20.00000;-2.00000;,
 -40.00000;10.00000;-2.00000;,
 -45.00000;10.00000;-2.00000;,
 -35.00000;10.00000;-2.00000;,
 -40.00000;0.00000;-2.00000;,
 -45.00000;0.00000;-2.00000;,
 -35.00000;0.00000;-2.00000;,
 -35.00000;70.00000;-2.00000;,
 -35.00000;70.00000;2.00000;,
 -35.00000;60.00000;2.00000;,
 -35.00000;60.00000;-2.00000;,
 -35.00000;50.00000;2.00000;,
 -35.00000;50.00000;-2.00000;,
 -35.00000;40.00000;2.00000;,
 -35.00000;40.00000;-2.00000;,
 -35.00000;30.00000;2.00000;,
 -35.00000;30.00000;-2.00000;,
 -35.00000;20.00000;2.00000;,
 -35.00000;20.00000;-2.00000;,
 -35.00000;10.00000;2.00000;,
 -35.00000;10.00000;-2.00000;,
 -35.00000;0.00000;2.00000;,
 -35.00000;0.00000;-2.00000;,
 -35.00000;70.00000;2.00000;,
 -40.00000;70.00000;2.00000;,
 -40.00000;60.00000;2.00000;,
 -35.00000;60.00000;2.00000;,
 -45.00000;70.00000;2.00000;,
 -45.00000;60.00000;2.00000;,
 -40.00000;50.00000;2.00000;,
 -35.00000;50.00000;2.00000;,
 -45.00000;50.00000;2.00000;,
 -40.00000;40.00000;2.00000;,
 -35.00000;40.00000;2.00000;,
 -45.00000;40.00000;2.00000;,
 -40.00000;30.00000;2.00000;,
 -35.00000;30.00000;2.00000;,
 -45.00000;30.00000;2.00000;,
 -40.00000;20.00000;2.00000;,
 -35.00000;20.00000;2.00000;,
 -45.00000;20.00000;2.00000;,
 -40.00000;10.00000;2.00000;,
 -35.00000;10.00000;2.00000;,
 -45.00000;10.00000;2.00000;,
 -40.00000;0.00000;2.00000;,
 -35.00000;0.00000;2.00000;,
 -45.00000;0.00000;2.00000;,
 -45.00000;70.00000;2.00000;,
 -45.00000;70.00000;-2.00000;,
 -45.00000;60.00000;-2.00000;,
 -45.00000;60.00000;2.00000;,
 -45.00000;50.00000;-2.00000;,
 -45.00000;50.00000;2.00000;,
 -45.00000;40.00000;-2.00000;,
 -45.00000;40.00000;2.00000;,
 -45.00000;30.00000;-2.00000;,
 -45.00000;30.00000;2.00000;,
 -45.00000;20.00000;-2.00000;,
 -45.00000;20.00000;2.00000;,
 -45.00000;10.00000;-2.00000;,
 -45.00000;10.00000;2.00000;,
 -45.00000;0.00000;-2.00000;,
 -45.00000;0.00000;2.00000;,
 -45.00000;0.00000;-2.00000;,
 -40.00000;0.00000;-2.00000;,
 -35.00000;0.00000;-2.00000;,
 -40.00000;80.00000;2.00000;,
 -40.00000;80.00000;-2.00000;,
 -40.00000;80.00000;-2.00000;,
 60.00000;32.00000;-2.00000;,
 60.00000;24.00000;-2.00000;,
 45.00000;24.00000;-2.00000;,
 45.00000;32.00000;-2.00000;,
 60.00000;16.00000;-2.00000;,
 45.00000;16.00000;-2.00000;,
 30.00000;24.00000;-2.00000;,
 30.00000;32.00000;-2.00000;,
 30.00000;16.00000;-2.00000;,
 15.00000;24.00000;-2.00000;,
 15.00000;32.00000;-2.00000;,
 15.00000;16.00000;-2.00000;,
 0.00000;24.00000;-2.00000;,
 0.00000;32.00000;-2.00000;,
 0.00000;16.00000;-2.00000;,
 -15.00000;24.00000;-2.00000;,
 -15.00000;32.00000;-2.00000;,
 -15.00000;16.00000;-2.00000;,
 -30.00000;24.00000;-2.00000;,
 -30.00000;32.00000;-2.00000;,
 -30.00000;16.00000;-2.00000;,
 -45.00000;24.00000;-2.00000;,
 -45.00000;32.00000;-2.00000;,
 -45.00000;16.00000;-2.00000;,
 -60.00000;24.00000;-2.00000;,
 -60.00000;32.00000;-2.00000;,
 -60.00000;16.00000;-2.00000;,
 60.00000;16.00000;-2.00000;,
 60.00000;16.00000;2.00000;,
 45.00000;16.00000;2.00000;,
 45.00000;16.00000;-2.00000;,
 30.00000;16.00000;2.00000;,
 30.00000;16.00000;-2.00000;,
 15.00000;16.00000;2.00000;,
 15.00000;16.00000;-2.00000;,
 0.00000;16.00000;2.00000;,
 0.00000;16.00000;-2.00000;,
 -15.00000;16.00000;2.00000;,
 -15.00000;16.00000;-2.00000;,
 -30.00000;16.00000;2.00000;,
 -30.00000;16.00000;-2.00000;,
 -45.00000;16.00000;2.00000;,
 -45.00000;16.00000;-2.00000;,
 -60.00000;16.00000;2.00000;,
 -60.00000;16.00000;-2.00000;,
 60.00000;16.00000;2.00000;,
 60.00000;24.00000;2.00000;,
 45.00000;24.00000;2.00000;,
 45.00000;16.00000;2.00000;,
 60.00000;32.00000;2.00000;,
 45.00000;32.00000;2.00000;,
 30.00000;24.00000;2.00000;,
 30.00000;16.00000;2.00000;,
 30.00000;32.00000;2.00000;,
 15.00000;24.00000;2.00000;,
 15.00000;16.00000;2.00000;,
 15.00000;32.00000;2.00000;,
 0.00000;24.00000;2.00000;,
 0.00000;16.00000;2.00000;,
 0.00000;32.00000;2.00000;,
 -15.00000;24.00000;2.00000;,
 -15.00000;16.00000;2.00000;,
 -15.00000;32.00000;2.00000;,
 -30.00000;24.00000;2.00000;,
 -30.00000;16.00000;2.00000;,
 -30.00000;32.00000;2.00000;,
 -45.00000;24.00000;2.00000;,
 -45.00000;16.00000;2.00000;,
 -45.00000;32.00000;2.00000;,
 -60.00000;24.00000;2.00000;,
 -60.00000;16.00000;2.00000;,
 -60.00000;32.00000;2.00000;,
 60.00000;32.00000;2.00000;,
 60.00000;32.00000;-2.00000;,
 45.00000;32.00000;-2.00000;,
 45.00000;32.00000;2.00000;,
 30.00000;32.00000;-2.00000;,
 30.00000;32.00000;2.00000;,
 15.00000;32.00000;-2.00000;,
 15.00000;32.00000;2.00000;,
 0.00000;32.00000;-2.00000;,
 0.00000;32.00000;2.00000;,
 -15.00000;32.00000;-2.00000;,
 -15.00000;32.00000;2.00000;,
 -30.00000;32.00000;-2.00000;,
 -30.00000;32.00000;2.00000;,
 -45.00000;32.00000;-2.00000;,
 -45.00000;32.00000;2.00000;,
 -60.00000;32.00000;-2.00000;,
 -60.00000;32.00000;2.00000;,
 60.00000;24.00000;-2.00000;,
 60.00000;32.00000;-2.00000;,
 60.00000;16.00000;-2.00000;,
 -60.00000;32.00000;-2.00000;,
 -60.00000;24.00000;-2.00000;,
 -60.00000;16.00000;-2.00000;;
 
 254;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;7,6,9,10;,
 4;6,8,11,9;,
 4;10,9,12,13;,
 4;9,11,14,12;,
 4;13,12,15,16;,
 4;12,14,17,15;,
 4;16,15,18,19;,
 4;15,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;40,41,42,43;,
 4;41,44,45,42;,
 4;43,42,46,47;,
 4;42,45,48,46;,
 4;47,46,49,50;,
 4;46,48,51,49;,
 4;50,49,52,53;,
 4;49,51,54,52;,
 4;53,52,55,56;,
 4;52,54,57,55;,
 4;56,55,58,59;,
 4;55,57,60,58;,
 4;59,58,61,62;,
 4;58,60,63,61;,
 4;64,65,66,67;,
 4;67,66,68,69;,
 4;69,68,70,71;,
 4;71,70,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;80,81,61,79;,
 4;81,82,38,61;,
 4;83,84,65,64;,
 3;83,44,41;,
 3;1,0,85;,
 4;84,83,25,24;,
 3;4,1,85;,
 3;41,40,83;,
 4;86,87,88,89;,
 4;87,90,91,88;,
 4;89,88,92,93;,
 4;88,91,94,92;,
 4;93,92,95,96;,
 4;92,94,97,95;,
 4;96,95,98,99;,
 4;95,97,100,98;,
 4;99,98,101,102;,
 4;98,100,103,101;,
 4;102,101,104,105;,
 4;101,103,106,104;,
 4;105,104,107,108;,
 4;104,106,109,107;,
 4;108,107,110,111;,
 4;107,109,112,110;,
 4;113,114,115,116;,
 4;116,115,117,118;,
 4;118,117,119,120;,
 4;120,119,121,122;,
 4;122,121,123,124;,
 4;124,123,125,126;,
 4;126,125,127,128;,
 4;128,127,129,130;,
 4;131,132,133,134;,
 4;132,135,136,133;,
 4;134,133,137,138;,
 4;133,136,139,137;,
 4;138,137,140,141;,
 4;137,139,142,140;,
 4;141,140,143,144;,
 4;140,142,145,143;,
 4;144,143,146,147;,
 4;143,145,148,146;,
 4;147,146,149,150;,
 4;146,148,151,149;,
 4;150,149,152,153;,
 4;149,151,154,152;,
 4;153,152,155,156;,
 4;152,154,157,155;,
 4;158,159,160,161;,
 4;161,160,162,163;,
 4;163,162,164,165;,
 4;165,164,166,167;,
 4;167,166,168,169;,
 4;169,168,170,171;,
 4;171,170,172,173;,
 4;173,172,174,175;,
 4;158,132,176,177;,
 4;132,114,178,176;,
 4;179,180,155,175;,
 4;180,181,129,155;,
 4;182,183,184,185;,
 4;183,186,187,184;,
 4;185,184,188,189;,
 4;184,187,190,188;,
 4;189,188,191,192;,
 4;188,190,193,191;,
 4;192,191,194,195;,
 4;191,193,196,194;,
 4;195,194,197,198;,
 4;194,196,199,197;,
 4;198,197,200,201;,
 4;197,199,202,200;,
 4;201,200,203,204;,
 4;200,202,205,203;,
 4;206,207,208,209;,
 4;209,208,210,211;,
 4;211,210,212,213;,
 4;213,212,214,215;,
 4;215,214,216,217;,
 4;217,216,218,219;,
 4;219,218,220,221;,
 4;222,223,224,225;,
 4;223,226,227,224;,
 4;225,224,228,229;,
 4;224,227,230,228;,
 4;229,228,231,232;,
 4;228,230,233,231;,
 4;232,231,234,235;,
 4;231,233,236,234;,
 4;235,234,237,238;,
 4;234,236,239,237;,
 4;238,237,240,241;,
 4;237,239,242,240;,
 4;241,240,243,244;,
 4;240,242,245,243;,
 4;246,247,248,249;,
 4;249,248,250,251;,
 4;251,250,252,253;,
 4;253,252,254,255;,
 4;255,254,256,257;,
 4;257,256,258,259;,
 4;259,258,260,261;,
 4;262,263,243,261;,
 4;263,264,220,243;,
 4;265,266,247,246;,
 3;265,226,223;,
 3;183,182,267;,
 4;266,265,207,206;,
 3;186,183,267;,
 3;223,222,265;,
 4;268,269,270,271;,
 4;269,272,273,270;,
 4;271,270,274,275;,
 4;270,273,276,274;,
 4;275,274,277,278;,
 4;274,276,279,277;,
 4;278,277,280,281;,
 4;277,279,282,280;,
 4;281,280,283,284;,
 4;280,282,285,283;,
 4;284,283,286,287;,
 4;283,285,288,286;,
 4;287,286,289,290;,
 4;286,288,291,289;,
 4;292,293,294,295;,
 4;295,294,296,297;,
 4;297,296,298,299;,
 4;299,298,300,301;,
 4;301,300,302,303;,
 4;303,302,304,305;,
 4;305,304,306,307;,
 4;308,309,310,311;,
 4;309,312,313,310;,
 4;311,310,314,315;,
 4;310,313,316,314;,
 4;315,314,317,318;,
 4;314,316,319,317;,
 4;318,317,320,321;,
 4;317,319,322,320;,
 4;321,320,323,324;,
 4;320,322,325,323;,
 4;324,323,326,327;,
 4;323,325,328,326;,
 4;327,326,329,330;,
 4;326,328,331,329;,
 4;332,333,334,335;,
 4;335,334,336,337;,
 4;337,336,338,339;,
 4;339,338,340,341;,
 4;341,340,342,343;,
 4;343,342,344,345;,
 4;345,344,346,347;,
 4;348,349,329,347;,
 4;349,350,306,329;,
 4;351,352,333,332;,
 3;351,312,309;,
 3;269,268,353;,
 4;352,351,293,292;,
 3;272,269,353;,
 3;309,308,351;,
 4;354,355,356,357;,
 4;355,358,359,356;,
 4;357,356,360,361;,
 4;356,359,362,360;,
 4;361,360,363,364;,
 4;360,362,365,363;,
 4;364,363,366,367;,
 4;363,365,368,366;,
 4;367,366,369,370;,
 4;366,368,371,369;,
 4;370,369,372,373;,
 4;369,371,374,372;,
 4;373,372,375,376;,
 4;372,374,377,375;,
 4;376,375,378,379;,
 4;375,377,380,378;,
 4;381,382,383,384;,
 4;384,383,385,386;,
 4;386,385,387,388;,
 4;388,387,389,390;,
 4;390,389,391,392;,
 4;392,391,393,394;,
 4;394,393,395,396;,
 4;396,395,397,398;,
 4;399,400,401,402;,
 4;400,403,404,401;,
 4;402,401,405,406;,
 4;401,404,407,405;,
 4;406,405,408,409;,
 4;405,407,410,408;,
 4;409,408,411,412;,
 4;408,410,413,411;,
 4;412,411,414,415;,
 4;411,413,416,414;,
 4;415,414,417,418;,
 4;414,416,419,417;,
 4;418,417,420,421;,
 4;417,419,422,420;,
 4;421,420,423,424;,
 4;420,422,425,423;,
 4;426,427,428,429;,
 4;429,428,430,431;,
 4;431,430,432,433;,
 4;433,432,434,435;,
 4;435,434,436,437;,
 4;437,436,438,439;,
 4;439,438,440,441;,
 4;441,440,442,443;,
 4;426,400,444,445;,
 4;400,382,446,444;,
 4;447,448,423,443;,
 4;448,449,397,423;;
 
 MeshMaterialList {
  1;
  254;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.470588;0.078431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\fence100.jpg";
   }
  }
 }
 MeshNormals {
  34;
  -0.894427;0.447214;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.973249;0.229753;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.973249;0.229753;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.894427;0.447214;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.894427;0.447214;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.973249;0.229753;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -0.973249;0.229753;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.894427;0.447214;0.000000;,
  -0.894427;0.447214;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.973249;0.229753;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -0.973249;0.229753;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.894427;0.447214;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  254;
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;6,6,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,6,6;,
  3;3,3,3;,
  3;1,1,1;,
  4;8,8,2,2;,
  3;1,1,1;,
  3;3,3,3;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;12,12,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;15,15,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;10,10,15,15;,
  3;13,13,13;,
  3;11,11,11;,
  4;18,18,12,12;,
  3;11,11,11;,
  3;13,13,13;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;21,21,23,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;24,24,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;19,19,24,24;,
  3;22,22,22;,
  3;20,20,20;,
  4;27,27,21,21;,
  3;20,20,20;,
  3;22,22,22;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;33,33,33,33;;
 }
 MeshTextureCoords {
  450;
  0.000000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.000000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
