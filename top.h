/* Author Sam Muir
3/23/2010 */
#ifndef _TOP
#define _TOP

#include "cube.h"


unsigned char flip_corner_loc(unsigned char location);
unsigned char flip_edge_loc(unsigned char location);
unsigned char get_top_color_process(void);
unsigned char get_top_sides_process(void);
unsigned char top_color(void);
void top_sides(void);


unsigned char stage3_front;
unsigned char stage4_front;
unsigned char stage4_pos_table[15][2] = {//lookup table for positions on top layer. index corresponds to table full of moves. Source:http://www.ws.binghamton.edu/fridrich/Mike/permute.html
						//first number is permutation of edges, bits (0,1) say where edge 0 should go (0 1 2 or 3), bits (2,3)=edge1, ect.
						//second number is permutation of corners, assigned the same way as first number. (0xE4 = correct already)
	{0xE4,0xE4},	    //	{0b1110 0100,0b1110 0100},	    //0, solved!
	{0x36,0xE4},	    //	{0b0011 0110,0b1110 0100},	    //1	= U formation
	{0xE4,0xD2},		//	{0b1110 0100,0b1101 0010},		//2 = A formation
	{0xB1,0xE4},		//	{0b1011 0001,0b1110 0100},		//3 = Z formation
	{0x4E,0xE4},		//	{0b0100 1110,0b1110 0100},		//4 = H formation
	{0xE4,0x1B},		//	{0b1110 0100,0b0001 1011},		//5 = E formation
	{0xC6,0xD8},		//	{0b1100 0110,0b1101 1000},		//6 = T formation
	{0x27,0xC6},		//	{0b0010 0111,0b1100 0110},		//7 = V formation
	{0xC6,0xB4},		//	{0b1100 0110,0b1011 0100},		//8 = F formation
	{0x27,0xD8},		//	{0b0010 0111,0b1101 1000},		//9 = R formation
	{0x27,0xB4},		//	{0b0010 0111,0b1011 0100},		//10 = J formation
	{0xE1,0xC6},		//	{0b1110 0001,0b1100 0110},		//11 = Y formation
	{0x9C,0x78},		//	{0b1001 1100,0b0111 1000},		//12 = G formation
	{0x6C,0x6C},		//	{0b0110 1100,0b0110 1100},		//13 = N formation
	{0x78,0x9C}			//	{0b0111 1000,0b1001 1100},		//14 = G' formation
};

unsigned char stage4_move_table[15][14] = {//lookup table for moves on top layer. index corresponds to table full of moves. Source:http://www.ws.binghamton.edu/fridrich/Mike/permute.html
						//index is the same as stage4_pos_table
	{20,20,20,20,20,20,20,20,20,20,20,20,20,20},	    //0, solved!
	{10,0,1,15,10,3,13,0,10,20,20,20,20,20},	    //1	= U formation
	{2,13,2,9,14,1,2,9,8,20,20,20,20,20},		//2 = A formation
	{16,1,4,13,15,4,1,15,4,13,16,9,20,20},		//3b = Z formation
	{10,9,7,8,17,10,9,7,8,20,20,20,20,20},		//4b = H formation
	{4,3,2,15,16,1,3,4,13,14,1,16,13,15},		//5a = E formation
	{9,5,8,17,9,10,17,7,5,10,20,20,20,20},		//6a = T formation
	{13,0,13,12,16,5,16,17,10,13,16,1,4,1},		//7b = V formation
	{13,3,8,3,17,1,8,15,0,7,15,10,7,20},		//8b* = F formation
	{16,6,4,12,13,2,1,16,13,14,1,12,4,20},		//9a* = R formation
	{9,2,0,14,9,4,17,4,5,10,20,20,20,20},		//10a = J formation
	{4,3,12,15,4,5,15,14,15,2,9,17,10,20},		//11a = Y formation
	{1,0,13,8,17,3,12,15,0,15,5,8,20,20},		//12b = G formation
	{4,17,7,8,17,2,9,14,5,8,7,5,16,20},			//13b = N formation
	{8,17,3,12,3,0,15,5,8,1,12,13,20,20}			//12b' = G' formation
};

unsigned char stage3_pos_table[41][2] = {//lookup table for positions on top layer. index corresponds to table full of moves. Source:http://www.ws.binghamton.edu/fridrich/Mike/orient.html
						//first number is orientation of edges, bits 0-3 corresponding to edges 0-3 1=facing up
						//second number is orientation of corners, 2 bits for each corner, 00 = facing up, 01 = facing l/r 10 = facing up/down
	{0x0F,0x00},	    //	{0b00001111,0b00000000},	    //0	
	{0x00,0x55},	    //	{0b00000000,0b01010101},	    //1	
	{0x00,0x5A},		//	{0b00000000,0b01011010},		//2
	{0x00,0x26},		//	{0b00000000,0b00100110},		//3
	{0x00,0x12},		//	{0b00000000,0b00010010},		//4
	{0x00,0x82},		//	{0b00000000,0b10000010},		//5
	{0x00,0x41},		//	{0b00000000,0b01000001},		//6
	{0x00,0x00},		//	{0b00000000,0b00000000},		//7
	{0x05,0x55},		//	{0b00000101,0b01010101},		//8
	{0x05,0xAA},		//	{0b00000101,0b10101010},		//9
	{0x05,0x96},		//	{0b00000101,0b10010110},		//10
	{0x05,0x5A},		//	{0b00000101,0b01011010},		//11
	{0x03,0x55},		//	{0b00000011,0b01010101},		//12
	{0x03,0x5A},		//	{0b00000011,0b01011010},		//13
	{0x03,0x96},		//	{0b00000011,0b10010110},		//14
	{0x09,0x89},		//	{0b00001001,0b10001001},		//15
	{0x09,0x46},		//	{0b00001001,0b01000110},		//16
	{0x09,0x62},		//	{0b00001001,0b01100010},		//17
	{0x09,0x19},		//	{0b00001001,0b00011001},		//18
	{0x0A,0x89},		//	{0b00001010,0b10001001},		//19
	{0x0A,0x46},		//	{0b00001010,0b01000110},		//20
	{0x09,0x82},		//	{0b00001001,0b10000010},		//21
	{0x09,0x41},		//	{0b00001001,0b01000001},		//22
	{0x09,0x0A},		//	{0b00001001,0b00001010},		//23
	{0x09,0x21},		//	{0b00001001,0b00100001},		//24
	{0x09,0x05},		//	{0b00001001,0b00000101},		//25
	{0x09,0x12},		//	{0b00001001,0b00010010},		//26
	{0x05,0x82},		//	{0b00000101,0b10000010},		//27
	{0x05,0x41},		//	{0b00000101,0b01000001},		//28
	{0x0A,0x84},		//	{0b00001010,0b10000100},		//29
	{0x0A,0x41},		//	{0b00001010,0b01000001},		//30
	{0x0A,0x82},		//	{0b00001010,0b10000010},		//31
	{0x09,0x84},		//	{0b00001001,0b10000100},		//32
	{0x0F,0x55},		//	{0b00001111,0b01010101},		//33
	{0x0F,0xA5},		//	{0b00001111,0b10100101},		//34
	{0x0F,0x50},		//	{0b00001111,0b01010000},		//35
	{0x0F,0xA0},		//	{0b00001111,0b10100000},		//36
	{0x0F,0x21},		//	{0b00001111,0b00100001},		//37
	{0x0F,0x64},		//	{0b00001111,0b01100100},		//38
	{0x06,0x00},		//	{0b00000110,0b00000000},		//39
	{0x05,0x00}			//	{0b00000101,0b00000000}			//40
};
unsigned char stage3_move_table[41][12] = {//lookup table for moves on top layer. index corresponds to table full of positions. Source:http://www.ws.binghamton.edu/fridrich/Mike/orient.html
	{20,20,20,20,20,20,20,20,20,20,20,20},	//0	 - Top already aligned correctly.
	{4,0,15,4,3,10,12,16,1,4,13,20},	    //1b	
	{1,16,13,4,0,10,15,16,3,12,16,20},		//2b
	{4,14,15,2,6,14,15,4,15,10,2,20},		//3b
	{2,13,14,1,6,1,12,4,12,16,13,20},		//4b
	{3,2,0,14,0,15,6,15,4,3,16,20},			//5b
	{4,9,0,14,12,15,0,2,15,12,16,20},		//6b
	{10,6,3,13,14,9,7,16,11,10,3,13},		//7b
	{2,1,12,4,0,10,13,14,1,4,13,20},		//8a
	{3,2,1,14,9,2,0,13,12,14,3,20},			//9b
	{2,0,1,12,13,0,1,12,13,14,20,20},		//10
	{4,0,3,12,3,14,15,2,15,16,20,20},		//11a
	{1,16,13,4,6,7,2,1,14,1,20,20},			//12a
	{4,13,6,1,6,1,10,13,4,20,20,20},		//13a
	{4,3,0,15,12,3,0,15,12,16,20,20},		//14
	{4,3,14,3,2,9,16,20,20,20,20,20},		//15a
	{13,14,3,14,3,17,15,5,15,8,1,20},		//16b
	{14,12,2,3,14,15,0,3,2,15,20,20},		//17a
	{14,9,4,3,16,3,2,20,20,20,20,20},		//18a
	{4,15,16,12,4,3,16,15,0,3,20,20},		//19
	{2,1,14,4,0,16,12,2,13,14,20,20},		//20a
	{4,12,16,6,4,0,3,12,15,12,16,20},		//21b
	{3,0,2,12,1,14,15,2,13,14,20,20},		//22a
	{4,0,15,12,16,0,4,3,16,20,20,20},		//23a
	{3,14,15,2,0,2,12,14,20,20,20,20},		//24a
	{3,0,2,12,14,15,20,20,20,20,20,20},		//25a
	{13,6,7,16,13,4,13,6,1,20,20,20},		//26
	{4,3,0,15,12,16,20,20,20,20,20,20},		//27
	{15,12,3,0,3,14,15,2,20,20,20,20},		//28
	{4,15,16,12,4,0,3,12,16,20,20,20},		//29
	{2,0,14,12,13,14,3,2,1,15,20,20},		//30a
	{1,4,12,3,0,15,16,13,20,20,20,20},		//31a
	{4,3,0,9,12,16,0,4,3,16,20,20},			//32a
	{2,0,14,0,2,0,16,0,14,12,4,20},			//33b
	{4,6,10,12,10,12,10,6,4,20,20,20},		//34a
	{7,17,1,6,13,5,1,6,1,20,20,20},			//35a
	{16,13,2,1,4,13,14,1,20,20,20,20},		//36
	{16,13,14,1,4,13,2,1,20,20,20,20},		//37
	{15,0,1,12,3,0,13,20,20,20,20,20},		//38a
	{2,13,2,7,16,1,4,7,8,20,20,20},			//39b
	{1,15,0,13,12,3,13,2,1,14,20,20}		//40a
};






unsigned char flip_corner_loc(unsigned char location){		//flips a corner over the FR-LB axis.
	switch(location){
		case 0: return 2;
		case 2: return 0;
		default: return location;
	}
}

unsigned char flip_edge_loc(unsigned char location){		//flips an edge over the FR-LB axis.
	switch(location){
		case 0: return 3;
		case 1: return 2;
		case 2: return 1;
		default: return 0;
	}
}


unsigned char get_top_color_process(void){		//read top of top layer, match layer to correct algorithm
	unsigned char top_edges[4] = {0,0,0,0};
	unsigned char top_corners[4] = {0,0,0,0};
	unsigned char i, j, edgebyte, cornerbyte, currentcorner, tempedge, tempcorner;
	stage3_front = 1;
	for(i=0; i<4; i++){							//read in top edges, corners for comparison with stage 3 position lookup table
		if(edges[i][0] == 0) top_edges[i] = 1;
		if(corners[i][1] == 0) top_corners[i] = 2;
		if(corners[i][2] == 0) top_corners[i] = 1;
	}
	for(i=0; i<4; i++){
		edgebyte = 0;
		cornerbyte = 0;
		for(j=0; j< 4; j++){				//set bytes to contain data corresponding to top face
			edgebyte |= (top_edges[j] << j);
			cornerbyte |= (top_corners[j] << (j*2));
		}
		for(j=0; j<41; j++){
			if(stage3_pos_table[j][0] == edgebyte && stage3_pos_table[j][1] == cornerbyte) return j;
		}
		edgebyte = 0;
		cornerbyte = 0;
		for(j=0; j< 4; j++){				//set bytes to contain data corresponding to top face reflected over fr to lb diagonal
			edgebyte |= (top_edges[3-j] << j);
			if(j < 2) {
				currentcorner = top_corners[2-j];
				if(currentcorner != 0) cornerbyte |= ((3-currentcorner)<<(j*2));
			} else {
				currentcorner = top_corners[(j-2)*3];
				if(currentcorner != 0) cornerbyte |= ((3-currentcorner)<<(j*2));
			}
		}
		for(j=0; j<41; j++){
			if(stage3_pos_table[j][0] == edgebyte && stage3_pos_table[j][1] == cornerbyte) return j+50;
		}
		tempedge = top_edges[0];		//rotate cube counterclockwise, considering a different side as the front to find a match.
		tempcorner = top_corners[0];
		for(j=0; j<3;j++) {
			top_edges[j] = top_edges[j+1];
			top_corners[j] = top_corners[j+1];
		}
		top_edges[3] = tempedge;
		top_corners[3] = tempcorner;
		for(j=0; j<4; j++){
			if(top_corners[j] != 0) top_corners[j] = 3 - top_corners[j];
		}
		stage3_front++;
	}
	return 100;		//should never get here!
}

unsigned char get_top_sides_process(void){				//read sides of top layer, match layer to correct algorithm
	unsigned char i, j, edgebyte, cornerbyte, frontcolor = 1, edge_dest[4], corner_dest[4], current_place;
	for(frontcolor=1; frontcolor<5; frontcolor++){
		for(j=0;j<4;j++){
			edge_dest[j] = ((edges[j][1] - 1) + 4 - (frontcolor-1)) % 4;		//find where current edge needs to go.
			corner_dest[j] = corners[j][1] + corners[j][2];
			if(corner_dest[j] == 3) corner_dest[j] = 0;			//determine where current corner needs to go
			else {
				if(corner_dest[j] == 7) corner_dest[j] = 2;
				else{
					if(corners[j][1] == 1 || corners[j][1] == 4) corner_dest[j] = 3;
					else corner_dest[j] = 1;
				}
			}
			corner_dest[j] = (corner_dest[j] + 4 - (frontcolor-1)) % 4;		//adjust corner destination depending on frontcolor
		}
		for(stage4_front=1;stage4_front<5;stage4_front++){
			edgebyte = 0;
			cornerbyte = 0;
			for(i=0;i<4;i++){		//read corner destinations with current front face.
				current_place = (i + stage4_front - 1) % 4;
				edgebyte |= (((4+edge_dest[current_place]-(stage4_front-1))%4) << (i*2));
				cornerbyte |= (((4+corner_dest[current_place]-(stage4_front-1))%4) << (i*2));
			}
			for(i=0;i<15;i++){
				if(edgebyte == stage4_pos_table[i][0] && cornerbyte == stage4_pos_table[i][1]) return i;
			}

			edgebyte = 0;
			cornerbyte = 0;
			for(i=0;i<4;i++){		//read corner destinations with current front face, this time places are flipped over fr-lb plane
				current_place = (i + stage4_front - 1) % 4;
				edgebyte |= (((4+flip_edge_loc(edge_dest[flip_edge_loc(current_place)])-(stage4_front-1))%4) << (i*2));
				cornerbyte |= (((4+flip_corner_loc(corner_dest[flip_corner_loc(current_place)])-(stage4_front-1))%4) << (i*2));
			}			
			for(i=0;i<15;i++){
				if(edgebyte == stage4_pos_table[i][0] && cornerbyte == stage4_pos_table[i][1]) return i+50;	//50 signals that move is flipped
			}
		}
	}
	return 0;		//should never get here!
}


unsigned char top_color(void){						//This function fixes the tops of the top layer (make them all the same)
	unsigned char process, i, flipped = 0, move;	//find correct algorithm, then do it.
	process = get_top_color_process();
	if(process == 100) return 1;
	if(process > 49) {						//Algorithm needs to be flipped over FR-LB axis.
		flipped = 1;
		process -= 50;
	}
	for(i=0;i<12;i++){
		move = stage3_move_table[process][i];
		if(move == 20) return 0;
		if(flipped == 1) move = flip_move(move);
		move = translate_front_move(stage3_front, move);
		turn_face(move);
	}
	return 0;
}

void top_sides(void){							//This function fixes the sides of the top layer.
	unsigned char process, i, flipped = 0, move;	//The correct algorithm is found and executed.
	process = get_top_sides_process();
	if(process > 49) {						//Algorithm needs to be flipped over FR-LB axis.
		flipped = 1;
		process -= 50;
	}
	for(i=0;i<14;i++){
		move = stage4_move_table[process][i];
		if(move == 20) break;
		move = translate_front_move(stage4_front, move);
		if(flipped == 1) move = flip_move(move);
		turn_face(move);
	}

	if(edges[0][1] != 1) turn_face((edges[0][1] - 2)*6);
}

#endif