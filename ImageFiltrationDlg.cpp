
// ImageFiltrationDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ImageFiltration.h"
#include "ImageFiltrationDlg.h"
#include "afxdialogex.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define INPUT_TRANSFORM(x,y) (input_xp*((x)-input_xmin)),(input_yp*((y)-input_ymax)) 


CImageFiltrationDlg::CImageFiltrationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEFILTRATION_DIALOG, pParent)
	, EDIT_FIRST_AMPL(1)
	, EDIT_SECOND_AMPL(1)
	, EDIT_THIRD_AMPL(1)
	, EDIT_FIRST_X_SHIFT()
	, EDIT_SECOND_X_SHIFT()
	, EDIT_THIRD_X_SHIFT()
	, EDIT_FIRST_Y_SHIFT()
	, EDIT_SECOND_Y_SHIFT()
	, EDIT_THIRD_Y_SHIFT()
	, EDIT_FIRST_X_DISP()
	, EDIT_SECOND_X_DISP()
	, EDIT_THIRD_X_DISP()
	, EDIT_FIRST_Y_DISP()
	, EDIT_SECOND_Y_DISP()
	, EDIT_THIRD_Y_DISP()
	, EDIT_IMAGE_HEIGHT(0)
	, EDIT_IMAGE_WIDTH(0)
	, EDIT_KERNEL_SIZE(3)
	, EDIT_FILTRATION_CRITERION(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageFiltrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_FIRST_GAUSS, CHECK_FIRST_GAUSS);
	DDX_Control(pDX, IDC_CHECK_SECOND_GAUSS, CHECK_SECOND_GAUSS);
	DDX_Control(pDX, IDC_CHECK_THIRD_GAUSS, CHECK_THIRD_GAUSS);
	DDX_Text(pDX, IDC_EDIT_FIRST_AMPL, EDIT_FIRST_AMPL);
	DDX_Text(pDX, IDC_EDIT_SECOND_AMPL, EDIT_SECOND_AMPL);
	DDX_Text(pDX, IDC_EDIT_THIRD_AMPL, EDIT_THIRD_AMPL);
	DDX_Text(pDX, IDC_EDIT_FIRST_X_SHIFT, EDIT_FIRST_X_SHIFT);
	DDX_Text(pDX, IDC_EDIT_SECOND_X_SHIFT, EDIT_SECOND_X_SHIFT);
	DDX_Text(pDX, IDC_EDIT_THIRD_X_SHIFT, EDIT_THIRD_X_SHIFT);
	DDX_Text(pDX, IDC_EDIT_FIRST_Y_SHIFT, EDIT_FIRST_Y_SHIFT);
	DDX_Text(pDX, IDC_EDIT_SECOND_Y_SHIFT, EDIT_SECOND_Y_SHIFT);
	DDX_Text(pDX, IDC_EDIT_THIRD_Y_SHIFT, EDIT_THIRD_Y_SHIFT);
	DDX_Text(pDX, IDC_EDIT_FIRST_X_DISP, EDIT_FIRST_X_DISP);
	DDX_Text(pDX, IDC_EDIT_SECOND_X_DISP, EDIT_SECOND_X_DISP);
	DDX_Text(pDX, IDC_EDIT_THIRD_X_DISP, EDIT_THIRD_X_DISP);
	DDX_Text(pDX, IDC_EDIT_FIRST_Y_DISP, EDIT_FIRST_Y_DISP);
	DDX_Text(pDX, IDC_EDIT_SECOND_Y_DISP, EDIT_SECOND_Y_DISP);
	DDX_Text(pDX, IDC_EDIT_THIRD_Y_DISP, EDIT_THIRD_Y_DISP);
	DDX_Control(pDX, IDC_EDIT_IMAGE_PATH, EDIT_IMAGE_PATH);
	DDX_Text(pDX, IDC_EDIT_IMAGE_HEIGHT, EDIT_IMAGE_HEIGHT);
	DDX_Text(pDX, IDC_EDIT_IMAGE_WIDTH, EDIT_IMAGE_WIDTH);
	DDX_Control(pDX, IDC_RADIO_LINEAR_FILTER, RADIO_LINEAR_FILTER);
	DDX_Control(pDX, IDC_RADIO_MEDIAN_FILTER, RADIO_MEDIAN_FILTER);
	DDX_Text(pDX, IDC_EDIT_KERNEL_SIZE, EDIT_KERNEL_SIZE);
	DDX_Text(pDX, IDC_EDIT_CRITERION, EDIT_FILTRATION_CRITERION);
	DDX_Control(pDX, IDC_EDIT_FIRST_AMPL, EDIT_CONTROL_FIRST_AMPL);
	DDX_Control(pDX, IDC_EDIT_SECOND_AMPL, EDIT_CONTROL_SECOND_AMPL);
	DDX_Control(pDX, IDC_EDIT_THIRD_AMPL, EDIT_CONTROL_THIRD_AMPL);
	DDX_Control(pDX, IDC_EDIT_FIRST_X_SHIFT, EDIT_CONTROL_FIRST_X_SHIFT);
	DDX_Control(pDX, IDC_EDIT_SECOND_X_SHIFT, EDIT_CONTROL_SECOND_X_SHIFT);
	DDX_Control(pDX, IDC_EDIT_THIRD_X_SHIFT, EDIT_CONTROL_THIRD_X_SHIFT);
	DDX_Control(pDX, IDC_EDIT_FIRST_Y_SHIFT, EDIT_CONTROL_FIRST_Y_SHIFT);
	DDX_Control(pDX, IDC_EDIT_SECOND_Y_SHIFT, EDIT_CONTROL_SECOND_Y_SHIFT);
	DDX_Control(pDX, IDC_EDIT_THIRD_Y_SHIFT, EDIT_CONTROL_THIRD_Y_SHIFT);
	DDX_Control(pDX, IDC_EDIT_FIRST_X_DISP, EDIT_CONTROL_FIRST_X_DISP);
	DDX_Control(pDX, IDC_EDIT_SECOND_X_DISP, EDIT_CONTROL_SECOND_X_DISP);
	DDX_Control(pDX, IDC_EDIT_THIRD_X_DISP, EDIT_CONTROL_THIRD_X_DISP);
	DDX_Control(pDX, IDC_EDIT_FIRST_Y_DISP, EDIT_CONTROL_FIRST_Y_DISP);
	DDX_Control(pDX, IDC_EDIT_SECOND_Y_DISP, EDIT_CONTROL_SECOND_Y_DISP);
	DDX_Control(pDX, IDC_EDIT_THIRD_Y_DISP, EDIT_CONTROL_THIRD_Y_DISP);
}

BEGIN_MESSAGE_MAP(CImageFiltrationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW_IMAGE, &CImageFiltrationDlg::OnBnClickedButtonDrawImage)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_IMAGE, &CImageFiltrationDlg::OnBnClickedButtonClearImage)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_FILTER, &CImageFiltrationDlg::OnBnClickedButtonDrawFilter)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_FILTER, &CImageFiltrationDlg::OnBnClickedButtonClearFilter)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_VEIL, &CImageFiltrationDlg::OnBnClickedButtonDrawVeil)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_VEIL, &CImageFiltrationDlg::OnBnClickedButtonClearVeil)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_CORRUPT, &CImageFiltrationDlg::OnBnClickedButtonDrawCorrupt)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_CORRUPT, &CImageFiltrationDlg::OnBnClickedButtonClearCorrupt)
	ON_BN_CLICKED(IDC_CHECK_FIRST_GAUSS, &CImageFiltrationDlg::OnBnClickedCheckFirstGauss)
	ON_BN_CLICKED(IDC_CHECK_SECOND_GAUSS, &CImageFiltrationDlg::OnBnClickedCheckSecondGauss)
	ON_BN_CLICKED(IDC_CHECK_THIRD_GAUSS, &CImageFiltrationDlg::OnBnClickedCheckThirdGauss)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CImageFiltrationDlg::OnBnClickedButtonLoadImage)
END_MESSAGE_MAP()


// Обработчики сообщений CImageFiltrationDlg

BOOL CImageFiltrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// Активирование чекпоинтов.
	CHECK_FIRST_GAUSS.SetCheck(TRUE);
	CHECK_SECOND_GAUSS.SetCheck(TRUE);
	CHECK_THIRD_GAUSS.SetCheck(TRUE);

	// Привязка окон рисования.
	InputWnd = GetDlgItem(IDC_PICTURE_IMAGE);
	InputDc = InputWnd->GetDC();
	InputWnd->GetClientRect(&Input);

	// Обновление данных из интерфейса.
	UpdateData(TRUE);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CImageFiltrationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CImageFiltrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


Pixel::Pixel() {
	// Конструктор по умолчанию.
	value = 0.0;
	color = 0;
}


Pixel::Pixel(double in_value) {
	value = in_value;
	color = 0;
}


int Pixel::get_color_from_value(double min_value, double max_value) {
	double color_range = (max_value - min_value) / 256.;

	for (int i = 0; i <= 255; i++) {
		double limit_value = color_range * i + color_range;
		if (value <= limit_value) return i;
	}
}


void CImageFiltrationDlg::draw_image(vector<vector<Pixel>> image, CWnd* wnd, CDC* dc, CRect pic) {
	if (!image.empty()) {
		input_xmin = 0;
		input_xmax = image[0].size();
		input_ymin = 0;
		input_ymax = image.size();
	}
	else {
		input_xmin = 0;
		input_xmax = 1;
		input_ymin = 0;
		input_ymax = 1;
	}

	CBitmap bmp;
	CDC* MemDc;
	MemDc = new CDC;
	MemDc->CreateCompatibleDC(dc);

	double window_signal_width = pic.Width();
	double window_signal_height = pic.Height();
	input_xp = (window_signal_width / (input_xmax - input_xmin));
	input_yp = -(window_signal_height / (input_ymax - input_ymin));

	bmp.CreateCompatibleBitmap(dc, window_signal_width, window_signal_height);
	CBitmap* pBmp = (CBitmap*)MemDc->SelectObject(&bmp);

	if (!image.empty()) {
		// Отображение пикселей изображений.
		for (int i = 0; i < image.size(); i++) {
			for (int j = 0; j < image[i].size(); j++) {
				// Получение цвета.
				COLORREF color = RGB(image[i][j].color, image[i][j].color, image[i][j].color);


				double x_rect = 6;
				double y_rect = 6;
				MemDc->FillSolidRect(INPUT_TRANSFORM(j, i), (int)x_rect, (int)y_rect, color);
			}
		}
	}
	else {
		// Закрашивание фона.
		MemDc->FillSolidRect(pic, RGB(240, 240, 240));

		// Красный крест.
		CPen pen;
		pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		MemDc->SelectObject(&pen);
		MemDc->MoveTo(INPUT_TRANSFORM(input_xmin, input_ymin));
		MemDc->LineTo(INPUT_TRANSFORM(input_xmax, input_ymax));
		MemDc->MoveTo(INPUT_TRANSFORM(input_xmin, input_ymax));
		MemDc->LineTo(INPUT_TRANSFORM(input_xmax, input_ymin));

		// Граница.
		pen.DeleteObject();
		pen.CreatePen(PS_SOLID, -1, RGB(0, 0, 0));
		MemDc->SelectObject(&pen);
		MemDc->MoveTo(INPUT_TRANSFORM(input_xmin, input_ymin));
		MemDc->LineTo(INPUT_TRANSFORM(input_xmin, input_ymax));
		MemDc->MoveTo(INPUT_TRANSFORM(input_xmin, input_ymax));
		MemDc->LineTo(INPUT_TRANSFORM(input_xmax, input_ymax));
		MemDc->MoveTo(INPUT_TRANSFORM(input_xmax - 0.001 * input_xmax, input_ymax));
		MemDc->LineTo(INPUT_TRANSFORM(input_xmax - 0.001 * input_xmax, input_ymin));
		MemDc->MoveTo(INPUT_TRANSFORM(input_xmax, input_ymin + 0.001 * input_ymax));
		MemDc->LineTo(INPUT_TRANSFORM(input_xmin, input_ymin + 0.001 * input_ymax));
	}

	// Заполнение буфера.
	dc->BitBlt(0, 0, window_signal_width, window_signal_height, MemDc, 0, 0, SRCCOPY);
	delete MemDc;
}


void CImageFiltrationDlg::OnBnClickedButtonDrawImage()
{
	// Получение массива значений загруженного изображения.
	UpdateData(TRUE);
	input_image.clear();
	if (EDIT_IMAGE_HEIGHT != 0 && EDIT_IMAGE_WIDTH != 0) {
		// Заполнение вектора входного изображения.
		// TODO: Сделать быстрый алгоритм.
		input_image.resize(EDIT_IMAGE_HEIGHT);
		for (int i = 0; i < EDIT_IMAGE_HEIGHT; i++) {
			input_image[i].resize(EDIT_IMAGE_WIDTH);
		}

		for (int i = 0; i < EDIT_IMAGE_HEIGHT; i++) {
			for (int j = 0; j < EDIT_IMAGE_WIDTH; j++) {
				input_image[EDIT_IMAGE_HEIGHT - 1 - i][j].value = image.GetPixel(j, i);
			}
		}

		// Вычисление цвета.
		vector<double> values;
		for (int i = 0; i < input_image.size(); i++) {
			for (int j = 0; j < input_image[i].size(); j++) {
				values.push_back(input_image[i][j].value);
			}
		}
		double smallest_element = *min_element(values.begin(), values.end());
		double largest_element = *max_element(values.begin(), values.end());
		for (int i = 0; i < input_image.size(); i++) {
			for (int j = 0; j < input_image[i].size(); j++) {
				input_image[i][j].color = input_image[i][j].get_color_from_value(smallest_element, largest_element);
			}
		}
	}
	draw_image(input_image, InputWnd, InputDc, Input);
}


void CImageFiltrationDlg::OnBnClickedButtonClearImage()
{
	// Очистка вектора с исходным изображением.
	input_image.clear();

	// Перерисовка.
	draw_image(input_image, InputWnd, InputDc, Input);
}


void CImageFiltrationDlg::OnBnClickedButtonDrawFilter()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CImageFiltrationDlg::OnBnClickedButtonClearFilter()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CImageFiltrationDlg::OnBnClickedButtonDrawVeil()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CImageFiltrationDlg::OnBnClickedButtonClearVeil()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CImageFiltrationDlg::OnBnClickedButtonDrawCorrupt()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CImageFiltrationDlg::OnBnClickedButtonClearCorrupt()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CImageFiltrationDlg::OnBnClickedCheckFirstGauss()
{
	// Если чекбокс активен - активирование параметров первого купола.
	if (CHECK_FIRST_GAUSS.GetCheck() == BST_CHECKED) {
		EDIT_CONTROL_FIRST_AMPL.EnableWindow(TRUE);
		EDIT_CONTROL_FIRST_X_DISP.EnableWindow(TRUE);
		EDIT_CONTROL_FIRST_Y_DISP.EnableWindow(TRUE);
		EDIT_CONTROL_FIRST_X_SHIFT.EnableWindow(TRUE);
		EDIT_CONTROL_FIRST_Y_SHIFT.EnableWindow(TRUE);
	}
	// Иначе - блокировка параметров для первого купола.
	else if (CHECK_FIRST_GAUSS.GetCheck() == BST_UNCHECKED) {
		EDIT_CONTROL_FIRST_AMPL.EnableWindow(FALSE);
		EDIT_CONTROL_FIRST_X_DISP.EnableWindow(FALSE);
		EDIT_CONTROL_FIRST_Y_DISP.EnableWindow(FALSE);
		EDIT_CONTROL_FIRST_X_SHIFT.EnableWindow(FALSE);
		EDIT_CONTROL_FIRST_Y_SHIFT.EnableWindow(FALSE);
	}
}


void CImageFiltrationDlg::OnBnClickedCheckSecondGauss()
{
	// Если чекбокс активен - активирование параметров второго купола.
	if (CHECK_SECOND_GAUSS.GetCheck() == BST_CHECKED) {
		EDIT_CONTROL_SECOND_AMPL.EnableWindow(TRUE);
		EDIT_CONTROL_SECOND_X_DISP.EnableWindow(TRUE);
		EDIT_CONTROL_SECOND_Y_DISP.EnableWindow(TRUE);
		EDIT_CONTROL_SECOND_X_SHIFT.EnableWindow(TRUE);
		EDIT_CONTROL_SECOND_Y_SHIFT.EnableWindow(TRUE);
	}
	// Иначе - блокировка параметров для второго купола.
	else if (CHECK_SECOND_GAUSS.GetCheck() == BST_UNCHECKED) {
		EDIT_CONTROL_SECOND_AMPL.EnableWindow(FALSE);
		EDIT_CONTROL_SECOND_X_DISP.EnableWindow(FALSE);
		EDIT_CONTROL_SECOND_Y_DISP.EnableWindow(FALSE);
		EDIT_CONTROL_SECOND_X_SHIFT.EnableWindow(FALSE);
		EDIT_CONTROL_SECOND_Y_SHIFT.EnableWindow(FALSE);
	}
}


void CImageFiltrationDlg::OnBnClickedCheckThirdGauss()
{
	// Если чекбокс активен - активирование параметров третьего купола.
	if (CHECK_THIRD_GAUSS.GetCheck() == BST_CHECKED) {
		EDIT_CONTROL_THIRD_AMPL.EnableWindow(TRUE);
		EDIT_CONTROL_THIRD_X_DISP.EnableWindow(TRUE);
		EDIT_CONTROL_THIRD_Y_DISP.EnableWindow(TRUE);
		EDIT_CONTROL_THIRD_X_SHIFT.EnableWindow(TRUE);
		EDIT_CONTROL_THIRD_Y_SHIFT.EnableWindow(TRUE);
	}
	// Иначе - блокировка параметров для третьего купола.
	else if (CHECK_THIRD_GAUSS.GetCheck() == BST_UNCHECKED) {
		EDIT_CONTROL_THIRD_AMPL.EnableWindow(FALSE);
		EDIT_CONTROL_THIRD_X_DISP.EnableWindow(FALSE);
		EDIT_CONTROL_THIRD_Y_DISP.EnableWindow(FALSE);
		EDIT_CONTROL_THIRD_X_SHIFT.EnableWindow(FALSE);
		EDIT_CONTROL_THIRD_Y_SHIFT.EnableWindow(FALSE);
	}
}


void CImageFiltrationDlg::OnBnClickedButtonLoadImage()
{
	// Загрузка изображений.
	CFileDialog fileDialog(TRUE, NULL, L"*.png;*.bmp;*.jpg;*.jpeg");
	int res = fileDialog.DoModal();
	if (res != IDOK)
		return;

	CString file_name = fileDialog.GetPathName();
	HRESULT read_img = image.Load(file_name);

	EDIT_IMAGE_PATH.SetWindowTextW(file_name);
	EDIT_IMAGE_WIDTH = image.GetWidth();
	EDIT_IMAGE_HEIGHT = image.GetHeight();

	UpdateData(FALSE);
}
