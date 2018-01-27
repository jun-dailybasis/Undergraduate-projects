using Microsoft.Win32;
using System;
using System.Drawing;
using System.Drawing.Printing;
using System.Windows;
using System.Windows.Input;
using UbiPdf;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.15
    /// LastUpdate : 2017.08.30 (DLLNotFoundException에 대한 예외처리 추가)
    /// Description : Fun4_PrintHeader.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class fun4_PrintHeader : Window
    {
        /// <summary>
        /// textBox_file의 초기값
        /// </summary>
        private const string textBox_file_firstValue = @"C:\";
        /// <summary>
        /// 현재 오픈한 파일의 총 페이지 갯수
        /// </summary>
        private int totalPage = 0;
        /// <summary>
        /// 현재 오픈한 파일의 첫번째 페이지 이미지
        /// </summary>
        Image firstPage = null;

        /// <summary>
        /// 생성자. text_Box_file의 텍스트 초기화
        /// </summary>
        public fun4_PrintHeader()
        {
            try
            {
                InitializeComponent();
                textBox_file.Text = textBox_file_firstValue;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + e.Message);
            }
        }

        /// <summary>
        /// 미리보기 이미지를 업데이트
        /// </summary>
        private void updatePreview()
        {
            try
            {
                if (firstPage == null) return;
                if (textBox_file.Text == textBox_file_firstValue) return;

                Image drawingImage = firstPage.Clone() as Image;
                PdfPrint.addPrintHeader(drawingImage, StringAlignment.Far, makeHeader());
                image.Source = PdfToImage.imageToBitmapImage(drawingImage);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// 옵션에 따라 헤더에 들어갈 문자열을 작성, 반환
        /// </summary>
        /// <returns>헤더에 사용될 문자열</returns>
        private string makeHeader()
        {
            try
            {
                string header = "";
                PdfPrint.Option option = makeOption();
                if ((option & PdfPrint.Option.SHOW_PRINTDATE) == PdfPrint.Option.SHOW_PRINTDATE)
                    header += DateTime.Now.ToString("yyyy-M-d h:m:s tt") + "; \t";
                if ((option & PdfPrint.Option.SHOW_FILENAME) == PdfPrint.Option.SHOW_FILENAME)
                    header += textBox_file.Text + "; \t";
                if ((option & PdfPrint.Option.SHOW_PAGENUM) == PdfPrint.Option.SHOW_PAGENUM)
                    header += "1/" + totalPage;
                return header;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
                return "ERROR : " + GetType().ToString();
            }

        }

        /// <summary>
        /// UI에서 선택된 옵션에 따라 PdfPrint의 옵션을 만들어서 반환
        /// </summary>
        /// <returns></returns>
        private PdfPrint.Option makeOption()
        {
            try
            {
                PdfPrint.Option option = PdfPrint.Option.DEFAULT;

                if (checkBox_FileName.IsChecked == true)
                    option |= PdfPrint.Option.SHOW_FILENAME;
                if (checkBox_PageNumber.IsChecked == true)
                    option |= PdfPrint.Option.SHOW_PAGENUM;
                if (checkBox_PrintDate.IsChecked == true)
                    option |= PdfPrint.Option.SHOW_PRINTDATE;

                return option;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
                return PdfPrint.Option.INVALID;
            }

        }

        /// <summary>
        /// Open 버튼이 클릭된 경우 호출
        /// 파일을 선택하고 미리보기 이미지를 갱신한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                if (openFileDialog.ShowDialog() == true)
                {
                    Mouse.OverrideCursor = Cursors.Wait;
                    PdfPrint pdfPrint = new PdfPrint();
                    textBox_file.Text = openFileDialog.FileName;
                    pdfPrint.insertDocument(textBox_file.Text, 96, 1, 1);
                    firstPage = pdfPrint.createPreviewImage(0, 210 * 4, 297 * 4);
                    totalPage = pdfPrint.Count;
                    updatePreview();
                }
            }
            catch (DllNotFoundException exception)
            {
                Model.ExceptionMessageBoxTemplate.showGhostscriptDllNotFound(exception);
            }
            catch (Ghostscript.NET.GhostscriptException exception)
            {
                Model.ExceptionMessageBoxTemplate.showGhostscriptOnlySupportedEnglishPath(exception);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
            finally
            {
                Mouse.OverrideCursor = null;
            }
        }
        /// <summary>
        /// 체크박스가 클릭된 경우 호출
        /// 미리보기 이미지를 갱신한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void checkBox_Click(object sender, RoutedEventArgs e)
        {
            updatePreview();
        }

        /// <summary>
        /// 프린트 버튼이 클릭된 경우 호출
        /// 선택된 옵션에 따라 프린트한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>`
        private void btnPrint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (textBox_file.Text == textBox_file_firstValue) return;

                var prgDlg = new Progress_Dialog("Convert PDF to Print Document...");
                prgDlg.ProgressModel.TotalFileSize = new System.IO.FileInfo(textBox_file.Text).Length;
                prgDlg.ProgressModel.CurrentFileSize = prgDlg.ProgressModel.TotalFileSize;
                prgDlg.Show();
                PdfPrint pdfPrint = new PdfPrint();
                pdfPrint.insertDocument(textBox_file.Text, 96, prgDlg.ProgressModel);
                prgDlg.Close();
                prgDlg = new Progress_Dialog("PDF Print...");
                PrintDocument printDocument = pdfPrint.createPrintDocument(makeOption(), prgDlg.ProgressModel);
                System.Windows.Forms.PrintDialog printDialog = new System.Windows.Forms.PrintDialog();
                if (printDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    printDocument.PrinterSettings = printDialog.PrinterSettings;
                    prgDlg.resetCreatedTime();
                    prgDlg.Show();
                    printDocument.Print();
                }
                prgDlg.Close();
            }
            catch (DllNotFoundException exception)
            {
                Model.ExceptionMessageBoxTemplate.showGhostscriptDllNotFound(exception);
            }
            catch (Ghostscript.NET.GhostscriptException exception)
            {
                Model.ExceptionMessageBoxTemplate.showGhostscriptOnlySupportedEnglishPath(exception);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }
        /// <summary>
        /// 각각의 button의 핫키 부여
        /// 핫키 입력시 각각의 기능 수행
        /// </summary>
        private void PrintHeader_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.O)
            {
                btnOpen_Click(null, null);
            }
            else if (e.Key == Key.P)
            {
                btnPrint_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }
    }
}
