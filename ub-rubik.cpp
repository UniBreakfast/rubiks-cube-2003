	//////////////////// UB-Rubik v0.01 ////////////////////
	//  (Rubik's Cube proudly presented by UnBreakfast :) //
	//													  //
	// Программа покажет, как складывать Кубик Рубика,	  //
	// и позволит пользователю делать это самостоятельно. //
	////////////////////////////////////////////////////////

#include < iostream.h >
#include < conio.h    >
#include < windows.h  >
#include < string.h   >
#include < stdlib.h   >
#include < stdio.h    >
#include < time.h     >

	// (прототип) Сравнит команду со строкой
bool Compare (char[]);

	// (прототип) Установит позицию курсора
void Cursor (int, int);

	// (прототип) Подберет идеальный цвет :)
void Color (short);

	// (прототип) Напишет особый текст в особом месте особым цветом :)
void Say (int, int, short, char[]);

	// (прототип) Внесет изменения в текущее состояние кубика :)
void Turn ();

	// (прототип) Покажет текущее состояние кубика
void Show ();

	// Создаст переменные управления, количества строк,
	// точки зрения, команды, клеток кубика, их копий для отката,
	// случайных бросков для перемешивания, времени
	// и временную переменную на всякий пожарный :)
HANDLE Main = GetStdHandle (STD_OUTPUT_HANDLE);
bool Extended, UnderView;
char Command[200];
short C[6][9]={{240,240,240,240,240,240,240,240,240},
					{144,144,144,144,144,144,144,144,144},
					{ 64, 64, 64, 64, 64, 64, 64, 64, 64},
					{160,160,160,160,160,160,160,160,160},
					{192,192,192,192,192,192,192,192,192},
					{224,224,224,224,224,224,224,224,224}};
int Point[6][9], Backup[10][6][9];
short Roll=0;
long Time=time(0);
int Temp=0;

			////////////////////////////////////////
			// Приступит к исполнению, надеюсь :) //
			////////////////////////////////////////

void main ()
	{
		// Подготовит переменные для откатов
	for (int b=0; b<=9; b++)
		for (int s=0; s<=5; s++)
			for (int i=0; i<=8; i++)
				Backup[b][s][i] = C[s][i];
	for (int s=0; s<=5; s++)
		for (int i=0; i<=8; i++) Point[s][i] = C[s][i];

		// Поприветствует вступлением а также
		// спросит высоту экрана текстового режима и
		// выберет соответствующий режим отображения
	for (Temp=0; Temp<50; Temp++) Say(0, Temp,14, "\t\t\t\t\t\t\t\t\t\t");
	for (Temp=0; Temp<49; Temp++) Say(0, Temp,224,"\t\t\t\t\t\t\t");
	for (Temp=0; Temp<25; Temp++) Say(56,Temp,14, "\t\t\t");	
	for (Temp=0; Temp<19; Temp++) Say(0, Temp,14, "\t\t\t\t\t\t\t");
	for (Temp=0; Temp<4;  Temp++) Say(61,Temp,224,"\t\t\t");
	for (Temp=4; Temp<19; Temp++) Say(56,Temp,224,"     ");
	Say(54,6, 14, "Un     fast");
	Say(56,6, 224,"Break");
	Say(61,8, 14, "proudly");
	Say(61,9, 14, "presented");
	Say(54,12,14, "UB");
	Say(56,12,224,"Rubik");
	Say(61,14,14, "aka");
	Say(61,15,14, "Rubik's");
	Say(61,16,14, "Cube");
	Say(56,20,14, "How many rows on screen");
	Say(56,21,14, "now set, 25 or 50?");
	Cursor(61,23);
	do
		{
		scanf("%s",Command);
		Say(61,23,14,"\t\t\t");
		strupr(Command);
		if (Compare("QUIT")) break;
		if (Compare("25"  )) break;
		if (Compare("50"  ))
			{
			Extended = 1;
			break;
			}
		system("cls");
		Say(56,20,14,"Sorry, only 25 or 50   ");
		Say(56,21,14,"rows. Try again:  ");
		Cursor(61,23);
		}
	while (!(Compare("25") || Compare("50") || Compare("QUIT")));
	system("cls");

		// Покажет текущее положение кубика и правила
	while (!Compare("QUIT"))
		{
		Color(14);
		system("cls");
		Show();
		if (!Extended)
			if (!UnderView)
				{
				Say(43, 7,14,"1");
				Say(43,11,14,"2");
				Say(43,15,14,"3");
				Say(39,18,14,"4");
				Say(32,19,14,"5");
				Say(25,20,14,"6");
				Say( 3,18,14,"9");
				Say(10,19,14,"8");
				Say(17,20,14,"7");
				}
			else
				{
				Say(43, 6,14,"1");
				Say(43,10,14,"2");
				Say(43,14,14,"3");
				Say(39, 3,14,"4");
				Say(32, 2,14,"5");
				Say(25, 1,14,"6");
				Say( 3, 3,14,"9");
				Say(10, 2,14,"8");
				Say(17, 1,14,"7");
				}
		else
			if (!UnderView)
				{
				Say(43,14,14,"1");
				Say(43,21,14,"2");
				Say(43,28,14,"3");
				Say(40,32,14,"4");
				Say(33,35,14,"5");
				Say(26,38,14,"6");
				Say( 2,32,14,"9");
				Say( 9,35,14,"8");
				Say(16,38,14,"7");
				}
			else
				{
				Say(43,11,14,"1");
				Say(43,18,14,"2");
				Say(43,25,14,"3");
				Say(40, 7,14,"4");
				Say(33, 4,14,"5");
				Say(26, 1,14,"6");
				Say( 2, 7,14,"9");
				Say( 9, 4,14,"8");
				Say(16, 1,14,"7");
				}
		Say(46, 5,15,"RND or RAND");
		Say(50, 5,14,"or");
		Say(58, 5,14,"will make 33 random");
		Say(58, 6,14,"turns");
		Say(47, 7,15,"1L, 1R, 2L, 2R, 3L or 3R");
		for (int p=49; p<=61; p+=4) Say(p, 7,14,",");
		Say(66, 7,14,"or");
		Say(72, 7,14,"will");
		Say(46, 8,14,"turn left or right 1st, 2nd or");
		Say(57, 9,14,"3rd row");
		Say(46,10,15,"4U, 4D, 5U, 5D, 6U, 6D, 7U, 7D,");
		for (p=48; p<=76; p+=4) Say(p, 10,14,",");
		Say(47,11,15,"8U, 8D, 9U or 9D");
		for (p=49; p<=53; p+=4) Say(p, 11,14,",");
		Say(58,11,14,"or");
		Say(64,11,14,"will turn up");
		Say(46,12,14,"or down 4th, 5th, 6th, 7th, 8th");
		Say(54,13,14,"or 9th column");
		Say(48,14,15,"L, R, U or D");
		for (p=49; p<=52; p+=3) Say(p, 14,14,",");
		Say(56,14,14,"or");
		Say(61,14,14,"will turn cube");
		Say(50,15,14,"left, right, up or down");
		Say(47,16,15,"T");
		Say(49,16,14,"will turn cube upside-down");
		Say(46,17,15,"SAVE and LOAD");
		Say(51,17,14,"and");
		Say(60,17,14,"will remember or");
		Say(52,18,14,"set cube position");
		Say(48,19,15,"UNDO");
		Say(53,19,14,"will cancel last turn");
		Say(51,20,15,"QUIT");
		Say(56,20,14,"will offend me");

			// Предложит ввести команду и может быть даже выполнит ее :)
		if (!Extended) Cursor(46,22);
		else Cursor(46,39);
		scanf("%s",Command);
		Say(61,23,14,"\t\t\t");
		strupr(Command);
		if ( 
			Compare("1L") || Compare("1R") ||
			Compare("2L") || Compare("2R") ||
			Compare("3L") || Compare("3R") ||
			Compare("4U") || Compare("4D") ||
			Compare("5U") || Compare("5D") ||
			Compare("6U") || Compare("6D") ||
			Compare("7U") || Compare("7D") ||
			Compare("8U") || Compare("8D") ||
			Compare("9U") || Compare("9D")
			)
			{
			for (int s=0; s<=5; s++)
				for (int i=0; i<=8; i++)
					{
					for (int b=9; b>0; b--)
						Backup[b][s][i] = Backup[b-1][s][i];
					Backup[0][s][i] = C[s][i];
					}
			Time = time(0);
			while (time(0) < (Time + 1));
			Turn ();
			}
			else 
				if (
					Compare("U" ) || Compare("D" ) ||
					Compare("L" ) || Compare("R" ) ||
					Compare("T" )
					) Turn ();

			// Отменит последнее действие
		if (Compare("UNDO"))
			for (int s=0; s<=5; s++)
				for (int i=0; i<=8; i++)
					{
					C[s][i] = Backup[0][s][i];
					for (int b=0; b<9; b++)
						Backup[b][s][i] = Backup[b+1][s][i];
					}

			// Запомнит точку возврата или вернется к ней
		if (Compare("SAVE"))
			for (int s=0; s<=5; s++)
				for (int i=0; i<=8; i++)
					Point[s][i] = C[s][i];
		else
			if (Compare("LOAD"))
				for (int s=0; s<=5; s++)
					for (int i=0; i<=8; i++)
						C[s][i] = Point[s][i];
					
			// Скрутит кубику шею случайным образом :)
		if (Compare("RAND"))    // ... на глазах у изумленного пользователя :)
			{
			srand(time(0));
			for (int roll=0; roll<33; roll++)
				{
				Roll=(rand()%6+1);
				Time = time(0);
				while (time(0) < (Time + 1));
				Turn();
				Show();
				}
			Roll=0;
			}
		if (Compare("RND"))    // ... незаметно для глаз простых смертных :)
			{
			srand(time(0));
			for (int roll=0; roll<33; roll++)
				{
				Roll=(rand()%6+1);
				Turn();
				}
			Roll=0;
			}

		if (Compare("QUIT"))
			{
			if (!Extended) Cursor(46,21);
			else Cursor(46,38);
			Color(12);
			printf("Are you kidding? (Y/N)  ");
			Temp = getche();
			if (!(Temp == 78 || Temp == 110)) strcpy(Command,"\0");
			}
		}

		// Очистит экран перед выходом
	Color(14); system("cls"); Cursor(0,0);
	}
			/////////////////////////////////
			// Прекратит активные действия //
			/////////////////////////////////
    // (функция) Сравнит команду со строкой
bool Compare (char String[])
	{
	for (unsigned int i = 0; i < strlen(String)+1; i++)
		if (Command[i] != String[i]) return 0;	
	return 1;
	}

	// (функция) Установит позицию курсора
void Cursor (int x, int y)
	{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition (Main, Pos);
	}

	// (функция) Подберет идеальный цвет
void Color (short ColorNumber)
	{
	SetConsoleTextAttribute (Main, ColorNumber);
	}

	// (функция) Напишет особый текст в особом месте особым цветом
void Say (int x, int y, short ColorNumber, char Text[])
	{
	Cursor(x,y);
	Color(ColorNumber);
	printf(Text);
	}

	// (функция) Внесет изменения в текущее состояние кубика :)
void Turn ()
{
		// Заглянет снизу 
	if (Compare ("U")) UnderView=1;

		// Посмотрит сверху
	if (Compare ("D")) UnderView=0;
	
		// Перевернет вверх дном, сохранив точку зрения
	if (Compare ("T"))
		{
		if (UnderView) UnderView = 0;
		else UnderView = 1;
		for (int s=1; s<=3; s+=2)
			for (int i=0; i<=8; i++)
				{
				Temp = C[s][i]; C[s][i] = C[s+1][8-i];
				C[s+1][8-i] = Temp;
				}
		for (int i=0; i<=8; i++)
			{
			Temp = C[0][i]; C[0][i] = C[5][8-i];
			C[5][8-i] = Temp;
			}
		}

		// Повернет верхнюю плоскость вправо
	if (Compare ("1R") || Roll==1)
		{
		for (int i=0; i<=2; i++)
			{
			Temp = C[1][i];
			for (int t=1; t<4; t++) C[t][i] = C[t+1][i];
			C[4][i] = Temp;
			}
		Temp = C[0][0];
		C[0][0] = C[0][2]; C[0][2] = C[0][8]; C[0][8] = C[0][6];
		C[0][6] = Temp;
		Temp = C[0][1];
		C[0][1] = C[0][5]; C[0][5] = C[0][7]; C[0][7] = C[0][3];
		C[0][3] = Temp;
		}

		// Повернет среднюю горизонталь вправо
	if (Compare ("2R") || Roll==2)
	for (int i=3; i<=5; i++)
		{
		Temp = C[1][i];
		for (int t=1; t<4; t++) C[t][i] = C[t+1][i];
		C[4][i] = Temp;
		}

		// Повернет нижнюю плоскость вправо
	if (Compare ("3R") || Roll==3)
		{
		for (int i=6; i<=8; i++)
			{
			Temp = C[1][i];
			for (int t=1; t<4; t++) C[t][i] = C[t+1][i];
			C[4][i] = Temp;
			}
		Temp = C[5][0];
		C[5][0] = C[5][6]; C[5][6] = C[5][8]; C[5][8] = C[5][2];
		C[5][2] = Temp;
		Temp = C[5][1];
		C[5][1] = C[5][3]; C[5][3] = C[5][7]; C[5][7] = C[5][5];
		C[5][5] = Temp;
		}

		// Повернет на левой стороне левую вертикаль вверх
	if (Compare ("9U") || Roll==4)
		{
		Temp = C[0][0];
		C[0][0] = C[2][6]; C[2][6] = C[5][6]; C[5][6] = C[4][2];
		C[4][2] = Temp;
		Temp = C[0][1];
		C[0][1] = C[2][3]; C[2][3] = C[5][3]; C[5][3] = C[4][5];
		C[4][5] = Temp;
		Temp = C[0][2];
		C[0][2] = C[2][0]; C[2][0] = C[5][0]; C[5][0] = C[4][8];
		C[4][8] = Temp;
		Temp = C[3][0];
		C[3][0] = C[3][2]; C[3][2] = C[3][8]; C[3][8] = C[3][6];
		C[3][6] = Temp;
		Temp = C[3][1];
		C[3][1] = C[3][5]; C[3][5] = C[3][7]; C[3][7] = C[3][3];
		C[3][3] = Temp;
		}

		// Повернет на левой стороне среднюю вертикаль вверх
	if (Compare ("8U") || Roll==5)
		{
		Temp = C[0][3];
		C[0][3] = C[2][7]; C[2][7] = C[5][7]; C[5][7] = C[4][1];
		C[4][1] = Temp;
		Temp = C[0][4];
		C[0][4] = C[2][4]; C[2][4] = C[5][4]; C[5][4] = C[4][4];
		C[4][4] = Temp;
		Temp = C[0][5];
		C[0][5] = C[2][1]; C[2][1] = C[5][1]; C[5][1] = C[4][7];
		C[4][7] = Temp;
		}

		// Повернет на левой стороне правую вертикаль вверх
	if (Compare ("7U") || Roll==6)
		{
		Temp = C[0][6];
		C[0][6] = C[2][8]; C[2][8] = C[5][8]; C[5][8] = C[4][0];
		C[4][0] = Temp;
		Temp = C[0][7];
		C[0][7] = C[2][5]; C[2][5] = C[5][5]; C[5][5] = C[4][3];
		C[4][3] = Temp;
		Temp = C[0][8];
		C[0][8] = C[2][2]; C[2][2] = C[5][2]; C[5][2] = C[4][6];
		C[4][6] = Temp;
		Temp = C[1][0];
		C[1][0] = C[1][6]; C[1][6] = C[1][8]; C[1][8] = C[1][2];
		C[1][2] = Temp;
		Temp = C[1][1];
		C[1][1] = C[1][3]; C[1][3] = C[1][7]; C[1][7] = C[1][5];
		C[1][5] = Temp;
	}

		// Повернет верхнюю плоскость влево
	if (Compare ("1L"))
		{
		strcpy(Command,"1R");
		Turn(); Turn(); Turn();
		}

		// Повернет среднюю горизонталь влево
	if (Compare ("2L"))
		{
		strcpy(Command,"2R");
		Turn(); Turn(); Turn();
		}

		// Повернет нижнюю плоскость влево
	if (Compare ("3L"))
		{
		strcpy(Command,"3R");
		Turn(); Turn(); Turn();
		}

		// Повернет кубик вправо
	if (Compare ("R"))
		{
		strcpy(Command,"1R"); Turn();
		strcpy(Command,"2R"); Turn();
		strcpy(Command,"3R"); Turn();
		}

		// Повернет кубик влево
	if (Compare ("L"))
		{
		strcpy(Command,"R"); Turn();
		strcpy(Command,"R"); Turn();
		strcpy(Command,"R"); Turn();
		}

		// Повернет на левой стороне левую вертикаль вниз
	if (Compare ("9D"))
		{
		strcpy(Command,"R");  Turn();
		strcpy(Command,"R");  Turn();
		strcpy(Command,"7U"); Turn();
		strcpy(Command,"R");  Turn();
		strcpy(Command,"R");  Turn();
		}

		// Повернет на левой стороне среднюю вертикаль вниз
	if (Compare ("8D"))
		{
		strcpy(Command,"R");  Turn();
		strcpy(Command,"R");  Turn();
		strcpy(Command,"8U"); Turn();
		strcpy(Command,"R");  Turn();
		strcpy(Command,"R");  Turn();
		}

		// Повернет на левой стороне правую вертикаль вниз
	if (Compare ("7D"))
		{
		strcpy(Command,"R");  Turn();
		strcpy(Command,"R");  Turn();
		strcpy(Command,"9U"); Turn();
		strcpy(Command,"R");  Turn();
		strcpy(Command,"R");  Turn();
		}

		// Повернет на правой стороне левую вертикаль вверх
	if (Compare ("6U"))
		{
		strcpy(Command,"T");  Turn();
		strcpy(Command,"7D"); Turn();
		strcpy(Command,"T");  Turn();
		}

		// Повернет на правой стороне среднюю вертикаль вверх
	if (Compare ("5U"))
		{
		strcpy(Command,"T");  Turn();
		strcpy(Command,"8D"); Turn();
		strcpy(Command,"T");  Turn();
		}

		// Повернет на правой стороне правую вертикаль вверх
	if (Compare ("4U"))
		{
		strcpy(Command,"T");  Turn();
		strcpy(Command,"9D"); Turn();
		strcpy(Command,"T");  Turn();
		}

		// Повернет на правой стороне левую вертикаль вниз
	if (Compare ("6D"))
		{
		strcpy(Command,"T");  Turn();
		strcpy(Command,"7U"); Turn();
		strcpy(Command,"T");  Turn();
		}

		// Повернет на правой стороне среднюю вертикаль вниз
	if (Compare ("5D"))
		{
		strcpy(Command,"T");  Turn();
		strcpy(Command,"8U"); Turn();
		strcpy(Command,"T");  Turn();
		}

		// Повернет на правой стороне правую вертикаль вниз
	if (Compare ("4D"))
		{
		strcpy(Command,"T");  Turn();
		strcpy(Command,"9U"); Turn();
		strcpy(Command,"T");  Turn();
		}
}

	// (функция) Покажет текущее состояние кубика под данным углом зрения
void Show ()
	{
	short ColPos, RowPos;
		// Покажет кубик для режима 25-и строк ...
	if (!Extended) 

			// ... сверху
		if (!UnderView) 
			{
			RowPos=2; ColPos=4;
			for (int i=0; i<=8; i++)
				{
				Color(C[0][i]);
				if (i%2==0)
					{
					Cursor(RowPos+4, ColPos); printf("ЯЯЯ");
					Cursor(RowPos, ColPos+1); printf("ЯЯ       ЯЯ");
					Cursor(RowPos+2, ColPos+2); printf("ЬЬ   ЬЬ");
					ColPos--;
					}
				else
					{
					Cursor(RowPos+2, ColPos); printf("ЯЯ   ЯЯ");
					Cursor(RowPos, ColPos+1); printf("ЬЬ       ЬЬ");
					Cursor(RowPos+4, ColPos+2); printf("ЬЬЬ");
					ColPos-=2;
					}
				RowPos+=7;
				if (i==2 || i==5) { ColPos+=6; RowPos-=14; }
				}
			RowPos=22; ColPos=9;
			for (i=0; i<=8; i++)
				{
				Color(C[1][i]);
				if (i%2==0)
					{
					Cursor(RowPos+4, ColPos); printf("ЯЯ");
					Cursor(RowPos, ColPos+1); printf("ЯЯ    ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos, ColPos+3); printf("    ЬЬ");
					Cursor(RowPos, ColPos+4); printf("ЬЬ");
					ColPos--;
					}
				else
					{
					Cursor(RowPos+2, ColPos); printf("ЯЯ  ");
					Cursor(RowPos, ColPos+1); printf("      ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos, ColPos+3); printf("  ЬЬ");
					ColPos-=2;
					}
				RowPos+=7;
				if (i==2 || i==5) { ColPos+=8; RowPos-=21; }
				}
			RowPos=1; ColPos=6;
			for (i=0; i<=8; i++)
				{
				Color(C[2][i]);
				if (i%2==0)
					{
					Cursor(RowPos, ColPos); printf("ЯЯ");
					Cursor(RowPos, ColPos+1); printf("    ЯЯ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos, ColPos+3); printf("ЬЬ    ");
					Cursor(RowPos+4, ColPos+4); printf("ЬЬ");
					ColPos+=2;
					}
				else
					{
					Cursor(RowPos, ColPos); printf("  ЯЯ");
					Cursor(RowPos, ColPos+1); printf("      ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos+2, ColPos+3); printf("ЬЬ  ");
					ColPos++;
					}
				RowPos+=7;
				if (i==2 || i==5) { ColPos--; RowPos-=21; }
				}
			}

			// ... снизу
		else 
			{
			RowPos=1; ColPos=4;
			for (int i=0; i<=8; i++)
				{
				Color(C[2][i]);
				if (i%2==0)
					{
					Cursor(RowPos+4, ColPos); printf("ЯЯ");
					Cursor(RowPos, ColPos+1); printf("ЯЯ    ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos, ColPos+3); printf("    ЬЬ");
					Cursor(RowPos, ColPos+4); printf("ЬЬ");
					ColPos--;
					}
				else
					{
					Cursor(RowPos+2, ColPos); printf("ЯЯ  ");
					Cursor(RowPos, ColPos+1); printf("      ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos, ColPos+3); printf("  ЬЬ");
					ColPos-=2;
					}
				RowPos+=7;
				if (i==2 || i==5) { ColPos+=8; RowPos-=21; }
				}
			RowPos=22; ColPos=1;
			for (i=0; i<=8; i++)
				{
				Color(C[1][i]);
				if (i%2==0)
					{
					Cursor(RowPos, ColPos); printf("ЯЯ");    
					Cursor(RowPos, ColPos+1); printf("    ЯЯ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos, ColPos+3); printf("ЬЬ    "); 
					Cursor(RowPos+4, ColPos+4); printf("ЬЬ");     
					ColPos+=2;
					}
				else
					{
					Cursor(RowPos, ColPos); printf("  ЯЯ");
					Cursor(RowPos, ColPos+1); printf("      ");
					Cursor(RowPos, ColPos+2); printf("      ");
					Cursor(RowPos+2, ColPos+3); printf("ЬЬ  ");
					ColPos++;
					}
				RowPos+=7;
				if (i==2 || i==5) { ColPos--; RowPos-=21; }
				}
			RowPos=2; ColPos=15;
			for (i=0; i<=8; i++)
				{
				Color(C[5][i]);
				if (i%2==0)
					{
					Cursor(RowPos+2, ColPos); printf("ЯЯ   ЯЯ");
					Cursor(RowPos, ColPos+1); printf("ЬЬ       ЬЬ");
					Cursor(RowPos+4, ColPos+2); printf("ЬЬЬ");
					ColPos-=2;
					}
				else
					{
					Cursor(RowPos+4, ColPos); printf("ЯЯЯ");
					Cursor(RowPos, ColPos+1); printf("ЯЯ       ЯЯ");
					Cursor(RowPos+2, ColPos+2); printf("ЬЬ   ЬЬ");
					ColPos--;
					}
				RowPos+=7;
				if (i==2 || i==5) { ColPos+=6; RowPos-=14; }
				}
			}

		// Покажет кубик для режима 50-и строк ...	
	else 
			// ... сверху
		if (!UnderView)
			{
			RowPos=2; ColPos=7;
			for (int i=0; i<=8; i++)
				{
				Color(C[0][i]);
				Cursor(RowPos+3, ColPos); printf("Я   Я");
				Cursor(RowPos+1, ColPos+1); printf("Я       Я");
				Cursor(RowPos, ColPos+2); printf("           ");
				Cursor(RowPos+1, ColPos+3); printf("Ь       Ь");
				Cursor(RowPos+3, ColPos+4); printf("Ь   Ь");
				RowPos+=7; ColPos-=3;
				if (i==2 || i==5) { ColPos+=12; RowPos-=14; }
				}
			RowPos=22; ColPos=17;
			for (i=0; i<=8; i++)
				{
				Color(C[1][i]);
				Cursor(RowPos+3, ColPos); printf("Я  ");
				Cursor(RowPos+1, ColPos+1); printf("Я    "); 
				Cursor(RowPos, ColPos+2); printf("      ");
				Cursor(RowPos, ColPos+3); printf("      ");
				Cursor(RowPos, ColPos+4); printf("      ");
				Cursor(RowPos, ColPos+5); printf("      ");
				Cursor(RowPos, ColPos+6); printf("    Ь");
				Cursor(RowPos, ColPos+7); printf("  Ь");
				RowPos+=7; ColPos-=3;
				if (i==2 || i==5) { ColPos+=16; RowPos-=21; }
				}
			RowPos=1; ColPos=11;
			for (i=0; i<=8; i++)
				{
				Color(C[2][i]);
				Cursor(RowPos, ColPos); printf("  Я");
				Cursor(RowPos, ColPos+1); printf("    Я");
				Cursor(RowPos, ColPos+2); printf("      ");
				Cursor(RowPos, ColPos+3); printf("      ");
				Cursor(RowPos, ColPos+4); printf("      ");
				Cursor(RowPos, ColPos+5); printf("      ");
				Cursor(RowPos+1, ColPos+6); printf("Ь    ");
				Cursor(RowPos+3, ColPos+7); printf("Ь  ");
				RowPos+=7; ColPos+=3;
				if (i==2 || i==5) { ColPos-=2; RowPos-=21; }
				}
			}

			// ... снизу.
		else
		{
			RowPos=2; ColPos=28;
			for (int i=0; i<=8; i++)
				{
				Color(C[5][i]);
				Cursor(RowPos+3, ColPos); printf("Я   Я");
				Cursor(RowPos+1, ColPos+1); printf("Я       Я");
				Cursor(RowPos, ColPos+2); printf("           ");
				Cursor(RowPos+1, ColPos+3); printf("Ь       Ь");
				Cursor(RowPos+3, ColPos+4); printf("Ь   Ь");
				RowPos+=7; ColPos-=3;
				if (i==2 || i==5) { ColPos+=12; RowPos-=14; }
				}
			RowPos=22; ColPos=1;
			for (i=0; i<=8; i++)
				{
				Color(C[1][i]);
				Cursor(RowPos, ColPos); printf("  Я");
				Cursor(RowPos, ColPos+1); printf("    Я");
				Cursor(RowPos, ColPos+2); printf("      ");
				Cursor(RowPos, ColPos+3); printf("      ");
				Cursor(RowPos, ColPos+4); printf("      ");
				Cursor(RowPos, ColPos+5); printf("      ");
				Cursor(RowPos+1, ColPos+6); printf("Ь    ");
				Cursor(RowPos+3, ColPos+7); printf("Ь  ");
				RowPos+=7; ColPos+=3;
				if (i==2 || i==5) { ColPos-=2; RowPos-=21; }
				}
			RowPos=1; ColPos=7;
			for (i=0; i<=8; i++)
				{
				Color(C[2][i]);
				Cursor(RowPos+3, ColPos); printf("Я  ");
				Cursor(RowPos+1, ColPos+1); printf("Я    "); 
				Cursor(RowPos, ColPos+2); printf("      ");
				Cursor(RowPos, ColPos+3); printf("      ");
				Cursor(RowPos, ColPos+4); printf("      ");
				Cursor(RowPos, ColPos+5); printf("      ");
				Cursor(RowPos, ColPos+6); printf("    Ь");
				Cursor(RowPos, ColPos+7); printf("  Ь");
				RowPos+=7; ColPos-=3;
				if (i==2 || i==5) { ColPos+=16; RowPos-=21; }
				}
			}
	}

//
// cout << '\n' << "                    BBB                   ";
// cout << '\n' << "                  BBBBBBB                 ";
// cout << '\n' << "                BBBBBBBBBBB               ";
//	cout << '\n' << "             BBB  BBBBBBB  BBB            ";
//	cout << '\n' << "           BBBBBBB  BBB  BBBBBBB          ";
//	cout << '\n' << "         BBBBBBBBBBB   BBBBBBBBBBB        ";
//	cout << '\n' << "      BBB  BBBBBBB  BBB  BBBBBBB  BBB     ";
//	cout << '\n' << "    BBBBBBB  BBB  BBBBBBB  BBB  BBBBBBB   ";
//	cout << '\n' << "  BBBBBBBBBBB   BBBBBBBBBBB   BBBBBBBBBBB ";
//	cout << '\n' << "    BBBBBBB  BBB  BBBBBBB  BBB  BBBBBBB   ";
//	cout << '\n' << " OO   BBB  BBBBBBB  BBB  BBBBBBB  BBB   WW";
//	cout << '\n' << " OOOO    BBBBBBBBBBB   BBBBBBBBBBB    WWWW";
//	cout << '\n' << " OOOOOO    BBBBBBB  BBB  BBBBBBB    WWWWWW";
//	cout << '\n' << " OOOOOO OO   BBB  BBBBBBB  BBB   WW WWWWWW";
//	cout << '\n' << " OOOOOO OOOO    BBBBBBBBBBB    WWWW WWWWWW";
//	cout << '\n' << " OOOOOO OOOOOO    BBBBBBB    WWWWWW WWWWWW";
//	cout << '\n' << "   OOOO OOOOOO OO   BBB   WW WWWWWW WWWW  ";
//	cout << '\n' << " OO  OO OOOOOO OOOO     WWWW WWWWWW WW  WW";
//	cout << '\n' << " OOOO   OOOOOO OOOOOO WWWWWW WWWWWW   WWWW";
//	cout << '\n' << " OOOOOO   OOOO OOOOOO WWWWWW WWWW   WWWWWW";
//	cout << '\n' << " OOOOOO OO  OO OOOOOO WWWWWW WW  WW WWWWWW";
//	cout << '\n' << " OOOOOO OOOO   OOOOOO WWWWWW   WWWW WWWWWW";
//	cout << '\n' << " OOOOOO OOOOOO   OOOO WWWW   WWWWWW WWWWWW";
//	cout << '\n' << "   OOOO OOOOOO OO  OO WW  WW WWWWWW WWWW  ";
//	cout << '\n' << " OO  OO OOOOOO OOOO     WWWW WWWWWW WW  WW";
//	cout << '\n' << " OOOO   OOOOOO OOOOOO WWWWWW WWWWWW   WWWW";
//	cout << '\n' << " OOOOOO   OOOO OOOOOO WWWWWW WWWW   WWWWWW";
//	cout << '\n' << " OOOOOO OO  OO OOOOOO WWWWWW WW  WW WWWWWW";
//	cout << '\n' << " OOOOOO OOOO   OOOOOO WWWWWW   WWWW WWWWWW";
//	cout << '\n' << " OOOOOO OOOOOO   OOOO WWWW   WWWWWW WWWWWW";
//	cout << '\n' << "   OOOO OOOOOO OO  OO WW  WW WWWWWW WWWW  ";
//	cout << '\n' << "     OO OOOOOO OOOO     WWWW WWWWWW WW    ";
//	cout << '\n' << "        OOOOOO OOOOOO WWWWWW WWWWWW       ";
//	cout << '\n' << "          OOOO OOOOOO WWWWWW WWWW         ";
//	cout << '\n' << "            OO OOOOOO WWWWWW WW           ";
//	cout << '\n' << "               OOOOOO WWWWWW              ";
//	cout << '\n' << "                 OOOO WWWW                ";
//	cout << '\n' << "                   OO WW                  ";
//
//Time = time(0);
//while (time(0) < (Time + 1));
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	возврат курсора, параметры функции по умолчанию
//
//
