﻿###Задължително домашно (септемврийска сесия)

Run-length encoding (RLE) представлява кодиране на стрингове, при което последователности от еднакви символи се заменят с двойка от символа и броя повторения. Например следният стринг:

AAAABBBBCCCA

може да се представи с RLE по следния начин:

 (4,A) (4,B) (3,C) (1,A)

Забележете, че в горното представяне числата са строго по-големи от нула и не може да има две съседни двойки съдържащи един и същ символ. Например това по-долу НЕ Е валидно представяне на горния низ:

(2,A) (2,A) (4,B) (0,B) (0,B) (0,B) (6,C) (-3,C) (1,A) (0,Z)

Да се напише клас RLEString, който представя низове чрез RLE по горе-описания начин. Класът трябва да може да получава C-style символен низ (const char*) и вътрешно да го съхранява като едносвързан списък от двойки от вида (число, символ).

За реализацията на класа НЕ можете да използвате наготово STL, а трябва сами да реализирате представянето на списъка като поредица от двойни кутии.

###За класа е достатъчно да се реализират следните операции:

Голяма четворка;

Конструктор RLEString(char const*);

ostream& operator<<(ostream& os, const RLEString&) – извежда стринга в декомпресиран вид на текстовия изходен поток os;

size_t length() const – връща дължината на декомпресирания низ;

char& operator[](int i) – достъп до i-тия символ на декомпресирания низ;

RLEString operator+(RLEString const & right) const – конкатенира два низа;

void splice(int start, int length) – изтрива част от представения низ; премахват се length на брой елементи, като се започне от елемента на позиция start;

void insert(const RLEString& rles, int pos) – вмъква един RLE низ на позиция pos в друг RLE низ;

###Примери:

Ако е даден низът AAABBCBBC, той ще бъде представен като (3,A) (2,B) (1,C) (2,B) (1,C).

splice(2,5) за този низ ще даде резултат (2,A) (1,B) (1,C), защото ако от AAABBCBBC премахнем пет елемента, започвайки от индекс 2, се получава низът AABC.

Нека сега имаме друг низ AB, представен като (1,A) (1,B). Ако с insert добавим този низ към AABCC на позиция 2, ще се получи низът AAABBCC, който трябва да се представи като (3,A) (2,B) (2,C).