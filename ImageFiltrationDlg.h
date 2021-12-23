#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
using namespace std;
using namespace cv;


class Pixel {
public:
	double value;
	int color;

	/**
	Конструктор по умолчанию.
	*/
	Pixel();

	/**
	Конструктор с параметром.
	@param in_value: Значение пикселя.
	*/
	Pixel(double in_value);

	/**
	Перевод значения пикселя в цвет.
	@param min_value: Минимальное значение пикселя в изображении.
	@param max_value: Максимальное значение пикселя в изображении.
	@return Значение цвета [0-255].
	*/
	int get_color_from_value(double min_value, double max_value);
};



// Диалоговое окно CImageFiltrationDlg
class CImageFiltrationDlg : public CDialogEx
{
// Создание
public:
	CImageFiltrationDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEFILTRATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	//////////////////////////////
	/// Переменные
	//////////////////////////////

	CEdit EDIT_CONTROL_FIRST_AMPL;
	CEdit EDIT_CONTROL_SECOND_AMPL;
	CEdit EDIT_CONTROL_THIRD_AMPL;
	CEdit EDIT_CONTROL_FIRST_X_SHIFT;
	CEdit EDIT_CONTROL_SECOND_X_SHIFT;
	CEdit EDIT_CONTROL_THIRD_X_SHIFT;
	CEdit EDIT_CONTROL_FIRST_Y_SHIFT;
	CEdit EDIT_CONTROL_SECOND_Y_SHIFT;
	CEdit EDIT_CONTROL_THIRD_Y_SHIFT;
	CEdit EDIT_CONTROL_FIRST_X_DISP;
	CEdit EDIT_CONTROL_SECOND_X_DISP;
	CEdit EDIT_CONTROL_THIRD_X_DISP;
	CEdit EDIT_CONTROL_FIRST_Y_DISP;
	CEdit EDIT_CONTROL_SECOND_Y_DISP;
	CEdit EDIT_CONTROL_THIRD_Y_DISP;
	CEdit EDIT_IMAGE_PATH;
	CButton CHECK_FIRST_GAUSS;
	CButton CHECK_SECOND_GAUSS;
	CButton CHECK_THIRD_GAUSS;
	CButton RADIO_LINEAR_FILTER;
	CButton RADIO_MEDIAN_FILTER;
	double EDIT_FIRST_AMPL;
	double EDIT_SECOND_AMPL;
	double EDIT_THIRD_AMPL;
	double EDIT_FIRST_X_SHIFT;
	double EDIT_SECOND_X_SHIFT;
	double EDIT_THIRD_X_SHIFT;
	double EDIT_FIRST_Y_SHIFT;
	double EDIT_SECOND_Y_SHIFT;
	double EDIT_THIRD_Y_SHIFT;
	double EDIT_FIRST_X_DISP;
	double EDIT_SECOND_X_DISP;
	double EDIT_THIRD_X_DISP;
	double EDIT_FIRST_Y_DISP;
	double EDIT_SECOND_Y_DISP;
	double EDIT_THIRD_Y_DISP;
	double EDIT_FILTRATION_CRITERION;
	int EDIT_IMAGE_HEIGHT;
	int EDIT_IMAGE_WIDTH;
	int EDIT_KERNEL_SIZE;
	
	// Переменные, связываемые с окном исходного изображения.
	CWnd* InputWnd;
	CDC* InputDc;
	CRect Input;
	double input_xmin, input_xmax, input_ymin, input_ymax, input_xp, input_yp;

	// Переменные, связываемые с окном для отображения вуали.
	CWnd* VeilWnd;
	CDC* VeilDc;
	CRect Veil;
	double veil_xmin, veil_xmax, veil_ymin, veil_ymax, veil_xp, veil_yp;

	// Переменные, связываемые с окном для отображения искаженного изображения.
	CWnd* CorruptWnd;
	CDC* CorruptDc;
	CRect Corrupt;
	double corrupt_xmin, corrupt_xmax, corrupt_ymin, corrupt_ymax, corrupt_xp, corrupt_yp;

	// Переменные, связываемые с окном для отображения отфильтрованного изображения.
	CWnd* FilterWnd;
	CDC* FilterDc;
	CRect Filter;
	double filter_xmin, filter_xmax, filter_ymin, filter_ymax, filter_xp, filter_yp;

	// Переменные, связываемые с окном для отображения оценки вуали.
	CWnd* VeilRatingWnd;
	CDC* VeilRatingDc;
	CRect VeilRating;
	double veil_rating_xmin, veil_rating_xmax, veil_rating_ymin, veil_rating_ymax, veil_rating_xp, veil_rating_yp;
	
	//////////////////////////////
	/// Глобальные переменные
	//////////////////////////////
	
	CImage image;
	vector<vector<Pixel>> input_image;
	vector<vector<Pixel>> veil_image;
	vector<vector<Pixel>> corrupt_image;
	vector<vector<Pixel>> filtered_image;
	vector<vector<Pixel>> veil_rating_image;

	//////////////////////////////
	/// Функции
	//////////////////////////////
	void draw_image(vector<vector<Pixel>> image, CWnd* wnd, CDC* dc, CRect rect, string image_name);
	vector<vector<Pixel>> calculate_color_of_image(vector<vector<Pixel>> image_vec);

	//////////////////////////////
	/// Обработчики нажатий
	//////////////////////////////

	afx_msg void OnBnClickedButtonDrawImage();
	afx_msg void OnBnClickedButtonClearImage();
	afx_msg void OnBnClickedButtonDrawFilter();
	afx_msg void OnBnClickedButtonClearFilter();
	afx_msg void OnBnClickedButtonDrawVeil();
	afx_msg void OnBnClickedButtonClearVeil();
	afx_msg void OnBnClickedButtonDrawCorrupt();
	afx_msg void OnBnClickedButtonClearCorrupt();
	afx_msg void OnBnClickedCheckFirstGauss();
	afx_msg void OnBnClickedCheckSecondGauss();
	afx_msg void OnBnClickedCheckThirdGauss();
	afx_msg void OnBnClickedButtonLoadImage();
};