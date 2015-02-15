#ifndef FATSO_MESHDATA_H__
#define FATSO_MESHDATA_H__

int fatsoNbVerts = 376;
int fatsoNbData = 3008;

//Array to be parsed to way : x, y, z, r, g, b, u, v
float fatsoVerts [] = {
0.431737, 0.842168, -1, 1, 1, 1, 0.625113, 0.401873,
1, 0.842168, -1, 1, 1, 1, 0.624842, 0.313376,
1, 0.842168, -0.383323, 1, 1, 1, 0.720878, 0.313082,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0.72115, 0.401579,
0.431737, 2.842168, -0.383323, 1, 1, 1, 0.848105, 0.216113,
1, 2.842168, -0.383323, 1, 1, 1, 0.936602, 0.216384,
1, 2.842168, -0.999999, 1, 1, 1, 0.936307, 0.312421,
0.431738, 2.842168, -1, 1, 1, 1, 0.84781, 0.312149,
1, 0.842168, 0.372632, 1, 1, 1, 0.838605, 0.312721,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0.838877, 0.401218,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0.72115, 0.401579,
1, 0.842168, -0.383323, 1, 1, 1, 0.720878, 0.313082,
1, 0.842168, 1, 1, 1, 1, 0.936307, 0.312421,
0.431737, 0.842168, 1, 1, 1, 1, 0.936578, 0.400918,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0.838877, 0.401218,
1, 0.842168, 0.372632, 1, 1, 1, 0.838605, 0.312721,
0.431737, 2.842168, 0.372632, 1, 1, 1, 0.848466, 0.098386,
1, 2.842168, 0.372632, 1, 1, 1, 0.936963, 0.098657,
1, 2.842168, -0.383323, 1, 1, 1, 0.936602, 0.216384,
0.431737, 2.842168, -0.383323, 1, 1, 1, 0.848105, 0.216113,
0.431737, 2.842168, 1, 1, 1, 1, 0.848765, 0.000684,
0.999999, 2.842168, 1.000001, 1, 1, 1, 0.937262, 0.000955,
1, 2.842168, 0.372632, 1, 1, 1, 0.936963, 0.098657,
0.431737, 2.842168, 0.372632, 1, 1, 1, 0.848466, 0.098386,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0.721594, 0.546478,
-1, 0.842168, -0.383324, 1, 1, 1, 0.721834, 0.624547,
-1, 0.842168, -1, 1, 1, 1, 0.625797, 0.624842,
-0.4987, 0.842168, -1, 1, 1, 1, 0.625558, 0.546773,
-1, 2.842168, -0.383323, 1, 1, 1, 0.625136, 0.215429,
-0.4987, 2.842168, -0.383323, 1, 1, 1, 0.703205, 0.215668,
-0.4987, 2.842168, -1, 1, 1, 1, 0.70291, 0.311705,
-1, 2.842168, -1, 1, 1, 1, 0.624842, 0.311465,
-0.4987, 2.842168, -0.383323, 1, 1, 1, 0.703205, 0.215668,
0.431737, 2.842168, -0.383323, 1, 1, 1, 0.848105, 0.216113,
0.431738, 2.842168, -1, 1, 1, 1, 0.84781, 0.312149,
-0.4987, 2.842168, -1, 1, 1, 1, 0.70291, 0.311705,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0.838877, 0.401218,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0.839321, 0.546117,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0.721594, 0.546478,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0.72115, 0.401579,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0.839321, 0.546117,
-1, 0.842168, 0.372631, 1, 1, 1, 0.839561, 0.624186,
-1, 0.842168, -0.383324, 1, 1, 1, 0.721834, 0.624547,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0.721594, 0.546478,
-0.4987, 0.842168, 1, 1, 1, 1, 0.937023, 0.545817,
-1, 0.842168, 1, 1, 1, 1, 0.937262, 0.623886,
-1, 0.842168, 0.372631, 1, 1, 1, 0.839561, 0.624186,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0.839321, 0.546117,
-1, 2.842168, 0.372631, 1, 1, 1, 0.625497, 0.097702,
-0.4987, 2.842168, 0.372632, 1, 1, 1, 0.703566, 0.097941,
-0.4987, 2.842168, -0.383323, 1, 1, 1, 0.703205, 0.215668,
-1, 2.842168, -0.383323, 1, 1, 1, 0.625136, 0.215429,
-1, 2.842168, 1, 1, 1, 1, 0.625797, 0,
-0.4987, 2.842168, 1, 1, 1, 1, 0.703866, 0.000239,
-0.4987, 2.842168, 0.372632, 1, 1, 1, 0.703566, 0.097941,
-1, 2.842168, 0.372631, 1, 1, 1, 0.625497, 0.097702,
-0.4987, 2.842168, 1, 1, 1, 1, 0.703866, 0.000239,
0.431737, 2.842168, 1, 1, 1, 1, 0.848765, 0.000684,
0.431737, 2.842168, 0.372632, 1, 1, 1, 0.848466, 0.098386,
-0.4987, 2.842168, 0.372632, 1, 1, 1, 0.703566, 0.097941,
-0.4987, 2.842168, -0.383323, 1, 1, 1, 0.863692, 0.770028,
-0.4987, 2.842168, 0.372632, 1, 1, 1, 0.864054, 0.887755,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0.770614, 0.888041,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0.770253, 0.770314,
-0.4987, 2.842168, 0.372632, 1, 1, 1, 0.863692, 0.624842,
0.431737, 2.842168, 0.372632, 1, 1, 1, 0.864137, 0.769741,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0.770697, 0.770028,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0.770253, 0.625128,
0.431737, 2.842168, -0.383323, 1, 1, 1, 0.19203, 0.625129,
-0.4987, 2.842168, -0.383323, 1, 1, 1, 0.191586, 0.770028,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0.098146, 0.769741,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0.098591, 0.624842,
0.431737, 2.842168, 0.372632, 1, 1, 1, 0.191669, 0.770028,
0.431737, 2.842168, -0.383323, 1, 1, 1, 0.19203, 0.887755,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0.098591, 0.888041,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0.09823, 0.770315,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 3.442168, 0.372632, 1, 1, 1, 0.430592, 0.625203,
0.431737, 3.442168, 0.372632, 1, 1, 1, 0.430148, 0.770102,
0.431737, 3.442168, -0.383323, 1, 1, 1, 0.312421, 0.769741,
-0.4987, 3.442168, -0.383323, 1, 1, 1, 0.312865, 0.624842,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, 1, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0, 0,
-0.4987, 0.842168, 1, 1, 1, 1, 0.770553, 0.985934,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0.770253, 0.888232,
-0.4987, 0.442168, 0.372631, 1, 1, 1, 0.832546, 0.888041,
-0.4987, 0.442168, 1, 1, 1, 1, 0.832846, 0.985743,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0.937557, 0.479751,
-0.4987, 0.842168, -1, 1, 1, 1, 0.937262, 0.383714,
-0.4987, 0.442168, -1, 1, 1, 1, 0.999555, 0.383523,
-0.4987, 0.442168, -0.383323, 1, 1, 1, 0.99985, 0.47956,
-0.4987, 0.842168, 0.372631, 1, 1, 1, 0.562104, 0.936971,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0.562549, 0.792072,
0.431737, 0.442168, 0.372632, 1, 1, 1, 0.624842, 0.792263,
-0.4987, 0.442168, 0.372631, 1, 1, 1, 0.624397, 0.937162,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0.625286, 0.937162,
-0.4987, 0.842168, -0.383323, 1, 1, 1, 0.624842, 0.792262,
-0.4987, 0.442168, -0.383323, 1, 1, 1, 0.687135, 0.792071,
0.431737, 0.442168, -0.383323, 1, 1, 1, 0.687579, 0.936971,
0.431737, 0.842168, 1, 1, 1, 1, 0.864581, 0.936908,
-0.4987, 0.842168, 1, 1, 1, 1, 0.864137, 0.792009,
-0.4987, 0.442168, 1, 1, 1, 1, 0.92643, 0.791818,
0.431737, 0.442168, 1, 1, 1, 1, 0.926874, 0.936717,
-0.4987, 0.842168, -1, 1, 1, 1, 0.479875, 0.937162,
0.431737, 0.842168, -1, 1, 1, 1, 0.479431, 0.792263,
0.431737, 0.442168, -1, 1, 1, 1, 0.541724, 0.792072,
-0.4987, 0.442168, -1, 1, 1, 1, 0.542168, 0.936971,
0.431737, 0.842168, 0.372632, 1, 1, 1, 0.129737, 0.985934,
0.431737, 0.842168, 1, 1, 1, 1, 0.129438, 0.888233,
0.431737, 0.442168, 1, 1, 1, 1, 0.191731, 0.888041,
0.431737, 0.442168, 0.372632, 1, 1, 1, 0.19203, 0.985743,
0.431737, 0.842168, -1, 1, 1, 1, 0.067145, 0.984269,
0.431737, 0.842168, -0.383323, 1, 1, 1, 0.06685, 0.888233,
0.431737, 0.442168, -0.383323, 1, 1, 1, 0.129143, 0.888041,
0.431737, 0.442168, -1, 1, 1, 1, 0.129438, 0.984078,
0.431737, 0.442168, 1, 1, 1, 1, 0.097702, 0.624842,
-0.4987, 0.442168, 1, 1, 1, 1, 0.098146, 0.769741,
-0.4987, 0.442168, 0.372631, 1, 1, 1, 0.000444, 0.770041,
0.431737, 0.442168, 0.372632, 1, 1, 1, 0, 0.625142,
0.431737, 0.442168, -0.383323, 1, 1, 1, 0.311976, 0.624842,
-0.4987, 0.442168, -0.383323, 1, 1, 1, 0.312421, 0.769741,
-0.4987, 0.442168, -1, 1, 1, 1, 0.216384, 0.770036,
0.431737, 0.442168, -1, 1, 1, 1, 0.21594, 0.625136,
1, 2.842168, -0.383323, 1, 1, 1, 0.528805, 0.31176,
1, 2.362992, -0.383323, 1, 1, 1, 0.528576, 0.237136,
1, 2.362992, -1, 1, 1, 1, 0.624613, 0.236842,
1, 2.842168, -0.999999, 1, 1, 1, 0.624842, 0.311465,
-1, 2.842168, -1, 1, 1, 1, 0, 0.000956,
-1, 2.362992, -1, 1, 1, 1, 0.074623, 0.000727,
-1, 2.362992, -0.383323, 1, 1, 1, 0.074918, 0.096763,
-1, 2.842168, -0.383323, 1, 1, 1, 0.000295, 0.096992,
1, 2.842168, 0.372632, 1, 1, 1, 0.411078, 0.312121,
1, 2.362992, 0.372632, 1, 1, 1, 0.410849, 0.237498,
1, 2.362992, -0.383323, 1, 1, 1, 0.528576, 0.237136,
1, 2.842168, -0.383323, 1, 1, 1, 0.528805, 0.31176,
0.999999, 2.842168, 1.000001, 1, 1, 1, 0.313376, 0.312421,
0.999999, 2.362992, 1, 1, 1, 1, 0.313147, 0.237797,
1, 2.362992, 0.372632, 1, 1, 1, 0.410849, 0.237498,
1, 2.842168, 0.372632, 1, 1, 1, 0.411078, 0.312121,
-1, 2.842168, 0.372631, 1, 1, 1, 0.000656, 0.214719,
-1, 2.362992, 0.372631, 1, 1, 1, 0.075279, 0.21449,
-1, 2.362992, 1, 1, 1, 1, 0.075579, 0.312192,
-1, 2.842168, 1, 1, 1, 1, 0.000956, 0.312421,
-1, 2.842168, -0.383323, 1, 1, 1, 0.000295, 0.096992,
-1, 2.362992, -0.383323, 1, 1, 1, 0.074918, 0.096763,
-1, 2.362992, 0.372631, 1, 1, 1, 0.075279, 0.21449,
-1, 2.842168, 0.372631, 1, 1, 1, 0.000656, 0.214719,
0.431737, 2.842168, 1, 1, 1, 1, 0.400918, 0.313105,
0.431737, 2.362992, 1, 1, 1, 1, 0.401147, 0.387728,
0.999999, 2.362992, 1, 1, 1, 1, 0.31265, 0.388,
0.999999, 2.842168, 1.000001, 1, 1, 1, 0.312421, 0.313376,
0.431737, 2.362992, -1, 1, 1, 1, 0.074895, 0.401645,
0.431738, 2.842168, -1, 1, 1, 1, 0.000271, 0.401873,
1, 2.842168, -0.999999, 1, 1, 1, 0, 0.313376,
1, 2.362992, -1, 1, 1, 1, 0.074623, 0.313148,
-0.4987, 2.842168, 1, 1, 1, 1, 0.545817, 0.31266,
-0.4987, 2.362992, 1, 1, 1, 1, 0.546046, 0.387284,
0.431737, 2.362992, 1, 1, 1, 1, 0.401147, 0.387728,
0.431737, 2.842168, 1, 1, 1, 1, 0.400918, 0.313105,
-1, 2.842168, 1, 1, 1, 1, 0.623886, 0.312421,
-1, 2.362992, 1, 1, 1, 1, 0.624115, 0.387044,
-0.4987, 2.362992, 1, 1, 1, 1, 0.546046, 0.387284,
-0.4987, 2.842168, 1, 1, 1, 1, 0.545817, 0.31266,
-0.4987, 2.362992, -1, 1, 1, 1, 0.075339, 0.546544,
-0.4987, 2.842168, -1, 1, 1, 1, 0.000716, 0.546773,
0.431738, 2.842168, -1, 1, 1, 1, 0.000271, 0.401873,
0.431737, 2.362992, -1, 1, 1, 1, 0.074895, 0.401645,
-1, 2.362992, -1, 1, 1, 1, 0.075579, 0.624613,
-1, 2.842168, -1, 1, 1, 1, 0.000956, 0.624842,
-0.4987, 2.842168, -1, 1, 1, 1, 0.000716, 0.546773,
-0.4987, 2.362992, -1, 1, 1, 1, 0.075339, 0.546544,
1, 2.362992, -0.383323, 1, 1, 1, 0.528576, 0.237136,
1, 1.29202, -0.383323, 1, 1, 1, 0.528064, 0.070351,
1, 1.29202, -1, 1, 1, 1, 0.624101, 0.070057,
1, 2.362992, -1, 1, 1, 1, 0.624613, 0.236842,
1, 0.842168, -1, 1, 1, 1, 0.623886, 0,
1, 1.29202, -1, 1, 1, 1, 0.624101, 0.070057,
1, 1.29202, -0.383323, 1, 1, 1, 0.528064, 0.070351,
1, 0.842168, -0.383323, 1, 1, 1, 0.527849, 0.000295,
-1, 2.362992, -1, 1, 1, 1, 0.074623, 0.000727,
-1, 1.29202, -1, 1, 1, 1, 0.241409, 0.000215,
-1, 1.29202, -0.383323, 1, 1, 1, 0.241703, 0.096252,
-1, 2.362992, -0.383323, 1, 1, 1, 0.074918, 0.096763,
-1, 1.29202, -1, 1, 1, 1, 0.241409, 0.000215,
-1, 0.842168, -1, 1, 1, 1, 0.311465, 0,
-1, 0.842168, -0.383324, 1, 1, 1, 0.31176, 0.096037,
-1, 1.29202, -0.383323, 1, 1, 1, 0.241703, 0.096252,
1, 2.362992, 0.372632, 1, 1, 1, 0.410849, 0.237498,
1, 1.29202, 0.372632, 1, 1, 1, 0.410338, 0.070712,
1, 1.29202, -0.383323, 1, 1, 1, 0.528064, 0.070351,
1, 2.362992, -0.383323, 1, 1, 1, 0.528576, 0.237136,
1, 1.29202, 0.372632, 1, 1, 1, 0.410338, 0.070712,
1, 0.842168, 0.372632, 1, 1, 1, 0.410123, 0.000656,
1, 0.842168, -0.383323, 1, 1, 1, 0.527849, 0.000295,
1, 1.29202, -0.383323, 1, 1, 1, 0.528064, 0.070351,
0.999999, 2.362992, 1, 1, 1, 1, 0.313147, 0.237797,
1, 1.29202, 1, 1, 1, 1, 0.312636, 0.071012,
1, 1.29202, 0.372632, 1, 1, 1, 0.410338, 0.070712,
1, 2.362992, 0.372632, 1, 1, 1, 0.410849, 0.237498,
1, 1.29202, 1, 1, 1, 1, 0.312636, 0.071012,
1, 0.842168, 1, 1, 1, 1, 0.312421, 0.000956,
1, 0.842168, 0.372632, 1, 1, 1, 0.410123, 0.000656,
1, 1.29202, 0.372632, 1, 1, 1, 0.410338, 0.070712,
-1, 2.362992, 0.372631, 1, 1, 1, 0.075279, 0.21449,
-1, 1.29202, 0.372631, 1, 1, 1, 0.242064, 0.213979,
-1, 1.29202, 1, 1, 1, 1, 0.242364, 0.31168,
-1, 2.362992, 1, 1, 1, 1, 0.075579, 0.312192,
-1, 1.29202, 0.372631, 1, 1, 1, 0.242064, 0.213979,
-1, 0.842168, 0.372631, 1, 1, 1, 0.312121, 0.213764,
-1, 0.842168, 1, 1, 1, 1, 0.312421, 0.311465,
-1, 1.29202, 1, 1, 1, 1, 0.242364, 0.31168,
-1, 2.362992, -0.383323, 1, 1, 1, 0.074918, 0.096763,
-1, 1.29202, -0.383323, 1, 1, 1, 0.241703, 0.096252,
-1, 1.29202, 0.372631, 1, 1, 1, 0.242064, 0.213979,
-1, 2.362992, 0.372631, 1, 1, 1, 0.075279, 0.21449,
-1, 1.29202, -0.383323, 1, 1, 1, 0.241703, 0.096252,
-1, 0.842168, -0.383324, 1, 1, 1, 0.31176, 0.096037,
-1, 0.842168, 0.372631, 1, 1, 1, 0.312121, 0.213764,
-1, 1.29202, 0.372631, 1, 1, 1, 0.242064, 0.213979,
0.431737, 2.362992, 1, 1, 1, 1, 0.401147, 0.387728,
0.431737, 1.29202, 1, 1, 1, 1, 0.401659, 0.554514,
1, 1.29202, 1, 1, 1, 1, 0.313161, 0.554785,
0.999999, 2.362992, 1, 1, 1, 1, 0.31265, 0.388,
0.431737, 1.29202, 1, 1, 1, 1, 0.401659, 0.554514,
0.431737, 0.842168, 1, 1, 1, 1, 0.401873, 0.62457,
1, 0.842168, 1, 1, 1, 1, 0.313376, 0.624842,
1, 1.29202, 1, 1, 1, 1, 0.313161, 0.554785,
1, 1.29202, -1, 1, 1, 1, 0.241409, 0.312636,
1, 0.842168, -1, 1, 1, 1, 0.311465, 0.312421,
0.431737, 0.842168, -1, 1, 1, 1, 0.311737, 0.400918,
0.431737, 1.29202, -1, 1, 1, 1, 0.24168, 0.401133,
0.431737, 1.29202, -1, 1, 1, 1, 0.24168, 0.401133,
0.431737, 2.362992, -1, 1, 1, 1, 0.074895, 0.401645,
1, 2.362992, -1, 1, 1, 1, 0.074623, 0.313148,
1, 1.29202, -1, 1, 1, 1, 0.241409, 0.312636,
-0.4987, 1.29202, 1, 1, 1, 1, 0.546558, 0.554069,
-0.4987, 0.842168, 1, 1, 1, 1, 0.546773, 0.624126,
0.431737, 0.842168, 1, 1, 1, 1, 0.401873, 0.62457,
0.431737, 1.29202, 1, 1, 1, 1, 0.401659, 0.554514,
-1, 2.362992, 1, 1, 1, 1, 0.624115, 0.387044,
-1, 1.29202, 1, 1, 1, 1, 0.624627, 0.553829,
-0.4987, 1.29202, 1, 1, 1, 1, 0.546558, 0.554069,
-0.4987, 2.362992, 1, 1, 1, 1, 0.546046, 0.387284,
-1, 1.29202, 1, 1, 1, 1, 0.624627, 0.553829,
-1, 0.842168, 1, 1, 1, 1, 0.624842, 0.623886,
-0.4987, 0.842168, 1, 1, 1, 1, 0.546773, 0.624126,
-0.4987, 1.29202, 1, 1, 1, 1, 0.546558, 0.554069,
-0.4987, 0.842168, -1, 1, 1, 1, 0.312181, 0.545817,
-0.4987, 1.29202, -1, 1, 1, 1, 0.242125, 0.546032,
0.431737, 1.29202, -1, 1, 1, 1, 0.24168, 0.401133,
0.431737, 0.842168, -1, 1, 1, 1, 0.311737, 0.400918,
-1, 0.842168, -1, 1, 1, 1, 0.312421, 0.623886,
-1, 1.29202, -1, 1, 1, 1, 0.242364, 0.624101,
-0.4987, 1.29202, -1, 1, 1, 1, 0.242125, 0.546032,
-0.4987, 0.842168, -1, 1, 1, 1, 0.312181, 0.545817,
-1, 1.29202, -1, 1, 1, 1, 0.242364, 0.624101,
-1, 2.362992, -1, 1, 1, 1, 0.075579, 0.624613,
-0.4987, 2.362992, -1, 1, 1, 1, 0.075339, 0.546544,
-0.4987, 1.29202, -1, 1, 1, 1, 0.242125, 0.546032,
-0.4987, 1.29202, 1, 1, 1, 1, 0.927386, 0.791818,
0.431737, 1.29202, 1, 1, 1, 1, 0.926942, 0.646918,
0.431737, 1.29202, 1.4, 1, 1, 1, 0.989235, 0.646727,
-0.4987, 1.29202, 1.4, 1, 1, 1, 0.989679, 0.791627,
-0.4987, 2.362992, 1, 1, 1, 1, 0.250128, 0.937012,
-0.4987, 1.29202, 1, 1, 1, 1, 0.249616, 0.770227,
-0.4987, 1.29202, 1.4, 1, 1, 1, 0.311909, 0.770036,
-0.4987, 2.362992, 1.4, 1, 1, 1, 0.312421, 0.936821,
0.431737, 1.29202, 1, 1, 1, 1, 0.926942, 0.625033,
0.431737, 2.362992, 1, 1, 1, 1, 0.92643, 0.791818,
0.431737, 2.362992, 1.4, 1, 1, 1, 0.864137, 0.791627,
0.431737, 1.29202, 1.4, 1, 1, 1, 0.864649, 0.624842,
0.431737, 2.362992, 1, 1, 1, 1, 0.937262, 0.624651,
-0.4987, 2.362992, 1, 1, 1, 1, 0.937707, 0.479751,
-0.4987, 2.362992, 1.4, 1, 1, 1, 1, 0.479942,
0.431737, 2.362992, 1.4, 1, 1, 1, 0.999555, 0.624842,
-0.4987, 2.362992, 1.4, 1, 1, 1, 0.62433, 0.624842,
-0.4987, 1.29202, 1.4, 1, 1, 1, 0.624842, 0.791627,
0.431737, 1.29202, 1.4, 1, 1, 1, 0.479942, 0.792072,
0.431737, 2.362992, 1.4, 1, 1, 1, 0.479431, 0.625286,
0.431737, 1.29202, -1, 1, 1, 1, 0.989168, 0.791818,
-0.4987, 1.29202, -1, 1, 1, 1, 0.989612, 0.936717,
-0.4987, 1.29202, -1.4, 1, 1, 1, 0.927319, 0.936908,
0.431737, 1.29202, -1.4, 1, 1, 1, 0.926874, 0.792009,
-0.4987, 1.29202, -1, 1, 1, 1, 0.062805, 0.770232,
-0.4987, 2.362992, -1, 1, 1, 1, 0.062293, 0.937017,
-0.4987, 2.362992, -1.4, 1, 1, 1, 0, 0.936826,
-0.4987, 1.29202, -1.4, 1, 1, 1, 0.000512, 0.770041,
0.431737, 2.362992, -1, 1, 1, 1, 0.368299, 0.937079,
0.431737, 1.29202, -1, 1, 1, 1, 0.367787, 0.770293,
0.431737, 1.29202, -1.4, 1, 1, 1, 0.430081, 0.770102,
0.431738, 2.362992, -1.4, 1, 1, 1, 0.430592, 0.936888,
-0.4987, 2.362992, -1, 1, 1, 1, 0.770253, 0.792262,
0.431737, 2.362992, -1, 1, 1, 1, 0.769808, 0.937162,
0.431738, 2.362992, -1.4, 1, 1, 1, 0.707515, 0.936971,
-0.4987, 2.362992, -1.4, 1, 1, 1, 0.70796, 0.792071,
-0.4987, 1.29202, -1.4, 1, 1, 1, 0.770253, 0.625286,
-0.4987, 2.362992, -1.4, 1, 1, 1, 0.769741, 0.792071,
0.431738, 2.362992, -1.4, 1, 1, 1, 0.624842, 0.791627,
0.431737, 1.29202, -1.4, 1, 1, 1, 0.625353, 0.624842
};
#endif
