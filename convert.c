#include <stdio.h>
#include <stdlib.h>

unsigned char realmap(unsigned int value) {
	switch(value) {
		case 0x20ac: return 0x80;
		case 0x201a: return 0x82;
		case 0x0192: return 0x83;
		case 0x201e: return 0x84; 
		case 0x2026: return 0x85;
		case 0x2020: return 0x86;
		case 0x2021: return 0x87;
		case 0x02c6: return 0x88;
		case 0x2030: return 0x89; 
		case 0x0160: return 0x8a;
		case 0x2039: return 0x8b;
		case 0x0152: return 0x8c;
		case 0x017d: return 0x8e;
		case 0x2018: return 0x91;
		case 0x2019: return 0x92;
		case 0x201c: return 0x93;
		case 0x201d: return 0x94;
		case 0x2022: return 0x95;
		case 0x2013: return 0x96;
		case 0x2014: return 0x97;
		case 0x02dc: return 0x98;
		case 0x2122: return 0x99;
		case 0x0161: return 0x9a;
		case 0x203a: return 0x9b;
		case 0x0153: return 0x9c;
		case 0x017e: return 0x9e;
		case 0x0178: return 0x9f;
		default: if (value <= 0xFF) return (value & 0xff) ; else exit (99);

	}
	return 0; // should not reach here
}

unsigned char map(unsigned char lo, unsigned char hi) {
	unsigned int value = ((hi & 0x1f) << 6) | (lo & 0x3f);
	//fprintf(stdout, "%0x-%0x\n", value, realmap(value));
	return realmap(value);
}

unsigned char map3(unsigned char lo, unsigned char hi, unsigned char ultrahi) {
	unsigned int value = ((ultrahi & 0x0F) << 12) | ((hi & 0x3f) << 6) | (lo & 0x3f);
	return realmap(value);
}


int main(int argc, char**argv) {
	FILE *source;
	FILE *destination;

	if (argc < 3) {
		fprintf(stderr, "Usage:\n\tconvert <inputfile> <outputfile>\n\n");
		return -1;
	}
	source = fopen(argv[1], "rb");
	destination = fopen(argv[2], "wb");
	unsigned char reg1, reg2, reg3;
	while (!feof(source)) {
		if (fread(&reg1, 1, 1, source)) {
			if (reg1 < 0x80) {
				fwrite(&reg1, 1, 1, destination);
				continue;
			}
			if (reg1 >= 0xC0 && reg1 <= 0xDF) {
				fread(&reg2, 1, 1, source);
				reg1 = map(reg2, reg1);
				fwrite(&reg1, 1, 1, destination);
				continue;
			}
			if (reg1 >= 0xE0 && reg1 <= 0xEF) {
				fread(&reg2, 1, 1, source);
				fread(&reg3, 1, 1, source);
				reg1 = map3(reg3, reg2, reg1);
				fwrite(&reg1, 1, 1, destination);
				continue;
			}
			fwrite(&reg1, 1, 1, destination);
			return -2;
		}
	}
	fclose(source);
	fclose(destination);
	return 0;
}

