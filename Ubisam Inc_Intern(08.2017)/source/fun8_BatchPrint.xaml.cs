using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Drawing.Printing;
using Microsoft.Win32;
using UbiPdf;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 강예진, 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.09
    /// LastUpdate : 2017.08.30 (디렉토리를 드래그앤드롭한 경우의 처리 추가)
    /// Description : Fun08_BatchPrint.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class fun8_BatchPrint : Window
    {
        /// <summary>
        /// 생성자
        /// 사용가능한 프린터 목록을 읽어 Printer 콤보박스에 등록
        /// </summary>
        public fun8_BatchPrint()
        {
            try
            {
                InitializeComponent();
                PrinterSettings settings = new PrinterSettings();
                foreach (string printer in PrinterSettings.InstalledPrinters)
                {
                    comboBox_Printer.Items.Add(printer);
                    if (printer == settings.PrinterName)
                        comboBox_Printer.SelectedValue = printer;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// 프린터 콤보박스 값이 변경된 경우 호출
        /// 변경된 프린터에 따라 양면인쇄가 가능한지 판단, 양면인쇄 콤보박스 활성화/비활성화
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox_Printer_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                PrinterSettings settings = new PrinterSettings();
                settings.PrinterName = comboBox_Printer.SelectedValue as string;
                comboBox_Duplex.IsEnabled = settings.CanDuplex;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// 파일리스트 listBox를 좌클릭한 경우 호출
        /// 한개 혹은 복수의 파일을 선택하여 추가한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listBox_FileList_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Multiselect = true;
                openFileDialog.Filter = "Pdf files (*.pdf)|*.pdf|All files(*)|*";
                if (openFileDialog.ShowDialog() == true)
                {
                    foreach (string file in openFileDialog.FileNames)
                        addFileListItem(file);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// 파일리스트에 중복검사한 후 파일을 추가한다.
        /// </summary>
        /// <param name="file"></param>
        private void addFileListItem(string file)
        {
            if (!listBox_FileList.Items.Contains(file)) listBox_FileList.Items.Add(file);
            if (listBox_FileList.Items.Count == 1) showPreviewImage();
        }

        /// <summary>
        /// 프린트 버튼을 클릭한 경우 호출
        /// 옵션에 따라 PrintDocument를 생성, 프린트한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPrint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!tryParseOption(true)) return;

                int dpi = 0;
                Int32.TryParse(textBox_dpi.Text, out dpi);

                var prgDlg = new Progress_Dialog("Convert PDF to Print Document...");
                prgDlg.ProgressModel.TotalFileNum = listBox_FileList.Items.Count;
                foreach (string file in listBox_FileList.Items)
                {
                    prgDlg.ProgressModel.TotalFileSize += new System.IO.FileInfo(file).Length;
                }
                prgDlg.Show();
                PdfPrint pdfPrint = new PdfPrint();
                for (int i = 0; i < listBox_FileList.Items.Count; ++i)
                {
                    prgDlg.ProgressModel.CurrentFileNum = i + 1;
                    prgDlg.ProgressModel.CurrentFileSize = new System.IO.FileInfo(listBox_FileList.Items[i] as string).Length;
                    if (listBox_FileList.Items[i] as string != "")
                        pdfPrint.insertDocument(listBox_FileList.Items[i] as string, dpi, prgDlg.ProgressModel);
                }
                prgDlg.Close();
                prgDlg = new Progress_Dialog("PDF Print...");
                PrintDocument printDocument = pdfPrint.createPrintDocument(makeOption(), prgDlg.ProgressModel);
                printDocument.PrinterSettings.PrinterName = comboBox_Printer.Text;
                prgDlg.Show();
                printDocument.Print();
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
        /// 선택된 옵션이 문제가 없는지 검사한다.
        /// </summary>
        /// <param name="showMessage">메시지박스 출력여부</param>
        /// <returns>검사 결과, 가능하면 true를 반환한다.</returns>
        private bool tryParseOption(bool showMessage)
        {
            if (textBox_dpi == null || listBox_FileList == null) return false;

            int dpi = 0;
            bool parseOk = Int32.TryParse(textBox_dpi.Text, out dpi);
            if (!parseOk || dpi <= 0)
            {
                if (showMessage)
                    MessageBox.Show("dpi는 0보다 큰 숫자가 입력되어야 합니다.");
                return false;
            }
            if (listBox_FileList.Items.Count == 0)
            {
                if (showMessage)
                    MessageBox.Show("파일을 선택해주세요.");
                return false;
            }
            return true;
        }

        /// <summary>
        /// 선택된 옵션에 따라 PdfPrint.Option을 만들어 반환한다.
        /// </summary>
        /// <returns></returns>
        private PdfPrint.Option makeOption()
        {
            PdfPrint.Option option = PdfPrint.Option.DEFAULT;

            switch (comboBox_PageFit.SelectedIndex)
            {
                case 1: option |= PdfPrint.Option.WIDTH_BOUND; break;
                case 2: option |= PdfPrint.Option.HEIGHT_BOUND; break;
                case 3: option |= PdfPrint.Option.NOTCHANGE; break;
            }

            switch (comboBox_Duplex.SelectedIndex)
            {
                case 1: option |= PdfPrint.Option.DUPLEX_H; break;
                case 2: option |= PdfPrint.Option.DUPLEX_V; break;
            }

            switch (comboBox_SlideNum.SelectedIndex)
            {
                case 1: option |= PdfPrint.Option.PAGE1SLIDE2; break;
                case 2: option |= PdfPrint.Option.PAGE1SLIDE4; break;
            }

            switch (comboBox_Rotate.SelectedIndex)
            {
                case 1: option |= PdfPrint.Option.ROTATE90; break;
                case 2: option |= PdfPrint.Option.ROTATE180; break;
                case 3: option |= PdfPrint.Option.ROTATE270; break;
            }

            if (checkBox_FileName.IsChecked == true)
                option |= PdfPrint.Option.SHOW_FILENAME;
            if (checkBox_PageNumber.IsChecked == true)
                option |= PdfPrint.Option.SHOW_PAGENUM;

            return option;
        }

        /// <summary>
        /// Clear 버튼이 클릭된 경우 호출
        /// 파일리스트 listBox를 초기화한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                listBox_FileList.Items.Clear();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// 미리보기 이미지를 보인다.
        /// 옵션이 미리보기를 출력하지 못하면 중도에 리턴한다.
        /// </summary>
        private void showPreviewImage()
        {
            Mouse.OverrideCursor = Cursors.Wait;
            try
            {
                if (checkBox_Preview == null || (checkBox_Preview.IsChecked == false)) return;
                if (!tryParseOption(false)) return;

                int dpi = 0;
                Int32.TryParse(textBox_dpi.Text, out dpi);

                PdfPrint.Option option = makeOption();
                int lastPage = 1;
                if ((option & PdfPrint.Option.PAGE1SLIDE2) == PdfPrint.Option.PAGE1SLIDE2)
                    lastPage = 2;
                else if ((option & PdfPrint.Option.PAGE1SLIDE4) == PdfPrint.Option.PAGE1SLIDE4)
                    lastPage = 4;

                PdfPrint pdfPrint = new PdfPrint();
                pdfPrint.insertDocument(listBox_FileList.Items[0] as string, dpi, 1, lastPage);
                System.Drawing.Image image = pdfPrint.createPreviewImage(0, 210 * 4, 297 * 4, makeOption());

                image_Preview.Source = PdfToImage.imageToBitmapImage(image);
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
        /// 콤보박스 옵션이 변경된 경우 호출
        /// 미리보기를 수정한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBoxOption_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            showPreviewImage();
        }

        /// <summary>
        /// 체크박스 옵션이 변경된 경우 호출
        /// 미리보기를 수정한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void checkBoxOption_SelectionChanged(object sender, RoutedEventArgs e)
        {
            showPreviewImage();
        }

        /// <summary>
        /// 파일리스트 listBox에 드래그앤드롭된 경우 호출
        /// 드롭된 파일들을 리스트에 추가한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listBox_FileList_Drop(object sender, DragEventArgs e)
        {
            try
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {
                    string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                    foreach (string file in Model.FileExplorer.filesAndInSubDirectoryFiles(files))
                    {
                        if (System.IO.Path.GetExtension(file) != ".pdf") continue;
                        addFileListItem(file);
                    }
                }
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
        private void BatchPrint_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.P)
            {
                btnPrint_Click(null, null);
            }
            else if (e.Key == Key.C)
            {
                btnClear_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }
    }

}
