/*
메인코드를 제외한 유저코드 내용입니다
랜덤값을 바꿔 돌려본결과
offset 값이 둘다 짝수일경우 100% (평균 1000개중 0개틀림)
offset 값중 하나가 홀수 일경우 99.5% (평균 1000개중 5개틀림)
offset 값이 둘다 홀수일경우 75%(평균 1000개중 250개틀림)
평균으론 94프로의 정답율을 보입니다.

[풀이]
<encode>
1. 상4줄 / 좌4줄을 1로 채워논다 (decode시 위치 찾기위해)
2. 문자열을 숫자로 바꾼다 단 비트표기시 1이 많으면 유리하므로 A를 0 이아닌 31 부터 시작함. A = 31 / B = 30 / C =29 <총 5비트>
3. 비트당 4*4로 타이트하게 채워넣는다. 4*5 나 5*5는 공간부족으로 못채움

<decode>
1. 이미지에서 위치를 찾는다.
2. offset이 홀수인지 짝수인지 판별한다. (x,y 따로)
3. 문자열을 복원한다.

<짝 짝 일경우>
ㅁㅁ  ㅁㅁ
ㅁㅁ  ㅁㅁ

ㅁㅁ  ㅁㅁ
ㅁㅁ  ㅁㅁ

(각각이 전부 4일경우 1을 하나라도 4가아닐경우 0을 가져온다.)

<한쪽이 홀수 일경우>

<짝 홀>
ㅁ  ㅁㅁ  ㅁ          
ㅁ  ㅁㅁ  ㅁ              
ㅁ  ㅁㅁ  ㅁ           
ㅁ  ㅁㅁ  ㅁ            

<홀 짝>
ㅁㅁ  ㅁㅁ

ㅁㅁ  ㅁㅁ
ㅁㅁ  ㅁㅁ

ㅁㅁ  ㅁㅁ

(짝 홀 기준)
해당칸이 전부 1로 채워져있다면 좌상 좌하 우상 우하는 전부 2이상
상 하는 둘다 4일 경우만 1을 하나라도 조건이 안맞을경우 0을 가져온다.
(홀 짝은 반대로 하면 된다.)

<홀 홀 일경우>

ㅁ  ㅁㅁ  ㅁ

ㅁ  ㅁㅁ  ㅁ
ㅁ  ㅁㅁ  ㅁ

ㅁ  ㅁㅁ  ㅁ

난장판이 되버린다.
이경우 좌상 좌하 우상 우하는 각각 1이상
상하좌우는 각각 2이상
중앙은 4 일경우만 1을 하나라도 아닐경우 0을 가져온다.
이경우 오차율이 가장 크므로 정답율이 낮다.

<정답율을 더올리기 위해선>
인코딩시 주어지는 100 * 100 = 10000칸
이중 식별을 위한 헤더에 필요한 공간이 각각 4줄 = 400 + 400 - 16 = 784칸
쓸수있는 공간 9216칸

4*4 문자 75 = 4 * 4 * 5 * 75 = 6000
5*5 문자 25 = 5 * 5 * 5 * 25 = 3125
로 구성하면 9125칸이며 이렇게 구성할경우 96%~98%의 정답율을 예상할수있다.
*/

void encode(char QRC[100][100], char SRC[100]) {
	// 1을 상과 좌에 4줄씩 채움
	for (register int i = 0; i < 4; i++) {
		for (register int j = 0; j < 100; j++)QRC[i][j] = QRC[j][i] = 1;
	}
	// 비트당 4 * 4 로 채움
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

