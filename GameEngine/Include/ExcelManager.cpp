#include "ExcelManager.h"

#include <sstream>

DEFINITION_SINGLE(CExcelManager);





struct Monster
{
	string mName;
	int iHP = 0;
	int iMP = 0;
	int iAttack = 0;
	int iDeffend = 0;
	float fMoveSpeed = 0;
};


CExcelManager::CExcelManager()
{
}


CExcelManager::~CExcelManager()
{
}

bool CExcelManager::CreateBook()
{
	Book* book = xlCreateBook();

	return true;
}

bool CExcelManager::LoadMonster(const TCHAR* filename)
{
	Book* book = xlCreateBook();



	if (book->load(L"HK.xls"))
	{
		Sheet* sheet = book->getSheet(0);

		if (nullptr != sheet)
		{
			for (int row = 0; row < sheet->lastRow(); ++row)
			{
				CellType cellType = sheet->cellType(row, 1);
				
				switch (cellType)
				{
				case CELLTYPE_EMPTY: 
					break;
				case CELLTYPE_NUMBER:
				{
					int index = row % 7;
					switch (index)
					{
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					default:
						BOOM;
						break;

					}
					double d = sheet->readNum(row, 1);
					break;
				}
				case CELLTYPE_STRING:
				{
					const wchar_t* s = sheet->readStr(row, 1);
					break;
				}
				case CELLTYPE_BOOLEAN:
				{
					bool b = sheet->readBool(row, 1);
					break;
				}
				case CELLTYPE_BLANK: 
					break;
				case CELLTYPE_ERROR: 
					BOOM
					break;
				}
				
			}
		}		
	}
	else
	{
		BOOM
	}

	book->release();

	return true;
}

void CExcelManager::Test()
{
	LoadMonster(TEXT("../../Client2D/Include/HollowKnight.xls"));
}

int CExcelManager::ReadingTest()
{
	Book* book = xlCreateBook();

	int logoId = book->addPicture(L"logo.png");

	// fonts

	Font* textFont = book->addFont();
	textFont->setSize(8);
	textFont->setName(L"Century Gothic");

	Font* titleFont = book->addFont(textFont);
	titleFont->setSize(38);
	titleFont->setColor(COLOR_GRAY25);

	Font* font12 = book->addFont(textFont);
	font12->setSize(12);

	Font* font10 = book->addFont(textFont);
	font10->setSize(10);

	// formats

	Format* textFormat = book->addFormat();
	textFormat->setFont(textFont);
	textFormat->setAlignH(ALIGNH_LEFT);

	Format* titleFormat = book->addFormat();
	titleFormat->setFont(titleFont);
	titleFormat->setAlignH(ALIGNH_RIGHT);

	Format* companyFormat = book->addFormat();
	companyFormat->setFont(font12);

	Format* dateFormat = book->addFormat(textFormat);
	dateFormat->setNumFormat(book->addCustomNumFormat(L"[$-409]mmmm\\ d\\,\\ yyyy;@"));

	Format* phoneFormat = book->addFormat(textFormat);
	phoneFormat->setNumFormat(
		book->addCustomNumFormat(L"[<=9999999]###\\-####;\\(###\\)\\ ###\\-####")
	);

	Format* borderFormat = book->addFormat(textFormat);
	borderFormat->setBorder();
	borderFormat->setBorderColor(COLOR_GRAY25);
	borderFormat->setAlignV(ALIGNV_CENTER);

	Format* percentFormat = book->addFormat(borderFormat);
	percentFormat->setNumFormat(book->addCustomNumFormat(L"#%_)"));
	percentFormat->setAlignH(ALIGNH_RIGHT);

	Format* textRightFormat = book->addFormat(textFormat);
	textRightFormat->setAlignH(ALIGNH_RIGHT);
	textRightFormat->setAlignV(ALIGNV_CENTER);

	Format* thankFormat = book->addFormat();
	thankFormat->setFont(font10);
	thankFormat->setAlignH(ALIGNH_CENTER);

	Format* dollarFormat = book->addFormat(borderFormat);
	dollarFormat->setNumFormat(
		book->addCustomNumFormat(L"_($* # ##0.00_);_($* (# ##0.00);_($* -??_);_(@_)")
	);

	// actions

	Sheet* sheet = book->addSheet(L"Sales Receipt");

	sheet->setDisplayGridlines(false);

	sheet->setCol(1, 1, 36);
	sheet->setCol(0, 0, 10);
	sheet->setCol(2, 4, 11);

	sheet->setRow(2, 47.25);
	sheet->writeStr(2, 1, L"Sales Receipt", titleFormat);
	sheet->setMerge(2, 2, 1, 4);
	sheet->setPicture(2, 1, logoId);

	sheet->writeStr(4, 0, L"Apricot Ltd.", companyFormat);
	sheet->writeStr(4, 3, L"Date:", textFormat);
	sheet->writeFormula(4, 4, L"TODAY()", dateFormat);

	sheet->writeStr(5, 3, L"Receipt #:", textFormat);
	sheet->writeNum(5, 4, 652, textFormat);

	sheet->writeStr(8, 0, L"Sold to:", textFormat);
	sheet->writeStr(8, 1, L"John Smith", textFormat);
	sheet->writeStr(9, 1, L"Pineapple Ltd.", textFormat);
	sheet->writeStr(10, 1, L"123 Dreamland Street", textFormat);
	sheet->writeStr(11, 1, L"Moema, 52674", textFormat);
	sheet->writeNum(12, 1, 2659872055, phoneFormat);

	sheet->writeStr(14, 0, L"Item #", textFormat);
	sheet->writeStr(14, 1, L"Description", textFormat);
	sheet->writeStr(14, 2, L"Qty", textFormat);
	sheet->writeStr(14, 3, L"Unit Price", textFormat);
	sheet->writeStr(14, 4, L"Line Total", textFormat);

	for (unsigned short row = 15; row < 38; ++row)
	{
		sheet->setRow(row, 15);
		for (unsigned short col = 0; col < 3; ++col)
		{
			sheet->writeBlank(row, col, borderFormat);
		}
		sheet->writeBlank(row, 3, dollarFormat);

		std::wstringstream stream;
		stream << "IF(C" << row + 1 << ">0;ABS(C" << row + 1 << "*D" << row + 1 << ");\"\")";
		sheet->writeFormula(row, 4, stream.str().c_str(), dollarFormat);
	}

	sheet->writeStr(38, 3, L"Subtotal ", textRightFormat);
	sheet->writeStr(39, 3, L"Sales Tax ", textRightFormat);
	sheet->writeStr(40, 3, L"Total ", textRightFormat);
	sheet->writeFormula(38, 4, L"SUM(E16:E38)", dollarFormat);
	sheet->writeNum(39, 4, 0.2, percentFormat);
	sheet->writeFormula(40, 4, L"E39+E39*E40", dollarFormat);
	sheet->setRow(38, 15);
	sheet->setRow(39, 15);
	sheet->setRow(40, 15);

	sheet->writeStr(42, 0, L"Thank you for your business!", thankFormat);
	sheet->setMerge(42, 42, 0, 4);

	// items

	sheet->writeNum(15, 0, 45, borderFormat);
	sheet->writeStr(15, 1, L"Grapes", borderFormat);
	sheet->writeNum(15, 2, 250, borderFormat);
	sheet->writeNum(15, 3, 4.5, dollarFormat);

	sheet->writeNum(16, 0, 12, borderFormat);
	sheet->writeStr(16, 1, L"Bananas", borderFormat);
	sheet->writeNum(16, 2, 480, borderFormat);
	sheet->writeNum(16, 3, 1.4, dollarFormat);

	sheet->writeNum(17, 0, 19, borderFormat);
	sheet->writeStr(17, 1, L"Apples", borderFormat);
	sheet->writeNum(17, 2, 180, borderFormat);
	sheet->writeNum(17, 3, 2.8, dollarFormat);

	book->save(L"receipt.xls");
	book->release();

	return 0;
}
