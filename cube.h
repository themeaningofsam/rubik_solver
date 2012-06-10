/* Author Sam Muir
3/23/2010 */

#ifndef _CUBE
#define _CUBE		//Defines all functions common to manipulating the cube as a whole.
					//also contains all variables pertaining to cube.

unsigned char edges[12][2];
unsigned char corners[8][3];
unsigned char solution[75];
unsigned char bestsolution[75];
unsigned char bestsolution_length;
unsigned char solution_pos;
unsigned char input[6][3][3];
unsigned char from_sensor[6][3][3] = {
			{				//top
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
			},
			{				//front
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1}
			},
			{				//left
				{2, 2, 2},
				{2, 2, 2},
				{2, 2, 2}
			},
			{				//back
				{3, 3, 3},
				{3, 3, 3},
				{3, 3, 3}
			},
			{				//right
				{4, 4, 4},
				{4, 4, 4},
				{4, 4, 4}
			},
			{				//bottom
				{5, 5, 5},
				{5, 5, 5},
				{5, 5, 5}
			}
	};

void corner_rot(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth, unsigned char flip);
void edge_rot(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth, unsigned char flip);
unsigned char flip_move(unsigned char move);
void read_cube(void);
void set_bottom(unsigned char bottom);
unsigned char translate_front_move(unsigned char front, unsigned char move);
void turn_face(unsigned char move);
void turn_once(unsigned char move);
void write_move(unsigned char move);

void corner_rot(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth, unsigned char flip){
	unsigned char temp[3];				//rotate four corners being moved in this rotation
	unsigned char from0, from1, from2;	//rotate the corners in memory as necessary.
	temp[0] = corners[first][0];
	temp[1] = corners[first][1];
	temp[2] = corners[first][2];
	if(flip == 1){		//flip 0 and 1 corners (l and r rotation)
		from2 = 2;
		from1 = 0;
		from0 = 1;
	} else if(flip == 2){	//flip 0 and 2 corners (f and b rotation)
		from1 = 1;
		from2 = 0;
		from0 = 2;
	} else { //flip 2 and 1 corners (top or bottom rotation)
		from0 = 0;
		from1 = 2;
		from2 = 1;
	}
	corners[first][from0] = corners[fourth][0];
	corners[first][from1] = corners[fourth][1];
	corners[first][from2] = corners[fourth][2];

	corners[fourth][from0] = corners[third][0];
	corners[fourth][from1] = corners[third][1];
	corners[fourth][from2] = corners[third][2];

	corners[third][from0] = corners[second][0];
	corners[third][from1] = corners[second][1];
	corners[third][from2] = corners[second][2];

	corners[second][from0] = temp[0];
	corners[second][from1] = temp[1];
	corners[second][from2] = temp[2];
}

void edge_rot(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth, unsigned char flip){
	unsigned char temp[2];		//rotate the four edges being moved in this rotation
	temp[0] = edges[first][0];	//flip edges if front or back is being rotated (due to reference point).
	temp[1] = edges[first][1];
	edges[first][flip] = edges[fourth][0];
	edges[first][1-flip] = edges[fourth][1];
	edges[fourth][flip] = edges[third][0];
	edges[fourth][1-flip] = edges[third][1];
	edges[third][flip] = edges[second][0];
	edges[third][1-flip] = edges[second][1];
	edges[second][flip] = temp[0];
	edges[second][1-flip] = temp[1];
}

unsigned char flip_move(unsigned char move){		//flips a move accros the diagonal plane connecting the FR edge and the LB edge
	unsigned char order, type;
	order = move / 6;
	type = move % 6;
	if(order == 2) move -= 12;
	if(order == 0) move += 12;
	switch(type){
		case 0: return move;		// u <-> u'
		case 1: return move + 3;	//f <-> r'
		case 2: return move + 1;	//l <-> b'
		case 3: return move - 1;	//b <-> l'
		case 4: return move - 3;	//r <-> f'
		default: return move;		//d <-> d'
	}
}

void read_cube(void){
	unsigned char refs[6];		//cube will be represented by 12 edges * 2 colors each and 8 corners*3colors each
	unsigned char i, j, k;		//ORDER = (up/down face) -> (front/back face) -> (left/right face)
	for(i = 0; i < 6; i++) {	//edges/corners are represented as a 2/3 array of colors in above ORDER.
		for(j=0; j<6; j++) {
			if(input[j][1][1] == i) refs[i] = j;		//find the locations of all the colors on the middle squares.
		}
	}
	for(i = 0; i < 6; i++){
		for(j = 0; j < 3; j++){
			for(k=0; k<3; k++){
				input[i][j][k] = refs[input[i][j][k]];		//represent each cubie face by the side it belongs on
			}
		}
	}	

	
	for(i = 0; i < 3; i+=2){
		edges[i][0] = input[0][2-i][1];		//input to edges from top
		edges[i+1][0] = input[0][1][i];
		edges[i+8][0] = input[5][i][1];		//input to edges from bottom
		edges[i+9][0] = input[5][1][i];
		edges[i*4][1] = input[1][i][1];		//input from front.
		edges[4+((i/2)*3)][0] = input[1][1][i];
		edges[5+(i/2)][0] = input[3][1][i];		//input from back
		edges[2+(i*4)][1] = input[3][2-i][1];
		edges[1+(i*4)][1] = input[2][i][1];			//input from left side
		edges[4+(i/2)][1] = input[2][1][2-i];
		edges[6+(i/2)][1] = input[4][1][2-i];		//input from right side
		edges[3+(4*i)][1] = input[4][i][1];
	}
	for(i=0; i<2; i++){
		corners[i+1][0] = input[0][0][i*2];		//read corners from top
		corners[i*3][0] = input[0][2][i*2];
		corners[i*3][1] = input[1][0][i*2];		//read from front
		corners[4+(i*3)][1] = input[1][2][i*2];
		corners[4+(i*3)][0] = input[5][0][i*2];	//read from bottom
		corners[5+i][0] = input[5][2][i*2];
		corners[i+1][1] = input[3][2][i*2];		//read from back
		corners[5+i][1] = input[3][0][i*2];
		corners[i][2] = input[2][0][2-2*i];			//read from left
		corners[i+4][2] = input[2][2][2-2*i];
		corners[2+i][2] = input[4][0][2-2*i];		//read from right
		corners[6+i][2] = input[4][2][2-2*i];
	}
}

void set_bottom(unsigned char bottom){
	unsigned char mapping[6];
	unsigned char i, j;
	if(bottom != 2 && bottom != 4){
		switch(bottom){
			case 5: 
				mapping[0] = 0;
				mapping[1] = 1;
				mapping[2] = 5;
				mapping[3] = 3;
				break;
			case 1: 
				mapping[0] = 1;
				mapping[1] = 5;
				mapping[2] = 3;
				mapping[3] = 0;
				break;
			case 0:
				mapping[0] = 5;
				mapping[1] = 3;
				mapping[2] = 0;
				mapping[3] = 1;
				break;
			default:
				mapping[0] = 3;
				mapping[1] = 0;
				mapping[2] = 1;
				mapping[3] = 5;
				break;
		}
		for(i = 0; i < 3; i++){
			for(j=0; j<3; j++){
				input[mapping[0]][i][j] = from_sensor[0][i][j];	//move up face somewhere according to map
				input[mapping[1]][i][j] = from_sensor[1][i][j];	// move front face
				input[mapping[2]][i][j] = from_sensor[5][i][j];	//move bottom face
				input[mapping[3]][i][j] = from_sensor[3][i][j];	//move back face.
				switch(bottom){
					case 5:	input[2][i][j] = from_sensor[2][i][j]; //down=down
							input[4][i][j] = from_sensor[4][i][j];   break;			
					case 1:	input[2][i][j] = from_sensor[2][2-j][i]; 			//front = down
							input[4][i][j] = from_sensor[4][j][2-i];	break;
					case 0:	input[2][i][j] = from_sensor[2][2-i][2-j]; 	//up = down
							input[4][i][j] = from_sensor[4][2-i][2-j]; break;
					default:	input[2][i][j] = from_sensor[2][j][2-i]; 	//back=down
								input[4][i][j] = from_sensor[4][2-j][i];
				}
			}
		}
	}else {
		if(bottom == 2){		//left = down
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					input[0][i][j] = from_sensor[4][j][2-i];
					input[1][i][j] = from_sensor[1][j][2-i];
					input[5][i][j] = from_sensor[2][j][2-i];
					input[3][i][j] = from_sensor[3][2-j][i];
					input[2][i][j] = from_sensor[0][j][2-i];
					input[4][i][j] = from_sensor[5][j][2-i];
				}
			}
		} else {			//right = down
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					input[0][i][j] = from_sensor[2][2-j][i];
					input[1][i][j] = from_sensor[1][2-j][i];
					input[5][i][j] = from_sensor[4][2-j][i];
					input[3][i][j] = from_sensor[3][j][2-i];
					input[2][i][j] = from_sensor[5][2-j][i];
					input[4][i][j] = from_sensor[0][2-j][i];
				}
			}
		}
	}
}

unsigned char translate_front_move(unsigned char front, unsigned char move){		//front must be [1-4], returns same move with actual front as new front.
	unsigned char type = move % 6, order = move / 6;						//this function assumes bottom remains 5.
	switch(type){															
		case 0: return move;
		case 5: return move;
		default:
			type = type + front - 1;
			if(type > 4) type -= 4;
			return ((order * 6) + type);
	}
}

void turn_face(unsigned char move){ //move: (0=U 1=f 2=l 3=b 4=r 5=d) + 6*(number of rotations-1).
	unsigned char times;
	write_move(move);
	times = move / 6;
	for(times++; times>0; times--) turn_once(move % 6);
}

void turn_once(unsigned char move){  //Rotate the given face once clockwise. Move edges and corners.
	switch(move){
		case(0):			//u
			edge_rot(0,1,2,3,0);
			corner_rot(0,1,2,3,0);
			break;
		case(1):			//f
			edge_rot(0,7,8,4,1);
			corner_rot(0,3,7,4,2);
			break;
		case(2):			//l
			edge_rot(1,4,9,5,0);
			corner_rot(0,4,5,1,1);
			break;
		case(3):			//b
			edge_rot(2,5,10,6,1);
			corner_rot(1,5,6,2,2);
			break;
		case(4):			//r
			edge_rot(3,6,11,7,0);
			corner_rot(3,2,6,7,1);
			break;
		default:			//b
			edge_rot(8,11,10,9,0);
			corner_rot(4,7,6,5,0);
	}
}

void write_move(unsigned char move){
	solution[solution_pos] = move;	//add to solution array
	solution_pos++;					//increment number of moves in array
}

#endif