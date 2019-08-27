
void encode(char QRC[100][100], char SRC[100]) {
	for (register int i = 0; i < 4; i++) {
		for (register int j = 0; j < 100; j++)QRC[i][j] = QRC[j][i] = 1;
	}
	int si = 4, sj = 0;
	for (register int i = 0; i < 100; i++) {
		int pos = 31 - SRC[i] + 'A';
		//over
		for (register int j = 0; j < 5; j++) {
			int bit = (pos & (1 << j)) == 0 ? 0 : 1;
			if (sj + 4 >= 100)si += 4, sj = 0;
			sj += 4;
			for (register int p = 0; p < 4; p++) {
				for (int q = 0; q < 4; q++)QRC[si + p][sj + q] = bit;
			}
		}
	}
}
void decode(char GRY[100][100], char DST[100]) {
	// x상하  y좌우
	int x = 0, y = 0;
	// 0 짝 1 홀
	int chk1 = 0, chk2 = 0;
	// 왼위 지점 찾기
	for (register int i = 0; i <= 50; i++) {
		int cut = 0;
		for (register int j = 0; j <= 50; j++) {
			cut = 1;
			for (register int k = 0; k < 49; k++) {
				if (GRY[i][j + k] != 4 || GRY[i + k][j] != 4)cut = 0;
			}
			if (cut) {
				x = i;
				y = j;
				break;
			}
		}
		if (cut)break;
	}
	// i 축 홀짝 (chk1)
	for (register int i = 0; i < 49; i++) {
		if (GRY[x + 1][y + i] != 4) chk1 = 1;
	}
	// j 축 홀짝 (chk2)
	for (register int i = 0; i < 49; i++) {
		if (GRY[x + i][y + 1] != 4)chk2 = 1;
	}
	// 시작 지점
	int sx = 2, sy = 0;
	// 통합
	for (register int i = 0; i < 100; i++) {
		int sum = 0;
		for (register int j = 0; j < 5; j++) {
			if (sy + 2 >= 50)sx += 2, sy = 0;
			sy += 2;
			// 짝 짝
			if (!chk1 && !chk2
				&& GRY[x + sx][y + sy] + GRY[x + sx][y + sy + 1] + GRY[x + sx + 1][y + sy] + GRY[x + sx + 1][y + sy + 1] == 16) sum += (1 << j);
			// 짝 홀
			if (!chk1 && chk2 && GRY[x + sx][y + sy] == 4 && GRY[x + sx + 1][y + sy] == 4
				&& GRY[x + sx][y + sy - 1] > 1 && GRY[x + sx + 1][y + sy - 1] > 1
				&& GRY[x + sx][y + sy + 1] > 1 && GRY[x + sx + 1][y + sy + 1] > 1)sum += (1 << j);
			// 홀 짝
			if (chk1 && !chk2 && GRY[x + sx][y + sy] == 4 && GRY[x + sx][y + sy + 1] == 4
				&& GRY[x + sx - 1][y + sy] > 1 && GRY[x + sx + 1][y + sy] > 1
				&& GRY[x + sx - 1][y + sy + 1] > 1 && GRY[x + sx + 1][y + sy + 1] > 1)sum += (1 << j);
			// 홀 홀
			if (chk1 && chk2 && GRY[x + sx - 1][y + sy - 1] > 0 && GRY[x + sx + 1][y + sy + 1] > 0
				&& GRY[x + sx - 1][y + sy + 1] > 0 && GRY[x + sx + 1][y + sy - 1] > 0
				&& GRY[x + sx - 1][y + sy] > 1 && GRY[x + sx + 1][y + sy] > 1
				&& GRY[x + sx][y + sy - 1] > 1 && GRY[x + sx][y + sy + 1] > 1 && GRY[x + sx][y + sy] == 4) sum += (1 << j);
		}
		DST[i] = 'A' + 31 - sum;
	}
}

