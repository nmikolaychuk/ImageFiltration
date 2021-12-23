
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

using namespace std;
using namespace cv;

#define INPUT_TRANSFORM(x,y) (input_xp*((x)-input_xmin)),(input_yp*((y)-input_ymax))
#define VEIL_TRANSFORM(x,y) (veil_xp*((x)-veil_xmin)),(veil_yp*((y)-veil_ymax))
#define CORRUPT_TRANSFORM(x,y) (corrupt_xp*((x)-corrupt_xmin)),(corrupt_yp*((y)-corrupt_ymax))
#define FILTER_TRANSFORM(x,y) (filter_xp*((x)-filter_xmin)),(filter_yp*((y)-filter_ymax))


CImageFiltrationDlg::CImageFiltrationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEFILTRATION_DIALOG, pParent)
	, EDIT_FIRST_AMPL(1)
	, EDIT_SECOND_AMPL(1)
	, EDIT_THIRD_AMPL(1)
	, EDIT_FIRST_X_SHIFT(30)
	, EDIT_SECOND_X_SHIFT(480)
	, EDIT_THIRD_X_SHIFT(400)
	, EDIT_FIRST_Y_SHIFT(300)
	, EDIT_SECOND_Y_SHIFT(480)
	, EDIT_THIRD_Y_SHIFT(30)
	, EDIT_FIRST_X_DISP(120)
	, EDIT_SECOND_X_DISP(160)
	, EDIT_THIRD_X_DISP(170)
	, EDIT_FIRST_Y_DISP(120)
	, EDIT_SECOND_Y_DISP(160)
	, EDIT_THIRD_Y_DISP(170)
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
	RADIO_LINEAR_FILTER.SetCheck(TRUE);

	// Привязка окон рисования.
	InputWnd = GetDlgItem(IDC_PICTURE_IMAGE);
	InputDc = InputWnd->GetDC();
	InputWnd->GetClientRect(&Input);

	VeilWnd = GetDlgItem(IDC_PICTURE_VEIL);
	VeilDc = VeilWnd->GetDC();
	VeilWnd->GetClientRect(&Veil);

	CorruptWnd = GetDlgItem(IDC_PICTURE_CORRUPT);
	CorruptDc = CorruptWnd->GetDC();
	CorruptWnd->GetClientRect(&Corrupt);

	FilterWnd = GetDlgItem(IDC_PICTURE_FILTER);
	FilterDc = FilterWnd->GetDC();
	FilterWnd->GetClientRect(&Filter);

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

		// Отрисовка графиков.
		draw_image(input_image, InputWnd, InputDc, Input, "input");
		draw_image(veil_image, VeilWnd, VeilDc, Veil, "veil");
		draw_image(corrupt_image, CorruptWnd, CorruptDc, Corrupt, "corrupt");
		draw_image(filtered_image, FilterWnd, FilterDc, Filter, "filter");
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
		if (value < limit_value) return i;
	}
}


void CImageFiltrationDlg::draw_image(vector<vector<Pixel>> image, CWnd* wnd, CDC* dc, CRect pic, string image_name) {
	double xmin = 0.0;
	double xmax = 1.0;
	double ymin = 0.0;
	double ymax = 1.0;

	if (!image.empty()) {
		xmin = 0;
		xmax = image[0].size();
		ymin = 0;
		ymax = image.size();
	}

	if (image_name == "input") {
		input_xmin = xmin;
		input_xmax = xmax;
		input_ymin = ymin;
		input_ymax = ymax;
	}
	else if (image_name == "veil") {
		veil_xmin = xmin;
		veil_xmax = xmax;
		veil_ymin = ymin;
		veil_ymax = ymax;
	}
	else if (image_name == "corrupt") {
		corrupt_xmin = xmin;
		corrupt_xmax = xmax;
		corrupt_ymin = ymin;
		corrupt_ymax = ymax;
	}
	else if (image_name == "filter") {
		filter_xmin = xmin;
		filter_xmax = xmax;
		filter_ymin = ymin;
		filter_ymax = ymax;
	}
	else {
		return;
	}

	CBitmap bmp;
	CDC* MemDc;
	MemDc = new CDC;
	MemDc->CreateCompatibleDC(dc);

	double window_signal_width = pic.Width();
	double window_signal_height = pic.Height();

	if (image_name == "input") {
		input_xp = (window_signal_width / (input_xmax - input_xmin));
		input_yp = -(window_signal_height / (input_ymax - input_ymin));
	}
	else if (image_name == "veil") {
		veil_xp = (window_signal_width / (veil_xmax - veil_xmin));
		veil_yp = -(window_signal_height / (veil_ymax - veil_ymin));
	}
	else if (image_name == "corrupt") {
		corrupt_xp = (window_signal_width / (corrupt_xmax - corrupt_xmin));
		corrupt_yp = -(window_signal_height / (corrupt_ymax - corrupt_ymin));
	}
	else if (image_name == "filter") {
		filter_xp = (window_signal_width / (filter_xmax - filter_xmin));
		filter_yp = -(window_signal_height / (filter_ymax - filter_ymin));
	}

	bmp.CreateCompatibleBitmap(dc, window_signal_width, window_signal_height);
	CBitmap* pBmp = (CBitmap*)MemDc->SelectObject(&bmp);

	if (!image.empty()) {
		// Отображение пикселей изображений.
		for (int i = 0; i < image.size(); i++) {
			for (int j = 0; j < image[i].size(); j++) {
				// Получение цвета.
				COLORREF color;
				if (image[i][j].color > 255) {
					color = RGB(255, 255, 255);
				}
				else {
					color = RGB(image[i][j].color, image[i][j].color, image[i][j].color);
				}


				double x_rect = 5;
				double y_rect = 5;
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

		if (image_name == "input") {
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
		else if (image_name == "veil") {
			MemDc->MoveTo(VEIL_TRANSFORM(veil_xmin, veil_ymin));
			MemDc->LineTo(VEIL_TRANSFORM(veil_xmax, veil_ymax));
			MemDc->MoveTo(VEIL_TRANSFORM(veil_xmin, veil_ymax));
			MemDc->LineTo(VEIL_TRANSFORM(veil_xmax, veil_ymin));

			// Граница.
			pen.DeleteObject();
			pen.CreatePen(PS_SOLID, -1, RGB(0, 0, 0));
			MemDc->SelectObject(&pen);
			MemDc->MoveTo(VEIL_TRANSFORM(veil_xmin, veil_ymin));
			MemDc->LineTo(VEIL_TRANSFORM(veil_xmin, veil_ymax));
			MemDc->MoveTo(VEIL_TRANSFORM(veil_xmin, veil_ymax));
			MemDc->LineTo(VEIL_TRANSFORM(veil_xmax, veil_ymax));
			MemDc->MoveTo(VEIL_TRANSFORM(veil_xmax - 0.001 * veil_xmax, veil_ymax));
			MemDc->LineTo(VEIL_TRANSFORM(veil_xmax - 0.001 * veil_xmax, veil_ymin));
			MemDc->MoveTo(VEIL_TRANSFORM(veil_xmax, veil_ymin + 0.001 * veil_ymax));
			MemDc->LineTo(VEIL_TRANSFORM(veil_xmin, veil_ymin + 0.001 * veil_ymax));
		}
		else if (image_name == "corrupt") {
			MemDc->MoveTo(CORRUPT_TRANSFORM(corrupt_xmin, corrupt_ymin));
			MemDc->LineTo(CORRUPT_TRANSFORM(corrupt_xmax, corrupt_ymax));
			MemDc->MoveTo(CORRUPT_TRANSFORM(corrupt_xmin, corrupt_ymax));
			MemDc->LineTo(CORRUPT_TRANSFORM(corrupt_xmax, corrupt_ymin));

			// Граница.
			pen.DeleteObject();
			pen.CreatePen(PS_SOLID, -1, RGB(0, 0, 0));
			MemDc->SelectObject(&pen);
			MemDc->MoveTo(CORRUPT_TRANSFORM(corrupt_xmin, corrupt_ymin));
			MemDc->LineTo(CORRUPT_TRANSFORM(corrupt_xmin, corrupt_ymax));
			MemDc->MoveTo(CORRUPT_TRANSFORM(corrupt_xmin, corrupt_ymax));
			MemDc->LineTo(CORRUPT_TRANSFORM(corrupt_xmax, corrupt_ymax));
			MemDc->MoveTo(CORRUPT_TRANSFORM(corrupt_xmax - 0.001 * corrupt_xmax, corrupt_ymax));
			MemDc->LineTo(CORRUPT_TRANSFORM(corrupt_xmax - 0.001 * corrupt_xmax, corrupt_ymin));
			MemDc->MoveTo(CORRUPT_TRANSFORM(corrupt_xmax, corrupt_ymin + 0.001 * corrupt_ymax));
			MemDc->LineTo(CORRUPT_TRANSFORM(corrupt_xmin, corrupt_ymin + 0.001 * corrupt_ymax));
		}
		else if (image_name == "filter") {
			MemDc->MoveTo(FILTER_TRANSFORM(filter_xmin, filter_ymin));
			MemDc->LineTo(FILTER_TRANSFORM(filter_xmax, filter_ymax));
			MemDc->MoveTo(FILTER_TRANSFORM(filter_xmin, filter_ymax));
			MemDc->LineTo(FILTER_TRANSFORM(filter_xmax, filter_ymin));

			// Граница.
			pen.DeleteObject();
			pen.CreatePen(PS_SOLID, -1, RGB(0, 0, 0));
			MemDc->SelectObject(&pen);
			MemDc->MoveTo(FILTER_TRANSFORM(filter_xmin, filter_ymin));
			MemDc->LineTo(FILTER_TRANSFORM(filter_xmin, filter_ymax));
			MemDc->MoveTo(FILTER_TRANSFORM(filter_xmin, filter_ymax));
			MemDc->LineTo(FILTER_TRANSFORM(filter_xmax, filter_ymax));
			MemDc->MoveTo(FILTER_TRANSFORM(filter_xmax - 0.001 * filter_xmax, filter_ymax));
			MemDc->LineTo(FILTER_TRANSFORM(filter_xmax - 0.001 * filter_xmax, filter_ymin));
			MemDc->MoveTo(FILTER_TRANSFORM(filter_xmax, filter_ymin + 0.001 * filter_ymax));
			MemDc->LineTo(FILTER_TRANSFORM(filter_xmin, filter_ymin + 0.001 * filter_ymax));
		}
	}

	// Заполнение буфера.
	dc->BitBlt(0, 0, window_signal_width, window_signal_height, MemDc, 0, 0, SRCCOPY);
	delete MemDc;
}


vector<vector<Pixel>> CImageFiltrationDlg::calculate_color_of_image(vector<vector<Pixel>> image_vec) {
	if (!image_vec.empty()) {
		vector<double> values;
		for (int i = 0; i < image_vec.size(); i++) {
			for (int j = 0; j < image_vec[i].size(); j++) {
				values.push_back(image_vec[i][j].value);
			}
		}

		double smallest_element = *min_element(values.begin(), values.end());
		double largest_element = *max_element(values.begin(), values.end());
		for (int i = 0; i < image_vec.size(); i++) {
			for (int j = 0; j < image_vec[i].size(); j++) {
				int color = image_vec[i][j].get_color_from_value(smallest_element, largest_element);
				image_vec[i][j].color = color;
			}
		}
		return image_vec;
	}
}


void CImageFiltrationDlg::OnBnClickedButtonDrawImage()
{
	// Получение массива значений загруженного изображения.
	UpdateData(TRUE);

	if (input_image.empty()) {
		// Получение полного пути к изображению.
		CString im_path_c;
		EDIT_IMAGE_PATH.GetWindowTextW(im_path_c);

		// Конвертация CString -> std::string.
		CT2CA pszConvertedAnsiString(im_path_c);
		std::string image_path(pszConvertedAnsiString);

		// Загрузка изображения.
		Mat I = imread(image_path, IMREAD_UNCHANGED);
		if (I.empty())
		{
			MessageBox(L"Ошибка при чтении изображения: изображение не найдено!", L"Ошибка", MB_OK | MB_ICONERROR);
			draw_image(input_image, InputWnd, InputDc, Input, "input");
			return;
		}

		input_image.clear();
		input_image.resize(I.rows);
		for (int i = 0; i < I.rows; i++) {
			input_image[i].resize(I.cols);
		}

		// Mat -> vector<vector<Pixel>>.
		for (int y = 0; y < I.rows; y++)
		{
			for (int x = 0; x < I.cols; x++)
			{
				Vec3b& color = I.at<Vec3b>(y, x);
				input_image[I.rows - 1 - y][x].color = 0.299 * (double)color[0] + 0.587 * (double)color[1] + 0.114 * (double)color[2];
				input_image[I.rows - 1 - y][x].value = input_image[I.rows - 1 - y][x].color;
			}
		}
	}

	draw_image(input_image, InputWnd, InputDc, Input, "input");
}


void CImageFiltrationDlg::OnBnClickedButtonClearImage()
{
	// Очистка вектора с исходным изображением.
	input_image.clear();

	// Перерисовка.
	draw_image(input_image, InputWnd, InputDc, Input, "input");
}


void CImageFiltrationDlg::OnBnClickedButtonDrawFilter()
{
	UpdateData(TRUE);
	if (corrupt_image.empty()) {
		MessageBox(L"Отсутствует искаженное изображение!", L"Ошибка", MB_OK | MB_ICONERROR);
	}
	else {
		// Получение Mat из corrupt_image.
		Mat gray(corrupt_image.size(), corrupt_image[0].size(), CV_8UC1, Scalar(255));
		Mat input(input_image.size(), input_image[0].size(), CV_8UC1, Scalar(255));

		for (int y = 0; y < gray.rows; y++)
		{
			for (int x = 0; x < gray.cols; x++)
			{
				gray.at<uchar>(y, x) = (int)corrupt_image[gray.rows - 1 - y][x].color;
				input.at<uchar>(y, x) = (int)input_image[input.rows - 1 - y][x].color;
			}
		}

		// Проверка на наличие размера ядра.
		if (EDIT_KERNEL_SIZE == 0) {
			MessageBox(L"Не был указан размер ядра фильтра!", L"Ошибка", MB_OK | MB_ICONERROR);
		}
		else {
			// Выбор фильтра.
			Mat result;
			if (RADIO_LINEAR_FILTER.GetCheck() == BST_CHECKED) {
				blur(gray, result, Size(EDIT_KERNEL_SIZE, EDIT_KERNEL_SIZE), Point(-1, -1), BORDER_CONSTANT);
			}
			else if (RADIO_MEDIAN_FILTER.GetCheck() == BST_CHECKED) {
				medianBlur(gray, result, EDIT_KERNEL_SIZE);
			}

			// Вычитание отифльтрованного из зашумленного.
			Mat filtered = gray;
			double c = 0.89;
			for (int i = 0; i < gray.rows; i++) {
				for (int j = 0; j < gray.cols; j++) {
					filtered.at<uchar>(i, j) = c * gray.at<uchar>(i, j) - (1. - c) * result.at<uchar>(i, j);
				}
			}

			// Вычисление критерия (градиентный).
			float sobel_x[9] = { -1, -2, -1,
								0, 0, 0,
								1, 2, 1 };

			float sobel_y[9] = { -1, 0, 1,
								-2, 0, 2,
								-1, 0, 1 };
			Mat sobel_filter_x = Mat(3, 3, CV_32F, sobel_x);
			Mat sobel_filter_y = Mat(3, 3, CV_32F, sobel_y);
			Mat grad_input_x, grad_input_y;
			Mat grad_filter_x, grad_filter_y;
			// Вычисления градиентов исходного и отфильтрованного изображения.
			filter2D(input, grad_input_x, -1, sobel_filter_x, Point(-1, -1), 0, cv::BORDER_DEFAULT);
			filter2D(input, grad_input_y, -1, sobel_filter_y, Point(-1, -1), 0, cv::BORDER_DEFAULT);
			filter2D(filtered, grad_filter_x, -1, sobel_filter_x, Point(-1, -1), 0, cv::BORDER_DEFAULT);
			filter2D(filtered, grad_filter_y, -1, sobel_filter_y, Point(-1, -1), 0, cv::BORDER_DEFAULT);

			// Получение яркости.
			Mat grad_input(input_image.size(), input_image[0].size(), CV_8UC1, Scalar(255));
			Mat grad_filter(input_image.size(), input_image[0].size(), CV_8UC1, Scalar(255));
			for (int i = 0; i < grad_input_x.rows; i++) {
				for (int j = 0; j < grad_input_x.cols; j++) {
					grad_input.at<uchar>(i, j) = sqrt((double)grad_input_x.at<uchar>(i, j) * (double)grad_input_x.at<uchar>(i, j) +
						(double)grad_input_y.at<uchar>(i, j) * (double)grad_input_y.at<uchar>(i, j));
					grad_filter.at<uchar>(i, j) = sqrt((double)grad_filter_x.at<uchar>(i, j) * (double)grad_filter_x.at<uchar>(i, j) +
						(double)grad_filter_y.at<uchar>(i, j) * (double)grad_filter_y.at<uchar>(i, j));
				}
			}

			// Вычисление невязки - среднеквадратичное отклонение по градиентам.
			double upper = 0.0;
			double lower = 0.0;
			for (int i = 0; i < grad_input.rows; i++) {
				for (int j = 0; j < grad_input.cols; j++) {
					upper += ((double)grad_input.at<uchar>(i, j) - (double)grad_filter.at<uchar>(i, j)) *
						((double)grad_input.at<uchar>(i, j) - (double)grad_filter.at<uchar>(i, j));
					lower += (double)grad_input.at<uchar>(i, j) * (double)grad_input.at<uchar>(i, j);
				}
			}
			EDIT_FILTRATION_CRITERION = upper / lower;
			UpdateData(FALSE);

			filtered_image.clear();
			filtered_image.resize(filtered.rows);
			for (int i = 0; i < filtered.rows; i++) {
				filtered_image[i].resize(filtered.cols);
			}

			// Mat -> vector<vector<Pixel>>.
			for (int y = 0; y < filtered.rows; y++)
			{
				for (int x = 0; x < filtered.cols; x++)
				{
					filtered_image[filtered.rows - 1 - y][x].color = (double)filtered.at<uchar>(y, x);
					filtered_image[filtered.rows - 1 - y][x].value = filtered_image[filtered.rows - 1 - y][x].color;
				}
			}

			filtered_image = calculate_color_of_image(filtered_image);
		}
	}

	draw_image(filtered_image, FilterWnd, FilterDc, Filter, "filter");
}


void CImageFiltrationDlg::OnBnClickedButtonClearFilter()
{
	// Очистка вектора с исходным изображением.
	filtered_image.clear();

	// Перерисовка.
	draw_image(filtered_image, FilterWnd, FilterDc, Filter, "filter");
}


void CImageFiltrationDlg::OnBnClickedButtonDrawVeil()
{
	UpdateData(TRUE);
	if (!input_image.empty()) {
		veil_image.clear();
		// Инициализация векторов с конфигурацией куполов.
		vector<double> amplitude;
		vector<double> sigma_x;
		vector<double> sigma_y;
		vector<double> center_x;
		vector<double> center_y;

		// Заполнение параметров в зависимости от выбранных куполов.
		if (CHECK_FIRST_GAUSS.GetCheck() == BST_CHECKED) {
			amplitude.push_back(EDIT_FIRST_AMPL);
			sigma_x.push_back(EDIT_FIRST_X_DISP);
			sigma_y.push_back(EDIT_FIRST_Y_DISP);
			center_x.push_back(EDIT_FIRST_X_SHIFT);
			center_y.push_back(EDIT_FIRST_Y_SHIFT);
		}

		if (CHECK_SECOND_GAUSS.GetCheck() == BST_CHECKED) {
			amplitude.push_back(EDIT_SECOND_AMPL);
			sigma_x.push_back(EDIT_SECOND_X_DISP);
			sigma_y.push_back(EDIT_SECOND_Y_DISP);
			center_x.push_back(EDIT_SECOND_X_SHIFT);
			center_y.push_back(EDIT_SECOND_Y_SHIFT);
		}

		if (CHECK_THIRD_GAUSS.GetCheck() == BST_CHECKED) {
			amplitude.push_back(EDIT_THIRD_AMPL);
			sigma_x.push_back(EDIT_THIRD_X_DISP);
			sigma_y.push_back(EDIT_THIRD_Y_DISP);
			center_x.push_back(EDIT_THIRD_X_SHIFT);
			center_y.push_back(EDIT_THIRD_Y_SHIFT);
		}

		if (amplitude.empty()) {
			MessageBox(L"Не включен ни один из гауссовых куполов для формирования вуали!", L"Ошибка", MB_OK | MB_ICONERROR);
			return;
		}

		// Заполнение вектора вуали.
		for (int y = 0; y < input_image.size(); y++) {
			vector<Pixel> row;
			for (int x = 0; x < input_image[y].size(); x++) {
				double signal = 0.0;
				for (int i = 0; i < amplitude.size(); i++) {
					double exp_expression_first = ((x - center_x[i]) * (x - center_x[i]));
					double exp_expression_second = ((y - center_y[i]) * (y - center_y[i]));
					signal += amplitude[i] * exp(-(exp_expression_first + exp_expression_second) / (2. * sigma_x[i] * sigma_y[i]));
				}

				Pixel pix(signal);
				row.push_back(pix);
			}
			veil_image.push_back(row);
		}

		veil_image = calculate_color_of_image(veil_image);
	}
	else {
		MessageBox(L"Не загружено исходное изображение!", L"Ошибка", MB_OK | MB_ICONERROR);
	}

	draw_image(veil_image, VeilWnd, VeilDc, Veil, "veil");
}


void CImageFiltrationDlg::OnBnClickedButtonClearVeil()
{
	veil_image.clear();
	draw_image(veil_image, VeilWnd, VeilDc, Veil, "veil");
}


void CImageFiltrationDlg::OnBnClickedButtonDrawCorrupt()
{
	UpdateData(TRUE);
	if (input_image.empty()) {
		MessageBox(L"Не загружено исходное изображение!", L"Ошибка", MB_OK | MB_ICONERROR);
	}
	else {
		if (veil_image.empty()) {
			MessageBox(L"Не сформирована вуаль!", L"Ошибка", MB_OK | MB_ICONERROR);
		}
		else {
			corrupt_image.clear();
			corrupt_image.resize(input_image.size());
			for (int i = 0; i < input_image.size(); i++) {
				corrupt_image[i].resize(input_image[i].size());
			}

			vector<double> values;
			for (int i = 0; i < corrupt_image.size(); i++) {
				for (int j = 0; j < corrupt_image[i].size(); j++) {
					values.push_back(corrupt_image[i][j].value);
				}
			}

			double smallest_element = *min_element(values.begin(), values.end());
			double largest_element = *max_element(values.begin(), values.end());

			double K = (largest_element - smallest_element) / (largest_element + smallest_element);

			for (int i = 0; i < input_image.size(); i++) {
				for (int j = 0; j < input_image[i].size(); j++) {
					corrupt_image[i][j] = input_image[i][j].value * (veil_image[i][j].color/255.);
				}
			}

			corrupt_image = calculate_color_of_image(corrupt_image);
		}
	}

	draw_image(corrupt_image, CorruptWnd, CorruptDc, Corrupt, "corrupt");
}


void CImageFiltrationDlg::OnBnClickedButtonClearCorrupt()
{
	corrupt_image.clear();
	draw_image(corrupt_image, CorruptWnd, CorruptDc, Corrupt, "corrupt");
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

	if (EDIT_IMAGE_PATH.GetWindowTextLengthW() > 0) {
		CImage new_img;
		image = new_img;
	}
	CString file_name = fileDialog.GetPathName();
	HRESULT read_img = image.Load(file_name);

	EDIT_IMAGE_PATH.SetWindowTextW(file_name);
	EDIT_IMAGE_WIDTH = image.GetWidth();
	EDIT_IMAGE_HEIGHT = image.GetHeight();

	UpdateData(FALSE);
}
